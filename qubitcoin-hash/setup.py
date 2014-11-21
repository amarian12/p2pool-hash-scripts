from distutils.core import setup, Extension

qubit_hash_module = Extension('qubit_hash',
                               sources = ['qubitmodule.c',
                                          'qubit.c',
										  'sph/aes_helper.c',
										  'sph/cubehash.c',
										  'sph/luffa.c',
										  'sph/shavite.c',
										  'sph/simd.c',
										  'sph/echo.c'],
                               include_dirs=['.', './sph'])

setup (name = 'qubit_hashs',
       version = '1.0',
       description = 'Bindings for scrypt proof of work used by Qubitcoin',
       ext_modules = [qubit_hash_module])
