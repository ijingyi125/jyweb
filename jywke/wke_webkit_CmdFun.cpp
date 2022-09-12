#include "wke_webkit_header.h"
#include "CwkeTBInfo.h"
#include "wke_webkit_event.h"


PWEBKIT_PROPERTYEX wke_wkectrl(PMDATA_INF pArgInf, HWND* pHwnd)
{
    PWEBKIT_PROPERTYEX data = 0;
    if ( pArgInf->m_unit.m_dwUnitID )
    {
        // 不等于0,是组件,=0是数据类型
        data = (PWEBKIT_PROPERTYEX)GetWebkitDataFromArg(pArgInf);
    }
    else
    {
        // 走到这就是数据类型
        data = (PWEBKIT_PROPERTYEX)*pArgInf[0].m_ppCompoundData;
    }

    if ( data && pHwnd )	// 是新窗口的数据
    {
        if ( pHwnd )
            *pHwnd = data->hWnd;
    }
    return data;
}

#define WKE_CTRL(_pHwnd) PWEBKIT_PROPERTYEX data = wke_wkectrl(pArgInf, _pHwnd); if(!data) return; PWEBKIT_CTL wke = data->pCtl













// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).浏览网页, 命令说明: "浏览指定网页。"
// 参数<1>: URL地址 SDT_TEXT, 参数说明: "即将浏览的URL地址,如果url地址有中文,请传递utf8编码文本."
EXTERN_C void WKE_NAME(0, SetUrl)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->LoadURL(pArgInf[1].m_pText);
}

// 调用格式: SDT_TEXT (精易Web浏览器/弹出窗口操作).取网页URL, 命令说明: "获取当前网页URL地址。"
// 无参数
EXTERN_C void WKE_NAME(1, GetUrl)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    LPCSTR szUrl = wke->GetUrl();
    pRetData->m_dtDataType = SDT_TEXT;
    pRetData->m_pText = CloneTextData((char*)szUrl);

}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).载入HTML文本, 命令说明: "载入HTML代码文本。注意，如果网页代码中需要编码，则需要自行进行编码转换。"
// 参数<1>: HTML文本 SDT_TEXT, 参数说明: "一段HTML文本,请传递与网页相同编码的文本."
EXTERN_C void WKE_NAME(2, wke_LoadHtml)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->LoadHTML(pArgInf[1].m_pText);
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).载入HTML文件, 命令说明: "载入HTML文件。"
// 参数<1>: HTML文件 SDT_TEXT, 参数说明: "HTML文件名,如果路径有中文,请传递utf8编码文本."
EXTERN_C void WKE_NAME(3, wke_LoadFile)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->LoadFile(pArgInf[1].m_pText);
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).前进, 命令说明: "浏览器前进命令。"
// 无参数
EXTERN_C void WKE_NAME(4, wke_GoForward)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

    WKE_CTRL(0);
    wke->GoForward();
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).后退, 命令说明: "浏览器后退命令。"
// 无参数
EXTERN_C void WKE_NAME(5, wke_CanGoBack)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

    WKE_CTRL(0);
    wke->GoBack();
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).停止载入, 命令说明: "停止加载当前网页。"
// 无参数
EXTERN_C void WKE_NAME(6, wke_StopLoading)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->StopLoading();
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).重新载入, 命令说明: "重新载入当前网页,相当于刷新命令。"
// 无参数
EXTERN_C void WKE_NAME(7, wke_Reload)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->Reload();
}

inline void __fun_webkie_makejs(_str& retStr, wkeWebView webView, int frameID, int mode, const char* name, int index, const char* jsCode)
{
    CwkeTBInfo js;		// 执行js

    if ( mode <= 0 ) mode = 2;
    if ( index <= 0 )index = 1;


    int frameCount = js.form_GetFrameCount(webView);	// 框架数量
    name = ( name && name[0] ) ? name : "html";

    if ( frameID > frameCount ) frameID = frameCount;

    js.form_SetFrame(webView, mode, name, frameID);
    _str str(2000);
    str.assign("return ").append(js.CreateElementSelectorStr(webView, mode, name, index));
    str.append(".").append(jsCode);
    jsValue vl = js.RunJS(webView, str);
    jsExecState es = wkeGlobalExec(webView);
    retStr = jsToString(es, vl);	// 指定框架就取这个框架指定元素的网页文本,未指定元素就默认取 html,然后返回
}

// 调用格式: SDT_TEXT (精易Web浏览器/弹出窗口操作).取网页源码, 命令说明: "返回当前网页源码,如果出现乱码,请使用 \"wke_Utf8ToAnsi()\" 转换。"
// 参数<1>: [框架ID SDT_INT], 参数说明: "ID从1开始,为空或者小于0,默认取主框架"
// 参数<2>: [填表模式 SDT_INT], 参数说明: "默认为 #填表模式_JS表达式, 请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: [选择表达式 SDT_TEXT], 参数说明: "为空则取整个网页,选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(8, GetWebPageSource)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    _str ret;			// 需要执行的js代码
    __fun_webkie_makejs(ret, wke->GetWkeWebView(), pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, "outerHTML");
    pRetData->m_pText = CloneTextData((char*)ret.c_str());	//返回utf8
}



