/*
 * $Id$
 * -----------------------
 * All amazon backend functions
 */

/*
 * A lot was shamelessly copied from:
 * http://www.xmlsoft.org/examples/index.html#parse3.c
 * Thx to the author Dodji Seketeli
 */

/* For the XML stuff */
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <strings.h>

/* And the rest */
#include <string.h>
#include <stdio.h>
#include <ctype.h> 
#include "dbook.h"

#define MAPLEN 6
xmlDoc *doc = NULL;

int dbook_amazon_populate(xmlNode * a_node, dbook_book *book) {

    char *amazonMap[MAPLEN][2] = {{"Author", book->author},
                                  {"Title", book->title},
                                  {"Publisher", book->publisher},
                                  {"PublicationDate", book->date},
                                  {"ISBN", book->isbn}};
                                  //{"NumberOfPages", book->pagecount}};
    
    int ret = DBOOK_TRUE;
    xmlNode *cur_node = NULL;
    xmlChar *key;
    int i;

    /* check dbook is initialised */
    if (dbook_check_initialised() == DBOOK_FALSE) {
        return DBOOK_FALSE;
    }

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            for (i =0; i < MAPLEN; i++){

                if (xmlStrcmp((const xmlChar *) amazonMap[i][0],
                            cur_node->name) == 0){

                    /*
                     * We have found something in the map.
                     * Check if the child is of type 
                     */

                    if (cur_node->children->type == XML_TEXT_NODE){
                        key = xmlNodeListGetString(doc,
                                cur_node->xmlChildrenNode, 1);
                        
                        /* Match the fields we are interested in */
                        if(strncasecmp(cur_node->name, amazonMap[i][0], 
                                    ( sizeof(char*) * strlen(cur_node->name)) ) == 0){
                            strncpy(amazonMap[i][1], key, sizeof(char*)*strlen(key) );
                        }

                        xmlFree(key);
                    } else {
                        DBOOK_SET_ERROR(DBOOK_ERR_AMAZON_ERROR);
                        return DBOOK_FALSE;
                    }
                } else if(xmlStrcmp((const xmlChar *) "Error", cur_node->name) == 0){
                    /* It seems we have an error DBOOK_ERR_AMAZON_ERROR */
                    key = xmlNodeListGetString(doc,
                            cur_node->children->xmlChildrenNode, 1);

                    fprintf(stderr, "Amazon: %s\n",key);
                    xmlFree(key);
                    DBOOK_SET_ERROR(DBOOK_ERR_AMAZON_ERROR);
                    return DBOOK_FALSE;
                }
            }
        }


        ret = dbook_amazon_populate(cur_node->children, book);
    }

    return ret;
}

/*
 * Query amazon - get book details
 */
int dbook_amazon_get_isbn_details(DBOOK_CHAR *isbn, dbook_book *book) {
   
    DBOOK_CHAR *isbnClean = (DBOOK_CHAR *) malloc(DBOOK_ISBN_LEN);
    dbook_sanitize(isbn, isbnClean);

    /* check dbook is initialised */
    if (dbook_check_initialised() == DBOOK_FALSE) {
        return DBOOK_FALSE;
    }

    //Before we do anything we should check that the ISBN is valid
    if (dbook_check_isbn(isbnClean) != DBOOK_TRUE){
        DBOOK_SET_ERROR(DBOOK_ERR_INVALID_ISBN);
        return DBOOK_FALSE;
    }


    xmlNode *root_element = NULL;
    char *url_pre = "http://webservices.amazon.com/onca/xml?Service=AWSECommerceService&Version=2005-03-23&Operation=ItemLookup&ContentType=text%2Fxml&SubscriptionId=0DK8EWAWVKXSH8SEMVR2&ItemId=";
    char *url_post = "&ResponseGroup=Medium", *url;
    int url_len = strlen(url_pre) + 13 + strlen(url_post);
    
    // The return value
    int ret = DBOOK_TRUE;

    /* setup libxml */
    LIBXML_TEST_VERSION

    /* Build the url */
    url = (char *) malloc(url_len + 1);
    snprintf(url, url_len + 1, "%s%s%s", url_pre, isbnClean, url_post);

    /* parse the file and get the DOM */
    doc = xmlReadFile(url, NULL, 0);

    if (doc == NULL) {
        /* do not skip freeing if failing */
        ret = DBOOK_FALSE;
        DBOOK_SET_ERROR(DBOOK_ERR_AMAZON_ERROR);
        goto clean;
    }

    /* Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    memset(book, 0, sizeof(dbook_book));
    ret = dbook_amazon_populate(root_element, book);

clean:
    /* clean up */
    xmlFreeDoc(doc);
    xmlCleanupParser();
    free(url);
    free(isbnClean);
    return ret;
}
