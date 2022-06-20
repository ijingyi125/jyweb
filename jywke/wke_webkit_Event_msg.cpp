#include "wke_webkit_event.h"
#include <windowsx.h>


int event_notify_wke(PWEBKIT_PROPERTYEX data, int nIndex, int nCount, ...);
LRESULT wke_WebViewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

inline static int GetKey()
{
    const short ctrl = GetAsyncKeyState(VK_CONTROL);
    const short shift = GetAsyncKeyState(VK_SHIFT);
    const short alt = GetAsyncKeyState(VK_MENU);

    int key = 0;
    if ( ctrl & 0x8000 ) key |= 2; // Shift��״̬
    if ( shift & 0x8000 ) key |= 1; // Ctrl��״̬
    if ( alt & 0x8000 ) key |= 4; // Alt��״̬
    return key;
}


// ֪ͨ�¼�, ȫ�������������������Ͳ���, ���ص����¼��ķ���ֵ, ���ú���ݷ���ֵ�����Ƿ��������
// �û�����0�ŷ���0, ���򷵻�ֵ���Ƿ�0
int event_notify_wke(PWEBKIT_PROPERTYEX data, int nIndex, int nCount, ...)
{
    EVENT_NOTIFY2 eventInfo(data->dwWinFormID, data->dwUnitID, nIndex);
    PWEBKIT_CTL wke = data->pCtl;
    int nRet = 1;    // ֻ���û����ؼٲŸ�ֵΪ0, 0�ǲ�����������Ϣ

    int i;
    va_list vl;
    va_start(vl, nCount);
    eventInfo.m_nArgCount = nCount;
    for ( i = 0; i < nCount; i++ )
    {
        eventInfo.m_arg[i].m_inf.m_dtDataType = SDT_INT;
        eventInfo.m_arg[i].m_inf.m_int = va_arg(vl, int);
    }
    va_end(vl);

    nRet = NotifySys(NRS_EVENT_NOTIFY2, (DWORD)&eventInfo, 0);
    if ( nRet == 0 )    //���ݵ��������¼�ʧ��
    {
        if ( nIndex == EVENT_CHAR )
            return eventInfo.m_arg[0].m_inf.m_int;    //�ַ�����Ļ�����������ַ�
        return 1;    // ����Ĭ�Ϸ���1, ����1����Ҫ��������, ����0��ʾ��������¼�
    }

    nRet = 1;
    if ( eventInfo.m_blHasRetVal )    //�û�������һ��ֵ
    {
        if ( nIndex == EVENT_CHAR )    //�ַ����뵥������,����Ƿ���������
        {
            // ��¼�û����ص�ֵ, �����Ϊ��������ķ���ֵ
            nRet = eventInfo.m_infRetData.m_int;
        }
        else if ( !eventInfo.m_infRetData.m_bool)    
        {
            // �����ַ�����ķ���ֵ�����߼���, �����û����ؼ�, �ǾͰѷ���ֵ�ĳ�0, 0�ǲ�����������Ϣ
            nRet = 0;
        }
    }
    else if ( nIndex == EVENT_CHAR )    
    {
        // �û�û�з���ֵ, ��������¼����ַ�����, �Ǿͷ��ش��ݽ������ַ�����
        nRet = eventInfo.m_arg[0].m_inf.m_int;
    }

    return nRet;
}


// ����ǰ����¼�, ������F5, �Ǿ͸����Ƿ�F5ˢ�½��в���
inline void _isF5_down(PWEBKIT_PROPERTYEX data, UINT message, WPARAM wParam)
{
    if ( (message == WM_KEYDOWN || message == WM_SYSKEYDOWN) && wParam == VK_F5 )
    {
        //wkeCtrl = (WKECtrl*)g_wke[(int)hWnd]; 
        if ( data && data->prop.DisableF5 == FALSE ) // ��ֹF5ˢ��=��
        {
            data->pCtl->Reload();
        }
    }
}

// ���ùҽӵ���Ϣ�¼�, nEvent = �¼�����, nEvent != -1����õ������Ե��¼�, ������õ��󶨵��¼�
LRESULT call_msg_event(PWEBKIT_PROPERTYEX data, jyWebKey_Event_callBack& callType, UINT message, WPARAM wParam, LPARAM lParam, int nEvent)
{
    PWEBKIT_CTL wke = data->pCtl;
    if ( nEvent == -1 )
    {
        jyWebKit_event_mouse fun = (jyWebKit_event_mouse)callType.fun;
        if ( fun && !fun(wke->GetWkeWebView(), callType.arg, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), GetKey()) )
            return 0;
        return ::CallWindowProcW(data->oldProc, data->hWnd, message, wParam, lParam);
    }
    // �����ǵ��������Ե��¼�, �����̵��¼�����3������, �󶨵��¼���һ��webview����
    int ret = event_notify_wke(data, nEvent, 3, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), GetKey());
    if ( ret )
    {
        if ( nEvent == EVENT_CHAR )
        {
            wParam = ret; // �ַ����滻���û����ص�ֵ
            if ( wParam == 0 )
                return 0;
        }
        return ::CallWindowProcW(data->oldProc, data->hWnd, message, wParam, lParam);
    }
    return 0;
}

#define _JYWEBKIT_EVENT_MOUSE(_case, _type, _evt) \
case _case:\
    return call_msg_event(data, wke->jyEvent._type, message, wParam, lParam, (__query(data->flags, EVENT_PTR_E) ? (_evt) : -1));\
    break