// 调用格式: SDT_TEXT (精易Web浏览器/弹出窗口操作).获取Cookie, 命令说明: "获取当前网页的Cookie。"
// 无参数
EXTERN_C void WKE_NAME(9, wke_GetCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    LPCSTR szCookie = wke->GetCookie();
    pRetData->m_dtDataType = SDT_TEXT;
    pRetData->m_pText = CloneTextData((char*)szCookie);
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).设置Cookie_此命令已弃用_请调用_设置cookie_CURL_来设置_设置cookie_CURL是node_dll提供的接口_没有任何二次封装, 命令说明: "支持库不提供任何针对cookie进行二次封装的命令, 所有cookie相关的命令都是原封调用node.dll\r\n        设置cookie请调用 设置cookie_CURL(), 该命令原封调用node.dll的wkeSetCookie接口\r\n"
// 参数<1>: URL SDT_TEXT, 参数说明: "待设置cookie的网站域名,如果url地址有中文,请传递utf8编码文本."
// 参数<2>: COOKIE SDT_TEXT, 参数说明: "要设置的Cookie，多个cookie使用;隔开，例如： a=1;b=2;c=3;d=4;"
EXTERN_C void WKE_NAME(10, wke_SetCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    MessageBoxW(0, L"支持库不提供任何针对cookie进行二次封装的命令, 所有cookie相关的命令都是原封调用node.dll\r\n"
                L"设置cookie请调用 设置cookie_CURL(), 该命令原封调用node.dll的wkeSetCookie接口\r\n"
                L"cookie相关问题不再回答", L"已弃用的命令", 0);
    return;

    //WKE_CTRL(0);
    //_str cookie(pArgInf[2].m_pText);
    //LPSTR p = strtok(cookie.GetPtr(), ";");
    //_str s1;
    //if (pArgInf[1].m_dtDataType == _SDT_NULL)
    //{
    //	s1 = ";PRODUCTINFO=webxpress; path=/; secure";
    //}
    //else
    //{
    //	s1 = _str(";PRODUCTINFO=webxpress; domain=") + pArgInf[1].m_pText + "; path=/; secure";
    //}
    ////_str s1(";PRODUCTINFO=webxpress; path=/; secure");
    //const wchar_t* jsCode =
    //    L"function clearAllCookie() {"
    //    L"    var keys = document.cookie.match(/[^ =;]+(?=\\=)/g);"
    //    L"    if(keys) {"
    //    L"        for(var i = keys.length; i--;)"
    //    L"            document.cookie = keys[i] + '=0;expires=' + new Date(0).toUTCString();"
    //    L"    }"
    //    L"} clearAllCookie();";

    //////wke->RunJS(L"$.removeCookie('jy',{ path: '/'});");	// 清除原有cookie
    ////wke->RunJS(jsCode);	// 清除原有cookie
    ////wke->ClearCookie();

    //while (p)
    //{
    //	//TODO 设置cookie还没处理好
    //	_str tmp(p);
    //	//tmp.replace(' ', 0);
    //	_str s2(tmp + s1);

    //	wke->SetCookie(pArgInf[1].m_pText, s2.c_str());
    //	p = strtok(NULL, ";");
    //}


    ////wkeSetCookie(webView, "localhost", "a=1;PRODUCTINFO=webxpress; domain=.localhost; path=/; secure");
    ////wkeSetCookie(webView, "localhost", "b=2;PRODUCTINFO=webxpress; domain=.localhost; path=/; secure");
    ////wkeSetCookie(webView, "localhost", "c=3;PRODUCTINFO=webxpress; domain=.localhost; path=/; secure");
    ////wkeSetCookie(webView, "localhost", "d=4;expires=Monday, 13-Jun-2022 03:04:55 GMT; domain=.localhost; path=/; secure");
    //// name=value; Domain=Domain; Path=httponly;secure
    ////var tmp = string.Format("{0}={1}; Domain={2}; {3} Path={4}", item.Name, item.Value, item.Domain, ((item.HttpOnly) ? "httponly; " : ""), (item.Secure ? "secure" : ""));

}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).执行Cookie命令, 命令说明: "执行cookie相关命令。"
// 参数<1>: 操作类型 SDT_INT, 参数说明: "0 = 清空所有Cookie , 1 = 清空所有session , 2 = 刷新cookie文件  3= 重新载入cookie文件"
EXTERN_C void WKE_NAME(11, wke_ExecuteCookeCommand)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    switch ( pArgInf[1].m_int )
    {
    case 0:
        //wke->RunJS(L"$.removeCookie('name',{ path: '/'});");	// 清除原有cookie
        wke->PerformCookieCommand(wkeCookieCommandClearAllCookies);
        break;
    case 1:
        wke->PerformCookieCommand(wkeCookieCommandClearSessionCookies);
        break;
    case 2:
        wke->PerformCookieCommand(wkeCookieCommandFlushCookiesToFile);
        break;
    case 3:
        wke->PerformCookieCommand(wkeCookieCommandReloadCookiesFromFile);
        break;
    default:
        wke->PerformCookieCommand(wkeCookieCommandClearAllCookies);
    }
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).设置UserAgent, 命令说明: "设置浏览器默认的UserAgent。"
// 参数<1>: UserAgent SDT_TEXT, 参数说明: "UserAgent文本,如果url地址有中文,请传递utf8编码文本."
EXTERN_C void WKE_NAME(12, wke_SetUserAgent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->SetUserAgent(pArgInf[1].m_pText);
}

