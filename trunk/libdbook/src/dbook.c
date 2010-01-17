/*;
 * DBOOK2
 * $Id$
 * -----------------------
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbook.h"

/* externed in libdbook.h */
int             dbook_debug_flag = 0;
int             dbook_errno = DBOOK_ERR_NONE;
char            dbook_err_file[DBOOK_MAX_ERRFILE] = "";
int             dbook_err_line = 0;
dbook_bkend     *dbook_bkend_list[DBOOK_MAX_BKENDS];
int             dbook_bkends_in_use = 0;

#define DBOOK_ERR_NOT_IMPL "Error code not implemented"
char *dbook_err_descrs[] = {
    "No error",
    "Unknown error",
    "Invalid ISBN",
    "Wrong ISBN len",
    "XML parsing failure",
    "Backend not set",
    "Too many backends in use",
    "libdbook not initialised, use dbook_initialise()",
    "Malloc failure",
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL
};

/**
 * Backend definitions
 * Only one for now, but we hope to allow for future plugins.
 */
dbook_bkend dbook_bkend_dbook_org = {
    "Dbook.org Lookup Service",
    &dbook_org_get_item_details
};

/* A lookup table of available backends, indexes should match 
 * DBOOK_BKEND_* definitions in dbook.h
 * These are loaded in dbook_init();
 * Can't be initialised here unfortunately.
 */
dbook_bkend *dbook_avail_bkends[DBOOK_MAX_BKENDS];

int dbook_initialised = 0;

/* set up the available backends and other initialisation */
int dbook_initialise() {
    int i;

    /* for now, we only support our backend */
    dbook_avail_bkends[0] = &dbook_bkend_dbook_org;

    /* fill unimplemented backends */
    for (i = 1; i < DBOOK_MAX_BKENDS; i ++) {
        dbook_avail_bkends[i] = NULL;
    }

    dbook_initialised = 1;

    return DBOOK_TRUE;
}

/* call this at the start of all outward facing functions that need
 * to use backends.
 */
int dbook_check_initialised() {
    if (dbook_initialised) {
        return DBOOK_TRUE;
    }

    DBOOK_SET_ERROR(DBOOK_ERR_UNINITIALISED);
    return DBOOK_FALSE;
}

int dbook_get_item_details(DBOOK_CHAR *osbn, dbook_item *item) {

    /* check dbook is initialised */
    if (dbook_check_initialised() == DBOOK_FALSE)
        return DBOOK_FALSE;

    /* check atleast one backend was sleected */
    if (dbook_bkends_in_use == 0) {
        DBOOK_SET_ERROR(DBOOK_ERR_NO_BACKEND);
        return DBOOK_FALSE;
    }

    /* for now we always use the first registered backend.
     * This will change when/if we have further backends.
     */
    return dbook_bkend_list[0]->get_item_details_func(osbn, item);
}

/*
 * XXX this probably needs revision
 */
