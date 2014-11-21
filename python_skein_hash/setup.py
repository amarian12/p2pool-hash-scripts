from distutils.core import setup, Extension

skeinhash_module = Extension('skeinhash',
                               sources = ['skeinmodule.c',
                                          'skeinhash.c',
                                          'skein.c',
                                          'sha2.c'],
                               include_dirs=['.'],
                               extra_compile_args=['-O1'])

setup (name = 'skeinhash',
       version = '1.0',
       description = 'Bindings for skein proof of work modified for Myriadcoin Skein',
       ext_modules = [skeinhash_module])
