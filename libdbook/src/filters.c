/*
 * DBOOK2
 * output filers
 * $Id$
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dbook.h"

DBOOK_CHAR *dbook_filter_book_plain(dbook_item *item) {
    /* XXX */

    return NULL;
}

/* remember to free the result */
DBOOK_CHAR *dbook_filter_book_bibtex(dbook_item *item) {

    DBOOK_CHAR *ret;
    size_t sz;
    int i;

    DBOOK_CHAR *mapping[] = {
        item->author, "author",
        item->edition, "edition",
        item->editor, "editor",
        item->institution, "institution",
        item->isbn, "isbn",
        item->journal, "journal",
        item->note, "note",
        item->pages, "pages", 
        item->pubdate, "year", /* XXX only year */
        item->publisher, "publisher",
        item->title, "title",
        item->volume, "volume",
        (DBOOK_CHAR *) -1, (DBOOK_CHAR *) -1 
    };

    /* allocate the bibtex db entry heder and copy in */
    sz = strlen("-- Fetched from dbook.org\n@ARTICLE {") +
        strlen(item->osbn) + strlen(",\n") + 1;

    ret = xmalloc(sz);
    snprintf(ret, sz, "-- Fetched from dbook.org\n@ARTICLE {%s,\n",
        item->osbn);

    for (i = 0; mapping[i] != (DBOOK_CHAR *) -1; i += 2) {
        /* if used, reallocate more space and copy in */
        if (mapping[i] != NULL) {
            sz = strlen(ret) + strlen("\t") + strlen(mapping[i + 1]) +
                strlen(" = \"") + strlen(mapping[i]) + strlen("\",\n") + 1;
            ret = realloc(ret, sz);
            
            /* XXX if realloc fails, clean up and exit */
            snprintf(ret, sz, "%s\t%s = \"%s\",\n",
                ret, mapping[i + 1], mapping[i]);
        }
    }

    /* kill final , */
    ret[sz - 3] = '\n';
    ret[sz - 2] = '\0';

    /* close off record */
    sz = strlen(ret) + strlen("}\n") + 1;
    ret = realloc(ret, sz);
    snprintf(ret, sz, "%s}\n", ret);

    return ret;
}
