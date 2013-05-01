/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Server Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CNetwork.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

class CNetwork : public CPacketManager
{
private:
	static CNetwork * m_sInstance;

	unsigned short m_usPort;
	unsigned int m_uiMaxPlayers;
	
	RakNet::RakPeerInterface * m_pRakPeer;
public:
	CNetwork(unsigned int uiMaxPlayers, unsigned short usPort);
	~CNetwork();

	void pulse();

	static void PacketHandle(ePacketId packetId, RakNet::BitStream * pBitStream, RakNet::Packet * pPacket);

	inline RakNet::RakPeerInterface* getRakPeer() { return m_pRakPeer; }

	static CNetwork& GetInstance() { return *m_sInstance; }
};