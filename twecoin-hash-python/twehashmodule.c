#include <Python.h>

#include <string.h>
#include <stdint.h>

#include "sph_fugue.h"
#include "sph_hamsi.h"
#include "sph_panama.h"
#include "sph_shavite.h"

void twehash(char* output, const char *input, uint32_t length)
{
    unsigned char hash[128];
    
    memset(hash, 0, 128);

    sph_fugue256_context ctx_fugue;
    sph_shavite256_context ctx_shavite;
    sph_hamsi256_context ctx_hamsi;
    sph_panama_context ctx_panama;
	  
    sph_fugue256_init(&ctx_fugue);
    sph_fugue256(&ctx_fugue, input, length);
    sph_fugue256_close(&ctx_fugue, hash);
    
    sph_shavite256_init(&ctx_shavite);
    sph_shavite256(&ctx_shavite, hash, 64);
    sph_shavite256_close(&ctx_shavite, hash + 64);
    
    sph_hamsi256_init(&ctx_hamsi);
    sph_hamsi256(&ctx_hamsi, hash + 64, 64);
    sph_hamsi256_close(&ctx_hamsi, hash);
    
    sph_panama_init(&ctx_panama);
    sph_panama(&ctx_panama, hash, 64);
    sph_panama_close(&ctx_panama, hash + 64);
    
    memcpy(output, hash + 64, 32);
}

static PyObject *twehash_gethash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
    PyStringObject *input;
    uint32_t length;
    if (!PyArg_ParseTuple(args, "Si", &input, &length))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);
    twehash(output, (char*)PyString_AsString((PyObject*)input), length);
    Py_DECREF(input);
    value = Py_BuildValue("s#", output, 32);
    PyMem_Free(output);
    return value;
}

static PyMethodDef TwehashMethods[] = {
    { "getHash", twehash_gethash, METH_VARARGS, "Returns the hash" },
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC inittwehash(void) {
    (void) Py_InitModule("twehash", TwehashMethods);
}
