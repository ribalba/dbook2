#include <Python.h>
#include <libdbook.h>

static PyObject * check_isbn(PyObject *self, PyObject *args)
{
    char* isbn;
    int rtn;
    
    if(!PyArg_ParseTuple(args, "s", isbn)){
        return NULL;
    }
    
    rtn = dbook_check_isbn(isbn);
    return Py_BuildValue("i", rtn);
}

static PyObject * isbn_10_to_13(PyObject *self, PyObject *args)
{
    char *isbn;
    dbook_isbn ret_isbn;
    int rtn;
    
    if(!PyArg_ParseTuple(args, "s", isbn)){
        return NULL;
    }
    
    rtn = dbook_isbn_10_to_13(isbn, ret_isbn);
    
    return Py_BuildValue("s", ret_isbn);
}

static PyObject * isbn_13_to_10(PyObject *self, PyObject *args)
{
    char *isbn;
    dbook_isbn ret_isbn;
    int rtn;
    
    if(!PyArg_ParseTuple(args, "s", isbn)){
        return NULL;
    }
    
    rtn = dbook_isbn_13_to_10(isbn, ret_isbn);
    
    return Py_BuildValue("s", ret_isbn);
}

static PyObject * sanitize(PyObject *self, PyObject *args)
{
    char *isbn;
    dbook_isbn ret_isbn;
    int rtn;
    
    if(!PyArg_ParseTuple(args, "s", isbn)){
        return NULL;
    }
    
    rtn = dbook_sanitize(isbn, ret_isbn);
    
    return Py_BuildValue("s", ret_isbn);
}

static PyObject * get_isbn_details(PyObject * self, PyObject *args){
    char* isbn;
    dbook_isbn book_isbn;
    dbook_book book_details;
    int rtn;
    
    if(!PyArg_ParseTuple(args, "s", isbn)){
        return NULL;
    }
    
    dbook_sanitize(isbn, book_isbn);
    rtn = dbook_get_isbn_details(book_isbn, &book_details);
    
    /* TODO: Figure out how to translate book_details into a python obj */
}

static PyMethodDef dbook_methods[] = {
    {"check_isbn", check_isbn,  METH_VARARGS, "Check ISBN is valid"},
    {"isbn_10_to_13", isbn_10_to_13, METH_VARARGS, "Convert ISBN10 to ISBN13"},
    {"isbn_13_to_13", isbn_13_to_10, METH_VARARGS, "Convert ISBN13 to ISBN10"},
    {"sanitize", sanitize, METH_VARARGS, "Sanitize ISBN"},
    {NULL, NULL, 0, NULL},
};

PyMODINIT_FUNC initdbook(void){
    (void) Py_InitModule("dbook", dbook_methods);
}
