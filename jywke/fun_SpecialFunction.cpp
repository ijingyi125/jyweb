#include "wke_typedef.h"
#include "WKECtrl.h"


// 调用格式: _SDT_NULL (特殊功能).特殊功能初始化, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(117, NETIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// 调用格式: _SDT_NULL (特殊功能).特殊功能赋值, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(118, NETCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// 调用格式: _SDT_NULL (特殊功能).特殊功能销毁, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(119, NETDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// 调用格式: _SDT_NULL (特殊功能).NPAPI插件开启关闭, 命令说明: "该浏览器内核支持NPAPI插件，借助NPAPI插件，可以实现例如FLASH播放的功能。真开启，假关闭"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 是否开启 SDT_BOOL, 参数说明: "真 代表开启 , 假关闭  默认开启"
EXTERN_C void WKE_NAME(120, wke_NPAPIEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetNpapiPluginsEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// 调用格式: _SDT_NULL (特殊功能).爬虫模式开启关闭, 命令说明: "开启或关闭网页渲染,提高网页加载速度 适用于爬虫。注意：如果关闭后，网页不再进行渲染，但内容依然存在。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 是否开启 SDT_BOOL, 参数说明: "真 代表开启 , 假关闭  默认开启"
EXTERN_C void WKE_NAME(121, wke_SpiderEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetHeadlessEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// 调用格式: _SDT_NULL (特殊功能).Cookie开启关闭, 命令说明: "Cookie开启和禁用，如果关闭，浏览器将不再带有Cookie。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 是否开启 SDT_BOOL, 参数说明: "真 代表开启 , 假关闭  默认开启"
EXTERN_C void WKE_NAME(122, wke_SetCookieEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetCookieEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// 调用格式: SDT_BOOL (特殊功能).Cookie是否可用, 命令说明: "Cookie是否已经开启。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(123, wke_CookieIsEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    BOOL nRet = wkeIsCookieEnabled((wkeWebView)pArgInf[1].m_int);
    pRetData->m_dtDataType = SDT_BOOL;
    pRetData->m_bool = nRet;
}

// 调用格式: _SDT_NULL (特殊功能).跨域检查开启关闭, 命令说明: "跨域检查是否开启 如果设置为真，则检查跨域操作，跨域操作将无权执行，如果设置为假，则允许跨域操作。默认值为假。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 是否开启 SDT_BOOL, 参数说明: "真 代表开启 , 假关闭  默认开启"
EXTERN_C void WKE_NAME(124, wke_CspCheckEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetCspCheckEnable((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_bool);
}

// 调用格式: _SDT_NULL (特殊功能).拦截网络请求, 命令说明: "可以 Url载入开始 事件中调用,Hook指定资源。必须调用此方法后，Url载入结束事件才会被调用"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(125, HookRequest)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetHookRequest((wkeNetJob)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (特殊功能).修改HTTP头字段信息, 命令说明: "可以 Url载入开始 事件中调用，表示设置http请求（或者file:///协议）的 HTTP头字段信息。"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
// 参数<2>: HTTP头名称 SDT_TEXT, 参数说明: "Http头字段名称 如 Accept , Content-Type 等..."
// 参数<3>: HTTP头值 SDT_TEXT, 参数说明: "Http头字段对应值, 如: text/javascript , appliction/json 等..."
EXTERN_C void WKE_NAME(126, wke_NetSetHTTPHeaderField)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //wkeSetCspCheckEnable((wkeWebView)pArgInf[1].m_int,pArgInf[2].m_bool);
    //在wkeOnLoadUrlBegin回调里调用，表示设置http请求（或者file:///协议）的 http header field。response一直要被设置成false

    wstr key = wstr::A2W(pArgInf[2].m_pText);
    wstr value = wstr::A2W(pArgInf[3].m_pText);
    wkeNetSetHTTPHeaderField((wkeNetJob)pArgInf[1].m_int, key.c_str(), value.c_str(), FALSE);

}

// 调用格式: _SDT_NULL (特殊功能).修改请求MIME类型, 命令说明: "可以在 URL载入开始 事件中调用 表示设置http请求的MIME type。"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
// 参数<2>: MIME类型 SDT_TEXT, 参数说明: "MIMEType..."
EXTERN_C void WKE_NAME(127, wke_NetSetMIMEType)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetSetMIMEType((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText);
}


// 调用格式: _SDT_NULL (特殊功能).修改请求URL, 命令说明: "可以在 URL载入开始 事件中调用 可以修改一个网络请求的url。"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
// 参数<2>: Url SDT_TEXT, 参数说明: "URL..."
EXTERN_C void WKE_NAME(128, wke_NetChangeRequestUrl)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetChangeRequestUrl((wkeNetJob)pArgInf[1].m_int, pArgInf[2].m_pText);
}

// 调用格式: _SDT_NULL (特殊功能).修改拦截数据, 命令说明: "在 Url载入开始 事件里调用，表示设置拦截后缓存的数据。"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
// 参数<2>: 数据 SDT_BIN, 参数说明: "数据"
// 参数<3>: [数据长度 SDT_INT], 参数说明: "数据长度"
EXTERN_C void WKE_NAME(129, wke_SetRequestData)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    int dwLen = 0;
    LPBYTE pData = GetAryElementInf(pArgInf[2].m_pBin, &dwLen);
    if (pArgInf[3].m_dtDataType != _SDT_NULL)
    {
        dwLen = pArgInf[3].m_int;
    }

    wkeNetSetData((wkeNetJob)pArgInf[1].m_int, (void*)(pData), dwLen);
}

