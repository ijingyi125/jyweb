#include "wke_webkit_header.h"

#define __TEXT_TO_W(quote) L##quote      // r_winnt
#define __TEXT_TO_U(quote) u8##quote      // r_winnt
#define TEXT_TO_W(quote) __TEXT_TO_W(quote)      // r_winnt
#define TEXT_TO_U(quote) __TEXT_TO_W(quote)      // r_winnt

BOOL WINAPI wke_PropChanged_Webkit(HUNIT hUnit, INT nPropertyIndex,  // 被修改的属性索引
                                PUNIT_PROPERTY_VALUE pPropertyVaule, // 用作修改的相应属性数据。
                                LPTSTR* ppszTipText)    //精易Web浏览器  下的属性被改变方法
{
    //    通知某属性(非UD_CUSTOMIZE类别属性)数据被用户修改, 需要根据该修改相应更改
    //    内部数据及外形, 如果确实需要重新创建才能修改单元外形, 请返回真。
    //    注意：必须进行所传入值的合法性校验。
    //DWORD hWnd = wkeNotifySys(NAS_GET_HWND_OF_CWND_OBJECT, hUnit, 0);
    //PWEBKIT_PROPERTYEX data = g_wke[hWnd];
    PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);
    if ( !data ) return false;

    WEBKIT_PROPERTY& prop = data->prop;
    PWEBKIT_CTL wkectrl = data->pCtl;
    switch ( nPropertyIndex )
    {
    case PROP_URL:                //URL地址
    {
        data->SetUrl(pPropertyVaule->m_szText);
        wstr wzStr = wstr::A2W(pPropertyVaule->m_szText);
        if ( prop.urlW[0] )
        {
            if ( ( prop.debugShow && data->blInDesignMode ) || data->blInDesignMode == FALSE )    //如果设计模式=真,且设计模式=真, 或者设计模式=假 则跳转到指定网页
                wkectrl->GoUrl(wzStr.c_str());
        }
        else
        {
            wkectrl->LoadHTML(L" ");
        }

        break;
    }
    case PROP_TITLE:            //网页标题
        //wkectrl->prop.title= pPropertyVaule->m_szText;
        break;
    case PROP_CANCELF5RELOAD:    //禁止F5刷新
        prop.DisableF5 = pPropertyVaule->m_bool;
        break;
    case PROP_NEWWINDOW:        //允许新窗打开
        prop.isNewWnd = pPropertyVaule->m_bool;
        wkeSetNavigationToNewWindowEnable(wkectrl->GetWkeWebView(), prop.isNewWnd);
        break;
    case PROP_ISENABLECOOKIE:    //禁止cookie
        prop.DisableCookie = pPropertyVaule->m_bool;
        wkectrl->SetCookieEnabled(!prop.DisableCookie);
        break;
    case PROP_CACHEPATH:        //缓存目录
    {
        data->SetCache(pPropertyVaule->m_szText);
        data->SetCachePath();
        break;
    }
    case PROP_COOKIEPATH:        //cookie目录
    {
        data->SetCookie(pPropertyVaule->m_szText);
        data->SetCookiePath();
        break;
    }
    case PROP_USERAGENT:        //User Agent
    {
        // 好像vc6不支持 u8"" , 而且UA应该没有中文, 那就不管编码了
#define _PROP_UA_SET_VALUE(_vl) prop.pszUserAgentW = TEXT_TO_W(_vl); prop.pszUserAgent = _vl
        _str szStr = pPropertyVaule->m_szText;
        //"iPhone X\0""iPad Pro\0""安卓Galaxy S5\0""Safari\0""Chrome\0""Firefox\0""Opera\0""IE9\0""IE8\0""IE7\0\0"},
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
        else if ( szStr == "安卓Galaxy S5" )
        {
            _PROP_UA_SET_VALUE(UA_ANDROID);
        }
        else if ( szStr == "Winsows Safari" )
        {
            _PROP_UA_SET_VALUE(UA_WINSAFARI);
        }
        else if ( szStr == "Winsows Chrome" || szStr == "默认UA" )
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

        if ( ( prop.debugShow && data->blInDesignMode ) || data->blInDesignMode == FALSE )    //允许设计时预览 并且现在是设计状态,或者不是设计状态
        {
            wkectrl->SetUserAgent(prop.pszUserAgent);
            wkectrl->Reload();
        }

        break;
    }
    case PROP_DEBUG:            //设计时允许预览
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
