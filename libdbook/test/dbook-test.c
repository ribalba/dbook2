/*
 * DBOOK2
 * $Id$
 * -----------------------
 * libdbook test stub
 */

#include <stdio.h>
#include <libdbook.h>
#include <string.h>

int main(void) {
	int ret;
	dbook_book b1;
	dbook_isbn i1="", i2="", i3="", i4 = "";
	dbook_config c1, c2;
    memset(i3, 0, strlen(i3));
    memset(i4, 0, strlen(i4));

	printf("dbook_check_isbn() 10...\n");
	ret = dbook_check_isbn("059305427X");
    if(ret != DBOOK_TRUE){
        printf("ERROR in dbook_check_isbn true\n");
    }
    
    printf("dbook_check_isbn() 10...\n");
	ret = dbook_check_isbn("059305527X");
    if(ret != DBOOK_FALSE){
        printf("ERROR in dbook_check_isbn false\n");
    }

	printf("dbook_check_isbn() 13...\n");
	ret = dbook_check_isbn("978-0593054277");
    if(ret != DBOOK_TRUE){
        printf("ERROR in dbook_check_isbn true\n");
    }
    
    printf("dbook_check_isbn() 13...\n");
	ret = dbook_check_isbn("978-0593055277");
    if(ret != DBOOK_FALSE){
        printf("ERROR in dbook_check_isbn false\n");
    }

	printf("dbook_isbn_10_to_13()...\n");
	ret = dbook_isbn_10_to_13("059305427X", i1);
	printf("returned: %d\n\n", ret);

	printf("dbook_isbn_13_to_10()...\n");
	ret = dbook_isbn_13_to_10("978-0593054277", i2);
	printf("returned: %d\n\n", ret);

	printf("dbook_sanitize()...\n");
	ret = dbook_sanitize("978-0593054277", i3);
    if (strcmp(i3, "9780593054277") != 0) {
        printf("ERROR in dbook_sanitize test1\n");
    }

    printf("dbook_sanitize()...\n");
	ret = dbook_sanitize("978-059305aldh42-+*77", i4);
    if (strcmp(i4, "9780593054277") != 0) {
        printf("ERROR in dbook_sanitize test2\n");
    }

    printf("dbook_get_isbn_details()...\n");
	ret = dbook_get_isbn_details(i3, &b1);
	printf("returned: %d\n\n", ret);

    printf("dbook_is_isbn_13()...\n");
	ret = dbook_is_isbn_13("9780593054277");
    if (ret != DBOOK_TRUE) {
        printf("ERROR in is_isbn13\n");
    }

    printf("dbook_is_isbn_13()...\n");
	ret = dbook_is_isbn_13("978059305427x");
    if (ret != DBOOK_FALSE) {
        printf("ERROR in is_isbn13 error\n");
    }
 
    printf("dbook_is_isbn_10()...\n");
	ret = dbook_is_isbn_10("0593054277");
    if (ret != DBOOK_TRUE) {
        printf("ERROR in is_isbn10\n");
    }

    printf("dbook_is_isbn_10()...\n");
	ret = dbook_is_isbn_10("059305427x");
    if (ret != DBOOK_FALSE) {
        printf("ERROR in is_isbn10 error\n");
    }


/*	printf("dbook_configure()...\n");
	ret = dbook_configure(&c1);
	printf("returned: %d\n\n", ret);

	printf("dbook_get_config()...\n");
	ret = dbook_get_config(&c2);
	printf("returned: %d\n\n", ret);
*/
	printf("Tests complete...\n");

	return 0;
}
