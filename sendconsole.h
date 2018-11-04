#ifndef SENDCONSOLE
#define SENDCONSOLE
#include <Windows.h>
#include <tchar.h>
#include <cstdio>
#include <string>

DWORD SendScanCode(WORD, BOOL);

DWORD SendVirtualKey(UINT, BOOL);

void sendConsoleCommand(const std::string &);


#endif // SENDCONSOLE

