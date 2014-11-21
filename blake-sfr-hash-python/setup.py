from distutils.core import setup, Extension

blake_sfr_hash_module = Extension('blake_sfr_hash', sources = ['blake_sfr_module.c', 'blake.c'])

setup (name = 'blake_sfr_hash',
       version = '1.0',
       ext_modules = [blake_sfr_hash_module])
