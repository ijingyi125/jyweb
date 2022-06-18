#pragma once
#include "wke_typedef.h"
#include "WKECtrl.h"

#define WKE_USERDATA    L"{B419B3FF-F46F-42E2-A836-F28452158010}"

#define UA_IPHONEX      "Mozilla/5.0 (iPhone; CPU iPhone OS 11_0 like Mac OS X) AppleWebKit/604.1.38 (KHTML, like Gecko) Version/11.0 Mobile/15A372 Safari/604.1\0\0"
#define UA_IPADPRO      "Mozilla/5.0 (iPad; CPU OS 11_0 like Mac OS X) AppleWebKit/604.1.34 (KHTML, like Gecko) Version/11.0 Mobile/15A5341f Safari/604.1\0"
#define UA_ANDROID      "Mozilla/5.0 (Linux; Android 5.0; SM-G900P Build/LRX21T) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Mobile Safari/537.36\0"
#define UA_WINSAFARI    "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50\0"
#define UA_WINCHROME    "Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.100 Safari/537.36\0"
#define UA_WINFF        "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:6.0) Gecko/20100101 Firefox/6.0\0"
#define UA_WINOPERA     "Opera/9.80 (Windows NT 10.0; U; zh-cn) Presto/2.9.168 Version/11.50\0"
#define UA_WINIE9       "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 10.0; Win64; x64; Trident/5.0; .NET CLR 2.0.50727; SLCC2; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; Tablet PC 2.0; .NET4.0E)\0"
#define UA_WINIE8       "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 10.0; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; .NET4.0C; InfoPath.3)\0"
#define UA_WINIE7       "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 10.0; WOW64)\0"

// 1.7.6.12, 1.7�ǰ汾��, 6.12������
#define WEBKIT_VERSION          MAKELONG(MAKEWORD(1, 7), MAKEWORD(6, 12))   // �汾��, ���Ը��ݰ汾����һЩ��ͬ�Ĵ���

#define PROP_URL                0    // URL��ַ
#define PROP_TITLE              1    // ��ҳ����
#define PROP_CANCELF5RELOAD     2    // ��ֹF5ˢ��
#define PROP_ISENABLECOOKIE     3    // ��ֹcookie
#define PROP_CACHEPATH          4    // ����Ŀ¼
#define PROP_COOKIEPATH         5    // cookieĿ¼
#define PROP_USERAGENT          6    // User Agent
#define PROP_DEBUG              7    // ����ʱԤ��
#define PROP_NEWWINDOW          8    // �����´��ڴ�

// �����������Խṹ, ���е����Զ���������, Ҫ�����µ����Ծ��������
// ˳��Ҫ���, ����û��ʹ��һ����־��ȷ���汾��, ֻ����������
typedef struct _WEBKIT_PROPERTY
{
    LPCSTR              url;                // URL��ַ
    LPCSTR              title;              // ��ҳ����
    BOOL                DisableF5;          // ��ֹF5ˢ��
    BOOL                DisableCookie;      // ��ֹcookie
    LPCSTR              pszCachePath;       // ����Ŀ¼
    LPCSTR              pszCookiePath;      // cookieĿ¼
    LPCSTR              pszUserAgent;       // User Agent
    BOOL                debugShow;          // ����ʱԤ��
    BOOL                isNewWnd;           // �����´��ڴ�

    LPCWSTR             runPath;            // ��������Ŀ¼
    // W���ı�, �����ò���, �ȱ�����
    LPCWSTR             urlW;               // URL��ַ
    LPCWSTR             titleW;             // ��ҳ����
    LPCWSTR             pszCachePathW;      // ����Ŀ¼
    LPCWSTR             pszCookiePathW;     // cookieĿ¼
    LPCWSTR             pszUserAgentW;      // User Agent



}WEBKIT_PROPERTY, * PWEBKIT_PROPERTY;





