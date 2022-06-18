#include "wke_webkit_event.h"
#include <hook/apiHook.h>


#define _JYWKEWEBKIT_EVENT_CALLBACK(_index, _argCount) PWEBKIT_PROPERTYEX pMem = (PWEBKIT_PROPERTYEX)param;\
jyWebKit_event_arg##_argCount fun = (jyWebKit_event_arg##_argCount)pMem->pCtl->jyEvent.arg[_index].fun;

HHOOK g_hhk = 0;
PWEBKIT_PROPERTYEX g_wkeCtrl = 0;
void wke_OnNetGetFaviconCallback(wkeWebView webView, void* param, const utf8* url, wkeMemBuf* buf);
static apiHook hook;
static BOOL(WINAPI* GetSaveFileNameW_hook)(LPOPENFILENAMEW lpmbp) = GetSaveFileNameW;
static BOOL(WINAPI* GetOpenFileNameW_hook)(LPOPENFILENAMEW lpmbp) = GetOpenFileNameW;
BOOL WINAPI MyGetSaveFileNameW(LPOPENFILENAMEW lpmbp)
{
    EVENT_NOTIFY2 eventInfo(g_wkeCtrl->dwWinFormID, g_wkeCtrl->dwUnitID, 0);
    char* tmp = 0;
    eventInfo.m_nEventIndex = EVENT_SAVEFILENAME;
    eventInfo.m_nArgCount = 1;
    eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
    eventInfo.m_arg[0].m_inf.m_pText = (char*)(&tmp);
    eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;
    INT ret = NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);

    wstr s = _str::A2W(tmp);
    size_t len = s.size();
    if (len < lpmbp->nMaxFile)
    {
        memcpy(lpmbp->lpstrFile, s.c_str(), len * sizeof(wchar_t));
    }
    else
    {
        memcpy(lpmbp->lpstrFile, s.c_str(), lpmbp->nMaxFile * sizeof(wchar_t));
    }

    if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == false)    // �з���ֵ, �ҷ���ֵ==false
    {
        return TRUE;    // ����API����, ֱ�ӷ�����
    }
    return GetSaveFileNameW_hook(lpmbp);
}

BOOL WINAPI MyGetOpenFileNameW(LPOPENFILENAMEW lpmbp)
{
    EVENT_NOTIFY2 eventInfo(g_wkeCtrl->dwWinFormID, g_wkeCtrl->dwUnitID, 0);
    char* tmp = 0;
    eventInfo.m_nEventIndex = EVENT_OPENFILENAME;
    eventInfo.m_nArgCount = 1;
    eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
    eventInfo.m_arg[0].m_inf.m_pText = (char*)(&tmp);
    eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;
    INT ret = NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);

    wstr s = _str::A2W(tmp);
    size_t len = s.size();
    if (len < lpmbp->nMaxFile)
    {
        memcpy(lpmbp->lpstrFile, s.c_str(), len * sizeof(wchar_t));
    }
    else
    {
        memcpy(lpmbp->lpstrFile, s.c_str(), lpmbp->nMaxFile * sizeof(wchar_t));
    }

    if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == false)    // �з���ֵ, �ҷ���ֵ==false
    {
        return TRUE;    // ����API����, ֱ�ӷ�����
    }
    return GetOpenFileNameW_hook(lpmbp);
}

// ֻ���û����ؼٲŷ���0,�û�û�з��ػ򷵻����򷵻�1,����ʧ�ܷ���-1,����ʧ��һ�����û�û�ж�������¼�
inline static int webkit_notify_wke(PWEBKIT_PROPERTYEX data, int nIndex, int nCount, ...)
{
    EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, nIndex);
    int i;
    va_list vl;
    va_start(vl, nCount);
    eventInfo.m_nArgCount = nCount;
    int nRet = 1;    //������ֵ,ֻ���û����ؼٲŸ�ֵΪ0, 0�ǲ�����������Ϣ
    for (i = 0; i < nCount; i++)
    {
        eventInfo.m_arg[i].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[i].m_inf.m_int = va_arg(vl, int);
    }
    va_end(vl);

    nRet = NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    if (!nRet) return -1;// �¼�������,���̵�һ������û�û�д�������¼�
    if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)    //���ݵ��������¼��ɹ��ҷ����˼�
        return 0;
    return 1;    //�û�û�з���һ��ֵ,���߷��ص�ֵΪ��
}


// param = WKECtrl��ָ��
// ��¼�¼�����Դ
// DWORD    m_dwFormID;      // ����ITF_CREATE_UNIT�ӿ������ݹ�������������ID��dwWinFormID������
// DWORD    m_dwUnitID;      // ����ITF_CREATE_UNIT�ӿ������ݹ����Ĵ��ڵ�ԪID��dwUnitID������
// INT      m_nEventIndex;   //   �¼��������ڴ��ڵ�Ԫ������ϢLIB_DATA_TYPE_INFO��m_pPropertyBegin��Ա�е�λ�ã�

// EVENT_ARG_VALUE m_arg [MAX_EVENT2_ARG_COUNT];  // ��¼������ֵ��
// EVENT_ARG_VALUE      m_arg [5]; // ��¼������ֵ��SDT_BOOL �Ͳ���ֵΪ 1 �� 0��

