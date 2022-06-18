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

    if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == false)    // 有返回值, 且返回值==false
    {
        return TRUE;    // 拦截API操作, 直接返回真
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

    if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == false)    // 有返回值, 且返回值==false
    {
        return TRUE;    // 拦截API操作, 直接返回真
    }
    return GetOpenFileNameW_hook(lpmbp);
}

// 只有用户返回假才返回0,用户没有返回或返回真则返回1,调用失败返回-1,调用失败一般是用户没有定义这个事件
inline static int webkit_notify_wke(PWEBKIT_PROPERTYEX data, int nIndex, int nCount, ...)
{
    EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, nIndex);
    int i;
    va_list vl;
    va_start(vl, nCount);
    eventInfo.m_nArgCount = nCount;
    int nRet = 1;    //赋个初值,只有用户返回假才赋值为0, 0是不继续分派消息
    for (i = 0; i < nCount; i++)
    {
        eventInfo.m_arg[i].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[i].m_inf.m_int = va_arg(vl, int);
    }
    va_end(vl);

    nRet = NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    if (!nRet) return -1;// 事件被吞了,被吞的一般就是用户没有创建这个事件
    if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)    //传递到易语言事件成功且返回了假
        return 0;
    return 1;    //用户没有返回一个值,或者返回的值为真
}


// param = WKECtrl类指针
// 记录事件的来源
// DWORD    m_dwFormID;      // 调用ITF_CREATE_UNIT接口所传递过来的所处窗口ID（dwWinFormID参数）
// DWORD    m_dwUnitID;      // 调用ITF_CREATE_UNIT接口所传递过来的窗口单元ID（dwUnitID参数）
// INT      m_nEventIndex;   //   事件索引（在窗口单元定义信息LIB_DATA_TYPE_INFO中m_pPropertyBegin成员中的位置）

// EVENT_ARG_VALUE m_arg [MAX_EVENT2_ARG_COUNT];  // 记录各参数值。
// EVENT_ARG_VALUE      m_arg [5]; // 记录各参数值，SDT_BOOL 型参数值为 1 或 0。

