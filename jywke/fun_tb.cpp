#include "wke_typedef.h"
#include "WKECtrl.h"
#include "CwkeTBInfo.h"

// 填表相关命令实现文件


CwkeTBInfo* GetTBjsFromArginf_wke(PMDATA_INF pArgInf)
{
	return (CwkeTBInfo*)* pArgInf[0].m_ppCompoundData;
}
#define WKE_TB CwkeTBInfo* js=0; if(!pArgInf[0].m_ppCompoundData) return; js = (CwkeTBInfo*) (*pArgInf[0].m_ppCompoundData); if(!js) return


// 调用格式: _SDT_NULL (WKE_填表).填表初始化, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(61, TBIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	//*pArgInf[0].m_ppCompoundData = (void*)100;
	*pArgInf[0].m_ppCompoundData = new CwkeTBInfo;
	return;
	//int a = (int)*pArgInf[0].m_ppCompoundData;
	//CwkeTBInfo* js = new CwkeTBInfo;
	//g_wke.insert(a, (void*)js);
}

// 调用格式: _SDT_NULL (WKE_填表).填表赋值, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(62, TBCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	//假设在易中A=B,pArgInf[0]是A
	//CwkeTBInfo* pA= (CwkeTBInfo*)*pArgInf[0].m_ppCompoundData;  
	//CwkeTBInfo* pB= (CwkeTBInfo*)*pArgInf[1].m_ppCompoundData;  
	////绝对不能直接把B指针赋值给A
	//_str s = pB->m_frameStr;
	//_str s2 = pB->m_frameStr;
	//pA->m_frameStr.resize(0);
	////pA->m_frameStr.assign(s);
	//pA->m_framex = pB->m_framex;
	//pA->m_framey = pB->m_framey;

}

// 调用格式: _SDT_NULL (WKE_填表).填表销毁, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(63, TBDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	WKE_TB;
	if (js)delete js;
	*pArgInf[0].m_ppCompoundData = NULL;

}

// 调用格式: _SDT_NULL (WKE_填表).元素点击, 命令说明: "元素点击。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(64, wke_ElementClick)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_Click((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);

}