//!!! ע�������Ա��û�ж��巵��ֵ���¼���������Ч��
// BOOL     m_blHasRetVal; // �û��¼������ӳ���������¼����Ƿ��ṩ�˷���ֵ��
// INT      m_infRetData; // �û��¼������ӳ���������¼���ķ���ֵ���߼�ֵ����ֵ 0���٣� �� 1���棩 ���ء�

void OnwkeCallbackAll(wkeWebView webView, PWEBKIT_PROPERTYEX data)
{
    static bool isInit;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( g_wkeCtrl == 0 )
        {
            g_wkeCtrl = data;
        }
    }
    __fill_wnd_data(data, webView);

    ////���ñ���仯��֪ͨ�ص�
    //wkeOnTitleChanged(webView, OnwkeTitleChanged, data);
    //
    ////��껮����Ԫ�أ�����ǣ�����ô˻ص���������a��ǩ��url
    //wkeOnMouseOverUrlChanged(webView, OnwkeMouseOverUrlChanged, data);
    //
    ////url�ı�ص�
    ////wkeOnURLChanged(webView, OnwkeURLChanged, pUnit);
    //
    ////url�ı�ص�,���ϸ��ӿڲ�ͬ���ǣ��ص����˸�����
    //wkeOnURLChanged2(webView, OnwkeURLChanged2, data);
    //
    ////ҳ�����κ���Ҫˢ�µĵط��������ô˻ص�
    ////wkeOnPaintUpdated(webView, OnwkePaintUpdated, pUnit);
    //
    ////ҳ�����κ���Ҫˢ�µĵط��������ô˻ص�,�ص����������������ص�buffer��������DC������Ƕ�뵽��Ϸ����������Ⱦ
    ////wkeOnPaintBitUpdated(webView, OnwkePaintBitUpdated, pUnit);
    ////AlertBox �����ô���
    //wkeOnAlertBox(webView, OnwkeAlertBox, data);
    //
    ////ConfirmBox �����ô���
    //wkeOnConfirmBox(webView, OnwkeConfirmBox, data);
    //
    ////PromptBox �����ô���
    //wkeOnPromptBox(webView, OnwkePromptBox, data);
    //
    ////��ҳ��ʼ����������ص�
    //wkeOnNavigation(webView, OnwkeNavigation, data);
    //
    ////��ҳ���a��ǩ�����´���ʱ�������ص�
    //wkeOnCreateView(webView, OnwkeCreateView, data);
    //
    ////��Ӧjs���body onload�¼�
    ////wkeOnDocumentReady(webView, OnwkeDocumentReady, pUnit);
    //
    ////��Ӧjs���body onload�¼�,����wkeWebFrameHandle frameId�����������ж��Ƿ�����frame
    //wkeOnDocumentReady2(webView, OnwkeDocumentReady2, data);
    //
    ////�ĵ��������
    //wkeOnLoadingFinish(webView, OnwkeLoadingFinish, data);
    //
    //
    ////ҳ�������¼��ص������ĳЩ���ӣ��������ػ����
    //wkeOnDownload(webView, OnwkeDownload, data);
    //
    ////һ�����������ͺ��յ�������response�����ص�
    ////wkeNetOnResponse(webView, OnwkeNetResponse, pUnit);
    //
    ////��ҳ����console����
    //wkeOnConsole(webView, OnConsoleMessage, data);
    //
    ////��ʱδʵ��
    ////wkeSetUIThreadCallback(webView, OnwkeCallUiThread, pUnit);
    //
    ////�κ�����������ǰ�ᴥ���˻ص�
    //wkeOnLoadUrlBegin(webView, OnwkeLoadUrlBegin, data);
    //
    ////url�������
    //wkeOnLoadUrlEnd(webView, OnwkeLoadUrlEnd, data);
    //
    ////javascript��v8ִ�л���������ʱ�����˻ص�,ע�⣺ÿ��frame����ʱ���ᴥ���˻ص�
    ////wkeOnDidCreateScriptContext(webView, OnwkeDidCreateScriptContext, pUnit);
    //
    ////ÿ��frame��javascript��v8ִ�л������ر�ʱ�����˻ص�
    ////wkeOnWillReleaseScriptContext(webView, OnwkeWillReleaseScriptContext, pUnit);
    //
    ////video�ȶ�ý���ǩ����ʱ�����˻ص�
    ////wkeOnWillMediaLoad(webView, OnwkeWillMediaLoad, pUnit);
    //
    ////g_hhk = SetWindowsHookExW(WH_CBT, CBTProc, NULL, GetCurrentThreadId());
    ////g_wkeCtrl = (WKECtrl*)pUnit;
    ////hook.hook(&(PVOID&)GetSaveFileNameW_hook, MyGetSaveFileNameW);
    if ( !isInit )
    {
        hook.hook(&(PVOID&)GetOpenFileNameW_hook, MyGetOpenFileNameW);
        isInit = true;
    }
}

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    switch (nCode)
    {
    case HCBT_CREATEWND:
    {
        LPCBT_CREATEWNDW ct = (LPCBT_CREATEWNDW)lParam;
        if ((int)ct->lpcs->lpszClass != 32770)break;
        if ((ct->lpcs->style & WS_THICKFRAME) == 0)break;    // ���ڵ��жϷ�ʽ����������,�����Ǹ�����û�пɵ��߿����ж��Ƿ�Ϊ�ļ��Ի���

        HWND hWnd = (HWND)wParam;
        //WCHAR szClass[MAX_PATH] = { 0 };
        //GetClassNameW(hWnd, szClass, MAX_PATH);
        //if (wcscmp(szClass, L"#32770") != 0)return CallNextHookEx(g_hhk, nCode, wParam, lParam);
        //FindWindowExW(hWnd,)

        webkit_notify_wke(g_wkeCtrl, EVENT_DLGCREATEING, 3, (int)hWnd, 1, 0);
        break;
    }
    }

    return CallNextHookEx(g_hhk, nCode, wParam, lParam);
}