LRESULT wke_WebViewWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PWEBKIT_PROPERTYEX data = GetWebkitDataFromHwnd(hWnd);
    if ( !data )
        return DefWindowProcW(hWnd, message, wParam, lParam);

    PWEBKIT_CTL wke = data->pCtl;
    WNDPROC oldProc = data->oldProc;
    if (!wke || !oldProc)return DefWindowProcW(hWnd, message, wParam, lParam);
    switch (message)
    {
        _JYWEBKIT_EVENT_MOUSE(WM_LBUTTONDOWN    , lDowm,    EVENT_LDOWN);
        _JYWEBKIT_EVENT_MOUSE(WM_LBUTTONUP      , lUp,      EVENT_LUP);
        _JYWEBKIT_EVENT_MOUSE(WM_LBUTTONDBLCLK  , lDblClk,  EVENT_LDBLCLK);

        //_JYWEBKIT_EVENT_MOUSE(WM_MBUTTONDOWN    , , );
        //_JYWEBKIT_EVENT_MOUSE(WM_MBUTTONUP      , , );
        //_JYWEBKIT_EVENT_MOUSE(WM_MBUTTONDBLCLK  , , );

        _JYWEBKIT_EVENT_MOUSE(WM_RBUTTONDOWN    , rDowm,    EVENT_RDOWN);
        _JYWEBKIT_EVENT_MOUSE(WM_RBUTTONUP      , rUp,      EVENT_RUP);
        //_JYWEBKIT_EVENT_MOUSE(WM_RBUTTONDBLCLK  , ,     );
        _JYWEBKIT_EVENT_MOUSE(WM_MOUSEMOVE      , move,     EVENT_MOUSEMOVE);

    case WM_SETFOCUS:
    {
        if ( __query(data->flags, EVENT_PTR_E) )
        {
            event_notify_wke(data, EVENT_SETFOCUS, 0);
            break;
        }
        if ( wke->jyEvent.getFocus.fun )
        {
            jyWebKit_event_focus fun = (jyWebKit_event_focus)wke->jyEvent.getFocus.fun;
            fun(wke->GetWkeWebView(), wke->jyEvent.getFocus.arg);
        }
        break;
    }
    case WM_KILLFOCUS:
    {
        if ( __query(data->flags, EVENT_PTR_E) )
        {
            event_notify_wke(data, EVENT_KILLFOCUS, 0);
            break;
        }
        if ( wke->jyEvent.killFocus.fun )
        {
            jyWebKit_event_focus fun = (jyWebKit_event_focus)wke->jyEvent.killFocus.fun;
            fun(wke->GetWkeWebView(), wke->jyEvent.killFocus.arg);
        }
        break;
    }
    case WM_HSCROLL:
    case WM_VSCROLL:
    {
        if ( __query(data->flags, EVENT_PTR_E) )
        {
            event_notify_wke(data, EVENT_SCROLL, 2, HIWORD(wParam), GetKey());
            break;
        }
        if ( wke->jyEvent.scroll.fun )
        {
            jyWebKit_event_scroll fun = (jyWebKit_event_scroll)wke->jyEvent.scroll.fun;
            if ( !fun(wke->GetWkeWebView(), wke->jyEvent.scroll.arg, HIWORD(wParam), GetKey()) )return 0;
        }
        break;
    }
    case WM_CHAR:
    {
        if ( __query(data->flags, EVENT_PTR_E) )
        {
            wParam = event_notify_wke(data, EVENT_CHAR, 1, wParam);
            if ( !wParam ) return 0;
            break;
        }
        if ( wke->jyEvent.charSet.fun )
        {
            jyWebKit_event_char fun = (jyWebKit_event_char)wke->jyEvent.charSet.fun;
            wParam = fun(wke->GetWkeWebView(), wke->jyEvent.charSet.arg, wParam);
            if ( wParam == 0 )return 0;
        }
        break;
    }
    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
    {
        if ( __query(data->flags, EVENT_PTR_E) )
        {
            int nRet = event_notify_wke(data, EVENT_KEYDOWN, 2, wParam, GetKey());
            _isF5_down(data, message, wParam);
            if ( !nRet ) return 0;
            break;
        }
        if ( wke->jyEvent.keyDowm.fun )
        {
            jyWebKit_event_keyDowm fun = (jyWebKit_event_keyDowm)wke->jyEvent.keyDowm.fun;
            int nRet = fun(wke->GetWkeWebView(), wke->jyEvent.keyDowm.arg, wParam, GetKey());
            _isF5_down(data, message, wParam);
            if ( !nRet ) return 0;
        }
        break;
    }
    case WM_SYSKEYUP:
    case WM_KEYUP:
    {
        if ( __query(data->flags, EVENT_PTR_E) )
        {
            if ( !event_notify_wke(data, EVENT_KEYUP, 2, wParam, GetKey()) )
                return 0;
            break;
        }

        if ( wke->jyEvent.keyUp.fun )
        {
            jyWebKit_event_keyDowm fun = (jyWebKit_event_keyDowm)wke->jyEvent.keyUp.fun;
            if ( !fun(wke->GetWkeWebView(), wke->jyEvent.keyUp.arg, wParam, GetKey()) )return 0;
        }
        break;
    }
    case WM_DESTROY:
    {
        BOOL isDlg = wke->isDlg;
        RemovePropW(hWnd, L"newProc");
        SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)oldProc);    //�����໯
        data->Uninit();
        delete data;
        if (isDlg)
            PostQuitMessage(0);
        return 0;
    }
    default:
        break;
        return ::CallWindowProcW(oldProc, hWnd, message, wParam, lParam);
    }

    return ::CallWindowProcW(oldProc, hWnd, message, wParam, lParam);
}


void wke_SubWebviewWindow(PWEBKIT_PROPERTYEX data)
{
    HWND hWnd = data->hWnd;
    data->oldProc = (WNDPROC)SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)wke_WebViewWndProc);
    SetPropW(hWnd, WKE_USERDATA, data);
}

