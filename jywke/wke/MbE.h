#pragma once

#include "RenderGDI.h"
#include "MbECommon.h"
#include "jsRunningManager.h"


class MbE
{
private:
    jsRunningManager* m_jsRunninger;

private:
    wkeWebView  _webview;
    HWND        _parentHWND;
    CRenderGDI* _render;

public:
    MbE()
    {
        _webview = NULL;
        _parentHWND = NULL;
        _render = NULL;
        m_jsRunninger = NULL;
    }
    ~MbE()
    {
        if ( m_jsRunninger )delete m_jsRunninger;
        if ( _render )delete _render;
        _webview = NULL;
        _parentHWND = NULL;
        _render = NULL;
        m_jsRunninger = NULL;
    }


    static bool Initialize()
    {
        if ( wkeIsInitialize && wkeIsInitialize() )
            return true;

        //if (GetModuleHandleW(L"node.dll"))    // 已经加载过了node.dll
        //    return true;

        wkeSettings setting;
        memset(&setting, 0, sizeof(setting));
        //setting.mask = WKE_SETTING_PAINTCALLBACK_IN_OTHER_THREAD;
        wkeInitializeEx(&setting);
        return true;
    }
    static void wkeUnInit_wke()
    {
        if ( wkeIsInitialize != NULL && wkeIsInitialize() )
        {
            //wkeFinalize();
        }
    }


    
    inline bool Create(wkeWindowType type, HWND parent, int x, int y, int cx, int cy)
    {
        _webview = wkeCreateWebWindow(type, parent, x, y, cx, cy);
        if ( !_webview )
            return false;

        m_jsRunninger = new jsRunningManager;
        m_jsRunninger->SetWebView(_webview);

        _render = new CRenderGDI();
        _render->init(parent);

        wkeShowWindow(_webview, TRUE);
        wkeSetTransparent(_webview, false);
        HWND hWnd = wkeGetWindowHandle(_webview);
        if ( !IsWindow(hWnd) )
            return false;


        //wkeOnPaintUpdated(_webview, MbE::OnPaintUpdated, _render);    //默认事件，必须含有，所以放在这里。
        SetCspCheckEnable(false);
        SetNpapiPluginsEnabled(true);
        SetNavigationToNewWindowEnable(true);
        return true;
    }

    //获取目前api版本号
    inline unsigned int GetVersion() { return wkeVersion(); }

    //延迟让miniblink垃圾回收
    inline void GC(long delayMS) { wkeGC(GetWkeWebView(), delayMS); }

    //获取页面宽度
    inline int GetWidth() { return wkeGetWidth(GetWkeWebView()); }

    //获取网页排版出来的宽度
    inline int GetContentWidth() { return wkeGetContentWidth(GetWkeWebView()); }

    //获取页面高度
    inline int GetHeight() { return wkeGetHeight(GetWkeWebView()); }

    //获取网页排版出来的高度
    inline int GetContentHeight() { return wkeGetContentHeight(GetWkeWebView()); }

    //获取webview的DC
    inline HDC GetViewDC() { return wkeGetViewDC(GetWkeWebView()); }

    //获取webveiw对应的窗口句柄。实现和wkeGetWindowHandle完全相同
    inline HWND GetHostHWND() { return wkeGetHostHWND(GetWkeWebView()); }
    inline HWND GetWindowHandle() { return wkeGetWindowHandle(GetWkeWebView()); }
    inline void DestroyWebWindow() { wkeDestroyWebWindow(GetWkeWebView()); }

    inline void ShowWindow(bool showFlag) { wkeShowWindow(GetWkeWebView(), showFlag); }
    inline void EnableWindow(bool enableFlag) { wkeEnableWindow(GetWkeWebView(), enableFlag); }

    inline void MoveWindow(int x, int y, int width, int height) { wkeMoveWindow(GetWkeWebView(), x, y, width, height); }

    //窗口在父窗口或屏幕里居中
    inline void MoveToCenter() { wkeMoveToCenter(GetWkeWebView()); }

    //设置webview是焦点态。如果webveiw关联了窗口，窗口也会有焦点
    inline void SetFocus() { wkeSetFocus(GetWkeWebView()); }

    inline void KillFocus() { wkeKillFocus(GetWkeWebView()); }

