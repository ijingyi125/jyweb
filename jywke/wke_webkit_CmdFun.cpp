#include "wke_webkit_header.h"
#include "CwkeTBInfo.h"
#include "wke_webkit_event.h"


PWEBKIT_PROPERTYEX wke_wkectrl(PMDATA_INF pArgInf, HWND* pHwnd)
{
    PWEBKIT_PROPERTYEX data = 0;
    if ( pArgInf->m_unit.m_dwUnitID )
    {
        // ������0,�����,=0����������
        data = (PWEBKIT_PROPERTYEX)GetWebkitDataFromArg(pArgInf);
    }
    else
    {
        // �ߵ��������������
        data = (PWEBKIT_PROPERTYEX)*pArgInf[0].m_ppCompoundData;
    }

    if ( data && pHwnd )	// ���´��ڵ�����
    {
        if ( pHwnd )
            *pHwnd = data->hWnd;
    }
    return data;
}

#define WKE_CTRL(_pHwnd) PWEBKIT_PROPERTYEX data = wke_wkectrl(pArgInf, _pHwnd); if(!data) return; PWEBKIT_CTL wke = data->pCtl













// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).�����ҳ, ����˵��: "���ָ����ҳ��"
// ����<1>: URL��ַ SDT_TEXT, ����˵��: "���������URL��ַ,���url��ַ������,�봫��utf8�����ı�."
EXTERN_C void WKE_NAME(0, SetUrl)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->LoadURL(pArgInf[1].m_pText);
}

// ���ø�ʽ: SDT_TEXT (����Web�����/�������ڲ���).ȡ��ҳURL, ����˵��: "��ȡ��ǰ��ҳURL��ַ��"
// �޲���
EXTERN_C void WKE_NAME(1, GetUrl)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    LPCSTR szUrl = wke->GetUrl();
    pRetData->m_dtDataType = SDT_TEXT;
    pRetData->m_pText = CloneTextData((char*)szUrl);

}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).����HTML�ı�, ����˵��: "����HTML�����ı���ע�⣬�����ҳ��������Ҫ���룬����Ҫ���н��б���ת����"
// ����<1>: HTML�ı� SDT_TEXT, ����˵��: "һ��HTML�ı�,�봫������ҳ��ͬ������ı�."
EXTERN_C void WKE_NAME(2, wke_LoadHtml)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->LoadHTML(pArgInf[1].m_pText);
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).����HTML�ļ�, ����˵��: "����HTML�ļ���"
// ����<1>: HTML�ļ� SDT_TEXT, ����˵��: "HTML�ļ���,���·��������,�봫��utf8�����ı�."
EXTERN_C void WKE_NAME(3, wke_LoadFile)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->LoadFile(pArgInf[1].m_pText);
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).ǰ��, ����˵��: "�����ǰ�����"
// �޲���
EXTERN_C void WKE_NAME(4, wke_GoForward)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

    WKE_CTRL(0);
    wke->GoForward();
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).����, ����˵��: "������������"
// �޲���
EXTERN_C void WKE_NAME(5, wke_CanGoBack)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

    WKE_CTRL(0);
    wke->GoBack();
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).ֹͣ����, ����˵��: "ֹͣ���ص�ǰ��ҳ��"
// �޲���
EXTERN_C void WKE_NAME(6, wke_StopLoading)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->StopLoading();
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).��������, ����˵��: "�������뵱ǰ��ҳ,�൱��ˢ�����"
// �޲���
EXTERN_C void WKE_NAME(7, wke_Reload)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->Reload();
}

inline void __fun_webkie_makejs(_str& retStr, wkeWebView webView, int frameID, int mode, const char* name, int index, const char* jsCode)
{
    CwkeTBInfo js;		// ִ��js

    if ( mode <= 0 ) mode = 2;
    if ( index <= 0 )index = 1;


    int frameCount = js.form_GetFrameCount(webView);	// �������
    name = ( name && name[0] ) ? name : "html";

    if ( frameID > frameCount ) frameID = frameCount;

    js.form_SetFrame(webView, mode, name, frameID);
    _str str(2000);
    str.assign("return ").append(js.CreateElementSelectorStr(webView, mode, name, index));
    str.append(".").append(jsCode);
    jsValue vl = js.RunJS(webView, str);
    jsExecState es = wkeGlobalExec(webView);
    retStr = jsToString(es, vl);	// ָ����ܾ�ȡ������ָ��Ԫ�ص���ҳ�ı�,δָ��Ԫ�ؾ�Ĭ��ȡ html,Ȼ�󷵻�
}

// ���ø�ʽ: SDT_TEXT (����Web�����/�������ڲ���).ȡ��ҳԴ��, ����˵��: "���ص�ǰ��ҳԴ��,�����������,��ʹ�� \"wke_Utf8ToAnsi()\" ת����"
// ����<1>: [���ID SDT_INT], ����˵��: "ID��1��ʼ,Ϊ�ջ���С��0,Ĭ��ȡ�����"
// ����<2>: [���ģʽ SDT_INT], ����˵��: "Ĭ��Ϊ #���ģʽ_JS���ʽ, ��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: [ѡ����ʽ SDT_TEXT], ����˵��: "Ϊ����ȡ������ҳ,ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(8, GetWebPageSource)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    _str ret;			// ��Ҫִ�е�js����
    __fun_webkie_makejs(ret, wke->GetWkeWebView(), pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, "outerHTML");
    pRetData->m_pText = CloneTextData((char*)ret.c_str());	//����utf8
}