void OnwkeTitleChanged(wkeWebView webView, void* param, const wkeString title)
{
    //�¼����ƣ����ⱻ�ı�
    //�¼����ܣ���ҳ���ⱻ�ı�ʱ�������¼�
    //�������ͣ��޷���ֵ
    //�¼�����<1>������Ϊ�����⡱������Ϊ��SDT_TEXT������ҳ���ⱻ����ʱ����
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return;

        _str url = wstr::W2A(wkeGetStringW(title));

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_TITLECHANGE;
        eventInfo.m_nArgCount = 1;
        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = url.c_str();
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;
        NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(1, 1);
        const wchar_t* wstr = wkeGetStringW(title);
        if (fun)
        {
            _str str = _str::W2A(wstr);
            fun(webView, pMem->pCtl->jyEvent.arg[1].arg, (int)str.c_str());
        }
        else
        {
            wkeSetWindowTitleW(webView, wstr);
        }
    }

}

//URL�ı�ص�,��������
void OnwkeURLChanged(wkeWebView webView, void* param, const wkeString url)
{
}

//URL�ı�ص�,������
void OnwkeURLChanged2(wkeWebView webView, void* param, wkeWebFrameHandle frameId, const wkeString url)
{
    //�¼����ƣ�URL���ı�
    //�¼����ܣ�URL���ı�ʱ����
    //�������ͣ��޷���ֵ
    //�¼�����<1>������Ϊ��URL��������Ϊ��SDT_TEXT�����ı��URL
    //�¼�����<2>������Ϊ���������ID��������Ϊ��SDT_INT������ǰURL�����ĸ����ID
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return;

        _str url1 = wstr::W2A((LPWSTR)wkeGetStringW(url));

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_URLCHANGE;
        eventInfo.m_nArgCount = 2;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = url1.c_str();
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[1].m_inf.m_int = (int)frameId;
        NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(2, 2);
        if (fun)
        {
            _str str = _str::W2A(wkeGetStringW(url));
            fun(webView, pMem->pCtl->jyEvent.arg[2].arg, (int)str.c_str(), (int)frameId);
        }
    }
}


//ҳ�����κ���Ҫˢ�µĵط��������ô˻ص�
void OnwkePaintUpdated(wkeWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {

    }
}

//ҳ�����κ���Ҫˢ�µĵط��������ô˻ص�,�ص����������������ص�buffer��������DC������Ƕ�뵽��Ϸ����������Ⱦ
void OnwkePaintBitUpdated(wkeWebView webView, void* param, const void* buffer, const wkeRect* r, int width, int height)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {

    }
}

//��ҳ����alert����
void OnwkeAlertBox(wkeWebView webView, void* param, const wkeString message)
{
    //�¼����ƣ�Alert��������
    //�¼����ܣ�����ҳ�е�alert�����õ�ʱ�򴥷�
    //�������ͣ��޷���ֵ
    //�¼�����<1>������Ϊ����Ϣ��������Ϊ��SDT_TEXT����������������Ϣ
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return;

        _str szMsg;
        szMsg = wstr::W2A((LPWSTR)wkeGetStringW(message));

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_ALERTBOX;
        eventInfo.m_nArgCount = 1;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = szMsg.c_str();
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(7, 1);
        if (fun)
        {
            _str str1 = _str::W2A(wkeGetStringW(message));
            fun(webView, pMem->pCtl->jyEvent.arg[7].arg, (int)str1.c_str());
        }
    }
}

//ConfirmBoxָ����Ϣ�� OK ��ȡ����ť�ĶԻ���
bool OnwkeConfirmBox(wkeWebView webView, void* param, const wkeString msg)
{
    //�¼����ƣ�Confirm��������
    //�¼����ܣ�����ҳ�е�alert�����õ�ʱ�򴥷�
    //�������ͣ�SDT_BOOL
    //�¼�����<1>������Ϊ����Ϣ��������Ϊ��SDT_TEXT����������������Ϣ
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return true;

        bool bRet = true;
        _str szMsg;
        szMsg = wstr::W2A((LPWSTR)wkeGetStringW(msg));

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_CONFIRMBOX;
        eventInfo.m_nArgCount = 1;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = szMsg.c_str();
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//Ͷ�ݳɹ�,�����û������˼�
        {
            if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)
                bRet = false;
        }

        return bRet;
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(8, 1);
        if (fun)
        {
            _str str1 = _str::W2A(wkeGetStringW(msg));
            return fun(webView, pMem->pCtl->jyEvent.arg[8].arg, (int)str1.c_str());
        }
        return true;
    }
}

