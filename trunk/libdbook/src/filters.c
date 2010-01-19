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
    sz = strlen("@ARTICLE {OSBN-") + strlen(item->osbn) + strlen(",\n") + 1;
    ret = xmalloc(sz);
    snprintf(ret, sz, "@ARTICLE {OSBN-%s,\n", item->osbn);

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

    sz = strlen(ret) + strlen("}\n") + 1;
    ret = realloc(ret, sz);
    snprintf(ret, sz, "%s}\n", ret);


    return ret;
#if 0
    char *lines[9]; /* line 10 is always just a close brace */
    char *ret = "";
    int sz, ret_sz = 0;
    int i;
    const int btex_lines = 10;

    /* key line */
    sz = 9 + strlen(bk->isbn); /* ie, 7 + \n + \0 + isbn */
    lines[0] = (char *) malloc(sz);
    snprintf(lines[0], sz, "@BOOK{%s,\n", bk->isbn);

    /* title line */
    sz = 14 + strlen(bk->title);
    lines[1] = (char *) malloc(sz);
    snprintf(lines[1], sz, "\ttitle = \"%s\",\n", bk->title);

    /* author line */
    sz = 15 + strlen(bk->author);
    lines[2] = (char *) malloc(sz);
    snprintf(lines[2], sz, "\tauthor = \"%s\",\n", bk->author);

    /* year line */
    sz = 13 + strlen(bk->date); /* XXX extract year only */
    lines[3] = (char *) malloc(sz);
    snprintf(lines[3], sz, "\tyear = \"%s\",\n", bk->date);

    /* isbn line */
    sz = 13 + strlen(bk->isbn);
    lines[4] = (char *) malloc(sz);
    snprintf(lines[4], sz, "\tisbn = \"%s\",\n", bk->isbn);

    /* publisher line */
    sz = 18 + strlen(bk->publisher);
    lines[5] = (char *) malloc(sz);
    snprintf(lines[5], sz, "\tpublisher = \"%s\",\n", bk->publisher);

    /* edition line */
    sz = 16 + sizeof(int);
    lines[6] = (char *) malloc(sz);
    snprintf(lines[6], sz, "\tedition = \"%d\",\n", bk->edition);

    /* pages line */
    sz = 14 + sizeof(int);
    lines[7] = (char *) malloc(sz);
    snprintf(lines[7], sz, "\tpages = \"%d\",\n", bk->pagecount);

    /* url line */
    sz = 12 + strlen(bk->url);
    lines[8] = (char *) malloc(sz);
    snprintf(lines[8], sz, "\turl = \"%s\"\n", bk->url);

    /* close brace  - no \n on this*/
    sz = 2;
    lines[9] = (char *) malloc(sz);
    snprintf(lines[9], sz, "}");

    for (i = 0; i < btex_lines; i ++) {
        ret_sz = ret_sz + strlen(lines[i]);
    }

    ret = (char *) malloc(ret_sz) + 1;
    for (i = 0; i < btex_lines; i ++) {
        strncat(ret, lines[i], strlen(lines[i]));
        //free(lines[i]);
    }
#endif

}
