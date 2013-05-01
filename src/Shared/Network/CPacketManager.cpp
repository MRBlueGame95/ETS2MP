/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : Shared\Network
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include "CPacketManager.h"

CPacketManager::CPacketManager() 
	: m_pRakPeer(0),
	  m_pfnPacketHandle(0)
{

}

CPacketManager::~CPacketManager()
{

}

void CPacketManager::setRakPeer(RakNet::RakPeerInterface * pRakPeer)
{
	m_pRakPeer = pRakPeer;
}

void CPacketManager::setPacketHandle(pfnPacketHandle _pfnPacketHandle)
{
	m_pfnPacketHandle = _pfnPacketHandle;
}

bool CPacketManager::send(ePacketId packetId, RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability,
						 char orderingChannel, const RakNet::AddressOrGUID systemIdentifier, bool broadcast, uint32_t forceReceiptNumber)
{
	if(!m_pRakPeer)
		return false;

	RakNet::BitStream bsPacket;
	bsPacket.Write((RakNet::MessageID)ID_PACKET_MANAGER);
	bsPacket.Write((RakNet::MessageID)packetId);
	if(bitStream)
	{
		bitStream->ResetReadPointer();
		bsPacket.AlignWriteToByteBoundary();
		bsPacket.Write(bitStream);
	}

	m_pRakPeer->Send(&bsPacket, priority, reliability, orderingChannel, systemIdentifier, broadcast, forceReceiptNumber);
	return true;
}

void CPacketManager::parsePacket(RakNet::Packet * pPacket)
{
	if(!m_pfnPacketHandle)
	{
		// If we doesn't have any packet handle we doesn't need to parse packet because we can't handle it ;)
		printf("[net:warning] No packet handler set (%s, %d)\n", __FILE__, __LINE__);
		return;
	}
		
	if(!pPacket)
	{
		// Invalid packet
		printf("[net:error] Invalid packet (%s, %d)\n", __FILE__, __LINE__);
		return;
	}

	RakNet::BitStream bsData((unsigned char *)pPacket->data, pPacket->length, false);
	
	bsData.IgnoreBytes(1);//Ignore first message (ID_PACKET_MANAGER)
	RakNet::MessageID PacketId;
	bsData.Read(PacketId);

	bsData.AlignReadToByteBoundary();
	m_pfnPacketHandle((ePacketId) PacketId, &bsData, pPacket);
}