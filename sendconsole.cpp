#include <QtCore>
#include <Windows.h>
#include <tchar.h>
#include <cstdio>
#include <string>
#include <iostream>
#include "sendconsole.h"

DWORD SendScanCode(WORD scan, BOOL up)
{
    INPUT inp = {0};
    inp.type = INPUT_KEYBOARD;
    inp.ki.wScan = scan;
    inp.ki.dwFlags = KEYEVENTF_SCANCODE | (up ? KEYEVENTF_KEYUP : 0);
    return SendInput(1, &inp, sizeof(inp)) ? NO_ERROR : GetLastError();
}

DWORD SendVirtualKey(UINT vk, BOOL up)

{
    UINT scan = MapVirtualKey(vk, MAPVK_VK_TO_VSC);

    return scan ? SendScanCode(scan, up) : ERROR_NO_UNICODE_TRANSLATION;

}


void sendConsoleCommand(const std::string &comm)
{
 // std::cout<<comm;
  HWND hwnd = FindWindow(0, _T(L"Dota 2"));
  SetForegroundWindow(hwnd);
 // SendMessage(hwnd, WM_ACTIVATE, WA_ACTIVE, 0);
  // SendMessage(hwnd, WM_SETFOCUS, 0, 0);

 SendVirtualKey(0x0D,false); // enter
 Sleep(150);
 for(int i = 0; i != comm.length(); ++i)
  {
      SendMessage(hwnd, WM_CHAR, comm[i], 0);
  }

  SendVirtualKey(0x0D,false); // enter

//  SendMessage(hwnd, WM_ACTIVATE, WA_ACTIVE, 0);
 //  SendMessage(hwnd, WM_SETFOCUS, 0, 0);
}

