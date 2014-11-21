from distutils.core import Extension, setup

magi_hash_module = Extension('magi_hash',
                               sources = ['m7m_module.c',
                                          'm7m.c',
                                          'magimath.c',
                                          'hash/keccak.c',
                                          'hash/haval.c',
                                          'hash/ripemd.c',
                                          'hash/sha2.c',
                                          'hash/sha2big.c',
                                          'hash/tiger.c',
                                          'hash/whirlpool.c'
                                          ],
                               include_dirs=['.','./hash'], 
                               libraries=['gmp'])

setup (name = 'magi_hash',
       version = '1.0',
       description = 'Bindings for scrypt proof of work used by Coin Magi',
       ext_modules = [magi_hash_module])
