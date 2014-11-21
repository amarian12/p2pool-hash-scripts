from distutils.core import setup, Extension

cryptonite_hash_module = Extension('cryptonite_hash',
    sources = [
        'cryptonitemodule.cpp',
        'hash/sha2.cpp',
        'hash/sha2big.cpp',
        'hash/keccak.cpp',
        'hash/haval.cpp',
        'hash/tiger.cpp',
        'hash/whirlpool.cpp',
        'hash/ripemd.cpp',
    ],
    libraries = ['gmp'])

setup (name = 'cryptonite_hash',
    version = '1.0',
    ext_modules = [cryptonite_hash_module])
