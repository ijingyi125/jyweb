#include "wke_typedef.h"
#include "WKECtrl.h"
#include "CwkeTBInfo.h"

// ����������ʵ���ļ�


CwkeTBInfo* GetTBjsFromArginf_wke(PMDATA_INF pArgInf)
{
	return (CwkeTBInfo*)* pArgInf[0].m_ppCompoundData;
}
#define WKE_TB CwkeTBInfo* js=0; if(!pArgInf[0].m_ppCompoundData) return; js = (CwkeTBInfo*) (*pArgInf[0].m_ppCompoundData); if(!js) return


// ���ø�ʽ: _SDT_NULL (WKE_���).����ʼ��, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(61, TBIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	//*pArgInf[0].m_ppCompoundData = (void*)100;
	*pArgInf[0].m_ppCompoundData = new CwkeTBInfo;
	return;
	//int a = (int)*pArgInf[0].m_ppCompoundData;
	//CwkeTBInfo* js = new CwkeTBInfo;
	//g_wke.insert(a, (void*)js);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).���ֵ, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(62, TBCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	//����������A=B,pArgInf[0]��A
	//CwkeTBInfo* pA= (CwkeTBInfo*)*pArgInf[0].m_ppCompoundData;  
	//CwkeTBInfo* pB= (CwkeTBInfo*)*pArgInf[1].m_ppCompoundData;  
	////���Բ���ֱ�Ӱ�Bָ�븳ֵ��A
	//_str s = pB->m_frameStr;
	//_str s2 = pB->m_frameStr;
	//pA->m_frameStr.resize(0);
	////pA->m_frameStr.assign(s);
	//pA->m_framex = pB->m_framex;
	//pA->m_framey = pB->m_framey;

}

// ���ø�ʽ: _SDT_NULL (WKE_���).�������, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(63, TBDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	WKE_TB;
	if (js)delete js;
	*pArgInf[0].m_ppCompoundData = NULL;

}

// ���ø�ʽ: _SDT_NULL (WKE_���).Ԫ�ص��, ����˵��: "Ԫ�ص����"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(64, wke_ElementClick)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_Click((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);

}

