#include "wke_webkit_header.h"






//����Web�����  �µĻ�ȡ�������Է���
BOOL WINAPI wke_PropGetData_Webkit(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule)
{
    // ȡĳ�������ݵ�pPropertyValue��, �ɹ�������, ���򷵻ؼ١�
    // typedef BOOL (WINAPI *PFN_GET_PROPERTY_DATA) (
    // HUNIT hUnit,
    // INT nPropertyIndex,
    // PUNIT_PROPERTY_VALUE pPropertyValue);   // ������������ȡ���Ե����ݡ�

    // ע�⣺��������ʱ(�ɵ���PFN_CREATE_UNITʱ��blInDesignMode��������), 
    // pPropertyValue���뷵�����洢��ֵ�����������ʱ(blInDesignModeΪ��), ����
    // ����ʵ�ʵĵ�ǰʵʱֵ��
    // ����˵, �༭�򴰿ڵ�Ԫ��\"����\"����, ���ʱ���뷵���ڲ��������ֵ, ��
    // ����ʱ�ͱ������ GetWindowText ȥʵʱ��ȡ��
    PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);
    if ( !data ) return false;

    WEBKIT_PROPERTY& prop = data->prop;
    PWEBKIT_CTL wkectrl = data->pCtl;

    BOOL bRet = TRUE;
    switch ( nPropertyIndex )
    {
    case PROP_URL:                //URL��ַ
        pPropertyVaule->m_szText = prop.url;
        break;
    case PROP_TITLE:            //��ҳ����
        //pPropertyVaule->m_szText = prop.title.GetBuffer(prop.url.GetLength());
        pPropertyVaule->m_szText = (char*)wkectrl->GetTitle();
        break;
    case PROP_CANCELF5RELOAD:    //��ֹF5ˢ��
        pPropertyVaule->m_bool = prop.DisableF5;
        break;
    case PROP_ISENABLECOOKIE:    //��ֹcookie
        pPropertyVaule->m_bool = prop.DisableCookie;
        break;
    case PROP_NEWWINDOW:        // �����´��ڴ�
        pPropertyVaule->m_bool = prop.isNewWnd;
        break;
    case PROP_CACHEPATH:        //����Ŀ¼
        pPropertyVaule->m_szText = (char*)prop.pszCachePath;
        break;
    case PROP_COOKIEPATH:        //cookieĿ¼
        pPropertyVaule->m_szText = (char*)prop.pszCookiePath;
        break;
    case PROP_USERAGENT:        //User Agent
        pPropertyVaule->m_szText = (char*)prop.pszUserAgent;
        break;
    case PROP_DEBUG:            //����ʱ����Ԥ��
        pPropertyVaule->m_bool = prop.debugShow;
    default:
        return FALSE;
    }

    return bRet;
}