// 调用格式: SDT_BOOL (精易Web浏览器/弹出窗口操作).设置代理, 命令说明: "为指定的webView设置代理。"
// 参数<1>: 代理类型 SDT_INT, 参数说明: "#代理类型_开头的常量"
// 参数<2>: 代理地址 SDT_TEXT, 参数说明: "代理ip与端口,如 122.132.123.123:666"
// 参数<3>: [用户名 SDT_TEXT], 参数说明: "代理用户名,没有请留空"
// 参数<4>: [密码 SDT_TEXT], 参数说明: "代理密码,没有请留空"
EXTERN_C void WKE_NAME(13, SetProxy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = FALSE;
    wkeProxy proxy;
    memset(&proxy, 0, sizeof(wkeProxy));
    proxy.type = (wkeProxyType)( pArgInf[1].m_int );
    _str str(pArgInf[2].m_pText), IP, port;
    IP = str.left(":");
    port = str.right(":");
    //if (IP == "" || port == "") return;

    if ( !IP.empty() )
        strcpy(proxy.hostname, IP.c_str());	//代理地址
    proxy.port = port.stoi();	//端口

    if ( pArgInf[3].m_pText && *( pArgInf[3].m_pText ) )
        strcpy(proxy.username, pArgInf[3].m_pText);

    if ( pArgInf[4].m_pText != NULL && *( pArgInf[4].m_pText ) )
        strcpy(proxy.password, pArgInf[4].m_pText);

    wke->SetProxy(&proxy);
    pRetData->m_bool = TRUE;
}

// 调用格式: SDT_FLOAT (精易Web浏览器/弹出窗口操作).设置网页音量, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(14, SetWebVolume)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    // UNDONE 设置网页音量,wke未实现
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).设置媒体音量, 命令说明: "设置网页媒体音量。"
// 参数<1>: 音量 SDT_INT, 参数说明: "欲设置的音量"
EXTERN_C void WKE_NAME(15, SetMediVolume)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    // UNDONE wkeSetMediaVolume 设置媒体音量,wke未实现
}

// 调用格式: SDT_INT (精易Web浏览器/弹出窗口操作).取WebView, 命令说明: "返回WebView指针。"
// 无参数
EXTERN_C void WKE_NAME(16, GetWebView)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_int = (int)wke->GetWkeWebView();
}

// 调用格式: SDT_BOOL (精易Web浏览器/弹出窗口操作).是否可以前进, 命令说明: "返回浏览器是否可以执行前进命令。"
// 无参数
EXTERN_C void WKE_NAME(17, IsGoRorward)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = wke->CanGoForward();
}

// 调用格式: SDT_BOOL (精易Web浏览器/弹出窗口操作).是否可以后退, 命令说明: "返回浏览器是否可以执行后退命令。"
// 无参数
EXTERN_C void WKE_NAME(18, CanGoBack)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = wke->CanGoBack();
}

// 调用格式: SDT_BOOL (精易Web浏览器/弹出窗口操作).是否加载完成, 命令说明: "返回网页是否加载完成。"
// 无参数
EXTERN_C void WKE_NAME(19, IsLodingCompleted)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = wke->IsLoadingCompleted();
}

// 调用格式: SDT_BOOL (精易Web浏览器/弹出窗口操作).文档是否就绪, 命令说明: "返回文档是否已就绪。"
// 无参数
EXTERN_C void WKE_NAME(20, IsDocumentReady)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = wke->IsDocumentReady();
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).延时回收垃圾, 命令说明: "延迟让miniblink垃圾回收。"
// 参数<1>: 延时时长 SDT_INT, 参数说明: "单位毫秒,延迟让miniblink垃圾回收"
EXTERN_C void WKE_NAME(154, wkeGC)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->GC(pArgInf[1].m_int);
}

// 调用格式: SDT_BOOL (精易Web浏览器/弹出窗口操作).置用户数据, 命令说明: "把数据和webView绑定。"
// 参数<1>: 键名 SDT_TEXT, 参数说明: "设置键名后可通过这个键名取到设置的值"
// 参数<2>: 键值 SDT_INT, 参数说明: "需要设置的键值"
EXTERN_C void WKE_NAME(157, wke_SetUserKeyValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->SetUserKeyValue(pArgInf[1].m_pText, (void*)pArgInf[2].m_int);
}

// 调用格式: SDT_INT (精易Web浏览器/弹出窗口操作).取用户数据, 命令说明: "取出 置用户数据() 设置的值。"
// 参数<1>: 键名 SDT_TEXT, 参数说明: "置用户数据() 里设置的键名"
EXTERN_C void WKE_NAME(158, wke_GetUserKeyValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_int = (int)wke->GetUserKeyValue(pArgInf[1].m_pText);
}

