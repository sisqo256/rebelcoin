/**
  ____           _              _                  _              __  ____    ____    _      __  
 |  _ \    ___  | |__     ___  | |   ___    ___   (_)  _ __      / / |  _ \  | __ )  | |     \ \ 
 | |_) |  / _ \ | '_ \   / _ \ | |  / __|  / _ \  | | | '_ \    | |  | |_) | |  _ \  | |      | |
 |  _ <  |  __/ | |_) | |  __/ | | | (__  | (_) | | | | | | |   | |  |  _ <  | |_) | | |___   | |
 |_| \_\  \___| |_.__/   \___| |_|  \___|  \___/  |_| |_| |_|   | |  |_| \_\ |____/  |_____|  | |
                                                                 \_\                         /_/  
                                                                                             
*/


// Copyright (c) 2010 Satoshi Nakamoto
// Rebelcoin Developers - TylerAnderson T.A
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <rebelcoin.h>

#include <rebelcoinseeds.h>
#include <consensus/merkle.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>


#include "uint256.h"
#include "arith_uint256.h"
#include "hash.h"
#include "streams.h"
#include <time.h>



static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}


static CBlock CreateGenesisBlockMainNet(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Rebelcoin March 2023";
    const CScript genesisOutputScript = CScript() << ParseHex("0412dcd0f8f8046c15806553dedf852c389a05994580e002417750891842e131fac024e3c36cc525f054c834bced9d6fdb26caf79dc8a537a7dea40b4187684829") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

static CBlock CreateGenesisBlockTestNet(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Rebelcoin March 2023";
    const CScript genesisOutputScript = CScript() << ParseHex("0412dcd0f8f8046c15806553dedf852c389a05994580e002417750891842e131fac024e3c36cc525f054c834bced9d6fdb26caf79dc8a537a7dea40b4187684829") << OP_CHECKSIG;
//    const CScript genesisOutputScript = CScript() << ParseHex("04b9106474eae57736be77d6e22b6bb76d4325bddde7d1980b8c67bbf3f6b3890e446c7ae5aecfbecf988fa85b13fe4688b79e0989d21c0313f69f21e8265a1d88") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

static CBlock CreateGenesisBlockRegTest(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "Rebelcoin March 2023";
    const CScript genesisOutputScript = CScript() << ParseHex("04af02023278caa54988e0f05660f56c51417c3c28264fab95600a59c9062190e369be84ea52dc866da659cbd2d882f17276d95dc109c8f44543a49f7a8590b1d9") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}


/**
'##::::'##::::'###::::'####:'##::: ##:'##::: ##:'########:'########:
 ###::'###:::'## ##:::. ##:: ###:: ##: ###:: ##: ##.....::... ##..::
 ####'####::'##:. ##::: ##:: ####: ##: ####: ##: ##:::::::::: ##::::
 ## ### ##:'##:::. ##:: ##:: ## ## ##: ## ## ##: ######:::::: ##::::
 ##. #: ##: #########:: ##:: ##. ####: ##. ####: ##...::::::: ##::::
 ##:.:: ##: ##.... ##:: ##:: ##:. ###: ##:. ###: ##:::::::::: ##::::
 ##:::: ##: ##:::: ##:'####: ##::. ##: ##::. ##: ########:::: ##::::
..:::::..::..:::::..::....::..::::..::..::::..::........:::::..:::::
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 500000;
        consensus.BIP16Exception = uint256S("0x0000000081b58599cbb570ad943f068ee2c5a1754f52cf0f69b0b6a5c713be04");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0000000081b58599cbb570ad943f068ee2c5a1754f52cf0f69b0b6a5c713be04");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0; 
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 0.5 * 60;
        consensus.nPowTargetSpacing = 0.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowTRDHeight = 0;
        consensus.nRuleChangeActivationThreshold = 1800;
        consensus.nMinerConfirmationWindow = 2400;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");
        consensus.defaultAssumeValid = uint256S("0x0000000081b58599cbb570ad943f068ee2c5a1754f52cf0f69b0b6a5c713be04");

        pchMessageStart[0] = 0xa9;
        pchMessageStart[1] = 0xa9;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0xa9;
        nDefaultPort = 10505;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        genesis = CreateGenesisBlockMainNet(1679938055, 2618935687, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000000081b58599cbb570ad943f068ee2c5a1754f52cf0f69b0b6a5c713be04"));
        assert(genesis.hashMerkleRoot == uint256S("0xe2d0bd35c14e84ed1479e669122c688ec488c289960cd0e8bd3e5b4f6b1f36e7"));


        vSeeds.emplace_back("seed01.rebelcoin.io");
        vSeeds.emplace_back("seed02.rebelcoin.io");
        vSeeds.emplace_back("seed03.rebelcoin.io");
        vSeeds.emplace_back("seed04.rebelcoin.io");


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,60);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,61);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,181);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB9, 0x4F};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAC, 0xF8};

        bech32_hrp = "rebelcoin";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;

        checkpointData = {
            {
                { 0, uint256S("0x0000000081b58599cbb570ad943f068ee2c5a1754f52cf0f69b0b6a5c713be04")},
                { 1, uint256S("0x0032a0f16d47ce05379b2f7a265694a6ce90778fac2f7c72d627fe45fbca44e2")},
                { 16, uint256S("0x00d26fbce488af14c48c166f7725711b85cee215f57382dc654631ab31213752")},
                { 101, uint256S("0x000058b0fde93e973ad978a26644bf3a2e9bcd154408dbefded8dc1f0f73b2d4")},
                { 112, uint256S("0x00001f63d96adf05e7ea03e4141e857dfea25dfeeb0a3711ea5b61d40f75a3b8")},
                { 126, uint256S("0x00000ccc5cb547cbc333e65ac0be41a95d071666d37e817bbe8c20d9f3ff0f9e")},
            }
        };

        chainTxData = ChainTxData{ 1679947972, 128, 0.79012345};
    }
};


/**
'########:'########::'######::'########:'##::: ##:'########:'########:
... ##..:: ##.....::'##... ##:... ##..:: ###:: ##: ##.....::... ##..::
::: ##:::: ##::::::: ##:::..::::: ##:::: ####: ##: ##:::::::::: ##::::
::: ##:::: ######:::. ######::::: ##:::: ## ## ##: ######:::::: ##::::
::: ##:::: ##...:::::..... ##:::: ##:::: ##. ####: ##...::::::: ##::::
::: ##:::: ##:::::::'##::: ##:::: ##:::: ##:. ###: ##:::::::::: ##::::
::: ##:::: ########:. ######::::: ##:::: ##::. ##: ########:::: ##::::
:::..:::::........:::......::::::..:::::..::::..::........:::::..:::::
 */

class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 500000;
        consensus.BIP16Exception = uint256S("0x00000000935936283470323b9da38e8ea0f89c9e2c7be2a52fb593b8728dfc26");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00000000935936283470323b9da38e8ea0f89c9e2c7be2a52fb593b8728dfc26");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("00ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = .50 * 60;
        consensus.nPowTargetSpacing = .50 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 180;
        consensus.nMinerConfirmationWindow = 240;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000100010");
        consensus.defaultAssumeValid = uint256S("0x00000000935936283470323b9da38e8ea0f89c9e2c7be2a52fb593b8728dfc26");

        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xf1;
        pchMessageStart[2] = 0xf1;
        pchMessageStart[3] = 0xf1;
        nDefaultPort = 20505;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        genesis = CreateGenesisBlockTestNet(1679937866, 579284542, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000000935936283470323b9da38e8ea0f89c9e2c7be2a52fb593b8728dfc26"));
        assert(genesis.hashMerkleRoot == uint256S("0xe2d0bd35c14e84ed1479e669122c688ec488c289960cd0e8bd3e5b4f6b1f36e7"));

        vFixedSeeds.clear();
        vSeeds.clear();

      //  vSeeds.emplace_back("");


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,143);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x07, 0x45, 0x87, 0xCE};
        base58Prefixes[EXT_SECRET_KEY] = {0x07, 0x45, 0x84, 0x91};

        bech32_hrp = "trebelcoin";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;


        checkpointData = {
            {
                {0, uint256S("0x00000000935936283470323b9da38e8ea0f89c9e2c7be2a52fb593b8728dfc26")},
            }
        };

        chainTxData = ChainTxData{ 1679937866, 0, 0.00000};
    }
};