//!!! 注意下面成员在没有定义返回值的事件处理中无效。
// BOOL     m_blHasRetVal; // 用户事件处理子程序处理完毕事件后是否提供了返回值。
// INT      m_infRetData; // 用户事件处理子程序处理完毕事件后的返回值，逻辑值用数值 0（假） 和 1（真） 返回。

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

    ////设置标题变化的通知回调
    //wkeOnTitleChanged(webView, OnwkeTitleChanged, data);
    //
    ////鼠标划过的元素，如果是，则调用此回调，并发送a标签的url
    //wkeOnMouseOverUrlChanged(webView, OnwkeMouseOverUrlChanged, data);
    //
    ////url改变回调
    ////wkeOnURLChanged(webView, OnwkeURLChanged, pUnit);
    //
    ////url改变回调,和上个接口不同的是，回调多了个参数
    //wkeOnURLChanged2(webView, OnwkeURLChanged2, data);
    //
    ////页面有任何需要刷新的地方，将调用此回调
    ////wkeOnPaintUpdated(webView, OnwkePaintUpdated, pUnit);
    //
    ////页面有任何需要刷新的地方，将调用此回调,回调过来的是填充好像素的buffer，而不是DC。方便嵌入到游戏中做离屏渲染
    ////wkeOnPaintBitUpdated(webView, OnwkePaintBitUpdated, pUnit);
    ////AlertBox 被调用触发
    //wkeOnAlertBox(webView, OnwkeAlertBox, data);
    //
    ////ConfirmBox 被调用触发
    //wkeOnConfirmBox(webView, OnwkeConfirmBox, data);
    //
    ////PromptBox 被调用触发
    //wkeOnPromptBox(webView, OnwkePromptBox, data);
    //
    ////网页开始浏览将触发回调
    //wkeOnNavigation(webView, OnwkeNavigation, data);
    //
    ////网页点击a标签创建新窗口时将触发回调
    //wkeOnCreateView(webView, OnwkeCreateView, data);
    //
    ////对应js里的body onload事件
    ////wkeOnDocumentReady(webView, OnwkeDocumentReady, pUnit);
    //
    ////对应js里的body onload事件,多了wkeWebFrameHandle frameId参数。可以判断是否是主frame
    //wkeOnDocumentReady2(webView, OnwkeDocumentReady2, data);
    //
    ////文档载入完毕
    //wkeOnLoadingFinish(webView, OnwkeLoadingFinish, data);
    //
    //
    ////页面下载事件回调。点击某些链接，触发下载会调用
    //wkeOnDownload(webView, OnwkeDownload, data);
    //
    ////一个网络请求发送后，收到服务器response触发回调
    ////wkeNetOnResponse(webView, OnwkeNetResponse, pUnit);
    //
    ////网页调用console触发
    //wkeOnConsole(webView, OnConsoleMessage, data);
    //
    ////暂时未实现
    ////wkeSetUIThreadCallback(webView, OnwkeCallUiThread, pUnit);
    //
    ////任何网络请求发起前会触发此回调
    //wkeOnLoadUrlBegin(webView, OnwkeLoadUrlBegin, data);
    //
    ////url载入完毕
    //wkeOnLoadUrlEnd(webView, OnwkeLoadUrlEnd, data);
    //
    ////javascript的v8执行环境被创建时触发此回调,注意：每个frame创建时都会触发此回调
    ////wkeOnDidCreateScriptContext(webView, OnwkeDidCreateScriptContext, pUnit);
    //
    ////每个frame的javascript的v8执行环境被关闭时触发此回调
    ////wkeOnWillReleaseScriptContext(webView, OnwkeWillReleaseScriptContext, pUnit);
    //
    ////video等多媒体标签创建时触发此回调
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
        if ((ct->lpcs->style & WS_THICKFRAME) == 0)break;    // 现在的判断方式还是有问题,现在是根据有没有可调边框来判断是否为文件对话框

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
    //事件名称：标题被改变
    //事件介绍：网页标题被改变时触发此事件
    //返回类型：无返回值
    //事件参数<1>的名称为“标题”，类型为“SDT_TEXT”。网页标题被更改时触发
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

//URL改变回调,不带参数
void OnwkeURLChanged(wkeWebView webView, void* param, const wkeString url)
{
}

//URL改变回调,带参数
void OnwkeURLChanged2(wkeWebView webView, void* param, wkeWebFrameHandle frameId, const wkeString url)
{
    //事件名称：URL被改变
    //事件介绍：URL被改变时触发
    //返回类型：无返回值
    //事件参数<1>的名称为“URL”，类型为“SDT_TEXT”。改变的URL
    //事件参数<2>的名称为“所属框架ID”，类型为“SDT_INT”。当前URL属于哪个框架ID
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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


//页面有任何需要刷新的地方，将调用此回调
void OnwkePaintUpdated(wkeWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {

    }
}

//页面有任何需要刷新的地方，将调用此回调,回调过来的是填充好像素的buffer，而不是DC。方便嵌入到游戏中做离屏渲染
void OnwkePaintBitUpdated(wkeWebView webView, void* param, const void* buffer, const wkeRect* r, int width, int height)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {

    }
}

