from distutils.core import setup, Extension

whirlcoin_hash_module = Extension('whirlcoin_hash', sources = ['whirlcoinmodule.c', 'whirlpool.c'])

setup (name = 'whirlcoin_hash',
       version = '1.0',
       ext_modules = [whirlcoin_hash_module])
