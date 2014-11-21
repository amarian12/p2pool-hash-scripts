#include <Python.h>

#include "sph_whirlpool.h"

static void WhirlCoinHash(const char *input, int length, char *output)
{
    uint32_t hashA[16], hashB[16];	
    sph_whirlpool1_context ctx_whirlpool;
    
    sph_whirlpool1_init(&ctx_whirlpool);
    sph_whirlpool1(&ctx_whirlpool, input, length); 
    sph_whirlpool1_close(&ctx_whirlpool, hashA); 
    
    sph_whirlpool1_init(&ctx_whirlpool);
    sph_whirlpool1(&ctx_whirlpool, hashA, 64); 
    sph_whirlpool1_close(&ctx_whirlpool, hashB); 
    
    sph_whirlpool1_init(&ctx_whirlpool);
    sph_whirlpool1(&ctx_whirlpool, hashB, 64); 
    sph_whirlpool1_close(&ctx_whirlpool, hashA); 
    
    sph_whirlpool1_init(&ctx_whirlpool);
    sph_whirlpool1(&ctx_whirlpool, hashA, 64); 
    sph_whirlpool1_close(&ctx_whirlpool, hashB); 
    
    memcpy(output, hashB, 32);
}

static PyObject *whirlcoin_gethash(PyObject *self, PyObject *args)
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
    WhirlCoinHash((char *)PyBytes_AsString((PyObject*) input), length, output);
#else
    WhirlCoinHash((char *)PyString_AsString((PyObject*) input), length, output);
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

static PyMethodDef WhirlcoinMethods[] = {
    { "getHash", whirlcoin_gethash, METH_VARARGS, "Returns the whirlcoin hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef WhirlcoinModule = {
    PyModuleDef_HEAD_INIT,
    "whirlcoin_hash",
    "...",
    -1,
    WhirlcoinMethods
};

PyMODINIT_FUNC PyInit_whirlcoin_hash(void) {
    return PyModule_Create(&WhirlcoinModule);
}

#else

PyMODINIT_FUNC initwhirlcoin_hash(void) {
    (void) Py_InitModule("whirlcoin_hash", WhirlcoinMethods);
}
#endif
