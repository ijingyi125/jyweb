#pragma once
#include "wke/MbE.h"


typedef BOOL(__stdcall* jyWebKit_event_mouse)( wkeWebView webView, void* param, int x, int y, int AsyncKeyState );
typedef void(__stdcall* jyWebKit_event_focus)( wkeWebView webView, void* param );
typedef BOOL(__stdcall* jyWebKit_event_keyDowm)( wkeWebView webView, void* param, int key, int AsyncKeyState );
typedef int(__stdcall* jyWebKit_event_char)( wkeWebView webView, void* param, int ch );
typedef BOOL(__stdcall* jyWebKit_event_scroll)( wkeWebView webView, void* param, int pos, int AsyncKeyState );
typedef BOOL(__stdcall* jyWebKit_event_arg1)( wkeWebView webView, void* param, int arg );
typedef BOOL(__stdcall* jyWebKit_event_arg2)( wkeWebView webView, void* param, int arg, int arg2 );
typedef BOOL(__stdcall* jyWebKit_event_arg3)( wkeWebView webView, void* param, int arg, int arg2, int arg3 );
typedef BOOL(__stdcall* jyWebKit_event_arg4)( wkeWebView webView, void* param, int arg, int arg2, int arg3, int arg4 );
typedef BOOL(__stdcall* jyWebKit_event_arg5)( wkeWebView webView, void* param, int arg, int arg2, int arg3, int arg4, int arg5 );
typedef BOOL(__stdcall* jyWebKit_event_arg6)( wkeWebView webView, void* param, int arg, int arg2, int arg3, int arg4, int arg5, int arg6 );
typedef BOOL(__stdcall* jyWebKit_event_arg7)( wkeWebView webView, void* param, int arg, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7 );
typedef BOOL(__stdcall* jyWebKit_event_arg8)( wkeWebView webView, void* param, int arg, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8 );

typedef struct _jyWebKey_Event_callBack
{
    DWORD fun;
    void* arg;
}jyWebKey_Event_callBack;
typedef struct _JYWEBKIT_EVENT
{
    jyWebKey_Event_callBack arg[14];
    jyWebKey_Event_callBack lDowm;
    jyWebKey_Event_callBack lUp;
    jyWebKey_Event_callBack lDblClk;
    jyWebKey_Event_callBack rDowm;
    jyWebKey_Event_callBack rUp;
    jyWebKey_Event_callBack move;
    jyWebKey_Event_callBack getFocus;
    jyWebKey_Event_callBack killFocus;
    jyWebKey_Event_callBack keyDowm;
    jyWebKey_Event_callBack keyUp;
    jyWebKey_Event_callBack charSet;
    jyWebKey_Event_callBack scroll;
    jyWebKey_Event_callBack getAllCookie;
    jyWebKey_Event_callBack paint;
}JYWEBKIT_EVENT, * LPJYWEBKIT_EVENT;


#define EVENT_PTR_E                1    // 触发事件的是易语言组件
#define EVENT_PTR_NEWWINDOW        2    // 触发事件的是新弹出的窗口
// 事件指针, 根据标志来确定是哪个在触发事件




class WKECtrl : public MbE
{
public:
    JYWEBKIT_EVENT jyEvent;
    BOOL isDlg;
public:
    WKECtrl::WKECtrl() :MbE()
    {
        memset(&jyEvent, 0, sizeof(jyEvent));
        isDlg = 0;
    }

    virtual WKECtrl::~WKECtrl()
    {

    }

    // 创建易语言用的窗口, 外面一层标签, 内部是mb窗口
    inline HWND create(HWND hParentWnd, DWORD dwStyle, int nID, int x, int y, int cx, int cy, void* lParam, wkeWindowType type = WKE_WINDOW_TYPE_CONTROL)
    {
        bool bRet = MbE::Create(type, hParentWnd, x, y, cx, cy);
        WKECtrl_OnPaint();
        HWND hWnd = MbE::GetWindowHandle();
        if ((GetClassLongPtrW(hWnd, GCL_STYLE) & CS_DBLCLKS) == 0) //如果没有双击的样式,加上一个,如果不需要双击事件,这里可以屏蔽
        {
            SetClassLongPtrW(hWnd, GCL_STYLE, GetClassLongPtrW(hWnd, GCL_STYLE) | CS_DBLCLKS);    // 没有 CS_DBLCLKS 这个标志不会触发双击,只会触发两次单击
        }
        return hWnd;
    }

    inline void callEvent(jyWebKey_Event_callBack& evt)
    {
        if ( evt.fun )
        {
            jyWebKit_event_focus fun = (jyWebKit_event_focus)evt.fun;
            fun(GetWkeWebView(), evt.arg);
        }
    }
    void WKECtrl_OnPaint()
    {
        wkeOnPaintUpdated(MbE::GetWkeWebView(), callback_OnPaintUpdated, this);
    }

private:
    static void callback_OnPaintUpdated(wkeWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy)
    {
        WKECtrl* wke = (WKECtrl*)param;
        //#ifdef _DEBUG
        //    static int i;
        //    wstr::dbg(L"callback_OnPaintUpdated 重画%d\n", ++i);
        //#endif
        bool bRet = false;
        if ( wke->jyEvent.paint.fun )
        {
            typedef bool ( CALLBACK* pfn_E_paint )( wkeWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy );
            pfn_E_paint fun = (pfn_E_paint)wke->jyEvent.paint.fun;
            bRet = fun(webView, wke->jyEvent.paint.arg, hdc, x, y, cx, cy);
        }
        //if (!bRet)
        //{
        //    CRenderGDI* render = wke->GetWkeRender();
        //    render->renderOnBlinkPaint(webView, hdc, x, y, cx, cy);
        //}
        return;
    }

};

typedef WKECtrl WEBKIT_CTL, * PWEBKIT_CTL;