    //获取编辑框的那个游标的位置
    inline wkeRect GetCaretRect() { return wkeGetCaretRect(GetWkeWebView()); }

    inline void SetWindowRect(RECT rect)
    {
        if ( GetWkeWebView() != NULL )
        {
            SetWindowPos(_parentHWND, NULL, 0, 0, rect.right, rect.bottom, SWP_NOMOVE);
            wkeResize(GetWkeWebView(), rect.right, rect.bottom);
        }
    }

    //设置页面缩放系数，默认是1
    inline void SetZoomFactor(float factor) { wkeSetZoomFactor(GetWkeWebView(), factor); }

    //获取页面缩放系数
    inline float GetZoomFactor() { return wkeGetZoomFactor(GetWkeWebView()); }

    inline int GetCursorInfoType() { return wkeGetCursorInfoType(GetWkeWebView()); }

    //inline wkeWebView CreateWebView() { return wkeCreateWebView(); }

    inline void DestroyWebView() { wkeDestroyWebView(GetWkeWebView()); }

    inline void SetWindowTitle(const utf8* title) { wkeSetWindowTitle(GetWkeWebView(), title); }
    inline void SetWindowTitle(const wchar_t* title) { wkeSetWindowTitleW(GetWkeWebView(), title); }

    //////////////////////////////////////////////////////////////////////////////
    /*
    设置mb模拟的硬件设备环境。主要用在伪装手机设备场景
    device：设备的字符串。可取值有：
    "navigator.maxTouchPoints"    此时 paramInt 需要被设置，表示 touch 的点数
    "navigator.platform"    此时 paramStr 需要被设置，表示js里获取的 navigator.platform字符串
    "navigator.hardwareConcurrency"    此时 paramInt 需要被设置，表示js里获取的 navigator.hardwareConcurrency 整数值
    "screen.width"    此时 paramInt 需要被设置，表示js里获取的 screen.width 整数值
    "screen.height"    此时 paramInt 需要被设置，表示js里获取的 screen.height 整数值
    "screen.availWidth"    此时 paramInt 需要被设置，表示js里获取的 screen.availWidth 整数值
    "screen.availHeight"    此时 paramInt 需要被设置，表示js里获取的 screen.availHeight 整数值
    "screen.pixelDepth"    此时 paramInt 需要被设置，表示js里获取的 screen.pixelDepth 整数值
    "scre    en.pixelDepth"    目前等价于"screen.pixelDepth"
    "window.devicePixelRatio"    同上
    */
    inline void SetDeviceParameter(const char* device, const char* paramStr, int paramInt, float paramFloat) { wkeSetDeviceParameter(GetWkeWebView(), device, paramStr, paramInt, paramFloat); }

    //设置整个mb的代码。此句是全局生效
    inline void SetProxy(const wkeProxy* proxy) { wkeSetProxy(proxy); }

    //设置整个mb的代码。此句是针对特定webview生效
    inline void SetViewProxy(wkeProxy* proxy) { wkeSetViewProxy(GetWkeWebView(), proxy); }

    //void wkeSetMemoryCacheEnable(wkeWebView webView, bool b)

    //开启触屏模式。开启后，鼠标消息将自动转换成触屏消息
    inline void SetTouchEnabled(bool b) { wkeSetTouchEnabled(GetWkeWebView(), b); }

    //开启关闭鼠标消息，可以在开启触屏后，关闭鼠标消息
    inline void SetMouseEnabled(bool b) { wkeSetMouseEnabled(GetWkeWebView(), b); }

    //关闭后，点a标签将不会弹出新窗口，而是在本窗口跳转
    inline void SetNavigationToNewWindowEnable(bool b) { wkeSetNavigationToNewWindowEnable(GetWkeWebView(), b); }

    //关闭后，跨域检查将被禁止，此时可以做任何跨域操作，如跨域ajax，跨域设置iframe
    inline void SetCspCheckEnable(bool b) { wkeSetCspCheckEnable(GetWkeWebView(), b); }

    //开启关闭npapi插件，如flash
    inline void SetNpapiPluginsEnabled(bool b) { wkeSetNpapiPluginsEnabled(GetWkeWebView(), b); }

