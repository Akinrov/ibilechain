// Copyright (c) 2016 The Bitcoin Core developers
// Copyright (c) 2021-2022 The Ibilechain Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_WALLET_TEST_FIXTURE_H
#define BITCOIN_WALLET_TEST_FIXTURE_H

#include "test/test_ibilechain.h"

/** Testing setup and teardown for wallet.
 */
struct WalletTestingSetup: public TestingSetup {
    WalletTestingSetup();
    ~WalletTestingSetup();
};

#endif