// 调用格式: _SDT_NULL (特殊功能).开启触屏模式, 命令说明: "开启后，鼠标消息将自动转换成触屏消息。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 是否开启 SDT_BOOL, 参数说明: "真 代表开启 , 假关闭  默认开启"
EXTERN_C void WKE_NAME(130, wke_SetTouchEnabled)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetTouchEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// 调用格式: _SDT_NULL (特殊功能).开关鼠标消息, 命令说明: "开启关闭鼠标消息，可以在开启触屏后，关闭鼠标消息。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 是否开启 SDT_BOOL, 参数说明: "真 代表开启 , 假关闭  默认开启"
EXTERN_C void WKE_NAME(131, wke_SetMouseEnabled)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetMouseEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// 调用格式: _SDT_NULL (特殊功能).调用DevTool, 命令说明: "开启一些试验型功能。 例如开启开发者工具。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: debugString SDT_TEXT, 参数说明: "showDevTools "
// 参数<3>: configParam SDT_TEXT, 参数说明: ", 注意param此时必须是utf8编码"
EXTERN_C void WKE_NAME(132, wke_ShowDevTool)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //wkeSetDebugConfig((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText, pArgInf[3].m_pText);

    //wkeSetDebugConfig((wkeWebView)(pArgInf[1].m_int), "showDevTools", _A2U_wke("F:\\Documents\\Desktop\\wke支持库测试\\front_end\\inspector.html"));

    wkeSetDebugConfig((wkeWebView)(pArgInf[1].m_int), pArgInf[2].m_pText, pArgInf[3].m_pText);
}


// 调用格式: SDT_INT (特殊功能).取主框架ID, 命令说明: "取主框架ID。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(133, wke_GetMainFrameId)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeWebFrameHandle ID = wkeWebFrameGetMainFrame((wkeWebView)pArgInf[1].m_int);
    pRetData->m_int = (int)ID;
}