bool OnwkePromptBox(wkeWebView webView, void* param, const wkeString msg, const wkeString defaultResult, wkeString result)
{
    //�¼����ƣ�Prompt��������
    //�¼����ܣ�����ҳ�е�Prompt�����õ�ʱ�򴥷�
    //�������ͣ�SDT_BOOL
    //�¼�����<1>������Ϊ����ʾ��Ϣ��������Ϊ��SDT_TEXT������������ʾ��Ϣ
    //�¼�����<2>������Ϊ��Ĭ��ֵ��������Ϊ��SDT_TEXT����������Ĭ��ֵ

    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return TRUE;

        bool bRet = TRUE;
        _str szDefStr = wstr::W2A((LPWSTR)wkeGetStringW(defaultResult));
        _str szResStr = wstr::W2A((LPWSTR)wkeGetStringW(result));

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_PROMPTBOX;
        eventInfo.m_nArgCount = 2;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = szResStr.c_str();
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp1 = szDefStr.c_str();

        eventInfo.m_arg[1].m_inf.m_pText = (char*)&tmp1;
        eventInfo.m_arg[1].m_dwState = EAV_IS_POINTER;
        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//Ͷ�ݳɹ�,�����û������˼�
        {
            if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)bRet = FALSE;
        }

        return bRet;
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(9, 2);
        if (fun)
        {
            _str str1 = _str::W2A(wkeGetStringW(msg));
            _str str2 = _str::W2A(wkeGetStringW(result));
            return fun(webView, pMem->pCtl->jyEvent.arg[9].arg, (int)str1.c_str(), (int)str2.c_str());
        }
        return true;
    }
}

//��ҳ��ʼ����������ص�, �����������µ�ַ
bool OnwkeNavigation(wkeWebView webView, void* param, wkeNavigationType navigationType, wkeString url)
{
    //wkeNavigationType: ��ʾ���������ԭ�򡣿���ȡ��ֵ�У�
    //WKE_NAVIGATION_TYPE_LINKCLICK�����a��ǩ����
    //WKE_NAVIGATION_TYPE_FORMSUBMITTE�����form����
    //WKE_NAVIGATION_TYPE_BACKFORWARD��ǰ�����˴���
    //WKE_NAVIGATION_TYPE_RELOAD�����¼��ش���
    //ע�⣺wkeNavigationCallback�ص��ķ���ֵ�������true����ʾ���Լ������������false��ʾ��ֹ���������

    //�¼����ƣ������������µ�ַ
    //�¼����ܣ���Ҫ�������µ���ַǰ����
    //�������ͣ�SDT_BOOL
    //�¼�����<1>������Ϊ���������͡�������Ϊ��SDT_INT������������������  0==�������� 1==���ύ 2==���� 3==��������(ˢ��) 4==�������ύ  5==��������
    //�¼�����<2>������Ϊ��URL��������Ϊ��SDT_TEXT��������������URL
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return true;
        bool bRet = true;
        _str szUrl = wstr::W2A((LPWSTR)wkeGetStringW(url));

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_NAVIGATION;
        eventInfo.m_nArgCount = 2;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[0].m_inf.m_int = (int)navigationType;

        eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = szUrl.c_str();
        eventInfo.m_arg[1].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[1].m_dwState = EAV_IS_POINTER;

        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//Ͷ�ݳɹ�,�����û������˼�
        {
            if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)//����ֵ=��
                bRet = false;
        }

        return bRet;
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(3, 2);
        if (fun)
        {
            _str str = _str::W2A(wkeGetStringW(url));
            return fun(webView, pMem->pCtl->jyEvent.arg[3].arg, (int)navigationType, (int)str.c_str());
        }
        return true;
    }
}

static wkeWebView _create_new_webview(PWEBKIT_PROPERTYEX data, HWND hWndParent, RECT& rc, bool isCallEEvt)
{
    if ( isCallEEvt )
        webkit_notify_wke(data, EVENT_NEWWNDCREATEING, 5, (int)&hWndParent, (int)&rc.left, (int)&rc.top, (int)&rc.right, (int)&rc.bottom);

    wkeWebView newWebView = wkeCreateWebWindow(WKE_WINDOW_TYPE_POPUP, hWndParent,
                                               rc.left, rc.top, rc.right, rc.bottom);

    PWEBKIT_PROPERTYEX newData = new WEBKIT_PROPERTYEX;
    newData->clear();
    newData->init();

    data->flags |= EVENT_PTR_NEWWINDOW;
    WKECtrl* wke = newData->pCtl;
    HWND hWnd = wkeGetWindowHandle(newWebView);
    newData->hWnd = hWnd;
    newData->prop.isNewWnd = data->prop.isNewWnd;
    wke->SetWkeWebView(newWebView);
    __fill_wnd_data(newData, newWebView);

    if ( isCallEEvt )
        webkit_notify_wke(data, EVENT_NEWWNDCREATEEND, 1, (int)newWebView);

    wkeSetWindowTitleW(newWebView, L"����Web�����");
    wkeShowWindow(newWebView, true);
    return newWebView;
}

