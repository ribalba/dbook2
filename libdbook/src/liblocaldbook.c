/*
 * $Id$
 * -----------------------
 * Does everything locally
 */
#include <ctype.h> 

int dbook_check_isbn_loc(DBOOK_ISBN *isbnToCheck){
    return DBOOK_TRUE;
}

int dbook_isbn_10_to_13_loc(DBOOK_ISBN *from, DBOOK_ISBN *to){
    to = "9780091906122";
    return DBOOK_TRUE;
}

int dbook_isbn_13_to_10_loc(DBOOK_ISBN *from, DBOOK_ISBN *to){
    to = "0091906121";
    return DBOOK_TRUE;
}

int dbook_sanitize_loc(char *from, DBOOK_ISBN *to){
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