// ���ø�ʽ: SDT_TEXT (����Web�����/�������ڲ���).��ȡCookie, ����˵��: "��ȡ��ǰ��ҳ��Cookie��"
// �޲���
EXTERN_C void WKE_NAME(9, wke_GetCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    LPCSTR szCookie = wke->GetCookie();
    pRetData->m_dtDataType = SDT_TEXT;
    pRetData->m_pText = CloneTextData((char*)szCookie);
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).����Cookie_������������_�����_����cookie_CURL_������_����cookie_CURL��node_dll�ṩ�Ľӿ�_û���κζ��η�װ, ����˵��: "֧�ֿⲻ�ṩ�κ����cookie���ж��η�װ������, ����cookie��ص������ԭ�����node.dll\r\n        ����cookie����� ����cookie_CURL(), ������ԭ�����node.dll��wkeSetCookie�ӿ�\r\n"
// ����<1>: URL SDT_TEXT, ����˵��: "������cookie����վ����,���url��ַ������,�봫��utf8�����ı�."
// ����<2>: COOKIE SDT_TEXT, ����˵��: "Ҫ���õ�Cookie�����cookieʹ��;���������磺 a=1;b=2;c=3;d=4;"
EXTERN_C void WKE_NAME(10, wke_SetCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    MessageBoxW(0, L"֧�ֿⲻ�ṩ�κ����cookie���ж��η�װ������, ����cookie��ص������ԭ�����node.dll\r\n"
                L"����cookie����� ����cookie_CURL(), ������ԭ�����node.dll��wkeSetCookie�ӿ�\r\n"
                L"cookie������ⲻ�ٻش�", L"�����õ�����", 0);
    return;

    //WKE_CTRL(0);
    //_str cookie(pArgInf[2].m_pText);
    //LPSTR p = strtok(cookie.GetPtr(), ";");
    //_str s1;
    //if (pArgInf[1].m_dtDataType == _SDT_NULL)
    //{
    //	s1 = ";PRODUCTINFO=webxpress; path=/; secure";
    //}
    //else
    //{
    //	s1 = _str(";PRODUCTINFO=webxpress; domain=") + pArgInf[1].m_pText + "; path=/; secure";
    //}
    ////_str s1(";PRODUCTINFO=webxpress; path=/; secure");
    //const wchar_t* jsCode =
    //    L"function clearAllCookie() {"
    //    L"    var keys = document.cookie.match(/[^ =;]+(?=\\=)/g);"
    //    L"    if(keys) {"
    //    L"        for(var i = keys.length; i--;)"
    //    L"            document.cookie = keys[i] + '=0;expires=' + new Date(0).toUTCString();"
    //    L"    }"
    //    L"} clearAllCookie();";

    //////wke->RunJS(L"$.removeCookie('jy',{ path: '/'});");	// ���ԭ��cookie
    ////wke->RunJS(jsCode);	// ���ԭ��cookie
    ////wke->ClearCookie();

    //while (p)
    //{
    //	//TODO ����cookie��û�����
    //	_str tmp(p);
    //	//tmp.replace(' ', 0);
    //	_str s2(tmp + s1);

    //	wke->SetCookie(pArgInf[1].m_pText, s2.c_str());
    //	p = strtok(NULL, ";");
    //}


    ////wkeSetCookie(webView, "localhost", "a=1;PRODUCTINFO=webxpress; domain=.localhost; path=/; secure");
    ////wkeSetCookie(webView, "localhost", "b=2;PRODUCTINFO=webxpress; domain=.localhost; path=/; secure");
    ////wkeSetCookie(webView, "localhost", "c=3;PRODUCTINFO=webxpress; domain=.localhost; path=/; secure");
    ////wkeSetCookie(webView, "localhost", "d=4;expires=Monday, 13-Jun-2022 03:04:55 GMT; domain=.localhost; path=/; secure");
    //// name=value; Domain=Domain; Path=httponly;secure
    ////var tmp = string.Format("{0}={1}; Domain={2}; {3} Path={4}", item.Name, item.Value, item.Domain, ((item.HttpOnly) ? "httponly; " : ""), (item.Secure ? "secure" : ""));

}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).ִ��Cookie����, ����˵��: "ִ��cookie������"
// ����<1>: �������� SDT_INT, ����˵��: "0 = �������Cookie , 1 = �������session , 2 = ˢ��cookie�ļ�  3= ��������cookie�ļ�"
EXTERN_C void WKE_NAME(11, wke_ExecuteCookeCommand)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    switch ( pArgInf[1].m_int )
    {
    case 0:
        //wke->RunJS(L"$.removeCookie('name',{ path: '/'});");	// ���ԭ��cookie
        wke->PerformCookieCommand(wkeCookieCommandClearAllCookies);
        break;
    case 1:
        wke->PerformCookieCommand(wkeCookieCommandClearSessionCookies);
        break;
    case 2:
        wke->PerformCookieCommand(wkeCookieCommandFlushCookiesToFile);
        break;
    case 3:
        wke->PerformCookieCommand(wkeCookieCommandReloadCookiesFromFile);
        break;
    default:
        wke->PerformCookieCommand(wkeCookieCommandClearAllCookies);
    }
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).����UserAgent, ����˵��: "���������Ĭ�ϵ�UserAgent��"
// ����<1>: UserAgent SDT_TEXT, ����˵��: "UserAgent�ı�,���url��ַ������,�봫��utf8�����ı�."
EXTERN_C void WKE_NAME(12, wke_SetUserAgent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->SetUserAgent(pArgInf[1].m_pText);
}

