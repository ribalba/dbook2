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

#define DBOOK_ORG_ADDRESS "http://dbook.org/"

/* libxml stuff */
xmlDocPtr       doc = NULL;
xmlNodePtr      cur_node;
const xmlChar   *last_elem;
u_int8_t        content_assigned; /* crappy hack, better way? */

/*
 * Query dbook.org - get book details
 */
int dbook_org_get_item_details(DBOOK_CHAR *osbn, dbook_item *item) {
    char    url[DBOOK_MAX_URL] = DBOOK_ORG_ADDRESS "ditems/";
    int     ok = DBOOK_TRUE;

    /* make the url */
    strncat(url, osbn, DBOOK_MAX_URL);
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

    xmlFreeDoc(doc);

	return ok;
}

/* recursively parse the tree */
int dbook_org_traverse(xmlNodePtr node, dbook_item *item) {

    xmlNodePtr n;
    for (n = node; n; n = n->next) {
        if(n->type == XML_ELEMENT_NODE) {
            last_elem = n->name;
            content_assigned = 0;
            dbook_org_traverse(n->children, item);
        } else if ((n->type == XML_TEXT_NODE) &&
            (n->parent->name == last_elem)) { /* dont use text not ours */

            if (!content_assigned) {
                    dbook_org_assign_field(item, last_elem, n->content);
                    content_assigned = 1;
            }
        }
    }

    return DBOOK_TRUE;
}
/* write a value into the struct */
int dbook_org_assign_field(dbook_item *item, const xmlChar *last_elem,
    const xmlChar *content) {

    char **target;

    if (!xmlStrcmp(last_elem, (const xmlChar *) "title")) {
        target = &(item->title);
    } else {
        /* not a value we are interested in */
        return DBOOK_FALSE;
    }

    *target = xmalloc(strlen(content));
    strncpy(*target, (DBOOK_CHAR *) content, strlen(content));

    dbook_debug("XML parser found:");
    dbook_debug(item->title);

    return DBOOK_TRUE;
}
