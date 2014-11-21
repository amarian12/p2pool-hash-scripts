from distutils.core import setup, Extension

groestl_hash_module = Extension('groestl_hash',
                               sources = ['groestlmodule.c',
                                          'groestl.c',
										  'sph/groestl.c',
										  'sph/sha2.c'],
                               include_dirs=['.', './sph'])


setup (name = 'groestl_hashs',
       version = '0.1',
       description = 'Bindings for Groestl Used by MyriadCoin',
       ext_modules = [groestl_hash_module])
