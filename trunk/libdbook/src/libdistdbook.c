'/*
 * $Id$
 * -----------------------
 * The distributed dbook thing
 */

#include <stdio.h>
#include <string.h>
#include "libdbook.h"


/** 
  Returns the checksum for a ISBN 10 passed in as paramter
  */
char dbook_genChkSum10_dis(DBOOK_ISBN *isbnToTest) {
    return 'X';
}


/** 
  Returns the checksum for a ISBN 13 passed in as paramter
  */
char dbook_genChkSum13_dis(DBOOK_ISBN *isbnToTest) {
    return 'X';
}



int dbook_check_isbn_dis(DBOOK_ISBN *isbnToCheck){
    return DBOOK_FALSE;
}

int dbook_isbn_10_to_13_dis(DBOOK_ISBN *from, DBOOK_ISBN *to){
    return DBOOK_FALSE;
}

int dbook_isbn_13_to_10_dis(DBOOK_ISBN *from, DBOOK_ISBN *to){
    return DBOOK_FALSE;
}

/**
 * Removes all the rubbish that is normally in an isbn like - and spaces
 * first value is a char * to be cleaned
 * second is a dbook_isbn for the clean isbn to be put in
 */ 
int dbook_sanitize_dis(char *from, DBOOK_ISBN *to){
    return DBOOK_FALSE;
}

int dbook_get_isbn_details_dis(DBOOK_ISBN *whichBook, dbook_book *book){
    return DBOOK_FALSE;
}


/**
 * Checks if the isbn is a isbn 13. Does not validate only takes the length
 */
int dbook_is_isbn_13_dis(DBOOK_ISBN *isbnToCheck){
    return DBOOK_FALSE;
}

/**
 * Checks if the isbn is a isbn 10. Does not validate only takes the length
 */
int dbook_is_isbn_10_dis(DBOOK_ISBN *isbnToCheck){
    return DBOOK_FALSE; 
}