// ���ø�ʽ: _SDT_NULL (WKE_���).Ԫ���ý���, ����˵��: "Ԫ���ý��㡣"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(65, wke_SetElementFouce)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_SetFouce((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// ���ø�ʽ: SDT_TEXT (WKE_���).ȡԪ������ֵ, ����˵��: "ȡָ��Ԫ�����Ե��á�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: �������� SDT_TEXT, ����˵��: "��Ҫ��ȡ����ֵ������ ��: name"
EXTERN_C void WKE_NAME(66, wke_GetAttribute)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->elem_GetAttribute((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: _SDT_NULL (WKE_���).��Ԫ������ֵ, ����˵��: "����ָ��Ԫ�ص�ֵ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: �������� SDT_TEXT, ����˵��: "��Ҫ��ȡ����ֵ������ ��: name"
// ����<6>: ����ֵ SDT_TEXT, ����˵��: "��Ҫ��ȡ����ֵ������ ��: name"
EXTERN_C void WKE_NAME(67, wke_SetAttribute)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_SetAttribute((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText, pArgInf[6].m_pText);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).��_�������, ����˵��: "���ÿ���Ժ�,���е� ��_ �������������������ڲ�����,����С��1,��ʾ�����ǰѡ����"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(68, Form_SetFrame)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_SetFrame((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// ���ø�ʽ: SDT_INT (WKE_���).��_ȡ��ǰ�������, ����˵��: "��ȡ��ǰ��ҳ�п��(iframe)��������"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(69, Form_GetFrameCount)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->form_GetFrameCount((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).��_Input���, ����˵��: "ȡָ��Ԫ�����Ե�ֵ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(70, wke_Input_Click)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_Click((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// ���ø�ʽ: SDT_TEXT (WKE_���).��_Input������, ����˵��: "��ȡ����ָ��inputԪ�ص�����ֵ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: �������� SDT_TEXT, ����˵��: "��Ҫ��ȡ����ֵ������ ��: name"
EXTERN_C void WKE_NAME(71, wke_Input_ReadAttrValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->form_Input_ReadAttrValue((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: _SDT_NULL (WKE_���).��_Inputд����, ����˵��: "��ָ��INPUTԪ��д������ֵ,������Դ�������¸����Ե�ֵ,������������һ�����ԡ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: �������� SDT_TEXT, ����˵��: "��Ҫ��ȡ����ֵ������ ��: name"
// ����<6>: ����ֵ SDT_TEXT, ����˵��: "��Ҫ��ȡ����ֵ������ ��: name"
EXTERN_C void WKE_NAME(72, wke_Input_WriteAttrVal)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_WriteAttrVal((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText, pArgInf[6].m_pText);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).��_Input�Ƴ�����, ����˵��: "�Ƴ�ָ����Ԫ���е�ָ�����ԡ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: �������� SDT_TEXT, ����˵��: "��Ҫ��ȡ����ֵ������ ��: name"
EXTERN_C void WKE_NAME(73, wke_Input_RemoveAttrValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_RemoveAttrValue((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText);

}

// ���ø�ʽ: _SDT_NULL (WKE_���).��_Inputѡ�����ѡ��״̬, ����˵��: "��_Inputѡ�����ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� �١�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: ѡ��״̬ SDT_BOOL, ����˵��: "����Ϊ�����ѡ�и�ѡ���,Ϊ����ȡ��ѡ��"
EXTERN_C void WKE_NAME(74, wke_Input_SetCheckBoxState)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_SetCheckBoxState((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_int);

}

// ���ø�ʽ: _SDT_NULL (WKE_���).��_Input��ѡ����ѡ��״̬, ����˵��: "��ѡ����ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� �١�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: ѡ��״̬ SDT_BOOL, ����˵��: "����Ϊ�����ѡ�и�ѡ���,Ϊ����ȡ��ѡ��"
EXTERN_C void WKE_NAME(75, wke_Input_SetRadioChecked)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_SetCheckBoxState((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_bool);
}


// ���ø�ʽ: _SDT_NULL (WKE_���).��_Input��Ͽ���ѡ����, ����˵��: "��Ͽ���ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� �١�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: ѡ���� SDT_INT, ����˵��: "ѡ����Ͽ��еĵڼ���,��Ŵ�0��ʼ"
EXTERN_C void WKE_NAME(76, wke_Input_SetComboxIndex)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    INT      arg1 = pArgInf[1].m_int;
    INT      arg2 = pArgInf[2].m_int;
    LPSTR    arg3 = pArgInf[3].m_pText;
    INT      arg4 = pArgInf[4].m_int;
    INT      arg5 = pArgInf[5].m_int;
	js->form_Input_SetComboxIndex((wkeWebView)pArgInf[1].m_int, arg2, arg3, arg4, arg5);
}


// ���ø�ʽ: SDT_INT (WKE_���).��_ȡ��Ԫ������, ����˵��: "��ȡָ�����µ����б�Ԫ�ظ���,ֻ�б�Ԫ�زŻ������"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(77, Form_GetSubCount)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->form_GetSubCount((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).��_�ύ, ����˵��: "�ύָ����,��ע������ύ���ɹ�,��ȷ����ҳ��û���������submit�Ĺ��̡�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(78, Form_Submit)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Submit((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_�ñ���, ����˵��: "ͨ��JS������ҳ�ĵ����⡣"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���� SDT_TEXT, ����˵��: "����"
EXTERN_C void WKE_NAME(79, wke_DocSetTitle)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_SetTitle((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_������, ����˵��: "�����ĵ����š�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ŷ�ֵ SDT_FLOAT, ����˵��: "���ŷ�ֵ"
EXTERN_C void WKE_NAME(80, wke_DocSetZoom)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_SetZoom((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_float);
}

// ���ø�ʽ: SDT_FLOAT (WKE_���).�ĵ�_ȡ����, ����˵��: "ȡ�ĵ����ŷ�ֵ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(81, wke_DocGetZoom)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_float = js->doc_GetZoom((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_INT (WKE_���).�ĵ�_ȡ�ĵ�������, ����˵��: "�ĵ�_ȡ�ĵ������ȡ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(82, wke_DocGetWidth)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetWidth((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_INT (WKE_���).�ĵ�_ȡ�ĵ�����߶�, ����˵��: "�ĵ�_ȡ�ĵ�����߶ȡ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(83, wke_DocGetHeight)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetHeight((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_INT (WKE_���).�ĵ�_ȡBody������, ����˵��: "�ĵ�_ȡBody�����ȡ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(84, wke_DocGetBodyWidth)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetBodyWidth((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_INT (WKE_���).�ĵ�_ȡBody����߶�, ����˵��: "�ĵ�_ȡBody����߶ȡ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(85, wke_DocGetBodyHeight)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetBodyHeight((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_INT (WKE_���).�ĵ�_ȡ���������λ��, ����˵��: "ȡ���������λ�á�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(86, wke_DocGetScollY)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetScollY((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_�����������λ��, ����˵��: "�������������λ�á�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ����λ�� SDT_INT, ����˵��: "�������������λ��"
EXTERN_C void WKE_NAME(87, wke_DocSetScollY)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_SetScollY((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int);
}


// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_�ú��������λ��, ����˵��: "���ú��������λ�á�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ����λ�� SDT_INT, ����˵��: "���ú��������λ��"
EXTERN_C void WKE_NAME(88, wke_DocSetScollX)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_SetScollX((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int);
}

// ���ø�ʽ: SDT_TEXT (WKE_���).�ĵ�_ȡ����, ����˵��: "��ȡ��ǰ��ҳ���롣"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(89, wke_DocGetEncoding)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetEncoding((wkeWebView)pArgInf[1].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_TEXT (WKE_���).�ĵ�_ȡ������, ����˵��: "wke_��ȡ��ҳ��������"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(90, DocGetDomain)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetDomain((wkeWebView)pArgInf[1].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_TEXT (WKE_���).�ĵ�_ȡѡ���ı�, ����˵��: "��ȡ��ǰѡ�е��ı���"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(91, wke_DocGetSelectText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetSelectText((wkeWebView)pArgInf[1].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_TEXT (WKE_���).�ĵ�_ȡԪ������, ����˵��: "ȡָ��Ԫ������ innerHTML��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(92, GetElementHTML)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetElementHTML((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_����༭ģʽ, ����˵��: "����༭ģʽ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: �Ƿ����༭״̬ SDT_BOOL, ����˵��: "Ϊ����򿪱༭ģʽ Ϊ����ر�"
EXTERN_C void WKE_NAME(93, wke_DocEnableEditModel)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EnableEditModel((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_bool);

}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_����, ����˵��: "�༭ģʽ���ơ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(94, DocEditCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditCopy((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_����, ����˵��: "�༭ģʽ���С�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(95, DocEditCut)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditCut((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_ճ��, ����˵��: "�༭ģʽճ����"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(96, DocEditPaste)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditPaste((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_����, ����˵��: "�༭ģʽ������"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(97, DocEditPaste)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditPaste1((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_ȫѡ, ����˵��: "�༭ģʽȫѡ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(98, DocSelectedAll)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	WKE_TB;
	js->doc_SelectedAll((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_ȡ��ȫѡ, ����˵��: "�༭ģʽȡ��ȫѡ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(99, DocCancelSelect)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_CancelSelect((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_����, ����˵��: "�༭ģʽ���á�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(100, DocEditRedo)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditRedo((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_�����������, ����˵��: "����������ӡ�"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: frameid SDT_INT, ����˵��: "���ID , 1�ǵ�ǰ��ҳ�����"
EXTERN_C void WKE_NAME(101, wke_MarkerAllLinks)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;

	js->doc_MarkerAllLinks((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_��������ı���, ����˵��: "��������ı���"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: frameid SDT_INT, ����˵��: "���ID , 1�ǵ�ǰ��ҳ�����"
EXTERN_C void WKE_NAME(102, wke_MarkerAllInputText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_MarkerAllInputText((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).�ĵ�_������а�ť, ����˵��: "������а�ť��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: frameid SDT_INT, ����˵��: "���ID , 1�ǵ�ǰ��ҳ�����"
EXTERN_C void WKE_NAME(103, wke_MarkerAllButton)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_MarkerAllButton((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
}

// ���ø�ʽ: SDT_BOOL (WKE_���).�ĵ�_Jquery�Ƿ��Ѽ���, ����˵��: "�ĵ�_Jquery�Ƿ��Ѽ��ء�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(104, wke_JqueryIsLoding)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_bool = js->doc_JqueryIsLoding((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_TEXT (WKE_���).�ĵ�_ִ��JS����, ����˵��: "���á�"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: �������� SDT_TEXT, ����˵��: "���� getContent() setContent('content') �� sc.getContent('aaaa')"
EXTERN_C void WKE_NAME(105, JSCall)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_JSCall((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText);
	//if (pRetData->m_pText != NULL)
		//delete[](pRetData->m_pText);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_TEXT (WKE_���).�ĵ�_ȡͼƬ��ַ, ����˵��: "�ĵ�_ͼƬȡ��ַ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(106, wke_GetImageElemSrc)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetImageElemSrc((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_TEXT (WKE_���).�ĵ�_ȡ���ӵ�ַ, ����˵��: "�ĵ�_����ȡ��ַ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(107, wke_GetLinkhref)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetLinkhref((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_TEXT (WKE_���).Ԫ��_ȡ����, ����˵��: "��ȡԪ�ص�title����ֵ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(108, wke_GetElemTitle)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->elem_GetTitle((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_TEXT (WKE_���).Ԫ��_ȡ������ʽ, ����˵��: "Ԫ��_ȡ������ʽ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(109, wke_GetElemStyleStr)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->elem_GetStyleStr((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_TEXT (WKE_���).Ԫ��_ȡ�����б�, ����˵��: "Ԫ��_ȡ�����б�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(110, wke_GetClassList)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->elem_GetClassList((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: _SDT_NULL (WKE_���).Ԫ��_��˸���, ����˵��: "���ָ��Ԫ�ء�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(111, wke_SetElementFlag)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_SetentFlag((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).Ԫ��_�ÿ���״̬, ����˵��: "����Ԫ�ؿɼ�״̬��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: Ԫ���±� SDT_INT, ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: �Ƿ���� SDT_BOOL, ����˵��: "��=����,��=������"
EXTERN_C void WKE_NAME(112, wke_SetElementVisableState)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_SetentVisableState((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_bool);
}

// ���ø�ʽ: SDT_INT (WKE_���).Ԫ��_ȡ������, ����˵��: "ȡԪ�غ����ꡣ"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: ƫ�� SDT_INT, ����˵��: "���������Ԫ�����и����ĺ��������,�����ģ��������ܻ��Ԫ�ط�Χ�ڲ�ͬ�ĵ���в���.���Դﵽ���õ�ģ��Ч��"
// ����<5>: [�±� SDT_INT], ����˵��: "������ص�Ԫ�ش���1��,����ʹ�ø��±�ָ��Ԫ���±� ,��ʹ�����ѡ���� div.myclass>ul>li  ��᷵��������Ϊ myclass ��DIV�µ�UL�µ�li���� ,�˴��Ϳ���ָ��ȡ�ڼ���LI,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(113, wke_GetElementPointX)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->elem_GetentPointX((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_int);
}

// ���ø�ʽ: SDT_INT (WKE_���).Ԫ��_ȡ������, ����˵��: "ȡԪ�������ꡣ"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: ƫ�� SDT_INT, ����˵��: "���������Ԫ�����и����ĺ��������,�����ģ��������ܻ��Ԫ�ط�Χ�ڲ�ͬ�ĵ���в���.���Դﵽ���õ�ģ��Ч��"
// ����<5>: [�±� SDT_INT], ����˵��: "������ص�Ԫ�ش���1��,����ʹ�ø��±�ָ��Ԫ���±� ,��ʹ�����ѡ���� div.myclass>ul>li  ��᷵��������Ϊ myclass ��DIV�µ�UL�µ�li���� ,�˴��Ϳ���ָ��ȡ�ڼ���LI,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(114, wke_GetElementPointY)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->elem_GetentPointY((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_int);
}

// ���ø�ʽ: MAKELONG(0x06, 0) (WKE_���).Ԫ��_ȡ������Ϣ, ����˵��: "ȡԪ�ؾ���,Ԫ�صľ�����Ϣ ��� �ұ� ���� �ױ� �� �ߡ�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(115, GetElementRect)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	RECT rc = js->elem_GetentRect((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	int* pMem = (int*)ealloc(sizeof(int) * 6);
	if (pMem)
	{
		memcpy(pMem, &rc, 16);
		*(pMem + 4) = rc.right - rc.left;
		*(pMem + 5) = rc.bottom - rc.top;
	}
	pRetData->m_dtDataType = SDT_TYPE_TYPERECT;
	pRetData->m_pCompoundData = pMem;
}


// ���ø�ʽ: _SDT_NULL (WKE_���).Ԫ��_����ָ���¼�, ����˵��: "����ָ��Ԫ�ص�ָ���¼�,���Դ����¼�������"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [�±� SDT_INT], ����˵��: "������ص�Ԫ�ش���1��,����ʹ�ø��±�ָ��Ԫ���±� ,��ʹ�����ѡ���� div.myclass>ul>li  ��᷵��������Ϊ myclass ��DIV�µ�UL�µ�li���� ,�˴��Ϳ���ָ��ȡ�ڼ���LI,�±��1��ʼ,Ĭ��Ϊ1"
// ����<5>: �¼����� SDT_TEXT, ����˵��: "��ʹ�� #�¼�_ ��ͷ�ĳ���"
// ����<6>: �ر��¼�ð�� SDT_BOOL, ����˵��: "�ر�ð��������Ϊ ��"
// ����<7>: [�¼����� SDT_TEXT], ����˵��: "���Դ���ʱ��ʱ�����¼��������,��Ϊ��"
EXTERN_C void WKE_NAME(116, CallEvent)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_CallEvent((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText, pArgInf[6].m_bool, pArgInf[7].m_pText);
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


// ���ø�ʽ: SDT_INT (WKE_���).�ĵ�_ȡ���������λ��, ����˵��: "��ȡ���������λ�á�"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(162, wke_DocGetScollX)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    pRetData->m_int = js->doc_GetScollX((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_BOOL (WKE_���).��_Inputѡ���ȡѡ��״̬, ����˵��: "ȡѡ���ѡ��״̬��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(163, wke_Input_GetCheckBoxState)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    INT      arg1 = pArgInf[1].m_int;
    INT      arg2 = pArgInf[2].m_int;
    LPSTR    arg3 = pArgInf[3].m_pText;
    INT      arg4 = pArgInf[4].m_int;
    pRetData->m_int = js->form_Input_GetCheckBoxState((wkeWebView)pArgInf[1].m_int, arg2, arg3, arg4);
}

// ���ø�ʽ: SDT_BOOL (WKE_���).��_Input��ѡ��ȡѡ��״̬, ����˵��: "ȡ��ѡ��ѡ��״̬��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(164, wke_Input_GetRadioChecked)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    INT      arg1 = pArgInf[1].m_int;
    INT      arg2 = pArgInf[2].m_int;
    LPSTR    arg3 = pArgInf[3].m_pText;
    INT      arg4 = pArgInf[4].m_int;
    pRetData->m_int = js->form_Input_GetRadioChecked((wkeWebView)pArgInf[1].m_int, arg2, arg3, arg4);
}

// ���ø�ʽ: SDT_INT (WKE_���).��_Input��Ͽ�ȡѡ����, ����˵��: "ȡ��Ͽ�ѡ����������"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(165, wke_Input_GetComboxIndex)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    pRetData->m_int = js->form_Input_GetComboxIndex((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);

}

// ���ø�ʽ: SDT_INT (WKE_���).��_ȡ������, ����˵��: "��ȡָ������µ�����form������,ֻ�б��Ż������"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(169, wke_GetFormLength)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    pRetData->m_int = js->form_GetFormCount((wkeWebView)pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_INT (WKE_���).Ԫ��_ȡ��Ԫ������, ����˵��: "ȡָ��Ԫ�ص���Ԫ������"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ģʽ SDT_INT, ����˵��: "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��"
// ����<3>: ѡ����ʽ SDT_TEXT, ����˵��: "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active"
// ����<4>: [Ԫ���±� SDT_INT], ����˵��: "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1"
EXTERN_C void WKE_NAME(181, GetElementCount)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    int r = js->elem_GetCount((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
    pRetData->m_int = r;
}

// ���ø�ʽ: _SDT_NULL (WKE_���).��ֵ, ����˵��: "����һ�� WKE_��� �ڲ������ݸ�ֵ����ǰ WKE_��� ��"
// ����<1>: WKE_TB MAKELONG(0x01, 0), ����˵��: "��һ��WKE_��� ����"
EXTERN_C void WKE_NAME(194, wke_assign)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    if ( !pArgInf[1].m_ppCompoundData )return;
    CwkeTBInfo* p = (CwkeTBInfo*)( *pArgInf[1].m_ppCompoundData );
    if ( !p )return;
    js->assign(p);
}

// ���ø�ʽ: _SDT_NULL (WKE_���).���, ����˵��: "��յ�ǰ WKE_����ڵ�����"
// �޲���
EXTERN_C void WKE_NAME(195, wke_clear)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    js->clear();
}

// ���ø�ʽ: _SDT_NULL (WKE_���).ȡ�༭���α�λ��, ����˵��: "��ȡ�༭����Ǹ��α��λ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
EXTERN_C void WKE_NAME(199, wke_GetCaretRect)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeWebView webView = (wkeWebView)pArgInf[1].m_int;
    if ( !webView )return;
    wkeGetCaretRect(webView);
}





















DEF_EXECUTE_CMD(wke_Input_SetRadioChecked)
{
    // ���ø�ʽ��_SDT_NULL ��_Input��ѡ����ѡ��״̬ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_BOOL ѡ��״̬)	
    //��ϸ���ܣ���ѡ����ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� ��
    WKE_TB;
    js->form_Input_SetRadioChecked((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_bool);
}














