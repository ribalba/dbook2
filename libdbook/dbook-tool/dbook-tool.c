/*
 * DBOOK2
 * $Id$
 * -----------------------
 * dbook-tool cli frontend
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <libdbook.h>

#define DBT_MODE_NONE			0
#define DBT_MODE_CHECK_ISBN 		1
#define DBT_MODE_ISBN_10_TO_13		2
#define DBT_MODE_ISBN_13_TO_10		3
#define DBT_MODE_SANITIZE		4
#define DBT_MODE_GET_ISBN_DETAILS	5
#define DBT_MODE_IS_ISBN_10		6
#define DBT_MODE_IS_ISBN_13		7

void usage();
void set_mode(int);
void get_details(char *);
void not_implemented(); /* XXX tmp */

int mode = DBT_MODE_NONE;

int main(int argc, char **argv) {
	int c;
	char *isbn;

	opterr = 0;

	while ((c = getopt(argc, argv, "cdjksxy")) != -1) {
		switch (c) {
			case 'c':
				set_mode(DBT_MODE_CHECK_ISBN);
				break;
			case 'd':
				set_mode(DBT_MODE_GET_ISBN_DETAILS);
				break;
			case 'j':
				set_mode(DBT_MODE_IS_ISBN_10);
				break;
			case 'k':
				set_mode(DBT_MODE_IS_ISBN_13);
				break;
			case 's':
				set_mode(DBT_MODE_SANITIZE);
				break;
			case 'x':
				set_mode(DBT_MODE_ISBN_10_TO_13);
				break;
			case 'y':
				set_mode(DBT_MODE_ISBN_13_TO_10);
				break;
		}
	}

	/* check only one isbn supplied */
	if (optind != argc - 1) {
		printf("*err: supply exactly one isbn code\n");
		usage();
		exit(EXIT_FAILURE);
	}

	isbn = argv[optind];

	switch (mode) {
		case DBT_MODE_NONE:
			printf("*err: choose a mode\n");
			break;
		case DBT_MODE_CHECK_ISBN:
			not_implemented(); /* XXX */
			break;
		case DBT_MODE_ISBN_10_TO_13:
			not_implemented(); /* XXX */
			break;
		case DBT_MODE_ISBN_13_TO_10:
			not_implemented(); /* XXX */
			break;
		case DBT_MODE_SANITIZE:
			not_implemented(); /* XXX */
			break;
		case DBT_MODE_GET_ISBN_DETAILS:
			not_implemented(); /* XXX */
			get_details(isbn);
			break;
		case DBT_MODE_IS_ISBN_10:
			not_implemented(); /* XXX */
			break;
		case DBT_MODE_IS_ISBN_13:
			not_implemented(); /* XXX */
			break;
	}

	return EXIT_SUCCESS;
}

void usage() {
	printf("usage:\n");
	printf("\tdbook-tool mode isbn\n");
	printf("\n");
	printf("\t-c	check isbn is valid 10 or 13 code\n");
	printf("\t-d	get book details\n");
	printf("\t-j	check is valid isbn 10 code\n");
	printf("\t-k	check is valid isbn 13 code\n");
	printf("\t-s 	sanitize (strip junk for isbn)\n");
	printf("\t-x 	convert isbn 10 to 13\n");
	printf("\t-y 	convert isbn 13 to 10\n");
}

void set_mode(int n_mode) {

	/* if already in a mode, user was wrong */
	if (mode != DBT_MODE_NONE) {
		printf("*err: choose only one mode\n");
		usage();
		exit(EXIT_FAILURE);
	}

	mode = n_mode;
}

void get_details(char *isbn) {
	dbook_book bk;

	if(dbook_get_isbn_details(isbn, &bk) == DBOOK_TRUE) {
		printf("ISBN:		%s\n", isbn);
		printf("Title:		%s\n", bk.title);
		printf("Author:		%s\n", bk.author);
		printf("Date:		%s\n", bk.date);
		printf("Publisher:	%s\n", bk.publisher);
		printf("Edition:	%d\n", bk.edition);
		printf("Pages:		%d\n", bk.pagecount);
		printf("Image Path:	%s\n", bk.image_path);
		printf("Category:	%s\n", bk.category);
		printf("URL:		%s\n", bk.url);
		printf("Type:		%s\n", bk.booktype);
	} else {
		/* XXX say what error when err codes are in libdbook */
		printf("*err: an error occurred\n");
	}
}

void not_implemented() {
	printf("*err: feature not coded yet\n");
}
