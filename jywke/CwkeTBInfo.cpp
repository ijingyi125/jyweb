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
			js.assign("console.log('选择器配置错误,如果选择a元素的innerHTML属性 请 输入a.innerHTML')");
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
	js = "console.log('选择器配置错误,如果选择a元素的innerHTML属性 请 输入a.innerHTML')";
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

// 递归生成取框架js代码
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


// 调用格式：_SDT_NULL 表单_置填表框架 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：设置框架以后,所有的 表单_ 填表操作都是在这个框架内部进行,
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

// 调用格式：SDT_INT 表单_取当前框架数量 (SDT_INT WebView)	详细介绍：获取当前网页中框架(iframe)的数量
int CwkeTBInfo::form_GetFrameCount(wkeWebView webView)
{
	_str str("var count = 0;function loop(frame){ for(var y=0; y<frame.length;y++){ count++; loop(frame[y].frames)}} window.frames.length > 0 ? count++:count=0;loop(window.frames); return count+''");
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, str);
	return jsToInt(es, vl);
}

// 调用格式：_SDT_NULL 表单_Input点击 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：取指定元素属性的值
void CwkeTBInfo::form_Input_Click(wkeWebView webView, int model, const char* con, int index)
{
	elem_Click(webView, model, con, index);
}

// 调用格式：SDT_TEXT 表单_Input读属性 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_TEXT 属性名称)	详细介绍：读取表单中指定input元素的属性值
_str CwkeTBInfo::form_Input_ReadAttrValue(wkeWebView webView, int model, const char* con, int index, char* name)
{
	//调用 取元素属性值() 实现
	return elem_GetAttribute(webView, model, con, index, name);
}

// 调用格式：_SDT_NULL 表单_Input写属性 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_TEXT 属性名称, SDT_TEXT 属性值)	详细介绍：向指定INPUT元素写入属性值,如果属性存在则更新该属性的值,不存在则增加一个属性
void CwkeTBInfo::form_Input_WriteAttrVal(wkeWebView webView, int model, const char* con, int index, char* name, char* value)
{
	//调用 置元素属性值() 实现
	elem_SetAttribute(webView, model, con, index, name, value);
}

// 调用格式：_SDT_NULL 表单_Input移除属性 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_TEXT 属性名称)	详细介绍：移除指定表单元素中的指定属性
void CwkeTBInfo::form_Input_RemoveAttrValue(wkeWebView webView, int model, const char* con, int index, char* name)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".removeAttribute('" + name + "')");
	RunJS(webView, str);
}

 //表单_Input选择框取选中状态 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：表单_Input选择框取选中状态,为真选中,为假取消选中 假
BOOL CwkeTBInfo::form_Input_GetCheckBoxState(wkeWebView webView, int model, const  char* con, int index)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".checked");
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, _str("return ") + str);
	return jsToBoolean(es, vl);


}

 // 调用格式：_SDT_NULL 表单_Input选择框置选中状态 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_BOOL 选中状态)	详细介绍：表单_Input选择框置选中状态,为真选中,为假取消选中 假
void CwkeTBInfo::form_Input_SetCheckBoxState(wkeWebView webView, int model, const char* con, int index, BOOL state)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".checked=" + (state ? "true" : "false"));
	RunJS(webView, str);

}

// 调用格式：_SDT_NULL 表单_Input单选框取选中状态 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：单选框取选中状态
BOOL CwkeTBInfo::form_Input_GetRadioChecked(wkeWebView webView, int model, const char* con, int index)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".checked");
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView,_str("return ") + str);
	return jsToBoolean(es, vl);
}

// 调用格式：_SDT_NULL 表单_Input单选框置选中状态 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_BOOL 选中状态)	详细介绍：单选框置选中状态,为真选中,为假取消选中 假
void CwkeTBInfo::form_Input_SetRadioChecked(wkeWebView webView, int model, const char* con, int index, BOOL state)
{
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".checked=" + (state ? "true" : "false"));
	RunJS(webView, str);
}

// 调用格式：_SDT_NULL 表单_Input_组合框取选中项 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：组合框置选中状态
int CwkeTBInfo::form_Input_GetComboxIndex(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str str(CreateElementSelectorStr(webView, model, con, index) + ".selectedIndex");
	jsValue vl = RunJS(webView,_str("return ") +  str);
	return jsToInt(es, vl);
}

