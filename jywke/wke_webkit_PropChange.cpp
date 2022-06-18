#include "wke_webkit_header.h"

#define __TEXT_TO_W(quote) L##quote      // r_winnt
#define __TEXT_TO_U(quote) u8##quote      // r_winnt
#define TEXT_TO_W(quote) __TEXT_TO_W(quote)      // r_winnt
#define TEXT_TO_U(quote) __TEXT_TO_W(quote)      // r_winnt

BOOL WINAPI wke_PropChanged_Webkit(HUNIT hUnit, INT nPropertyIndex,  // ���޸ĵ���������
                                PUNIT_PROPERTY_VALUE pPropertyVaule, // �����޸ĵ���Ӧ�������ݡ�
                                LPTSTR* ppszTipText)    //����Web�����  �µ����Ա��ı䷽��
{
    //    ֪ͨĳ����(��UD_CUSTOMIZE�������)���ݱ��û��޸�, ��Ҫ���ݸ��޸���Ӧ����
    //    �ڲ����ݼ�����, ���ȷʵ��Ҫ���´��������޸ĵ�Ԫ����, �뷵���档
    //    ע�⣺�������������ֵ�ĺϷ���У�顣
    //DWORD hWnd = wkeNotifySys(NAS_GET_HWND_OF_CWND_OBJECT, hUnit, 0);
    //PWEBKIT_PROPERTYEX data = g_wke[hWnd];
    PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);
    if ( !data ) return false;

    WEBKIT_PROPERTY& prop = data->prop;
    PWEBKIT_CTL wkectrl = data->pCtl;
    switch ( nPropertyIndex )
    {
    case PROP_URL:                //URL��ַ
    {
        data->SetUrl(pPropertyVaule->m_szText);
        wstr wzStr = wstr::A2W(pPropertyVaule->m_szText);
        if ( prop.urlW[0] )
        {
            if ( ( prop.debugShow && data->blInDesignMode ) || data->blInDesignMode == FALSE )    //������ģʽ=��,�����ģʽ=��, �������ģʽ=�� ����ת��ָ����ҳ
                wkectrl->GoUrl(wzStr.c_str());
        }
        else
        {
            wkectrl->LoadHTML(L" ");
        }

        break;
    }
    case PROP_TITLE:            //��ҳ����
        //wkectrl->prop.title= pPropertyVaule->m_szText;
        break;
    case PROP_CANCELF5RELOAD:    //��ֹF5ˢ��
        prop.DisableF5 = pPropertyVaule->m_bool;
        break;
    case PROP_NEWWINDOW:        //�����´���
        prop.isNewWnd = pPropertyVaule->m_bool;
        wkeSetNavigationToNewWindowEnable(wkectrl->GetWkeWebView(), prop.isNewWnd);
        break;
    case PROP_ISENABLECOOKIE:    //��ֹcookie
        prop.DisableCookie = pPropertyVaule->m_bool;
        wkectrl->SetCookieEnabled(!prop.DisableCookie);
        break;
    case PROP_CACHEPATH:        //����Ŀ¼
    {
        data->SetCache(pPropertyVaule->m_szText);
        data->SetCachePath();
        break;
    }
    case PROP_COOKIEPATH:        //cookieĿ¼
    {
        data->SetCookie(pPropertyVaule->m_szText);
        data->SetCookiePath();
        break;
    }
    case PROP_USERAGENT:        //User Agent
    {
        // ����vc6��֧�� u8"" , ����UAӦ��û������, �ǾͲ��ܱ�����
#define _PROP_UA_SET_VALUE(_vl) prop.pszUserAgentW = TEXT_TO_W(_vl); prop.pszUserAgent = _vl
        _str szStr = pPropertyVaule->m_szText;
        //"iPhone X\0""iPad Pro\0""��׿Galaxy S5\0""Safari\0""Chrome\0""Firefox\0""Opera\0""IE9\0""IE8\0""IE7\0\0"},
        if ( szStr == "" )
        {
            prop.pszUserAgent = "";
        }
        else if ( szStr == "iPhone X" )
        {
            _PROP_UA_SET_VALUE(UA_IPHONEX);
        }
        else if ( szStr == "iPad Pro" )
        {
            _PROP_UA_SET_VALUE(UA_IPADPRO);
        }
        else if ( szStr == "��׿Galaxy S5" )
        {
            _PROP_UA_SET_VALUE(UA_ANDROID);
        }
        else if ( szStr == "Winsows Safari" )
        {
            _PROP_UA_SET_VALUE(UA_WINSAFARI);
        }
        else if ( szStr == "Winsows Chrome" || szStr == "Ĭ��UA" )
        {
            _PROP_UA_SET_VALUE(UA_WINCHROME);
        }
        else if ( szStr == "Winsows Firefox" )
        {
            _PROP_UA_SET_VALUE(UA_WINFF);
        }
        else if ( szStr == "Winsows Opera" )
        {
            _PROP_UA_SET_VALUE(UA_WINOPERA);
        }
        else if ( szStr == "Winsows IE9" )
        {
            _PROP_UA_SET_VALUE(UA_WINIE9);
        }
        else if ( szStr == "Winsows IE8" )
        {
            _PROP_UA_SET_VALUE(UA_WINIE8);
        }
        else if ( szStr == "Winsows IE7" )
        {
            _PROP_UA_SET_VALUE(UA_WINIE7);
        }
        else
        {
            prop.pszUserAgent = data->bufPool->AddStringA(pPropertyVaule->m_szText);
            prop.pszUserAgentW = data->bufPool->AddStringWFromAnsi(pPropertyVaule->m_szText);
        }

        if ( ( prop.debugShow && data->blInDesignMode ) || data->blInDesignMode == FALSE )    //�������ʱԤ�� �������������״̬,���߲������״̬
        {
            wkectrl->SetUserAgent(prop.pszUserAgent);
            wkectrl->Reload();
        }

        break;
    }
    case PROP_DEBUG:            //���ʱ����Ԥ��
    {
        prop.debugShow = pPropertyVaule->m_bool;
        if ( prop.debugShow )
        {
            if ( prop.pszUserAgent && prop.pszUserAgent[0] )
                wkectrl->SetUserAgent(prop.pszUserAgent);
            if ( prop.urlW && prop.urlW[0] )
                wkectrl->GoUrl(prop.urlW);
        }
        else
        {
            wkectrl->LoadHTML(L" ");
        }
        break;
    }
    default:
        return FALSE;
    }

    return FALSE;
}