    //开启无头模式。开启后，将不会渲染页面，提升了网页性能。此功能方便用来实现一些爬虫，或者刷单工具
    inline void SetHeadlessEnabled(bool b) { wkeSetHeadlessEnabled(GetWkeWebView(), b); }

    //设置webview的UA
    inline void SetUserAgent(const utf8* userAgent) { wkeSetUserAgent(GetWkeWebView(), userAgent); }
    inline void SetUserAgentW(const wchar_t* userAgent) { wkeSetUserAgentW(GetWkeWebView(), userAgent); }

    //////////////////////////////////////////////////////////////////////////

    inline void LoadURL(const char* url) const            { wkeLoadURL(GetWkeWebView(), url); }
    inline void LoadURL(const wchar_t* url) const         { wkeLoadURLW(GetWkeWebView(), url); }
    inline void GoUrl(const char* url) const              { wkeLoadURL(GetWkeWebView(), url); }
    inline void GoUrl(const wchar_t* url) const           { wkeLoadURLW(GetWkeWebView(), url); }
    inline void LoadHTML(const char* html) const          { wkeLoadHTML(GetWkeWebView(), html); }
    inline void LoadHTML(const wchar_t* html) const       { wkeLoadHTMLW(GetWkeWebView(), html); }
    inline void LoadFile(const char* filename) const      { wkeLoadFile(GetWkeWebView(), filename); }
    inline void LoadFileW(const wchar_t* filename) const  { wkeLoadFileW(GetWkeWebView(), filename); }
    inline jsValue RunJS(const char* script) const        { return wkeRunJS(GetWkeWebView(), script); }
    inline jsValue RunJS(const wchar_t* script) const     { return wkeRunJSW(GetWkeWebView(), script); }


    inline const char* GetUrl() const       { return wkeGetURL(GetWkeWebView()); }
    inline void StopLoading() const         { wkeStopLoading(GetWkeWebView()); }
    inline bool CanGoForward() const        { return wkeCanGoForward(GetWkeWebView()); }
    inline void GoForward() const           { wkeGoForward(GetWkeWebView()); }
    inline bool CanGoBack() const           { return wkeCanGoBack(GetWkeWebView()); }
    inline void GoBack() const              { wkeGoBack(GetWkeWebView()); }
    inline void Reload() const              { wkeReload(GetWkeWebView()); }
    inline const utf8* GetSource() const    { return wkeGetSource(GetWkeWebView()); }
    inline bool IsLoadingCompleted() const  { return wkeIsLoadingCompleted(GetWkeWebView()); }

    //DOM文档结构是否加载完成
    inline bool IsDocumentReady() const       { return wkeIsDocumentReady(GetWkeWebView()); }

    //////////////////////////////////////////////////////////////////////////

    inline void EditorSelectAll() const { wkeEditorSelectAll(GetWkeWebView()); }
    inline void EditorUnSelect() const  { wkeEditorUnSelect(GetWkeWebView()); }
    inline void EditorCopy() const      { wkeEditorCopy(GetWkeWebView()); }
    inline void EditorCut() const       { wkeEditorCut(GetWkeWebView()); }
    inline void EditorDelete() const    { wkeEditorDelete(GetWkeWebView()); }
    inline void EditorUndo() const      { wkeEditorUndo(GetWkeWebView()); }
    inline void EditorRedo() const      { wkeEditorRedo(GetWkeWebView()); }

    //////////////////////////////////////////////////////////////////////////
    inline const char* GetCookie()const     { return wkeGetCookie(GetWkeWebView()); }
    inline const wchar_t* GetCookieW()const { return wkeGetCookieW(GetWkeWebView()); }

    //设置页面cookie。
    //注意：cookie必须符合curl的cookie写法。一个例子是：PERSONALIZE = 123; expires = Monday, 13 - Jun - 2022 03:04 : 55 GMT; domain = .fidelity.com; path = / ; secure
    inline void ClearCookie() { wkeClearCookie(GetWkeWebView()); }
    inline void SetCookie(const utf8* url, const utf8* cookie) { wkeSetCookie(GetWkeWebView(), url, cookie); }
    inline void PerformCookieCommand(wkeCookieCommand command) { wkePerformCookieCommand(GetWkeWebView(), command); }
    inline void VisitAllCookie(void* param, wkeCookieVisitor pfn) { wkeVisitAllCookie(GetWkeWebView(), param, pfn); }
    //wkeVisitAllCookie //未实现。

