#include "wke_typedef.h"
#include "WKECtrl.h"


// ���ø�ʽ: _SDT_NULL (���⹦��).���⹦�ܳ�ʼ��, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(117, NETIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// ���ø�ʽ: _SDT_NULL (���⹦��).���⹦�ܸ�ֵ, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(118, NETCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// ���ø�ʽ: _SDT_NULL (���⹦��).���⹦������, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(119, NETDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// ���ø�ʽ: _SDT_NULL (���⹦��).NPAPI��������ر�, ����˵��: "��������ں�֧��NPAPI���������NPAPI���������ʵ������FLASH���ŵĹ��ܡ��濪�����ٹر�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: �Ƿ��� SDT_BOOL, ����˵��: "�� ������ , �ٹر�  Ĭ�Ͽ���"
EXTERN_C void WKE_NAME(120, wke_NPAPIEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetNpapiPluginsEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����ģʽ�����ر�, ����˵��: "������ر���ҳ��Ⱦ,�����ҳ�����ٶ� ���������档ע�⣺����رպ���ҳ���ٽ�����Ⱦ����������Ȼ���ڡ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: �Ƿ��� SDT_BOOL, ����˵��: "�� ������ , �ٹر�  Ĭ�Ͽ���"
EXTERN_C void WKE_NAME(121, wke_SpiderEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetHeadlessEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).Cookie�����ر�, ����˵��: "Cookie�����ͽ��ã�����رգ�����������ٴ���Cookie��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: �Ƿ��� SDT_BOOL, ����˵��: "�� ������ , �ٹر�  Ĭ�Ͽ���"
EXTERN_C void WKE_NAME(122, wke_SetCookieEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetCookieEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// ���ø�ʽ: SDT_BOOL (���⹦��).Cookie�Ƿ����, ����˵��: "Cookie�Ƿ��Ѿ�������"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(123, wke_CookieIsEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    BOOL nRet = wkeIsCookieEnabled((wkeWebView)pArgInf[1].m_int);
    pRetData->m_dtDataType = SDT_BOOL;
    pRetData->m_bool = nRet;
}

// ���ø�ʽ: _SDT_NULL (���⹦��).�����鿪���ر�, ����˵��: "�������Ƿ��� �������Ϊ�棬�����������������������Ȩִ�У��������Ϊ�٣���������������Ĭ��ֵΪ�١�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: �Ƿ��� SDT_BOOL, ����˵��: "�� ������ , �ٹر�  Ĭ�Ͽ���"
EXTERN_C void WKE_NAME(124, wke_CspCheckEnable)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetCspCheckEnable((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_bool);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).������������, ����˵��: "���� Url���뿪ʼ �¼��е���,Hookָ����Դ��������ô˷�����Url��������¼��Żᱻ����"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(125, HookRequest)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetHookRequest((wkeNetJob)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).�޸�HTTPͷ�ֶ���Ϣ, ����˵��: "���� Url���뿪ʼ �¼��е��ã���ʾ����http���󣨻���file:///Э�飩�� HTTPͷ�ֶ���Ϣ��"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
// ����<2>: HTTPͷ���� SDT_TEXT, ����˵��: "Httpͷ�ֶ����� �� Accept , Content-Type ��..."
// ����<3>: HTTPͷֵ SDT_TEXT, ����˵��: "Httpͷ�ֶζ�Ӧֵ, ��: text/javascript , appliction/json ��..."
EXTERN_C void WKE_NAME(126, wke_NetSetHTTPHeaderField)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //wkeSetCspCheckEnable((wkeWebView)pArgInf[1].m_int,pArgInf[2].m_bool);
    //��wkeOnLoadUrlBegin�ص�����ã���ʾ����http���󣨻���file:///Э�飩�� http header field��responseһֱҪ�����ó�false

    wstr key = wstr::A2W(pArgInf[2].m_pText);
    wstr value = wstr::A2W(pArgInf[3].m_pText);
    wkeNetSetHTTPHeaderField((wkeNetJob)pArgInf[1].m_int, key.c_str(), value.c_str(), FALSE);

}

