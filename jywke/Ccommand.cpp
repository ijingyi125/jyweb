#include "Ccommand.h"

Ccommand::Ccommand()
{
    m_cmdIndex = NULL;
    m_cmdInfo = NULL;
    cmdLen = cmdArgLen = NULL;
}
Ccommand::~Ccommand()
{
}

BOOL Ccommand::AddCmd(LPSTR szName, LPSTR szEgName, LPSTR szExplain, SHORT shtCategory, WORD wState, DWORD dtRetValType, WORD wReserved, SHORT shtUserLevel)
{
    //CMD_INFO a;

    cmdLen++;
    return NULL;
}

BOOL Ccommand::AddArg()
{
    cmdArgLen++;
    return 0;
}

CMD_INFO* Ccommand::GetCmdPtr(int& dwLen)
{
    if (dwLen)dwLen = cmdLen;
    return 0;
}

CMD_INFO* Ccommand::GetCmdArgPtr(int& dwLen)
{
    if (dwLen)dwLen = cmdArgLen;
    return 0;
}