    //开启或关闭cookie
    //注意：这个接口只是影响blink，并不会设置curl。所以还是会生成curl的cookie文件
    inline void SetCookieEnabled(bool enable) { wkeSetCookieEnabled(GetWkeWebView(), enable); }

    inline bool IsCookieEnabled() { return wkeIsCookieEnabled(GetWkeWebView()); }

    //设置cookie的本地文件目录。默认是当前目录。cookies存在当前目录的“cookie.dat”里
    inline void SetCookieJarPath(const /*wchar_t*/WCHAR* path) { wkeSetCookieJarPath(GetWkeWebView(), path); }

    //设置cookie的全路径+文件名，如“c:\mb\cookie.dat”
    inline void SetCookieJarFullPath(const /*wchar_t*/WCHAR* path) { wkeSetCookieJarFullPath(GetWkeWebView(), path); }

    //////////////////////////////////////////////////////////////////////////

    //设置local storage的全路径。如“c:\mb\LocalStorage\”
    //注意：这个接口只能接受目录。
    inline void SetLocalStorageFullPath(const /*wchar_t*/WCHAR* path) { wkeSetLocalStorageFullPath(GetWkeWebView(), path); }

    //////////////////////////////////////////////////////////////////////////

    //设置音量，未实现
    inline void SetMediaVolume(float volume) { wkeSetMediaVolume(GetWkeWebView(), volume); }

    inline float GetMediaVolume() { return wkeGetMediaVolume(GetWkeWebView()); }

    //////////////////////////////////////////////////////////////////////////

    //判断frameId是否是主frame
    inline bool IsMainFrame(wkeWebFrameHandle frameId) { return wkeIsMainFrame(GetWkeWebView(), frameId); }

    //获取主frame的句柄
    inline wkeWebFrameHandle WebFrameGetMainFrame() { return wkeWebFrameGetMainFrame(GetWkeWebView()); }

    //获取frame对应的url
    inline const utf8* GetFrameUrl(wkeWebFrameHandle frameId) { return wkeGetFrameUrl(GetWkeWebView(), frameId); }

    //////////////////////////////////////////////////////////////////////////
    inline const char* GetTitle()const { return wkeGetTitle(GetWkeWebView()); }
    inline const wchar_t* GetTitleW()const { return wkeGetTitleW(GetWkeWebView()); }
    inline const char* GetUserAgent()const { return wkeGetUserAgent(GetWkeWebView()); }

    inline jsRunningManager* GetJsRunner() { return m_jsRunninger; }

    inline void EnablePlugins() { wkeSetNpapiPluginsEnabled(GetWkeWebView(), true); }

    inline void SetUserKeyValue(const char* key, void* value) { wkeSetUserKeyValue(GetWkeWebView(), key, value); }
    inline void* GetUserKeyValue(const char* key) { return wkeGetUserKeyValue(GetWkeWebView(), key); }

public:
    inline operator wkeWebView() const      { return _webview; }
    inline wkeWebView GetWkeWebView() const { return _webview; }
    inline void SetWkeWebView(wkeWebView webView) { _webview = webView; }
    inline wkeWebView WebView() const       { return _webview; }
    inline CRenderGDI* GetWkeRender()       { return _render; }

    static inline const utf8* GetString(const wkeString s) { return wkeGetString(s); }
    static inline const wchar_t* GetStringW(const wkeString _str) { return wkeGetStringW(_str); }
    static inline void SetString(wkeString _str, const utf8* str, size_t len) { wkeSetString(_str, str, len); }
    static inline void SetStringW(wkeString _str, const wchar_t* str, size_t len) { wkeSetStringW(_str, str, len); }
    static inline wkeString  CreateStringW(const wchar_t* str, size_t len) { return wkeCreateStringW(str, len); }
    static inline void  DeleteString(wkeString str) { wkeDeleteString(str); }

private:

#ifdef _DEBUG

