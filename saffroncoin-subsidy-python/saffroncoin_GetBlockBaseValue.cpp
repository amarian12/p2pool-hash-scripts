#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h> 

static const int64_t COIN = 100000000;

int64_t static GetBlockBaseValue(int nBits, int nHeight)
{

 int64_t nSubsidy = 72 * COIN;
 int64_t nMinSubsidy = 0.017 * COIN;


    // 1st 2 days bonus
    if(nHeight < 5761)     
    {
        nSubsidy *= 3;
    }


    // Mining phase: Subsidy is cut in half every SubsidyHalvingInterval
    nSubsidy >>= (nHeight / 524160);
    
    // Inflation phase: Subsidy reaches minimum subsidy
    // Network is rewarded for transaction processing with transaction fees and 
    // the inflationary subsidy
    if (nSubsidy < nMinSubsidy)
    {
        nSubsidy = nMinSubsidy;
    }

    return nSubsidy;

}


#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
using namespace boost::python;
 
BOOST_PYTHON_MODULE(saffroncoin_subsidy)
{
    def("GetBlockBaseValue", GetBlockBaseValue);
}

