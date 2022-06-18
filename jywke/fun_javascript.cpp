#include "wke_typedef.h"
#include "WKECtrl.h"

// javascript相关命令实现文件




// 调用格式: _SDT_NULL (Javascript).JS初始化, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(27, JSIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// 调用格式: _SDT_NULL (Javascript).JS赋值, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(28, JSCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// 调用格式: _SDT_NULL (Javascript).JS销毁, 命令说明: NULL
// 无参数
EXTERN_C void WKE_NAME(29, JSDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// 调用格式: _SDT_NULL (Javascript).垃圾回收, 命令说明: "wke_JSGC , 垃圾回收。"
// 无参数
EXTERN_C void WKE_NAME(30, JSGC)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	jsGC();
}

// 调用格式: SDT_INT (Javascript).取类型, 命令说明: "获取JS数据类型,传入执行结果即可 返回值参考 #JS类型_ 相关的常量。"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(31, wke_GetType)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

	jsType nRet = jsTypeOf((jsValue)pArgInf[1].m_int64);
	pRetData->m_dtDataType = SDT_INT;
	pRetData->m_int = nRet;
}

// 调用格式: SDT_INT64 (Javascript).指定框架运行JS, 命令说明: "指定框架运行JS。"
// 参数<1>: webView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 框架ID SDT_INT, 参数说明: "框架ID"
// 参数<3>: script SDT_TEXT, 参数说明: "javascript脚本"
// 参数<4>: 是否包含在Function中执行 SDT_BOOL, 参数说明: "script代码会在mb内部自动被包裹在一个function(){}中。所以使用的变量会被隔离,此处确定是否包裹在function中"
EXTERN_C void WKE_NAME(32, wke_RunJsByFrame)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	jsValue value = wkeRunJsByFrame((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int, (LPCSTR)pArgInf[3].m_pText, (bool)pArgInf[4].m_bool);
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = value;
}

// 调用格式: SDT_TEXT (Javascript).运行JS_文本_已废弃, 命令说明: "运行javascript脚本,有返回值则返回相应结果,否则返回空文本。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: script SDT_TEXT, 参数说明: "待运行的脚本"
// 参数<3>: 是否有返回值 SDT_BOOL, 参数说明: "JS是否有返回值"
EXTERN_C void WKE_NAME(33, wke_RunJsToStr)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_TEXT;
	pRetData->m_pText = 0;
}

// 调用格式: SDT_INT64 (Javascript).运行JS_值对象, 命令说明: "运行javascript脚本,返回运行结果指针(JsVlaue,值对象),获取到的结果需要使用 取结果到_xx 等命令取值。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: script SDT_TEXT, 参数说明: "待运行的脚本"
EXTERN_C void WKE_NAME(34, wke_RunJsToJsValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wstr szScript = wstr::A2W(pArgInf[2].m_pText);
	jsValue value = wkeRunJSW((wkeWebView)pArgInf[1].m_int, szScript.c_str());
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = value;
}

// 调用格式: SDT_TEXT (Javascript).计算表达式_文本, 命令说明: "使用eval方法计算js表达式,返回文本型结果 mb内部自动被包裹在一个function(){}中。所以使用的变量会被隔离 要获取返回值，请写return。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
// 参数<2>: 表达式 SDT_TEXT, 参数说明: "待计算的表达式"
// 参数<3>: 是否有返回值 SDT_BOOL, 参数说明: "JS是否有返回值"
EXTERN_C void WKE_NAME(35, wke_Eval_Str)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wkeWebView hWebView = (wkeWebView)pArgInf[1].m_int;
	jsExecState es = wkeGlobalExec(hWebView);
	_str str = pArgInf[2].m_pText;
	str = _str("return ") + str;
	wstr wzStr = wstr::A2W(str.c_str());
	_str szStr;

	jsValue lv = jsEvalW(es, wzStr.c_str());
	const wchar_t* wzRet = jsToStringW(es, lv);
	szStr = wstr::W2A((LPWSTR)wzRet);
	pRetData->m_dtDataType = SDT_TEXT;
	pRetData->m_pText = CloneTextData(szStr.c_str());

}