// ���ø�ʽ: SDT_BOOL (����Web�����/�������ڲ���).���ô���, ����˵��: "Ϊָ����webView���ô���"
// ����<1>: �������� SDT_INT, ����˵��: "#��������_��ͷ�ĳ���"
// ����<2>: �����ַ SDT_TEXT, ����˵��: "����ip��˿�,�� 122.132.123.123:666"
// ����<3>: [�û��� SDT_TEXT], ����˵��: "�����û���,û��������"
// ����<4>: [���� SDT_TEXT], ����˵��: "��������,û��������"
EXTERN_C void WKE_NAME(13, SetProxy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = FALSE;
    wkeProxy proxy;
    memset(&proxy, 0, sizeof(wkeProxy));
    proxy.type = (wkeProxyType)( pArgInf[1].m_int );
    _str str(pArgInf[2].m_pText), IP, port;
    IP = str.left(":");
    port = str.right(":");
    //if (IP == "" || port == "") return;

    if ( !IP.empty() )
        strcpy(proxy.hostname, IP.c_str());	//�����ַ
    proxy.port = port.stoi();	//�˿�

    if ( pArgInf[3].m_pText && *( pArgInf[3].m_pText ) )
        strcpy(proxy.username, pArgInf[3].m_pText);

    if ( pArgInf[4].m_pText != NULL && *( pArgInf[4].m_pText ) )
        strcpy(proxy.password, pArgInf[4].m_pText);

    wke->SetProxy(&proxy);
    pRetData->m_bool = TRUE;
}

// ���ø�ʽ: SDT_FLOAT (����Web�����/�������ڲ���).������ҳ����, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(14, SetWebVolume)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    // UNDONE ������ҳ����,wkeδʵ��
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).����ý������, ����˵��: "������ҳý��������"
// ����<1>: ���� SDT_INT, ����˵��: "�����õ�����"
EXTERN_C void WKE_NAME(15, SetMediVolume)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    // UNDONE wkeSetMediaVolume ����ý������,wkeδʵ��
}

// ���ø�ʽ: SDT_INT (����Web�����/�������ڲ���).ȡWebView, ����˵��: "����WebViewָ�롣"
// �޲���
EXTERN_C void WKE_NAME(16, GetWebView)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_int = (int)wke->GetWkeWebView();
}

// ���ø�ʽ: SDT_BOOL (����Web�����/�������ڲ���).�Ƿ����ǰ��, ����˵��: "����������Ƿ����ִ��ǰ�����"
// �޲���
EXTERN_C void WKE_NAME(17, IsGoRorward)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = wke->CanGoForward();
}

// ���ø�ʽ: SDT_BOOL (����Web�����/�������ڲ���).�Ƿ���Ժ���, ����˵��: "����������Ƿ����ִ�к������"
// �޲���
EXTERN_C void WKE_NAME(18, CanGoBack)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = wke->CanGoBack();
}

// ���ø�ʽ: SDT_BOOL (����Web�����/�������ڲ���).�Ƿ�������, ����˵��: "������ҳ�Ƿ������ɡ�"
// �޲���
EXTERN_C void WKE_NAME(19, IsLodingCompleted)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = wke->IsLoadingCompleted();
}

