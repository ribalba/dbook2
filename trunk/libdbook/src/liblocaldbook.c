/*
 * $Id$
 * -----------------------
 * Does everything locally
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
#include "libdbook.h"

#define MAPLEN 3

xmlDoc *doc = NULL;

/* For now only amazon is supported */
char *amazonMap[MAPLEN] = {"Author", "Title", "Publisher"};

void dbook_populate(xmlNode * a_node, dbook_book *book) {
    xmlNode *cur_node = NULL;
	xmlChar *key;
    int i;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            for (i =0; i < MAPLEN; i++){

                if (xmlStrcmp((const xmlChar *) amazonMap[i],
                    cur_node->name) == 0){

                    /*
                     * We have found something in the map.
                     * Check if the child is of type 
                     */

                    if (cur_node->children->type == XML_TEXT_NODE){
                        key = xmlNodeListGetString(doc,
                                cur_node->xmlChildrenNode, 1);

                        /* Match the fields we are interested in */
                        if(strncasecmp(cur_node->name, "Author",
                            sizeof(cur_node->name))){
                            strncpy(book->author, key,
                                sizeof(book->author));

                        } else if (strcmp(cur_node->name, "Title"),
                            sizeof(cur_node->name)) {
                            strncpy(book->title,key,sizeof(book->title));
                        }

                        xmlFree(key);

                    } else {
                        //return error;
                    }
                }
            }
        }

        dbook_populate(cur_node->children, book);
    }
}

/** 
  * Returns the checksum for a ISBN 10 passed in as paramter
  */
char dbook_gen_chksum_10_loc(DBOOK_ISBN *isbnToTest) {

    /*The multiplier */
    int multy = 10;
    int sum = 0;
    int checkSum = 0;
    int i = 0, atoi_res;

    for (i = 0; i < 9; i++) {
        /* Because atio thinks it is a pointer to a array it will 
         * shoot off into memory. So if you want to convert a single char 
         * into a int don't use atoi.
         */
        atoi_res = isbnToTest[i] - '0';
        sum = sum + (atoi_res * multy);
        multy --;
    }

    checkSum = (11 - (sum % 11));

    if (checkSum == 10)
        return 'X';

    if (checkSum == 11)
        return 0;

    return checkSum;
}


/** 
  Returns the checksum for a ISBN 13 passed in as paramter
  */
char dbook_gen_chksum_13_loc(DBOOK_ISBN *isbnToTest) {

    /* The multiplyer */
    int multy = 10;
    int sumodd = 0;
    int sumeve = 0;
    int checkSum = 0;
    int i = 0;
    int atoi1, atoi2;

    for (i = 0; i <= 11; i = i + 2) {
        /* Same as above */
        atoi1 = isbnToTest[i] - '0';
        atoi2 = isbnToTest[i + 1] - '0';

        sumodd = sumodd + atoi1;
        sumeve = sumeve + atoi2;
    }

    checkSum = (sumodd + (sumeve * 3)) % multy;

    if (checkSum != 0)
        checkSum = multy - checkSum;

    return checkSum;

}


/*
 * check an ISBN is valid
 */
int dbook_check_isbn_loc(DBOOK_ISBN *isbnToCheck){

    dbook_isbn isbnToTest = "";
    dbook_sanitize(isbnToCheck, isbnToTest);

    /* If the size is equal to 10 do it */
    if (dbook_is_isbn_10(isbnToTest) == DBOOK_TRUE) {
        int checkSum = dbook_gen_chksum_10(isbnToTest);

        if (checkSum == 'X' && isbnToTest[9] == 'X')
            return DBOOK_TRUE;

        if (checkSum == (isbnToTest[9] - '0'))
            return DBOOK_TRUE;

    /* If the size is equal to 13 do it */
    } else if (dbook_is_isbn_13(isbnToTest) == DBOOK_TRUE) {

        int checkSum = dbook_gen_chksum_13(isbnToTest);

        if (checkSum == (isbnToTest[12] - '0'))
            return DBOOK_TRUE;
    }

    /* If everything fails => fail */
    return DBOOK_FALSE;
}