// 调用格式: SDT_INT64 (Javascript).计算表达式_值对象, 命令说明: "使用eval方法计算js表达式,返回运行结果指针(JsVlaue,值对象),获取到的结果需要使用 取结果到_xx 等命令取值 mb内部自动被包裹在一个function(){}中。所以使用的变量会被隔离。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "请使用 全局创建JS执行状态() 获取"
// 参数<2>: 表达式 SDT_TEXT, 参数说明: "待计算的表达式"
EXTERN_C void WKE_NAME(36, wke_Eval_JsValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wstr wzStr = wstr::A2W(pArgInf[2].m_pText);
	jsValue value = jsEvalW((jsExecState)pArgInf[1].m_int, wzStr.c_str());
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = value;
}

// 调用格式: SDT_INT (Javascript).取JS执行状态, 命令说明: "获取指定view的JS执行状态,大部分需要获取返回值的JS方法都需要此状态。"
// 参数<1>: WebView SDT_INT, 参数说明: "WebView指针,请使用 精易WEB浏览器.取WebView()  获取"
EXTERN_C void WKE_NAME(37, wke_CreateGlobalState)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsExecState value = wkeGlobalExec((wkeWebView)pArgInf[1].m_int);
	pRetData->m_dtDataType = SDT_INT;
	pRetData->m_int = (int)value;
}

typedef __int64 (CALLBACK* userFunc)(int es, int nArgCount);

typedef struct tagjsDataEx : public jsData
{
	userFunc userfunc;
}jsDataEx;
jsValue _jsGetPropertyCallback(jsExecState es, jsValue object, const char* propertyName)
{
	return 0;
}
bool _jsSetPropertyCallback(jsExecState es, jsValue object, const char* propertyName, jsValue value)
{
	return false;
}
jsValue _jsCallAsFunctionCallback(jsExecState es, jsValue object, jsValue* args, int argCount)
{
	jsDataEx* data = (jsDataEx*)jsGetData(es, object);
	if (data->userfunc != NULL && strcmp(data->typeName, "Function") == 0)
	{
		return data->userfunc((int)es, argCount);
	}
	return 0;
}
void _jsFinalizeCallback(struct tagjsData* data)
{
	jsDataEx* pData = (jsDataEx*)data;
	delete pData;
}

// 调用格式: SDT_INT64 (Javascript).到JS方法指针, 命令说明: "将易语言中的子程序转换到JS可用的方法指针。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "请使用 全局创建JS执行状态() 获取"
// 参数<2>: 待转换子程序 SDT_SUB_PTR, 参数说明: "易语言中的子程序指针"
EXTERN_C void WKE_NAME(38, wke_ToJsFunc)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsDataEx* data = new jsDataEx;
	strcpy(data->typeName, "Function");

	data->callAsFunction = _jsCallAsFunctionCallback;
	data->finalize = _jsFinalizeCallback;
	data->propertyGet = _jsGetPropertyCallback;
	data->propertySet = _jsSetPropertyCallback;
	data->userfunc = (userFunc)(pArgInf[2].m_dwSubCodeAdr);

	jsFunction((jsExecState)pArgInf[1].m_int, (jsData*)data);
}

// 调用格式: SDT_INT64 (Javascript).取全局对象属性, 命令说明: "取全局对象属性JSValue 请使用相应转换命令得到最终结果。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "请使用 全局创建JS执行状态() 获取"
// 参数<2>: 属性名称 SDT_TEXT, 参数说明: "对象属性名称"
EXTERN_C void WKE_NAME(39, wke_GetGlobalObject)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsValue value = jsGetGlobal((jsExecState)pArgInf[1].m_int, pArgInf[2].m_pText);
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = value;
}

// 调用格式: _SDT_NULL (Javascript).置全局对象属性, 命令说明: "为指定全局对象属性设置值,常用于函数绑定,全局变量赋值等等。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "请使用 全局创建JS执行状态() 获取"
// 参数<2>: 属性名称 SDT_TEXT, 参数说明: "对象属性名称"
// 参数<3>: 属性值 SDT_INT64, 参数说明: "对象属性名称"
EXTERN_C void WKE_NAME(40, wke_SetGlobalObject)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsSetGlobal((jsExecState)pArgInf[1].m_int, pArgInf[2].m_pText, (jsValue)pArgInf[3].m_int64);
}

