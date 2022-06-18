#pragma once
#include "pch.h"
class Ccommand
{
public:
    Ccommand();
    ~Ccommand();
    BOOL AddCmd(LPSTR szName, LPSTR szEgName, LPSTR szExplain, SHORT shtCategory, WORD wState, DWORD dtRetValType, WORD wReserved, SHORT shtUserLevel);
    BOOL AddArg();
    CMD_INFO* GetCmdPtr(int& dwLen);
    CMD_INFO* GetCmdArgPtr(int& dwLen);
protected:

private:
    int* m_cmdIndex, cmdLen, cmdArgLen;
    CMD_INFO* m_cmdInfo;
};