//��ҳ���a��ǩ�����´���ʱ�������ص�, �����������´���
wkeWebView OnwkeCreateView(wkeWebView webView, void* param, wkeNavigationType navigationType, const wkeString url, const wkeWindowFeatures* windowFeatures)
{
    //�¼����ƣ������������´���
    //�¼����ܣ������������´���,����(��) �ڵ�ǰ���ڴ���ַ,����(��) ���д���
    //�������ͣ�SDT_BOOL
    //�¼�����<1>������Ϊ���������͡�������Ϊ��SDT_INT������������������  0==�������� 1==���ύ 2==���� 3==��������(ˢ��) 4==�������ύ  5==��������
    //�¼�����<2>������Ϊ��URL��������Ϊ��SDT_TEXT��������������URL
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return 0;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return NULL;

        wkeWebView newWebView = NULL;
        _str szUrl = wstr::W2A(wkeGetStringW(url));

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, EVENT_CREATEWENVIEW);
        eventInfo.m_nArgCount = 2;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[0].m_inf.m_int = (int)navigationType;

        eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = szUrl.c_str();
        eventInfo.m_arg[1].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[1].m_dwState = EAV_IS_POINTER;

        //eventInfo.m_arg[2].m_inf.m_dtDataType = SDT_INT;
        //eventInfo.m_arg[2].m_inf.m_int = (int)windowFeatures;

        BOOL b = TRUE;
        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//Ͷ�ݳɹ�
        {
            // �û������˼�,������
            if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)
                b = FALSE;
        }
        // �û���������,���������´��ڴ�
        if (b && data->prop.isNewWnd)
        {
            RECT rc = { 0 };
            HWND hWndParent = 0;
            rc.left = windowFeatures->x;
            rc.top = windowFeatures->y;
            rc.right = windowFeatures->width;
            rc.bottom = windowFeatures->height;
            return _create_new_webview(data, hWndParent, rc, true);
        }

        return newWebView;
    }

    _JYWKEWEBKIT_EVENT_CALLBACK(4, 2);
    if (fun)
    {
        _str str = _str::W2A(wkeGetStringW(url));
        BOOL isNew = fun(webView, pMem->pCtl->jyEvent.arg[4].arg, (int)navigationType, (int)str.c_str());
        if ( !isNew )
            return 0;
    }
    if (pMem->prop.isNewWnd)
    {
        RECT rc;
        GetWindowRect(pMem->hWnd, &rc);
        rc.right -= rc.left;
        rc.bottom -= rc.top;
        if (rc.right <= 0)rc.right = 500;
        if (rc.bottom <= 0)rc.bottom = 300;
        rc.left = CW_USEDEFAULT;
        rc.top = 0;
        return _create_new_webview(pMem, 0, rc, false);
    }
    return 0;

}


// �����봰�ڿɷ�ر�
bool handleWindowClosing(wkeWebView webWindow, void* param)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return NULL;
        int nRet = webkit_notify_wke(data, EVENT_NEWWNDCLOSE, 1, (int)webWindow);
        if (nRet == 0)
        {
            return false;
        }
        return true;
    }
    return true;
}

// �����봰�ڼ�������
void handleWindowDestroy(wkeWebView webWindow, void* param)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return;
        webkit_notify_wke(data, EVENT_NEWWNDDESTROY, 1, (int)webWindow);
    }
    return;
}


//��Ӧjs���body onload�¼�,�޿��ID,�ĵ�����
void OnwkeDocumentReady(wkeWebView webView, void* param)
{
}

//��Ӧjs���body onload�¼�,�п��ID,�ĵ�����
void OnwkeDocumentReady2(wkeWebView webView, void* param, wkeWebFrameHandle frameId)
{
    //�¼����ƣ��ĵ�����
    //�¼����ܣ��ĵ�����ʱ����
    //�������ͣ��޷���ֵ
    //�¼�����<1>������Ϊ���������ID��������Ϊ��SDT_INT������ҳ�ĵ��������ڲ���ܾ���ʱ����
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return;

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_DOCUMENTREADY;
        eventInfo.m_nArgCount = 1;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[0].m_inf.m_int = (int)frameId;

        NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(0, 1);
        if (fun)fun(webView, pMem->pCtl->jyEvent.arg[0].arg, (int)frameId);
    }
}


void OnwkeLoadingFinish(wkeWebView webView, void* param, const wkeString url, wkeLoadingResult result, const wkeString failedReason)
{
    //�¼����ƣ��ĵ��������
    //�¼����ܣ��ĵ��������ʱ����
    //�������ͣ��޷���ֵ
    //�¼�����<1>������Ϊ������URL��������Ϊ��SDT_TEXT����������ϵ�URL
    //�¼�����<2>������Ϊ������״̬��������Ϊ��SDT_INT���������״̬  0==����ɹ� 1==����ʧ�� 2==ȡ������
    //�¼�����<3>������Ϊ��ʧ��ԭ�򡱣�����Ϊ��SDT_TEXT�������ĵ�����ʧ��ʱ,���ʧ��ԭ��
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        _str szUrl, szfailedReason;
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return;
        if (url)
            szUrl = wstr::W2A((LPWSTR)wkeGetStringW(url));
        if (failedReason)
            szfailedReason = wstr::W2A((LPWSTR)wkeGetStringW(failedReason));
        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, EVENT_DOCUMENTED);

        eventInfo.m_nArgCount = 3;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = szUrl.c_str();
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_TEXT;
        eventInfo.m_arg[1].m_inf.m_int = (int)result;

        eventInfo.m_arg[2].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp1 = szfailedReason.c_str();
        eventInfo.m_arg[2].m_inf.m_pText = (char*)&tmp1;
        eventInfo.m_arg[2].m_dwState = EAV_IS_POINTER;

        //wkeNetGetFavicon(webView, wke_OnNetGetFaviconCallback, param);
        NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(5, 3);
        if (fun)
        {
            _str str = _str::W2A(wkeGetStringW(url));
            _str str1 = _str::W2A(wkeGetStringW(failedReason));
            fun(webView, pMem->pCtl->jyEvent.arg[5].arg, (int)str.c_str(), (int)result, (int)str1.c_str());
        }
    }

}

