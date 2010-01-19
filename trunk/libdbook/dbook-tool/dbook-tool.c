/*
 * DBOOK2
 * dbook-tool cli frontend
 * $Id$
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dbook.h>
#include <string.h>

#define DBT_MODE_NONE			0
#define DBT_MODE_CHECK_ISBN 		1
#define DBT_MODE_ISBN_10_TO_13		2
#define DBT_MODE_ISBN_13_TO_10		3
#define DBT_MODE_SANITIZE		4
#define DBT_MODE_GET_ISBN_DETAILS	5
#define DBT_MODE_IS_ISBN_10		6
#define DBT_MODE_IS_ISBN_13		7

#define DBT_FILTER_NONE			0
#define DBT_FILTER_PLAIN		1
#define DBT_FILTER_BIBTEX		2

void usage();
void set_mode(int);
int  get_details(char *);
void not_implemented(); /* XXX tmp */

int mode = DBT_MODE_NONE;
int filter = DBT_FILTER_NONE;

int main(int argc, char **argv) {

    int c, ok = DBOOK_FALSE;
    char *isbn;
    int filter_ok;

    /* in development, turn on debugging */
    dbook_debug_flag = 0;

    /* set up libdbook */
    dbook_initialise();

    opterr = 0;

    while ((c = getopt(argc, argv, "cdjko:sxy")) != -1) {
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
            case 'o':
                if (filter != DBT_FILTER_NONE) {
                    fprintf(stderr,
                            "*err: only one output filter may be set\n");
                    exit(EXIT_FAILURE);
                }

                /* will need to be more intricate,
                 * when the user can make thier own
                 * filters
                 */
                filter_ok = 0;
                if (strcmp(optarg, "plain") == 0) {
                    filter = DBT_FILTER_PLAIN;
                    filter_ok = 1;
                }

                if (strcmp(optarg, "bibtex") == 0) {
                    filter = DBT_FILTER_BIBTEX;
                    filter_ok = 1;
                }

                /* atleast one should be recognised */
                if (filter_ok == 0) {
                    fprintf(stderr,
                            "*err: unknown filter: '%s'\n", optarg);
                    usage();
                    exit(EXIT_FAILURE);
                }
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
            default:
                fprintf(stderr, "*err: unknown flag: '-%c'\n", optopt);
                usage();
                exit(EXIT_FAILURE);
                break;
        }
    }

    /* check only one isbn supplied */
    if (optind != argc - 1) {
        fprintf(stderr, "*err: supply exactly one isbn code\n");
        usage();
        exit(EXIT_FAILURE);
    }

    isbn = argv[optind];

    switch (mode) {
        case DBT_MODE_NONE:
            fprintf(stderr, "*err: choose a mode\n");
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
            ok = get_details(isbn);
            break;
        case DBT_MODE_IS_ISBN_10:
            not_implemented(); /* XXX */
            break;
        case DBT_MODE_IS_ISBN_13:
            not_implemented(); /* XXX */
            break;
    }

    if (ok == DBOOK_FALSE){
        dbook_perror();
    }

    return ok;
}

void usage() {
    printf("usage:\n");
    printf("\tdbook-tool mode isbn\n");
    printf("\n");
    printf("\t-c		check isbn is valid 10 or 13 code\n");
    printf("\t-d		get book details\n");
    printf("\t-j		check is valid isbn 10 code\n");
    printf("\t-k		check is valid isbn 13 code\n");
    printf("\t-o type	\tselect output type\n");
    printf("\t\t\tplain:	plain text output\n");
    printf("\t\t\tbibtex:	bibtex output\n");
    printf("\t-s 		sanitize (strip junk for isbn)\n");
    printf("\t-x 		convert isbn 10 to 13\n");
    printf("\t-y 		convert isbn 13 to 10\n");
}

void set_mode(int n_mode) {

    /* if already in a mode, user was wrong */
    if (mode != DBT_MODE_NONE) {
        fprintf(stderr, "*err: choose only one mode\n");
        usage();
        exit(EXIT_FAILURE);
    }

    mode = n_mode;
}

int get_details(char *isbn) {
    dbook_item *item;
    char *out;
    int ok = DBOOK_FALSE;

    item = dbook_new_item();

    /* For now we only support the dbook.org backend */
    dbook_register_backend(DBOOK_BKEND_DBOOK_ORG);

    /* If no output filter set, choose plain as a safe default */
    if (filter == DBT_FILTER_NONE)
        filter = DBT_FILTER_BIBTEX;

    ok = dbook_get_item_details(isbn, item);
    if (ok == DBOOK_TRUE) {
        switch (filter) {
            case DBT_FILTER_PLAIN:
                out = dbook_filter_book_plain(item);
                break;
            case DBT_FILTER_BIBTEX:
                out = dbook_filter_book_bibtex(item);
                break;
            default:
                /* NOREACH */
                fprintf(stderr, "*err: unkown internal filter!");
                exit(EXIT_FAILURE);
                break;
        }
        printf("%s\n", out);
    }

    dbook_free_item(item);

    return ok;
}

void not_implemented() {
    fprintf(stderr, "*err: feature not coded yet\n");
}
