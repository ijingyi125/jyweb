#include "pch.h"
#include "CwkeTBInfo.h"
#include <assist.h>
CwkeTBInfo::CwkeTBInfo()
{
	m_framex = 0;
	m_framey = 0;
}
CwkeTBInfo::CwkeTBInfo(const CwkeTBInfo& obj)
{
	m_framex = obj.m_framex;
	m_framey = obj.m_framey;
	m_frameStr = obj.m_frameStr;
}
CwkeTBInfo::~CwkeTBInfo()
{

}


jsValue CwkeTBInfo::RunJS(wkeWebView webView, const char* js)
{
	if (!webView)return 0;
	wstr str = wstr::A2W(js);
	return RunJS(webView, str.c_str());
}
jsValue CwkeTBInfo::RunJS(wkeWebView webView, const wchar_t* js)
{
	if (!webView)return 0;
	return wkeRunJSW(webView, js);
}
jsValue CwkeTBInfo::RunJS(wkeWebView webView, const _str& js)
{
	if (!webView)return 0;
	wstr str = js.a2w();
	return RunJS(webView, str.c_str());
}
jsValue CwkeTBInfo::RunJS(wkeWebView webView, const wstr& js)
{
	if (!webView)return 0;
	return RunJS(webView, js.c_str());
}

void CwkeTBInfo::clear()
{
	m_frameStr = "";
	m_framex = 0;
	m_framey = 0;
}

CwkeTBInfo& CwkeTBInfo::assign(const CwkeTBInfo& obj)
{
	m_frameStr = obj.m_frameStr;
	m_framex = obj.m_framex;
	m_framey = obj.m_framey;
	return *this;
}

CwkeTBInfo& CwkeTBInfo::assign(const CwkeTBInfo* obj)
{
	if (!obj)return *this;
	m_frameStr = obj->m_frameStr;
	m_framex = obj->m_framex;
	m_framey = obj->m_framey;
	return *this;
}

int CwkeTBInfo::GetFrameX(wkeWebView webView, const char* con)
{
	if (!webView)return 0;
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(m_frameStr).append("getBoundingClientRect().left+document.documentElement.scrollLeft;");

	jsValue vl = RunJS(webView, js);
	int framex = jsToInt(es, vl);
	return framex;
}

int CwkeTBInfo::GetFrameY(wkeWebView webView, const char* con)
{
	if (!webView)return 0;
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(m_frameStr).append("getBoundingClientRect().top+document.documentElement.scrollTop;");

	jsValue vl = RunJS(webView, js);
	int framey = jsToInt(es, vl);
	return framey;
}

_str CwkeTBInfo::InnerHtmlSelector(const char* con)
{
	_str js;
	strArrA tmp;

	int tmpCount = _str::strtok(con, &tmp, ".");
	if (tmpCount == 2)
	{
		strArrA rel;
		int relCount = _str::strtok(tmp[1], &rel, "==");
		if (relCount != 2)
		{
			js.assign("console.log('ѡ�������ô���,���ѡ��aԪ�ص�innerHTML���� �� ����a.innerHTML')");
			js.Addref();
			return js;
		}
		js.assign("(function(){var elems = ").append(m_frameStr);
		js.append("document.querySelectorAll('").append(tmp[0]);
		js.append("'); for(var i = 0; i < elems.length; i++){ if(elems[i].innerHTML == '");
		js.append(rel[1]).append("'){ return elems[i]; }}})()");
		js.Addref();
		return js;
	}
	js = "console.log('ѡ�������ô���,���ѡ��aԪ�ص�innerHTML���� �� ����a.innerHTML')";
	js.Addref();
	return js;
}


_str CwkeTBInfo::CreateElementSelectorStr(wkeWebView webView, int model, const char* con, int index)
{
	if (index < 1)index = 1;
	index--;
	_str str;
	if (model == MODEL_JY)
	{
		if (_str::find(con, "innerhtml", 0, FALSE) != -1)
		{
			str = InnerHtmlSelector(con);
			str.Addref();
			return str;
		}
		_str tmp(con);
		tmp.replace("=", "", 0, 1, true);

		str.assign(m_frameStr).append("document.querySelectorAll('[");
		str.append(tmp).append("]')[").append(index).append("]");
		str.Addref();
		return str;
	}
	str.assign(m_frameStr).append("document.querySelectorAll('");
	str.append(con).append("')[").append(index).append("]");
	str.Addref();
	return str;
}