// ���ø�ʽ: SDT_BOOL (����Web�����/�������ڲ���).�ĵ��Ƿ����, ����˵��: "�����ĵ��Ƿ��Ѿ�����"
// �޲���
EXTERN_C void WKE_NAME(20, IsDocumentReady)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_bool = wke->IsDocumentReady();
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).��ʱ��������, ����˵��: "�ӳ���miniblink�������ա�"
// ����<1>: ��ʱʱ�� SDT_INT, ����˵��: "��λ����,�ӳ���miniblink��������"
EXTERN_C void WKE_NAME(154, wkeGC)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->GC(pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_BOOL (����Web�����/�������ڲ���).���û�����, ����˵��: "�����ݺ�webView�󶨡�"
// ����<1>: ���� SDT_TEXT, ����˵��: "���ü������ͨ���������ȡ�����õ�ֵ"
// ����<2>: ��ֵ SDT_INT, ����˵��: "��Ҫ���õļ�ֵ"
EXTERN_C void WKE_NAME(157, wke_SetUserKeyValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->SetUserKeyValue(pArgInf[1].m_pText, (void*)pArgInf[2].m_int);
}

// ���ø�ʽ: SDT_INT (����Web�����/�������ڲ���).ȡ�û�����, ����˵��: "ȡ�� ���û�����() ���õ�ֵ��"
// ����<1>: ���� SDT_TEXT, ����˵��: "���û�����() �����õļ���"
EXTERN_C void WKE_NAME(158, wke_GetUserKeyValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_int = (int)wke->GetUserKeyValue(pArgInf[1].m_pText);
}

// ���ø�ʽ: SDT_INT ȡ��ҳ���, ����˵��: "ȡ�� miniblink �Ĵ��ھ����"
// �޲���
EXTERN_C void WKE_NAME(159, wke_GetWindowHandle)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    HWND hWnd = 0;
    WKE_CTRL(&hWnd);
    pRetData->m_int = (int)hWnd;
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).����Cookie_����_������������_�����_����cookie_CURL_������_����cookie_CURL��node_dll�ṩ�Ľӿ�_û���κζ��η�װ, ����˵��: "֧�ֿⲻ�ṩ�κ����cookie���ж��η�װ������, ����cookie��ص������ԭ�����node.dll\r\n        ����cookie����� ����cookie_CURL(), ������ԭ�����node.dll��wkeSetCookie�ӿ�\r\n"
// ����<1>: URL SDT_TEXT, ����˵��: "������cookie����վ����,���url��ַ������,�봫��utf8�����ı�."
// ����<2>: COOKIE SDT_TEXT, ����˵��: "Ҫ���õ�Cookie����ʽ��Ҫ����curl�ĸ�ʽ�����磺abc=1;expires=Monday, 1-Jun-2019 00:01:01 GMT; path=/; secure"
EXTERN_C void WKE_NAME(161, wke_SetSingleCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //WKE_CTRL(0);
    ////_str s1(_str("a=1;PRODUCTINFO=webxpress; domain=.") + pArgInf[1].m_pText + "baidu.com; path=/; secure");
    //_str cook(_str(pArgInf[2].m_pText) + ";PRODUCTINFO=webxpress; domain=." + pArgInf[1].m_pText + "; path=/; secure");
    //wke->SetCookie(pArgInf[1].m_pText, cook.c_str());
    MessageBoxW(0, L"֧�ֿⲻ�ṩ�κ����cookie���ж��η�װ������, ����cookie��ص������ԭ�����node.dll\r\n"
                L"����cookie����� ����cookie_CURL(), ������ԭ�����node.dll��wkeSetCookie�ӿ�\r\n"
                L"cookie������ⲻ�ڻش�", L"�����õ�����", 0);
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).�������cookie, ����˵��: "�����ǰwke������cookie��"
// �޲���
EXTERN_C void WKE_NAME(166, wke_clearCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    //wke->RunJS(L"$.removeCookie('name',{ path: '/'});");	// ���ԭ��cookie
    wke->ClearCookie();
}

// ���ø�ʽ: SDT_BOOL (����Web�����/�������ڲ���).�����´���, ����˵��: "������Ĭ��Ϊ��,���ڱ����ڴ�,������ \"�����������´���\" �¼�\r\n    Ϊ��ʱ�ᴥ�� \"�����������´���\" �¼�\r\n    �����ҳ��js hook�˵���¼�,Ȼ����window.open��,��ô ��ֹ�´���() �������Ч,��ֹ���ǻᵯ���´���\r\n    ����Ҫ�´��ڴ򿪵Ŀ����� �����������´��� �¼��·��� \"��\",����������\r\n    Ϊ����ȡ��ǰ״̬, ��Ϊ��ʱ����ֵ�����塣\r\n"
// ����<1>: [�Ƿ��ֹ SDT_BOOL], ����˵��: "�� = ��ֹ, �� = ����ֹ, ���� = ȡֵ, �ò�����Ϊ��ʱ����ֵ�����塣"
EXTERN_C void WKE_NAME(168, wke_IsEnableNewWnd)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    bool b = (bool)pArgInf[1].m_bool;
    WKE_CTRL(0);
    wke->SetNavigationToNewWindowEnable(b);
    data->prop.isNewWnd = b;
}

HBITMAP wke_Create32Bitmap(HDC hdc, int width, int height)
{
    BITMAPINFO bm = { 0 };
    bm.bmiHeader.biSize = 44;
    bm.bmiHeader.biWidth = width;
    bm.bmiHeader.biHeight = height;
    bm.bmiHeader.biPlanes = 1;
    bm.bmiHeader.biBitCount = 32;
    bm.bmiHeader.biSizeImage = bm.bmiHeader.biWidth * bm.bmiHeader.biHeight * bm.bmiHeader.biBitCount / 8;
    void* p;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bm, 0, &p, 0, 0);
    return hBitmap;
}

LPBYTE wke_saveBitmap(HDC hdc, HBITMAP hBitmap, int& dwSize)
{
    BITMAP bitmap = { 0 };
    if ( !GetObject(hBitmap, sizeof(bitmap), &bitmap) )
        return NULL;
    BITMAPFILEHEADER* head_file = 0;
    BITMAPINFOHEADER* head_info = 0;
    LPBYTE pMem = 0;	// ����ֵ,��¼����λͼ

    int nWidth = bitmap.bmWidth, nHeight = bitmap.bmHeight;
    int nPlanes = bitmap.bmPlanes, bitCount = bitmap.bmBitsPixel;

    int dwBitsSize = nWidth * nHeight * bitCount / 8; // λͼ���ݴ�С

    // ���ɵ�λͼ�ļ���С = λͼ���ݴ�С + �ļ�ͷ��Ϣ + λͼ��Ϣͷ
    dwSize = dwBitsSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    pMem = new BYTE[dwSize];
    memset(pMem, 0, dwSize);

    head_file = (BITMAPFILEHEADER*)pMem;
    head_file->bfType = 0x4D42;	//19778	λͼ�ļ�ͷ��־,"BM" 
    head_file->bfSize = dwSize;	// ���ɵ��ļ���С
    head_file->bfReserved1 = 0;	// ����
    head_file->bfReserved2 = 0;	// ����
    head_file->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);	// ͼ������ƫ��

    head_info = (BITMAPINFOHEADER*)( pMem + sizeof(BITMAPFILEHEADER) );	// �����ļ�ͷ�ṹ����

    head_info->biSize = sizeof(BITMAPINFOHEADER);
    head_info->biWidth = bitmap.bmWidth;
    head_info->biHeight = bitmap.bmHeight;
    head_info->biPlanes = bitmap.bmPlanes;
    head_info->biBitCount = bitmap.bmBitsPixel;

    GetDIBits(hdc, hBitmap, 0, bitmap.bmHeight, pMem + ( head_file->bfOffBits ), (BITMAPINFO*)head_info, NULL);
    return pMem;
}

