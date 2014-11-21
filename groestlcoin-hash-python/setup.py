from distutils.core import setup, Extension

groestlcoin_hash_module = Extension('groestlcoin_hash', sources = ['groestlcoinmodule.c', 'groestl.c'])

setup (name = 'groestlcoin_hash',
       version = '1.0',
       ext_modules = [groestlcoin_hash_module])
