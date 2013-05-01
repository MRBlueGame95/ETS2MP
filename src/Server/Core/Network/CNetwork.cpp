/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Server Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CNetwork.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

CNetwork * CNetwork::m_sInstance = 0;

CNetwork::CNetwork(unsigned int uiMaxPlayers, unsigned short usPort)
	: m_usPort(usPort),
	  m_uiMaxPlayers(uiMaxPlayers),
	  m_pRakPeer(0)
{
	// Build CNetwork instance
	m_sInstance = this;
	
	// Get RakPeer instance
	m_pRakPeer = RakNet::RakPeerInterface::GetInstance();

	// Startup RakPeer
	m_pRakPeer->Startup(m_uiMaxPlayers, &RakNet::SocketDescriptor(m_usPort, 0), 1);

	// Set max incomming connections
	m_pRakPeer->SetMaximumIncomingConnections(m_uiMaxPlayers);

	// Set timeout interval
	m_pRakPeer->SetTimeoutTime(3000, RakNet::UNASSIGNED_SYSTEM_ADDRESS);

	// String compressor init
	RakNet::StringCompressor::AddReference();
	
	// Set packet manager rakpeer
	setRakPeer(m_pRakPeer);

	// Set packet manager handler
	setPacketHandle(PacketHandle);
}

CNetwork::~CNetwork()
{

}

void CNetwork::pulse()
{
	RakNet::Packet * pPacket = 0;

	while(pPacket = m_pRakPeer->Receive())
	{
		switch(pPacket->data[0])
		{
		case ID_NEW_INCOMING_CONNECTION:
			{
				printf("[net] New incomming connection from %s\n", pPacket->systemAddress.ToString(true,':'));
			} break;
		case ID_PACKET_MANAGER:
			{
				this->parsePacket(pPacket);
			} break;
		}
		m_pRakPeer->DeallocatePacket(pPacket);
	}
}

void CNetwork::PacketHandle(ePacketId packetId, RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	switch(packetId)
	{
	case ID_PACKET_JOIN:
		{
			char szNickName[24];
			RakNet::StringCompressor::Instance()->DecodeString(szNickName, 24, pBitStream);

			printf("[net] Player %s connected\n", szNickName);

			RakNet::BitStream bsData;

			int iHour = 12;
			int iMinute = 00;
			int iWeather = 0;

			// Serialize world
			bsData.Write(iHour);
			bsData.Write(iMinute);
			bsData.Write(iWeather);


			CNetwork::GetInstance().send(ID_PACKET_JOIN_REPLY, &bsData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, pPacket->systemAddress, false);
		} break;
	case ID_CHAT_MESSAGE:
		{
			char szMessage[256] = { 0 };
			char szReadBuffer[256] = { 0 };

			RakNet::StringCompressor::Instance()->DecodeString(szReadBuffer, sizeof(szReadBuffer), pBitStream);
			
			sprintf(szMessage,"Player %d: %s", pPacket->systemAddress.systemIndex, szReadBuffer);

			printf("[chat] %s\n", szMessage);

			RakNet::BitStream bsData;	
			RakNet::StringCompressor::Instance()->EncodeString(szMessage, sizeof(szMessage), &bsData);
		
			CNetwork::GetInstance().send(ID_CHAT_MESSAGE, &bsData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
		} break; 
	}
}