// ���ø�ʽ: SDT_BIN (����Web�����/�������ڲ���).��ͼ, ����˵��: "��ͼָ������������������"
// ����<1>: [��� SDT_INT], ����˵��: "���ջ���С��0 = 0, Ĭ��Ϊ0"
// ����<2>: [���� SDT_INT], ����˵��: "���ջ���С��0 = 0, Ĭ��Ϊ0"
// ����<3>: [��� SDT_INT], ����˵��: "���ջ���С��0 = ��������,Ĭ��Ϊ��������"
// ����<4>: [�߶� SDT_INT], ����˵��: "���ջ���С��0 = ������߶�,Ĭ��Ϊ������߶�"
EXTERN_C void WKE_NAME(171, wke_screenshot)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    HWND hWnd = 0;
    WKE_CTRL(&hWnd);
    HDC hdc = wke->GetViewDC();
    RECT rc = { 0 };
    GetClientRect(hWnd, &rc);
    rc.right = rc.right - rc.left;
    rc.bottom = rc.bottom - rc.top;

    if ( pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_int > 0 ) rc.left = pArgInf[1].m_int;
    if ( pArgInf[2].m_dtDataType != _SDT_NULL && pArgInf[2].m_int > 0 ) rc.top = pArgInf[2].m_int;
    if ( pArgInf[3].m_dtDataType != _SDT_NULL && pArgInf[3].m_int > 0 ) rc.right = pArgInf[3].m_int;
    if ( pArgInf[4].m_dtDataType != _SDT_NULL && pArgInf[4].m_int > 0 ) rc.bottom = pArgInf[4].m_int;

    HDC hDCMem = CreateCompatibleDC(0);
    HBITMAP hBitmap = wke_Create32Bitmap(hDCMem, rc.right, rc.bottom);
    HBITMAP hBitmapOld = (HBITMAP)SelectObject(hDCMem, hBitmap);

    // ��MB��dc�п���ָ��λ�õ��Լ�������dc��
    BitBlt(hDCMem, 0, 0, rc.right, rc.bottom, hdc, rc.left, rc.top, SRCCOPY);

    int dwSize = 0;
    LPBYTE pMem = wke_saveBitmap(hDCMem, hBitmap, dwSize);

    pRetData->m_pBin = CloneBinData(pMem, dwSize);
    delete[] pMem;
    SelectObject(hDCMem, hBitmapOld);
    DeleteObject(hBitmap);
    DeleteDC(hDCMem);
}

// ���ø�ʽ: SDT_TEXT (����Web�����/�������ڲ���).ȡ��ҳ�ı�, ����˵��: "ȡָ�����ָ��Ԫ�ػ���ȡ����html���ı�,������html���"
// ����<1>: [���ID SDT_INT], ����˵��: "ID��1��ʼ,Ϊ�ջ���С��0,Ĭ��ȡ�����"
// ����<2>: [���ģʽ SDT_INT], ����˵��: "Ĭ��Ϊ #���ģʽ_JS���ʽ, ��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: [ѡ����ʽ SDT_TEXT], ����˵��: "Ϊ����ȡ������ҳ,ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(180, wke_GetInnerText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    _str ret;			// ��Ҫִ�е�js����
    __fun_webkie_makejs(ret, wke->GetWkeWebView(), pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, "outerText");
    pRetData->m_pText = CloneTextData((char*)ret.c_str());	//����utf8
}

// ���ø�ʽ: SDT_BOOL (�������ڲ���).����, ����˵��: "��һ��webView���ӵ���������,���Ӻ����ʹ�ñ�������κη���, �ɹ�������, ʧ�ܷ��ؼ�"
// ����<1>: [weiView SDT_INT], ����˵��: "Ϊ�ջ���Ϊ0,���������,��0ֵ�������һ��webView�����ʧ��,�´��ڴ������ �¼��е�webView,����������ʽ��ȡ����webView"
EXTERN_C void WKE_NAME(182, Attach)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = FALSE;
    if ( pArgInf[1].m_int == 0 || pArgInf[1].m_dtDataType == _SDT_NULL )
    {
        pArgInf[0].m_ppCompoundData[0] = 0;
        pRetData->m_bool = TRUE;
        return;
    }
    wkeWebView webView = (wkeWebView)pArgInf[1].m_int;
    HWND hWnd = wkeGetWindowHandle(webView);
    if ( !hWnd ) return;

    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)GetWebkitDataFromHwnd(hWnd);
    if ( !data )return;

    pArgInf[0].m_ppCompoundData[0] = data;
    pRetData->m_bool = TRUE;
}

