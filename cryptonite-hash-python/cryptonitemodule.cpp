#include <Python.h>

#include "uint256.h"

#include "hash/sph_sha2.h"
#include "hash/sph_keccak.h"
#include "hash/sph_haval.h"
#include "hash/sph_tiger.h"
#include "hash/sph_whirlpool.h"
#include "hash/sph_ripemd.h"

template<typename T1>
inline uint256 Hash7(const T1 pbegin, const T1 pend)
{
    sph_sha256_context       ctx_sha256;
    sph_sha512_context       ctx_sha512;
    sph_keccak512_context    ctx_keccak;
    sph_whirlpool_context    ctx_whirlpool;
    sph_haval256_5_context   ctx_haval;
    sph_tiger_context        ctx_tiger;
    sph_ripemd160_context    ctx_ripemd;
    static unsigned char pblank[1];

    uint512 hash[7];
    uint256 finalhash;
    for(int i=0; i < 7; i++)
	hash[i] = 0;

    const void* ptr = (pbegin == pend ? pblank : static_cast<const void*>(&pbegin[0]));
    size_t sz = (pend - pbegin) * sizeof(pbegin[0]);

    sph_sha256_init(&ctx_sha256);
    sph_sha256 (&ctx_sha256, ptr, sz);
    sph_sha256_close(&ctx_sha256, static_cast<void*>(&hash[0]));
    
    sph_sha512_init(&ctx_sha512);
    sph_sha512 (&ctx_sha512, ptr, sz);
    sph_sha512_close(&ctx_sha512, static_cast<void*>(&hash[1]));
    
    sph_keccak512_init(&ctx_keccak);
    sph_keccak512 (&ctx_keccak, ptr, sz);
    sph_keccak512_close(&ctx_keccak, static_cast<void*>(&hash[2]));

    sph_whirlpool_init(&ctx_whirlpool);
    sph_whirlpool (&ctx_whirlpool, ptr, sz);
    sph_whirlpool_close(&ctx_whirlpool, static_cast<void*>(&hash[3]));
    
    sph_haval256_5_init(&ctx_haval);
    sph_haval256_5 (&ctx_haval, ptr, sz);
    sph_haval256_5_close(&ctx_haval, static_cast<void*>(&hash[4]));

    sph_tiger_init(&ctx_tiger);
    sph_tiger (&ctx_tiger, ptr, sz);
    sph_tiger_close(&ctx_tiger, static_cast<void*>(&hash[5]));

    sph_ripemd160_init(&ctx_ripemd);
    sph_ripemd160 (&ctx_ripemd, ptr, sz);
    sph_ripemd160_close(&ctx_ripemd, static_cast<void*>(&hash[6]));

    mpz_t bns[7];

    //Take care of zeros and load gmp
    for(int i=0; i < 7; i++){
	if(hash[i]==0)
	    hash[i] = 1;
	mpz_init(bns[i]);
	mpz_set_uint512(bns[i],hash[i]);
    }
 
    mpz_t product;
    mpz_init(product);
    mpz_set_ui(product,1);
    for(int i=0; i < 7; i++){
	mpz_mul(product,product,bns[i]);
    }

    int bytes = mpz_sizeinbase(product, 256);
    char *data = (char*)malloc(bytes);
    mpz_export(data, NULL, -1, 1, 0, 0, product);

    //Free the memory
    for(int i=0; i < 7; i++){
	mpz_clear(bns[i]);
    }
    mpz_clear(product);

    sph_sha256_init(&ctx_sha256);
    sph_sha256 (&ctx_sha256, data,bytes);
    sph_sha256_close(&ctx_sha256, static_cast<void*>(&finalhash));

    free(data);

    return finalhash;
}

static void CryptoniteHash(const char *input, int length, char *output)
{
    uint256 hash = Hash7(input, input + length);

    memcpy(output, &hash, 32);
}

static PyObject *cryptonite_gethash(PyObject *self, PyObject *args)
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
    output = (char*)PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    CryptoniteHash((char *)PyBytes_AsString((PyObject*) input), length, output);
#else
    CryptoniteHash((char *)PyString_AsString((PyObject*) input), length, output);
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

static PyMethodDef CryptoniteMethods[] = {
    { "getHash", cryptonite_gethash, METH_VARARGS, "Returns the cryptonite hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef CryptoniteModule = {
    PyModuleDef_HEAD_INIT,
    "cryptonite_hash",
    "...",
    -1,
    CryptoniteMethods
};

PyMODINIT_FUNC PyInit_cryptonite_hash(void) {
    return PyModule_Create(&CryptoniteModule);
}

#else

PyMODINIT_FUNC initcryptonite_hash(void) {
    (void) Py_InitModule("cryptonite_hash", CryptoniteMethods);
}
#endif
