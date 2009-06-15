/*
 * DBOOK2
 * $Id$
 * -----------------------
 * 
 */

#include <stdio.h>
#include <string.h>
#include "libdbook.h"
#include "liblocaldbook.c"

char serverToTalkTo[50];
int onlineMode = DBOOK_FALSE;

int dbook_check_isbn(DBOOK_ISBN *isbnToCheck){
    if (onlineMode == DBOOK_FALSE){
        return dbook_check_isbn_loc(isbnToCheck);
    }else{
        //dbook_sanitize_dis(from, to);
    }

    return DBOOK_FALSE;
}

int dbook_isbn_10_to_13(DBOOK_ISBN *from, DBOOK_ISBN *to){
    if (onlineMode == DBOOK_FALSE){
       return dbook_isbn_10_to_13_loc(from, to);
    }else{
        //dbook_sanitize_dis(from, to);
    }

    return DBOOK_FALSE;

}

int dbook_isbn_13_to_10(DBOOK_ISBN *from, DBOOK_ISBN *to){
    if (onlineMode == DBOOK_FALSE){
       return dbook_isbn_13_to_10_loc(from, to);
    }else{
        //dbook_sanitize_dis(from, to);
    }

    return DBOOK_FALSE;
}

int dbook_sanitize(char *from, DBOOK_ISBN *to){
    if (onlineMode == DBOOK_FALSE){
        dbook_sanitize_loc(from, to);
    }else{
        //dbook_sanitize_dis(from, to);
    }

    return DBOOK_TRUE;
}

int dbook_get_isbn_details(DBOOK_ISBN *whichBook, dbook_book *book){
    memset(book, 0, sizeof(dbook_book));
    strcpy(book->isbn, "9780091906122");
    strcpy(book->title, "Are You a Geek?");
    strcpy(book->author, "Tim Collins");
    strcpy(book->date, "6-09-2005");
    strcpy(book->publisher, "Ebury Press");
    return DBOOK_TRUE;
}

int dbook_configure(dbook_config *config){
    strcpy(serverToTalkTo, config->server);
    return DBOOK_TRUE;
}

int dbook_get_config(dbook_config *config){
    strcpy(config->server, serverToTalkTo);
    return DBOOK_TRUE;
}


int dbook_is_isbn_13(DBOOK_ISBN *isbnToCheck){
    if (onlineMode == DBOOK_FALSE){
        return dbook_is_isbn_13_loc(isbnToCheck);
    }else{
        //dbook_sanitize_dis(from, to);
    }
    return DBOOK_FALSE;
}

int dbook_is_isbn_10(DBOOK_ISBN *isbnToCheck){
    if (onlineMode == DBOOK_FALSE){
        return dbook_is_isbn_10_loc(isbnToCheck);
    }else{
        //dbook_sanitize_dis(from, to);
    }
    return DBOOK_FALSE;

}

char dbook_genChkSum10(DBOOK_ISBN *isbnToTest){
    if (onlineMode == DBOOK_FALSE){
        return dbook_genChkSum10_loc(isbnToTest);
    }else{
        //dbook_sanitize_dis(from, to);
    }
    return DBOOK_FALSE;
}

char dbook_genChkSum13(DBOOK_ISBN *isbnToTest){
    if (onlineMode == DBOOK_FALSE){
        return dbook_genChkSum13_loc(isbnToTest);
    }else{
        //dbook_sanitize_dis(from, to);
    }
    return DBOOK_FALSE;
}