// ���ø�ʽ: _SDT_NULL (�������ڲ���).�´��ڹ��캯��, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(183, newWndIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //MessageBoxA(0, "���캯��", "��ʼ��", 0);
    //LPWKECtrl wke = new WKECtrl;
    pArgInf[0].m_ppCompoundData[0] = 0;
    //wke->pThis = pArgInf[0].m_ppCompoundData;
    return;
}

// ���ø�ʽ: _SDT_NULL (�������ڲ���).�´��ڸ��ƹ��캯��, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(184, newWndCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //MessageBoxA(0, "���ƹ��캯��", "��ʼ��", 0);

    //����������A=B,pArgInf[0]��A   
    //CwkeTBInfo* pA= (CwkeTBInfo*)*pArgInf[0].m_ppCompoundData;  
    //CwkeTBInfo* pB= (CwkeTBInfo*)*pArgInf[1].m_ppCompoundData;  
    //���Բ���ֱ�Ӱ�Bָ�븳ֵ��A   
}

// ���ø�ʽ: _SDT_NULL (�������ڲ���).�´�����������, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(185, newWndDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //MessageBoxA(0, "��������", "��ʼ��", 0);

    pArgInf[0].m_ppCompoundData[0] = 0;
}

// ���ø�ʽ: SDT_BOOL (�������ڲ���).�Ƿ��Ѵ���, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(186, newWndIsCreate)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = FALSE;
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)pArgInf[0].m_ppCompoundData[0];
    if ( !data )return;	// ָ��Ϊ�����ʾδ��ʼ��

    if ( !( data->hWnd ) || !data->pCtl->WebView() ) return;		// û�б��洰�ڻ�webViewҲ��δ��ʼ��
    if ( !IsWindow(data->hWnd) )return;	// ���ڲ�����Ч�ľ��,Ҳ��δ��ʼ��

    pRetData->m_bool = TRUE;	// �ߵ�������Ѿ���ʼ��
}

// ���ø�ʽ: _SDT_NULL (�������ڲ���).����, ����˵��: "���������µ����Ĵ���"
// �޲���
EXTERN_C void WKE_NAME(187, wke_DestroyWebView)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->DestroyWebWindow();
    pArgInf[0].m_ppCompoundData[0] = 0;
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).����cookie_CURL, ����˵��: "����node.dll�� wkeSetCookie, ���Բ������κ��޸�, ֧�ֿ�����cookie��ص������ԭ�����node.dll, �������κ��޸�"
// ����<1>: [url SDT_TEXT], ����˵��: "������cookie����վ����,���url��ַ������,�봫��utf8�����ı�."
// ����<2>: [cookie SDT_TEXT], ����˵��: "�����õ�cookie, cookie�������curl��cookieд��"
EXTERN_C void WKE_NAME(188, wke_SetCookieCURL)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->SetCookie(pArgInf[1].m_pText, pArgInf[2].m_pText);
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).ģ��Ӳ���豸����, ����˵��: "����mbģ���Ӳ���豸��������Ҫ����αװ�ֻ��豸����"
// ����<1>: �豸�ַ��� SDT_TEXT, ����˵��: "�豸���ַ�������ȡֵ�У�\r\n\t1. \"navigator.maxTouchPoints\"��ʱ \"��������\" ��Ҫ�����ã���ʾ touch �ĵ�����\r\n\t2. \"navigator.platform\"��ʱ \"�ı�����\" ��Ҫ�����ã���ʾjs���ȡ�� navigator.platform�ַ�����\r\n\t3. \"navigator.hardwareConcurrency\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� navigator.hardwareConcurrency ����ֵ��\r\n\t4. \"screen.width\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.width ����ֵ��\r\n\t5. \"screen.height\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.height ����ֵ��\r\n\t6. \"screen.availWidth\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.availWidth ����ֵ��\r\n\t7. \"screen.availHeight\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.availHeight ����ֵ��\r\n\t8. \"screen.pixelDepth\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.pixelDepth ����ֵ��\r\n\t9. \"screen.pixelDepth\"Ŀǰ�ȼ���\"screen.pixelDepth\"��\r\n\t10.\"window.devicePixelRatio\"ͬ��"
// ����<2>: [�ı����� SDT_TEXT], ����˵��: "�ı�����"
// ����<3>: [�������� SDT_INT], ����˵��: "��������"
// ����<4>: [������� SDT_FLOAT], ����˵��: "�������"
EXTERN_C void WKE_NAME(189, wke_SetDeviceParameter)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->SetDeviceParameter(pArgInf[1].m_pText, pArgInf[2].m_pText, pArgInf[3].m_int, pArgInf[4].m_float);
}

