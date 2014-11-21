from distutils.core import setup, Extension

dcrypt_hash_module = Extension('dcrypt_hash', sources = ['dcryptmodule.c', 'dcrypt.c', 'dcrypt_sha256.c'])

setup (name = 'dcrypt_hash',
       version = '1.0',
       ext_modules = [dcrypt_hash_module])