    inline static void onTitleChanged(wkeWebView webView, void* param, const wkeString title)
    {
        WCHAR pstr[4096] = { 0 };
        swprintf(pstr, L"onTitleChanged , %s\n", wkeGetStringW(title));
        OutputDebugStringW(pstr);
    }

    inline static void onURLChanged(wkeWebView webView, void* param, const wkeString url)
    {
        WCHAR pstr[4096] = { 0 };
        swprintf(pstr, L"onURLChanged , %s\n", wkeGetStringW(url));
        OutputDebugStringW(pstr);
    }

    inline static bool onNavigation(wkeWebView webView, void* param, wkeNavigationType type, const wkeString urlStr)
    {
        WCHAR pstr[1024] = { 0 };
        swprintf(pstr, L"onNavigation ,type:%d ,url:%s\n", type, wkeGetStringW(urlStr));
        OutputDebugStringW(pstr);
        return true;
    }

    inline static void onConsoleMessage(wkeWebView webView, void* param, wkeConsoleLevel level, const wkeString message, const wkeString sourceName, unsigned sourceLine, const wkeString stackTrace)
    {
        WCHAR pstr[4096] = { 0 };
        swprintf(pstr, L"onConsoleMessage ,url:%s\n", wkeGetStringW(message));
        OutputDebugStringW(pstr);
    }

    inline static bool onLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job)
    {
        /*
        const char* pos = strstr(url, kPreHead);
        if (pos) {
            const utf8* decodeURL = wkeUtilDecodeURLEscape(url);
            if (!decodeURL)
                return false;
            std::_str urlString(decodeURL);
            std::_str localPath = urlString.substr(sizeof(kPreHead) - 1);

            std::str path = getResourcesPath(utf8ToUtf16(localPath));
            std::vector<char> buffer;

            readJsFile(path.c_str(), &buffer);

            wkeNetSetData(job, buffer.data(), buffer.size());

            return true;
        }
        else if (strncmp(url, "http://localhost:12222", 22) == 0) {
            wkeNetSetMIMEType(job, (char*)"text/html");
            wkeNetSetData(job, (char*)"\"test1111\"", 10);
            return true;
        }
        else if (strcmp(url, "https://www.baidu.com/") == 0) {
            wkeNetHookRequest(job);
        }

        */

        if (strcmp(url, "https://bbs.125.la/") == 0)
        {
            OutputDebugStringA("打开了精易论坛");
            wkeNetHookRequest(job);
            return true;
        }

        //如果wkeLoadUrlBeginCallback回调里返回true，表示mb不处理此网络请求（既不会发送网络请求）。返回false，表示mb依然会发送网络请求。
        return false;
    }
    inline static void onLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len)
    {
        /*const wchar_t *str = L"百度一下";
        const wchar_t *str1 = L"下一度百";

        int slen = ::WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL);
        if (slen == 0) return;

        char utf81[100] = { 0 };
        ::WideCharToMultiByte(CP_UTF8, 0, str, -1, &utf81[0], slen, NULL, NULL);

        slen = ::WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
        if (slen == 0) return;

        char utf82[100] = { 0 };

        ::WideCharToMultiByte(CP_UTF8, 0, str1, -1, &utf82[0], slen, NULL, NULL);

        const char *b = strstr(static_cast<const char*>(buf), &utf81[0]);
        memcpy((void *)b, &utf82, slen - 1);
        */
    }

    inline static void OnWillMediaLoad(wkeWebView webView, void* param, const char* url, wkeMediaLoadInfo* info)
    {
        OutputDebugStringA(url);
    }
    inline static void OnDocumentReady2Callback(wkeWebView webView, void* param, wkeWebFrameHandle frameId)
    {
        jsRunningManager::RunJs(webView, "document.querySelector('#wp > div.wp.a_t').remove()");
    }
#endif // DEBUG


private:
    //callbacks:
    static void OnPaintUpdated(wkeWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy)
    {
#ifdef _DEBUG
        static int i;
        wstr::dbg(L"OnPaintUpdated 重画%d\n", ++i);
#endif
        //CRenderGDI* _render = (CRenderGDI*)(MbE::GetUserKeyValue(webView, "_render"));
        CRenderGDI* _render = (CRenderGDI*)param;
        _render->renderOnBlinkPaint(webView, hdc, x, y, cx, cy);
        return;
    }
    

};
