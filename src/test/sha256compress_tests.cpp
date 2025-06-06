#include "test/test_ibilechain.h"
#include "crypto/sha256.h"
#include "uint256.h"

#include <stdexcept>

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(sha256compress_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(compression)
{
    {
        unsigned char preimage[64] = {};
        CSHA256 hasher;
        hasher.Write(&preimage[0], 64);

        uint256 digest;

        hasher.FinalizeNoPadding(digest.begin());

        BOOST_CHECK_MESSAGE(digest == uint256S("d8a93718eaf9feba4362d2c091d4e58ccabe9f779957336269b4b917be9856da"),
                            digest.GetHex());
    }

    {
        unsigned char preimage[63] = {};
        CSHA256 hasher;
        hasher.Write(&preimage[0], 63);
        uint256 digest;
        BOOST_CHECK_THROW(hasher.FinalizeNoPadding(digest.begin()), std::length_error);
    }
}

BOOST_AUTO_TEST_SUITE_END()