// 调用格式: SDT_INT 取网页句柄, 命令说明: "取出 miniblink 的窗口句柄。"
// 无参数
EXTERN_C void WKE_NAME(159, wke_GetWindowHandle)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    HWND hWnd = 0;
    WKE_CTRL(&hWnd);
    pRetData->m_int = (int)hWnd;
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).设置Cookie_单条_此命令已弃用_请调用_设置cookie_CURL_来设置_设置cookie_CURL是node_dll提供的接口_没有任何二次封装, 命令说明: "支持库不提供任何针对cookie进行二次封装的命令, 所有cookie相关的命令都是原封调用node.dll\r\n        设置cookie请调用 设置cookie_CURL(), 该命令原封调用node.dll的wkeSetCookie接口\r\n"
// 参数<1>: URL SDT_TEXT, 参数说明: "待设置cookie的网站域名,如果url地址有中文,请传递utf8编码文本."
// 参数<2>: COOKIE SDT_TEXT, 参数说明: "要设置的Cookie，格式需要相与curl的格式。例如：abc=1;expires=Monday, 1-Jun-2019 00:01:01 GMT; path=/; secure"
EXTERN_C void WKE_NAME(161, wke_SetSingleCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //WKE_CTRL(0);
    ////_str s1(_str("a=1;PRODUCTINFO=webxpress; domain=.") + pArgInf[1].m_pText + "baidu.com; path=/; secure");
    //_str cook(_str(pArgInf[2].m_pText) + ";PRODUCTINFO=webxpress; domain=." + pArgInf[1].m_pText + "; path=/; secure");
    //wke->SetCookie(pArgInf[1].m_pText, cook.c_str());
    MessageBoxW(0, L"支持库不提供任何针对cookie进行二次封装的命令, 所有cookie相关的命令都是原封调用node.dll\r\n"
                L"设置cookie请调用 设置cookie_CURL(), 该命令原封调用node.dll的wkeSetCookie接口\r\n"
                L"cookie相关问题不在回答", L"已弃用的命令", 0);
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).清除所有cookie, 命令说明: "清除当前wke的所有cookie。"
// 无参数
EXTERN_C void WKE_NAME(166, wke_clearCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    //wke->RunJS(L"$.removeCookie('name',{ path: '/'});");	// 清除原有cookie
    wke->ClearCookie();
}

// 调用格式: SDT_BOOL (精易Web浏览器/弹出窗口操作).允许新窗打开, 命令说明: "不设置默认为假,都在本窗口打开,不触发 \"即将导航到新窗口\" 事件\r\n    为真时会触发 \"即将导航到新窗口\" 事件\r\n    如果网页用js hook了点击事件,然后用window.open打开,那么 禁止新窗打开() 对这个无效,禁止后还是会弹出新窗口\r\n    不需要新窗口打开的可以在 即将导航到新窗口 事件下返回 \"假\",不让他弹出\r\n    为空则取当前状态, 不为空时返回值无意义。\r\n"
// 参数<1>: [是否禁止 SDT_BOOL], 参数说明: "真 = 禁止, 假 = 不禁止, 留空 = 取值, 该参数不为空时返回值无意义。"
EXTERN_C void WKE_NAME(168, wke_IsEnableNewWnd)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    bool b = (bool)pArgInf[1].m_bool;
    WKE_CTRL(0);
    wke->SetNavigationToNewWindowEnable(b);
    data->prop.isNewWnd = b;
}

HBITMAP wke_Create32Bitmap(HDC hdc, int width, int height)
{
    BITMAPINFO bm = { 0 };
    bm.bmiHeader.biSize = 44;
    bm.bmiHeader.biWidth = width;
    bm.bmiHeader.biHeight = height;
    bm.bmiHeader.biPlanes = 1;
    bm.bmiHeader.biBitCount = 32;
    bm.bmiHeader.biSizeImage = bm.bmiHeader.biWidth * bm.bmiHeader.biHeight * bm.bmiHeader.biBitCount / 8;
    void* p;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bm, 0, &p, 0, 0);
    return hBitmap;
}

