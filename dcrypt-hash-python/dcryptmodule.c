#include <Python.h>

#include "dcrypt.h"

static PyObject *dcrypt_gethash(PyObject *self, PyObject *args)
{
    uint32_t *output;
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
    dcrypt((char *)PyBytes_AsString((PyObject*) input), 80, NULL, output);
#else
    dcrypt((char *)PyString_AsString((PyObject*) input), 80, NULL, output);
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

static PyMethodDef DcryptMethods[] = {
    { "getHash", dcrypt_gethash, METH_VARARGS, "Returns the dcrypt hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef DcryptModule = {
    PyModuleDef_HEAD_INIT,
    "dcrypt_hash",
    "...",
    -1,
    DcryptMethods
};

PyMODINIT_FUNC PyInit_dcrypt_hash(void) {
    return PyModule_Create(&DcryptModule);
}

#else

PyMODINIT_FUNC initdcrypt_hash(void) {
    (void) Py_InitModule("dcrypt_hash", DcryptMethods);
}
#endif