_str CwkeTBInfo::CreateFrameCodeStr(wkeWebView webView, int model, const char* con, int index)
{
	if (index < 1)index = 1;
	index--;
	_str str;
	if (model == MODEL_JY)
	{
		_str tmp(con);
		tmp.replace("=", "", 0, 1, true);

		str.assign(m_frameStr).append("document.querySelectorAll('[");
		str.append(tmp).append("]')[").append(index).append("].");
		str.Addref();
		return str;
	}
	str.assign(m_frameStr).append("document.querySelectorAll('");
	str.append(con).append("')[").append(index).append("].");
	str.Addref();
	return str;
}









inline int __int_runjs(wkeWebView webView, LPCSTR js)
{
	jsExecState es = wkeGlobalExec(webView);
	wstr jsw = _str::A2W(js);
	jsValue vl = wkeRunJSW(webView, jsw.c_str());
	return jsToInt(es, vl);
}
#define __RUNJS_INT(_js) __int_runjs(webView, _js)

// �ݹ�����ȡ���js����
inline void __make_frame_js(_str& js, int frameIndex, int index, int frameCount, wkeWebView webView)
{
	if (frameIndex == 0 || index > frameIndex)return;
	if (js.empty())
		js.assign("document.querySelectorAll('iframe')");
	else
		js.append("contentWindow.document.querySelectorAll('iframe')");

	_str code(js.size() + 100);

	code.assign("return ").append(js).append(".length");
	int fLen = __RUNJS_INT(code.c_str());
	if (fLen == 0) return;
	for (int i = 0; i < fLen; i++)
	{
		if (index == frameIndex)
		{
			js.append("[").append(i).append("].");
			return;
		}
		index++;
	}
	js.append("[").append(fLen - 1).append("].");
	if (index < frameCount)
		__make_frame_js(js, frameIndex, index, frameCount, webView);
}


// ���ø�ʽ��_SDT_NULL ��_������� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ����ÿ���Ժ�,���е� ��_ �������������������ڲ�����,
void CwkeTBInfo::form_SetFrame(wkeWebView webView, int model, const char* con, int index)
{
	if (index < 2)
	{
		m_frameStr = "";
		return;
	}

	if (con == 0 || *con == 0)
	{
		con = "iframe";
	}
	m_frameStr.resize(0);
	int count = form_GetFrameCount(webView);
	if (index > count)index = count;

	__make_frame_js(m_frameStr, index, 1, count, webView);
	//m_frameStr = CreateFrameCodeStr(webView, model, con, index);

	//m_framex = GetFrameX(webView, m_frameStr.c_str());
	//m_framey = GetFrameY(webView, m_frameStr.c_str());

	//m_frameStr.append("contentWindow.");



	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(m_frameStr).append("getBoundingClientRect().left+document.documentElement.scrollLeft;");
	jsValue vl = RunJS(webView, js);
	m_framex = jsToInt(es, vl);

	js.assign("return ").append(m_frameStr).append("getBoundingClientRect().top+document.documentElement.scrollTop;");
	vl = RunJS(webView, js);
	m_framey = jsToInt(es, vl);
	m_frameStr += "contentWindow.";

}

// ���ø�ʽ��SDT_INT ��_ȡ��ǰ������� (SDT_INT WebView)	��ϸ���ܣ���ȡ��ǰ��ҳ�п��(iframe)������
int CwkeTBInfo::form_GetFrameCount(wkeWebView webView)
{
	_str str("var count = 0;function loop(frame){ for(var y=0; y<frame.length;y++){ count++; loop(frame[y].frames)}} window.frames.length > 0 ? count++:count=0;loop(window.frames); return count+''");
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, str);
	return jsToInt(es, vl);
}

