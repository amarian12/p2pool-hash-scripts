from distutils.core import Extension, setup

ltc_scrypt_module = Extension('ltc_scrypt',
                               sources = ['m7m_module_ltc_scrypt.c',
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

setup (name = 'ltc_scrypt',
       version = '1.0',
       description = 'Bindings for scrypt proof of work used by Coin Magi',
       ext_modules = [ltc_scrypt_module])
