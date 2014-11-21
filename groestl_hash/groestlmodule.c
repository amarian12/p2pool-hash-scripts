#include <Python.h>


#include "groestl.h"


static PyObject *groestl_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);


#if PY_MAJOR_VERSION >= 3
    groestl_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    groestl_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}


static PyMethodDef groestlMethods[] = {
    { "getPoWHash", groestl_getpowhash, METH_VARARGS, "Returns the proof of work hash using groestl hash" },
    { NULL, NULL, 0, NULL }
};


#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef groestlModule = {
    PyModuleDef_HEAD_INIT,
    "groestl_hash",
    "...",
    -1,
    groestlMethods
};


PyMODINIT_FUNC PyInit_groestl_hash(void) {
    return PyModule_Create(&groestlModule);
}


#else


PyMODINIT_FUNC initgroestl_hash(void) {
    (void) Py_InitModule("groestl_hash", groestlMethods);
}
#endif
