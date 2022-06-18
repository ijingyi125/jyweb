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

// 1.7.6.12, 1.7是版本号, 6.12是日期
#define WEBKIT_VERSION          MAKELONG(MAKEWORD(1, 7), MAKEWORD(6, 12))   // 版本号, 可以根据版本号做一些不同的处理

#define PROP_URL                0    // URL地址
#define PROP_TITLE              1    // 网页标题
#define PROP_CANCELF5RELOAD     2    // 禁止F5刷新
#define PROP_ISENABLECOOKIE     3    // 禁止cookie
#define PROP_CACHEPATH          4    // 缓存目录
#define PROP_COOKIEPATH         5    // cookie目录
#define PROP_USERAGENT          6    // User Agent
#define PROP_DEBUG              7    // 调试时预览
#define PROP_NEWWINDOW          8    // 允许新窗口打开

// 浏览器组件属性结构, 所有的属性都存在这里, 要是有新的属性就往里面加
// 顺序不要搞错, 这里没有使用一个标志来确定版本号, 只能往后增加
typedef struct _WEBKIT_PROPERTY
{
    LPCSTR              url;                // URL地址
    LPCSTR              title;              // 网页标题
    BOOL                DisableF5;          // 禁止F5刷新
    BOOL                DisableCookie;      // 禁止cookie
    LPCSTR              pszCachePath;       // 缓存目录
    LPCSTR              pszCookiePath;      // cookie目录
    LPCSTR              pszUserAgent;       // User Agent
    BOOL                debugShow;          // 调试时预览
    BOOL                isNewWnd;           // 允许新窗口打开

    LPCWSTR             runPath;            // 程序运行目录
    // W版文本, 好像用不上, 先保留吧
    LPCWSTR             urlW;               // URL地址
    LPCWSTR             titleW;             // 网页标题
    LPCWSTR             pszCachePathW;      // 缓存目录
    LPCWSTR             pszCookiePathW;     // cookie目录
    LPCWSTR             pszUserAgentW;      // User Agent



}WEBKIT_PROPERTY, * PWEBKIT_PROPERTY;





// 组件使用的结构, 记录跟组件相关的所有信息
typedef struct _WEBKIT_PROPERTYEX : WKE_STRUCT_BASE
{
    WEBKIT_PROPERTY     prop;               // 组件使用的属性
    PBUFFER_POOL        bufPool;            // 缓存池
    PWEBKIT_CTL         pCtl;               // 组件对象

    // 清空当前对象数据, 不负责释放数据
    inline void clear()
    {
        memset(this, 0, sizeof(*this));
    }

    // 申请几个需要使用的对象
    inline void init()
    {
        bufPool = new BUFFER_POOL;
        pCtl    = new WEBKIT_CTL;
        bufPool->reserve(1024 * 4); // 预先申请4kb内存, 不够的话缓存池会自动申请

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

    // 释放那些申请的对象
    inline void Uninit()
    {
        delete bufPool;
        delete pCtl;
    }

    // 设置缓存路径, 这里有检测是否为完整路径, 不是完整路径就拼装路径, 使用的是记录的属性值, 设计模式直接返回
    inline void SetCachePath()
    {
        wstr path(260);
        make_path(path, prop.pszCookiePathW);
        pCtl->SetLocalStorageFullPath(path.c_str());

    }

    // 设置cookie路径, 这里有检测是否为完整路径, 不是完整路径就拼装路径, 使用的是记录的属性值, 设计模式直接返回
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
            return;  // 设计模式只记录值, 不设置路径信息

        if ( s && wcsncmp(s + 1, L":\\", 2) != 0 )
            path.assign(prop.runPath);  // 输入的不是完整路径, 没有磁盘信息, 需要加上路径

        path.append(s);

        if ( path.back() != '\\' )
            path.append(L"\\");
    }

}WEBKIT_PROPERTYEX, * PWEBKIT_PROPERTYEX;




//精易Web浏览器  下的更新属性方法
BOOL WINAPI wke_PropUpDate_Webkit(HUNIT hUnit, INT nPropertyIndex);

//精易Web浏览器  下的弹出对话框方法
BOOL WINAPI wke_PropPopDlg_Webkit(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData);

//精易Web浏览器  下的属性被改变方法
BOOL WINAPI wke_PropChanged_Webkit(HUNIT hUnit, INT nPropertyIndex,  // 被修改的属性索引
                                PUNIT_PROPERTY_VALUE pPropertyVaule, // 用作修改的相应属性数据。
                                LPTSTR* ppszTipText);    //精易Web浏览器  下的属性被改变方法

//精易Web浏览器  下的获取单个属性方法
BOOL WINAPI wke_PropGetData_Webkit(HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule);

//精易Web浏览器  下的获取全部属性方法
HGLOBAL WINAPI wke_PropGetDataAll_Webkit(HUNIT hUnit);


// 解析属性, 把数据填充到组件上
LPBYTE ParsePropData_webkit(PWEBKIT_PROPERTYEX data, LPBYTE pPropData, int nDataSize);

// 处理回调, 需要挂接wke所有的事件
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