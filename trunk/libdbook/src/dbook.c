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
 */
dbook_bkend dbook_bkend_dbook_org = {
    "Dbook.org Lookup Service",
    &dbook_org_get_isbn_details
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

int dbook_get_isbn_details(DBOOK_CHAR *isbn, dbook_item *book) {

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
    return dbook_bkend_list[0]->get_isbn_details_func(isbn, book);
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
char dbook_gen_chksum_10(DBOOK_CHAR *isbnToTest) {

    /* The multiplier */
    int multy = 10;
    int sum = 0;
    int checkSum = 0;
    int i = 0, atoi_res;

    for (i = 0; i < 9; i++) {
        /* Because atio thinks it is a pointer to a array it will 
         * shoot off into memory. So if you want to convert a single char 
         * into a int don't use atoi.
         */
        atoi_res = isbnToTest[i] - '0';
        sum = sum + (atoi_res * multy);
        multy --;
    }

    checkSum = (11 - (sum % 11));

    if (checkSum == 10)
        return 'X';

    if (checkSum == 11)
        return 0;

    return checkSum;
}


/** 
  Returns the checksum for a ISBN 13 passed in as paramter
  */
char dbook_gen_chksum_13(DBOOK_CHAR *isbnToTest) {

    /* The multiplyer */
    int multy = 10;
    int sumodd = 0;
    int sumeve = 0;
    int checkSum = 0;
    int i = 0;
    int atoi1, atoi2;

    for (i = 0; i <= 11; i = i + 2) {
        /* Same as above */
        atoi1 = isbnToTest[i] - '0';
        atoi2 = isbnToTest[i + 1] - '0';

        sumodd = sumodd + atoi1;
        sumeve = sumeve + atoi2;
    }

    checkSum = (sumodd + (sumeve * 3)) % multy;

    if (checkSum != 0)
        checkSum = multy - checkSum;

    return checkSum;

}

/*
 * check an ISBN is valid
 */
int dbook_check_isbn(DBOOK_CHAR *isbnToCheck){

    int ret = DBOOK_FALSE;
    int checksum;
    DBOOK_CHAR *isbn = (DBOOK_CHAR *) malloc(DBOOK_MAX_ISBN);
    dbook_sanitize(isbnToCheck, isbn);
    
    /* If the size is equal to 10 do it */
    if (dbook_is_isbn_10(isbn) == DBOOK_TRUE) {
        checksum = dbook_gen_chksum_10(isbn);

        if (checksum == 'X' && isbn[9] == 'X') {
            ret = DBOOK_TRUE;
            goto clean;
        }

        if (checksum == (isbn[9] - '0')) {
            ret = DBOOK_TRUE;
            goto clean;
        }
    /* If the size is equal to 13 do it */
    } else if (dbook_is_isbn_13(isbn) == DBOOK_TRUE) {

        checksum = dbook_gen_chksum_13(isbn);

        if (checksum == (isbn[12] - '0')) {
            ret = DBOOK_TRUE;
            goto clean;
        }
    }else{
        ret = DBOOK_FALSE;
    }

clean:
    free(isbn);

    /* If everything fails => fail */
    return ret;
}

/* XXX don't use camel case */
int dbook_isbn_10_to_13(DBOOK_CHAR *from, DBOOK_CHAR *to){
    char chkSum;

    memset(to, 0, strlen(to));

    /* XXX why is this printing, give it an errno and return that */
    if(dbook_is_isbn_10(from) != DBOOK_TRUE) {
        fprintf(stderr, "When calling dbook_isbn_10_to_13 please pass in a 10 based isbn");
        return DBOOK_FALSE;
    }

    if (dbook_check_isbn(from) != DBOOK_TRUE){
        fprintf(stderr, "Please pass in a valid isbn to dbook_isbn_10_to_13");
        return DBOOK_FALSE;
    }

    dbook_isbn fromClean = "";

    dbook_sanitize(from, fromClean);

    strncpy(to, "978",3);
    strncat(to,fromClean,9);
    chkSum = dbook_gen_chksum_13(to) + '0';

    strncat(to, &chkSum,1);
    return DBOOK_TRUE;
}

int dbook_isbn_13_to_10(DBOOK_CHAR *from, DBOOK_CHAR *to){
    memset(to, 0, strlen(to));

    if (dbook_is_isbn_13(from) != DBOOK_TRUE) {
        fprintf(stderr, "When calling dbook_isbn_13_to_10 please pass in a 10 based isbn");
        return DBOOK_FALSE;
    }

    if (dbook_check_isbn(from) != DBOOK_TRUE){
        fprintf(stderr, "Please pass in a valid isbn to dbook_isbn_13_to_10");
        return DBOOK_FALSE;
    }

    if (strncmp(from,"978",3) !=0) {
        fprintf(stderr, "Only ISBN-13 numbers beginning with 978 can be converted to ISBN-10.");
        return DBOOK_FALSE;
    }
   
    dbook_isbn fromClean = "";

    dbook_sanitize(from, fromClean);


    strncpy(to,fromClean+3,9);
    
    char chkSum = dbook_gen_chksum_10(to);
    
    if (chkSum == 'X') {
       strncat(to,"X",1);
    } else {
        char chkSumDeci = chkSum + '0' ;
        strncat(to, &chkSumDeci,1);
    }

    return DBOOK_TRUE;
}

/**
 * Removes all the rubbish that is normally in an isbn like - and spaces
 * first value is a char * to be cleaned
 * second is a dbook_isbn for the clean isbn to be put in
 */ 
int dbook_sanitize(char *from, DBOOK_CHAR *to){
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
    int ret = DBOOK_FALSE;

    /* Allocate and zero buffer */
    DBOOK_CHAR *sane = (DBOOK_CHAR *) malloc(DBOOK_MAX_ISBN);
    memset((void *) sane, 0, DBOOK_MAX_ISBN);

    dbook_sanitize(isbn, sane);

    if (strlen(sane) == 13)
        ret = DBOOK_TRUE;

    free(sane);
    return ret;
}

/**
 * Checks if the isbn is a isbn 10. Does not validate only takes the length
 */
int dbook_is_isbn_10(DBOOK_CHAR *isbn){
    int ret = DBOOK_FALSE;

    /* Allocate and zero buffer */
    DBOOK_CHAR *sane = (DBOOK_CHAR *) malloc(DBOOK_MAX_ISBN);
    memset((void *)sane, 0, DBOOK_MAX_ISBN);

    dbook_sanitize(isbn, sane);

    if (strlen(sane) == 10)
        ret = DBOOK_TRUE;

    free(sane);
    return ret;
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