// ���ø�ʽ��_SDT_NULL ��_Input��� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ�ȡָ��Ԫ�����Ե�ֵ
void CwkeTBInfo::form_Input_Click(wkeWebView webView, int model, const char* con, int index)
{
	elem_Click(webView, model, con, index);
}

// ���ø�ʽ��SDT_TEXT ��_Input������ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_TEXT ��������)	��ϸ���ܣ���ȡ����ָ��inputԪ�ص�����ֵ
_str CwkeTBInfo::form_Input_ReadAttrValue(wkeWebView webView, int model, const char* con, int index, char* name)
{
	//���� ȡԪ������ֵ() ʵ��
	return elem_GetAttribute(webView, model, con, index, name);
}

// ���ø�ʽ��_SDT_NULL ��_Inputд���� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_TEXT ��������, SDT_TEXT ����ֵ)	��ϸ���ܣ���ָ��INPUTԪ��д������ֵ,������Դ�������¸����Ե�ֵ,������������һ������
void CwkeTBInfo::form_Input_WriteAttrVal(wkeWebView webView, int model, const char* con, int index, char* name, char* value)
{
	//���� ��Ԫ������ֵ() ʵ��
	elem_SetAttribute(webView, model, con, index, name, value);
}

// ���ø�ʽ��_SDT_NULL ��_Input�Ƴ����� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_TEXT ��������)	��ϸ���ܣ��Ƴ�ָ����Ԫ���е�ָ������
void CwkeTBInfo::form_Input_RemoveAttrValue(wkeWebView webView, int model, const char* con, int index, char* name)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".removeAttribute('" + name + "')");
	RunJS(webView, str);
}

 //��_Inputѡ���ȡѡ��״̬ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ���_Inputѡ���ȡѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� ��
BOOL CwkeTBInfo::form_Input_GetCheckBoxState(wkeWebView webView, int model, const  char* con, int index)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".checked");
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, _str("return ") + str);
	return jsToBoolean(es, vl);


}

 // ���ø�ʽ��_SDT_NULL ��_Inputѡ�����ѡ��״̬ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_BOOL ѡ��״̬)	��ϸ���ܣ���_Inputѡ�����ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� ��
void CwkeTBInfo::form_Input_SetCheckBoxState(wkeWebView webView, int model, const char* con, int index, BOOL state)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".checked=" + (state ? "true" : "false"));
	RunJS(webView, str);

}

// ���ø�ʽ��_SDT_NULL ��_Input��ѡ��ȡѡ��״̬ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ���ѡ��ȡѡ��״̬
BOOL CwkeTBInfo::form_Input_GetRadioChecked(wkeWebView webView, int model, const char* con, int index)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".checked");
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView,_str("return ") + str);
	return jsToBoolean(es, vl);
}

// ���ø�ʽ��_SDT_NULL ��_Input��ѡ����ѡ��״̬ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_BOOL ѡ��״̬)	��ϸ���ܣ���ѡ����ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� ��
void CwkeTBInfo::form_Input_SetRadioChecked(wkeWebView webView, int model, const char* con, int index, BOOL state)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".checked=" + (state ? "true" : "false"));
	RunJS(webView, str);
}

// ���ø�ʽ��_SDT_NULL ��_Input_��Ͽ�ȡѡ���� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ���Ͽ���ѡ��״̬
int CwkeTBInfo::form_Input_GetComboxIndex(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".selectedIndex");
	jsValue vl = RunJS(webView,_str("return ") +  str);
	return jsToInt(es, vl);
}

// ���ø�ʽ��_SDT_NULL ��_Input_��Ͽ���ѡ��״̬ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_INT ѡ����)	��ϸ���ܣ���Ͽ���ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� ��
void CwkeTBInfo::form_Input_SetComboxIndex(wkeWebView webView, int model, const char* con, int index, int selIndex)
{
	char strIndex[10] = { 0 };
	if (selIndex < 0)selIndex = 0;
	itoa(selIndex, strIndex, 10);
	_str str(CreateElementSelectorStr(webView, model, con, index) + "[" + strIndex + "].selected=true");
	RunJS(webView, str);
}

 // ���ø�ʽ��SDT_INT ��_ȡ������ (SDT_INT WebView)	��ϸ���ܣ���ȡָ������µ�����form������,ֻ�б��Ż����
