/*
 * $Id$
 * -----------------------
 * All dbook.org backend functions
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

/* XXX config file for this */
#define DBOOK_ORG_ADDRESS "http://dbook.org/"

/* libxml stuff */
xmlDocPtr       doc = NULL;
xmlNodePtr      cur_node;
const xmlChar   *last_elem;
u_int8_t        content_assigned; /* crappy hack, better way? */

/*
 * Query dbook.org - get book details
 */
int dbook_org_get_isbn_details(DBOOK_CHAR *isbn, dbook_item *item) {
    char    url[DBOOK_MAX_URL] = DBOOK_ORG_ADDRESS "ditems/";
    int     ok = DBOOK_TRUE;

    /* make the url */
    strncat(url, isbn, DBOOK_MAX_URL);
    strncat(url, ".xml", DBOOK_MAX_URL);

    /* parse document */
    doc = xmlParseFile(url);
    if (doc == NULL) {
        DBOOK_SET_ERROR(DBOOK_ERR_XML_FAIL);
        return DBOOK_FALSE;
    }

    /* get root node */
    cur_node = xmlDocGetRootElement(doc);
    if (cur_node == NULL) {
        DBOOK_SET_ERROR(DBOOK_ERR_XML_FAIL);
        xmlFreeDoc(doc);
        return DBOOK_FALSE;
    }

    /* Top level node should be a <ditem> */
    if (xmlStrcmp(cur_node->name, (const xmlChar *) "ditem")) {
        DBOOK_SET_ERROR(DBOOK_ERR_XML_FAIL);
        xmlFreeDoc(doc);
        return DBOOK_FALSE;
    }

    /* traverse tree caching fields as we find 'em */
    ok = dbook_org_traverse(cur_node, item);

	return ok;
}

/* recursively parse the tree */
int dbook_org_traverse(xmlNodePtr node, dbook_item *item) {

#if 0
    /* XXX assign to structs soon
    xmlChar *val = xmlNodeListGetString(doc, cur_node, 1);

    if (!xmlStrcmp(cur_node->name, (const xmlChar *) "title")) {
        /* XXX free */
        item->title = xmalloc(sizeof(val));
        item->title = (char *) val;
    }
#endif

    xmlNodePtr n;
    for (n = node; n; n = n->next) {
        if(n->type == XML_ELEMENT_NODE) {
            last_elem = n->name;
            content_assigned = 0;
            dbook_org_traverse(n->children, item);
        } else if (n->type == XML_TEXT_NODE) {
            if (!content_assigned) {
                printf("%s = %s\n", last_elem, n->content);
                content_assigned = 1;
            }
        }
    }

    return DBOOK_TRUE;
}
