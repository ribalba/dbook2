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
#define DBOOK_MAX_ISBN 14
#define DBOOK_CHAR char

/* Error Codes */
#define DBOOK_ERR_NONE              0
#define DBOOK_ERR_UNKNOWN           1
#define DBOOK_ERR_INVALID_ISBN      2
#define DBOOK_ERR_WRONG_ISBN_LEN    3
#define DBOOK_ERR_XML_FAIL          4
#define DBOOK_ERR_NO_BACKEND        5
#define DBOOK_ERR_TOO_MANY_BKENDS   6
#define DBOOK_ERR_UNINITIALISED     7
#define DBOOK_ERR_MALLOC            8

#define DBOOK_MAX_ERRFILE  128
#define DBOOK_SET_ERROR(e) dbook_errno = e; dbook_err_line = __LINE__; strncpy(dbook_err_file, __FILE__, DBOOK_MAX_ERRFILE);

#define DBOOK_MAX_BKEND_NAME    128
#define DBOOK_MAX_BKENDS        8

#define DBOOK_MAX_URL           256

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
extern int  dbook_bkends_in_use;

typedef DBOOK_CHAR dbook_isbn[DBOOK_MAX_ISBN];

typedef struct dbook_item_ {
    DBOOK_CHAR  *type;
    DBOOK_CHAR  *author;
    DBOOK_CHAR  *created;
    DBOOK_CHAR  *dtype;
    DBOOK_CHAR  *edition;
    DBOOK_CHAR  *editor;
    DBOOK_CHAR  *institution;
    DBOOK_CHAR  *isbn;
    DBOOK_CHAR  *journal;
    DBOOK_CHAR  *note;
    DBOOK_CHAR  *osbn;
    DBOOK_CHAR  *pages;
    DBOOK_CHAR  *pubdate;
    DBOOK_CHAR  *publisher;
    DBOOK_CHAR  *source;
    DBOOK_CHAR  *title;
    DBOOK_CHAR  *modified;
    int         *volume;
} dbook_item;

typedef struct dbook_bkend_ {
    DBOOK_CHAR name[DBOOK_MAX_BKEND_NAME];
    int (*get_item_details_func) (DBOOK_CHAR *, dbook_item *);
} dbook_bkend;

/* list of *registered* backends, like a nsswitch for dbook backends.
 * A "registered" backend is one which the user has agreed they wish to
 * use.
 */
extern dbook_bkend *dbook_bkend_list[DBOOK_MAX_BKENDS];

/* unique identifiers for each backend. indexes
 * of the dbook_avail_bkends array in dbook.c
 */
#define DBOOK_BKEND_DBOOK_ORG  0
/* #define DBOOK_BKEND_DPROTO 1 */

extern dbook_bkend *dbook_avail_bkends[DBOOK_MAX_BKENDS];

/* ISBN bits */
int dbook_check_isbn(DBOOK_CHAR *isbn);
int dbook_isbn_10_to_13(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_isbn_13_to_10(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_sanitize_isbn(DBOOK_CHAR *from, DBOOK_CHAR *to);
int dbook_is_isbn_13(DBOOK_CHAR *isbn);
int dbook_is_isbn_10(DBOOK_CHAR *isbn);
char dbook_gen_isbn_chksum_10(DBOOK_CHAR *isbn);
char dbook_gen_isbn_chksum_13(DBOOK_CHAR *isbn);

/* various functions  */
int dbook_get_item_details(DBOOK_CHAR *osbn, dbook_item *book);
int dbook_register_backend(int bkend);
int dbook_check_initialised();
int dbook_initialise();
void *xmalloc(size_t sz);
dbook_item *dbook_new_item();
void dbook_free_item (dbook_item *item);

/* output_filters (filters.c) */
char *dbook_filter_book_plain(dbook_item *book);
char *dbook_filter_book_bibtex(dbook_item *book);

/* debugging bits */
void dbook_debug(char *);
void dbook_perror();

/* dbook.org backend functions */
int dbook_org_get_item_details(DBOOK_CHAR *isbn, dbook_item *book);
int dbook_org_traverse(xmlNodePtr node, dbook_item *item);
int dbook_org_assign_field(dbook_item *item, const xmlChar *last_elem,
    const xmlChar *content);

#endif
