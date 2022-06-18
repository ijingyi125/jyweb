#include "wke_version.h"
#include "wke_typedef.h"
#include "wke/MbE.h"

HINSTANCE g_hInst = 0;
EXTERN_C INT WINAPI wke_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2);



#ifndef __E_STATIC_LIB

//TODO dll������ڵ�
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch ( ul_reason_for_call )
    {
    case DLL_PROCESS_ATTACH:    // ��һ�α�����,LoadLibrary���ؾʹ���
        g_hInst = hModule;
        break;
    case DLL_PROCESS_DETACH:    // DLL���ͷ�
        break;
    case DLL_THREAD_ATTACH:     // �߳�ӳ��
        break;
    case DLL_THREAD_DETACH:     // �߳�ж��
        break;
    }
    return TRUE;
}

// ��������������ʵ�ֵĺ�����ַ
#define WKE_DEF_CMD_PTR(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    WKE_NAME(_index, _szEgName),

static PFN_EXECUTE_CMD g_CmdsFunc_web[] =
{
    WKE_DEF(WKE_DEF_CMD_PTR)
};


//TODO ������֧�ֿ�ӿ��������Ͷ���
static LIB_INFO s_libInfo =
{
    /*m_dwLibFormatVer*/        LIB_FORMAT_VER, // ���ʽ��, Ӧ�õ���LIB_FORMAT_VER
    /*m_szGuid*/                "{6EC0A773-ABA1-49F4-AFD2-977EA30C0D4E}", // ��Ӧ�ڱ����ΨһGUID��, ����ΪNULL���, ������а汾�˴���Ӧ��ͬ
    /*m_nMajorVersion*/         WKE_MAJORVERSION, // ��������汾��, �������0
    /*m_nMinorVersion*/         WKE_MINORVERSION, // ����Ĵΰ汾��
    /*m_nBuildNumber*/          WKE_BUILDVERSION, // �����汾��, ����Դ˰汾�����κδ���

    /*m_nRqSysMajorVer*/        3, // ����Ҫ��������ϵͳ�����汾��
    /*m_nRqSysMinorVer*/        0, // ����Ҫ��������ϵͳ�Ĵΰ汾��
    /*m_nRqSysKrnlLibMajorVer*/ 3, // ����Ҫ��ϵͳ����֧�ֿ�����汾��
    /*m_nRqSysKrnlLibMinorVer*/ 0, // ����Ҫ��ϵͳ����֧�ֿ�Ĵΰ汾��

    /*m_szName*/                "����Web�����", // ����, ����ΪNULL���
    /*m_nLanguage*/             __GBK_LANG_VER, // ����֧�ֵ�����
    /*m_szExplain*/             "����Web�����֧�ֿ�(miniblink�ں�)����֧�ֿ�Ϊ�������ṩ��wke����������������������ֱ�ӵ��á�\r\n    ��֧�ֿ���ȫ���\r\n"
                                "    ��֧�ֿ�Ŀǰ���ڲ��԰档�����Ҫ��ʽ�棬�뿴��https://bbs.125.la/thread-14410959-1-1.html", // ����ϸ����

    /*m_dwState*/               _LIB_OS(OS_ALL), // _LIB_OS() | LBS_ ��ͷ����, ����ǲ��,������� LBS_IDE_PLUGIN
    /*m_szAuthor*/              "�������׿Ƽ����޹�˾", // ����
    /*m_szZipCode*/             "515500", // �ʱ�
    /*m_szAddress*/             "�㶫ʡ�����нҶ��������", // ��ַ
    /*m_szPhoto*/               "0663-3422125", // ��ϵ�绰
    /*m_szFax*/                 "11903273", // ����
    /*m_szEmail*/               "800073686@b.qq.com ", // ����
    /*m_szHomePage*/            "http://bbs.125.la/ ", // ��ҳ
    /*m_szOther*/               "���԰淴�������� \r\n          ��Ⱥ��ֱ��@��Ŀ��006�ظ���\r\n          ��Ⱥ: ����\r\n          ��Ⱥ��746829283", // ������Ϣ

    /*m_nDataTypeCount*/        g_DataType_wke_global_var_count, // �������Զ����������͵���Ŀ
    /*m_pDataType*/             g_DataType_wke_global_var, // ���������е��Զ�����������


    /*m_nCategoryCount*/        2, // ȫ�����������Ŀ, ��Ϊ0
    /*m_szzCategory*/           "0000����web�����\0"
                                "0000����ת��\0"
                                "\0", // ȫ�����������Ŀ, ��Ϊ0

    /*m_nCmdCount*/             g_cmdInfo_wke_global_var_count, // �������ṩ����������(ȫ�������������)����Ŀ, ��Ϊ0
    /*m_pBeginCmdInfo*/         g_cmdInfo_wke_global_var, // �������ṩ����������

    /*m_pCmdsFunc*/             g_CmdsFunc_web, // ָ��ÿ�������ʵ�ִ����׵�ַ, ��ΪNULL

    /*m_pfnRunAddInFn*/         NULL, // ��ΪNULL,������IDEϵͳ��Ӹ�������, ���ṩ���ܻᱻ�Զ���ӵ�IDE�ġ����ߡ��˵���
                                            // �й�AddIn���ܵ�˵��, �����ַ���˵��һ�����ܡ���һ��Ϊ��������
                                            // (����һ��20�ַ�, ���ϣ�����г�ʼλ�ö������Զ����뵽���߲˵�, ��
                                            // ����Ӧ����@��ʼ, ��ʱ����յ�ֵΪ -(nAddInFnIndex + 1) �ĵ���֪ͨ), 
                                            // �ڶ���Ϊ������ϸ����(����һ��60�ַ�), ����������մ�������
    /*m_szzAddInFnInfo*/        NULL, // ������ϸ����(����һ��60�ַ�), ����������մ�����

    /*m_pfnNotify*/             wke_ProcessNotifyLib, // ����ΪNULL,��������ͨѶ���ӳ���

    /*m_pfnSuperTemplate*/      NULL, // ģ�� ��ΪNULL
                                            //  �й�SuperTemplate��˵��, �����ַ���˵��һ��SuperTemplate��
                                            //  ��һ��ΪSuperTemplate����(����һ��30�ַ�), �ڶ���Ϊ��ϸ����(����), 
                                            //  ����������մ�������
    /*m_szzSuperTemplateInfo*/  NULL, // ģ�� ��ΪNULL


    /*m_nLibConstCount*/        g_ConstInfo_wke_global_var_count, // ����Ԥ�ȶ�������г�������
    /*m_pLibConst*/             g_ConstInfo_wke_global_var, // ����Ԥ�ȶ�������г���

    /*m_szzDependFiles*/        NULL // ��ΪNULL, ����������������Ҫ����������֧���ļ�
};




