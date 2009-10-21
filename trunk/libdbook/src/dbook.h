/*
 * DBOOK2
 * $Id$
 * -----------------------
 * Type definitions, preprocessor macros and function prototypes.
 */

#ifndef DBOOK_H_
#define DBOOK_H_

#define DBOOK_TRUE	0
#define DBOOK_FALSE	1

/* 10 or 13 long plus \0 */
#define DBOOK_ISBN_LEN 14
#define DBOOK_CHAR char

/* Error Codes */
#define DBOOK_ERR_NONE              0
#define DBOOK_ERR_UNKNOWN           1
#define DBOOK_ERR_INVALID_ISBN      2
#define DBOOK_ERR_WRONG_ISBN_LEN    3
#define DBOOK_ERR_AMAZON_ERROR      4
#define DBOOK_ERR_NO_BACKEND        5
#define DBOOK_ERR_TOO_MANY_BKENDS   6
#define DBOOK_ERR_UNINITIALISED     7

#define DBOOK_MAX_ERRFILE  128
#define DBOOK_SET_ERROR(e) dbook_errno = e; dbook_err_line = __LINE__; strncpy(dbook_err_file, __FILE__, DBOOK_MAX_ERRFILE);

#define DBOOK_MAX_BKEND_NAME    128
#define DBOOK_MAX_BKENDS        8

/* For the XML stuff */
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <strings.h>

extern int  dbook_debug_flag;
extern int  dbook_errno;
extern char dbook_err_file[];
extern int  dbook_err_line;
extern char *dbook_err_descrs[];
extern int             dbook_bkends_in_use;

typedef DBOOK_CHAR dbook_isbn[];

typedef struct dbook_book_ {
    DBOOK_CHAR isbn[DBOOK_ISBN_LEN];
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

typedef struct dbook_bkend_ {
    DBOOK_CHAR name[DBOOK_MAX_BKEND_NAME];
    int (*get_isbn_details_func) (DBOOK_CHAR *, dbook_book *);
} dbook_bkend;

/* list of *registered* backends, like a nsswitch for dbook backends.
 * A "registered" backend is one which the user has agreed they wish to
 * use.
 */
extern dbook_bkend *dbook_bkend_list[DBOOK_MAX_BKENDS];

/* unique identifiers for each backend. indexes
 * of the dbook_avail_bkends array in dbook.c
 */
#define DBOOK_BKEND_AMAZON  0
/* #define DBOOK_BKEND_DPROTO 1 */

extern dbook_bkend *dbook_avail_bkends[DBOOK_MAX_BKENDS];

/* various functions  */
int dbook_check_isbn(DBOOK_CHAR *isbnToCheck);
int dbook_isbn_10_to_13(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_isbn_13_to_10(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_sanitize(char *from, DBOOK_CHAR *to);
int dbook_get_isbn_details(DBOOK_CHAR *whichBook, dbook_book *book);
int dbook_is_isbn_13(DBOOK_CHAR *isbnToCheck);
int dbook_is_isbn_10(DBOOK_CHAR *isbnToCheck);
char dbook_gen_chksum_10(DBOOK_CHAR *isbnToTest);
char dbook_gen_chksum_13(DBOOK_CHAR *isbnToTest);
int dbook_register_backend(int bkend);
int dbook_check_initialised();
int dbook_initialise();

/* output_filters (filters.c) */
char *dbook_filter_book_plain(dbook_book *book);
char *dbook_filter_book_bibtex(dbook_book *book);

/* debugging bits */
void dbook_debug(char *);
void dbook_perror();

/* backend */
int dbook_amazon_get_isbn_details(DBOOK_CHAR *isbn, dbook_book *book);

#endif