/**
'########::'########::'######:::'########:'########::'######::'########:
 ##.... ##: ##.....::'##... ##::... ##..:: ##.....::'##... ##:... ##..::
 ##:::: ##: ##::::::: ##:::..:::::: ##:::: ##::::::: ##:::..::::: ##::::
 ########:: ######::: ##::'####:::: ##:::: ######:::. ######::::: ##::::
 ##.. ##::: ##...:::: ##::: ##::::: ##:::: ##...:::::..... ##:::: ##::::
 ##::. ##:: ##::::::: ##::: ##::::: ##:::: ##:::::::'##::: ##:::: ##::::
 ##:::. ##: ########:. ######:::::: ##:::: ########:. ######::::: ##::::
..:::::..::........:::......:::::::..:::::........:::......::::::..:::::
 */

class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 0;
        consensus.BIP16Exception = uint256S("0x0a0a1359c3d96b399580bc669d824be29896915f4d09258c2d5ed4d966f7db6a");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x0a0a1359c3d96b399580bc669d824be29896915f4d09258c2d5ed4d966f7db6a");
        consensus.BIP65Height = 0;
        consensus.BIP66Height = 0;
        consensus.CSVHeight = 0;
        consensus.SegwitHeight = 0;
        consensus.MinBIP9WarningHeight = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 0.25 * 60;
        consensus.nPowTargetSpacing = 0.25 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;
        consensus.nMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000200020");
        consensus.defaultAssumeValid = uint256S("0x0a0a1359c3d96b399580bc669d824be29896915f4d09258c2d5ed4d966f7db6a");

        pchMessageStart[0] = 0xb0;
        pchMessageStart[1] = 0xb0;
        pchMessageStart[2] = 0xb0;
        pchMessageStart[3] = 0xb0;
        nDefaultPort = 30505;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        genesis = CreateGenesisBlockRegTest(1679937528, 2, 0x207fffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0a0a1359c3d96b399580bc669d824be29896915f4d09258c2d5ed4d966f7db6a"));
        assert(genesis.hashMerkleRoot == uint256S("0x6852220ebb4628aa1be5a82fe73e81334ffb75edcd37333f9e617f6a17be0457"));

        vFixedSeeds.clear();
        vSeeds.clear();

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;

        checkpointData = {
            {
                {0, uint256S("0x0a0a1359c3d96b399580bc669d824be29896915f4d09258c2d5ed4d966f7db6a")},
            }
        };

        chainTxData = ChainTxData{ 1679937528, 0, 0.00000};

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,122);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,133);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,123);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x89, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x81, 0x90};

        bech32_hrp = "rrebelcoin";
    }

    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (gArgs.IsArgSet("-segwitheight")) {
        int64_t height = gArgs.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}