// 调用格式: SDT_BOOL (特殊功能).是否为主框架, 命令说明: "是否为主框架。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: frameid SDT_INT, 参数说明: "框架ID"
EXTERN_C void WKE_NAME(134, wke_IsMainFrame)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    BOOL bRet = wkeIsMainFrame((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
    pRetData->m_bool = bRet;
}

// 调用格式: SDT_TEXT (特殊功能).取框架URL, 命令说明: "按框架ID取框架URL。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: frameid SDT_INT, 参数说明: "框架ID"
EXTERN_C void WKE_NAME(135, wke_GetFrameUrl)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    LPCSTR str = wkeGetFrameUrl((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
    pRetData->m_pText = CloneTextData((char*)str);
}

// 调用格式: _SDT_NULL (特殊功能).鼠标移动, 命令说明: "发送鼠标消息,模拟移动到指定位置。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: x SDT_INT, 参数说明: "横坐标"
// 参数<3>: y SDT_INT, 参数说明: "纵坐标"
EXTERN_C void WKE_NAME(136, wke_MBMouseMove)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_MOUSEMOVE, x, y, WKE_CONTROL);
}

// 调用格式: _SDT_NULL (特殊功能).鼠标左键按下, 命令说明: "发送鼠标左键按下消息。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: x SDT_INT, 参数说明: "横坐标"
// 参数<3>: y SDT_INT, 参数说明: "纵坐标"
EXTERN_C void WKE_NAME(137, wke_MouseLButtonDown)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_LBUTTONDOWN, x, y, WKE_LBUTTON);
}

// 调用格式: _SDT_NULL (特殊功能).鼠标左键抬起, 命令说明: "发送鼠标左键抬起消息。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: x SDT_INT, 参数说明: "横坐标"
// 参数<3>: y SDT_INT, 参数说明: "纵坐标"
EXTERN_C void WKE_NAME(138, wke_MouseLButtonUP)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_LBUTTONUP, x, y, WKE_LBUTTON);
}

// 调用格式: _SDT_NULL (特殊功能).鼠标中键按下, 命令说明: "发送鼠标中键按下消息。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: x SDT_INT, 参数说明: "横坐标"
// 参数<3>: y SDT_INT, 参数说明: "纵坐标"
EXTERN_C void WKE_NAME(139, wke_MouseMButtonDown)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_MBUTTONDOWN, x, y, WKE_MBUTTON);
}

// 调用格式: _SDT_NULL (特殊功能).鼠标中键抬起, 命令说明: "发送鼠标中键抬起消息。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: x SDT_INT, 参数说明: "横坐标"
// 参数<3>: y SDT_INT, 参数说明: "纵坐标"
EXTERN_C void WKE_NAME(140, wke_MouseMButtonUP)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_MBUTTONUP, x, y, WKE_MBUTTON);
}

// 调用格式: _SDT_NULL (特殊功能).鼠标右键按下, 命令说明: "发送鼠标右键按下消息。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: x SDT_INT, 参数说明: "横坐标"
// 参数<3>: y SDT_INT, 参数说明: "纵坐标"
EXTERN_C void WKE_NAME(141, wke_MouseRButtonDown)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_RBUTTONDOWN, x, y, WKE_RBUTTON);
}

// 调用格式: _SDT_NULL (特殊功能).鼠标右键抬起, 命令说明: "发送鼠标右键抬起消息。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: x SDT_INT, 参数说明: "横坐标"
// 参数<3>: y SDT_INT, 参数说明: "纵坐标"
EXTERN_C void WKE_NAME(142, wke_MouseRButtonUP)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_RBUTTONUP, x, y, WKE_RBUTTON);
}