// ���ø�ʽ: _SDT_NULL (���⹦��).�޸�����MIME����, ����˵��: "������ URL���뿪ʼ �¼��е��� ��ʾ����http�����MIME type��"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
// ����<2>: MIME���� SDT_TEXT, ����˵��: "MIMEType..."
EXTERN_C void WKE_NAME(127, wke_NetSetMIMEType)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetSetMIMEType((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText);
}


// ���ø�ʽ: _SDT_NULL (���⹦��).�޸�����URL, ����˵��: "������ URL���뿪ʼ �¼��е��� �����޸�һ�����������url��"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
// ����<2>: Url SDT_TEXT, ����˵��: "URL..."
EXTERN_C void WKE_NAME(128, wke_NetChangeRequestUrl)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetChangeRequestUrl((wkeNetJob)pArgInf[1].m_int, pArgInf[2].m_pText);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).�޸���������, ����˵��: "�� Url���뿪ʼ �¼�����ã���ʾ�������غ󻺴�����ݡ�"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
// ����<2>: ���� SDT_BIN, ����˵��: "����"
// ����<3>: [���ݳ��� SDT_INT], ����˵��: "���ݳ���"
EXTERN_C void WKE_NAME(129, wke_SetRequestData)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    int dwLen = 0;
    LPBYTE pData = GetAryElementInf(pArgInf[2].m_pBin, &dwLen);
    if (pArgInf[3].m_dtDataType != _SDT_NULL)
    {
        dwLen = pArgInf[3].m_int;
    }

    wkeNetSetData((wkeNetJob)pArgInf[1].m_int, (void*)(pData), dwLen);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).��������ģʽ, ����˵��: "�����������Ϣ���Զ�ת���ɴ�����Ϣ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: �Ƿ��� SDT_BOOL, ����˵��: "�� ������ , �ٹر�  Ĭ�Ͽ���"
EXTERN_C void WKE_NAME(130, wke_SetTouchEnabled)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetTouchEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).���������Ϣ, ����˵��: "�����ر������Ϣ�������ڿ��������󣬹ر������Ϣ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: �Ƿ��� SDT_BOOL, ����˵��: "�� ������ , �ٹر�  Ĭ�Ͽ���"
EXTERN_C void WKE_NAME(131, wke_SetMouseEnabled)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetMouseEnabled((wkeWebView)pArgInf[1].m_int, (bool)pArgInf[2].m_bool);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����DevTool, ����˵��: "����һЩ�����͹��ܡ� ���翪�������߹��ߡ�"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: debugString SDT_TEXT, ����˵��: "showDevTools "
// ����<3>: configParam SDT_TEXT, ����˵��: ", ע��param��ʱ������utf8����"
EXTERN_C void WKE_NAME(132, wke_ShowDevTool)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //wkeSetDebugConfig((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText, pArgInf[3].m_pText);

    //wkeSetDebugConfig((wkeWebView)(pArgInf[1].m_int), "showDevTools", _A2U_wke("F:\\Documents\\Desktop\\wke֧�ֿ����\\front_end\\inspector.html"));

    wkeSetDebugConfig((wkeWebView)(pArgInf[1].m_int), pArgInf[2].m_pText, pArgInf[3].m_pText);
}


// ���ø�ʽ: SDT_INT (���⹦��).ȡ�����ID, ����˵��: "ȡ�����ID��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(133, wke_GetMainFrameId)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeWebFrameHandle ID = wkeWebFrameGetMainFrame((wkeWebView)pArgInf[1].m_int);
    pRetData->m_int = (int)ID;
}

