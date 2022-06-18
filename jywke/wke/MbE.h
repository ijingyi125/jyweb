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

        //if (GetModuleHandleW(L"node.dll"))    // �Ѿ����ع���node.dll
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


        //wkeOnPaintUpdated(_webview, MbE::OnPaintUpdated, _render);    //Ĭ���¼������뺬�У����Է������
        SetCspCheckEnable(false);
        SetNpapiPluginsEnabled(true);
        SetNavigationToNewWindowEnable(true);
        return true;
    }

    //��ȡĿǰapi�汾��
    inline unsigned int GetVersion() { return wkeVersion(); }

    //�ӳ���miniblink��������
    inline void GC(long delayMS) { wkeGC(GetWkeWebView(), delayMS); }

    //��ȡҳ����
    inline int GetWidth() { return wkeGetWidth(GetWkeWebView()); }

    //��ȡ��ҳ�Ű�����Ŀ��
    inline int GetContentWidth() { return wkeGetContentWidth(GetWkeWebView()); }

    //��ȡҳ��߶�
    inline int GetHeight() { return wkeGetHeight(GetWkeWebView()); }

    //��ȡ��ҳ�Ű�����ĸ߶�
    inline int GetContentHeight() { return wkeGetContentHeight(GetWkeWebView()); }

    //��ȡwebview��DC
    inline HDC GetViewDC() { return wkeGetViewDC(GetWkeWebView()); }

    //��ȡwebveiw��Ӧ�Ĵ��ھ����ʵ�ֺ�wkeGetWindowHandle��ȫ��ͬ
    inline HWND GetHostHWND() { return wkeGetHostHWND(GetWkeWebView()); }
    inline HWND GetWindowHandle() { return wkeGetWindowHandle(GetWkeWebView()); }
    inline void DestroyWebWindow() { wkeDestroyWebWindow(GetWkeWebView()); }

    inline void ShowWindow(bool showFlag) { wkeShowWindow(GetWkeWebView(), showFlag); }
    inline void EnableWindow(bool enableFlag) { wkeEnableWindow(GetWkeWebView(), enableFlag); }

    inline void MoveWindow(int x, int y, int width, int height) { wkeMoveWindow(GetWkeWebView(), x, y, width, height); }

    //�����ڸ����ڻ���Ļ�����
    inline void MoveToCenter() { wkeMoveToCenter(GetWkeWebView()); }

    //����webview�ǽ���̬�����webveiw�����˴��ڣ�����Ҳ���н���
    inline void SetFocus() { wkeSetFocus(GetWkeWebView()); }

    inline void KillFocus() { wkeKillFocus(GetWkeWebView()); }

    //��ȡ�༭����Ǹ��α��λ��
    inline wkeRect GetCaretRect() { return wkeGetCaretRect(GetWkeWebView()); }

    inline void SetWindowRect(RECT rect)
    {
        if ( GetWkeWebView() != NULL )
        {
            SetWindowPos(_parentHWND, NULL, 0, 0, rect.right, rect.bottom, SWP_NOMOVE);
            wkeResize(GetWkeWebView(), rect.right, rect.bottom);
        }
    }

    //����ҳ������ϵ����Ĭ����1
    inline void SetZoomFactor(float factor) { wkeSetZoomFactor(GetWkeWebView(), factor); }

    //��ȡҳ������ϵ��
    inline float GetZoomFactor() { return wkeGetZoomFactor(GetWkeWebView()); }

    inline int GetCursorInfoType() { return wkeGetCursorInfoType(GetWkeWebView()); }

    //inline wkeWebView CreateWebView() { return wkeCreateWebView(); }

    inline void DestroyWebView() { wkeDestroyWebView(GetWkeWebView()); }

    inline void SetWindowTitle(const utf8* title) { wkeSetWindowTitle(GetWkeWebView(), title); }
    inline void SetWindowTitle(const wchar_t* title) { wkeSetWindowTitleW(GetWkeWebView(), title); }

    //////////////////////////////////////////////////////////////////////////////
    /*
    ����mbģ���Ӳ���豸��������Ҫ����αװ�ֻ��豸����
    device���豸���ַ�������ȡֵ�У�
    "navigator.maxTouchPoints"    ��ʱ paramInt ��Ҫ�����ã���ʾ touch �ĵ���
    "navigator.platform"    ��ʱ paramStr ��Ҫ�����ã���ʾjs���ȡ�� navigator.platform�ַ���
    "navigator.hardwareConcurrency"    ��ʱ paramInt ��Ҫ�����ã���ʾjs���ȡ�� navigator.hardwareConcurrency ����ֵ
    "screen.width"    ��ʱ paramInt ��Ҫ�����ã���ʾjs���ȡ�� screen.width ����ֵ
    "screen.height"    ��ʱ paramInt ��Ҫ�����ã���ʾjs���ȡ�� screen.height ����ֵ
    "screen.availWidth"    ��ʱ paramInt ��Ҫ�����ã���ʾjs���ȡ�� screen.availWidth ����ֵ
    "screen.availHeight"    ��ʱ paramInt ��Ҫ�����ã���ʾjs���ȡ�� screen.availHeight ����ֵ
    "screen.pixelDepth"    ��ʱ paramInt ��Ҫ�����ã���ʾjs���ȡ�� screen.pixelDepth ����ֵ
    "scre    en.pixelDepth"    Ŀǰ�ȼ���"screen.pixelDepth"
    "window.devicePixelRatio"    ͬ��
    */
    inline void SetDeviceParameter(const char* device, const char* paramStr, int paramInt, float paramFloat) { wkeSetDeviceParameter(GetWkeWebView(), device, paramStr, paramInt, paramFloat); }

    //��������mb�Ĵ��롣�˾���ȫ����Ч
    inline void SetProxy(const wkeProxy* proxy) { wkeSetProxy(proxy); }

    //��������mb�Ĵ��롣�˾�������ض�webview��Ч
    inline void SetViewProxy(wkeProxy* proxy) { wkeSetViewProxy(GetWkeWebView(), proxy); }

    //void wkeSetMemoryCacheEnable(wkeWebView webView, bool b)

    //��������ģʽ�������������Ϣ���Զ�ת���ɴ�����Ϣ
    inline void SetTouchEnabled(bool b) { wkeSetTouchEnabled(GetWkeWebView(), b); }

    //�����ر������Ϣ�������ڿ��������󣬹ر������Ϣ
    inline void SetMouseEnabled(bool b) { wkeSetMouseEnabled(GetWkeWebView(), b); }

    //�رպ󣬵�a��ǩ�����ᵯ���´��ڣ������ڱ�������ת
    inline void SetNavigationToNewWindowEnable(bool b) { wkeSetNavigationToNewWindowEnable(GetWkeWebView(), b); }

    //�رպ󣬿����齫����ֹ����ʱ�������κο�������������ajax����������iframe
    inline void SetCspCheckEnable(bool b) { wkeSetCspCheckEnable(GetWkeWebView(), b); }

    //�����ر�npapi�������flash
    inline void SetNpapiPluginsEnabled(bool b) { wkeSetNpapiPluginsEnabled(GetWkeWebView(), b); }

    //������ͷģʽ�������󣬽�������Ⱦҳ�棬��������ҳ���ܡ��˹��ܷ�������ʵ��һЩ���棬����ˢ������
    inline void SetHeadlessEnabled(bool b) { wkeSetHeadlessEnabled(GetWkeWebView(), b); }

    //����webview��UA
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

    //DOM�ĵ��ṹ�Ƿ�������
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

    //����ҳ��cookie��
    //ע�⣺cookie�������curl��cookieд����һ�������ǣ�PERSONALIZE = 123; expires = Monday, 13 - Jun - 2022 03:04 : 55 GMT; domain = .fidelity.com; path = / ; secure
    inline void ClearCookie() { wkeClearCookie(GetWkeWebView()); }
    inline void SetCookie(const utf8* url, const utf8* cookie) { wkeSetCookie(GetWkeWebView(), url, cookie); }
    inline void PerformCookieCommand(wkeCookieCommand command) { wkePerformCookieCommand(GetWkeWebView(), command); }
    inline void VisitAllCookie(void* param, wkeCookieVisitor pfn) { wkeVisitAllCookie(GetWkeWebView(), param, pfn); }
    //wkeVisitAllCookie //δʵ�֡�

    //������ر�cookie
    //ע�⣺����ӿ�ֻ��Ӱ��blink������������curl�����Ի��ǻ�����curl��cookie�ļ�
    inline void SetCookieEnabled(bool enable) { wkeSetCookieEnabled(GetWkeWebView(), enable); }

    inline bool IsCookieEnabled() { return wkeIsCookieEnabled(GetWkeWebView()); }

    //����cookie�ı����ļ�Ŀ¼��Ĭ���ǵ�ǰĿ¼��cookies���ڵ�ǰĿ¼�ġ�cookie.dat����
    inline void SetCookieJarPath(const /*wchar_t*/WCHAR* path) { wkeSetCookieJarPath(GetWkeWebView(), path); }

    //����cookie��ȫ·��+�ļ������硰c:\mb\cookie.dat��
    inline void SetCookieJarFullPath(const /*wchar_t*/WCHAR* path) { wkeSetCookieJarFullPath(GetWkeWebView(), path); }

    //////////////////////////////////////////////////////////////////////////

    //����local storage��ȫ·�����硰c:\mb\LocalStorage\��
    //ע�⣺����ӿ�ֻ�ܽ���Ŀ¼��
    inline void SetLocalStorageFullPath(const /*wchar_t*/WCHAR* path) { wkeSetLocalStorageFullPath(GetWkeWebView(), path); }

    //////////////////////////////////////////////////////////////////////////

    //����������δʵ��
    inline void SetMediaVolume(float volume) { wkeSetMediaVolume(GetWkeWebView(), volume); }

    inline float GetMediaVolume() { return wkeGetMediaVolume(GetWkeWebView()); }

    //////////////////////////////////////////////////////////////////////////

    //�ж�frameId�Ƿ�����frame
    inline bool IsMainFrame(wkeWebFrameHandle frameId) { return wkeIsMainFrame(GetWkeWebView(), frameId); }

    //��ȡ��frame�ľ��
    inline wkeWebFrameHandle WebFrameGetMainFrame() { return wkeWebFrameGetMainFrame(GetWkeWebView()); }

    //��ȡframe��Ӧ��url
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
            OutputDebugStringA("���˾�����̳");
            wkeNetHookRequest(job);
            return true;
        }

        //���wkeLoadUrlBeginCallback�ص��ﷵ��true����ʾmb��������������󣨼Ȳ��ᷢ���������󣩡�����false����ʾmb��Ȼ�ᷢ����������
        return false;
    }
    inline static void onLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len)
    {
        /*const wchar_t *str = L"�ٶ�һ��";
        const wchar_t *str1 = L"��һ�Ȱ�";

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
        wstr::dbg(L"OnPaintUpdated �ػ�%d\n", ++i);
#endif
        //CRenderGDI* _render = (CRenderGDI*)(MbE::GetUserKeyValue(webView, "_render"));
        CRenderGDI* _render = (CRenderGDI*)param;
        _render->renderOnBlinkPaint(webView, hdc, x, y, cx, cy);
        return;
    }
    

};