LPBYTE wke_saveBitmap(HDC hdc, HBITMAP hBitmap, int& dwSize)
{
    BITMAP bitmap = { 0 };
    if ( !GetObject(hBitmap, sizeof(bitmap), &bitmap) )
        return NULL;
    BITMAPFILEHEADER* head_file = 0;
    BITMAPINFOHEADER* head_info = 0;
    LPBYTE pMem = 0;	// 返回值,记录整张位图

    int nWidth = bitmap.bmWidth, nHeight = bitmap.bmHeight;
    int nPlanes = bitmap.bmPlanes, bitCount = bitmap.bmBitsPixel;

    int dwBitsSize = nWidth * nHeight * bitCount / 8; // 位图数据大小

    // 生成的位图文件大小 = 位图数据大小 + 文件头信息 + 位图信息头
    dwSize = dwBitsSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    pMem = new BYTE[dwSize];
    memset(pMem, 0, dwSize);

    head_file = (BITMAPFILEHEADER*)pMem;
    head_file->bfType = 0x4D42;	//19778	位图文件头标志,"BM" 
    head_file->bfSize = dwSize;	// 生成的文件大小
    head_file->bfReserved1 = 0;	// 保留
    head_file->bfReserved2 = 0;	// 保留
    head_file->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	// 图像数据偏移

    head_info = (BITMAPINFOHEADER*)( pMem + sizeof(BITMAPFILEHEADER) );	// 跳过文件头结构长度

    head_info->biSize = sizeof(BITMAPINFOHEADER);
    head_info->biWidth = bitmap.bmWidth;
    head_info->biHeight = bitmap.bmHeight;
    head_info->biPlanes = bitmap.bmPlanes;
    head_info->biBitCount = bitmap.bmBitsPixel;

    GetDIBits(hdc, hBitmap, 0, bitmap.bmHeight, pMem + ( head_file->bfOffBits ), (BITMAPINFO*)head_info, NULL);
    return pMem;
}

// 调用格式: SDT_BIN (精易Web浏览器/弹出窗口操作).截图, 命令说明: "截图指定区域或者整个浏览器"
// 参数<1>: [左边 SDT_INT], 参数说明: "留空或者小于0 = 0, 默认为0"
// 参数<2>: [顶边 SDT_INT], 参数说明: "留空或者小于0 = 0, 默认为0"
// 参数<3>: [宽度 SDT_INT], 参数说明: "留空或者小于0 = 浏览器宽度,默认为浏览器宽度"
// 参数<4>: [高度 SDT_INT], 参数说明: "留空或者小于0 = 浏览器高度,默认为浏览器高度"
EXTERN_C void WKE_NAME(171, wke_screenshot)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    HWND hWnd = 0;
    WKE_CTRL(&hWnd);
    HDC hdc = wke->GetViewDC();
    RECT rc = { 0 };
    GetClientRect(hWnd, &rc);
    rc.right = rc.right - rc.left;
    rc.bottom = rc.bottom - rc.top;

    if ( pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_int > 0 ) rc.left = pArgInf[1].m_int;
    if ( pArgInf[2].m_dtDataType != _SDT_NULL && pArgInf[2].m_int > 0 ) rc.top = pArgInf[2].m_int;
    if ( pArgInf[3].m_dtDataType != _SDT_NULL && pArgInf[3].m_int > 0 ) rc.right = pArgInf[3].m_int;
    if ( pArgInf[4].m_dtDataType != _SDT_NULL && pArgInf[4].m_int > 0 ) rc.bottom = pArgInf[4].m_int;

    HDC hDCMem = CreateCompatibleDC(0);
    HBITMAP hBitmap = wke_Create32Bitmap(hDCMem, rc.right, rc.bottom);
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(hDCMem, hBitmap);

    // 从MB的dc中拷贝指定位置到自己创建的dc中
    BitBlt(hDCMem, 0, 0, rc.right, rc.bottom, hdc, rc.left, rc.top, SRCCOPY);

    int dwSize = 0;
    LPBYTE pMem = wke_saveBitmap(hDCMem, hBitmap, dwSize);

    pRetData->m_pBin = CloneBinData(pMem, dwSize);
    delete[] pMem;
    SelectObject(hDCMem, hBitmapOld);
    DeleteObject(hBitmap);
    DeleteDC(hDCMem);
}

// 调用格式: SDT_TEXT (精易Web浏览器/弹出窗口操作).取网页文本, 命令说明: "取指定框架指定元素或者取整个html的文本,不包含html标记"
// 参数<1>: [框架ID SDT_INT], 参数说明: "ID从1开始,为空或者小于0,默认取主框架"
// 参数<2>: [填表模式 SDT_INT], 参数说明: "默认为 #填表模式_JS表达式, 请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: [选择表达式 SDT_TEXT], 参数说明: "为空则取整个网页,选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(180, wke_GetInnerText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    _str ret;			// 需要执行的js代码
    __fun_webkie_makejs(ret, wke->GetWkeWebView(), pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, "outerText");
    pRetData->m_pText = CloneTextData((char*)ret.c_str());	//返回utf8
}

// 调用格式: SDT_BOOL (弹出窗口操作).附加, 命令说明: "将一个webView附加到本对象中,附加后可以使用本对象的任何方法, 成功返回真, 失败返回假"
// 参数<1>: [weiView SDT_INT], 参数说明: "为空或者为0,则清除附加,非0值如果不是一个webView则调用失败,新窗口创建完毕 事件中的webView,或者其他方式获取到的webView"
EXTERN_C void WKE_NAME(182, Attach)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = FALSE;
    if ( pArgInf[1].m_int == 0 || pArgInf[1].m_dtDataType == _SDT_NULL )
    {
        pArgInf[0].m_ppCompoundData[0] = 0;
        pRetData->m_bool = TRUE;
        return;
    }
    wkeWebView webView = (wkeWebView)pArgInf[1].m_int;
    HWND hWnd = wkeGetWindowHandle(webView);
    if ( !hWnd ) return;

    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)GetWebkitDataFromHwnd(hWnd);
    if ( !data )return;

    pArgInf[0].m_ppCompoundData[0] = data;
    pRetData->m_bool = TRUE;
}