// 调用格式：_SDT_NULL 表单_Input_组合框置选中状态 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_INT 选中项)	详细介绍：组合框置选中状态,为真选中,为假取消选中 假
void CwkeTBInfo::form_Input_SetComboxIndex(wkeWebView webView, int model, const char* con, int index, int selIndex)
{
	char strIndex[10] = { 0 };
	if (selIndex < 0)selIndex = 0;
	itoa(selIndex, strIndex, 10);
	_str str(CreateElementSelectorStr(webView, model, con, index) + "[" + strIndex + "].selected=true");
	RunJS(webView, str);
}

 // 调用格式：SDT_INT 表单_取表单数量 (SDT_INT WebView)	详细介绍：获取指定框架下的所有form表单个数,只有表单才会计数
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

 // 调用格式：SDT_INT 表单_取表单元素数量 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：获取指定表单下的所有表单元素个数,只有表单元素才会计数
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

// 调用格式：_SDT_NULL 表单_提交 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：提交指定表单,请注意如果提交不成功,请确认网页中没有屏蔽这个submit的过程
void CwkeTBInfo::form_Submit(wkeWebView webView, int model, const char* con, int index)
{
	_str js(260);
	js.assign(CreateElementSelectorStr(webView, model, con, index)).append(".submit()");
	RunJS(webView, js);
}


// 调用格式：_SDT_NULL 文档_置标题 (SDT_INT WebView, SDT_TEXT 标题)	详细介绍：通过JS设置网页文档标题
void CwkeTBInfo::doc_SetTitle(wkeWebView webView, _str title)
{
	_str js(260);
	js.assign("document.title=\"").append(title).append("\"");
	RunJS(webView, js);
}

// 调用格式：_SDT_NULL 文档_置缩放 (SDT_INT WebView, SDT_FLOAT 缩放阀值)	详细介绍：设置文档缩放
void CwkeTBInfo::doc_SetZoom(wkeWebView webView, float factor)
{
	wkeSetZoomFactor(webView, factor);
}

// 调用格式：SDT_FLOAT 文档_取缩放 (SDT_INT WebView)	详细介绍：取文档缩放阀值
float CwkeTBInfo::doc_GetZoom(wkeWebView webView)
{
	return wkeGetZoomFactor(webView);
}

// 调用格式：SDT_INT 文档_取文档区域宽度 (SDT_INT WebView)	详细介绍：文档_取文档区域宽度
int CwkeTBInfo::doc_GetWidth(wkeWebView webView)
{
	return wkeGetWidth(webView);
}

// 调用格式：SDT_INT 文档_取文档区域高度 (SDT_INT WebView)	详细介绍：文档_取文档区域高度
int CwkeTBInfo::doc_GetHeight(wkeWebView webView)
{
	return wkeGetHeight(webView);
}

// 调用格式：SDT_INT 文档_取Body区域宽度 (SDT_INT WebView)	详细介绍：文档_取Body区域宽度
int CwkeTBInfo::doc_GetBodyWidth(wkeWebView webView)
{
	return wkeGetContentWidth(webView);
}

// 调用格式：SDT_INT 文档_取Body区域高度 (SDT_INT WebView)	详细介绍：文档_取Body区域高度
int CwkeTBInfo::doc_GetBodyHeight(wkeWebView webView)
{
	return wkeGetContentHeight(webView);;
}

// 调用格式：SDT_INT 文档_取纵向滚动条位置 (SDT_INT WebView)	详细介绍：取纵向滚动条位置
int CwkeTBInfo::doc_GetScollY(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.body.scrollTop");
	return jsToInt(es, vl);
}

// 调用格式：_SDT_NULL 文档_置纵向滚动条位置 (SDT_INT WebView, SDT_INT 纵向位置)	详细介绍：设置纵向滚动条位置
void CwkeTBInfo::doc_SetScollY(wkeWebView webView, int pos)
{
	_str js(260);
	js.assign("document.body.scrollTop=").append(pos);
	RunJS(webView, js);
}

// 调用格式：_SDT_NULL 文档_取横向滚动条位置 (SDT_INT WebView)	详细介绍：取横向滚动条位置
int CwkeTBInfo::doc_GetScollX(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.body.scrollLeft");
	return jsToInt(es, vl);
}

// 调用格式：_SDT_NULL 文档_置横向滚动条位置 (SDT_INT WebView, SDT_INT 横向位置)	详细介绍：设置横向滚动条位置
void CwkeTBInfo::doc_SetScollX(wkeWebView webView, int pos)
{
	_str js(260);
	js.assign("document.body.scrollLeft=").append(pos);
	RunJS(webView, js);
}

// 调用格式：SDT_TEXT 文档_取编码 (SDT_INT WebView)	详细介绍：获取当前网页编码
_str CwkeTBInfo::doc_GetEncoding(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.charset");
	LPCSTR tmp = jsToString(es, vl);
	return tmp;
}

// 调用格式：SDT_TEXT 文档_取根域名 (SDT_INT WebView)	详细介绍：wke_获取网页根域名
_str CwkeTBInfo::doc_GetDomain(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.domain");
	LPCSTR tmp = jsToString(es, vl);
	_str str(tmp);
	str.Addref();
	return str;
}