// ���ø�ʽ: SDT_BOOL (���⹦��).�Ƿ�Ϊ�����, ����˵��: "�Ƿ�Ϊ����ܡ�"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: frameid SDT_INT, ����˵��: "���ID"
EXTERN_C void WKE_NAME(134, wke_IsMainFrame)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    BOOL bRet = wkeIsMainFrame((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
    pRetData->m_bool = bRet;
}

// ���ø�ʽ: SDT_TEXT (���⹦��).ȡ���URL, ����˵��: "�����IDȡ���URL��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: frameid SDT_INT, ����˵��: "���ID"
EXTERN_C void WKE_NAME(135, wke_GetFrameUrl)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    LPCSTR str = wkeGetFrameUrl((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
    pRetData->m_pText = CloneTextData((char*)str);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����ƶ�, ����˵��: "���������Ϣ,ģ���ƶ���ָ��λ�á�"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: x SDT_INT, ����˵��: "������"
// ����<3>: y SDT_INT, ����˵��: "������"
EXTERN_C void WKE_NAME(136, wke_MBMouseMove)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_MOUSEMOVE, x, y, WKE_CONTROL);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����������, ����˵��: "����������������Ϣ��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: x SDT_INT, ����˵��: "������"
// ����<3>: y SDT_INT, ����˵��: "������"
EXTERN_C void WKE_NAME(137, wke_MouseLButtonDown)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_LBUTTONDOWN, x, y, WKE_LBUTTON);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).������̧��, ����˵��: "����������̧����Ϣ��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: x SDT_INT, ����˵��: "������"
// ����<3>: y SDT_INT, ����˵��: "������"
EXTERN_C void WKE_NAME(138, wke_MouseLButtonUP)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_LBUTTONUP, x, y, WKE_LBUTTON);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����м�����, ����˵��: "��������м�������Ϣ��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: x SDT_INT, ����˵��: "������"
// ����<3>: y SDT_INT, ����˵��: "������"
EXTERN_C void WKE_NAME(139, wke_MouseMButtonDown)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_MBUTTONDOWN, x, y, WKE_MBUTTON);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����м�̧��, ����˵��: "��������м�̧����Ϣ��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: x SDT_INT, ����˵��: "������"
// ����<3>: y SDT_INT, ����˵��: "������"
EXTERN_C void WKE_NAME(140, wke_MouseMButtonUP)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_MBUTTONUP, x, y, WKE_MBUTTON);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����Ҽ�����, ����˵��: "��������Ҽ�������Ϣ��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: x SDT_INT, ����˵��: "������"
// ����<3>: y SDT_INT, ����˵��: "������"
EXTERN_C void WKE_NAME(141, wke_MouseRButtonDown)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_RBUTTONDOWN, x, y, WKE_RBUTTON);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����Ҽ�̧��, ����˵��: "��������Ҽ�̧����Ϣ��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: x SDT_INT, ����˵��: "������"
// ����<3>: y SDT_INT, ����˵��: "������"
EXTERN_C void WKE_NAME(142, wke_MouseRButtonUP)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    int x = pArgInf[2].m_int, y = pArgInf[3].m_int;
    wkeFireMouseEvent((wkeWebView)pArgInf[1].m_int, WM_RBUTTONUP, x, y, WKE_RBUTTON);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����_����, ����˵��: "���Ͱ�����Ϣ��MB��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ������ SDT_INT, ����˵��: "��������ʹ�� �� #�˸��...."