// 调用格式: _SDT_NULL (弹出窗口操作).新窗口构造函数, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(183, newWndIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //MessageBoxA(0, "构造函数", "初始化", 0);
    //LPWKECtrl wke = new WKECtrl;
    pArgInf[0].m_ppCompoundData[0] = 0;
    //wke->pThis = pArgInf[0].m_ppCompoundData;
    return;
}

// 调用格式: _SDT_NULL (弹出窗口操作).新窗口复制构造函数, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(184, newWndCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //MessageBoxA(0, "复制构造函数", "初始化", 0);

    //假设在易中A=B,pArgInf[0]是A   
    //CwkeTBInfo* pA= (CwkeTBInfo*)*pArgInf[0].m_ppCompoundData;  
    //CwkeTBInfo* pB= (CwkeTBInfo*)*pArgInf[1].m_ppCompoundData;  
    //绝对不能直接把B指针赋值给A   
}

// 调用格式: _SDT_NULL (弹出窗口操作).新窗口析构函数, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(185, newWndDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //MessageBoxA(0, "析构函数", "初始化", 0);

    pArgInf[0].m_ppCompoundData[0] = 0;
}

// 调用格式: SDT_BOOL (弹出窗口操作).是否已创建, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(186, newWndIsCreate)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = FALSE;
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)pArgInf[0].m_ppCompoundData[0];
    if ( !data )return;	// 指针为空则表示未初始化

    if ( !( data->hWnd ) || !data->pCtl->WebView() ) return;		// 没有保存窗口或webView也是未初始化
    if ( !IsWindow(data->hWnd) )return;	// 窗口不是有效的句柄,也是未初始化

    pRetData->m_bool = TRUE;	// 走到这才是已经初始化
}

// 调用格式: _SDT_NULL (弹出窗口操作).销毁, 命令说明: "用于销毁新弹出的窗口"
// 无参数
EXTERN_C void WKE_NAME(187, wke_DestroyWebView)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->DestroyWebWindow();
    pArgInf[0].m_ppCompoundData[0] = 0;
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).设置cookie_CURL, 命令说明: "调用node.dll的 wkeSetCookie, 不对参数做任何修改, 支持库所有cookie相关的命令都是原封调用node.dll, 不会做任何修改"
// 参数<1>: [url SDT_TEXT], 参数说明: "待设置cookie的网站域名,如果url地址有中文,请传递utf8编码文本."
// 参数<2>: [cookie SDT_TEXT], 参数说明: "待设置的cookie, cookie必须符合curl的cookie写法"
EXTERN_C void WKE_NAME(188, wke_SetCookieCURL)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->SetCookie(pArgInf[1].m_pText, pArgInf[2].m_pText);
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).模拟硬件设备环境, 命令说明: "设置mb模拟的硬件设备环境。主要用在伪装手机设备场景"
// 参数<1>: 设备字符串 SDT_TEXT, 参数说明: "设备的字符串。可取值有：\r\n\t1. \"navigator.maxTouchPoints\"此时 \"整数参数\" 需要被设置，表示 touch 的点数。\r\n\t2. \"navigator.platform\"此时 \"文本参数\" 需要被设置，表示js里获取的 navigator.platform字符串。\r\n\t3. \"navigator.hardwareConcurrency\"此时 \"整数参数\" 需要被设置，表示js里获取的 navigator.hardwareConcurrency 整数值。\r\n\t4. \"screen.width\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.width 整数值。\r\n\t5. \"screen.height\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.height 整数值。\r\n\t6. \"screen.availWidth\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.availWidth 整数值。\r\n\t7. \"screen.availHeight\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.availHeight 整数值。\r\n\t8. \"screen.pixelDepth\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.pixelDepth 整数值。\r\n\t9. \"screen.pixelDepth\"目前等价于\"screen.pixelDepth\"。\r\n\t10.\"window.devicePixelRatio\"同上"
// 参数<2>: [文本参数 SDT_TEXT], 参数说明: "文本参数"
// 参数<3>: [整数参数 SDT_INT], 参数说明: "整数参数"
// 参数<4>: [浮点参数 SDT_FLOAT], 参数说明: "浮点参数"
EXTERN_C void WKE_NAME(189, wke_SetDeviceParameter)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->SetDeviceParameter(pArgInf[1].m_pText, pArgInf[2].m_pText, pArgInf[3].m_int, pArgInf[4].m_float);
}

