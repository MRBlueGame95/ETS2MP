/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : Shared\Network
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#include <RakPeerInterface.h>
#include <BitStream.h>
#include <MessageIdentifiers.h>

enum eMessageId
{
	ID_PACKET_MANAGER = (ID_USER_PACKET_ENUM+1)
};

enum ePacketId
{
	ID_PACKET_JOIN,
	ID_PACKET_JOIN_REPLY,
	ID_CHAT_MESSAGE
};

typedef void (*pfnPacketHandle)(ePacketId,RakNet::BitStream*,RakNet::Packet*);

class CPacketManager
{
private:
	RakNet::RakPeerInterface * m_pRakPeer;

	pfnPacketHandle m_pfnPacketHandle;
public:
	CPacketManager();
	~CPacketManager();

	void setRakPeer(RakNet::RakPeerInterface * pRakPeer);

	void setPacketHandle(pfnPacketHandle _pfnPacketHandle);

	bool send(ePacketId packetId, RakNet::BitStream *bitStream = 0, PacketPriority priority = LOW_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED,
		char orderingChannel = 0, const RakNet::AddressOrGUID systemIdentifier = RakNet::UNASSIGNED_SYSTEM_ADDRESS, bool broadcast = true, uint32_t forceReceiptNumber = -1);

	void parsePacket(RakNet::Packet * pPacket);
};