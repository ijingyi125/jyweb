#include "wke_typedef.h"
#include "WKECtrl.h"
#include "Cajax.h"

// ajax�������ʵ���ļ�


// ���ø�ʽ: _SDT_NULL (Ajax).Ajax��ʼ��, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(21, AJAXIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	*pArgInf->m_ppCompoundData = new Cajax;
}

// ���ø�ʽ: _SDT_NULL (Ajax).Ajax��ֵ, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(22, AJAXCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
}

// ���ø�ʽ: _SDT_NULL (Ajax).AJAX����, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(23, AJAXDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	Cajax* ajax = (Cajax*)* pArgInf->m_ppCompoundData;
	if (ajax)delete ajax;
	*pArgInf->m_ppCompoundData = NULL;
}

// ���ø�ʽ: _SDT_NULL (Ajax).����Http����ͷ, ����˵��: "����Http����ͷ,�ڵ���Get��Post����������ͷ������ա�"
// ����<1>: Key SDT_TEXT, ����˵��: "http����ͷ�ֶ�����,�� Content-Type UserAgent Referer �ȵ�"
// ����<2>: Value SDT_TEXT, ����˵��: "http����ͷ�ֶζ�Ӧ��ֵ"
EXTERN_C void WKE_NAME(24, SetHttpHeader)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    Cajax* ajax = (Cajax*)*pArgInf->m_ppCompoundData;
	if (ajax)
		ajax->SetHttpHeader(pArgInf[1].m_pText, pArgInf[2].m_pText);
}

// ���ø�ʽ: _SDT_NULL (Ajax).GET����, ����˵��: "����ҳ��ע��ajax�ű�����ʵ��Get����"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: url SDT_TEXT, ����˵��: "�����URL"
// ����<3>: �ص����� SDT_SUB_PTR, ����˵��: "��Ajax�������������ɽ����ô˷���,�ɹ����ط����������ı�,���󷵻�״̬��"
EXTERN_C void WKE_NAME(25, AjaxGet)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    Cajax* ajax = (Cajax*)*pArgInf->m_ppCompoundData;
	if (ajax)
		ajax->Get((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText, (ajax_userFunc)pArgInf[3].m_dwSubCodeAdr);
}

// ���ø�ʽ: _SDT_NULL (Ajax).POST����, ����˵��: "����ҳ��ע��ajax�ű�����ʵ��Post����"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: url SDT_TEXT, ����˵��: "�����URL"
// ����<3>: �Ƿ���JSON SDT_BOOL, ����˵��: "�ύ�����ݸ�ʽ�Ƿ���JSON"
// ����<4>: �ύ���� SDT_TEXT, ����˵��: "Ҫ�ύ��POST����"
// ����<5>: �ص����� SDT_SUB_PTR, ����˵��: "��Ajax�������������ɽ����ô˷���,�ɹ����ط����������ı�,���󷵻�״̬��"
EXTERN_C void WKE_NAME(26, AjaxPost)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    Cajax* ajax = (Cajax*)*pArgInf->m_ppCompoundData;
	if (ajax)
		ajax->Post((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText, pArgInf[3].m_bool, pArgInf[4].m_pText, (ajax_userFunc)pArgInf[5].m_dwSubCodeAdr);
}




