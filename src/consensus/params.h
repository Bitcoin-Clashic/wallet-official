// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_PARAMS_H
#define BITCOIN_CONSENSUS_PARAMS_H

#include "uint256.h"

#include <map>
#include <string>

namespace Consensus {

enum DeploymentPos {
    DEPLOYMENT_TESTDUMMY,
    // Deployment of BIP68, BIP112, and BIP113.
    DEPLOYMENT_CSV,
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in
    // versionbits.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    int bit;
    /** Start MedianTime for version bits miner confirmation. Can be a date in
     * the past */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    int64_t nTimeout;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    int nSubsidyHalvingInterval;
    int nSubsidyHalvingIntervalOneMinute;
    // Need to factor adjustment for changing to 1-minute blocks in the middle
    // of halving interval so we end up with 21m coins
    int nSubsidyHalvingIntervalOneMinuteAdjustment;

    /** Block height and hash at which BIP34 becomes active */
    int BIP34Height;
    uint256 BIP34Hash;
    /** Block height at which BIP65 becomes active */
    int BIP65Height;
    /** Block height at which BIP66 becomes active */
    int BIP66Height;
    /** Block height at which UAHF kicks in */
    int uahfHeight;
    /** Block height at which OP_RETURN replay protection stops */
    int antiReplayOpReturnSunsetHeight;
    /** Committed OP_RETURN value for replay protection */
    std::vector<uint8_t> antiReplayOpReturnCommitment;
    /** Block height at which we changed consensus to 1-minute blocks */
    int oneMinuteBlockHeight;
    /** Block height at which we changed PoW to Blake2b */
    int powBlake2Height;
    /** Block height at which 0x21 protocol version no longer accepted */
    int plug0x21ExploitHeight;

    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks
     * in a retargeting period, (nPowTargetTimespan / nPowTargetSpacing) which
     * is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    /** Proof of work parameters */
    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetSpacingOneMinute;
    int64_t nPowTargetTimespan;
    int64_t DifficultyAdjustmentInterval() const {
        return nPowTargetTimespan / nPowTargetSpacing;
    }
    int64_t DifficultyAdjustmentIntervalOneMinute() const {
        return nPowTargetTimespan / nPowTargetSpacingOneMinute;
    }
    uint256 nMinimumChainWork;
    uint256 defaultAssumeValid;

    /** Activation time at which the core HF kicks in. */
    int64_t coreHardForkActivationTime;

    /** Enforce PROTOCOL_VERSION=80050, reject PROTOCOL_VERSION=80030. */
    int64_t enforceProtocolVersion80050Time;
};
} // namespace Consensus

#endif // BITCOIN_CONSENSUS_PARAMS_H
