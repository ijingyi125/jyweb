#include "wke_webkit_header.h"
static wstr s_path;


INT WINAPI wke_PropNotifyReceiver_webkit(INT nMsg, DWORD dwParam1, DWORD dwParam2);
BOOL WINAPI wke_PropKetInfo_webkit(HUNIT hUnit, WORD wKey);


HUNIT WINAPI wke_ControlCreate_Webkit(
    LPBYTE pAllPropertyData,            //   ָ�򱾴��ڵ�Ԫ�������������ݣ��ɱ����ڵ�Ԫ��ITF_GET_PROPERTY_DATA�ӿڲ��������û��������ΪNULL��
    INT nAllPropertyDataSize,           //   �ṩpAllPropertyData��ָ�����ݵĳߴ磬���û����Ϊ0��
    DWORD dwStyle,                      //   Ԥ�����õĴ��ڷ��
    HWND hParentWnd,                    //   �����ھ����
    UINT uID,                           //   �ڸ������е�ID��
    HMENU hMenu,                        //   δʹ�á�
    INT x, INT y, INT cx, INT cy,       //   ָ��λ�ü��ߴ硣
    DWORD dwWinFormID, DWORD dwUnitID,  //   �����ڵ�Ԫ���ڴ��ڼ������ID������֪ͨ��ϵͳ��
    HWND hDesignWnd,					//   ���blInDesignModeΪ�棬��hDesignWnd�ṩ����ƴ��ڵĴ��ھ����
    BOOL blInDesignMode);  				//   ˵���Ƿ�������IDE�����Խ��п��ӻ���ƣ�����ʱΪ�١�

// ����Web�����  �µ������������
EXTERN_C PFN_INTERFACE WINAPI wke_GetInterface_webkit(INT nInterfaceNO)
{
    switch ( nInterfaceNO )
    {
    case ITF_CREATE_UNIT:
    {
        // �������
        return (PFN_INTERFACE)wke_ControlCreate_Webkit;
    }
    case ITF_PROPERTY_UPDATE_UI:
    {
        // ˵������Ŀǰ�ɷ��޸�
        return (PFN_INTERFACE)wke_PropUpDate_Webkit;
    }
    case ITF_DLG_INIT_CUSTOMIZE_DATA:
    {
        // ʹ�öԻ��������Զ�������
        return (PFN_INTERFACE)wke_PropPopDlg_Webkit;
    }
    case ITF_NOTIFY_PROPERTY_CHANGED:
    {
        // ֪ͨĳ�������ݱ��û��޸�
        return (PFN_INTERFACE)wke_PropChanged_Webkit;
    }
    case ITF_GET_ALL_PROPERTY_DATA:
    {
        // ȡȫ����������
        return (PFN_INTERFACE)wke_PropGetDataAll_Webkit;
    }
    case ITF_GET_PROPERTY_DATA:
    {
        // ȡĳ��������
        return (PFN_INTERFACE)wke_PropGetData_Webkit;
    }
    case ITF_GET_ICON_PROPERTY_DATA:
    {
        // ȡ���ڵ�ͼ����������(�����ڴ���)
        break;
    }
    case ITF_IS_NEED_THIS_KEY:
    {
        // ѯ�ʵ�Ԫ�Ƿ���Ҫָ���İ�����Ϣ, �������ڵ�Ԫ
        return (PFN_INTERFACE)wke_PropKetInfo_webkit;
    }
    case ITF_LANG_CNV:
    {
        // �����������ת��
        break;
    }
    case ITF_MSG_FILTER:
    {
        // ��Ϣ����
        break;
    }
    case ITF_GET_NOTIFY_RECEIVER:
    {
        // ȡ����ĸ���֪ͨ������(PFN_ON_NOTIFY_UNIT)
        return (PFN_INTERFACE)wke_PropNotifyReceiver_webkit;
    }
    default:
        return NULL;
    }
    return NULL;
}