int dbook_register_backend(int bk) {

    /* check dbook is initialised */
    if (dbook_check_initialised() == DBOOK_FALSE) {
        return DBOOK_FALSE;
    }

    /* do we have space for another backend */
    if (dbook_bkends_in_use == DBOOK_MAX_BKENDS) {
        DBOOK_SET_ERROR(DBOOK_ERR_TOO_MANY_BKENDS);
        return DBOOK_FALSE;
    }

    dbook_bkend_list[dbook_bkends_in_use] = dbook_avail_bkends[bk];
    dbook_bkends_in_use ++;

    return DBOOK_TRUE;
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

/** 
  * Returns the checksum for a ISBN 10 passed in as paramter
  */
char dbook_gen_isbn_chksum_10(DBOOK_CHAR *isbn) {

    /* The multiplier */
    int multy = 10;
    int sum = 0;
    int cksum = 0;
    int i = 0, atoi_res;

    for (i = 0; i < 9; i++) {
        /* Because atio thinks it is a pointer to a array it will 
         * shoot off into memory. So if you want to convert a single char 
         * into a int don't use atoi.
         */
        atoi_res = isbn[i] - '0';
        sum = sum + (atoi_res * multy);
        multy --;
    }

    cksum = (11 - (sum % 11));

    if (cksum == 10)
        return 'X';

    if (cksum == 11)
        return 0;

    return cksum;
}


/** 
  Returns the checksum for a ISBN 13 passed in as paramter
  */
char dbook_gen_isbn_chksum_13(DBOOK_CHAR *isbn) {

    /* The multiplyer */
    int multy = 10;
    int sumodd = 0;
    int sumeve = 0;
    int cksum = 0;
    int i = 0;
    int atoi1, atoi2;

    for (i = 0; i <= 11; i = i + 2) {
        /* Same as above */
        atoi1 = isbn[i] - '0';
        atoi2 = isbn[i + 1] - '0';

        sumodd = sumodd + atoi1;
        sumeve = sumeve + atoi2;
    }

    cksum = (sumodd + (sumeve * 3)) % multy;

    if (cksum != 0)
        cksum = multy - cksum;

    return cksum;

}

/*
 * check an ISBN is valid
 */
int dbook_check_isbn(DBOOK_CHAR *isbn){
    int cksum;
    DBOOK_CHAR new_isbn[DBOOK_MAX_ISBN];

    dbook_sanitize_isbn(isbn, new_isbn);
    
    /* If the size is equal to 10 do it */
    if (dbook_is_isbn_10(new_isbn) == DBOOK_TRUE) {
        cksum = dbook_gen_isbn_chksum_10(isbn);

        if ((cksum == 'X') && (new_isbn[9] == 'X')) {
            return DBOOK_TRUE;
        }

        if (cksum == (new_isbn[9] - '0')) {
            return DBOOK_TRUE;
        }

    /* If the size is equal to 13 do it */
    } else if (dbook_is_isbn_13(new_isbn) == DBOOK_TRUE) {

        cksum = dbook_gen_isbn_chksum_13(new_isbn);

        if (cksum == (new_isbn[12] - '0')) {
            return DBOOK_TRUE;
        }
    }

    return DBOOK_FALSE;
}

int dbook_isbn_10_to_13(DBOOK_CHAR *from, DBOOK_CHAR *to){
    char cksum;
    dbook_isbn from_clean = "";

    memset(to, NULL, strlen(to));

    if(dbook_is_isbn_10(from) != DBOOK_TRUE) {
        DBOOK_SET_ERROR(DBOOK_ERR_WRONG_ISBN_LEN);
        return DBOOK_FALSE;
    }

    if (dbook_check_isbn(from) != DBOOK_TRUE){
        DBOOK_SET_ERROR(DBOOK_ERR_INVALID_ISBN);
        return DBOOK_FALSE;
    }

    dbook_sanitize_isbn(from, from_clean);

    strncpy(to, "978", 3);
    strncat(to,from_clean, 9);
    cksum = dbook_gen_isbn_chksum_13(to) + '0';

    strncat(to, &cksum,1);
    return DBOOK_TRUE;
}

int dbook_isbn_13_to_10(DBOOK_CHAR *from, DBOOK_CHAR *to){
    dbook_isbn from_clean = "";
    char cksum, cksum_deci;

    memset(to, 0, strlen(to));

    if (dbook_is_isbn_13(from) != DBOOK_TRUE) {
        DBOOK_SET_ERROR(DBOOK_ERR_WRONG_ISBN_LEN);
        return DBOOK_FALSE;
    }

    if (dbook_check_isbn(from) != DBOOK_TRUE){
        DBOOK_SET_ERROR(DBOOK_ERR_INVALID_ISBN);
        return DBOOK_FALSE;
    }

    /* only ISBN13s beginning "978" can be converted */
    if (strncmp(from,"978",3) !=0) {
        DBOOK_SET_ERROR(DBOOK_ERR_INVALID_ISBN);
        return DBOOK_FALSE;
    }

    dbook_sanitize_isbn(from, from_clean);
    strncpy(to,from_clean + 3, 9);
    cksum = dbook_gen_isbn_chksum_10(to);
    
    if (cksum == 'X') {
       strncat(to, "X", 1);
    } else {
        cksum_deci = cksum + '0';
        strncat(to, &cksum_deci, 1);
    }

    return DBOOK_TRUE;
}

/**
 * Removes all the rubbish that is normally in an isbn like - and spaces
 * first value is a DBOOK_CHAR * to be cleaned *,  second is a dbook_isbn
 * for the clean isbn to be put in.
 */ 
int dbook_sanitize_isbn(DBOOK_CHAR *from, DBOOK_CHAR *to){
    int i,j = 0;

    /* Null everything before we do anything */
    memset((void *) to, 0, DBOOK_MAX_ISBN);
    
    for (i = 0; i < strlen(from); i++){
        if (isdigit(from[i]) || from[i] == 'X' || from[i] == 'x') {
            to[j] = from[i];
            j ++;
        }
    }

    /* terminate string */
    to[j] = '\0'; 

    return DBOOK_TRUE;
}

/**
 * Checks if the isbn is a isbn 13. Does not validate only takes the length
 */
int dbook_is_isbn_13(DBOOK_CHAR *isbn){
    DBOOK_CHAR sane[DBOOK_MAX_ISBN];

    memset((void *) sane, 0, DBOOK_MAX_ISBN);
    dbook_sanitize_isbn(isbn, sane);

    if (strlen(sane) == 13)
        return(DBOOK_TRUE);

    return(DBOOK_FALSE);
}

/**
 * Checks if the isbn is a isbn 10. Does not validate only takes the length
 */
int dbook_is_isbn_10(DBOOK_CHAR *isbn){
    DBOOK_CHAR sane[DBOOK_MAX_ISBN];

    memset((void *)sane, 0, DBOOK_MAX_ISBN);
    dbook_sanitize_isbn(isbn, sane);

    if (strlen(sane) == 10)
        return(DBOOK_TRUE);

    return(DBOOK_FALSE);
}

void *xmalloc(size_t sz) {
    void *ptr = malloc(sz);

    /* if this happens, expect a crash :( */
    if (sz == NULL) {
        DBOOK_SET_ERROR(DBOOK_ERR_MALLOC);
        dbook_perror(); /* we print this *now* as it's quite fatal */
        return ptr;
    }

    return ptr;
}

/* gives us a new NULLed dbook_item */
dbook_item *dbook_new_item() {
    dbook_item *ret = xmalloc(sizeof(dbook_item));
    memset(ret, NULL, sizeof(dbook_item));
    return ret;
}

/* free an item made by dbook_new_item() */
void dbook_free_item (dbook_item *item) {
    DBOOK_CHAR **i, *fields[] = {item->title, (DBOOK_CHAR *) NULL}; /* XXX */

    /* loop fields freeing if they were allocated */
    for (i = fields; *i != NULL; i ++) {
        if (i != NULL) {
            free(*i);
        }
    }

    /* now free the struct itself */
    free(item);
}