// 调用格式: SDT_BOOL (弹出窗口操作).挂接事件, 命令说明: "根据事件类型挂接不同的事件, 事件类型请使用 浏览器事件_ 开头的常量"
// 参数<1>: 事件类型 SDT_INT, 参数说明: "浏览器事件_ 开头常量, 需要的子程序参数和返回值请参考常量说明"
// 参数<2>: [回调地址 SDT_SUB_PTR], 参数说明: "详细定义请查看常量, 为空则取消该事件"
// 参数<3>: [参数 SDT_INT], 参数说明: "传入回调的参数"
EXTERN_C void WKE_NAME(190, wke_Event)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = FALSE;
    WKE_CTRL(0);

    void* arg = (void*)pArgInf[3].m_int;
    DWORD sub = pArgInf[2].m_dwSubCodeAdr;
    if ( sub == 0 || data->hWnd == 0 )
        return;

    int index = pArgInf[1].m_int - 1;
    switch ( pArgInf[1].m_int )
    {
    case 1:		// 文档就绪
    case 2:		// 标题被改变
    case 3:		// URL被改变
    case 4:		// 即将导航到新地址
    case 5:		// 即将导航到新窗口
    case 6:		// 文档载入完毕
    case 7:		// 控台消息输出
    case 8:		// Alert将被调用
    case 9:		// Confirm将被调用
    case 10:	// Prompt将被调用
    case 11:	// 正在下载文件
    case 12:	// Url载入开始
    case 13:	// Url载入结束
    case 14:	// 鼠标移入链接
        wke->jyEvent.arg[index].fun = sub;
        wke->jyEvent.arg[index].arg = arg;
        break;
    case 15:	// 左键按下
        wke->jyEvent.lDowm.fun = sub;
        wke->jyEvent.lDowm.arg = arg;
        break;
    case 16:		// 左键放开
        wke->jyEvent.lUp.fun = sub;
        wke->jyEvent.lUp.arg = arg;
        break;
    case 17:		// 左键双击
        wke->jyEvent.lDblClk.fun = sub;
        wke->jyEvent.lDblClk.arg = arg;
        break;
    case 18:		// 右键按下
        wke->jyEvent.rDowm.fun = sub;
        wke->jyEvent.rDowm.arg = arg;
        break;
    case 19:		// 右键放开
        wke->jyEvent.rUp.fun = sub;
        wke->jyEvent.rUp.arg = arg;
        break;
    case 20:		// 鼠标移动
        wke->jyEvent.move.fun = sub;
        wke->jyEvent.move.arg = arg;
        break;
    case 21:		// 焦点获取
        wke->jyEvent.getFocus.fun = sub;
        wke->jyEvent.getFocus.arg = arg;
        break;
    case 22:		// 焦点消失
        wke->jyEvent.killFocus.fun = sub;
        wke->jyEvent.killFocus.arg = arg;
        break;
    case 23:		// 某键按下
        wke->jyEvent.keyDowm.fun = sub;
        wke->jyEvent.keyDowm.arg = arg;
        break;
    case 24:		// 某键放开
        wke->jyEvent.keyUp.fun = sub;
        wke->jyEvent.keyUp.arg = arg;
        break;
    case 25:		// 输入字符
        wke->jyEvent.charSet.fun = sub;
        wke->jyEvent.charSet.arg = arg;
        break;
    case 26:		// 滚轮滚动
        wke->jyEvent.scroll.fun = sub;
        wke->jyEvent.scroll.arg = arg;
        break;
    case 27:		// 绘画事件
        wke->jyEvent.paint.fun = sub;
        wke->jyEvent.paint.arg = arg;
    default:
        return;
    }
    pRetData->m_bool = TRUE;
}

typedef bool(__stdcall* pfn_callback_getAllCookie_arg8)( void* params,
                                                        const char* name,
                                                        const char* value,
                                                        const char* domain,
                                                        const char* path, // If |path| is non-empty only URLs at or below the path will get the cookie value.
                                                        int secure, // If |secure| is true the cookie will only be sent for HTTPS requests.
                                                        int httpOnly, // If |httponly| is true the cookie will only be sent for HTTP requests.
                                                        int* expires // The cookie expiration date is only valid if |has_expires| is true.
                                                        );

inline static bool fun_wkeCookieVisitor(
    void* params,
    const char* name,
    const char* value,
    const char* domain,
    const char* path, // If |path| is non-empty only URLs at or below the path will get the cookie value.
    int secure, // If |secure| is true the cookie will only be sent for HTTPS requests.
    int httpOnly, // If |httponly| is true the cookie will only be sent for HTTP requests.
    int* expires // The cookie expiration date is only valid if |has_expires| is true.
)
{
    WKECtrl* wke = (WKECtrl*)params;
    pfn_callback_getAllCookie_arg8 fun = (pfn_callback_getAllCookie_arg8)wke->jyEvent.getAllCookie.fun;
    return fun(wke->jyEvent.getAllCookie.arg, name, value, domain, path, secure, httpOnly, expires);
}
// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).获取所有Cookie, 命令说明: "通过访问器visitor访问所有cookie"
// 参数<1>: 访问器 SDT_SUB_PTR, 参数说明: "逻辑型 回调函数(整数型 参数, 文本型 cookie名, 文本型 cookie值, 文本型 域名, 文本型 路径, 整数型 仅发送https请求, 整数型 仅发送http请求, 整数型传址 是否设置cookie过期事件); "
// 参数<2>: [参数 SDT_INT], 参数说明: "访问器参数, 传入参数1回调地址中的值"
EXTERN_C void WKE_NAME(191, wke_GetAllCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->jyEvent.getAllCookie.arg = (void*)pArgInf[2].m_int;
    wke->jyEvent.getAllCookie.fun = (DWORD)pArgInf[1].m_dwSubCodeAdr;
    if ( !wke->jyEvent.getAllCookie.fun )
        return;
    wke->VisitAllCookie(wke, fun_wkeCookieVisitor);
}

