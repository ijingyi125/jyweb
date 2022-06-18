#include "wke_webkit_header.h"




LPBYTE ParsePropData_webkit(PWEBKIT_PROPERTYEX data, LPBYTE pPropData, int nDataSize)
{
    LPBYTE pPropEnd = pPropData + nDataSize;
    LPBYTE pBuf = pPropData;
    WEBKIT_PROPERTY& prop = data->prop;
    PBUFFER_POOL pool = data->bufPool;

    if ( nDataSize <= 0 || pPropData == pPropEnd )
        return 0;

    int version         = read_int32(pBuf);  // �汾��, ��1.7��ʼ��¼����Unicode�ı�

    //TODO �Ӹ� || 1, ����һ��������, ��ʱ��ʹ��A��, ����û��Ҫ�õ�W��, ���Զ���A�������
    // Ϊ���Ժ����ʹ��W������, ����Ҳ��W�����Ա�������
    if ( version == 1 || 1 )
    {
        // �汾��=1���ϰ汾ʹ��
        prop.DisableF5      = read_int32(pBuf); // ��ֹF5ˢ��
        prop.DisableCookie  = read_int32(pBuf); // ��ֹcookie
        prop.urlW           = pool->AddStringWFromAnsi(read_str_A(pBuf));   // URL��ַ
        prop.pszCachePathW  = pool->AddStringWFromAnsi(read_str_A(pBuf));   // ����Ŀ¼
        prop.pszCookiePathW = pool->AddStringWFromAnsi(read_str_A(pBuf));   // cookieĿ¼
        prop.pszUserAgentW  = pool->AddStringWFromAnsi(read_str_A(pBuf));   // User Agent
        prop.isNewWnd       = read_int32(pBuf); // �����´��ڴ�

    }
    // ��ʱ��ʹ��, ���Ҫ��, ��������Ĵ����޸�һ�¾Ϳ�����
    //else
    //{
    //    // ʣ�µĶ����°汾, ���µİ汾�Ļ�, �Ժ���˵
    //    prop.urlW           = pool->AddStringW(read_str_W(pBuf));   // URL��ַ
    //    prop.titleW         = pool->AddStringW(read_str_W(pBuf));   // ��ҳ����
    //    prop.DisableF5      = read_int32(pBuf); // ��ֹF5ˢ��
    //    prop.DisableCookie  = read_int32(pBuf); // ��ֹcookie
    //    prop.pszCachePathW  = pool->AddStringW(read_str_W(pBuf));   // ����Ŀ¼
    //    prop.pszCookiePathW = pool->AddStringW(read_str_W(pBuf));   // cookieĿ¼
    //    prop.pszUserAgentW  = pool->AddStringW(read_str_W(pBuf));   // User Agent
    //    prop.debugShow      = read_int32(pBuf); // ����ʱԤ��
    //    prop.isNewWnd       = read_int32(pBuf); // �����´��ڴ�
    //}

    // �ౣ��һ��A����ı�, ˵�������������
    prop.titleW         = L"";
    prop.title          = "";
    prop.url            = pool->AddStringAFromUnicode(prop.urlW);
    prop.pszCachePath   = pool->AddStringAFromUnicode(prop.pszCachePathW);
    prop.pszCookiePath  = pool->AddStringAFromUnicode(prop.pszCookiePathW);
    prop.pszUserAgent   = pool->AddStringAFromUnicode(prop.pszUserAgentW);

#ifdef _DEBUG
    int readSize = pPropEnd - pPropData;
    if ( readSize != nDataSize )
        __debugbreak(); // ��ȡ�����Գߴ�ͼ�¼�ĳߴ粻ͬ, ���԰��¸��ϵ����
#endif

    assert(pBuf == pPropEnd);

    return pBuf;
}

//����Web�����  �µĻ�ȡȫ�����Է���
HGLOBAL WINAPI wke_PropGetDataAll_Webkit(HUNIT hUnit)
{
    assert(hUnit != NULL);
    PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);
    if ( !data ) return 0;
    WEBKIT_PROPERTY& prop = data->prop;

    _str buf(0x1000);
    int size = 0;

    //! д�����Ի��ǰ�A��д��
    size += write_int32(buf, WEBKIT_VERSION);       // �汾��
    size += write_str_A(buf, prop.url);             // URL��ַ
    size += write_str_A(buf, prop.title);           // ��ҳ����
    size += write_int32(buf, prop.DisableF5);       // ��ֹF5ˢ��
    size += write_int32(buf, prop.DisableCookie);   // ��ֹcookie
    size += write_str_A(buf, prop.pszCachePath);    // ����Ŀ¼
    size += write_str_A(buf, prop.pszCookiePath);   // cookieĿ¼
    size += write_str_A(buf, prop.pszUserAgent);    // User Agent
    size += write_int32(buf, prop.debugShow);       // ����ʱԤ��
    size += write_int32(buf, prop.isNewWnd);        // �����´��ڴ�

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
