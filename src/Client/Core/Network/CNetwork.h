/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CNetwork.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

enum eClientNetworkState
{
	WAITING_FOR_CONNECT,
	CONNECTED
};

class CNetwork : public CPacketManager
{
private:
	static CNetwork * m_sInstance;

	unsigned short m_usPort;
	char m_szHost[32];
	
	RakNet::RakPeerInterface * m_pRakPeer;

	eClientNetworkState m_eNetState;
public:
	CNetwork();
	~CNetwork();

	void pulse();
	
	bool connect(const char * szHost, unsigned short usPort);
	bool reconnect();

	static void PacketHandle(ePacketId packetId, RakNet::BitStream * pBitStream, RakNet::Packet * pPacket);

	static CNetwork& GetInstance() { return *m_sInstance; }
};