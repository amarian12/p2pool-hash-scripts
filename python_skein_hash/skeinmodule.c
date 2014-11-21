#include <Python.h>
#include "skeinhash.h"

static PyObject *skein_gethash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
    PyStringObject *input;
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

    skein_hash( (const char *)PyString_AsString((PyObject*) input), 
                (size_t)PyString_Size((PyObject*) input), 
                output);

    Py_DECREF(input);
    value = Py_BuildValue("s#", output, 32);
    PyMem_Free(output);
    return value;
}

static PyMethodDef SkeinMethods[] = {
    { "getPoWHash", skein_gethash, METH_VARARGS, "Returns a proof of work hash using skein and sha256" },
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initskeinhash(void) {
    (void) Py_InitModule("skeinhash", SkeinMethods);
}