int CwkeTBInfo::form_GetFormCount(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	_str str;
	jsValue vl = NULL;

	//document.querySelector("form").elements.length
	// str = return document.querySelectorAll('#tryitform').length
	str = _str("return ") + m_frameStr + "document.forms.length";
	vl = RunJS(webView, str);
	return jsToInt(es, vl);
}

 // ���ø�ʽ��SDT_INT ��_ȡ��Ԫ������ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ���ȡָ�����µ����б�Ԫ�ظ���,ֻ�б�Ԫ�زŻ����
int CwkeTBInfo::form_GetSubCount(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str str(con);
	jsValue vl = NULL;
	if (model == MODEL_JY)
	{
		str.replace("=", "", 0, 1, true);
		_str js(260);
		js.assign("return ").append(m_frameStr).append("document.querySelector('[").append(str);
		js.append("]').elements.length");
		vl = RunJS(webView, js);
	}
	else
	{
		//document.querySelector("form").elements.length
		// str = return document.querySelectorAll('#tryitform').length
		_str js(260);
		js.assign("return ").append(m_frameStr).append("document.querySelector('").append(con).append("').elements.length");
		vl = RunJS(webView, js);
	}

	return jsToInt(es, vl);
}

// ���ø�ʽ��_SDT_NULL ��_�ύ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ��ύָ����,��ע������ύ���ɹ�,��ȷ����ҳ��û���������submit�Ĺ���
void CwkeTBInfo::form_Submit(wkeWebView webView, int model, const char* con, int index)
{
	_str js(260);
	js.assign(CreateElementSelectorStr(webView, model, con, index)).append(".submit()");
	RunJS(webView, js);
}


