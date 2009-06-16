/*
 * DBOOK2
 * $Id: libdbook.c 60 2009-06-16 02:32:39Z vext01 $
 * -----------------------
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libdbook.h"

char *dbook_filter_book_plain(dbook_book *bk) {
    /*
       printf("ISBN:		%s\n", bk.isbn);
       printf("Title:		%s\n", bk.title);
       printf("Author:		%s\n", bk.author);
       printf("Date:		%s\n", bk.date);
       printf("Publisher:	%s\n", bk.publisher);
       printf("Edition:	%d\n", bk.edition);
       printf("Pages:		%d\n", bk.pagecount);
       printf("Image Path:	%s\n", bk.image_path);
       printf("Category:	%s\n", bk.category);
       printf("URL:		%s\n", bk.url);
       printf("Type:		%s\n", bk.booktype);
       */
    return 0; /* XXX fixme */
}

char *dbook_filter_book_bibtex(dbook_book *bk) {
    char *lines[9]; /* line 10 is always just a close brace */
    char *ret = "";
    int sz, ret_sz = 0;
    int i;
    const int btex_lines = 9;

    /* key line */
    sz = 9 + strlen(bk->isbn); /* ie, 7 + \n + \0 + isbn */
    lines[0] = (char *) malloc(sz);
    snprintf(lines[0], sz, "@BOOK{%s,\n", bk->isbn);

    /* author line */
    sz = 15 + strlen(bk->author);
    lines[1] = (char *) malloc(sz);
    snprintf(lines[1], sz, "\tauthor = \"%s\",\n", bk->author);

    /* year line */
    sz = 13 + strlen(bk->date); /* XXX extract year only */
    lines[2] = (char *) malloc(sz);
    snprintf(lines[2], sz, "\tyear = \"%s\",\n", bk->date);

    /* isbn line */
    sz = 13 + strlen(bk->isbn);
    lines[3] = (char *) malloc(sz);
    snprintf(lines[3], sz, "\tisbn = \"%s\",\n", bk->author);

    /* publisher line */
    sz = 18 + strlen(bk->publisher);
    lines[4] = (char *) malloc(sz);
    snprintf(lines[4], sz, "\tpublisher = \"%s\",\n", bk->publisher);

    /* edition line */
    sz = 24; /* allow 8 digits for edition */
    lines[5] = (char *) malloc(sz);
    snprintf(lines[5], sz, "\tedition = \"%8d\",\n", bk->edition);

    /* pages line */
    sz = 22; /* allow 8 digits for pages */
    lines[6] = (char *) malloc(sz);
    snprintf(lines[6], sz, "\tpages = \"%8d\",\n", bk->pagecount);

    /* url line */
    sz = 12 + strlen(bk->url);
    lines[7] = (char *) malloc(sz);
    snprintf(lines[7], sz, "\turl = \"%s\"\n", bk->url);

    /* close brace  - no \n on this*/
    sz = 2;
    lines[8] = (char *) malloc(sz);
    snprintf(lines[8], sz, "}");

    for (i = 0; i < btex_lines; i ++) {
        ret_sz = ret_sz + strlen(lines[i]);
    }

    ret = (char *) malloc(sz) + 1;
    for (i = 0; i < btex_lines; i ++) {
        strncat(ret, lines[i], strlen(lines[i]));
        free(lines[i]);
    }

    return ret;
}
