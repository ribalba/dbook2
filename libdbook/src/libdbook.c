/*
 * DBOOK2
 * $Id$
 * -----------------------
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libdbook.h"

char serverToTalkTo[50];
int onlineMode = DBOOK_FALSE; /* XXX is this still needed? */

int dbook_check_isbn(DBOOK_ISBN *isbnToCheck) {
    if (onlineMode == DBOOK_FALSE){
        return dbook_check_isbn_loc(isbnToCheck);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }

    return DBOOK_FALSE;
}

int dbook_isbn_10_to_13(DBOOK_ISBN *from, DBOOK_ISBN *to) {
    if (onlineMode == DBOOK_FALSE) {
        return dbook_isbn_10_to_13_loc(from, to);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }

    return DBOOK_FALSE;

}

int dbook_isbn_13_to_10(DBOOK_ISBN *from, DBOOK_ISBN *to){
    if (onlineMode == DBOOK_FALSE) {
        return dbook_isbn_13_to_10_loc(from, to);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }

    return DBOOK_FALSE;
}

int dbook_sanitize(char *from, DBOOK_ISBN *to){
    if (onlineMode == DBOOK_FALSE){
        dbook_sanitize_loc(from, to);
    }else{
        /* dbook_sanitize_dis(from, to); */
    }

    return DBOOK_TRUE;
}

int dbook_get_isbn_details(DBOOK_ISBN *whichBook, dbook_book *book){
    memset(book, 0, sizeof(dbook_book));
    strcpy(book->isbn, "9780091906122");
    strcpy(book->title, "Are You a Geek?");
    strcpy(book->author, "Tim Collins");
    strcpy(book->date, "6-09-2005");
    strcpy(book->publisher, "Ebury Press");
    return DBOOK_TRUE;
}

int dbook_configure(dbook_config *config){
    strcpy(serverToTalkTo, config->server);
    return DBOOK_TRUE;
}

int dbook_get_config(dbook_config *config){
    strcpy(config->server, serverToTalkTo);
    return DBOOK_TRUE;
}


int dbook_is_isbn_13(DBOOK_ISBN *isbnToCheck){
    if (onlineMode == DBOOK_FALSE){
        return dbook_is_isbn_13_loc(isbnToCheck);
    }else{
        /* dbook_sanitize_dis(from, to); */
    }
    return DBOOK_FALSE;
}

int dbook_is_isbn_10(DBOOK_ISBN *isbnToCheck) {
    if (onlineMode == DBOOK_FALSE) {
        return dbook_is_isbn_10_loc(isbnToCheck);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }
    return DBOOK_FALSE;
}

char dbook_gen_chksum_10(DBOOK_ISBN *isbnToTest) {

    if (onlineMode == DBOOK_FALSE) {
        return dbook_gen_chksum_10_loc(isbnToTest);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }
    return DBOOK_FALSE;
}

char dbook_gen_chksum_13(DBOOK_ISBN *isbnToTest) {
    if (onlineMode == DBOOK_FALSE) {
        return dbook_gen_chksum_13_loc(isbnToTest);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }
    return DBOOK_FALSE;
}

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
    const int btex_lines = 2;

    /* key line */
    sz = 9 + strlen(bk->isbn); /* ie, 7 + \n + \0 + isbn */
    lines[0] = (char *) malloc(sz);
    snprintf(lines[0], sz, "@BOOK{%s,\n", bk->isbn);

    /* author line */
    sz = 15 + strlen(bk->author);
    lines[1] = (char *) malloc(sz);
    snprintf(lines[1], sz, "\tauthor = \"%s\",\n", bk->author);

    /* XXX and the rest */

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
