/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CChat.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include <Includes.h>

CChat * CChat::m_sInstance = 0;

CChat::CChat(IDirect3DDevice9 * pDevice)
	: m_pDevice(pDevice),
	  m_pFont(0),
	  m_bInput(false)
{
	// Setup instance
	m_sInstance = this;

	// Setup all lines
	for(int i = 0; i < CHAT_LINES; i++)
	{
		m_pChatMessages[i].szMessage[0] = '\0';
		m_pChatMessages[i].ulColor = 0xFFFFFFFF;
	}

	// Set default input prefix
	setPrefix("Say: ");

	// Setup font
	D3DXCreateFont(m_pDevice, 15, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &m_pFont);

	// Clear input
	m_szInput[0] = '\0';
}

CChat::~CChat()
{
	if(m_pFont)
	{
		m_pFont->Release();
		m_pFont = 0;
	}
}

void CChat::onLost()
{
	if(m_pFont) m_pFont->OnLostDevice();
}

void CChat::onReset()
{
	if(m_pFont) m_pFont->OnResetDevice();
}

void CChat::onRender()
{
	if(m_pFont)
	{
		float fX = 10.f;
		float fY = 10.f;
		
		RECT SizeRct = { 0 };
		m_pFont->DrawText(0, "W", -1, &SizeRct, DT_CALCRECT, 0xFFFFFFFF);

		RECT rct = { 0 };
		for(int i = CHAT_LINES-1; i >= 0; i--)
		{
			SetRect(&rct, (int)(fX+1.f), (int)fY, 0, 0);
			m_pFont->DrawText(0, m_pChatMessages[i].szMessage, -1, &rct, DT_NOCLIP, 0xFF000000);
			SetRect(&rct, (int)(fX-1.f), (int)fY, 0, 0);
			m_pFont->DrawText(0, m_pChatMessages[i].szMessage, -1, &rct, DT_NOCLIP, 0xFF000000);
			SetRect(&rct, (int)fX, (int)(fY+1.f), 0, 0);
			m_pFont->DrawText(0, m_pChatMessages[i].szMessage, -1, &rct, DT_NOCLIP, 0xFF000000);
			SetRect(&rct, (int)fX, (int)(fY-1.f), 0, 0);
			m_pFont->DrawText(0, m_pChatMessages[i].szMessage, -1, &rct, DT_NOCLIP, 0xFF000000);

			SetRect(&rct, (int)fX, (int)fY, 0, 0);
			m_pFont->DrawText(0, m_pChatMessages[i].szMessage, -1, &rct, DT_NOCLIP, m_pChatMessages[i].ulColor);
			
			fY += ( (float)(SizeRct.bottom-SizeRct.top) ) + 0.8f;
		}

		if(m_bInput)
		{
			char szInput[267]; // +10 for prefix, +1 for _ symbol
			sprintf(szInput, "%s%s_", m_szPrefix, m_szInput);

			SetRect(&rct, (int)(fX+1.f), (int)fY, 0, 0);
			m_pFont->DrawText(0, szInput, -1, &rct, DT_NOCLIP, 0xFF000000);
			SetRect(&rct, (int)(fX-1.f), (int)fY, 0, 0);
			m_pFont->DrawText(0, szInput, -1, &rct, DT_NOCLIP, 0xFF000000);
			SetRect(&rct, (int)fX, (int)(fY+1.f), 0, 0);
			m_pFont->DrawText(0, szInput, -1, &rct, DT_NOCLIP, 0xFF000000);
			SetRect(&rct, (int)fX, (int)(fY-1.f), 0, 0);
			m_pFont->DrawText(0, szInput, -1, &rct, DT_NOCLIP, 0xFF000000);

			SetRect(&rct, (int)fX, (int)fY, 0, 0);
			m_pFont->DrawText(0, szInput, -1, &rct, DT_NOCLIP, 0xFFFFFFFF);
		}
	}
}

void CChat::output(const char * szMessage, ...)
{
	char szBuffer[256];
	va_list vArgs;
	va_start(vArgs, szMessage);
	vsprintf(szBuffer,szMessage,vArgs);
	va_end(vArgs);

	output(0xFFC0C0C0, szBuffer);
}

void CChat::output(unsigned long ulColor, const char * szMessage, ...)
{
	char szBuffer[256];
	va_list vArgs;
	va_start(vArgs, szMessage);
	vsprintf(szBuffer,szMessage,vArgs);
	va_end(vArgs);

	for(int i = CHAT_LINES-1; i > 0; i--)
	{
		strcpy(m_pChatMessages[i].szMessage, m_pChatMessages[i-1].szMessage);
		m_pChatMessages[i].ulColor = m_pChatMessages[i-1].ulColor;
	}

	strcpy(m_pChatMessages[0].szMessage, szBuffer);
	m_pChatMessages[0].ulColor =  ulColor;
}

bool CChat::inputHandler(unsigned int uMsg, DWORD dwChar)
{
	switch(uMsg)
	{
	case WM_CHAR:
		{
			if(m_bInput)
			{
				if(dwChar >= ' ')
				{
					if(strlen(m_szInput) < 256)
					{
						sprintf(m_szInput, "%s%c", m_szInput, dwChar);
						return true;
					}
				}
			} else {
				if( (dwChar == 't') || (dwChar == 'T') )
				{
					m_bInput = true;
					CClient::GetInstance().setControls(false);
					return true;
				}
			}
		} break;
	case WM_KEYDOWN:
		{
			if( (dwChar == VK_BACK) && m_bInput)
			{
				size_t iPos = strlen(m_szInput)-1;
				if(iPos >= 0) {
					m_szInput[iPos] = '\0';
				}
				return true;
			}
		} break;
	case WM_KEYUP:
		{
			if( (dwChar == VK_RETURN) && m_bInput )
			{
				// Send message to the server
				RakNet::BitStream bsData;
				RakNet::StringCompressor::Instance()->EncodeString(m_szInput, 256, &bsData);
				CNetwork::GetInstance().send(ID_CHAT_MESSAGE, &bsData);

				// Disable input
				m_bInput = false;

				// Cleanup input
				m_szInput[0] = '\0';

				// Revert game input
				CClient::GetInstance().setControls(true);
				return true;
			} 
			else if( (dwChar == VK_ESCAPE) && m_bInput) 
			{				
				// Disable input
				m_bInput = false;

				// Cleanup input
				m_szInput[0] = '\0';

				// Revert game input
				CClient::GetInstance().setControls(true);
				return true;
			}
		} break;
	}
	return false;
}