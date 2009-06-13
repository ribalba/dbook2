#include <stdio.h>
#include <string.h>
#include "libdbook.h"

dbook_config *configuration;

int dbook_check_isbn(DBOOK_ISBN *isbnToCheck){
    return DBOOK_TRUE;
}

int dbook_10_to_13(DBOOK_ISBN *from, DBOOK_ISBN *to){
    to = "9780091906122";
    return DBOOK_TRUE;
}

int dbook_13_to_10(DBOOK_ISBN *from, DBOOK_ISBN *to){
    to = "0091906121";
    return DBOOK_TRUE;
}

int dbook_sanatize(char *from, DBOOK_ISBN *to){
    to = "9780091906122";
    return DBOOK_TRUE;
}

int dbook_get_isbn_details(DBOOK_ISBN *whichBook, dbook_book *book){
    strcpy(book->isbn, "9780091906122");
    strcpy(book->title, "Are You a Geek?");
    strcpy(book->author, "Tim Collins");
    strcpy(book->date, "6-09-2005");
    strcpy(book->publisher, "Ebury Press");
    return DBOOK_TRUE;
}

int dbook_configure(dbook_config *config){
    configuration = config;
    return DBOOK_TRUE;
}

int dbook_get_config(dbook_config *config){
    config = configuration;
    return DBOOK_TRUE;
}
