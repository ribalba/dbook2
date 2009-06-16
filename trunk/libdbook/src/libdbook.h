/*
 * DBOOK2
 * $Id$
 * -----------------------
 * The header file for the lib 
 */

#ifndef LIBDBOOK_H_
#define LIBDBOOK_H_

#define DBOOK_TRUE	0
#define DBOOK_FALSE	1

/* 10 or 13 long plus \0 */
#define DBOOK_ISBN_LEN 14
#define DBOOK_ISBN char

typedef DBOOK_ISBN dbook_isbn[DBOOK_ISBN_LEN];

typedef struct dbook_config_ {
    char server[50];
    int serverMode;   
    int debug;
} dbook_config;


typedef struct dbook_book_ {
    DBOOK_ISBN isbn[DBOOK_ISBN_LEN];
    char title[250];
    char author[250];
    char date[50];
    char publisher[250];
    int  edition;
    int  pagecount;
    char image_path[250];
    char category[250];
    char url[250];
    char booktype[50];
} dbook_book;

int dbook_check_isbn(DBOOK_ISBN *isbnToCheck);
int dbook_isbn_10_to_13(DBOOK_ISBN *from, DBOOK_ISBN *to);
int dbook_isbn_13_to_10(DBOOK_ISBN *from, DBOOK_ISBN *to);
int dbook_sanitize(char *from, DBOOK_ISBN *to);
int dbook_get_isbn_details(DBOOK_ISBN *whichBook, dbook_book *book);
int dbook_configure(dbook_config *config);
int dbook_get_config(dbook_config *config);
int dbook_is_isbn_13(DBOOK_ISBN *isbnToCheck);
int dbook_is_isbn_10(DBOOK_ISBN *isbnToCheck);
char dbook_gen_chksum_10(DBOOK_ISBN *isbnToTest);
char dbook_gen_chksum_13(DBOOK_ISBN *isbnToTest);
char *dbook_filter_book_plain(dbook_book *book);
char *dbook_filter_book_bibtex(dbook_book *book);

#endif