// 调用格式: _SDT_NULL (特殊功能).按键_按下, 命令说明: "发送按键消息到MB。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 键代码 SDT_INT, 参数说明: "键代码请使用 如 #退格键...."
EXTERN_C void WKE_NAME(143, wke_KeyDownEvent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    //++HACK WKM_RREND = 1025 ????
    wkeFireKeyDownEvent((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, 1025, 0);
}

// 调用格式: _SDT_NULL (特殊功能).按键_抬起, 命令说明: "发送按键消息到MB。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 键代码 SDT_INT, 参数说明: "键代码请使用 如 #K键 #A键...."
EXTERN_C void WKE_NAME(144, wke_KeyUpEvent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    //++HACK WKM_RREND = 1025 ????
    wkeFireKeyUpEvent((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, 1025, 0);
}

// 调用格式: _SDT_NULL (特殊功能).按键_字符, 命令说明: "发送WM_CHAR消息。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 键代码 SDT_INT, 参数说明: "键代码请使用 如 #K键 #A键...."
EXTERN_C void WKE_NAME(145, wke_KeyPressEvent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeFireKeyPressEvent((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, WKE_REPEAT, 0);
}

// 调用格式: _SDT_NULL (特殊功能).取消该网络请求, 命令说明: "可以在 URL载入开始事件中 取消指定的网络请求。"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(146, wke_CancelByReuqest)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetCancelRequest((wkeNetJob)pArgInf[1].m_int);
}











//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


// 调用格式: SDT_TEXT (特殊功能).[]获取请求头数据, 命令说明: "获取发送的请求头的数据。"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(167, wke_NetGetRawHttpHead)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    const wkeSlist* list = wkeNetGetRawHttpHead((wkeNetJob)pArgInf[1].m_int);
    const wkeSlist* plist = list;
    if ( !list )
    {
        LPINT p = (LPINT)ealloc(sizeof(INT) * 2);
        p[0] = 1;  // 数组维数。
        p[1] = 0;
        pRetData->m_pAryData = p;  // 返回内容数组。
        return;
    }

    int len = 0;
    while ( list != NULL )
    {
        len++;
        list = list->next;
    }
    list = plist;
    LPINT p = (LPINT)ealloc(sizeof(INT) * ( 2 + len ));
    p[0] = 1;  // 数组维数。
    p[1] = len;

    int i = 2;
    while ( list != NULL )
    {
        p[i] = (int)CloneTextData(list->data);
        i++;
        list = list->next;
    }
    pRetData->m_pAryData = p;  // 返回内容数组。
}

// 调用格式: SDT_INT (特殊功能).取请求模式, 命令说明: "返回当前的请求模式, 请使用 #请求模式_ 开头的常量\r\n无法修改post数据,只能取"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(172, wke_NetGetRequestMethod)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_int = wkeNetGetRequestMethod((wkeNetJob)pArgInf[1].m_int);
}


typedef struct __POSTELEMENT
{
    int cbSize;
    int type;
    LPBYTE data;
    LPCSTR filePath;
    __int64 startPos;
    __int64 length;
}POSTELEMENT, * LPPOSTELEMENT;

typedef struct __POSTELEMENTS
{
    int cbSize;
    int* pElement;
    int count;
    int isChange;
    wkePostBodyElements* oldData;
}POSTELEMENTS, *LPPOSTELEMENTS;


// 调用格式: MAKELONG(0x09, 0) (特殊功能).取post数据, 命令说明: "获取post数据"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(173, wke_NetGetPostBody)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    /*DTP_POSTELEMENTS =
    {
        结构大小
        元素组[]
            {
                结构大小
                类型
                数据
                文件路径
                文件开始位置
                文件长度
            }
        元素数量
        是否改变
        原始数据
    }
    */
    wkePostBodyElements* data = wkeNetGetPostBody((wkeNetJob)pArgInf[1].m_int);
    if (!data)
    {
        LPPOSTELEMENTS pMem = (LPPOSTELEMENTS)ealloc(sizeof(POSTELEMENTS));
        int* pArrElement = (int*)ealloc(2 * sizeof(int));
        pArrElement[0] = 1;
        pArrElement[1] = 0;

        pMem->cbSize = sizeof(POSTELEMENTS);
        pMem->count = 0;
        pMem->isChange = 0;
        pMem->oldData = 0;
        pMem->pElement = pArrElement;
        pRetData->m_pCompoundData = pMem;
        return;
    }
    //return;

    wkeMemBuf* pData = 0;
    LPPOSTELEMENTS pMem = (LPPOSTELEMENTS)ealloc(sizeof(POSTELEMENTS));

    int* pArrElement = (int*)ealloc((data->elementSize + 2) * sizeof(int));
    int index = 0;
    pArrElement[index++] = 1;
    pArrElement[index++] = data->elementSize;
    
    if (pMem)
    {
        pMem->cbSize = sizeof(POSTELEMENTS);
        pMem->count = data->elementSize;
        pMem->isChange = data->isDirty;
        pMem->oldData = data;
        pMem->pElement = pArrElement;
        for (size_t i = 0; i < data->elementSize; i++)
        {
            LPPOSTELEMENT pElement = (LPPOSTELEMENT)ealloc(sizeof(POSTELEMENT));
            pArrElement[index++] = (int)pElement;

            pElement->cbSize = (data->element[i])->size;
            pElement->type = (data->element[i])->type;
            pData = (data->element[i])->data;
            if (pData)pElement->data = CloneBinData((LPBYTE)pData->data, pData->length);
            pElement->filePath = CloneTextData(wkeGetString((data->element[i])->filePath));
            pElement->startPos = (data->element[i])->fileStart;
            pElement->length = (data->element[i])->fileLength;
        }
    }
    
    pRetData->m_dtDataType = SDT_TYPE_POSTELEMENTS;
    pRetData->m_pCompoundData = pMem;
}