// 调用格式：SDT_TEXT 文档_取选中文本 (SDT_INT WebView)	详细介绍：获取当前选中的文本
_str CwkeTBInfo::doc_GetSelectText(wkeWebView webView)
{
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, "return document.getSelection().toString()");
	LPCSTR tmp = jsToString(es, vl);
	return tmp;
}

// 调用格式：SDT_TEXT 文档_取元素内容 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：取指定元素内容 innerHTML
_str CwkeTBInfo::doc_GetElementHTML(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".innerHTML");
	jsValue vl = RunJS(webView, js);
	LPCSTR tmp = jsToString(es, vl);
	return tmp;
}

// 调用格式：_SDT_NULL 文档_进入编辑模式 (SDT_INT WebView, SDT_BOOL 是否开启编辑状态)	详细介绍：进入编辑模式
void CwkeTBInfo::doc_EnableEditModel(wkeWebView webView, bool editable)
{
	wkeSetEditable(webView, editable);
}

// 调用格式：_SDT_NULL 文档_复制 (SDT_INT WebView)	详细介绍：编辑模式复制
void CwkeTBInfo::doc_EditCopy(wkeWebView webView)
{
	wkeEditorCopy(webView);
}

// 调用格式：_SDT_NULL 文档_剪切 (SDT_INT WebView)	详细介绍：编辑模式剪切
void CwkeTBInfo::doc_EditCut(wkeWebView webView)
{
	wkeEditorCut(webView);
}

// 调用格式：_SDT_NULL 文档_粘贴 (SDT_INT WebView)	详细介绍：编辑模式粘贴
void CwkeTBInfo::doc_EditPaste(wkeWebView webView)
{
	wkeEditorPaste(webView);
}

// 调用格式：_SDT_NULL 文档_撤销 (SDT_INT WebView)	详细介绍：编辑模式撤销
void CwkeTBInfo::doc_EditPaste1(wkeWebView webView)
{
	wkeEditorUndo(webView);
}

// 调用格式：_SDT_NULL 文档_全选 (SDT_INT WebView)	详细介绍：编辑模式全选
void CwkeTBInfo::doc_SelectedAll(wkeWebView webView)
{
	wkeEditorSelectAll(webView);
}

// 调用格式：_SDT_NULL 文档_取消全选 (SDT_INT WebView)	详细介绍：编辑模式取消全选
void CwkeTBInfo::doc_CancelSelect(wkeWebView webView)
{
	wkeEditorUnSelect(webView);
}

// 调用格式：_SDT_NULL 文档_重置 (SDT_INT WebView)	详细介绍：编辑模式重置
void CwkeTBInfo::doc_EditRedo(wkeWebView webView)
{
	wkeEditorRedo(webView);
}

// 调用格式：_SDT_NULL 文档_标记所有连接 (SDT_INT webView, SDT_INT frameid)	详细介绍：标记所有连接
void CwkeTBInfo::doc_MarkerAllLinks(wkeWebView webView, wkeWebFrameHandle frameID)
{
	const wchar_t js[] = L"var dom = new Array();\
dom=document.getElementsByTagName(\"a\");\
for (var i=0;i<dom.length;i++)\
{\
var Mess=dom[i].innerHTML;\
if (Mess.indexOf(\">链\")==-1)\
  {\
  dom[i].innerHTML=Mess+\"_<font color=red>链\" +i+ \"</font>\";\
  }\
}";
	_str str = wstr::W2U(js);
	wkeRunJsByFrame(webView, frameID, str.c_str(), TRUE);
}

// 调用格式：_SDT_NULL 文档_标记所有文本框 (SDT_INT webView, SDT_INT frameid)	详细介绍：标记所有文本框
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
  dom[i].value=\"文本框\"+X;\
  }\
}";
	_str str = wstr::W2U(js);
	wkeRunJsByFrame(webView, frameID, str.c_str(), TRUE);
}

// 调用格式：_SDT_NULL 文档_标记所有按钮 (SDT_INT webView, SDT_INT frameid)	详细介绍：标记所有按钮
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
  dom[i].value=\"按钮\"+X;\
  }\
}\
var dom = new Array();\
dom=document.getElementsByTagName(\"button\");\
var i=0;\
for (var i=0;i<dom.length;i++)\
{\
  X=X+1;\
  dom[i].value=\"按钮\"+X;\
}";
	_str str = wstr::W2U(js);
	wkeRunJsByFrame(webView, frameID, str.c_str(), TRUE);
}