// 调用格式: _SDT_NULL (WKE_填表).元素置焦点, 命令说明: "元素置焦点。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(65, wke_SetElementFouce)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_SetFouce((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// 调用格式: SDT_TEXT (WKE_填表).取元素属性值, 命令说明: "取指定元素属性的置。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 属性名称 SDT_TEXT, 参数说明: "需要获取属性值的名称 如: name"
EXTERN_C void WKE_NAME(66, wke_GetAttribute)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->elem_GetAttribute((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: _SDT_NULL (WKE_填表).置元素属性值, 命令说明: "设置指定元素的值。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 属性名称 SDT_TEXT, 参数说明: "需要获取属性值的名称 如: name"
// 参数<6>: 属性值 SDT_TEXT, 参数说明: "需要获取属性值的名称 如: name"
EXTERN_C void WKE_NAME(67, wke_SetAttribute)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_SetAttribute((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText, pArgInf[6].m_pText);
}

// 调用格式: _SDT_NULL (WKE_填表).表单_置填表框架, 命令说明: "设置框架以后,所有的 表单_ 填表操作都是在这个框架内部进行,索引小于1,表示清除当前选择框架"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(68, Form_SetFrame)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_SetFrame((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// 调用格式: SDT_INT (WKE_填表).表单_取当前框架数量, 命令说明: "获取当前网页中框架(iframe)的数量。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(69, Form_GetFrameCount)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->form_GetFrameCount((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).表单_Input点击, 命令说明: "取指定元素属性的值。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(70, wke_Input_Click)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_Click((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// 调用格式: SDT_TEXT (WKE_填表).表单_Input读属性, 命令说明: "读取表单中指定input元素的属性值。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 属性名称 SDT_TEXT, 参数说明: "需要获取属性值的名称 如: name"
EXTERN_C void WKE_NAME(71, wke_Input_ReadAttrValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->form_Input_ReadAttrValue((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: _SDT_NULL (WKE_填表).表单_Input写属性, 命令说明: "向指定INPUT元素写入属性值,如果属性存在则更新该属性的值,不存在则增加一个属性。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 属性名称 SDT_TEXT, 参数说明: "需要获取属性值的名称 如: name"
// 参数<6>: 属性值 SDT_TEXT, 参数说明: "需要获取属性值的名称 如: name"
EXTERN_C void WKE_NAME(72, wke_Input_WriteAttrVal)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_WriteAttrVal((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText, pArgInf[6].m_pText);
}

// 调用格式: _SDT_NULL (WKE_填表).表单_Input移除属性, 命令说明: "移除指定表单元素中的指定属性。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 属性名称 SDT_TEXT, 参数说明: "需要获取属性值的名称 如: name"
EXTERN_C void WKE_NAME(73, wke_Input_RemoveAttrValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_RemoveAttrValue((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_pText);

}

// 调用格式: _SDT_NULL (WKE_填表).表单_Input选择框置选中状态, 命令说明: "表单_Input选择框置选中状态,为真选中,为假取消选中 假。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 选中状态 SDT_BOOL, 参数说明: "设置为真代表选中该选择框,为假则取消选中"
EXTERN_C void WKE_NAME(74, wke_Input_SetCheckBoxState)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_SetCheckBoxState((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_int);

}

// 调用格式: _SDT_NULL (WKE_填表).表单_Input单选框置选中状态, 命令说明: "单选框置选中状态,为真选中,为假取消选中 假。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 选中状态 SDT_BOOL, 参数说明: "设置为真代表选中该选择框,为假则取消选中"
EXTERN_C void WKE_NAME(75, wke_Input_SetRadioChecked)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Input_SetCheckBoxState((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_bool);
}


// 调用格式: _SDT_NULL (WKE_填表).表单_Input组合框置选中项, 命令说明: "组合框置选中状态,为真选中,为假取消选中 假。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 选中项 SDT_INT, 参数说明: "选中组合框中的第几项,序号从0开始"
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


// 调用格式: SDT_INT (WKE_填表).表单_取表单元素数量, 命令说明: "获取指定表单下的所有表单元素个数,只有表单元素才会计数。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(77, Form_GetSubCount)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->form_GetSubCount((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).表单_提交, 命令说明: "提交指定表单,请注意如果提交不成功,请确认网页中没有屏蔽这个submit的过程。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(78, Form_Submit)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->form_Submit((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_置标题, 命令说明: "通过JS设置网页文档标题。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 标题 SDT_TEXT, 参数说明: "标题"
EXTERN_C void WKE_NAME(79, wke_DocSetTitle)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_SetTitle((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_置缩放, 命令说明: "设置文档缩放。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 缩放阀值 SDT_FLOAT, 参数说明: "缩放阀值"
EXTERN_C void WKE_NAME(80, wke_DocSetZoom)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_SetZoom((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_float);
}

// 调用格式: SDT_FLOAT (WKE_填表).文档_取缩放, 命令说明: "取文档缩放阀值。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(81, wke_DocGetZoom)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_float = js->doc_GetZoom((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: SDT_INT (WKE_填表).文档_取文档区域宽度, 命令说明: "文档_取文档区域宽度。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(82, wke_DocGetWidth)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetWidth((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: SDT_INT (WKE_填表).文档_取文档区域高度, 命令说明: "文档_取文档区域高度。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(83, wke_DocGetHeight)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetHeight((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: SDT_INT (WKE_填表).文档_取Body区域宽度, 命令说明: "文档_取Body区域宽度。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(84, wke_DocGetBodyWidth)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetBodyWidth((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: SDT_INT (WKE_填表).文档_取Body区域高度, 命令说明: "文档_取Body区域高度。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(85, wke_DocGetBodyHeight)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetBodyHeight((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: SDT_INT (WKE_填表).文档_取纵向滚动条位置, 命令说明: "取纵向滚动条位置。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(86, wke_DocGetScollY)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->doc_GetScollY((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_置纵向滚动条位置, 命令说明: "设置纵向滚动条位置。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 纵向位置 SDT_INT, 参数说明: "设置纵向滚动条位置"
EXTERN_C void WKE_NAME(87, wke_DocSetScollY)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_SetScollY((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int);
}


// 调用格式: _SDT_NULL (WKE_填表).文档_置横向滚动条位置, 命令说明: "设置横向滚动条位置。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 横向位置 SDT_INT, 参数说明: "设置横向滚动条位置"
EXTERN_C void WKE_NAME(88, wke_DocSetScollX)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_SetScollX((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int);
}

// 调用格式: SDT_TEXT (WKE_填表).文档_取编码, 命令说明: "获取当前网页编码。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(89, wke_DocGetEncoding)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetEncoding((wkeWebView)pArgInf[1].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_TEXT (WKE_填表).文档_取根域名, 命令说明: "wke_获取网页根域名。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(90, DocGetDomain)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetDomain((wkeWebView)pArgInf[1].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_TEXT (WKE_填表).文档_取选中文本, 命令说明: "获取当前选中的文本。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(91, wke_DocGetSelectText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetSelectText((wkeWebView)pArgInf[1].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_TEXT (WKE_填表).文档_取元素内容, 命令说明: "取指定元素内容 innerHTML。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(92, GetElementHTML)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetElementHTML((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: _SDT_NULL (WKE_填表).文档_进入编辑模式, 命令说明: "进入编辑模式。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 是否开启编辑状态 SDT_BOOL, 参数说明: "为真则打开编辑模式 为假则关闭"
EXTERN_C void WKE_NAME(93, wke_DocEnableEditModel)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EnableEditModel((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_bool);

}

// 调用格式: _SDT_NULL (WKE_填表).文档_复制, 命令说明: "编辑模式复制。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(94, DocEditCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditCopy((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_剪切, 命令说明: "编辑模式剪切。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(95, DocEditCut)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditCut((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_粘贴, 命令说明: "编辑模式粘贴。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(96, DocEditPaste)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditPaste((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_撤销, 命令说明: "编辑模式撤销。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(97, DocEditPaste)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditPaste1((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_全选, 命令说明: "编辑模式全选。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(98, DocSelectedAll)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	WKE_TB;
	js->doc_SelectedAll((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_取消全选, 命令说明: "编辑模式取消全选。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(99, DocCancelSelect)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_CancelSelect((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_重置, 命令说明: "编辑模式重置。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(100, DocEditRedo)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_EditRedo((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_标记所有连接, 命令说明: "标记所有连接。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: frameid SDT_INT, 参数说明: "框架ID , 1是当前网页主框架"
EXTERN_C void WKE_NAME(101, wke_MarkerAllLinks)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;

	js->doc_MarkerAllLinks((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_标记所有文本框, 命令说明: "标记所有文本框。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: frameid SDT_INT, 参数说明: "框架ID , 1是当前网页主框架"
EXTERN_C void WKE_NAME(102, wke_MarkerAllInputText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_MarkerAllInputText((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).文档_标记所有按钮, 命令说明: "标记所有按钮。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: frameid SDT_INT, 参数说明: "框架ID , 1是当前网页主框架"
EXTERN_C void WKE_NAME(103, wke_MarkerAllButton)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->doc_MarkerAllButton((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int);
}

// 调用格式: SDT_BOOL (WKE_填表).文档_Jquery是否已加载, 命令说明: "文档_Jquery是否已加载。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(104, wke_JqueryIsLoding)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_bool = js->doc_JqueryIsLoding((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: SDT_TEXT (WKE_填表).文档_执行JS方法, 命令说明: "调用。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 方法名称 SDT_TEXT, 参数说明: "比如 getContent() setContent('content') 或 sc.getContent('aaaa')"
EXTERN_C void WKE_NAME(105, JSCall)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_JSCall((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText);
	//if (pRetData->m_pText != NULL)
		//delete[](pRetData->m_pText);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_TEXT (WKE_填表).文档_取图片地址, 命令说明: "文档_图片取地址。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(106, wke_GetImageElemSrc)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetImageElemSrc((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_TEXT (WKE_填表).文档_取链接地址, 命令说明: "文档_链接取地址。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(107, wke_GetLinkhref)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->doc_GetLinkhref((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_TEXT (WKE_填表).元素_取标题, 命令说明: "获取元素的title属性值。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(108, wke_GetElemTitle)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->elem_GetTitle((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_TEXT (WKE_填表).元素_取内联样式, 命令说明: "元素_取内联样式。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(109, wke_GetElemStyleStr)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->elem_GetStyleStr((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_TEXT (WKE_填表).元素_取类名列表, 命令说明: "元素_取类名列表。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(110, wke_GetClassList)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	_str str = js->elem_GetClassList((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
	pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: _SDT_NULL (WKE_填表).元素_闪烁标记, 命令说明: "标记指定元素。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(111, wke_SetElementFlag)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_SetentFlag((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
}

// 调用格式: _SDT_NULL (WKE_填表).元素_置可视状态, 命令说明: "设置元素可见状态。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: 元素下标 SDT_INT, 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
// 参数<5>: 是否可视 SDT_BOOL, 参数说明: "真=可视,假=不可视"
EXTERN_C void WKE_NAME(112, wke_SetElementVisableState)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	js->elem_SetentVisableState((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_bool);
}

// 调用格式: SDT_INT (WKE_填表).元素_取横坐标, 命令说明: "取元素横坐标。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: 偏移 SDT_INT, 参数说明: "方法会计算元素所有父级的横坐标叠加,但鼠标模拟操作可能会对元素范围内不同的点进行操作.用以达到更好的模拟效果"
// 参数<5>: [下标 SDT_INT], 参数说明: "如果返回的元素大于1个,可以使用该下标指定元素下标 ,如使用这个选择器 div.myclass>ul>li  则会返回类型名为 myclass 的DIV下的UL下的li集合 ,此处就可以指定取第几个LI,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(113, wke_GetElementPointX)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->elem_GetentPointX((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_int);
}

// 调用格式: SDT_INT (WKE_填表).元素_取纵坐标, 命令说明: "取元素纵坐标。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: 偏移 SDT_INT, 参数说明: "方法会计算元素所有父级的横坐标叠加,但鼠标模拟操作可能会对元素范围内不同的点进行操作.用以达到更好的模拟效果"
// 参数<5>: [下标 SDT_INT], 参数说明: "如果返回的元素大于1个,可以使用该下标指定元素下标 ,如使用这个选择器 div.myclass>ul>li  则会返回类型名为 myclass 的DIV下的UL下的li集合 ,此处就可以指定取第几个LI,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(114, wke_GetElementPointY)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
	pRetData->m_int = js->elem_GetentPointY((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_int);
}

// 调用格式: MAKELONG(0x06, 0) (WKE_填表).元素_取矩形信息, 命令说明: "取元素矩形,元素的矩形信息 左边 右边 顶边 底边 宽 高。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
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


// 调用格式: _SDT_NULL (WKE_填表).元素_触发指定事件, 命令说明: "触发指定元素的指定事件,可以传递事件参数。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [下标 SDT_INT], 参数说明: "如果返回的元素大于1个,可以使用该下标指定元素下标 ,如使用这个选择器 div.myclass>ul>li  则会返回类型名为 myclass 的DIV下的UL下的li集合 ,此处就可以指定取第几个LI,下标从1开始,默认为1"
// 参数<5>: 事件名称 SDT_TEXT, 参数说明: "请使用 #事件_ 开头的常量"
// 参数<6>: 关闭事件冒泡 SDT_BOOL, 参数说明: "关闭冒泡请设置为 真"
// 参数<7>: [事件参数 SDT_TEXT], 参数说明: "可以触发时间时传递事件对象参数,可为空"
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


// 调用格式: SDT_INT (WKE_填表).文档_取横向滚动条位置, 命令说明: "获取横向滚动条位置。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(162, wke_DocGetScollX)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    pRetData->m_int = js->doc_GetScollX((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: SDT_BOOL (WKE_填表).表单_Input选择框取选中状态, 命令说明: "取选择框选中状态。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(163, wke_Input_GetCheckBoxState)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    INT      arg1 = pArgInf[1].m_int;
    INT      arg2 = pArgInf[2].m_int;
    LPSTR    arg3 = pArgInf[3].m_pText;
    INT      arg4 = pArgInf[4].m_int;
    pRetData->m_int = js->form_Input_GetCheckBoxState((wkeWebView)pArgInf[1].m_int, arg2, arg3, arg4);
}

// 调用格式: SDT_BOOL (WKE_填表).表单_Input单选框取选中状态, 命令说明: "取单选框选中状态。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(164, wke_Input_GetRadioChecked)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    INT      arg1 = pArgInf[1].m_int;
    INT      arg2 = pArgInf[2].m_int;
    LPSTR    arg3 = pArgInf[3].m_pText;
    INT      arg4 = pArgInf[4].m_int;
    pRetData->m_int = js->form_Input_GetRadioChecked((wkeWebView)pArgInf[1].m_int, arg2, arg3, arg4);
}

// 调用格式: SDT_INT (WKE_填表).表单_Input组合框取选中项, 命令说明: "取组合框选中项索引。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(165, wke_Input_GetComboxIndex)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    pRetData->m_int = js->form_Input_GetComboxIndex((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);

}

// 调用格式: SDT_INT (WKE_填表).表单_取表单数量, 命令说明: "获取指定框架下的所有form表单个数,只有表单才会计数。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(169, wke_GetFormLength)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    pRetData->m_int = js->form_GetFormCount((wkeWebView)pArgInf[1].m_int);
}

// 调用格式: SDT_INT (WKE_填表).元素_取子元素数量, 命令说明: "取指定元素的子元素数量"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 填表模式 SDT_INT, 参数说明: "请使用 #填表模式_ 开头的常量,具体看常量说明"
// 参数<3>: 选择表达式 SDT_TEXT, 参数说明: "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active"
// 参数<4>: [元素下标 SDT_INT], 参数说明: "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1"
EXTERN_C void WKE_NAME(181, GetElementCount)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    int r = js->elem_GetCount((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int);
    pRetData->m_int = r;
}

// 调用格式: _SDT_NULL (WKE_填表).赋值, 命令说明: "把另一个 WKE_填表 内部的数据赋值到当前 WKE_填表 里"
// 参数<1>: WKE_TB MAKELONG(0x01, 0), 参数说明: "另一个WKE_填表 变量"
EXTERN_C void WKE_NAME(194, wke_assign)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    if ( !pArgInf[1].m_ppCompoundData )return;
    CwkeTBInfo* p = (CwkeTBInfo*)( *pArgInf[1].m_ppCompoundData );
    if ( !p )return;
    js->assign(p);
}

// 调用格式: _SDT_NULL (WKE_填表).清空, 命令说明: "清空当前 WKE_填表内的数据"
// 无参数
EXTERN_C void WKE_NAME(195, wke_clear)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    WKE_TB;
    js->clear();
}

// 调用格式: _SDT_NULL (WKE_填表).取编辑框游标位置, 命令说明: "获取编辑框的那个游标的位置"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(199, wke_GetCaretRect)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeWebView webView = (wkeWebView)pArgInf[1].m_int;
    if ( !webView )return;
    wkeGetCaretRect(webView);
}





















DEF_EXECUTE_CMD(wke_Input_SetRadioChecked)
{
    // 调用格式：_SDT_NULL 表单_Input单选框置选中状态 (SDT_INT WebView, SDT_INT 填表模式, SDT_TEXT 选择表达式, SDT_INT 元素下标, SDT_BOOL 选中状态)	
    //详细介绍：单选框置选中状态,为真选中,为假取消选中 假
    WKE_TB;
    js->form_Input_SetRadioChecked((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_int, pArgInf[3].m_pText, pArgInf[4].m_int, pArgInf[5].m_bool);
}