int dbook_isbn_10_to_13_loc(DBOOK_ISBN *from, DBOOK_ISBN *to){
    char chkSum;

    memset(to, 0, strlen(to));

    if(dbook_is_isbn_10(from) != DBOOK_TRUE) {
        fprintf(stderr, "When calling dbook_isbn_10_to_13 please pass in a 10 based isbn");
        return DBOOK_FALSE;
    }

    if (dbook_check_isbn(from) != DBOOK_TRUE){
        fprintf(stderr, "Please pass in a valid isbn to dbook_isbn_10_to_13");
        return DBOOK_FALSE;
    }

    dbook_isbn fromClean = "";

    dbook_sanitize(from, fromClean);

    strncpy(to, "978",3);
    strncat(to,fromClean,9);
    chkSum = dbook_gen_chksum_13(to) + '0';

    strncat(to, &chkSum,1);
    return DBOOK_TRUE;
}

int dbook_isbn_13_to_10_loc(DBOOK_ISBN *from, DBOOK_ISBN *to){
    memset(to, 0, strlen(to));

    if (dbook_is_isbn_13(from) != DBOOK_TRUE) {
        fprintf(stderr, "When calling dbook_isbn_13_to_10 please pass in a 10 based isbn");
        return DBOOK_FALSE;
    }

    if (dbook_check_isbn(from) != DBOOK_TRUE){
        fprintf(stderr, "Please pass in a valid isbn to dbook_isbn_13_to_10");
        return DBOOK_FALSE;
    }

    if (strncmp(from,"978",3) !=0) {
        fprintf(stderr, "Only ISBN-13 numbers beginning with 978 can be converted to ISBN-10.");
        return DBOOK_FALSE;
    }
   
    dbook_isbn fromClean = "";

    dbook_sanitize(from, fromClean);


    strncpy(to,fromClean+3,9);
    
    char chkSum = dbook_gen_chksum_10(to);
    
    if (chkSum == 'X') {
       strncat(to,"X",1);
    } else {
        char chkSumDeci = chkSum + '0' ;
        strncat(to, &chkSumDeci,1);
    }

    return DBOOK_TRUE;
}

/**
 * Removes all the rubbish that is normally in an isbn like - and spaces
 * first value is a char * to be cleaned
 * second is a dbook_isbn for the clean isbn to be put in
 */ 
int dbook_sanitize_loc(char *from, DBOOK_ISBN *to){
    //Null everything before we do anything
    memset(to, 0, strlen(to));
    
    int i;
    for (i = 0; i< strlen(from); i++){
        if ( isdigit(from[i])  || from[i] == 'X' || from[i] == 'x'){
            strncat(to, &from[i], 1);
        }
    }
    return DBOOK_TRUE;
}

/*
 * Query amazon - get book details
 */
int dbook_get_isbn_details_loc(DBOOK_ISBN *isbn, dbook_book *book){

    xmlNode *root_element = NULL;
    char *url_pre = "http://webservices.amazon.com/onca/xml?Service=AWSECommerceService&Version=2005-03-23&Operation=ItemLookup&ContentType=text%2Fxml&SubscriptionId=0DK8EWAWVKXSH8SEMVR2&ItemId=";
    char *url_post = "&ResponseGroup=Medium", *url;
    int url_len = strlen(url_pre) + 13 + strlen(url_post);
    int ret = DBOOK_TRUE;

    /* setup libxml */
    LIBXML_TEST_VERSION

    /* Build the url */
    url = (char *) malloc(url_len + 1);
    snprintf(url, url_len + 1, "%s%s%s", url_pre, isbn, url_post);
    dbook_debug("Amazon URL:");
    dbook_debug(url);

    /* parse the file and get the DOM */
    doc = xmlReadFile(url, NULL, 0);

    if (doc == NULL) {
        /* do not skip freeing if failing */
        ret = DBOOK_FALSE;
        goto clean;
    }

    /* Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    memset(book, 0, sizeof(dbook_book));
    dbook_populate(root_element, book);

clean:
    /* clean up */
    xmlFreeDoc(doc);
    xmlCleanupParser();
    free(url);
    return ret;
}


/**
 * Checks if the isbn is a isbn 13. Does not validate only takes the length
 */
int dbook_is_isbn_13_loc(DBOOK_ISBN *isbnToCheck){
    dbook_isbn retVal = "";
    dbook_sanitize(isbnToCheck, retVal);
    return ((strlen(retVal) == 13) ? DBOOK_TRUE : DBOOK_FALSE) ;
}

/**
 * Checks if the isbn is a isbn 10. Does not validate only takes the length
 */
int dbook_is_isbn_10_loc(DBOOK_ISBN *isbnToCheck){
    dbook_isbn retVal = "";
    dbook_sanitize(isbnToCheck, retVal);
    return ((strlen(retVal) == 10) ? DBOOK_TRUE : DBOOK_FALSE) ;
}


