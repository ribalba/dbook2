/*
 * DBOOK2
 * $Id$
 * -----------------------
 * libdbook test stub
 */

#include <stdio.h>
#include <libdbook.h>

int main(void) {
	int ret;
	dbook_book b1;
	dbook_isbn i1, i2, i3;
	dbook_config c1, c2;

	printf("dbook_check_isbn()...\n");
	ret = dbook_check_isbn("978-0593054277");
	printf("returned: %d\n\n", ret);

	printf("dbook_isbn_10_to_13()...\n");
	ret = dbook_isbn_10_to_13("059305427X", i1);
	printf("returned: %d\n\n", ret);

	printf("dbook_isbn_13_to_10()...\n");
	ret = dbook_isbn_13_to_10("978-0593054277", i2);
	printf("returned: %d\n\n", ret);

	printf("dbook_sanitize()...\n");
	ret = dbook_sanitize("978-0593054277", i3);
	printf("returned: %d\n\n", ret);

	printf("dbook_get_isbn_details()...\n");
	ret = dbook_get_isbn_details(i3, &b1);
	printf("returned: %d\n\n", ret);

	printf("dbook_configure()...\n");
	ret = dbook_configure(&c1);
	printf("returned: %d\n\n", ret);

	printf("dbook_get_config()...\n");
	ret = dbook_get_config(&c2);
	printf("returned: %d\n\n", ret);

	printf("Tests complete...\n");

	return 0;
}