// 调用格式: SDT_INT64 (Javascript).调用全局函数, 命令说明: "调用js全局函数。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "请使用 全局创建JS执行状态() 获取"
// 参数<2>: js函数 SDT_INT64, 参数说明: "js函数"
// 参数<3>: [参数数组 数组 SDT_INT64], 参数说明: "传入的参数数组"
EXTERN_C void WKE_NAME(41, wke_CallGlobal)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    int dwLen = 0;
	LPBYTE pArr = NULL;
	if (pArgInf[3].m_pAryData != NULL)
	{
		pArr = GetAryElementInf(pArgInf[3].m_pAryData, &dwLen);
	}

	jsValue ret = jsCallGlobal((jsExecState)pArgInf[1].m_int, (jsValue)pArgInf[2].m_int64, (jsValue*)pArr, dwLen);
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = (INT64)ret;
}

// 调用格式: SDT_INT64 (Javascript).调用对象函数, 命令说明: "调用js全局函数,可以指定this。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "请使用 全局创建JS执行状态() 获取"
// 参数<2>: js函数 SDT_INT64, 参数说明: "js函数"
// 参数<3>: this对象 SDT_INT64, 参数说明: "函数的this对象"
// 参数<4>: [参数数组 数组 SDT_INT64], 参数说明: "传入的参数数组"
EXTERN_C void WKE_NAME(42, wke_Call)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    int dwLen = 0;
	LPBYTE pArr = NULL;
	if (pArgInf[4].m_pAryData != NULL)
	{
		pArr = GetAryElementInf(pArgInf[4].m_pAryData, &dwLen);
	}

	jsValue ret = jsCall((jsExecState)pArgInf[1].m_int, (jsValue)pArgInf[2].m_int64, (jsValue)pArgInf[3].m_int64, (jsValue*)pArr, dwLen);
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = (INT64)ret;
}

// 调用格式: _SDT_NULL (Javascript).取全局对象, 命令说明: "取全局对象,window。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "请使用 全局创建JS执行状态() 获取"
EXTERN_C void WKE_NAME(43, wke_GetGlobal)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsGlobalObject((jsExecState)pArgInf[1].m_int);
}

typedef __int64 (CALLBACK* CALLFUNC)(int);

jsValue NativeCallBackFunc(jsExecState es, void* param)
{
	//MessageBox(0, "NativeCallBackFunc", "N", MB_OK);
	//param 是传递过来的易语言子程序指针。

	if (param != 0)
	{
		CALLFUNC func = (CALLFUNC)param;
		return func(int(es));
	}
	else
	{
		return 0;
	}
}

// 调用格式: _SDT_NULL (Javascript).绑定子程序, 命令说明: "JS中的函数与易语言子程序进行绑定,当JS中函数出发的时候回自动回调易语言中的子程序,并传入相应的参数。"
// 参数<1>: Js函数名称 SDT_TEXT, 参数说明: "js中函数的名称"
// 参数<2>: 易语言子程序指针 SDT_SUB_PTR, 参数说明: "易语言中的子程序指针。 该子程序有一个长整数型参数（表示js环境），返回长整数型。如果参数或返回值错误，程序将会崩溃！！"
// 参数<3>: 参数个数 SDT_INT, 参数说明: "传入的参数个数"
EXTERN_C void WKE_NAME(44, wke_BindFunc)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	//char szLog[1024] = { 0 };
	//sprintf(szLog, "wke_BindFunc\nNativeCallBackFunc:%d , threadId:%d", NativeCallBackFunc, ::GetCurrentThreadId());

	//MessageBox(0, szLog, pArgInf[1].m_pText, MB_OK);

	wkeJsBindFunction(pArgInf[1].m_pText, NativeCallBackFunc, (void*)(pArgInf[2].m_dwSubCodeAdr), pArgInf[3].m_int);
}

// 调用格式: SDT_INT (Javascript).取参数个数, 命令说明: "取回调函数参数个数。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态,回调函数第一个参数"
EXTERN_C void WKE_NAME(45, wke_ParamsCount)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT;
	pRetData->m_int = jsArgCount((jsExecState)(pArgInf[1].m_int));
}



