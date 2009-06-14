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
    
    PyObject *book_dict = PyDict_New();
    
    if(!PyArg_ParseTuple(args, "s", isbn)){
        return NULL;
    }
    
    dbook_sanitize(isbn, book_isbn);
    rtn = dbook_get_isbn_details(book_isbn, &book_details);
    
    /* TODO: Figure out how to translate book_details into a python obj */
    PyDict_SetItem(book_dict, PyString_FromString("title"), PyString_FromString(book_details.title));
    PyDict_SetItem(book_dict, PyString_FromString("author"), PyString_FromString(book_details.author));
    PyDict_SetItem(book_dict, PyString_FromString("date"), PyString_FromString(book_details.date));
    PyDict_SetItem(book_dict, PyString_FromString("publisher"), PyString_FromString(book_details.publisher));
    PyDict_SetItem(book_dict, PyString_FromString("edition"), Py_BuildValue("d", book_details.edition));
    PyDict_SetItem(book_dict, PyString_FromString("pagecount"), Py_BuildValue("d", book_details.pagecount));
    PyDict_SetItem(book_dict, PyString_FromString("image_path"), PyString_FromString(book_details.image_path));
    PyDict_SetItem(book_dict, PyString_FromString("category"), PyString_FromString(book_details.category));
    PyDict_SetItem(book_dict, PyString_FromString("url"), PyString_FromString(book_details.url));
    PyDict_SetItem(book_dict, PyString_FromString("booktype"), PyString_FromString(book_details.booktype));
    
    return book_dict;
}

static PyMethodDef dbook_methods[] = {
    {"check_isbn", check_isbn,  METH_VARARGS, "Check ISBN is valid"},
    {"isbn_10_to_13", isbn_10_to_13, METH_VARARGS, "Convert ISBN10 to ISBN13"},
    {"isbn_13_to_13", isbn_13_to_10, METH_VARARGS, "Convert ISBN13 to ISBN10"},
    {"sanitize", sanitize, METH_VARARGS, "Sanitize ISBN"},
    {"get_isbn_details", get_isbn_details, METH_VARARGS, "Get Details on a book in a dict"},
    {NULL, NULL, 0, NULL},
};

PyMODINIT_FUNC initdbook(void){
    (void) Py_InitModule("dbookpy", dbook_methods);
}