// ���ø�ʽ: SDT_BOOL (�������ڲ���).�ҽ��¼�, ����˵��: "�����¼����͹ҽӲ�ͬ���¼�, �¼�������ʹ�� ������¼�_ ��ͷ�ĳ���"
// ����<1>: �¼����� SDT_INT, ����˵��: "������¼�_ ��ͷ����, ��Ҫ���ӳ�������ͷ���ֵ��ο�����˵��"
// ����<2>: [�ص���ַ SDT_SUB_PTR], ����˵��: "��ϸ������鿴����, Ϊ����ȡ�����¼�"
// ����<3>: [���� SDT_INT], ����˵��: "����ص��Ĳ���"
EXTERN_C void WKE_NAME(190, wke_Event)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = FALSE;
    WKE_CTRL(0);

    void* arg = (void*)pArgInf[3].m_int;
    DWORD sub = pArgInf[2].m_dwSubCodeAdr;
    if ( sub == 0 || data->hWnd == 0 )
        return;

    int index = pArgInf[1].m_int - 1;
    switch ( pArgInf[1].m_int )
    {
    case 1:		// �ĵ�����
    case 2:		// ���ⱻ�ı�
    case 3:		// URL���ı�
    case 4:		// �����������µ�ַ
    case 5:		// �����������´���
    case 6:		// �ĵ��������
    case 7:		// ��̨��Ϣ���
    case 8:		// Alert��������
    case 9:		// Confirm��������
    case 10:	// Prompt��������
    case 11:	// ���������ļ�
    case 12:	// Url���뿪ʼ
    case 13:	// Url�������
    case 14:	// �����������
        wke->jyEvent.arg[index].fun = sub;
        wke->jyEvent.arg[index].arg = arg;
        break;
    case 15:	// �������
        wke->jyEvent.lDowm.fun = sub;
        wke->jyEvent.lDowm.arg = arg;
        break;
    case 16:		// ����ſ�
        wke->jyEvent.lUp.fun = sub;
        wke->jyEvent.lUp.arg = arg;
        break;
    case 17:		// ���˫��
        wke->jyEvent.lDblClk.fun = sub;
        wke->jyEvent.lDblClk.arg = arg;
        break;
    case 18:		// �Ҽ�����
        wke->jyEvent.rDowm.fun = sub;
        wke->jyEvent.rDowm.arg = arg;
        break;
    case 19:		// �Ҽ��ſ�
        wke->jyEvent.rUp.fun = sub;
        wke->jyEvent.rUp.arg = arg;
        break;
    case 20:		// ����ƶ�
        wke->jyEvent.move.fun = sub;
        wke->jyEvent.move.arg = arg;
        break;
    case 21:		// �����ȡ
        wke->jyEvent.getFocus.fun = sub;
        wke->jyEvent.getFocus.arg = arg;
        break;
    case 22:		// ������ʧ
        wke->jyEvent.killFocus.fun = sub;
        wke->jyEvent.killFocus.arg = arg;
        break;
    case 23:		// ĳ������
        wke->jyEvent.keyDowm.fun = sub;
        wke->jyEvent.keyDowm.arg = arg;
        break;
    case 24:		// ĳ���ſ�
        wke->jyEvent.keyUp.fun = sub;
        wke->jyEvent.keyUp.arg = arg;
        break;
    case 25:		// �����ַ�
        wke->jyEvent.charSet.fun = sub;
        wke->jyEvent.charSet.arg = arg;
        break;
    case 26:		// ���ֹ���
        wke->jyEvent.scroll.fun = sub;
        wke->jyEvent.scroll.arg = arg;
        break;
    case 27:		// �滭�¼�
        wke->jyEvent.paint.fun = sub;
        wke->jyEvent.paint.arg = arg;
    default:
        return;
    }
    pRetData->m_bool = TRUE;
}

typedef bool(__stdcall* pfn_callback_getAllCookie_arg8)( void* params,
                                                        const char* name,
                                                        const char* value,
                                                        const char* domain,
                                                        const char* path, // If |path| is non-empty only URLs at or below the path will get the cookie value.
                                                        int secure, // If |secure| is true the cookie will only be sent for HTTPS requests.
                                                        int httpOnly, // If |httponly| is true the cookie will only be sent for HTTP requests.
                                                        int* expires // The cookie expiration date is only valid if |has_expires| is true.
                                                        );

inline static bool fun_wkeCookieVisitor(
    void* params,
    const char* name,
    const char* value,
    const char* domain,
    const char* path, // If |path| is non-empty only URLs at or below the path will get the cookie value.
    int secure, // If |secure| is true the cookie will only be sent for HTTPS requests.
    int httpOnly, // If |httponly| is true the cookie will only be sent for HTTP requests.
    int* expires // The cookie expiration date is only valid if |has_expires| is true.
)
{
    WKECtrl* wke = (WKECtrl*)params;
    pfn_callback_getAllCookie_arg8 fun = (pfn_callback_getAllCookie_arg8)wke->jyEvent.getAllCookie.fun;
    return fun(wke->jyEvent.getAllCookie.arg, name, value, domain, path, secure, httpOnly, expires);
}
// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).��ȡ����Cookie, ����˵��: "ͨ��������visitor��������cookie"
// ����<1>: ������ SDT_SUB_PTR, ����˵��: "�߼��� �ص�����(������ ����, �ı��� cookie��, �ı��� cookieֵ, �ı��� ����, �ı��� ·��, ������ ������https����, ������ ������http����, �����ʹ�ַ �Ƿ�����cookie�����¼�); "
// ����<2>: [���� SDT_INT], ����˵��: "����������, �������1�ص���ַ�е�ֵ"
EXTERN_C void WKE_NAME(191, wke_GetAllCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->jyEvent.getAllCookie.arg = (void*)pArgInf[2].m_int;
    wke->jyEvent.getAllCookie.fun = (DWORD)pArgInf[1].m_dwSubCodeAdr;
    if ( !wke->jyEvent.getAllCookie.fun )
        return;
    wke->VisitAllCookie(wke, fun_wkeCookieVisitor);
}