EXTERN_C void WKE_NAME(143, wke_KeyDownEvent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    //++HACK WKM_RREND = 1025 ????
    wkeFireKeyDownEvent((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, 1025, 0);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����_̧��, ����˵��: "���Ͱ�����Ϣ��MB��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ������ SDT_INT, ����˵��: "��������ʹ�� �� #K�� #A��...."
EXTERN_C void WKE_NAME(144, wke_KeyUpEvent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetFocus((wkeWebView)pArgInf[1].m_int);
    //++HACK WKM_RREND = 1025 ????
    wkeFireKeyUpEvent((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, 1025, 0);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).����_�ַ�, ����˵��: "����WM_CHAR��Ϣ��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ������ SDT_INT, ����˵��: "��������ʹ�� �� #K�� #A��...."
EXTERN_C void WKE_NAME(145, wke_KeyPressEvent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeFireKeyPressEvent((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, WKE_REPEAT, 0);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).ȡ������������, ����˵��: "������ URL���뿪ʼ�¼��� ȡ��ָ������������"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(146, wke_CancelByReuqest)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetCancelRequest((wkeNetJob)pArgInf[1].m_int);
}











//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


// ���ø�ʽ: SDT_TEXT (���⹦��).[]��ȡ����ͷ����, ����˵��: "��ȡ���͵�����ͷ�����ݡ�"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(167, wke_NetGetRawHttpHead)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    const wkeSlist* list = wkeNetGetRawHttpHead((wkeNetJob)pArgInf[1].m_int);
    const wkeSlist* plist = list;
    if ( !list )
    {
        LPINT p = (LPINT)ealloc(sizeof(INT) * 2);
        p[0] = 1;  // ����ά����
        p[1] = 0;
        pRetData->m_pAryData = p;  // �����������顣
        return;
    }

    int len = 0;
    while ( list != NULL )
    {
        len++;
        list = list->next;
    }
    list = plist;
    LPINT p = (LPINT)ealloc(sizeof(INT) * ( 2 + len ));
    p[0] = 1;  // ����ά����
    p[1] = len;

    int i = 2;
    while ( list != NULL )
    {
        p[i] = (int)CloneTextData(list->data);
        i++;
        list = list->next;
    }
    pRetData->m_pAryData = p;  // �����������顣
}

// ���ø�ʽ: SDT_INT (���⹦��).ȡ����ģʽ, ����˵��: "���ص�ǰ������ģʽ, ��ʹ�� #����ģʽ_ ��ͷ�ĳ���\r\n�޷��޸�post����,ֻ��ȡ"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(172, wke_NetGetRequestMethod)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_int = wkeNetGetRequestMethod((wkeNetJob)pArgInf[1].m_int);
}


typedef struct __POSTELEMENT
{
    int cbSize;
    int type;
    LPBYTE data;
    LPCSTR filePath;
    __int64 startPos;
    __int64 length;
}POSTELEMENT, * LPPOSTELEMENT;

typedef struct __POSTELEMENTS
{
    int cbSize;
    int* pElement;
    int count;
    int isChange;
    wkePostBodyElements* oldData;
}POSTELEMENTS, *LPPOSTELEMENTS;


// ���ø�ʽ: MAKELONG(0x09, 0) (���⹦��).ȡpost����, ����˵��: "��ȡpost����"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(173, wke_NetGetPostBody)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    /*DTP_POSTELEMENTS =
    {
        �ṹ��С
        Ԫ����[]
            {
                �ṹ��С
                ����
                ����
                �ļ�·��
                �ļ���ʼλ��
                �ļ�����
            }
        Ԫ������
        �Ƿ�ı�
        ԭʼ����
    }
    */
    wkePostBodyElements* data = wkeNetGetPostBody((wkeNetJob)pArgInf[1].m_int);
    if (!data)
    {
        LPPOSTELEMENTS pMem = (LPPOSTELEMENTS)ealloc(sizeof(POSTELEMENTS));
        int* pArrElement = (int*)ealloc(2 * sizeof(int));
        pArrElement[0] = 1;
        pArrElement[1] = 0;

        pMem->cbSize = sizeof(POSTELEMENTS);
        pMem->count = 0;
        pMem->isChange = 0;
        pMem->oldData = 0;
        pMem->pElement = pArrElement;
        pRetData->m_pCompoundData = pMem;
        return;
    }
    //return;

    wkeMemBuf* pData = 0;
    LPPOSTELEMENTS pMem = (LPPOSTELEMENTS)ealloc(sizeof(POSTELEMENTS));

    int* pArrElement = (int*)ealloc((data->elementSize + 2) * sizeof(int));
    int index = 0;
    pArrElement[index++] = 1;
    pArrElement[index++] = data->elementSize;
    
    if (pMem)
    {
        pMem->cbSize = sizeof(POSTELEMENTS);
        pMem->count = data->elementSize;
        pMem->isChange = data->isDirty;
        pMem->oldData = data;
        pMem->pElement = pArrElement;
        for (size_t i = 0; i < data->elementSize; i++)
        {
            LPPOSTELEMENT pElement = (LPPOSTELEMENT)ealloc(sizeof(POSTELEMENT));
            pArrElement[index++] = (int)pElement;

            pElement->cbSize = (data->element[i])->size;
            pElement->type = (data->element[i])->type;
            pData = (data->element[i])->data;
            if (pData)pElement->data = CloneBinData((LPBYTE)pData->data, pData->length);
            pElement->filePath = CloneTextData(wkeGetString((data->element[i])->filePath));
            pElement->startPos = (data->element[i])->fileStart;
            pElement->length = (data->element[i])->fileLength;
        }
    }
    
    pRetData->m_dtDataType = SDT_TYPE_POSTELEMENTS;
    pRetData->m_pCompoundData = pMem;
}

