#include <Python.h>

#include "m7m.h"

static PyObject *magi_getpowhash(PyObject *self, PyObject *args)
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
    m7magi_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    m7magi_hash((char *)PyString_AsString((PyObject*) input), output);
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

static PyMethodDef magiMethods[] = {
    { "getPoWHash", magi_getpowhash, METH_VARARGS, "Returns the proof of work hash using m7m" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef magiModule = {
    PyModuleDef_HEAD_INIT,
    "magi_hash",
    "...",
    -1,
    magiMethods
};

PyMODINIT_FUNC PyInit_magi_hash(void) {
    return PyModule_Create(&magiModule);
}

#else

PyMODINIT_FUNC initmagi_hash(void) {
    (void) Py_InitModule("magi_hash", magiMethods);
}
#endif