EXTERN_C _declspec(dllexport) PLIB_INFO WINAPI GetNewInf()
{
    head_dtType_Webkit(g_DataType_wke_global_var[4]);   // ����web����� ��Ҫ���ṹ
    head_dtType_NewWnd(g_DataType_wke_global_var[9]);   // ��������������Ҫ���ṹ


    return &s_libInfo;
}



// ���������Ծ�̬������Ҫ��������, �����ʵ�ֹ��ܵĺ�����, ��̬���������������ֵ���, �����Ի�ʹ��������������ȥ���þ�̬��
#define WKE_DEF_CMDNAME_STR(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    (DWORD) WKE_NAME_STR(_index, _szEgName), 

// ������, �������̬����ʹ��
static DWORD g_cmdNames[] =
{
    WKE_DEF(WKE_DEF_CMDNAME_STR)
};

#endif


//TODO ��������ͨѶ���ӳ���
EXTERN_C INT WINAPI wke_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
    static BOOL tmp = FALSE;
    int nRet = NR_OK;

    switch ( nMsg )
    {
#ifndef __E_STATIC_LIB
    case NL_GET_CMD_FUNC_NAMES:
        return (INT)g_cmdNames;
    case NL_GET_NOTIFY_LIB_FUNC_NAME:
        return (INT)"wke_ProcessNotifyLib";
    case NL_GET_DEPENDENT_LIBS:
        return (INT)"\0\0\0";
#endif

    // ��֪��֪ͨϵͳ�õĺ���ָ��,��װ��֧�ֿ�ǰ֪ͨ,�����ж��,��֪ͨ��ֵӦ�ø���ǰ����֪ͨ��ֵ,���Է���ֵ
    // ��ɽ��˺���ָ���¼�����Ա�����Ҫʱʹ����֪ͨ��Ϣ��ϵͳ
    // dwParam1: (PFN_NOTIFY_SYS)
    case NL_SYS_NOTIFY_FUNCTION:
    {
        ProcessNotifyLib(nMsg, dwParam1, dwParam2);
        if ( !g_hInst )
            g_hInst = GetModuleHandleW(0);  //  Ϊ0�Ļ��Ǿ���û��dllmain����

        break;
    }
    case NL_FREE_LIB_DATA:      //IDEȡ��ѡ�л��߿⼴���ͷ�
    case NL_UNLOAD_FROM_IDE:
    {
        //����ִֻ��һ��
        tmp = TRUE;
        MbE::wkeUnInit_wke();
        return (INT)NULL;
    }
    default:
        nRet = NR_ERR;
        break;
    }
    return nRet;
}
