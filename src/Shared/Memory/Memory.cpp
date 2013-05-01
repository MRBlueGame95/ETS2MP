/**************************************************************
 *
 * Solution    : Euro Truck Simulator 2 Multiplayer
 * Project     : Shared\Memory
 * Licence     : See LICENSE in the top level directory
 * File		   : Memory.cpp
 * Developers  : RootKiller <rootkiller.programmer@gmail.com>
 *
 ***************************************************************/
#include "Memory.h"

void Memory::UnprotectSegment(const char * szName)
{
	BYTE * pImageBase = (BYTE *)GetModuleHandle(NULL);
	PIMAGE_DOS_HEADER   pDosHeader = (PIMAGE_DOS_HEADER)pImageBase;
	PIMAGE_NT_HEADERS   pNtHeader  = (PIMAGE_NT_HEADERS)(pImageBase + pDosHeader->e_lfanew);
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHeader);

	for(int iSection = 0; iSection < pNtHeader->FileHeader.NumberOfSections; iSection++, pSection++)
	{
		char * pszSectionName = (char *)pSection->Name;
		if(!strcmp(pszSectionName, szName))
			Memory::Unprotect((DWORD)(pImageBase + pSection->VirtualAddress), ((pSection->Misc.VirtualSize + 4095) & ~4095));
	}
}

DWORD Memory::Unprotect(DWORD dwAddress, int iSize)
{
	DWORD dwOldProt = NULL;
	VirtualProtect((void *)dwAddress, iSize, PAGE_EXECUTE_READWRITE, &dwOldProt);
	return dwOldProt;
}

void Memory::Reprotect(DWORD dwAddress, int iSize, DWORD dwOldProtect)
{
	DWORD dwProt;
	VirtualProtect((void *)dwAddress, iSize, dwOldProtect, &dwProt);
}

void Memory::JumpHook(DWORD dwFrom, DWORD dwTo)
{
#define X86OPT 0xE9
	// Unprotect an memory
	Memory::Unprotect(dwFrom,5);

	// Define an bytes array started at dwForm address
	BYTE * baPatch = (BYTE*)dwFrom;

	// Set operation offset
	*baPatch = X86OPT;

	// Install hook
	*(DWORD *)(baPatch + 0x1) = (dwTo - (dwFrom + 5));
#undef X86OPT
}

void Memory::CallHook(DWORD dwFrom, DWORD dwTo)
{
#define X86OPT 0xE8
	// Unprotect an memory
	Memory::Unprotect(dwFrom,5);

	// Define an bytes array started at dwForm address
	BYTE * baPatch = (BYTE*)dwFrom;

	// Set operation offset
	*baPatch = X86OPT;

	// Install hook
	*(DWORD *)(baPatch + 0x1) = (dwTo - (dwFrom + 5));
#undef X86OPT
}

void Memory::ReturnHook(DWORD dwAddress)
{
#define X86OPT 0xC3
	// Unprotect an memory address
	Unprotect(dwAddress, 1);

	// Install return hook
	*(BYTE *)dwAddress = X86OPT;
#undef X86OPT
}

void Memory::NopHook(DWORD dwAddress, int iSize)
{
#define X86OPT 0xC3
	// Unprotect an memory address
	Unprotect(dwAddress, iSize);

	// Install nop hook
	memset((void *)dwAddress, X86OPT, iSize);
#undef X86OPT
}