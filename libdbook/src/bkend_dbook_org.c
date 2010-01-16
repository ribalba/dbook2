/*
 * $Id$
 * -----------------------
 * All amazon backend functions
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

xmlDoc *doc = NULL;

/*
 * Query dbook.org - get book details
 */
int dbook_org_get_isbn_details(DBOOK_CHAR *isbn, dbook_item *book) {
	return NULL; /* XXX placeholder */
}
