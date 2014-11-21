#include <Python.h>

#include "bitblock.h"

static PyObject *bitblock_getpowhash(PyObject *self, PyObject *args)
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
    bitblock_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    bitblock_hash((char *)PyString_AsString((PyObject*) input), output);
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

static PyMethodDef bitblockMethods[] = {
    { "getPoWHash", bitblock_getpowhash, METH_VARARGS, "Returns the proof of work hash using x13 hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef bitblockModule = {
    PyModuleDef_HEAD_INIT,
    "bitblock_hash",
    "...",
    -1,
    bitblockMethods
};

PyMODINIT_FUNC PyInit_bitblock_hash(void) {
    return PyModule_Create(&bitblockModule);
}

#else

PyMODINIT_FUNC initbitblock_hash(void) {
    (void) Py_InitModule("bitblock_hash", bitblockMethods);
}
#endif
