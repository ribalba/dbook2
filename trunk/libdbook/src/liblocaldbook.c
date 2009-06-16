/*
 * $Id$
 * -----------------------
 * Does everything locally
 */

#include <stdio.h>
#include <ctype.h> 
#include "libdbook.h"

/** 
  * Returns the checksum for a ISBN 10 passed in as paramter
  */
char dbook_gen_chksum_10_loc(DBOOK_ISBN *isbnToTest) {

    /*The multiplier */
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
char dbook_gen_chksum_13_loc(DBOOK_ISBN *isbnToTest) {

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



int dbook_check_isbn_loc(DBOOK_ISBN *isbnToCheck){

    dbook_isbn isbnToTest = "";


    dbook_sanitize(isbnToCheck, isbnToTest);

    /* If the size is equal to 10 do it */
    if (dbook_is_isbn_10(isbnToTest) == DBOOK_TRUE) {
        int checkSum = dbook_gen_chksum_10(isbnToTest);

        if (checkSum == 'X' && isbnToTest[9]=='X')
            return DBOOK_TRUE;

        if (checkSum == (isbnToTest[9] - '0'))
            return DBOOK_TRUE;

    }


    /* If the size is equal to 13 do it */
    else if (dbook_is_isbn_13(isbnToTest) == DBOOK_TRUE) {

        int checkSum = dbook_gen_chksum_13(isbnToTest);

        if (checkSum == (isbnToTest[12] - '0'))
            return DBOOK_TRUE;

    }

    else {
        fprintf(stderr,"It seams the ISBN passed in is neither a valid 10 or 13"); 
    }


    /* If everything fails => fail */
    return DBOOK_FALSE;
}

int dbook_isbn_10_to_13_loc(DBOOK_ISBN *from, DBOOK_ISBN *to){
    //Null everything before we do anything
    memset(to, 0, strlen(to));

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

    strncpy(to,"978",3);
    strncat(to,fromClean,9);
    char chkSum = dbook_gen_chksum_13(to) + '0';

    strncat(to, &chkSum,1);


    return DBOOK_TRUE;
}

int dbook_isbn_13_to_10_loc(DBOOK_ISBN *from, DBOOK_ISBN *to){
    //Null everything before we do anything
    memset(to, 0, strlen(to));
    if(dbook_is_isbn_13(from) != DBOOK_TRUE) {
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
int dbook_sanitize_loc(char *from, DBOOK_ISBN *to){
    //Null everything before we do anything
    memset(to, 0, strlen(to));
    
    int i;
    for (i = 0; i< strlen(from); i++){
        if ( isdigit(from[i])  || from[i] == 'X' || from[i] == 'x'){
            strncat(to, &from[i], 1);
        }
    }
    return DBOOK_TRUE;
}

int dbook_get_isbn_details_loc(DBOOK_ISBN *whichBook, dbook_book *book){
    strcpy(book->isbn, "9780091906122");
    strcpy(book->title, "Are You a Geek?");
    strcpy(book->author, "Tim Collins");
    strcpy(book->date, "6-09-2005");
    strcpy(book->publisher, "Ebury Press");
    return DBOOK_TRUE;
}


/**
 * Checks if the isbn is a isbn 13. Does not validate only takes the length
 */
int dbook_is_isbn_13_loc(DBOOK_ISBN *isbnToCheck){
    dbook_isbn retVal = "";
    dbook_sanitize(isbnToCheck, retVal);
    return ((strlen(retVal) == 13) ? DBOOK_TRUE : DBOOK_FALSE) ;
}

/**
 * Checks if the isbn is a isbn 10. Does not validate only takes the length
 */
int dbook_is_isbn_10_loc(DBOOK_ISBN *isbnToCheck){
    dbook_isbn retVal = "";
    dbook_sanitize(isbnToCheck, retVal);
    return ((strlen(retVal) == 10) ? DBOOK_TRUE : DBOOK_FALSE) ;
}


