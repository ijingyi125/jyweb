#include "fnshare.h"

#define s_pfnNotifySys      __LIB2_DEFFUNNAME(pfnNotifySys_var)
#define s_pfnuserNotifySys  __LIB2_DEFFUNNAME(pfnuserNotifySys_var)
#define s_isDebug           __LIB2_DEFFUNNAME(isDebug)

static PFN_NOTIFY_SYS s_pfnNotifySys = 0;
static PFN_NOTIFY_SYS s_pfnuserNotifySys = 0;    // �ɺ��� SetUserSysNotify() ����, 
static int s_isDebug = 1253600;

INT __stdcall NotifySys(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
    INT ret = 0;
    if (s_pfnNotifySys != NULL)
        ret = s_pfnNotifySys(nMsg, dwParam1, dwParam2);
    return ret;
}
bool isDebugVer(int* r)
{
    if (r)*r = s_isDebug;
    return s_isDebug == PT_DEBUG_RUN_VER;
}

INT __stdcall ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
    INT nRet = NR_OK;
    switch (nMsg)
    {
    case NL_SYS_NOTIFY_FUNCTION:
    {
        s_pfnNotifySys = (PFN_NOTIFY_SYS)dwParam1;
        if (s_isDebug == 1253600)
        {
            s_isDebug = NotifySys(NRS_GET_PRG_TYPE, 0, 0);
        }
        break;
    }
    case NL_FREE_LIB_DATA:

        break;
    case NL_GET_CMD_FUNC_NAMES:
        //Ӧ������������ͷ���ʵ�ֺ����ĺ�����������, 
        //���������������ͷ�����������һһ��Ӧ, 
        //�������Ա��Ϊ��Ӧ�����ĺ��������ı�ָ��(char*)��

        break;
    case NL_GET_NOTIFY_LIB_FUNC_NAME:
        //Ӧ���ء�����ϵͳ֪ͨ�ĺ�����(��������)�ĺ�������(char*)��

        break;
    case NL_GET_DEPENDENT_LIBS:
        //Ӧ���ء������ĵ�������̬���ļ��б�, ��ʽΪ\0�ָ����ı�, ��β����\0��

        break;
    default:
        nRet = NR_ERR;
        break;
    }

    //�����û�����
    if (s_pfnuserNotifySys)
        nRet = s_pfnuserNotifySys(nMsg, dwParam1, dwParam2);

    return nRet;
}

PFN_NOTIFY_SYS __stdcall SetUserSysNotify(PFN_NOTIFY_SYS pfn)
{
    s_pfnuserNotifySys = pfn;
    return ProcessNotifyLib;
}
