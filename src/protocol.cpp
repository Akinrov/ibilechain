// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2017-2020 The PIVX developers
// Copyright (c) 2021-2022 The Ibilechain Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "protocol.h"

#include "util.h"
#include "utilstrencodings.h"

#ifndef WIN32
#include <arpa/inet.h>
#endif

namespace NetMsgType
{
const char* VERSION = "version";
const char* VERACK = "verack";
const char* ADDR = "addr";
const char* INV = "inv";
const char* GETDATA = "getdata";
const char* MERKLEBLOCK = "merkleblock";
const char* GETBLOCKS = "getblocks";
const char* GETHEADERS = "getheaders";
const char* TX = "tx";
const char* HEADERS = "headers";
const char* BLOCK = "block";
const char* GETADDR = "getaddr";
const char* MEMPOOL = "mempool";
const char* PING = "ping";
const char* PONG = "pong";
const char* ALERT = "alert";
const char* NOTFOUND = "notfound";
const char* FILTERLOAD = "filterload";
const char* FILTERADD = "filteradd";
const char* FILTERCLEAR = "filterclear";
const char* REJECT = "reject";
const char* SENDHEADERS = "sendheaders";
const char* IX = "ix";
const char* IXLOCKVOTE = "txlvote";
const char* SPORK = "spork";
const char* GETSPORKS = "getsporks";
const char* MNBROADCAST = "mnb";
const char* MNPING = "mnp";
const char* MNWINNER = "mnw";
const char* GETMNWINNERS = "mnget";
const char* BUDGETPROPOSAL = "mprop";
const char* BUDGETVOTE = "mvote";
const char* BUDGETVOTESYNC = "mnvs";
const char* FINALBUDGET = "fbs";
const char* FINALBUDGETVOTE = "fbvote";
const char* SYNCSTATUSCOUNT = "ssc";
const char* GETMNLIST = "dseg";
}; // namespace NetMsgType

static const char* ppszTypeName[] = {
    "ERROR", // Should never occur
    NetMsgType::TX,
    NetMsgType::BLOCK,
    "filtered block", // Should never occur
    NetMsgType::IX,
    NetMsgType::IXLOCKVOTE,
    NetMsgType::SPORK,
    NetMsgType::GETSPORKS,
    NetMsgType::MNBROADCAST,
    NetMsgType::MNPING,
    NetMsgType::MNWINNER,
    NetMsgType::GETMNWINNERS,
    NetMsgType::GETMNLIST,
    NetMsgType::BUDGETPROPOSAL,
    NetMsgType::BUDGETVOTE,
    NetMsgType::FINALBUDGET,
    NetMsgType::FINALBUDGETVOTE
};

/** All known message types. Keep this in the same order as the list of
 * messages above and in protocol.h.
 */
const static std::string allNetMessageTypes[] = {
    NetMsgType::VERSION,
    NetMsgType::VERACK,
    NetMsgType::ADDR,
    NetMsgType::INV,
    NetMsgType::GETDATA,
    NetMsgType::MERKLEBLOCK,
    NetMsgType::GETBLOCKS,
    NetMsgType::GETHEADERS,
    NetMsgType::TX,
    NetMsgType::HEADERS,
    NetMsgType::BLOCK,
    NetMsgType::GETADDR,
    NetMsgType::MEMPOOL,
    NetMsgType::PING,
    NetMsgType::PONG,
    NetMsgType::ALERT,
    NetMsgType::NOTFOUND,
    NetMsgType::FILTERLOAD,
    NetMsgType::FILTERADD,
    NetMsgType::FILTERCLEAR,
    NetMsgType::REJECT,
    NetMsgType::SENDHEADERS,
    NetMsgType::IX,
    NetMsgType::IXLOCKVOTE,
    NetMsgType::SPORK,
    NetMsgType::GETSPORKS,
    NetMsgType::MNBROADCAST,
    NetMsgType::MNPING,
    NetMsgType::MNWINNER,
    NetMsgType::GETMNWINNERS,
    NetMsgType::GETMNLIST,
    NetMsgType::BUDGETPROPOSAL,
    NetMsgType::BUDGETVOTE,
    NetMsgType::BUDGETVOTESYNC,
    NetMsgType::FINALBUDGET,
    NetMsgType::FINALBUDGETVOTE,
    NetMsgType::SYNCSTATUSCOUNT
};
const static std::vector<std::string> allNetMessageTypesVec(allNetMessageTypes, allNetMessageTypes + ARRAYLEN(allNetMessageTypes));

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    nMessageSize = -1;
    memset(pchChecksum, 0, CHECKSUM_SIZE);
}

