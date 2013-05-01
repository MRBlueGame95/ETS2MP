/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Client Core
 * Licence     : See LICENSE in the top level directory
 * File		   : CChat.h
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#pragma once

#define CHAT_LINES 10

struct sChatMessage
{
	char szMessage[256];
	unsigned long ulColor;
};

class CChat
{
private:
	static CChat * m_sInstance;

	IDirect3DDevice9 * m_pDevice;
	ID3DXFont * m_pFont;

	char m_szPrefix[10];

	sChatMessage m_pChatMessages[CHAT_LINES];

	char m_szInput[256];

	bool m_bInput;
public:
	CChat(IDirect3DDevice9 * pDevice);
	~CChat();

	void onLost();
	void onReset();
	void onRender();

	void output(const char * szMessage, ...);
	void output(unsigned long ulColor, const char * szMessage, ...);

	inline void setPrefix(char *szPrefix) { strcpy(m_szPrefix, szPrefix); };

	bool inputHandler(unsigned int uMsg, DWORD dwChar);

	static CChat& GetInstance() { return *m_sInstance; }
};