// 调用格式: SDT_BOOL (特殊功能).创建post数据, 命令说明: "创建单条post数据"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(174, wke_NetCreatePostBodyElement)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //1.这四个接口要结合起来使用。 当wkeOnLoadUrlBegin里判断是post时，可以通过wkeNetCreatePostBodyElements来创建一个新的post数据包。 
    //然后wkeNetFreePostBodyElements来释放原post数据。

    /*DTP_POSTELEMENTS = 
    {
        结构大小
        元素组[]
            {
                结构大小
                类型
                数据
                文件路径
                文件开始位置
                文件长度
            }
        元素数量
        是否改变
        原始数据
    }
    */
    wkeWebView webView = (wkeWebView)pArgInf[1].m_int;
    pRetData->m_bool = FALSE;
    wkePostBodyElements* data = 0;
    wkePostBodyElements* dataOld = 0;
    int* pMem = 0;
    int* pAry = 0;
    int dwLen = 0;
    if (!pArgInf[2].m_pCompoundData)return;
    pMem = (int*)pArgInf[2].m_pCompoundData;
    dataOld = (wkePostBodyElements*)pMem[4];
    
    pAry = (int*)(pMem[1]);
    int size = pAry[1];
    pAry = pAry + 2;

    if (size == 0)return;
    data = wkeNetCreatePostBodyElements(webView, size);
    if (data == 0)return;
    
    // pAry = 用户传递过来的post数据组,现在是指向第一个成员,每个成员都是一个数据类型

    //pData  0 = 结构大小 1 = 类型  2 = 字节集数据 3 = 文件路径  4 = 文件开始位置  6 = 文件长度
    int* pData = 0;
    INT64* i64 = 0;
    for (int i = 0; i < size; i++)
    {
        data->element[i] = wkeNetCreatePostBodyElement(webView);
        wkeMemBuf* buf = new wkeMemBuf;
        memset(buf, 0, sizeof(wkeMemBuf));
        if (data->element[i])
        {
            pData = (int*)pAry[i];
            data->element[i]->size = sizeof(wkePostBodyElement);
            data->element[i]->type = (wkeHttBodyElementType)pData[1];
            data->element[i]->data = buf;
                buf->data = GetAryElementInf((LPBYTE)pData[2], &dwLen);
                //buf->data = (void*)(pData[2] + 8);
                buf->length = dwLen;
                buf->unuse = sizeof(wkeMemBuf);
            data->element[i]->filePath = wkeString(pData[3]);
            i64 = (INT64*)(pData + 4);
            data->element[i]->fileStart = *i64;
            i64 = (INT64*)(pData + 6);
            data->element[i]->fileLength = *i64;
        }
    }
    if (dataOld)wkeNetFreePostBodyElements(dataOld);
    pMem[4] = (int)data;
}