// ���ø�ʽ��_SDT_NULL �ĵ�_�ñ��� (SDT_INT WebView, SDT_TEXT ����)	��ϸ���ܣ�ͨ��JS������ҳ�ĵ�����
void CwkeTBInfo::doc_SetTitle(wkeWebView webView, _str title)
{
	_str js(260);
	js.assign("document.title=\"").append(title).append("\"");
	RunJS(webView, js);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_������ (SDT_INT WebView, SDT_FLOAT ���ŷ�ֵ)	��ϸ���ܣ������ĵ�����
void CwkeTBInfo::doc_SetZoom(wkeWebView webView, float factor)
{
	wkeSetZoomFactor(webView, factor);
}

// ���ø�ʽ��SDT_FLOAT �ĵ�_ȡ���� (SDT_INT WebView)	��ϸ���ܣ�ȡ�ĵ����ŷ�ֵ
float CwkeTBInfo::doc_GetZoom(wkeWebView webView)
{
	return wkeGetZoomFactor(webView);
}

// ���ø�ʽ��SDT_INT �ĵ�_ȡ�ĵ������� (SDT_INT WebView)	��ϸ���ܣ��ĵ�_ȡ�ĵ�������
int CwkeTBInfo::doc_GetWidth(wkeWebView webView)
{
	return wkeGetWidth(webView);
}

// ���ø�ʽ��SDT_INT �ĵ�_ȡ�ĵ�����߶� (SDT_INT WebView)	��ϸ���ܣ��ĵ�_ȡ�ĵ�����߶�
int CwkeTBInfo::doc_GetHeight(wkeWebView webView)
{
	return wkeGetHeight(webView);
}

// ���ø�ʽ��SDT_INT �ĵ�_ȡBody������ (SDT_INT WebView)	��ϸ���ܣ��ĵ�_ȡBody������
int CwkeTBInfo::doc_GetBodyWidth(wkeWebView webView)
{
	return wkeGetContentWidth(webView);
}

// ���ø�ʽ��SDT_INT �ĵ�_ȡBody����߶� (SDT_INT WebView)	��ϸ���ܣ��ĵ�_ȡBody����߶�
int CwkeTBInfo::doc_GetBodyHeight(wkeWebView webView)
{
	return wkeGetContentHeight(webView);;
}

// ���ø�ʽ��SDT_INT �ĵ�_ȡ���������λ�� (SDT_INT WebView)	��ϸ���ܣ�ȡ���������λ��
int CwkeTBInfo::doc_GetScollY(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.body.scrollTop");
	return jsToInt(es, vl);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_�����������λ�� (SDT_INT WebView, SDT_INT ����λ��)	��ϸ���ܣ��������������λ��
void CwkeTBInfo::doc_SetScollY(wkeWebView webView, int pos)
{
	_str js(260);
	js.assign("document.body.scrollTop=").append(pos);
	RunJS(webView, js);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_ȡ���������λ�� (SDT_INT WebView)	��ϸ���ܣ�ȡ���������λ��
int CwkeTBInfo::doc_GetScollX(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.body.scrollLeft");
	return jsToInt(es, vl);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_�ú��������λ�� (SDT_INT WebView, SDT_INT ����λ��)	��ϸ���ܣ����ú��������λ��
void CwkeTBInfo::doc_SetScollX(wkeWebView webView, int pos)
{
	_str js(260);
	js.assign("document.body.scrollLeft=").append(pos);
	RunJS(webView, js);
}

// ���ø�ʽ��SDT_TEXT �ĵ�_ȡ���� (SDT_INT WebView)	��ϸ���ܣ���ȡ��ǰ��ҳ����
_str CwkeTBInfo::doc_GetEncoding(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.charset");
	LPCSTR tmp = jsToString(es, vl);
	return tmp;
}

// ���ø�ʽ��SDT_TEXT �ĵ�_ȡ������ (SDT_INT WebView)	��ϸ���ܣ�wke_��ȡ��ҳ������
_str CwkeTBInfo::doc_GetDomain(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.domain");
	LPCSTR tmp = jsToString(es, vl);
	_str str(tmp);
	str.Addref();
	return str;
}

// ���ø�ʽ��SDT_TEXT �ĵ�_ȡѡ���ı� (SDT_INT WebView)	��ϸ���ܣ���ȡ��ǰѡ�е��ı�
_str CwkeTBInfo::doc_GetSelectText(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.getSelection().toString()");
	LPCSTR tmp = jsToString(es, vl);
	return tmp;
}

// ���ø�ʽ��SDT_TEXT �ĵ�_ȡԪ������ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ�ȡָ��Ԫ������ innerHTML
_str CwkeTBInfo::doc_GetElementHTML(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".innerHTML");
	jsValue vl = RunJS(webView, js);
	LPCSTR tmp = jsToString(es, vl);
	return tmp;
}

// ���ø�ʽ��_SDT_NULL �ĵ�_����༭ģʽ (SDT_INT WebView, SDT_BOOL �Ƿ����༭״̬)	��ϸ���ܣ�����༭ģʽ
void CwkeTBInfo::doc_EnableEditModel(wkeWebView webView, bool editable)
{
	wkeSetEditable(webView, editable);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_���� (SDT_INT WebView)	��ϸ���ܣ��༭ģʽ����
void CwkeTBInfo::doc_EditCopy(wkeWebView webView)
{
	wkeEditorCopy(webView);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_���� (SDT_INT WebView)	��ϸ���ܣ��༭ģʽ����
void CwkeTBInfo::doc_EditCut(wkeWebView webView)
{
	wkeEditorCut(webView);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_ճ�� (SDT_INT WebView)	��ϸ���ܣ��༭ģʽճ��
void CwkeTBInfo::doc_EditPaste(wkeWebView webView)
{
	wkeEditorPaste(webView);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_���� (SDT_INT WebView)	��ϸ���ܣ��༭ģʽ����
void CwkeTBInfo::doc_EditPaste1(wkeWebView webView)
{
	wkeEditorUndo(webView);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_ȫѡ (SDT_INT WebView)	��ϸ���ܣ��༭ģʽȫѡ
void CwkeTBInfo::doc_SelectedAll(wkeWebView webView)
{
	wkeEditorSelectAll(webView);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_ȡ��ȫѡ (SDT_INT WebView)	��ϸ���ܣ��༭ģʽȡ��ȫѡ
void CwkeTBInfo::doc_CancelSelect(wkeWebView webView)
{
	wkeEditorUnSelect(webView);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_���� (SDT_INT WebView)	��ϸ���ܣ��༭ģʽ����
void CwkeTBInfo::doc_EditRedo(wkeWebView webView)
{
	wkeEditorRedo(webView);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_����������� (SDT_INT webView, SDT_INT frameid)	��ϸ���ܣ������������
void CwkeTBInfo::doc_MarkerAllLinks(wkeWebView webView, wkeWebFrameHandle frameID)
{
	const wchar_t js[] = L"var dom = new Array();\
dom=document.getElementsByTagName(\"a\");\
for (var i=0;i<dom.length;i++)\
{\
var Mess=dom[i].innerHTML;\
if (Mess.indexOf(\">��\")==-1)\
  {\
  dom[i].innerHTML=Mess+\"_<font color=red>��\" +i+ \"</font>\";\
  }\
}";
	_str str = wstr::W2U(js);
	wkeRunJsByFrame(webView, frameID, str.c_str(), TRUE);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_��������ı��� (SDT_INT webView, SDT_INT frameid)	��ϸ���ܣ���������ı���
void CwkeTBInfo::doc_MarkerAllInputText(wkeWebView webView, wkeWebFrameHandle frameID)
{
	const wchar_t js[] = L"var dom = new Array();\
var X=0;\
dom=document.getElementsByTagName(\"input\");\
for (var i=0;i<dom.length;i++)\
{\
var Mess=dom[i].type;\
var biaozhun=\"text|password|file\";\
if (biaozhun.indexOf(Mess)==-1)\
  {\
}else{\
  X=X+1;\
  dom[i].value=\"�ı���\"+X;\
  }\
}";
	_str str = wstr::W2U(js);
	wkeRunJsByFrame(webView, frameID, str.c_str(), TRUE);
}

// ���ø�ʽ��_SDT_NULL �ĵ�_������а�ť (SDT_INT webView, SDT_INT frameid)	��ϸ���ܣ�������а�ť
void CwkeTBInfo::doc_MarkerAllButton(wkeWebView webView, wkeWebFrameHandle frameID)
{
	const wchar_t js[] = L"var dom = new Array();\
var X=0;\
var biaozhun=\"button|submit|reset\";\
dom=document.getElementsByTagName(\"input\");\
for (var i=0;i<dom.length;i++)\
{\
var Mess=dom[i].type;\
if (biaozhun.indexOf(Mess)==-1)\
  {\
}else{\
  X=X+1;\
  dom[i].value=\"��ť\"+X;\
  }\
}\
var dom = new Array();\
dom=document.getElementsByTagName(\"button\");\
var i=0;\
for (var i=0;i<dom.length;i++)\
{\
  X=X+1;\
  dom[i].value=\"��ť\"+X;\
}";
	_str str = wstr::W2U(js);
	wkeRunJsByFrame(webView, frameID, str.c_str(), TRUE);
}

// ���ø�ʽ��SDT_BOOL �ĵ�_Jquery�Ƿ��Ѽ��� (SDT_INT webView)	��ϸ���ܣ��ĵ�_Jquery�Ƿ��Ѽ���
BOOL CwkeTBInfo::doc_JqueryIsLoding(wkeWebView webView)
{
	wchar_t* src = L"src = ��try{ if( $ || Jquery ) return 'fn.init'; if(jQuery) $=jQuery; return jQuery; }catch(err){ return 'err'; }��";
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, src);
	_str str = wstr::W2A(jsToStringW(es, vl));
	
	BOOL bRet = _str::find(str.c_str(), "fn.init") > -1;
	return bRet;
}

// ���ø�ʽ��SDT_TEXT �ĵ�_ִ��JS���� (SDT_INT webView, SDT_TEXT ��������)	��ϸ���ܣ�����
_str CwkeTBInfo::doc_JSCall(wkeWebView webView, _str name)
{
	_str str("try {\
  return {code};\
} catch (error) {\
  return error.toString();\
}");
	_str js(260);
	js.assign(m_frameStr).append(name);

	str.replace("{code}", js);
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, str);
	_str sRet = jsToString(es, vl);
	return sRet;
}

// ���ø�ʽ��SDT_TEXT �ĵ�_ȡͼƬ��ַ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ��ĵ�_ͼƬȡ��ַ
_str CwkeTBInfo::doc_GetImageElemSrc(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('src')");
	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

// ���ø�ʽ��SDT_TEXT �ĵ�_ȡ���ӵ�ַ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ��ĵ�_����ȡ��ַ
_str CwkeTBInfo::doc_GetLinkhref(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('href')");

	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

 // ���ø�ʽ��_SDT_NULL Ԫ�ص�� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ�Ԫ�ص��
void CwkeTBInfo::elem_Click(wkeWebView webView, int model, const char* con, int index)
{
	_str js(260);
	js.assign(CreateElementSelectorStr(webView, model, con, index)).append(".click()");
	RunJS(webView, js);
}

// ���ø�ʽ��_SDT_NULL Ԫ���ý��� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ�Ԫ���ý���
void CwkeTBInfo::elem_SetFouce(wkeWebView webView, int model, const char* con, int index)
{
	wkeSetFocus(webView);
	RunJS(webView, CreateElementSelectorStr(webView, model, con, index) + ".focus()");
}

// ���ø�ʽ��SDT_TEXT ȡԪ������ֵ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_TEXT ��������)	��ϸ���ܣ�ȡָ��Ԫ�����Ե���
_str CwkeTBInfo::elem_GetAttribute(wkeWebView webView, int model, const char* con, int index, char* name)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(520);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".").append(name).append(" || ");
	js.append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('").append(name).append("')");
	jsValue el = RunJS(webView, js);
	_str sRet = jsToString(es, el);
	return sRet;
}

// ���ø�ʽ��_SDT_NULL ��Ԫ������ֵ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�, SDT_TEXT ��������, SDT_TEXT ����ֵ)	��ϸ���ܣ�����ָ��Ԫ�ص�ֵ
void CwkeTBInfo::elem_SetAttribute(wkeWebView webView, int model, const char* con, int index, char* name, char* value)
{
	_str js(CreateElementSelectorStr(webView, model, con, index));
	_str s(520);
	s.assign(js).append(".setAttribute('").append(name).append("','").append(value).append("')");
	RunJS(webView, s);
	s.assign(js).append(".").append(name).append("='").append(value).append('\'');
	RunJS(webView, s);

}

// ���ø�ʽ��SDT_TEXT Ԫ��_ȡ���� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ���ȡԪ�ص�title����ֵ
_str CwkeTBInfo::elem_GetTitle(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".title");
	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

 // ���ø�ʽ��SDT_TEXT Ԫ��_ȡ������ʽ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ�Ԫ��_ȡ������ʽ
_str CwkeTBInfo::elem_GetStyleStr(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('style')");
	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

// ���ø�ʽ��SDT_TEXT Ԫ��_ȡ�����б� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ�Ԫ��_ȡ�����б�
_str CwkeTBInfo::elem_GetClassList(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('class')");
	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

// ���ø�ʽ��_SDT_NULL Ԫ��_��˸��� (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ����ָ��Ԫ��
void CwkeTBInfo::elem_SetentFlag(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str tmp = CreateElementSelectorStr(webView, model, con, index);
	_str js(520);
	js.assign("(function(){ var ele=");
	js.append(tmp);
	js.append(";var count=0;var p= setInterval( function(){ if (count==10){ele.style.border='2px solid #CC0000';clearInterval(p);return; }if(count%2==0){ ele.style.border='2px solid #CC0000'} else {ele.style.border=''} count++;},100) })();");	

	RunJS(webView, js);
}

// ���ø�ʽ��_SDT_NULL Ԫ��_�ÿ���״̬ (SDT_INT WebView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT Ԫ���±�)	��ϸ���ܣ�����Ԫ�ؿɼ�״̬
void CwkeTBInfo::elem_SetentVisableState(wkeWebView webView, int model, const char* con, int index, BOOL isVisible)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.append(CreateElementSelectorStr(webView, model, con, index));
	js.append(isVisible ? ".style.display='block'" : ".style.display='none'");

	RunJS(webView, js);
}

// ���ø�ʽ��SDT_INT Ԫ��_ȡ������ (SDT_INT webView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT ƫ��, SDT_INT �±�)	��ϸ���ܣ�ȡԪ�غ�����
int CwkeTBInfo::elem_GetentPointX(wkeWebView webView, int model, const char* con, int offsetX, int index)
{
	jsExecState es = wkeGlobalExec(webView);

	_str js(260);
	js.assign("return ");
	js.append(CreateElementSelectorStr(webView, model, con, index));
	js.append(".getBoundingClientRect().left+document.documentElement.scrollLeft;");

	jsValue vl = RunJS(webView, js);
	int rel = jsToInt(es, vl);
	return rel + m_framex + offsetX;
}

// ���ø�ʽ��SDT_INT Ԫ��_ȡ������ (SDT_INT webView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT ƫ��, SDT_INT �±�)	��ϸ���ܣ�ȡԪ��������
int CwkeTBInfo::elem_GetentPointY(wkeWebView webView, int model, const char* con, int offsetY, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ");
	js.append(CreateElementSelectorStr(webView, model, con, index));
	js.append(".getBoundingClientRect().top+document.documentElement.scrollTop;");

	jsValue vl = RunJS(webView, js);
	int rel = jsToInt(es, vl);
	return rel + m_framey + offsetY;
}

// ���ø�ʽ��6 Ԫ��_ȡ������Ϣ (SDT_INT webView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT �±�)	��ϸ���ܣ�ȡԪ�ؾ���,Ԫ�صľ�����Ϣ ��� �ұ� ���� �ױ� �� ��
RECT CwkeTBInfo::elem_GetentRect(wkeWebView webView, int model, const char* con, int index)
{
	_str js(260);
	js.assign("return ");
	js.append(CreateElementSelectorStr(webView, model, con, index));
	js.append(".getBoundingClientRect()");

	jsValue vl = NULL;
	jsExecState es = wkeGlobalExec(webView);
	RECT rc = { 0 };
	vl = RunJS(webView, js + ".left");
	rc.left = jsToInt(es, vl);

	vl = RunJS(webView, js + ".top");
	rc.top = jsToInt(es, vl);

	vl = RunJS(webView, js + ".right");
	rc.right = jsToInt(es, vl);

	vl = RunJS(webView, js + ".bottom");
	rc.bottom = jsToInt(es, vl);
	return rc;
}

// ���ø�ʽ��_SDT_NULL Ԫ��_����ָ���¼� (SDT_INT webView, SDT_INT ���ģʽ, SDT_TEXT ѡ����ʽ, SDT_INT �±�, SDT_TEXT �¼�����, SDT_BOOL �ر��¼�ð��, SDT_TEXT �¼�����)	��ϸ���ܣ�����ָ��Ԫ�ص�ָ���¼�,���Դ����¼�����
void CwkeTBInfo::elem_CallEvent(wkeWebView webView, int model, const char* con, int index, char* eventName, BOOL bubbles, char* eventArg)
{
	_str js(520);
	js.assign("var dom=");
	js.append(CreateElementSelectorStr(webView, model, con, index));
	js.append("; dom.dispatchEvent(new CustomEvent('");
	js.append(eventName).append("', {detail: '");
	js.append(eventArg).append("',bubbles: ");
	js.append(bubbles ? "false" : "true");
	js.append(",cancelable: true}));");

	wkeSetFocus(webView);
	RunJS(webView, js);
}

// Ԫ��_ȡ��Ԫ������
int CwkeTBInfo::elem_GetCount(wkeWebView webView, int model, const char* con, int index)
{
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index));
	js.append(".childElementCount");

	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, js);
	return jsToInt(es, vl);
}