// ���ø�ʽ: SDT_BOOL (���⹦��).����post����, ����˵��: "��������post����"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(174, wke_NetCreatePostBodyElement)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //1.���ĸ��ӿ�Ҫ�������ʹ�á� ��wkeOnLoadUrlBegin���ж���postʱ������ͨ��wkeNetCreatePostBodyElements������һ���µ�post���ݰ��� 
    //Ȼ��wkeNetFreePostBodyElements���ͷ�ԭpost���ݡ�

    /*DTP_POSTELEMENTS = 
    {
        �ṹ��С
        Ԫ����[]
            {
                �ṹ��С
                ����
                ����
                �ļ�·��
                �ļ���ʼλ��
                �ļ�����
            }
        Ԫ������
        �Ƿ�ı�
        ԭʼ����
    }
    */
    wkeWebView webView = (wkeWebView)pArgInf[1].m_int;
    pRetData->m_bool = FALSE;
    wkePostBodyElements* data = 0;
    wkePostBodyElements* dataOld = 0;
    int* pMem = 0;
    int* pAry = 0;
    int dwLen = 0;
    if (!pArgInf[2].m_pCompoundData)return;
    pMem = (int*)pArgInf[2].m_pCompoundData;
    dataOld = (wkePostBodyElements*)pMem[4];
    
    pAry = (int*)(pMem[1]);
    int size = pAry[1];
    pAry = pAry + 2;

    if (size == 0)return;
    data = wkeNetCreatePostBodyElements(webView, size);
    if (data == 0)return;
    
    // pAry = �û����ݹ�����post������,������ָ���һ����Ա,ÿ����Ա����һ����������

    //pData  0 = �ṹ��С 1 = ����  2 = �ֽڼ����� 3 = �ļ�·��  4 = �ļ���ʼλ��  6 = �ļ�����
    int* pData = 0;
    INT64* i64 = 0;
    for (int i = 0; i < size; i++)
    {
        data->element[i] = wkeNetCreatePostBodyElement(webView);
        wkeMemBuf* buf = new wkeMemBuf;
        memset(buf, 0, sizeof(wkeMemBuf));
        if (data->element[i])
        {
            pData = (int*)pAry[i];
            data->element[i]->size = sizeof(wkePostBodyElement);
            data->element[i]->type = (wkeHttBodyElementType)pData[1];
            data->element[i]->data = buf;
                buf->data = GetAryElementInf((LPBYTE)pData[2], &dwLen);
                //buf->data = (void*)(pData[2] + 8);
                buf->length = dwLen;
                buf->unuse = sizeof(wkeMemBuf);
            data->element[i]->filePath = wkeString(pData[3]);
            i64 = (INT64*)(pData + 4);
            data->element[i]->fileStart = *i64;
            i64 = (INT64*)(pData + 6);
            data->element[i]->fileLength = *i64;
        }
    }
    if (dataOld)wkeNetFreePostBodyElements(dataOld);
    pMem[4] = (int)data;
}

