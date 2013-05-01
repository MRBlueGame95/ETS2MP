/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CNetwork.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

CNetwork * CNetwork::m_sInstance = 0;

CNetwork::CNetwork()
	: m_pRakPeer(0),
	  m_eNetState(WAITING_FOR_CONNECT)
{
	// Build CNetwork instance
	m_sInstance = this;

	// Get RakPeer instance
	m_pRakPeer = RakNet::RakPeerInterface::GetInstance();

	// Startup RakPeer
	m_pRakPeer->Startup(1, &RakNet::SocketDescriptor(), 1);
	
	// String compressor init
	RakNet::StringCompressor::AddReference();

	// Set packet manager rakpeer
	setRakPeer(m_pRakPeer);

	// Set packet manager handler
	setPacketHandle(PacketHandle);

	// Setup default data
	m_usPort = 8365;
	strcpy(m_szHost, "127.0.0.1");

	// Start network manager
	CLogger::Printf("[net] Network manager started");
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
		case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				m_eNetState = CONNECTED;

				// We're connecting so send packet to get server data like current hour etc
				RakNet::BitStream bsData;
				
				char * szPlayerName = "Developer";
				RakNet::StringCompressor::Instance()->EncodeString(szPlayerName,24,&bsData);

				this->send(ID_PACKET_JOIN, &bsData);
			} break;
		case ID_CONNECTION_LOST:
			{
				CChat::GetInstance().output(0xFF600000,"Lost connection! Reconnecting..");
				reconnect();
			} break;
		case ID_CONNECTION_ATTEMPT_FAILED:
			{
				CChat::GetInstance().output(0xFF600000,"Cannot connect to host! Reconnecting..");
				reconnect();
			} break;
		case ID_PACKET_MANAGER:
			{
				parsePacket(pPacket);
			} break;
		}
		m_pRakPeer->DeallocatePacket(pPacket);
	}
}

bool CNetwork::connect(const char * szHost, unsigned short usPort)
{
	strcpy(m_szHost, szHost);
	m_usPort = usPort;

	RakNet::ConnectionAttemptResult res = m_pRakPeer->Connect(m_szHost, m_usPort, 0, 0);
	return (res == RakNet::CONNECTION_ATTEMPT_STARTED);
}

bool CNetwork::reconnect()
{
	RakNet::ConnectionAttemptResult res = m_pRakPeer->Connect(m_szHost, m_usPort, 0, 0);
	return (res == RakNet::CONNECTION_ATTEMPT_STARTED);
}

void CNetwork::PacketHandle(ePacketId packetId, RakNet::BitStream * pBitStream, RakNet::Packet * pPacket)
{
	switch(packetId)
	{
	case ID_PACKET_JOIN_REPLY:
		{
			int Hour, Minute, Weather;
			pBitStream->Read(Hour);
			pBitStream->Read(Minute);
			pBitStream->Read(Weather);

			CChat::GetInstance().output(0xFF575757,"Connected! (Hour: %d, Minute: %d, Weathed ID: %d)", Hour, Minute, Weather);

#ifdef NO_131_COMPILATION
			GameETS2 * pGame = *(GameETS2**)CGameOffsets::VAR_GamePtr;

			Hour = (Hour * 60) % 0x5A0;
			//unsigned long ulTime = pGame->economy->time = ( Hour + 64 * (24 - pGame->economy->time%0x5A0/0x3C) - pGame->economy->time%0x3C) % 0x5A0;
			unsigned long ulTime = pGame->economy->time = (Hour + 60 * (24 - pGame->economy->time  % 0x5A0u / 0x3C) - pGame->economy->time % 0x3Cu) % 0x5A0;;

			EconomyETS2 * pEconomyETS = pGame->economy;
			DWORD FUNC_Unk = 0x41C550;
			_asm
			{
				//mov xmm0, 0
				mov eax, pEconomyETS
				push 3
				push ulTime
				call FUNC_Unk
				add esp, 8h
			}

			CConsole::Write("0x%p", *(DWORD*)pGame + 216);

			// Weather set

			DWORD dwPtr = *(DWORD*)0xA6B838;
			DWORD dwUnknown = *(DWORD*)(dwPtr + 2032); //It's can be WorldManager (I'm not sure!)

			*(DWORD *)(dwUnknown+5300) = Weather;
			*(DWORD *)(dwUnknown+5848) = ( Weather ? 0 : *(DWORD*)(0x98AC10) );
			*(DWORD *)(dwUnknown+5772) = 1;
			*(DWORD *)(dwUnknown+5768) = 0;

			DWORD FUNC_CWeatherManager__Unk = 0x463F40;
			_asm
			{
				mov ecx, dwUnknown
				call FUNC_CWeatherManager__Unk
			}
#endif
		} break;
	case ID_CHAT_MESSAGE:
		{
			char szMessage[256];
			RakNet::StringCompressor::Instance()->DecodeString(szMessage, sizeof(szMessage), pBitStream);

			CChat::GetInstance().output(szMessage);
		} break;
	}
}