// 调用格式: SDT_INT (Javascript).取整数型参数, 命令说明: "整数型参数取值。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态,回调函数第一个参数"
// 参数<2>: 参数序号 SDT_INT, 参数说明: "参数下标,从0开始计算"
EXTERN_C void WKE_NAME(46, wke_ParamToInt)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

    pRetData->m_dtDataType = SDT_INT;
    jsValue val = jsArg((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int);
    pRetData->m_int = jsToInt((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int);
}

// 调用格式: SDT_TEXT (Javascript).取文本型参数, 命令说明: "文本型参数取值。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态,回调函数第一个参数"
// 参数<2>: 参数序号 SDT_INT, 参数说明: "参数下标,从0开始计算"
EXTERN_C void WKE_NAME(47, wke_ParamToText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str str;
    pRetData->m_dtDataType = SDT_TEXT;
    jsValue val = jsArg((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int);
    const wchar_t* pWchar = jsToTempStringW((jsExecState)( pArgInf[1].m_int ), val);
    str = wstr::W2A((LPWSTR)pWchar);
    pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_BOOL (Javascript).取逻辑型参数, 命令说明: "逻辑型参数取值。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态,回调函数第一个参数"
// 参数<2>: 参数序号 SDT_INT, 参数说明: "参数下标,从0开始计算"
EXTERN_C void WKE_NAME(48, wke_ParamToBool)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_BOOL;
    pRetData->m_bool = jsToBoolean((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// 调用格式: SDT_FLOAT (Javascript).取小数型参数, 命令说明: "小数型参数取值。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态,回调函数第一个参数"
// 参数<2>: 参数序号 SDT_INT, 参数说明: "参数下标,从0开始计算"
EXTERN_C void WKE_NAME(49, wke_ParamToFloat)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_FLOAT;
    pRetData->m_float = jsToFloat((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// 调用格式: SDT_DOUBLE (Javascript).取双精度小数型参数, 命令说明: "双精度小数型参数取值。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态,回调函数第一个参数"
// 参数<2>: 参数序号 SDT_INT, 参数说明: "参数下标,从0开始计算"
EXTERN_C void WKE_NAME(50, wke_ParamToDouble)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_DOUBLE;
    pRetData->m_double = jsToDouble((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// 调用格式: SDT_INT (Javascript).取执行结果到整数, 命令说明: "取整数型的执行结果。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态"
// 参数<2>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(51, wke_ResultToInt)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT;
    pRetData->m_int = jsToInt((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// 调用格式: SDT_TEXT (Javascript).取执行结果到文本, 命令说明: "取文本型的执行结果。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态"
// 参数<2>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(52, wke_ResultToText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str str;
    pRetData->m_dtDataType = SDT_TEXT;
    LPCSTR pWchar = jsToString((jsExecState)( pArgInf[1].m_int ), (jsValue)pArgInf[2].m_int64);
    if ( pWchar == NULL )
    {
        pRetData->m_pText = NULL;
    }
    else
    {
        pRetData->m_pText = CloneTextData(pWchar);
    }
}

// 调用格式: SDT_BOOL (Javascript).取执行结果到逻辑, 命令说明: "取逻辑型的执行结果。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态"
// 参数<2>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(53, wke_ResultToBool)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_BOOL;
    pRetData->m_bool = jsToBoolean((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// 调用格式: SDT_FLOAT (Javascript).取执行结果到小数, 命令说明: "取小数型的执行结果。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态"
// 参数<2>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(54, wke_ResultToFloat)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_FLOAT;
    pRetData->m_float = jsToFloat((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// 调用格式: SDT_DOUBLE (Javascript).取执行结果到双精度, 命令说明: "取双精度小数型的执行结果。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态"
// 参数<2>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(55, wke_ResultToDouble)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_DOUBLE;
    pRetData->m_double = jsToDouble((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// 调用格式: SDT_INT64 (Javascript).置返回值整数型, 命令说明: NULL
// 参数<1>: 待设置值 SDT_INT, 参数说明: "待设置值"
EXTERN_C void WKE_NAME(56, wke_SetRetTypeByInt)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = jsInt(pArgInf[1].m_int);
}

// 调用格式: SDT_INT64 (Javascript).置返回值文本型, 命令说明: NULL
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态"
// 参数<2>: 待设置值 SDT_TEXT, 参数说明: "待设置值"
EXTERN_C void WKE_NAME(57, wke_SetRetTypeByText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    wstr pWchar = wstr::A2W(pArgInf[2].m_pText);
    //pArgInf[2].m_pText
    pRetData->m_int64 = jsStringW((jsExecState)( pArgInf[1].m_int ), pWchar.c_str());
}

// 调用格式: SDT_INT64 (Javascript).置返回值逻辑型, 命令说明: NULL
// 参数<1>: 待设置值 SDT_BOOL, 参数说明: "待设置值"
EXTERN_C void WKE_NAME(58, wke_SetRetTypeByBool)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = jsBoolean((bool)pArgInf[1].m_bool);
}

// 调用格式: SDT_INT64 (Javascript).置返回值小数型, 命令说明: NULL
// 参数<1>: 待设置值 SDT_FLOAT, 参数说明: "待设置值"
EXTERN_C void WKE_NAME(59, wke_SetRetTypeByFloat)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = jsFloat(pArgInf[1].m_float);
}

// 调用格式: SDT_INT64 (Javascript).置返回值双精度小数型, 命令说明: NULL
// 参数<1>: 待设置值 SDT_DOUBLE, 参数说明: "待设置值"
EXTERN_C void WKE_NAME(60, wke_SetRetTypeByDouble)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = jsDouble(pArgInf[1].m_double);
}





//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// 调用格式: SDT_INT64 (Javascript).取对象属性, 命令说明: "取指定对象的属性JSValue 请使用相应转换命令得到最终结果，如果object不是正确的类型，则返回jsUndefined。本命令为高级对象成员命令。"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "请使用 全局创建JS执行状态() 获取"
// 参数<2>: object对象 SDT_INT64, 参数说明: "js的object"
// 参数<3>: 要取的属性名称 SDT_TEXT, 参数说明: "属性名"
EXTERN_C void WKE_NAME(160, wke_GetObjectProp)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsValue value = jsGet((jsExecState)pArgInf[1].m_int, (jsValue)pArgInf[2].m_int64, pArgInf[3].m_pText);
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = value;
}

// 调用格式: SDT_INT (Javascript).取参数类型, 命令说明: "取参数类型"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态"
// 参数<2>: 参数序号 SDT_INT, 参数说明: "参数下标,从0开始计算"
EXTERN_C void WKE_NAME(204, wke_jsArgType)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsType type = jsArgType((jsExecState)pArgInf[1].m_int, pArgInf[2].m_int);
    pRetData->m_int = (int)type;
}

// 调用格式: SDT_INT64 (Javascript).取参数值, 命令说明: "取参数值"
// 参数<1>: 执行状态 SDT_INT, 参数说明: "执行状态"
// 参数<2>: 参数序号 SDT_INT, 参数说明: "参数下标,从0开始计算"
EXTERN_C void WKE_NAME(205, wke_jsArg)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsValue type = jsArg((jsExecState)pArgInf[1].m_int, pArgInf[2].m_int);
    pRetData->m_int64 = (__int64)type;
}

// 调用格式: SDT_BOOL (Javascript).是否为数值, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(206, wke_jsIsNumber)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsNumber((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为字符串, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(207, wke_jsIsString)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsString((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为逻辑值, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(208, wke_jsIsBoolean)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsBoolean((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为对象, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(209, wke_jsIsObject)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsObject((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为函数, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(210, wke_jsIsFunction)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsFunction((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为Undefined, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(211, wke_jsIsUndefined)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsUndefined((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为空, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(212, wke_jsIsNull)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsNull((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为数组, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(213, wke_jsIsArray)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsArray((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为真, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(214, wke_jsIsTrue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsTrue((jsValue)pArgInf[1].m_int64);
}

// 调用格式: SDT_BOOL (Javascript).是否为假, 命令说明: "判断值对象是否为该类型"
// 参数<1>: 值对象 SDT_INT64, 参数说明: "值对象,执行结果指针"
EXTERN_C void WKE_NAME(215, wke_jsIsFalse)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsFalse((jsValue)pArgInf[1].m_int64);
}