HUNIT WINAPI wke_ControlCreate_Webkit(
    LPBYTE pAllPropertyData,            //   ָ�򱾴��ڵ�Ԫ��������������, �ɱ����ڵ�Ԫ��ITF_GET_PROPERTY_DATA�ӿڲ���, ���û��������ΪNULL��
    INT nAllPropertyDataSize,           //   �ṩpAllPropertyData��ָ�����ݵĳߴ�, ���û����Ϊ0��
    DWORD dwStyle,                      //   Ԥ�����õĴ��ڷ��
    HWND hParentWnd,                    //   �����ھ����
    UINT uID,                           //   �ڸ������е�ID��
    HMENU hMenu,                        //   δʹ�á�
    INT x, INT y, INT cx, INT cy,       //   ָ��λ�ü��ߴ硣
    DWORD dwWinFormID, DWORD dwUnitID,  //   �����ڵ�Ԫ���ڴ��ڼ������ID, ����֪ͨ��ϵͳ��
    HWND hDesignWnd,                    //   ���blInDesignModeΪ��, ��hDesignWnd�ṩ����ƴ��ڵĴ��ھ����
    BOOL blInDesignMode)                //   ˵���Ƿ�������IDE�����Խ��п��ӻ����, ����ʱΪ�١�
{
    // ��ʼ�����������
    if ( s_path.empty() )
    {
        if ( !wke_SetDllPath() )
            return 0;
    }

    static bool isInit;
    if ( !isInit )
    {
        if ( !MbE::Initialize() )
            return 0;
        isInit = true;
    }

    PWEBKIT_PROPERTYEX data = 0;
    HUNIT hUnit = GethUnitFromId(dwWinFormID, dwUnitID, (PVOID*)&data);
    if ( InitDataEx(data) )
    {
        //TODO ���������ڴ�, ��Ҫ�ѵ�ַ��¼����, �Ƚ�����ʱ���ͷ�, Ŀǰ������й©��
    }
    bool isDefProp = false; // �Ƿ���ҪĬ������
    try
    {
        isDefProp = ParsePropData_webkit(data, pAllPropertyData, nAllPropertyDataSize) == 0;
    }
    catch ( ... )
    {
        isDefProp = true;
    }

    // ��¼�����һЩ��Ϣ
    SET_DATA_DEFVALUE(data);

    data->hWnd = data->pCtl->create(hParentWnd, dwStyle | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | 256, uID, x, y, cx, cy, data);
    if ( !data->hWnd )
    {
        // �������ʧ��, ��Ҫ������ʲô����
        wstr dbg;
        dbg.Format(L"���� ����web����� ���ʧ��\n������ = %d", GetLastError());
        MessageBoxW(hParentWnd, dbg.c_str(), L"�������ʧ��", MB_ICONERROR);
        delete data;
        return 0;
    }

    WEBKIT_PROPERTY& prop = data->prop;

    if ( prop.pszUserAgent && prop.pszUserAgent[0] )
        data->pCtl->SetUserAgent(prop.pszUserAgent);    //����UA

    if ( prop.DisableCookie )
        data->pCtl->SetCookieEnabled(false);    // ����cookie

    if ( !data->blInDesignMode )    //�������ģʽ������Ŀ¼��Ϣ
    {
        wstr pathBuffer(260);

        char exePath[MAX_PATH] = { 0 };
        NotifySys(NAS_GET_PATH, 2001, (DWORD)exePath);
        prop.runPath = data->bufPool->AddStringWFromAnsi(exePath);   // ����·��, �����������״̬, ��·��Ϊ��

        if ( prop.pszCachePathW[0] )
        {
            // �л���Ŀ¼, �ж�Ŀ¼�Ƿ��Ǿ���·��
            if ( wcsncmp(prop.pszCachePathW + 1, L":\\", 2) != 0 )
            {
                // ��������·��, ��Ҫ�Ӵ���һ��
                pathBuffer.assign(prop.runPath);
            }
            pathBuffer.append(prop.pszCachePathW);
            if ( pathBuffer.back() != L'\\' )
                pathBuffer.push_back(L'\\');
            data->pCtl->SetLocalStorageFullPath(pathBuffer.c_str());    //���û���Ŀ¼
        }

        if ( prop.pszCookiePathW[0] )
        {
            // �л���Ŀ¼, �ж�Ŀ¼�Ƿ��Ǿ���·��
            if ( wcsncmp(prop.pszCookiePathW + 1, L":\\", 2) != 0 )
            {
                // ��������·��, ��Ҫ�Ӵ���һ��
                pathBuffer.assign(prop.runPath);
            }
            pathBuffer.append(prop.pszCookiePathW);
            if ( pathBuffer.back() != L'\\' )
                pathBuffer.push_back(L'\\');
            data->pCtl->SetCookieJarPath(pathBuffer.c_str());    //����cookieĿ¼
        }


        if ( prop.urlW[0] )
        {
            data->pCtl->GoUrl(prop.urlW);    //�������ģʽ�¾���ת���������url
        }
        wkeSetNavigationToNewWindowEnable(data->pCtl->GetWkeWebView(), prop.isNewWnd);
        data->flags |= EVENT_PTR_E;
        OnwkeCallbackAll(data->pCtl->GetWkeWebView(), data);    //���ûص�
    }
    else
    {
        // ���ģʽ, ��Ҫ�����Ƿ�Ԥ������ҳ��
        if ( prop.debugShow && prop.urlW[0] )
            data->pCtl->GoUrl(prop.urlW);    //�������ģʽ�¾���ת���������url
    }

    //SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, )
    return CreateUnit(data);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    return 0;
}


INT WINAPI wke_PropNotifyReceiver_webkit(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
    switch ( nMsg )
    {
    case NU_GET_CREATE_SIZE_IN_DESIGNER:
        // ȡ���ʱ������������õ�������ʱ��Ĭ�ϴ����ߴ�.
        // dwParam1: ����: INT*, ���ؿ��(��λ����)
        // dwParam2: ����: INT*, ���ظ߶�(��λ����)
        // �ɹ�����1,ʧ�ܷ���0.
        *( (int*)dwParam1 ) = 200;
        *( (int*)dwParam2 ) = 100;
        return 1;
    }
    return 0;
}