//网页调用alert触发
void OnwkeAlertBox(wkeWebView webView, void* param, const wkeString message)
{
    //事件名称：Alert将被调用
    //事件介绍：当网页中的alert被调用的时候触发
    //返回类型：无返回值
    //事件参数<1>的名称为“消息”，类型为“SDT_TEXT”。即将弹出的消息
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

//ConfirmBox指定消息和 OK 及取消按钮的对话框
bool OnwkeConfirmBox(wkeWebView webView, void* param, const wkeString msg)
{
    //事件名称：Confirm将被调用
    //事件介绍：当网页中的alert被调用的时候触发
    //返回类型：SDT_BOOL
    //事件参数<1>的名称为“消息”，类型为“SDT_TEXT”。即将弹出的消息
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//投递成功,并且用户返回了假
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
    //事件名称：Prompt将被调用
    //事件介绍：当网页中的Prompt被调用的时候触发
    //返回类型：SDT_BOOL
    //事件参数<1>的名称为“提示信息”，类型为“SDT_TEXT”。输入框的提示信息
    //事件参数<2>的名称为“默认值”，类型为“SDT_TEXT”。输入框的默认值

    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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
        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//投递成功,并且用户返回了假
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

//网页开始浏览将触发回调, 即将导航到新地址
bool OnwkeNavigation(wkeWebView webView, void* param, wkeNavigationType navigationType, wkeString url)
{
    //wkeNavigationType: 表示浏览触发的原因。可以取的值有：
    //WKE_NAVIGATION_TYPE_LINKCLICK：点击a标签触发
    //WKE_NAVIGATION_TYPE_FORMSUBMITTE：点击form触发
    //WKE_NAVIGATION_TYPE_BACKFORWARD：前进后退触发
    //WKE_NAVIGATION_TYPE_RELOAD：重新加载触发
    //注意：wkeNavigationCallback回调的返回值，如果是true，表示可以继续进行浏览，false表示阻止本次浏览。

    //事件名称：即将导航到新地址
    //事件介绍：将要导航到新的网址前触发
    //返回类型：SDT_BOOL
    //事件参数<1>的名称为“导航类型”，类型为“SDT_INT”。即将导航的类型  0==单击连接 1==表单提交 2==后退 3==重新载入(刷新) 4==表单重新提交  5==其他类型
    //事件参数<2>的名称为“URL”，类型为“SDT_TEXT”。即将导航的URL
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//投递成功,并且用户返回了假
        {
            if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)//返回值=假
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

    wkeSetWindowTitleW(newWebView, L"精易Web浏览器");
    wkeShowWindow(newWebView, true);
    return newWebView;
}

//网页点击a标签创建新窗口时将触发回调, 即将导航到新窗口
wkeWebView OnwkeCreateView(wkeWebView webView, void* param, wkeNavigationType navigationType, const wkeString url, const wkeWindowFeatures* windowFeatures)
{
    //事件名称：即将导航到新窗口
    //事件介绍：即将导航到新窗口,返回(真) 在当前窗口打开网址,返回(假) 自行处理
    //返回类型：SDT_BOOL
    //事件参数<1>的名称为“导航类型”，类型为“SDT_INT”。即将导航的类型  0==单击连接 1==表单提交 2==后退 3==重新载入(刷新) 4==表单重新提交  5==其他类型
    //事件参数<2>的名称为“URL”，类型为“SDT_TEXT”。即将导航的URL
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return 0;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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
        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//投递成功
        {
            // 用户返回了假,不处理
            if (eventInfo.m_blHasRetVal && eventInfo.m_infRetData.m_bool == FALSE)
                b = FALSE;
        }
        // 用户返回了真,并且允许新窗口打开
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


// 新载入窗口可否关闭
bool handleWindowClosing(wkeWebView webWindow, void* param)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

// 新载入窗口即将销毁
void handleWindowDestroy(wkeWebView webWindow, void* param)
{
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
            return;
        webkit_notify_wke(data, EVENT_NEWWNDDESTROY, 1, (int)webWindow);
    }
    return;
}


//对应js里的body onload事件,无框架ID,文档就绪
void OnwkeDocumentReady(wkeWebView webView, void* param)
{
}

//对应js里的body onload事件,有框架ID,文档就绪
void OnwkeDocumentReady2(wkeWebView webView, void* param, wkeWebFrameHandle frameId)
{
    //事件名称：文档就绪
    //事件介绍：文档就绪时触发
    //返回类型：无返回值
    //事件参数<1>的名称为“就绪框架ID”，类型为“SDT_INT”。网页文档就绪或内部框架就绪时触发
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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
    //事件名称：文档载入完毕
    //事件介绍：文档载入完毕时触发
    //返回类型：无返回值
    //事件参数<1>的名称为“载入URL”，类型为“SDT_TEXT”。载入完毕的URL
    //事件参数<2>的名称为“载入状态”，类型为“SDT_INT”。载入的状态  0==载入成功 1==载入失败 2==取消载入
    //事件参数<3>的名称为“失败原因”，类型为“SDT_TEXT”。当文档载入失败时,输出失败原因
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        _str szUrl, szfailedReason;
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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
        //事件名称：网页图标改变
        //事件介绍：网页图标改变时触发
        //返回类型：无返回值
        //事件参数<1>的名称为“URL”，类型为“SDT_TEXT”
        //事件参数<2>的名称为“图标指针”，类型为“SDT_INT”。指向图标数据的地址
        //事件参数<3>的名称为“图标长度”，类型为“SDT_INT”。图标长度

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


//页面下载事件回调。点击某些链接，触发下载会调用
bool OnwkeDownload(wkeWebView webView, void* param, const char* url)
{
    //事件名称：正在下载文件
    //事件介绍：正在下载文件时触发本事件
    //返回类型：SDT_BOOL
    //事件参数<1>的名称为“文件URL”，类型为“SDT_TEXT”。准备下载的文件URL
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//投递成功,并且用户返回了假
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

//一个网络请求发送后，收到服务器response触发回调
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

//网页调用console触发
//事件名称：控台消息输出
//事件介绍：当产生控制台消息时触发
//返回类型：无返回值
//事件参数<1>的名称为“级别”，类型为“SDT_INT”。消息级别 , #消息级别_ 开头的常量
//事件参数<2>的名称为“行号”，类型为“SDT_INT”。消息产生的行号
//事件参数<3>的名称为“消息”，类型为“SDT_TEXT”。控制台消息
//事件参数<4>的名称为“来源名称”，类型为“SDT_TEXT”。来源名称
//事件参数<5>的名称为“堆栈跟踪”，类型为“SDT_TEXT”。来源名称
void OnConsoleMessage(wkeWebView webView, void* param, wkeConsoleLevel level, const wkeString message, const wkeString sourceName, unsigned sourceLine, const wkeString stackTrace)
{
    char* sz = "onConsoleMessageonConsoleMessageonConsoleMessageonConsoleMessageonConsoleMessageonConsoleMessageonConsoleMessage";
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        SendCallBack(data, param, level, message, sourceName, sourceLine, stackTrace);
        return;
        // 需要写到一个子程序中，如果写到下面，就会错乱
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

//暂时未实现
void OnwkeCallUiThread(wkeWebView webView, wkeOnCallUiThread func, void* param)
{
}

//任何网络请求发起前会触发此回调
bool OnwkeLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job)
{
    //参数：typedef bool(*wkeLoadUrlBeginCallback)(wkeWebView webView, void* param, const char *url, void *job)
    //注意：
    //1，此回调功能强大，在回调里，如果对job设置了wkeNetHookRequest，则表示mb会缓存获取到的网络数据，并在这次网络请求 结束后调用wkeOnLoadUrlEnd设置的回调，同时传递缓存的数据。在此期间，mb不会处理网络数据。
    //2，如果在wkeLoadUrlBeginCallback里没设置wkeNetHookRequest，则不会触发wkeOnLoadUrlEnd回调。
    //3，如果wkeLoadUrlBeginCallback回调里返回true，表示mb不处理此网络请求（既不会发送网络请求）。返回false，表示mb依然会发送网络请求。

    //事件名称：Url载入开始
    //事件介绍：Url开始载入
    //返回类型：SDT_BOOL
    //事件参数<1>的名称为“Url”，类型为“SDT_TEXT”。要载入的URL
    //事件参数<2>的名称为“Job”，类型为“SDT_INT”。Job
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return false;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

        if (NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0))//投递成功,并且用户返回了假
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

//载入url完毕
void OnwkeLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len)
{
    //事件名称：Url载入结束
    //事件介绍：Url载入结束
    //返回类型：无返回值
    //事件参数<1>的名称为“Url”，类型为“SDT_TEXT”。要载入的URL
    //事件参数<2>的名称为“Job”，类型为“SDT_INT”。Job
    //事件参数<3>的名称为“数据字节集指针”，类型为“SDT_INT”。请使用 指针到字节集() 命令获取
    //事件参数<4>的名称为“数据长度”，类型为“SDT_INT”。数据长度
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

//video等多媒体标签创建时触发此回调
void OnwkeWillMediaLoad(wkeWebView webView, void* param, const char* url, wkeMediaLoadInfo* info)
{
    OutputDebugStringA("video等多媒体标签被创建");
}

//鼠标划过的元素，如果是，则调用此回调，并发送a标签的url
void OnwkeMouseOverUrlChanged(wkeWebView webView, void* param, const wkeString url)
{
    //事件名称：鼠标移入链接
    //事件介绍：鼠标移动到A元素范围内时触发,并传入A元素连接
    //返回类型：无返回值
    //事件参数<1>的名称为“Url”，类型为“SDT_TEXT”。鼠标移动到A元素范围内时触发,并传入A元素连接
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)param;
    if (!data)return;
    if ( __query(data->flags, EVENT_PTR_E) )
    {
        
        if ( data->blInDesignMode )    //调试模式或指针无效直接返回
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

//javascript的v8执行环境被创建时触发此回调, 注意：每个frame创建时都会触发此回调
void OnwkeDidCreateScriptContext(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId)
{
}

//每个frame的javascript的v8执行环境被关闭时触发此回调
void OnwkeWillReleaseScriptContext(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int worldId)
{
}



void __fill_wnd_data(PWEBKIT_PROPERTYEX data, wkeWebView webView)
{
    if (!data)return;
    PWEBKIT_CTL wke = data->pCtl;
    wke->isDlg = FALSE;

    wkeOnDocumentReady2(webView,        OnwkeDocumentReady2     , data); // 文档就绪
    wkeOnTitleChanged(webView,          OnwkeTitleChanged       , data); // 标题被改变
    wkeOnURLChanged2(webView,           OnwkeURLChanged2        , data); // URL被改变
    wkeOnNavigation(webView,            OnwkeNavigation         , data); // 即将导航到新地址
    wkeOnCreateView(webView,            OnwkeCreateView         , data); // 即将导航到新窗口
    wkeOnLoadingFinish(webView,         OnwkeLoadingFinish      , data); // 文档载入完毕
    wkeOnConsole(webView,               OnConsoleMessage        , data); // 控台消息输出
    wkeOnAlertBox(webView,              OnwkeAlertBox           , data); // Alert将被调用
    wkeOnConfirmBox(webView,            OnwkeConfirmBox         , data); // Confirm将被调用
    wkeOnPromptBox(webView,             OnwkePromptBox          , data); // Prompt将被调用
    wkeOnDownload(webView,              OnwkeDownload           , data); // 正在下载文件
    wkeOnLoadUrlBegin(webView,          OnwkeLoadUrlBegin       , data); // Url载入开始
    wkeOnLoadUrlEnd(webView,            OnwkeLoadUrlEnd         , data); // Url载入结束
    wkeOnMouseOverUrlChanged(webView,   OnwkeMouseOverUrlChanged, data); // 鼠标移入链接
    wkeOnWindowClosing(webView,         handleWindowClosing     , data); // 绑定窗口可否关闭事件
    wkeOnWindowDestroy(webView,         handleWindowDestroy     , data); // 绑定窗口即将被销毁事件
    wkeSetNavigationToNewWindowEnable(webView, data->prop.isNewWnd);     //允许窗口新窗打开

    wke_SubWebviewWindow(data); // 子类化窗口, 获取鼠标键盘消息
}
