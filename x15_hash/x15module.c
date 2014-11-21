#include <Python.h>

#include "x15.h"

static PyObject *x15_getpowhash(PyObject *self, PyObject *args)
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
    x15_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    x15_hash((char *)PyString_AsString((PyObject*) input), output);
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

static PyMethodDef X15Methods[] = {
    { "getPoWHash", x15_getpowhash, METH_VARARGS, "Returns the proof of work hash using X15 hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef X15Module = {
    PyModuleDef_HEAD_INIT,
    "x15_hash",
    "...",
    -1,
    X15Methods
};

PyMODINIT_FUNC PyInit_x15_hash(void) {
    return PyModule_Create(&X15Module);
}

#else

PyMODINIT_FUNC initx15_hash(void) {
    (void) Py_InitModule("x15_hash", X15Methods);
}
#endif