// ���ʹ�õĽṹ, ��¼�������ص�������Ϣ
typedef struct _WEBKIT_PROPERTYEX : WKE_STRUCT_BASE
{
    WEBKIT_PROPERTY     prop;               // ���ʹ�õ�����
    PBUFFER_POOL        bufPool;            // �����
    PWEBKIT_CTL         pCtl;               // �������

    // ��յ�ǰ��������, �������ͷ�����
    inline void clear()
    {
        memset(this, 0, sizeof(*this));
    }

    // ���뼸����Ҫʹ�õĶ���
    inline void init()
    {
        bufPool = new BUFFER_POOL;
        pCtl    = new WEBKIT_CTL;
        bufPool->reserve(1024 * 4); // Ԥ������4kb�ڴ�, �����Ļ�����ػ��Զ�����

        prop.url = "";
        prop.title = "";
        prop.pszCachePath = "";
        prop.pszCookiePath = "";
        prop.pszUserAgent = "";

        prop.runPath = L"";

        prop.urlW = L"";
        prop.titleW = L"";
        prop.pszCachePathW = L"";
        prop.pszCookiePathW = L"";
        prop.pszUserAgentW = L"";


    }

    // �ͷ���Щ����Ķ���
    inline void Uninit()
    {
        delete bufPool;
        delete pCtl;
    }

    // ���û���·��, �����м���Ƿ�Ϊ����·��, ��������·����ƴװ·��, ʹ�õ��Ǽ�¼������ֵ, ���ģʽֱ�ӷ���
    inline void SetCachePath()
    {
        wstr path(260);
        make_path(path, prop.pszCookiePathW);
        pCtl->SetLocalStorageFullPath(path.c_str());

    }

    // ����cookie·��, �����м���Ƿ�Ϊ����·��, ��������·����ƴװ·��, ʹ�õ��Ǽ�¼������ֵ, ���ģʽֱ�ӷ���
    inline void SetCookiePath()
    {
        wstr path(260);
        make_path(path, prop.pszCookiePathW);
        pCtl->SetCookieJarPath(path.c_str());

    }

#define _SET_TEXT_FUN(_fun, _text) \
    inline void _fun(LPCWSTR pStr)\
    {\
        _set_buf_text(bufPool, &prop._text##W, pStr);\
        prop._text = bufPool->AddStringAFromUnicode(prop._text##W);\
    }\
    inline void _fun(LPCSTR pStr)\
    {\
        _set_buf_text(bufPool, &prop._text, pStr);\
        prop._text##W = bufPool->AddStringWFromAnsi(prop._text);\
    }


    _SET_TEXT_FUN(SetUrl, url)
    _SET_TEXT_FUN(SetTitle, title)
    _SET_TEXT_FUN(SetCache, pszCachePath)
    _SET_TEXT_FUN(SetCookie, pszCookiePath)
    _SET_TEXT_FUN(SetUA, pszUserAgent)

private:
    inline void make_path(wstr& path, LPCWSTR s)
    {
        if ( blInDesignMode )
            return;  // ���ģʽֻ��¼ֵ, ������·����Ϣ

        if ( s && wcsncmp(s + 1, L":\\", 2) != 0 )
            path.assign(prop.runPath);  // ����Ĳ�������·��, û�д�����Ϣ, ��Ҫ����·��

        path.append(s);

        if ( path.back() != '\\' )
            path.append(L"\\");
    }

}WEBKIT_PROPERTYEX, * PWEBKIT_PROPERTYEX;




//����Web�����  �µĸ������Է���
BOOL WINAPI wke_PropUpDate_Webkit(HUNIT hUnit, INT nPropertyIndex);

//����Web�����  �µĵ����Ի��򷽷�
BOOL WINAPI wke_PropPopDlg_Webkit(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData);

//����Web�����  �µ����Ա��ı䷽��
BOOL WINAPI wke_PropChanged_Webkit(HUNIT hUnit, INT nPropertyIndex,  // ���޸ĵ���������
                                PUNIT_PROPERTY_VALUE pPropertyVaule, // �����޸ĵ���Ӧ�������ݡ�
                                LPTSTR* ppszTipText);    //����Web�����  �µ����Ա��ı䷽��

//����Web�����  �µĻ�ȡ�������Է���
BOOL WINAPI wke_PropGetData_Webkit(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule);

//����Web�����  �µĻ�ȡȫ�����Է���
HGLOBAL WINAPI wke_PropGetDataAll_Webkit(HUNIT hUnit);


// ��������, ��������䵽�����
LPBYTE ParsePropData_webkit(PWEBKIT_PROPERTYEX data, LPBYTE pPropData, int nDataSize);

// ����ص�, ��Ҫ�ҽ�wke���е��¼�
void OnwkeCallbackAll(wkeWebView hWebView, PWEBKIT_PROPERTYEX data);

inline PWEBKIT_PROPERTYEX GetWebkitDataFromHunit(HUNIT hUnit)
{
    return (PWEBKIT_PROPERTYEX)GetDataFromHunit(hUnit);
}
inline PWEBKIT_PROPERTYEX GetWebkitDataFromHwnd(HWND hWnd)
{
    return (PWEBKIT_PROPERTYEX)GetPropW(hWnd, WKE_USERDATA);
}
inline PWEBKIT_PROPERTYEX GetWebkitDataFromArg(PMDATA_INF pInf)
{
    PWEBKIT_PROPERTYEX data = 0;
    GethUnitFromArgInf(pInf, (PVOID*)&data);
    return data;
}

bool wke_SetDllPath();
bool wke_SetDllPath(LPCWSTR path);
bool wke_SetDllPath(LPCSTR path);