// ���ø�ʽ: _SDT_NULL (���⹦��).�ͷ�post����, ����˵��: "������ı����� ����post����()�� ���ص�ֵ"
// ����<1>: post���� SDT_INT, ����˵��: "����post���ݷ��ص�ֵ"
EXTERN_C void WKE_NAME(175, wke_NetFreePostBodyElement)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //wkePostBodyElements
    //2.���ĸ��ӿ�Ҫ�������ʹ�á� ��wkeOnLoadUrlBegin���ж���postʱ������ͨ��wkeNetCreatePostBodyElements������һ���µ�post���ݰ��� 
    //Ȼ��wkeNetFreePostBodyElements���ͷ�ԭpost���ݡ�

    if (!pArgInf[2].m_pCompoundData)return;
    int* pMem = (int*)pArgInf[1].m_pCompoundData;
    wkePostBodyElements* data = (wkePostBodyElements*)pMem[4];
    if (!data) return;
    
    int* pAry = (int*)(pMem[1]);
    int size = pAry[1];
    pAry = pAry + 2;

    if (size == 0)
    {
        if (data)wkeNetFreePostBodyElements(data);
        return;
    }
    

    for (int i = 0; i < size; i++)
    {
        if (data->element[i] && data->element[i]->data)
        {
            delete data->element[i]->data;
        }
    }
    if (data)wkeNetFreePostBodyElements(data);
}

// ���ø�ʽ: SDT_BOOL (���⹦��).����post������, ����˵��: "����һ���µ�post������,�ǵò���ʱ�Լ����� ���⹦��.�ͷ�post������() ���ͷ�"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: Ԫ���� MAKELONG(0x09, 0), ����˵��: "Ԫ����"
EXTERN_C void WKE_NAME(176, wke_NetCreatePostBodyElements)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //3.���ĸ��ӿ�Ҫ�������ʹ�á� ��wkeOnLoadUrlBegin���ж���postʱ������ͨ��wkeNetCreatePostBodyElements������һ���µ�post���ݰ��� 
    //Ȼ��wkeNetFreePostBodyElement���ͷ�ԭpost���ݡ�
    //UNDONE ����ӹ���,���⹦��->����post����
    wkePostBodyElement* data = wkeNetCreatePostBodyElement((wkeWebView)pArgInf[1].m_int);

}

// ���ø�ʽ: _SDT_NULL (���⹦��).�ͷ�post������, ����˵��: "������ı����� ����post������()�� ���ص�ֵ\r\n��[Url���뿪ʼ]�¼����ж���postʱ������ͨ�� ���⹦��.����post������() ������һ���µ�post���ݰ���Ȼ����� ���⹦��.�ͷ�post������() ���ͷ�ԭpost���ݡ�"
// ����<1>: Ԫ���� MAKELONG(0x09, 0), ����˵��: "Ԫ����"
EXTERN_C void WKE_NAME(177, wke_NetFreePostBodyElements)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //4.���ĸ��ӿ�Ҫ�������ʹ�á� ��wkeOnLoadUrlBegin���ж���postʱ������ͨ��wkeNetCreatePostBodyElements������һ���µ�post���ݰ��� 
    //Ȼ��wkeNetFreePostBodyElement���ͷ�ԭpost���ݡ�
    //UNDONE ����ӹ���,���⹦��->�ͷ�post����
    //wkePostBodyElements
    wkeNetFreePostBodyElement((wkePostBodyElement*)pArgInf[1].m_int);

}

// ���ø�ʽ: SDT_BOOL (���⹦��).�첽����, ����˵��: "�߼��÷�����[Url���뿪ʼ]�ص�����á� ��ʱ��[Url���뿪ʼ]�¼������ص�һ������󣬲��������жϳ��������ʱ���Ե��ñ��ӿڣ�Ȼ���� �첽��ĳ��ʱ�̣����� ���⹦��.��������() ���ô������������\r\n���������ɹ����ٴ������ʧ�ܣ������ٵ��� ���⹦��.��������() ��"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(178, wke_NetHoldJobToAsynCommit)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    // ���������жϳ��������ʱ���Ե��ñ��ӿڣ�Ȼ���� �첽��ĳ��ʱ�̣����� ���⹦��.��������() ���ô������������
    pRetData->m_bool = wkeNetHoldJobToAsynCommit((wkeNetJob)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).��������, ����˵��: "�߼��÷������ ���⹦��.�첽����() ʹ��"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(179, wke_NetContinueJob)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeNetContinueJob((wkeNetJob)pArgInf[1].m_int);
}


