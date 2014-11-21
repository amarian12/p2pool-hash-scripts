from distutils.core import setup
from distutils.extension import Extension

setup(name="saffroncoin_subsidys",
    ext_modules=[
        Extension("saffroncoin_subsidy", ["saffroncoin_GetBlockBaseValue.cpp"],
        libraries = ["boost_python"])
    ])