void wke_OnNetGetFaviconCallback(wkeWebView webView, void* param, const utf8* url, wkeMemBuf* buf)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, EVENT_ICONCHANGED);
        //�¼����ƣ���ҳͼ��ı�
        //�¼����ܣ���ҳͼ��ı�ʱ����
        //�������ͣ��޷���ֵ
        //�¼�����<1>������Ϊ��URL��������Ϊ��SDT_TEXT��
        //�¼�����<2>������Ϊ��ͼ��ָ�롱������Ϊ��SDT_INT����ָ��ͼ�����ݵĵ�ַ
        //�¼�����<3>������Ϊ��ͼ�곤�ȡ�������Ϊ��SDT_INT����ͼ�곤��

        eventInfo.m_nArgCount = 3;
        void* data = (buf ? buf->data : 0);
        int length = (buf ? buf->length : 0);

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&url;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[1].m_inf.m_int = (int)data;

        eventInfo.m_arg[2].m_inf.m_dtDataType = SDT_TEXT;
        eventInfo.m_arg[2].m_inf.m_int = (int)length;

        NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    }
}


//ҳ�������¼��ص������ĳЩ���ӣ��������ػ����
bool OnwkeDownload(wkeWebView webView, void* param, const char* url)
{
    //�¼����ƣ����������ļ�
    //�¼����ܣ����������ļ�ʱ�������¼�
    //�������ͣ�SDT_BOOL
    //�¼�����<1>������Ϊ���ļ�URL��������Ϊ��SDT_TEXT����׼�����ص��ļ�URL
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return TRUE;

        LPSTR szUrl = NULL;
        bool bRet = FALSE;
        szUrl = CloneTextData((char*)url);
        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_DOWNLOAD;
        eventInfo.m_nArgCount = 1;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&szUrl;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//Ͷ�ݳɹ�,�����û������˼�
        {
            if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)
                bRet = TRUE;
        }
        NotifySys(NRS_MFREE, (DWORD)szUrl, 0);
        return bRet;
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(10, 1);
        if (fun)
        {
            return fun(webView, pMem->pCtl->jyEvent.arg[10].arg, (int)url);
        }
        return true;
    }
    return false;
}

//һ�����������ͺ��յ�������response�����ص�
bool OnwkeNetResponse(wkeWebView webView, void* param, const utf8* url, wkeNetJob job)
{
    return NULL;
}

void SendCallBack(PWEBKIT_PROPERTYEX data, void* param, wkeConsoleLevel level, const wkeString message, const wkeString sourceName, unsigned sourceLine, const wkeString stackTrace)
{
    _str szMsg, szName, szStackTrace;
    if (message)
        szMsg = wstr::W2A((LPWSTR)wkeGetStringW(message));

    if (sourceName)
        szName = wstr::W2A((LPWSTR)wkeGetStringW(sourceName));

    if (stackTrace != NULL)
        szStackTrace = wstr::W2A((LPWSTR)wkeGetStringW(stackTrace));

    EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, EVENT_CONSOLE);
    eventInfo.m_nArgCount = 5;

    eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_INT;
    eventInfo.m_arg[0].m_inf.m_int = (int)level;

    eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_INT;
    eventInfo.m_arg[1].m_inf.m_int = (int)sourceLine;

    eventInfo.m_arg[2].m_inf.m_dtDataType = SDT_TEXT;
    LPCSTR tmp = szMsg.c_str();
    eventInfo.m_arg[2].m_inf.m_pText = (char*)&tmp;
    eventInfo.m_arg[2].m_dwState = EAV_IS_POINTER;

    eventInfo.m_arg[3].m_inf.m_dtDataType = SDT_TEXT;
    LPCSTR tmp1 = szName.c_str();
    eventInfo.m_arg[3].m_inf.m_pText = (char*)&tmp1;
    eventInfo.m_arg[3].m_dwState = EAV_IS_POINTER;

    eventInfo.m_arg[4].m_inf.m_dtDataType = SDT_TEXT;
    LPCSTR tmp2 = szStackTrace.c_str();
    eventInfo.m_arg[4].m_inf.m_pText = (char*)&tmp2;
    eventInfo.m_arg[4].m_dwState = EAV_IS_POINTER;

    NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);

}