// 调用格式：SDT_BOOL 文档_Jquery是否已加载 (SDT_INT webView)	详细介绍：文档_Jquery是否已加载
BOOL CwkeTBInfo::doc_JqueryIsLoding(wkeWebView webView)
{
	wchar_t* src = L"src = “try{ if( $ || Jquery ) return 'fn.init'; if(jQuery) $=jQuery; return jQuery; }catch(err){ return 'err'; }”";
	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, src);
	_str str = wstr::W2A(jsToStringW(es, vl));
	
	BOOL bRet = _str::find(str.c_str(), "fn.init") > -1;
	return bRet;
}

// 调用格式：SDT_TEXT 文档_执行JS方法 (SDT_INT webView, SDT_TEXT 方法名称)	详细介绍：调用
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

// 调用格式：SDT_TEXT 文档_取图片地址 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：文档_图片取地址
_str CwkeTBInfo::doc_GetImageElemSrc(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('src')");
	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

// 调用格式：SDT_TEXT 文档_取链接地址 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：文档_链接取地址
_str CwkeTBInfo::doc_GetLinkhref(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('href')");

	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

 // 调用格式：_SDT_NULL 元素点击 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：元素点击
void CwkeTBInfo::elem_Click(wkeWebView webView, int model, const char* con, int index)
{
	_str js(260);
	js.assign(CreateElementSelectorStr(webView, model, con, index)).append(".click()");
	RunJS(webView, js);
}

// 调用格式：_SDT_NULL 元素置焦点 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：元素置焦点
void CwkeTBInfo::elem_SetFouce(wkeWebView webView, int model, const char* con, int index)
{
	wkeSetFocus(webView);
	RunJS(webView, CreateElementSelectorStr(webView, model, con, index) + ".focus()");
}

// 调用格式：SDT_TEXT 取元素属性值 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_TEXT 属性名称)	详细介绍：取指定元素属性的置
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

// 调用格式：_SDT_NULL 置元素属性值 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_TEXT 属性名称, SDT_TEXT 属性值)	详细介绍：设置指定元素的值
void CwkeTBInfo::elem_SetAttribute(wkeWebView webView, int model, const char* con, int index, char* name, char* value)
{
	_str js(CreateElementSelectorStr(webView, model, con, index));
	_str s(520);
	s.assign(js).append(".setAttribute('").append(name).append("','").append(value).append("')");
	RunJS(webView, s);
	s.assign(js).append(".").append(name).append("='").append(value).append('\'');
	RunJS(webView, s);

}

// 调用格式：SDT_TEXT 元素_取标题 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：获取元素的title属性值
_str CwkeTBInfo::elem_GetTitle(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".title");
	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

 // 调用格式：SDT_TEXT 元素_取内联样式 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：元素_取内联样式
_str CwkeTBInfo::elem_GetStyleStr(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('style')");
	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

// 调用格式：SDT_TEXT 元素_取类名列表 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：元素_取类名列表
_str CwkeTBInfo::elem_GetClassList(wkeWebView webView, int model, const char* con, int index)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index)).append(".getAttribute('class')");
	jsValue vl = RunJS(webView, js);
	_str sRet = jsToString(es, vl);
	return sRet;
}

// 调用格式：_SDT_NULL 元素_闪烁标记 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：标记指定元素
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

// 调用格式：_SDT_NULL 元素_置可视状态 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标)	详细介绍：设置元素可见状态
void CwkeTBInfo::elem_SetentVisableState(wkeWebView webView, int model, const char* con, int index, BOOL isVisible)
{
	jsExecState es = wkeGlobalExec(webView);
	_str js(260);
	js.append(CreateElementSelectorStr(webView, model, con, index));
	js.append(isVisible ? ".style.display='block'" : ".style.display='none'");

	RunJS(webView, js);
}

// 调用格式：SDT_INT 元素_取横坐标 (SDT_INT webView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 偏移, SDT_INT 下标)	详细介绍：取元素横坐标
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

// 调用格式：SDT_INT 元素_取纵坐标 (SDT_INT webView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 偏移, SDT_INT 下标)	详细介绍：取元素纵坐标
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

// 调用格式：6 元素_取矩形信息 (SDT_INT webView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 下标)	详细介绍：取元素矩形,元素的矩形信息 左边 右边 顶边 底边 宽 高
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

// 调用格式：_SDT_NULL 元素_触发指定事件 (SDT_INT webView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 下标, SDT_TEXT 事件名称, SDT_BOOL 关闭事件冒泡, SDT_TEXT 事件参数)	详细介绍：触发指定元素的指定事件,可以传递事件参数
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

// 元素_取子元素数量
int CwkeTBInfo::elem_GetCount(wkeWebView webView, int model, const char* con, int index)
{
	_str js(260);
	js.assign("return ").append(CreateElementSelectorStr(webView, model, con, index));
	js.append(".childElementCount");

	jsExecState es = wkeGlobalExec(webView);
	jsValue vl = RunJS(webView, js);
	return jsToInt(es, vl);
}
