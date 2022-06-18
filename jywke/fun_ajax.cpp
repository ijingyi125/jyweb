#include "wke_typedef.h"
#include "WKECtrl.h"
#include "Cajax.h"

// ajax相关命令实现文件


// 调用格式: _SDT_NULL (Ajax).Ajax初始化, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(21, AJAXIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	*pArgInf->m_ppCompoundData = new Cajax;
}

// 调用格式: _SDT_NULL (Ajax).Ajax赋值, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(22, AJAXCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
}

// 调用格式: _SDT_NULL (Ajax).AJAX销毁, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(23, AJAXDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	Cajax* ajax = (Cajax*)* pArgInf->m_ppCompoundData;
	if (ajax)delete ajax;
	*pArgInf->m_ppCompoundData = NULL;
}

// 调用格式: _SDT_NULL (Ajax).设置Http请求头, 命令说明: "设置Http请求头,在调用Get或Post方法后请求头将被清空。"
// 参数<1>: Key SDT_TEXT, 参数说明: "http请求头字段名称,如 Content-Type UserAgent Referer 等等"
// 参数<2>: Value SDT_TEXT, 参数说明: "http请求头字段对应的值"
EXTERN_C void WKE_NAME(24, SetHttpHeader)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    Cajax* ajax = (Cajax*)*pArgInf->m_ppCompoundData;
	if (ajax)
		ajax->SetHttpHeader(pArgInf[1].m_pText, pArgInf[2].m_pText);
}

// 调用格式: _SDT_NULL (Ajax).GET请求, 命令说明: "向网页内注入ajax脚本方法实现Get请求。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: url SDT_TEXT, 参数说明: "请求的URL"
// 参数<3>: 回调方法 SDT_SUB_PTR, 参数说明: "当Ajax与服务器交互完成将调用此方法,成功返回服务器返回文本,错误返回状态码"
EXTERN_C void WKE_NAME(25, AjaxGet)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    Cajax* ajax = (Cajax*)*pArgInf->m_ppCompoundData;
	if (ajax)
		ajax->Get((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText, (ajax_userFunc)pArgInf[3].m_dwSubCodeAdr);
}

// 调用格式: _SDT_NULL (Ajax).POST请求, 命令说明: "向网页内注入ajax脚本方法实现Post请求。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: url SDT_TEXT, 参数说明: "请求的URL"
// 参数<3>: 是否是JSON SDT_BOOL, 参数说明: "提交的数据格式是否是JSON"
// 参数<4>: 提交数据 SDT_TEXT, 参数说明: "要提交的POST数据"
// 参数<5>: 回调方法 SDT_SUB_PTR, 参数说明: "当Ajax与服务器交互完成将调用此方法,成功返回服务器返回文本,错误返回状态码"
EXTERN_C void WKE_NAME(26, AjaxPost)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    Cajax* ajax = (Cajax*)*pArgInf->m_ppCompoundData;
	if (ajax)
		ajax->Post((wkeWebView)pArgInf[1].m_int, pArgInf[2].m_pText, pArgInf[3].m_bool, pArgInf[4].m_pText, (ajax_userFunc)pArgInf[5].m_dwSubCodeAdr);
}




