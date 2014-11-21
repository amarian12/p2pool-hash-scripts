from distutils.core import setup, Extension

quark_hash_module = Extension('quark_hash',
                               sources = ['quarkmodule.c',
                                          'quark.c',
										  'sha3/blake.c',
										  'sha3/bmw.c',
										  'sha3/groestl.c',
										  'sha3/jh.c',
										  'sha3/keccak.c',
										  'sha3/skein.c'],
                               include_dirs=['.', './sha3'])

setup (name = 'quark_hashs',
       version = '1.0',
       description = 'Bindings for scrypt proof of work used by Quarkcoin',
       ext_modules = [quark_hash_module])