// ���ø�ʽ: SDT_TEXT (���⹦��).[]��ȡ��Ӧͷ, ����˵��: "��ȡԭʼ��Ӧͷ, �� Url������� �¼���ʹ��"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(196, wke_NetGetRawResponseHead)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    const wkeSlist* list = wkeNetGetRawResponseHead((wkeNetJob)pArgInf[1].m_int);
    const wkeSlist* plist = list;
    if ( !list )
    {
        LPINT p = (LPINT)ealloc(sizeof(INT) * 2);
        p[0] = 1;  // ����ά����
        p[1] = 0;
        pRetData->m_pAryData = p;  // �����������顣
        return;
    }

    int len = 0;
    while ( list != NULL )
    {
        len++;
        list = list->next;
    }
    list = plist;
    LPINT p = (LPINT)wke_jy_ealloc_wke(sizeof(INT) * ( 2 + len ));

    p[0] = 1;  // ����ά����
    p[1] = len;

    int i = 2;
    while ( list != NULL )
    {
        p[i] = (int)CloneTextData(list->data);
        i++;
        list = list->next;
    }
    pRetData->m_pAryData = p;  // �����������顣
}

// ���ø�ʽ: _SDT_NULL (���⹦��).post, ����˵��: "post"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: url SDT_TEXT, ����˵��: "post��url"
// ����<3>: post���� SDT_BIN, ����˵��: "post������"
EXTERN_C void WKE_NAME(197, wke_PostURL)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeWebView webView = (wkeWebView)pArgInf[1].m_int;
    if ( !webView )return;
    int len = 0;
    LPBYTE pArr = GetAryElementInf(pArgInf[3].m_pBin, &len);
    if ( !pArr || len == 0 )return;
    wstr url = _str::U2W(pArgInf[2].m_pText);
    wkePostURLW(webView, url.c_str(), (const char*)pArr, len);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).��ȡ����MIME����, ����˵��: "�� URL���뿪ʼ �¼������, ��ʾ����http�����MIME type"
// ����<1>: Job SDT_INT, ����˵��: "Url���뿪ʼ �д���Ĳ���"
EXTERN_C void WKE_NAME(200, wke_NetGetMIMEType)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    //wkeNetGetMIMEType()
}

// ���ø�ʽ: SDT_TEXT (���⹦��).��ȡHTTPͷ�ֶ���Ϣ, ����˵��: "�� URL���뿪ʼ �¼������, ��ʾ����http���󣨻���file:///Э�飩�� http header field"
// ����<1>: Job SDT_INT, ����˵��: "�¼���Ĳ���"
// ����<2>: key SDT_TEXT, ����˵��: "Ҫ��ȡ�ĸ�ͷ"
EXTERN_C void WKE_NAME(201, wke_NetGetHTTPHeaderField)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    const char* s = wkeNetGetHTTPHeaderField((wkeNetJob)pArgInf[1].m_int, pArgInf[2].m_pText);
    pRetData->m_pText = CloneTextData(s);
}

// ���ø�ʽ: SDT_TEXT (���⹦��).��ȡ��ӦHTTPͷ�ֶ���Ϣ, ����˵��: "�� URL������� �¼������"
// ����<1>: Job SDT_INT, ����˵��: "�¼���Ĳ���"
// ����<2>: key SDT_TEXT, ����˵��: "Ҫ��ȡ�ĸ�ͷ"
EXTERN_C void WKE_NAME(202, wke_NetGetHTTPHeaderFieldFromResponse)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    const char* s = wkeNetGetHTTPHeaderFieldFromResponse((wkeNetJob)pArgInf[1].m_int, pArgInf[2].m_pText);
    pRetData->m_pText = CloneTextData(s);
}

// ���ø�ʽ: _SDT_NULL (���⹦��).�õ�����Ϣ, ����˵��: "�õ�����Ϣ"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: debugString SDT_TEXT, ����˵��: "showDevTools "
// ����<3>: configParam SDT_TEXT, ����˵��: ", ע��param��ʱ������utf8����"
EXTERN_C void WKE_NAME(221, wke_SetDebugConfig)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeSetDebugConfig((wkeWebView)( pArgInf[1].m_int ), pArgInf[2].m_pText, pArgInf[3].m_pText);
}

