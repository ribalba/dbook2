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

/* externed in libdbook.h */
char    dbook_server[50];
int     dbook_debug_flag = 0;
int     dbook_errno = DBOOK_ERR_NONE;
char    dbook_err_file[DBOOK_MAX_ERRFILE] = "";
int     dbook_err_line = 0;

char *dbook_err_descrs[] = {
    "Not set",
    "Unknown error",
    "Invalid ISBN",
    "Wrong ISBN len",
    "Amazon error",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set",
    "Not set"
};

/* TODO Shall we scrap the online mode ??? || PROBABLY (edd) */
int onlineMode = DBOOK_FALSE; /* XXX is this still needed? */

int dbook_check_isbn(DBOOK_CHAR *isbnToCheck) {
    if (onlineMode == DBOOK_FALSE){
        return dbook_check_isbn_loc(isbnToCheck);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }

    return DBOOK_FALSE;
}

int dbook_isbn_10_to_13(DBOOK_CHAR *from, DBOOK_CHAR *to) {
    if (onlineMode == DBOOK_FALSE) {
        return dbook_isbn_10_to_13_loc(from, to);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }

    return DBOOK_FALSE;

}

int dbook_isbn_13_to_10(DBOOK_CHAR *from, DBOOK_CHAR *to) {
    if (onlineMode == DBOOK_FALSE) {
        return dbook_isbn_13_to_10_loc(from, to);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }

    return DBOOK_FALSE;
}

int dbook_sanitize(char *from, DBOOK_CHAR *to){
    if (onlineMode == DBOOK_FALSE){
        return dbook_sanitize_loc(from, to);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }

    return DBOOK_TRUE;
}

int dbook_get_isbn_details(DBOOK_CHAR *whichBook, dbook_book *book) {
    if (onlineMode == DBOOK_FALSE){
        return dbook_get_isbn_details_loc(whichBook, book);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }
    
    
    return DBOOK_TRUE;
}

int dbook_configure(dbook_config *config){
    strcpy(dbook_server, config->server);
    return DBOOK_TRUE;
}

int dbook_get_config(dbook_config *config){
    strcpy(config->server, dbook_server);
    return DBOOK_TRUE;
}


int dbook_is_isbn_13(DBOOK_CHAR *isbnToCheck){
    if (onlineMode == DBOOK_FALSE){
        return dbook_is_isbn_13_loc(isbnToCheck);
    }else{
        /* dbook_sanitize_dis(from, to); */
    }
    return DBOOK_FALSE;
}

int dbook_is_isbn_10(DBOOK_CHAR *isbnToCheck) {
    if (onlineMode == DBOOK_FALSE) {
        return dbook_is_isbn_10_loc(isbnToCheck);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }
    return DBOOK_FALSE;
}

char dbook_gen_chksum_10(DBOOK_CHAR *isbnToTest) {

    if (onlineMode == DBOOK_FALSE) {
        return dbook_gen_chksum_10_loc(isbnToTest);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }
    return 'E';
}

char dbook_gen_chksum_13(DBOOK_CHAR *isbnToTest) {
    if (onlineMode == DBOOK_FALSE) {
        return dbook_gen_chksum_13_loc(isbnToTest);
    } else {
        /* dbook_sanitize_dis(from, to); */
    }
    return 'E';
}

/* print debug messages to stderror *if* dbook_debug_flag is set */
void dbook_debug(char *msg) {
    if (dbook_debug_flag != DBOOK_TRUE)
        return;

    fprintf(stderr, "DBOOK_DEBUG: %s\n", msg);
}

/* print an error message - only the library implementor uses this.
 * ie. Dont print from within library functions. The return vals of 
 * functions will inform the implementor that an error occured, not
 * the library making noise on the console!
 */
void dbook_perror() {
    fprintf(stderr, "DBOOK_ERROR %d\t(%s:%d):\n\t\t%s\n", dbook_errno,
            dbook_err_file, dbook_err_line,
            dbook_err_descrs[dbook_errno]);
}
