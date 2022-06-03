// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//
// Main network
//
class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x11;
        pchMessageStart[1] = 0x0f;
        pchMessageStart[2] = 0xaa;
        pchMessageStart[3] = 0x9b;
        vAlertPubKey = ParseHex("01efae5aa489f123756b659c91a56897eba2efaacb6a192acdbef7894465f81f85d131aadfef3be6145678454852a2d08c6314bba5ca3cbe5616262da3b1a6fffa");
        nDefaultPort = 20375; // peer
        nRPCPort = 20425; // rpc
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 22);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 22);

        const char* pszTimestamp = "Terra Luna 2.0 Price Up 46-percent As Bitcoin and Ethereum Show Significant Growth | Kyle Portman | May 31, 2022";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].nValue = 1 * COIN;
        vout[0].SetEmpty();
        CTransaction txNew(1, 1653998400, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1653998400;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 2339364;

        /** Genesis Block MainNet */
        /*
            Hashed MainNet Genesis Block Output
            block.hashMerkleRoot == df4d4879833ce1c2323ba8e17e2db4bbe7d1a2d49d9fed43f37ec1ca83217924
            block.nTime = 1653998400
            block.nNonce = 2339364
            block.GetHash = 000001460972e0995d45be390c1210af515965f100e96f719e16ef38e8a483a2
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000001460972e0995d45be390c1210af515965f100e96f719e16ef38e8a483a2"));
        assert(genesis.hashMerkleRoot == uint256("0xdf4d4879833ce1c2323ba8e17e2db4bbe7d1a2d49d9fed43f37ec1ca83217924"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,25);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,45);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,40);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,50);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        // vSeeds.push_back(CDNSSeedData("node0",  "000.000.000.000"));


        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nPoolMaxTransactions = 9;
        strMNenginePoolDummyAddress = "B5uY3piDFjPm43WGwhzwbmvLjNjL2irWL1";
        strDevOpsAddress = "B5e98EUcc3i2xStSZTxkgVuPhsoi9gaRoa";
        nEndPoWBlock = 0x7fffffff;
        nStartPoSBlock = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0x1f;
        pchMessageStart[2] = 0xab;
        pchMessageStart[3] = 0x9c;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 14);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 14);
        vAlertPubKey = ParseHex("21efae5aa489f996be6b659c91a518567ba2efaacb6acdefcdbef7894452f81f85d131aadfef3be6145678454852a2d08c6314bba5ca3cbe5616262da3b1a6aaab");
        nDefaultPort = 20099; // 
        nRPCPort = 20198; //
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime  = 1653998600;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2395;

        /** Genesis Block TestNet */
        /*
            Hashed TestNet Genesis Block Output
            block.hashMerkleRoot == df4d4879833ce1c2323ba8e17e2db4bbe7d1a2d49d9fed43f37ec1ca83217924
            block.nTime = 1653998600
            block.nNonce = 2395
            block.GetHash = 0000dfcb457205a669e77272822128a4d7f7a321664fdf6db14f49abf0193e20
        */

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x0000dfcb457205a669e77272822128a4d7f7a321664fdf6db14f49abf0193e20"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,26); // B
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,46); //
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,41); //
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,51); //
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        nEndPoWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0x12;
        pchMessageStart[1] = 0x1c;
        pchMessageStart[2] = 0xab;
        pchMessageStart[3] = 0x9c;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1653999400;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 20009; //
        strDataDir = "regtest";

        /** Genesis Block RegNet */
        /*
            Hashed RegNet Genesis Block Output
            block.hashMerkleRoot == df4d4879833ce1c2323ba8e17e2db4bbe7d1a2d49d9fed43f37ec1ca83217924
            block.nTime = 1653999400
            block.nNonce = 8
            block.GetHash = 848c809a98010b3fb102d4ab3c9c46980905731584d76484e7da9622916e5aa2
        */

        assert(hashGenesisBlock == uint256("0x848c809a98010b3fb102d4ab3c9c46980905731584d76484e7da9622916e5aa2"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
