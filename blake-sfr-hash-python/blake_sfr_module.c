#include <Python.h>

#include "sph_blake.h"

static void BlakeSfrHash(const char *input, int length, char *output)
{
    uint32_t hash[8];
    
    sph_blake256_context ctx_blake;

    sph_blake256_init(&ctx_blake);
    sph_blake256(&ctx_blake, input, length);
    sph_blake256_close(&ctx_blake, hash);
    
    memcpy(output, hash, 32);
}

static PyObject *blake_sfr_gethash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    int length;
    if (!PyArg_ParseTuple(args, "Si", &input, &length))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    BlakeSfrHash((char *)PyBytes_AsString((PyObject*) input), length, output);
#else
    BlakeSfrHash((char *)PyString_AsString((PyObject*) input), length, output);
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

static PyMethodDef BlakeSfrMethods[] = {
    { "getHash", blake_sfr_gethash, METH_VARARGS, "Returns the Saffroncoin blake256 hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef BlakeSfrModule = {
    PyModuleDef_HEAD_INIT,
    "blake_sfr_hash",
    "...",
    -1,
    BlakeSfrMethods
};

PyMODINIT_FUNC PyInit_blake_sfr_hash(void) {
    return PyModule_Create(&BlakeSfrModule);
}

#else

PyMODINIT_FUNC initblake_sfr_hash(void) {
    (void) Py_InitModule("blake_sfr_hash", BlakeSfrMethods);
}
#endif
