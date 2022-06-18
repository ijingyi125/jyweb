#pragma once
#include "pch.h"
#include "wke/wke.h"
#include "wke/MbE.h"


#define MODEL_JY	1	//填表模式 = 精易
#define MODEL_JS	2	//填表模式 = js表达式

//CwkeTBInfo.h 填表方法的声明
class CwkeTBInfo
{
public:
	CwkeTBInfo();
	CwkeTBInfo(const CwkeTBInfo& obj);
	~CwkeTBInfo();
	_str m_frameStr;
	int m_framex, m_framey;

public:
	//_str RpSubText(_str& str, const _str& old_value, const _str& new_value, int num);
	_str InnerHtmlSelector(const char* con);
	_str CreateElementSelectorStr(wkeWebView webView, int model, const char* con, int index);
	_str CreateFrameCodeStr(wkeWebView webView, int model, const char* con, int index);
	jsValue RunJS(wkeWebView webView, const char* js);
	jsValue RunJS(wkeWebView webView, const wchar_t* js);
	jsValue RunJS(wkeWebView webView, const _str& js);
	jsValue RunJS(wkeWebView webView, const wstr& js);
	void clear();
	CwkeTBInfo& assign(const CwkeTBInfo& obj);
	CwkeTBInfo& assign(const CwkeTBInfo* obj);
	int GetFrameX(wkeWebView webView, const char* con);
	int GetFrameY(wkeWebView webView, const char* con);
public:
	//表单_ 相关方法

	void	form_SetFrame(wkeWebView webView, int model, const char* con, int index);
	int 	form_GetFrameCount(wkeWebView webView);

	void 	form_Input_Click(wkeWebView webView, int model, const char* con, int index);
	_str 	form_Input_ReadAttrValue(wkeWebView webView, int model, const char* con, int index, char* name);
	void 	form_Input_WriteAttrVal(wkeWebView webView, int model, const char* con, int index, char* name, char* value);
	void 	form_Input_RemoveAttrValue(wkeWebView webView, int model, const char* con, int index,char* name);
	BOOL	form_Input_GetCheckBoxState(wkeWebView webView, int model, const char* con, int index);
	void 	form_Input_SetCheckBoxState(wkeWebView webView, int model, const char* con, int index, BOOL state);
	BOOL 	form_Input_GetRadioChecked(wkeWebView webView, int model, const char* con, int index);
	void 	form_Input_SetRadioChecked(wkeWebView webView, int model, const char* con, int index, BOOL state);
	int 	form_Input_GetComboxIndex(wkeWebView webView, int model, const char* con, int index);
	void 	form_Input_SetComboxIndex(wkeWebView webView, int model, const char* con, int index, int selIndex);
	
	int 	form_GetSubCount(wkeWebView webView, int model, const char* con, int index);
	int		form_GetFormCount(wkeWebView webView);
	void	form_Submit(wkeWebView webView, int model, const char* con, int index);


public:
	//文档_ 相关方法

	void	doc_SetTitle(wkeWebView webView, _str title);
	void	doc_SetZoom(wkeWebView webView, float factor);
	float	doc_GetZoom(wkeWebView webView);
	int		doc_GetWidth(wkeWebView webView);
	int 	doc_GetHeight(wkeWebView webView);
	int 	doc_GetBodyWidth(wkeWebView webView);
	int 	doc_GetBodyHeight(wkeWebView webView);
	int 	doc_GetScollY(wkeWebView webView);
	void	doc_SetScollY(wkeWebView webView, int pos);
	int		doc_GetScollX(wkeWebView webView);
	void	doc_SetScollX(wkeWebView webView, int pos);
	_str	doc_GetEncoding(wkeWebView webView);
	_str	doc_GetDomain(wkeWebView webView);
	_str	doc_GetSelectText(wkeWebView webView);
	_str	doc_GetElementHTML(wkeWebView webView, int model, const char* con, int index);
	void	doc_EnableEditModel(wkeWebView webView, bool editable);
	void	doc_EditCopy(wkeWebView webView);
	void	doc_EditCut(wkeWebView webView);
	void	doc_EditPaste(wkeWebView webView);
	void	doc_EditPaste1(wkeWebView webView);
	void	doc_SelectedAll(wkeWebView webView);
	void	doc_CancelSelect(wkeWebView webView);
	void	doc_EditRedo(wkeWebView webView);
	void	doc_MarkerAllLinks(wkeWebView webView, wkeWebFrameHandle frameID);
	void	doc_MarkerAllInputText(wkeWebView webView, wkeWebFrameHandle frameID);
	void	doc_MarkerAllButton(wkeWebView webView, wkeWebFrameHandle frameID);
	BOOL	doc_JqueryIsLoding(wkeWebView webView);
	_str	doc_JSCall(wkeWebView webView, _str name);
	_str	doc_GetImageElemSrc(wkeWebView webView, int model, const char* con, int index);
	_str	doc_GetLinkhref(wkeWebView webView, int model, const char* con, int index);

public:
	//元素_ 相关方法
	void	elem_Click(wkeWebView webView, int model, const char* con, int index);
	void	elem_SetFouce(wkeWebView webView, int model, const char* con, int index);
	_str	elem_GetAttribute(wkeWebView webView, int model, const char* con, int index, char* name);
	void	elem_SetAttribute(wkeWebView webView, int model, const char* con, int index, char* name, char* value);

	_str	elem_GetTitle(wkeWebView webView, int model, const char* con, int index);
	_str	elem_GetStyleStr(wkeWebView webView, int model, const char* con, int index);
	_str	elem_GetClassList(wkeWebView webView, int model, const char* con, int index);
	void	elem_SetentFlag(wkeWebView webView, int model, const char* con, int index);
	void	elem_SetentVisableState(wkeWebView webView, int model, const char* con, int index, BOOL isVisible);
	int		elem_GetentPointX(wkeWebView webView, int model, const char* con, int offsetX, int index);
	int 	elem_GetentPointY(wkeWebView webView, int model, const char* con, int offsetY, int index);
	RECT	elem_GetentRect(wkeWebView webView, int model, const char* con, int index);
	void	elem_CallEvent(wkeWebView webView, int model, const char* con, int index, char* eventName, BOOL bubbles, char* eventArg);
	int		elem_GetCount(wkeWebView webView, int model, const char* con, int index);

};