// 调用格式: _SDT_NULL (特殊功能).释放post数据, 命令说明: "【传入的必须是 创建post数据()】 返回的值"
// 参数<1>: post数据 SDT_INT, 参数说明: "创建post数据返回的值"
EXTERN_C void WKE_NAME(175, wke_NetFreePostBodyElement)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //wkePostBodyElements
    //2.这四个接口要结合起来使用。 当wkeOnLoadUrlBegin里判断是post时，可以通过wkeNetCreatePostBodyElements来创建一个新的post数据包。 
    //然后wkeNetFreePostBodyElements来释放原post数据。

    if (!pArgInf[2].m_pCompoundData)return;
    int* pMem = (int*)pArgInf[1].m_pCompoundData;
    wkePostBodyElements* data = (wkePostBodyElements*)pMem[4];
    if (!data) return;
    
    int* pAry = (int*)(pMem[1]);
    int size = pAry[1];
    pAry = pAry + 2;

    if (size == 0)
    {
        if (data)wkeNetFreePostBodyElements(data);
        return;
    }
    

    for (int i = 0; i < size; i++)
    {
        if (data->element[i] && data->element[i]->data)
        {
            delete data->element[i]->data;
        }
    }
    if (data)wkeNetFreePostBodyElements(data);
}

// 调用格式: SDT_BOOL (特殊功能).创建post数据组, 命令说明: "创建一个新的post数据组,记得不用时自己调用 特殊功能.释放post数据组() 来释放"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 元素组 MAKELONG(0x09, 0), 参数说明: "元素组"
EXTERN_C void WKE_NAME(176, wke_NetCreatePostBodyElements)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //3.这四个接口要结合起来使用。 当wkeOnLoadUrlBegin里判断是post时，可以通过wkeNetCreatePostBodyElements来创建一个新的post数据包。 
    //然后wkeNetFreePostBodyElement来释放原post数据。
    //UNDONE 待添加功能,特殊功能->创建post数据
    wkePostBodyElement* data = wkeNetCreatePostBodyElement((wkeWebView)pArgInf[1].m_int);

}

// 调用格式: _SDT_NULL (特殊功能).释放post数据组, 命令说明: "【传入的必须是 创建post数据组()】 返回的值\r\n在[Url载入开始]事件里判断是post时，可以通过 特殊功能.创建post数据组() 来创建一个新的post数据包。然后调用 特殊功能.释放post数据组() 来释放原post数据。"
// 参数<1>: 元素组 MAKELONG(0x09, 0), 参数说明: "元素组"
EXTERN_C void WKE_NAME(177, wke_NetFreePostBodyElements)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //4.这四个接口要结合起来使用。 当wkeOnLoadUrlBegin里判断是post时，可以通过wkeNetCreatePostBodyElements来创建一个新的post数据包。 
    //然后wkeNetFreePostBodyElement来释放原post数据。
    //UNDONE 待添加功能,特殊功能->释放post数据
    //wkePostBodyElements
    wkeNetFreePostBodyElement((wkePostBodyElement*)pArgInf[1].m_int);

}

// 调用格式: SDT_BOOL (特殊功能).异步请求, 命令说明: "高级用法。在[Url载入开始]回调里调用。 有时候，[Url载入开始]事件里拦截到一个请求后，不能马上判断出结果。此时可以调用本接口，然后在 异步的某个时刻，调用 特殊功能.继续请求() 来让此请求继续进行\r\n返回真代表成功，假代表调用失败，不能再调用 特殊功能.继续请求() 了"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(178, wke_NetHoldJobToAsynCommit)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    // 不能马上判断出结果。此时可以调用本接口，然后在 异步的某个时刻，调用 特殊功能.继续请求() 来让此请求继续进行
    pRetData->m_bool = wkeNetHoldJobToAsynCommit((wkeNetJob)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (特殊功能).继续请求, 命令说明: "高级用法。配合 特殊功能.异步请求() 使用"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(179, wke_NetContinueJob)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetContinueJob((wkeNetJob)pArgInf[1].m_int);
}


