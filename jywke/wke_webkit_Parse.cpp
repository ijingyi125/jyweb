#include "wke_webkit_header.h"




LPBYTE ParsePropData_webkit(PWEBKIT_PROPERTYEX data, LPBYTE pPropData, int nDataSize)
{
    LPBYTE pPropEnd = pPropData + nDataSize;
    LPBYTE pBuf = pPropData;
    WEBKIT_PROPERTY& prop = data->prop;
    PBUFFER_POOL pool = data->bufPool;

    if ( nDataSize <= 0 || pPropData == pPropEnd )
        return 0;

    int version         = read_int32(pBuf);  // 版本号, 从1.7开始记录的是Unicode文本

    //TODO 加个 || 1, 让他一定走里面, 暂时都使用A版, 好像没必要用到W版, 属性都是A版的属性
    // 为了以后可能使用W版属性, 现在也把W版属性保存起来
    if ( version == 1 || 1 )
    {
        // 版本号=1是老版本使用
        prop.DisableF5      = read_int32(pBuf); // 禁止F5刷新
        prop.DisableCookie  = read_int32(pBuf); // 禁止cookie
        prop.urlW           = pool->AddStringWFromAnsi(read_str_A(pBuf));   // URL地址
        prop.pszCachePathW  = pool->AddStringWFromAnsi(read_str_A(pBuf));   // 缓存目录
        prop.pszCookiePathW = pool->AddStringWFromAnsi(read_str_A(pBuf));   // cookie目录
        prop.pszUserAgentW  = pool->AddStringWFromAnsi(read_str_A(pBuf));   // User Agent
        prop.isNewWnd       = read_int32(pBuf); // 允许新窗口打开

    }
    // 暂时不使用, 如果要用, 根据上面的代码修改一下就可以了
    //else
    //{
    //    // 剩下的都是新版本, 更新的版本的话, 以后再说
    //    prop.urlW           = pool->AddStringW(read_str_W(pBuf));   // URL地址
    //    prop.titleW         = pool->AddStringW(read_str_W(pBuf));   // 网页标题
    //    prop.DisableF5      = read_int32(pBuf); // 禁止F5刷新
    //    prop.DisableCookie  = read_int32(pBuf); // 禁止cookie
    //    prop.pszCachePathW  = pool->AddStringW(read_str_W(pBuf));   // 缓存目录
    //    prop.pszCookiePathW = pool->AddStringW(read_str_W(pBuf));   // cookie目录
    //    prop.pszUserAgentW  = pool->AddStringW(read_str_W(pBuf));   // User Agent
    //    prop.debugShow      = read_int32(pBuf); // 调试时预览
    //    prop.isNewWnd       = read_int32(pBuf); // 允许新窗口打开
    //}

    // 多保存一份A版的文本, 说不定哪里会用上
    prop.titleW         = L"";
    prop.title          = "";
    prop.url            = pool->AddStringAFromUnicode(prop.urlW);
    prop.pszCachePath   = pool->AddStringAFromUnicode(prop.pszCachePathW);
    prop.pszCookiePath  = pool->AddStringAFromUnicode(prop.pszCookiePathW);
    prop.pszUserAgent   = pool->AddStringAFromUnicode(prop.pszUserAgentW);

#ifdef _DEBUG
    int readSize = pPropEnd - pPropData;
    if ( readSize != nDataSize )
        __debugbreak(); // 读取的属性尺寸和记录的尺寸不同, 调试版下个断点调试
#endif

    assert(pBuf == pPropEnd);

    return pBuf;
}

//精易Web浏览器  下的获取全部属性方法
HGLOBAL WINAPI wke_PropGetDataAll_Webkit(HUNIT hUnit)
{
    assert(hUnit != NULL);
    PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);
    if ( !data ) return 0;
    WEBKIT_PROPERTY& prop = data->prop;

    _str buf(0x1000);
    int size = 0;

    //! 写入属性还是按A版写入
    size += write_int32(buf, WEBKIT_VERSION);       // 版本号
    size += write_str_A(buf, prop.url);             // URL地址
    size += write_str_A(buf, prop.title);           // 网页标题
    size += write_int32(buf, prop.DisableF5);       // 禁止F5刷新
    size += write_int32(buf, prop.DisableCookie);   // 禁止cookie
    size += write_str_A(buf, prop.pszCachePath);    // 缓存目录
    size += write_str_A(buf, prop.pszCookiePath);   // cookie目录
    size += write_str_A(buf, prop.pszUserAgent);    // User Agent
    size += write_int32(buf, prop.debugShow);       // 调试时预览
    size += write_int32(buf, prop.isNewWnd);        // 允许新窗口打开

    HGLOBAL hGlobal = ::GlobalAlloc(GMEM_MOVEABLE, size);
    if ( hGlobal )
    {
        PVOID pGlobal = ::GlobalLock(hGlobal);
        if ( pGlobal )
        {
            LPCVOID pBuffer = buf.c_str();
            memcpy(pGlobal, pBuffer, size);
            ::GlobalUnlock(hGlobal);
        }
    }
    return hGlobal;
}
