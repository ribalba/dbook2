/*
 * DBOOK2
 * isbn_utils - various function for manipulating ISBN codes
 * $Id$
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbook.h"

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