// 调用格式: SDT_TEXT (特殊功能).[]获取响应头, 命令说明: "获取原始响应头, 在 Url载入结束 事件中使用"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(196, wke_NetGetRawResponseHead)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    const wkeSlist* list = wkeNetGetRawResponseHead((wkeNetJob)pArgInf[1].m_int);
    const wkeSlist* plist = list;
    if ( !list )
    {
        LPINT p = (LPINT)ealloc(sizeof(INT) * 2);
        p[0] = 1;  // 数组维数。
        p[1] = 0;
        pRetData->m_pAryData = p;  // 返回内容数组。
        return;
    }

    int len = 0;
    while ( list != NULL )
    {
        len++;
        list = list->next;
    }
    list = plist;
    LPINT p = (LPINT)wke_jy_ealloc_wke(sizeof(INT) * ( 2 + len ));

    p[0] = 1;  // 数组维数。
    p[1] = len;

    int i = 2;
    while ( list != NULL )
    {
        p[i] = (int)CloneTextData(list->data);
        i++;
        list = list->next;
    }
    pRetData->m_pAryData = p;  // 返回内容数组。
}

// 调用格式: _SDT_NULL (特殊功能).post, 命令说明: "post"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: url SDT_TEXT, 参数说明: "post的url"
// 参数<3>: post数据 SDT_BIN, 参数说明: "post的数据"
EXTERN_C void WKE_NAME(197, wke_PostURL)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeWebView webView = (wkeWebView)pArgInf[1].m_int;
    if ( !webView )return;
    int len = 0;
    LPBYTE pArr = GetAryElementInf(pArgInf[3].m_pBin, &len);
    if ( !pArr || len == 0 )return;
    wstr url = _str::U2W(pArgInf[2].m_pText);
    wkePostURLW(webView, url.c_str(), (const char*)pArr, len);
}

// 调用格式: _SDT_NULL (特殊功能).获取请求MIME类型, 命令说明: "在 URL载入开始 事件里调用, 表示设置http请求的MIME type"
// 参数<1>: Job SDT_INT, 参数说明: "Url载入开始 中传入的参数"
EXTERN_C void WKE_NAME(200, wke_NetGetMIMEType)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //wkeNetGetMIMEType()
}

// 调用格式: SDT_TEXT (特殊功能).获取HTTP头字段信息, 命令说明: "在 URL载入开始 事件里调用, 表示设置http请求（或者file:///协议）的 http header field"
// 参数<1>: Job SDT_INT, 参数说明: "事件里的参数"
// 参数<2>: key SDT_TEXT, 参数说明: "要获取哪个头"
EXTERN_C void WKE_NAME(201, wke_NetGetHTTPHeaderField)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    const char* s = wkeNetGetHTTPHeaderField((wkeNetJob)pArgInf[1].m_int, pArgInf[2].m_pText);
    pRetData->m_pText = CloneTextData(s);
}

// 调用格式: SDT_TEXT (特殊功能).获取响应HTTP头字段信息, 命令说明: "在 URL载入结束 事件里调用"
// 参数<1>: Job SDT_INT, 参数说明: "事件里的参数"
// 参数<2>: key SDT_TEXT, 参数说明: "要获取哪个头"
EXTERN_C void WKE_NAME(202, wke_NetGetHTTPHeaderFieldFromResponse)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    const char* s = wkeNetGetHTTPHeaderFieldFromResponse((wkeNetJob)pArgInf[1].m_int, pArgInf[2].m_pText);
    pRetData->m_pText = CloneTextData(s);
}

// 调用格式: _SDT_NULL (特殊功能).置调试信息, 命令说明: "置调试信息"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: debugString SDT_TEXT, 参数说明: "showDevTools "
// 参数<3>: configParam SDT_TEXT, 参数说明: ", 注意param此时必须是utf8编码"
EXTERN_C void WKE_NAME(221, wke_SetDebugConfig)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetDebugConfig((wkeWebView)( pArgInf[1].m_int ), pArgInf[2].m_pText, pArgInf[3].m_pText);
}

