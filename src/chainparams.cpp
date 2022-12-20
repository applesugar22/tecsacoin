// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2018 The PIVX developers
// Copyright (c) 2018 The tecsacoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x0000070a164b5ead1045e7e64e61c0f175c039c1446ae19c21f96d4688891900"))
    (1, uint256("0x0000030adcdba3cbeb71c7bfa701336085e069069f17d0010cb85c72e7ffcfcd"))
    (2, uint256("0x0000035f8c756f74af413c3e259f78883579fb5e457bf3b529f914530d1d0cf0"))
    (7, uint256("0x000004d1e6e97b6bd5dced8e33016001f1b858fceb9342c41db2a72043b8890c"))
    (11, uint256("0x000006e222828e7f8d9af5d0a7ed123764a183af42e628ef8ef87a805df467bb"))
    (100, uint256("0x00000038a0bed73b10ec59ba7b9daa97c9928394600555b3854a83943692c30c"))
    (2277, uint256("0x000000fd4dfae8a136372bb44a0186a5078e8d4398cf4e69e8602926cc7873ee"))
    (4725, uint256("0x0000022465afff23afd999296f17d20d846d0b94660ccae643e0eb04656012d2"))
    (6286, uint256("0x000001a7c53b5f1481025bc1647b5d8b86d8fffe1b00fc5c8bdec3bb9226ac4e"))
    (8334, uint256("0x00000275054dc8f8a88c30e8e6b122daf63785c668572b9f10927afaed590464"))
    (20409, uint256("0x00000009c4465df90cde3d3f3f1ec7026a7c7a782fe1dc50a2ade5de4a199c0f"))
    (28994, uint256("0x00000370a29916975a4fccf5678c3c1d0096e690760d4d9a18038f1d87b723a5"))
    (31433, uint256("0x000000523b1c32bb4bc3588366262b53dbbc8319e80d35d40a9374109f7a6c43"))
    (70000, uint256("0x00000002587a284f1b74316736df3337255d02c2ff4397c6039ff4a6a74d37eb"))
    (75901, uint256("0x0000000d5a004c2713390eaaece5843c25f56914879f53978b8691bdbc4377ae"))
    (75930, uint256("0x0000002b2a65094f550734caeace913ee3923ecab7c426a24c81c99c070aa42a"));
    //700000:

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1671497701, // * UNIX timestamp of last checkpoint block
    75962,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1.000000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params(bool useModulusV1) const
{
    assert(this);
    static CBigNum bnHexModulus = 0;
    if (!bnHexModulus)
        bnHexModulus.SetHex(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsHex = libzerocoin::ZerocoinParams(bnHexModulus);
    static CBigNum bnDecModulus = 0;
    if (!bnDecModulus)
        bnDecModulus.SetDec(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParamsDec = libzerocoin::ZerocoinParams(bnDecModulus);

    if (useModulusV1)
        return &ZCParamsHex;

    return &ZCParamsDec;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xa2;
        pchMessageStart[2] = 0xdb;
        pchMessageStart[3] = 0xc1;
        vAlertPubKey = ParseHex("025208d9c58b8edb90e7eed266d2aed4b5d1c81a6668083a296bf37798acbdc9ba");
        nDefaultPort = 5817;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 8100; // 75%
        nRejectBlockOutdatedMajority = 10260; // 95%
        nToCheckBlockUpgradeMajority = 10800; // Approximate expected amount of blocks in 7 days (1440*7.5)
        nMinerThreads = 0;
        nTargetTimespan = 15 * 60; // 15 minutes
        nTargetSpacing = 64; // 64 seconds
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 250000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 999999999;
        nPOSStartBlock = 999999999;
        nMandatoryUpgradeBlock = 182750;
        nUpgradeBlockVersion = 8;                                   // Block headers must be this version after upgrade block
        nZerocoinStartHeight = 2100000000;                          // OFF
        //nZerocoinStartTime = 4000000000;
        nModifierUpdateBlock = -1;
        nBlockEnforceSerialRange = -1;                              // Enforce serial range starting this block
        nBlockRecalculateAccumulators = nZerocoinStartHeight + 10;  // Trigger a recalculation of accumulators
        nBlockFirstFraudulent = nZerocoinStartHeight;               // First block that bad serials emerged
        nBlockLastGoodCheckpoint = nZerocoinStartHeight;            // Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = -1;                              // Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0*COIN;                            // Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = nZerocoinStartHeight + 20;               // The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1525158000;                           // Sporks signed after (GMT): Tuesday, May 1, 2018 7:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1527811200;                            // Fully reject old spork key after (GMT): Friday, June 1, 2018 12:00:00 AM

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "tecsacoin is born";
        CMutableTransaction txNew;
        txNew.nVersion = 1;
        txNew.nTime = 1489479450;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CScriptNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        //txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c10e83b2703ccf322f7dbd62dd5855ac7c10bd055814ce121ba32607d573b8810c02c0582aed05b4deb9c4b77b26d92428c61256cd42774babea0a073b2ed0c9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1614192833;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2762182;

        uint256 hashTarget = uint256().SetCompact(genesis.nBits);

  /*while (true) {
            uint256 hash = genesis.GetHash();
            if (hash <= hashTarget) {
                // Found a solution
                printf("genesis block found\n   hash: %s\n target: %s\n   bits: %08x\n  nonce: %u\n", hash.ToString().c_str(), hashTarget.ToString().c_str(), genesis.nBits, genesis.nNonce);
                break;
            }
            genesis.nNonce += 1;
            if ((genesis.nNonce & 0x1ffff) == 0)
                printf("testing nonce: %u\n", genesis.nNonce);
        } */





        assert(genesis.GetHash() <= hashTarget);

        hashGenesisBlock = genesis.GetHash();
        //printf("Merkle hash main: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //printf("Block hash main: %s\n", hashGenesisBlock.ToString().c_str());
        assert(genesis.hashMerkleRoot == uint256("0x73f2a35f48cdd2ba80a19f6da9943ab5ecb80d703cc74212197eb005f800ea85"));
        assert(hashGenesisBlock == uint256("0x0000070a164b5ead1045e7e64e61c0f175c039c1446ae19c21f96d4688891900"));

     
		
	vSeeds.push_back(CDNSSeedData("1", "45.76.144.137"));
	vSeeds.push_back(CDNSSeedData("2", "45.32.113.173"));
	vSeeds.push_back(CDNSSeedData("3", "45.63.79.135"));

		

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 66);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 161);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xf9).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "025208d9c58b8edb90e7eed266d2aed4b5d1c81a6668083a296bf37798acbdc9ba";
        strSporkKeyOld = "025208d9c58b8edb90e7eed266d2aed4b5d1c81a6668083a296bf37798acbdc9ba";
        strObfuscationPoolDummyAddress = "Ebsz2mBcw5hb1vqnBx7TP6CSaWt8sqTiz5";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 10; //Block headers must be this version once zerocoin is active
        nZerocoinRequiredStakeDepth = 200; //The required confirmations for a zeca to be stakable

        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xe7;
        pchMessageStart[1] = 0xe3;
        pchMessageStart[2] = 0xe2;
        pchMessageStart[3] = 0xe1;
        vAlertPubKey = ParseHex("025208d9c58b8edb90e7eed266d2aed4b5d1c81a6668083a296bf37798acbdc9ba");
        nDefaultPort = 15817;
        bnProofOfWorkLimit = ~uint256(0) >> 16;
        nEnforceBlockUpgradeMajority = 4320; // 75%
        nRejectBlockOutdatedMajority = 5472; // 95%
        nToCheckBlockUpgradeMajority = 5760; // 4 days
        nMinerThreads = 0;
        nTargetTimespan = 10 * 60; // 10 minutes
        nTargetSpacing = 48; // 48 seconds
        nLastPOWBlock = 2100000000;
        nPOSStartBlock = 50;
        nMaturity = 10;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = -1; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 2100000000;
        //nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = -1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = nZerocoinStartHeight + 10; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = nZerocoinStartHeight; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = nZerocoinStartHeight; //Last valid accumulator checkpoint
        nBlockEnforceInvalidUTXO = -1; //Start enforcing the invalid UTXO's
        nInvalidAmountFiltered = 0; //Amount of invalid coins filtered through exchanges, that should be considered valid
        nBlockZerocoinV2 = nZerocoinStartHeight + 20; //!> The block that zerocoin v2 becomes active
        nEnforceNewSporkKey = 1521604800; //!> Sporks signed after Wednesday, March 21, 2018 4:00:00 AM GMT must use the new spork key
        nRejectOldSporkKey = 1522454400; //!> Reject old spork key after Saturday, March 31, 2018 12:00:00 AM GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1612138687;
        genesis.nBits = bnProofOfWorkLimit.GetCompact(); //0x1f00ffff;
        genesis.nNonce = 729280;

        uint256 hashTarget = uint256().SetCompact(genesis.nBits);


        assert(genesis.GetHash() <= hashTarget);

        hashGenesisBlock = genesis.GetHash();
        //printf("Merkle hash test: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //printf("Block hash test: %s\n", hashGenesisBlock.ToString().c_str());
        assert(genesis.hashMerkleRoot == uint256("0x73f2a35f48cdd2ba80a19f6da9943ab5ecb80d703cc74212197eb005f800ea85"));
        assert(hashGenesisBlock == uint256("0x0000993389bc0635e94332e97216eb7e330ee7ba1ba3dd7fd6397ff2e90ab51c"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 92);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 41);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 220);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "025208d9c58b8edb90e7eed266d2aed4b5d1c81a6668083a296bf37798acbdc9ba";
        strSporkKeyOld = "025208d9c58b8edb90e7eed266d2aed4b5d1c81a6668083a296bf37798acbdc9ba";
        strObfuscationPoolDummyAddress = "eNdw2pzf2rirEmCfYGgUQdxJSo7ue6JyLK";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nDefaultPort = 51479;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 10 * 60; // 10 minutes
        nTargetSpacing = 48; // 48 seconds
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = bnProofOfWorkLimit.GetCompact(); //0x207fffff;
        genesis.nNonce = 116383;

        uint256 hashTarget = uint256().SetCompact(genesis.nBits);
 
        assert(genesis.GetHash() <= hashTarget);

        hashGenesisBlock = genesis.GetHash();
        //printf("Merkle hash reg: %s\n", genesis.hashMerkleRoot.ToString().c_str());
        //printf("Block hash reg: %s\n", hashGenesisBlock.ToString().c_str());
        assert(genesis.hashMerkleRoot == uint256("0x73f2a35f48cdd2ba80a19f6da9943ab5ecb80d703cc74212197eb005f800ea85"));
        assert(hashGenesisBlock == uint256("0x25ae6f11cf08520f278316838752fd45f05e0aa03e564b27a32ee9f7c57e55d4"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}