BOOL WINAPI wke_PropKetInfo_webkit(HUNIT hUnit, WORD wKey)
{
    // ѯ�ʵ�Ԫ�Ƿ���Ҫָ���İ�����Ϣ, �����Ҫ, ������, ���򷵻ؼ١�
    if ( hUnit == NULL )  return FALSE;
    BOOL bRet = FALSE;
    //PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);
    //assert(wkectrl->m_hWnd != NULL);

    // ���ھ���web��������û����Ҫ��ֹ������

    return bRet;
}

BOOL WINAPI wke_PropUpDate_Webkit(HUNIT hUnit, INT nPropertyIndex)    //����Web�����  �µĸ������Է���
{
    // ���ָ������Ŀǰ���Ա�����, ������, ���򷵻ؼ١�
    // ����Web�����  �µĸ������Է���
    //PWEBKIT_PROPERTYEX data = g_wke[pArgInf->m_unit.m_dwUnitID]
    //if (PROP_TITLE == nPropertyIndex)    //���ڱ��ⲻ�ɲ���
    //    return FALSE;
    
    // ���ھ���web��������û����Ҫ��ֹ������

    return TRUE;
}

BOOL WINAPI wke_PropPopDlg_Webkit(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)    //����Web�����  �µĵ����Ի��򷽷�
{
    // ������������ΪUD_CUSTOMIZE�ĵ�Ԫ���ԡ�
    // �����Ҫ���´����õ�Ԫ�����޸ĵ�Ԫ����, �뷵���档
    //pblModified ��ΪNULL, �������з����Ƿ��û������޸�(����������IDE����UNDO��¼)
    //PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);

    // ���ھ���web��������û����Ҫ�򿪶Ի��������
    return FALSE;
}




typedef BOOL(WINAPI* fun_PathFileExistsW)( LPCWSTR pszPath );
inline static BOOL __LIB2_DEFFUNNAME(PathFileExistsW)( LPCWSTR pszPath )
{
    static HMODULE hModule = 0;
    static fun_PathFileExistsW fun = 0;
    if ( !hModule )
    {
        hModule = LoadLibraryW(L"Shlwapi.dll");
        if ( !hModule )throw "��ȡShlwapi.dll���ʧ��";
        fun = (fun_PathFileExistsW)GetProcAddress(hModule, "PathFileExistsW");
    }
    if ( !fun )throw "PathFileExistsW������ȡʧ��";
    return fun(pszPath);
}
#define PathFileExistsW __LIB2_DEFFUNNAME(PathFileExistsW)


bool wke_SetDllPath()
{
    DWORD nRet = NotifySys(NRS_GET_PRG_TYPE, 0, 0);
    char szPath[MAX_PATH] = { 0 };
    //PT_DEBUG_RUN_VER�����԰棩 PT_RELEASE_RUN_VER�������棩��
    if ( PT_RELEASE_RUN_VER == nRet )
    {
        //����Ǳ����,����û�б�����dll·��,�Ǿ�ȡexe����Ŀ¼
        NotifySys(NAS_GET_PATH, 2001, (DWORD)szPath);
    }
    else
    {
        //������԰��ȡ�����Թ���·��,ide������ȡ�� e.exeĿ¼,F5 ����ʱȡ������ lib/ Ŀ¼
        NotifySys(NAS_GET_PATH, 1, (DWORD)szPath);
    }
    wstr path(260), file(260);
    path.assign(wstr::A2W(szPath));

    if ( path.substr(path.size() - 4, 3) == L"lib" )
        path.resize(path.size() - 4);
    
    file.assign(path).append(L"miniblink_4975_x32.dll");

#ifdef _DEBUG
    //::MessageBoxW(NULL, path.c_str(), nRet == PT_RELEASE_RUN_VER ? L"�����" : L"���԰�", MB_OK);
#endif

    // һ���ж�4��·��, ȫ���������ھ�����ʧ��
    if ( !PathFileExistsW(file.c_str()) )
    {
        file.assign(path).append(L"miniblink_4957_x32.dll");
        if ( !PathFileExistsW(file.c_str()) )
        {
            file.assign(path).append(L"miniblink_4949_x32.dll");
            if ( !PathFileExistsW(file.c_str()) )
            {
                file.assign(path).append(L"node.dll");
                if ( !PathFileExistsW(file.c_str()) )
                {
                    WCHAR szLog[520] = { 0 };
                    swprintf(szLog, L"���\"miniblink_4975_x32.dll\"\r\n"
                             L"���� \"miniblink_4957_x32.dll\"\r\n"
                             L"���� \"miniblink_4949_x32.dll\"\r\n"
                             L"���� \"node.dll\"\r\n"
                             L"����[%s]���Ŀ��", path.c_str());
                    ::MessageBoxW(NULL, szLog, L"����", MB_OK);
                    return false;
                }
            }
        }

    }
    wke_SetDllPath(file.c_str());
    return true;
}

bool wke_SetDllPath(LPCWSTR path)
{
    s_path = path;
    wkeSetWkeDllPath(s_path.c_str());
    return true;
}

bool wke_SetDllPath(LPCSTR path)
{
    wstr pathW = _str::A2W(path);
    bool ret = wke_SetDllPath(pathW.c_str());
    return ret;
}





