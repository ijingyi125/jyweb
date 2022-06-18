#include "wke_webkit_header.h"






//精易Web浏览器  下的获取单个属性方法
BOOL WINAPI wke_PropGetData_Webkit(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
{
    // 取某属性数据到pPropertyValue中, 成功返回真, 否则返回假。
    // typedef BOOL (WINAPI *PFN_GET_PROPERTY_DATA) (
    // HUNIT hUnit,
    // INT nPropertyIndex,
    // PUNIT_PROPERTY_VALUE pPropertyValue);   // 用作接收欲读取属性的数据。

    // 注意：如果在设计时(由调用PFN_CREATE_UNIT时的blInDesignMode参数决定), 
    // pPropertyValue必须返回所存储的值。如果在运行时(blInDesignMode为假), 必须
    // 返回实际的当前实时值。
    // 比如说, 编辑框窗口单元的\"内容\"属性, 设计时必须返回内部所保存的值, 而
    // 运行时就必须调用 GetWindowText 去实时获取。
    PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);
    if ( !data ) return false;

    WEBKIT_PROPERTY& prop = data->prop;
    PWEBKIT_CTL wkectrl = data->pCtl;

    BOOL bRet = TRUE;
    switch ( nPropertyIndex )
    {
    case PROP_URL:                //URL地址
        pPropertyVaule->m_szText = prop.url;
        break;
    case PROP_TITLE:            //网页标题
        //pPropertyVaule->m_szText = prop.title.GetBuffer(prop.url.GetLength());
        pPropertyVaule->m_szText = (char*)wkectrl->GetTitle();
        break;
    case PROP_CANCELF5RELOAD:    //禁止F5刷新
        pPropertyVaule->m_bool = prop.DisableF5;
        break;
    case PROP_ISENABLECOOKIE:    //禁止cookie
        pPropertyVaule->m_bool = prop.DisableCookie;
        break;
    case PROP_NEWWINDOW:        // 允许新窗口打开
        pPropertyVaule->m_bool = prop.isNewWnd;
        break;
    case PROP_CACHEPATH:        //缓存目录
        pPropertyVaule->m_szText = (char*)prop.pszCachePath;
        break;
    case PROP_COOKIEPATH:        //cookie目录
        pPropertyVaule->m_szText = (char*)prop.pszCookiePath;
        break;
    case PROP_USERAGENT:        //User Agent
        pPropertyVaule->m_szText = (char*)prop.pszUserAgent;
        break;
    case PROP_DEBUG:            //调试时允许预览
        pPropertyVaule->m_bool = prop.debugShow;
    default:
        return FALSE;
    }

    return bRet;
}