//��ҳ����console����
//�¼����ƣ���̨��Ϣ���
//�¼����ܣ�����������̨��Ϣʱ����
//�������ͣ��޷���ֵ
//�¼�����<1>������Ϊ�����𡱣�����Ϊ��SDT_INT������Ϣ���� , #��Ϣ����_ ��ͷ�ĳ���
//�¼�����<2>������Ϊ���кš�������Ϊ��SDT_INT������Ϣ�������к�
//�¼�����<3>������Ϊ����Ϣ��������Ϊ��SDT_TEXT��������̨��Ϣ
//�¼�����<4>������Ϊ����Դ���ơ�������Ϊ��SDT_TEXT������Դ����
//�¼�����<5>������Ϊ����ջ���١�������Ϊ��SDT_TEXT������Դ����
void OnConsoleMessage(wkeWebView webView, void* param, wkeConsoleLevel level, const wkeString message, const wkeString sourceName, unsigned sourceLine, const wkeString stackTrace)
{
    char* sz = "onConsoleMessageonConsoleMessageonConsoleMessageonConsoleMessageonConsoleMessageonConsoleMessageonConsoleMessage";
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        SendCallBack(data, param, level, message, sourceName, sourceLine, stackTrace);
        return;
        // ��Ҫд��һ���ӳ����У����д�����棬�ͻ����
        /*    LPTSTR szMsg = NULL, szName = NULL, szStackTrace = NULL;
            if (message != NULL)
                szMsg = _W2A_wke((LPWSTR)wkeGetStringW(message));

            if (sourceName != NULL)
                szName = _W2A_wke((LPWSTR)wkeGetStringW(sourceName));

            if (stackTrace != NULL)
                szStackTrace = _W2A_wke((LPWSTR)wkeGetStringW(stackTrace));

            EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, EVENT_CONSOLE);
            eventInfo.m_nArgCount = 5;

            eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_INT;
            eventInfo.m_arg[0].m_inf.m_int = (int)1;

            eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_INT;
            eventInfo.m_arg[1].m_inf.m_int = (int)2;

            eventInfo.m_arg[2].m_inf.m_dtDataType = SDT_TEXT;
            eventInfo.m_arg[2].m_inf.m_ppText = (char**)& szMsg;
            eventInfo.m_arg[2].m_dwState = EAV_IS_POINTER;

            eventInfo.m_arg[3].m_inf.m_dtDataType = SDT_TEXT;
            eventInfo.m_arg[3].m_inf.m_ppText = (char**) &szName;
            eventInfo.m_arg[3].m_dwState = EAV_IS_POINTER;

            eventInfo.m_arg[4].m_inf.m_dtDataType = SDT_TEXT;
            eventInfo.m_arg[4].m_inf.m_ppText = (char**)& szStackTrace;
            eventInfo.m_arg[4].m_dwState = EAV_IS_POINTER;

            char szlog[1024] ;
            sprintf
                (szlog, "level:%d \n sourceLine:%d\narg3:%d\narg4:%d\n,%arg5:%d\n , %s",level,sourceLine,eventInfo.m_arg[2].m_inf.m_ppText,eventInfo.m_arg[3].m_inf.m_ppText,eventInfo.m_arg[4].m_inf.m_ppText ,sz);

            MessageBox(0, szlog," ConsoleMessage ", MB_OK);

            wkeNotifySys(NRS_EVENT_NOTIFY2, (DWORD)& eventInfo, 0);

            //MessageBox(0, szlog," ConsoleMessageAFTER ", MB_OK);

            delete[] szMsg;
            delete[] szName;
            delete[] szStackTrace;
            */
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(6, 5);
        if (fun)
        {
            _str str1 = _str::W2A(wkeGetStringW(message));
            _str str2 = _str::W2A(wkeGetStringW(sourceName));
            _str str3 = _str::W2A(wkeGetStringW(stackTrace));
            fun(webView, pMem->pCtl->jyEvent.arg[6].arg, (int)level, (int)sourceLine, (int)str1.c_str(), (int)str2.c_str(), (int)str3.c_str());
        }
    }
}

//��ʱδʵ��
void OnwkeCallUiThread(wkeWebView webView, wkeOnCallUiThread func, void* param)
{
}

//�κ�����������ǰ�ᴥ���˻ص�
bool OnwkeLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job)
{
    //������typedef bool(*wkeLoadUrlBeginCallback)(wkeWebView webView, void* param, const char *url, void *job)
    //ע�⣺
    //1���˻ص�����ǿ���ڻص�������job������wkeNetHookRequest�����ʾmb�Ỻ���ȡ�����������ݣ���������������� ���������wkeOnLoadUrlEnd���õĻص���ͬʱ���ݻ�������ݡ��ڴ��ڼ䣬mb���ᴦ���������ݡ�
    //2�������wkeLoadUrlBeginCallback��û����wkeNetHookRequest���򲻻ᴥ��wkeOnLoadUrlEnd�ص���
    //3�����wkeLoadUrlBeginCallback�ص��ﷵ��true����ʾmb��������������󣨼Ȳ��ᷢ���������󣩡�����false����ʾmb��Ȼ�ᷢ����������

    //�¼����ƣ�Url���뿪ʼ
    //�¼����ܣ�Url��ʼ����
    //�������ͣ�SDT_BOOL
    //�¼�����<1>������Ϊ��Url��������Ϊ��SDT_TEXT����Ҫ�����URL
    //�¼�����<2>������Ϊ��Job��������Ϊ��SDT_INT����Job
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return false;

        bool bRet = false;

        _str szUrl = wstr::U2A((const utf8*)url);

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_LOADURLING;
        eventInfo.m_nArgCount = 2;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPSTR tmp = szUrl.data();
        eventInfo.m_arg[0].m_inf.m_ppText = &tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[1].m_inf.m_int = (int)job;

        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//Ͷ�ݳɹ�,�����û������˼�
            if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)
                bRet = false;
            else
                bRet = true;

        return bRet;
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(11, 2);
        if (fun)
        {
            return fun(webView, pMem->pCtl->jyEvent.arg[11].arg, (int)url, (int)job);
        }
        return true;
    }
}

