/*;
 * DBOOK2
 * main functionality of shared library
 * $Id$
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbook.h"

/* externed in libdbook.h */
int             dbook_debug_flag = 0;
int             dbook_errno = DBOOK_ERR_NONE;
char            dbook_err_file[DBOOK_MAX_ERRFILE] = "";
int             dbook_err_line = 0;
dbook_bkend     *dbook_bkend_list[DBOOK_MAX_BKENDS];
int             dbook_bkends_in_use = 0;

#define DBOOK_ERR_NOT_IMPL "Error code not implemented"
char *dbook_err_descrs[] = {
    "No error",
    "Unknown error",
    "Invalid ISBN",
    "Wrong ISBN len",
    "XML parsing failure",
    "Backend not set",
    "Too many backends in use",
    "libdbook not initialised, use dbook_initialise()",
    "Malloc failure",
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL,
    DBOOK_ERR_NOT_IMPL
};

/**
 * Backend definitions
 * Only one for now, but we hope to allow for future plugins.
 */
dbook_bkend dbook_bkend_dbook_org = {
    "Dbook.org Lookup Service",
    &dbook_org_get_item_details
};

/* A lookup table of available backends, indexes should match 
 * DBOOK_BKEND_* definitions in dbook.h
 * These are loaded in dbook_init();
 * Can't be initialised here unfortunately.
 */
dbook_bkend *dbook_avail_bkends[DBOOK_MAX_BKENDS];

int dbook_initialised = 0;

/* set up the available backends and other initialisation */
int dbook_initialise() {
    int i;

    /* for now, we only support our backend */
    dbook_avail_bkends[0] = &dbook_bkend_dbook_org;

    /* fill unimplemented backends */
    for (i = 1; i < DBOOK_MAX_BKENDS; i ++) {
        dbook_avail_bkends[i] = NULL;
    }

    dbook_initialised = 1;

    return DBOOK_TRUE;
}

/* call this at the start of all outward facing functions that need
 * to use backends.
 */
int dbook_check_initialised() {
    if (dbook_initialised) {
        return DBOOK_TRUE;
    }

    DBOOK_SET_ERROR(DBOOK_ERR_UNINITIALISED);
    return DBOOK_FALSE;
}

int dbook_get_item_details(DBOOK_CHAR *osbn, dbook_item *item) {

    /* check dbook is initialised */
    if (dbook_check_initialised() == DBOOK_FALSE)
        return DBOOK_FALSE;

    /* check atleast one backend was sleected */
    if (dbook_bkends_in_use == 0) {
        DBOOK_SET_ERROR(DBOOK_ERR_NO_BACKEND);
        return DBOOK_FALSE;
    }

    /* for now we always use the first registered backend.
     * This will change when/if we have further backends.
     */
    return dbook_bkend_list[0]->get_item_details_func(osbn, item);
}

/*
 * XXX this probably needs revision
 */
int dbook_register_backend(int bk) {

    /* check dbook is initialised */
    if (dbook_check_initialised() == DBOOK_FALSE) {
        return DBOOK_FALSE;
    }

    /* do we have space for another backend */
    if (dbook_bkends_in_use == DBOOK_MAX_BKENDS) {
        DBOOK_SET_ERROR(DBOOK_ERR_TOO_MANY_BKENDS);
        return DBOOK_FALSE;
    }

    dbook_bkend_list[dbook_bkends_in_use] = dbook_avail_bkends[bk];
    dbook_bkends_in_use ++;

    return DBOOK_TRUE;
}

/* print debug messages to stderror *if* dbook_debug_flag is set */
void dbook_debug(char *msg) {
    if (dbook_debug_flag != DBOOK_TRUE)
        return;

    fprintf(stderr, "DBOOK_DEBUG: %s\n", msg);
}

/* print an error message - only the library implementor uses this.
 * ie. Dont print from within library functions. The return vals of 
 * functions will inform the implementor that an error occured, not
 * the library making noise on the console!
 */
void dbook_perror() {
    fprintf(stderr, "DBOOK_ERROR %d\t(%s:%d):\n\t\t%s\n", dbook_errno,
            dbook_err_file, dbook_err_line,
            dbook_err_descrs[dbook_errno]);
}

void *xmalloc(size_t sz) {
    void *ptr = malloc(sz);

    /* if this happens, expect a crash :( */
    if (sz == NULL) {
        DBOOK_SET_ERROR(DBOOK_ERR_MALLOC);
        dbook_perror(); /* we print this *now* as it's quite fatal */
        return ptr;
    }

    return ptr;
}

/* gives us a new NULLed dbook_item */
dbook_item *dbook_new_item() {
    dbook_item *ret = xmalloc(sizeof(dbook_item));
    memset(ret, NULL, sizeof(dbook_item));
    return ret;
}

/* free an item made by dbook_new_item() */
void dbook_free_item (dbook_item *item) {
    DBOOK_CHAR **i, *fields[] = {item->title, (DBOOK_CHAR *) NULL}; /* XXX */

    /* loop fields freeing if they were allocated */
    for (i = fields; *i != NULL; i ++) {
        if (i != NULL) {
            free(*i);
        }
    }

    /* now free the struct itself */
    free(item);
}