CMessageHeader::CMessageHeader(const MessageStartChars& pchMessageStartIn, const char* pszCommand, unsigned int nMessageSizeIn)
{
    memcpy(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE);
    memset(pchCommand, 0, sizeof(pchCommand));
    strncpy(pchCommand, pszCommand, COMMAND_SIZE);
    nMessageSize = nMessageSizeIn;
    memset(pchChecksum, 0, CHECKSUM_SIZE);
}

std::string CMessageHeader::GetCommand() const
{
    return std::string(pchCommand, pchCommand + strnlen(pchCommand, COMMAND_SIZE));
}

bool CMessageHeader::IsValid(const MessageStartChars& pchMessageStartIn) const
{
    // Check start string
    if (memcmp(pchMessageStart, pchMessageStartIn, MESSAGE_START_SIZE) != 0)
        return false;

    // Check the command string for errors
    for (const char* p1 = pchCommand; p1 < pchCommand + COMMAND_SIZE; p1++) {
        if (*p1 == 0) {
            // Must be all zeros after the first zero
            for (; p1 < pchCommand + COMMAND_SIZE; p1++)
                if (*p1 != 0)
                    return false;
        } else if (*p1 < ' ' || *p1 > 0x7E)
            return false;
    }

    // Message size
    if (nMessageSize > MAX_SIZE) {
        LogPrintf("CMessageHeader::IsValid() : (%s, %u bytes) nMessageSize > MAX_SIZE\n", GetCommand(), nMessageSize);
        return false;
    }

    return true;
}


CAddress::CAddress() : CService()
{
    Init();
}

CAddress::CAddress(CService ipIn, ServiceFlags nServicesIn) : CService(ipIn)
{
    Init();
    nServices = nServicesIn;
}

void CAddress::Init()
{
    nServices = NODE_NONE;
    nTime = 100000000;
}

CInv::CInv()
{
    type = 0;
    hash.SetNull();
}

CInv::CInv(int typeIn, const uint256& hashIn)
{
    type = typeIn;
    hash = hashIn;
}

CInv::CInv(const std::string& strType, const uint256& hashIn)
{
    unsigned int i;
    for (i = 1; i < ARRAYLEN(ppszTypeName); i++) {
        if (strType == ppszTypeName[i]) {
            type = i;
            break;
        }
    }
    if (i == ARRAYLEN(ppszTypeName))
        LogPrint(BCLog::NET, "CInv::CInv(string, uint256) : unknown type '%s'", strType);
    hash = hashIn;
}

bool operator<(const CInv& a, const CInv& b)
{
    return (a.type < b.type || (a.type == b.type && a.hash < b.hash));
}

bool CInv::IsKnownType() const
{
    return (type >= 1 && type < (int)ARRAYLEN(ppszTypeName));
}

bool CInv::IsMasterNodeType() const{
     return (type >= 6);
}

const char* CInv::GetCommand() const
{
    if (!IsKnownType()) {
        LogPrint(BCLog::NET, "CInv::GetCommand() : type=%d unknown type", type);
        return "UNKNOWN";
    }

    return ppszTypeName[type];
}

std::string CInv::ToString() const
{
    return strprintf("%s %s", GetCommand(), hash.ToString());
}

const std::vector<std::string>& getAllNetMessageTypes()
{
    return allNetMessageTypesVec;
}