// 调用格式: _SDT_NULL (精易Web浏览器/弹出窗口操作).清除cookie, 命令说明: "清除cookie"
// 无参数
EXTERN_C void WKE_NAME(198, wke_ClearCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->ClearCookie();
}

// 调用格式: SDT_INT (精易Web浏览器/弹出窗口操作).取网页图标, 命令说明: "必须在 文档载入完毕 事件里调用"
// 无参数
EXTERN_C void WKE_NAME(203, wke_NetGetFavicon)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// 调用格式: SDT_INT (弹出窗口操作).创建, 命令说明: "创建一个浏览框, 创建成功返回窗口句柄, 失败返回0, 窗口句柄和webView是不一样的, 请严格传递参数"
// 参数<1>: [父窗口句柄 SDT_INT], 参数说明: "创建新浏览器的父窗口句柄, 如果当前程序没有消息循环, 则需要自己处理消息循环"
// 参数<2>: [左 SDT_INT], 参数说明: "创建浏览框左边的位置, 默认为0"
// 参数<3>: [顶 SDT_INT], 参数说明: "创建浏览框顶边的位置, 默认为0"
// 参数<4>: [宽 SDT_INT], 参数说明: "创建浏览框的宽度, 默认为0"
// 参数<5>: [高 SDT_INT], 参数说明: "创建浏览框的高度, 默认为0"
// 参数<6>: [存在销毁 SDT_BOOL], 参数说明: "如果当前类已经创建了浏览框, 则先销毁在创建, 否则返回假, 默认为真, 销毁后创建"
EXTERN_C void WKE_NAME(216, wke_Create)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = FALSE;
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)*pArgInf[0].m_ppCompoundData;
    init_webkit();
    if ( !data )
    {
        data = new WEBKIT_PROPERTYEX;
        data->clear();
        data->init();
        *pArgInf[0].m_ppCompoundData = data;
    }
    WKECtrl* wke = data->pCtl;

    HWND hParent = (HWND)pArgInf[1].m_int;
    //wkeWindowType type = (wkeWindowType)pArgInf[7].m_int;
    wkeWindowType type = WKE_WINDOW_TYPE_CONTROL;
    if ( !IsWindow(hParent) ) type = WKE_WINDOW_TYPE_POPUP;

    BOOL isDestroy = pArgInf[6].m_bool;

    if ( IsWindow(data->hWnd) )
    {
        if ( isDestroy == FALSE )
            return;	// 窗口已存在, 并且不是设置销毁后才创建
        wke->DestroyWebView();
        data->hWnd = 0;
    }

    RECT rc = { 0 };
    rc.left = pArgInf[2].m_int;
    rc.top = pArgInf[3].m_int;
    rc.right = pArgInf[4].m_int;
    rc.bottom = pArgInf[5].m_int;

    const DWORD dwStyle = WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE;
    if ( !wke->create(hParent, dwStyle, 0, rc.left, rc.top, rc.right, rc.bottom, 0, type) )
    {
        if ( pArgInf[0].m_ppCompoundData[0] == 0 )
        {
            delete wke;
        }
        return;
    }
    wkeWebView webView = wke->GetWkeWebView();
    data->hWnd = wke->GetWindowHandle();

    __fill_wnd_data(data, webView);
    wke->WKECtrl_OnPaint();
    wke->SetWindowTitle(L"精易Web浏览器");
    wke->ShowWindow(true);
    pRetData->m_int = (int)data->hWnd;
}

// 调用格式: SDT_BOOL (弹出窗口操作).消息循环, 命令说明: "消息循环, 如果没有创建窗口则返回假, 否则直到窗口收到 WM_QUIT 消息时此方法才返回真"
// 参数<1>: [窗口销毁退出消息循环 SDT_BOOL], 参数说明: "如果为真, 则该窗口收到 WM_DESTROY 消息时会调用 PostQuitMessage() 退出消息循环, 如果有自己子类化, 则在收到 WM_DESTROY 消息时需要调用 CallWindowProcW() 把消息转到原过程, 或者自己调用 PostQuitMessage(), 否则该函数不会返回"
EXTERN_C void WKE_NAME(217, wke_MessageLoop)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    HWND hWnd = 0;
    WKE_CTRL(&hWnd);
    pRetData->m_bool = FALSE;
    if ( !IsWindow(hWnd) )
        return;
    wke->isDlg = pArgInf[1].m_bool;
    wkeRunMessageLoop();
    pRetData->m_bool = TRUE;
}

// 调用格式: SDT_INT (精易Web浏览器/弹出窗口操作).取wke窗口句柄, 命令说明: "取当前wke的窗口句柄"
// 无参数
EXTERN_C void WKE_NAME(220, wke_GetWindow)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_int = (int)wke->GetWindowHandle();
}

