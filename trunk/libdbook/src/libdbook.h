/*
 * DBOOK2
 * $Id$
 * -----------------------
 * Type definitions, preprocessor macros and function prototypes.
 */

#ifndef LIBDBOOK_H_
#define LIBDBOOK_H_

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

#define DBOOK_MAX_ERRFILE  128
#define DBOOK_SET_ERROR(e) dbook_errno = e; dbook_err_line = __LINE__; strncpy(dbook_err_file, __FILE__, DBOOK_MAX_ERRFILE);



/* For the XML stuff */
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <strings.h>

extern char dbook_server[50];
extern int  dbook_debug_flag;
extern int  dbook_errno;
extern char dbook_err_file[];
extern int  dbook_err_line;
extern char *dbook_err_descrs[];

typedef DBOOK_CHAR dbook_isbn[];

typedef struct dbook_config_ {
    char server[50];
    int serverMode;   
    int debug;
} dbook_config;


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

int dbook_check_isbn(DBOOK_CHAR *isbnToCheck);
int dbook_isbn_10_to_13(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_isbn_13_to_10(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_sanitize(char *from, DBOOK_CHAR *to);
int dbook_get_isbn_details(DBOOK_CHAR *whichBook, dbook_book *book);
int dbook_configure(dbook_config *config);
int dbook_get_config(dbook_config *config);
int dbook_is_isbn_13(DBOOK_CHAR *isbnToCheck);
int dbook_is_isbn_10(DBOOK_CHAR *isbnToCheck);
char dbook_gen_chksum_10(DBOOK_CHAR *isbnToTest);
char dbook_gen_chksum_13(DBOOK_CHAR *isbnToTest);
char *dbook_filter_book_plain(dbook_book *book);
char *dbook_filter_book_bibtex(dbook_book *book);
void dbook_debug(char *);
void dbook_perror();



//Some local stuff for liblocaldbook
//Should somehow represent the above only that there is a local at the end of 
//every function

int dbook_populate(xmlNode * a_node, dbook_book *book);
char dbook_gen_chksum_10_loc(DBOOK_CHAR *isbnToTest);
char dbook_gen_chksum_13_loc(DBOOK_CHAR *isbnToTest);
int dbook_check_isbn_loc(DBOOK_CHAR *isbnToCheck);
int dbook_isbn_10_to_13_loc(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_isbn_13_to_10_loc(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_sanitize_loc(char *from, DBOOK_CHAR *to);
int dbook_get_isbn_details_loc(DBOOK_CHAR *isbn, dbook_book *book);
int dbook_is_isbn_13_loc(DBOOK_CHAR *isbnToCheck);
int dbook_is_isbn_10_loc(DBOOK_CHAR *isbnToCheck);


#endif
