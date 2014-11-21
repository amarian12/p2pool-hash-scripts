from distutils.core import setup, Extension

twehash_module = Extension('twehash',
    sources = ['twehashmodule.c', 'fugue.c', 'hamsi.c', 'panama.c', 'shavite.c'],
              include_dirs=['.'], extra_compile_args=['-O2'])

setup (name = 'twehash',
       version = '1.0',
       description = 'Bindings for Twecoin hash',
       ext_modules = [twehash_module])