// ���ø�ʽ: _SDT_NULL (����Web�����/�������ڲ���).���cookie, ����˵��: "���cookie"
// �޲���
EXTERN_C void WKE_NAME(198, wke_ClearCookie)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    wke->ClearCookie();
}

// ���ø�ʽ: SDT_INT (����Web�����/�������ڲ���).ȡ��ҳͼ��, ����˵��: "������ �ĵ�������� �¼������"
// �޲���
EXTERN_C void WKE_NAME(203, wke_NetGetFavicon)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// ���ø�ʽ: SDT_INT (�������ڲ���).����, ����˵��: "����һ�������, �����ɹ����ش��ھ��, ʧ�ܷ���0, ���ھ����webView�ǲ�һ����, ���ϸ񴫵ݲ���"
// ����<1>: [�����ھ�� SDT_INT], ����˵��: "������������ĸ����ھ��, �����ǰ����û����Ϣѭ��, ����Ҫ�Լ�������Ϣѭ��"
// ����<2>: [�� SDT_INT], ����˵��: "�����������ߵ�λ��, Ĭ��Ϊ0"
// ����<3>: [�� SDT_INT], ����˵��: "��������򶥱ߵ�λ��, Ĭ��Ϊ0"
// ����<4>: [�� SDT_INT], ����˵��: "���������Ŀ��, Ĭ��Ϊ0"
// ����<5>: [�� SDT_INT], ����˵��: "���������ĸ߶�, Ĭ��Ϊ0"
// ����<6>: [�������� SDT_BOOL], ����˵��: "�����ǰ���Ѿ������������, ���������ڴ���, ���򷵻ؼ�, Ĭ��Ϊ��, ���ٺ󴴽�"
EXTERN_C void WKE_NAME(216, wke_Create)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = FALSE;
    PWEBKIT_PROPERTYEX data = (PWEBKIT_PROPERTYEX)*pArgInf[0].m_ppCompoundData;
    init_webkit();
    if ( !data )
    {
        data = new WEBKIT_PROPERTYEX;
        data->clear();
        data->init();
        *pArgInf[0].m_ppCompoundData = data;
    }
    WKECtrl* wke = data->pCtl;

    HWND hParent = (HWND)pArgInf[1].m_int;
    //wkeWindowType type = (wkeWindowType)pArgInf[7].m_int;
    wkeWindowType type = WKE_WINDOW_TYPE_CONTROL;
    if ( !IsWindow(hParent) ) type = WKE_WINDOW_TYPE_POPUP;

    BOOL isDestroy = pArgInf[6].m_bool;

    if ( IsWindow(data->hWnd) )
    {
        if ( isDestroy == FALSE )
            return;	// �����Ѵ���, ���Ҳ����������ٺ�Ŵ���
        wke->DestroyWebView();
        data->hWnd = 0;
    }

    RECT rc = { 0 };
    rc.left = pArgInf[2].m_int;
    rc.top = pArgInf[3].m_int;
    rc.right = pArgInf[4].m_int;
    rc.bottom = pArgInf[5].m_int;

    const DWORD dwStyle = WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE;
    if ( !wke->create(hParent, dwStyle, 0, rc.left, rc.top, rc.right, rc.bottom, 0, type) )
    {
        if ( pArgInf[0].m_ppCompoundData[0] == 0 )
        {
            delete wke;
        }
        return;
    }
    wkeWebView webView = wke->GetWkeWebView();
    data->hWnd = wke->GetWindowHandle();

    __fill_wnd_data(data, webView);
    wke->WKECtrl_OnPaint();
    wke->SetWindowTitle(L"����Web�����");
    wke->ShowWindow(true);
    pRetData->m_int = (int)data->hWnd;
}

// ���ø�ʽ: SDT_BOOL (�������ڲ���).��Ϣѭ��, ����˵��: "��Ϣѭ��, ���û�д��������򷵻ؼ�, ����ֱ�������յ� WM_QUIT ��Ϣʱ�˷����ŷ�����"
// ����<1>: [���������˳���Ϣѭ�� SDT_BOOL], ����˵��: "���Ϊ��, ��ô����յ� WM_DESTROY ��Ϣʱ����� PostQuitMessage() �˳���Ϣѭ��, ������Լ����໯, �����յ� WM_DESTROY ��Ϣʱ��Ҫ���� CallWindowProcW() ����Ϣת��ԭ����, �����Լ����� PostQuitMessage(), ����ú������᷵��"
EXTERN_C void WKE_NAME(217, wke_MessageLoop)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    HWND hWnd = 0;
    WKE_CTRL(&hWnd);
    pRetData->m_bool = FALSE;
    if ( !IsWindow(hWnd) )
        return;
    wke->isDlg = pArgInf[1].m_bool;
    wkeRunMessageLoop();
    pRetData->m_bool = TRUE;
}

// ���ø�ʽ: SDT_INT (����Web�����/�������ڲ���).ȡwke���ھ��, ����˵��: "ȡ��ǰwke�Ĵ��ھ��"
// �޲���
EXTERN_C void WKE_NAME(220, wke_GetWindow)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_CTRL(0);
    pRetData->m_int = (int)wke->GetWindowHandle();
}

