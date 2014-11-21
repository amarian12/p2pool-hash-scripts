#include <Python.h>

#include "x14.h"

static PyObject *x14_getpowhash(PyObject *self, PyObject *args)
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
    x14_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    x14_hash((char *)PyString_AsString((PyObject*) input), output);
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

static PyMethodDef X14Methods[] = {
    { "getPoWHash", x14_getpowhash, METH_VARARGS, "Returns the proof of work hash using x14 hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef X14Module = {
    PyModuleDef_HEAD_INIT,
    "x14_hash",
    "...",
    -1,
    X14Methods
};

PyMODINIT_FUNC PyInit_x14_hash(void) {
    return PyModule_Create(&X14Module);
}

#else

PyMODINIT_FUNC initx14_hash(void) {
    (void) Py_InitModule("x14_hash", X14Methods);
}
#endif
