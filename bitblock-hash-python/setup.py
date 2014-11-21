from distutils.core import setup, Extension

bitblock_hash_module = Extension('bitblock_hash',
    sources = [
        'bitblockmodule.c',
        'bitblock.c',
        'sha3/blake.c',
        'sha3/bmw.c',
        'sha3/groestl.c',
        'sha3/jh.c',
        'sha3/keccak.c',
        'sha3/skein.c',
        'sha3/cubehash.c',
        'sha3/echo.c',
        'sha3/luffa.c',
        'sha3/simd.c',
        'sha3/hamsi.c',
        'sha3/hamsi_helper.c',
        'sha3/fugue.c',
        'sha3/shavite.c',
        'sha3/shabal.c',
        'sha3/whirlpool.c'
    ],
   include_dirs=['.', './sha3'])

setup (name = 'bitblock_hash',
   version = '1.0',
   description = 'Bindings for proof of work used by BitBlock',
   ext_modules = [bitblock_hash_module])