//����url���
void OnwkeLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len)
{
    //�¼����ƣ�Url�������
    //�¼����ܣ�Url�������
    //�������ͣ��޷���ֵ
    //�¼�����<1>������Ϊ��Url��������Ϊ��SDT_TEXT����Ҫ�����URL
    //�¼�����<2>������Ϊ��Job��������Ϊ��SDT_INT����Job
    //�¼�����<3>������Ϊ�������ֽڼ�ָ�롱������Ϊ��SDT_INT������ʹ�� ָ�뵽�ֽڼ�() �����ȡ
    //�¼�����<4>������Ϊ�����ݳ��ȡ�������Ϊ��SDT_INT�������ݳ���
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return;

        _str szUrl = wstr::U2A((const utf8*)url);

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_LOADURLEND;
        eventInfo.m_nArgCount = 4;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = szUrl.c_str();
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        eventInfo.m_arg[1].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[1].m_inf.m_int = (int)job;

        eventInfo.m_arg[2].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[2].m_inf.m_int = (int)buf;

        eventInfo.m_arg[3].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[3].m_inf.m_int = (int)len;

        NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(12, 4);
        if (fun)
        {
            fun(webView, pMem->pCtl->jyEvent.arg[12].arg, (int)url, (int)job, (int)buf, (int)len);
        }
    }
}

//video�ȶ�ý���ǩ����ʱ�����˻ص�
void OnwkeWillMediaLoad(wkeWebView webView, void* param, const char* url, wkeMediaLoadInfo* info)
{
    OutputDebugStringA("video�ȶ�ý���ǩ������");
}

//��껮����Ԫ�أ�����ǣ�����ô˻ص���������a��ǩ��url
void OnwkeMouseOverUrlChanged(wkeWebView webView, void* param, const wkeString url)
{
    //�¼����ƣ������������
    //�¼����ܣ�����ƶ���AԪ�ط�Χ��ʱ����,������AԪ������
    //�������ͣ��޷���ֵ
    //�¼�����<1>������Ϊ��Url��������Ϊ��SDT_TEXT��������ƶ���AԪ�ط�Χ��ʱ����,������AԪ������
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //����ģʽ��ָ����Чֱ�ӷ���
            return;

        _str szUrl = wstr::W2A((LPWSTR)wkeGetStringW(url));

        EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, 0);
        eventInfo.m_nEventIndex = EVENT_MOUSEHOVERURL;
        eventInfo.m_nArgCount = 1;

        eventInfo.m_arg[0].m_inf.m_dtDataType = SDT_TEXT;
        LPCSTR tmp = szUrl.c_str();
        eventInfo.m_arg[0].m_inf.m_pText = (char*)&tmp;
        eventInfo.m_arg[0].m_dwState = EAV_IS_POINTER;

        NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    }
    else
    {
        _JYWKEWEBKIT_EVENT_CALLBACK(13, 1);
        if (fun)
        {
            _str str1 = _str::W2A(wkeGetStringW(url));
            fun(webView, pMem->pCtl->jyEvent.arg[13].arg, (int)str1.c_str());
        }
    }

}

//javascript��v8ִ�л���������ʱ�����˻ص�, ע�⣺ÿ��frame����ʱ���ᴥ���˻ص�
void OnwkeDidCreateScriptContext(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId)
{
}

//ÿ��frame��javascript��v8ִ�л������ر�ʱ�����˻ص�
void OnwkeWillReleaseScriptContext(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int worldId)
{
}



void __fill_wnd_data(PWEBKIT_PROPERTYEX data, wkeWebView webView)
{
    if (!data)return;
    PWEBKIT_CTL wke = data->pCtl;
    wke->isDlg = FALSE;

    wkeOnDocumentReady2(webView,        OnwkeDocumentReady2     , data); // �ĵ�����
    wkeOnTitleChanged(webView,          OnwkeTitleChanged       , data); // ���ⱻ�ı�
    wkeOnURLChanged2(webView,           OnwkeURLChanged2        , data); // URL���ı�
    wkeOnNavigation(webView,            OnwkeNavigation         , data); // �����������µ�ַ
    wkeOnCreateView(webView,            OnwkeCreateView         , data); // �����������´���
    wkeOnLoadingFinish(webView,         OnwkeLoadingFinish      , data); // �ĵ��������
    wkeOnConsole(webView,               OnConsoleMessage        , data); // ��̨��Ϣ���
    wkeOnAlertBox(webView,              OnwkeAlertBox           , data); // Alert��������
    wkeOnConfirmBox(webView,            OnwkeConfirmBox         , data); // Confirm��������
    wkeOnPromptBox(webView,             OnwkePromptBox          , data); // Prompt��������
    wkeOnDownload(webView,              OnwkeDownload           , data); // ���������ļ�
    wkeOnLoadUrlBegin(webView,          OnwkeLoadUrlBegin       , data); // Url���뿪ʼ
    wkeOnLoadUrlEnd(webView,            OnwkeLoadUrlEnd         , data); // Url�������
    wkeOnMouseOverUrlChanged(webView,   OnwkeMouseOverUrlChanged, data); // �����������
    wkeOnWindowClosing(webView,         handleWindowClosing     , data); // �󶨴��ڿɷ�ر��¼�
    wkeOnWindowDestroy(webView,         handleWindowDestroy     , data); // �󶨴��ڼ����������¼�
    wkeSetNavigationToNewWindowEnable(webView, data->prop.isNewWnd);     //�������´���

    wke_SubWebviewWindow(data); // ���໯����, ��ȡ��������Ϣ
}
