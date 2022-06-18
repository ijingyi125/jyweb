#pragma once

#define __WKE_NAME(_index, _name) __LIB2_FNE_NAME_LEFT(__E_FNENAME)##_##_name##_##_index##_

// 传递函数名和索引, 拼接成 定义库名_名字_序号_定义库名, 比如 wke_test_0_wke
#define WKE_NAME(_index, _name) __LIB2_FNE_NAME_LEFT(__WKE_NAME(_index, _name))__LIB2_FNE_NAME_LEFT(__E_FNENAME)

// 传递函数名和索引, 拼接成 "定义库名_名字_序号_定义库名", 比如 "wke_test_0_wke"
#define WKE_NAME_STR(_index, _name) ______E_FNENAME(WKE_NAME(_index, _name))

// 这个宏定义了所有的命令, 以后需要命令名数组, 声明命令等, 都可以使用这个宏
#define WKE_DEF(_MAKE) \
    _MAKE(  0, "浏览网页", SetUrl, "浏览指定网页。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 0)\
    _MAKE(  1, "取网页URL", GetUrl, "获取当前网页URL地址。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  2, "载入HTML文本", wke_LoadHtml, "载入HTML代码文本。注意，如果网页代码中需要编码，则需要自行进行编码转换。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 1)\
    _MAKE(  3, "载入HTML文件", wke_LoadFile, "载入HTML文件。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 2)\
    _MAKE(  4, "前进", wke_GoForward, "浏览器前进命令。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  5, "后退", wke_CanGoBack, "浏览器后退命令。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  6, "停止载入", wke_StopLoading, "停止加载当前网页。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  7, "重新载入", wke_Reload, "重新载入当前网页,相当于刷新命令。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  8, "取网页源码", GetWebPageSource, "返回当前网页源码,如果出现乱码,请使用 \"wke_Utf8ToAnsi()\" 转换。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_jywebkit + 23)\
    _MAKE(  9, "获取Cookie", wke_GetCookie, "获取当前网页的Cookie。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 10, "设置Cookie_此命令已弃用_请调用_设置cookie_CURL_来设置_设置cookie_CURL是node_dll提供的接口_没有任何二次封装", wke_SetCookie, "支持库不提供任何针对cookie进行二次封装的命令, 所有cookie相关的命令都是原封调用node.dll\r\n""        设置cookie请调用 设置cookie_CURL(), 该命令原封调用node.dll的wkeSetCookie接口\r\n", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 3)\
    _MAKE( 11, "执行Cookie命令", wke_ExecuteCookeCommand, "执行cookie相关命令。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 5)\
    _MAKE( 12, "设置UserAgent", wke_SetUserAgent, "设置浏览器默认的UserAgent。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 6)\
    _MAKE( 13, "设置代理", SetProxy, "为指定的webView设置代理。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_jywebkit + 7)\
    _MAKE( 14, "设置网页音量", SetWebVolume, "", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_FLOAT, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 15, "设置媒体音量", SetMediVolume, "设置网页媒体音量。", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 11)\
    _MAKE( 16, "取WebView", GetWebView, "返回WebView指针。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 17, "是否可以前进", IsGoRorward, "返回浏览器是否可以执行前进命令。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 18, "是否可以后退", CanGoBack, "返回浏览器是否可以执行后退命令。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 19, "是否加载完成", IsLodingCompleted, "返回网页是否加载完成。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 20, "文档是否就绪", IsDocumentReady, "返回文档是否已就绪。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 21, "Ajax初始化", AJAXIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 22, "Ajax赋值", AJAXCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_COPY_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 23, "AJAX销毁", AJAXDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_FREE_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 24, "设置Http请求头", SetHttpHeader, "设置Http请求头,在调用Get或Post方法后请求头将被清空。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_ajax + 0)\
    _MAKE( 25, "GET请求", AjaxGet, "向网页内注入ajax脚本方法实现Get请求。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_ajax + 2)\
    _MAKE( 26, "POST请求", AjaxPost, "向网页内注入ajax脚本方法实现Post请求。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 5, g_Args_ajax + 5)\
    _MAKE( 27, "JS初始化", JSIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 28, "JS赋值", JSCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_COPY_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 29, "JS销毁", JSDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_FREE_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 30, "垃圾回收", JSGC, "wke_JSGC , 垃圾回收。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 31, "取类型", wke_GetType, "获取JS数据类型,传入执行结果即可 返回值参考 #JS类型_ 相关的常量。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0)\
    _MAKE( 32, "指定框架运行JS", wke_RunJsByFrame, "指定框架运行JS。", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_SECONDARY, 0, 0, 4, g_Args_JavaScript + 1)\
    _MAKE( 33, "运行JS_文本_已废弃", wke_RunJsToStr, "运行javascript脚本,有返回值则返回相应结果,否则返回空文本。", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 3, g_Args_JavaScript + 5)\
    _MAKE( 34, "运行JS_值对象", wke_RunJsToJsValue, "运行javascript脚本,返回运行结果指针(JsVlaue,值对象),获取到的结果需要使用 取结果到_xx 等命令取值。", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 8)\
    _MAKE( 35, "计算表达式_文本", wke_Eval_Str, "使用eval方法计算js表达式,返回文本型结果 mb内部自动被包裹在一个function(){}中。所以使用的变量会被隔离 要获取返回值，请写return。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 10)\
    _MAKE( 36, "计算表达式_值对象", wke_Eval_JsValue, "使用eval方法计算js表达式,返回运行结果指针(JsVlaue,值对象),获取到的结果需要使用 取结果到_xx 等命令取值 mb内部自动被包裹在一个function(){}中。所以使用的变量会被隔离。", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_SIMPLE, 0, 0, 2, g_Args_JavaScript + 13)\
    _MAKE( 37, "取JS执行状态", wke_CreateGlobalState, "获取指定view的JS执行状态,大部分需要获取返回值的JS方法都需要此状态。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 15)\
    _MAKE( 38, "到JS方法指针", wke_ToJsFunc, "将易语言中的子程序转换到JS可用的方法指针。", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 16)\
    _MAKE( 39, "取全局对象属性", wke_GetGlobalObject, "取全局对象属性JSValue 请使用相应转换命令得到最终结果。", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 18)\
    _MAKE( 40, "置全局对象属性", wke_SetGlobalObject, "为指定全局对象属性设置值,常用于函数绑定,全局变量赋值等等。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 20)\
    _MAKE( 41, "调用全局函数", wke_CallGlobal, "调用js全局函数。", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 23)\
    _MAKE( 42, "调用对象函数", wke_Call, "调用js全局函数,可以指定this。", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 4, g_Args_JavaScript + 26)\
    _MAKE( 43, "取全局对象", wke_GetGlobal, "取全局对象,window。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 30)\
    _MAKE( 44, "绑定子程序", wke_BindFunc, "JS中的函数与易语言子程序进行绑定,当JS中函数出发的时候回自动回调易语言中的子程序,并传入相应的参数。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 31)\
    _MAKE( 45, "取参数个数", wke_ParamsCount, "取回调函数参数个数。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 34)\
    _MAKE( 46, "取整数型参数", wke_ParamToInt, "整数型参数取值。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 35)\
    _MAKE( 47, "取文本型参数", wke_ParamToText, "文本型参数取值。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 37)\
    _MAKE( 48, "取逻辑型参数", wke_ParamToBool, "逻辑型参数取值。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 39)\
    _MAKE( 49, "取小数型参数", wke_ParamToFloat, "小数型参数取值。", -1, _CMD_OS(__OS_WIN), SDT_FLOAT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 41)\
    _MAKE( 50, "取双精度小数型参数", wke_ParamToDouble, "双精度小数型参数取值。", -1, _CMD_OS(__OS_WIN), SDT_DOUBLE, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 43)\
    _MAKE( 51, "取执行结果到整数", wke_ResultToInt, "取整数型的执行结果。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 45)\
    _MAKE( 52, "取执行结果到文本", wke_ResultToText, "取文本型的执行结果。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 47)\
    _MAKE( 53, "取执行结果到逻辑", wke_ResultToBool, "取逻辑型的执行结果。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 49)\
    _MAKE( 54, "取执行结果到小数", wke_ResultToFloat, "取小数型的执行结果。", -1, _CMD_OS(__OS_WIN), SDT_FLOAT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 51)\
    _MAKE( 55, "取执行结果到双精度", wke_ResultToDouble, "取双精度小数型的执行结果。", -1, _CMD_OS(__OS_WIN), SDT_DOUBLE, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 53)\
    _MAKE( 56, "置返回值整数型", wke_SetRetTypeByInt, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 55)\
    _MAKE( 57, "置返回值文本型", wke_SetRetTypeByText, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 56)\
    _MAKE( 58, "置返回值逻辑型", wke_SetRetTypeByBool, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 58)\
    _MAKE( 59, "置返回值小数型", wke_SetRetTypeByFloat, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 59)\
    _MAKE( 60, "置返回值双精度小数型", wke_SetRetTypeByDouble, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 60)\
    _MAKE( 61, "填表初始化", TBIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_CONSTURCT_CMD, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 62, "填表赋值", TBCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_COPY_CMD, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 63, "填表销毁", TBDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_FREE_CMD, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 64, "元素点击", wke_ElementClick, "元素点击。", -1, _CMD_OS(__OS_WIN) , _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 65, "元素置焦点", wke_SetElementFouce, "元素置焦点。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 66, "取元素属性值", wke_GetAttribute, "取指定元素属性的置。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 0)\
    _MAKE( 67, "置元素属性值", wke_SetAttribute, "设置指定元素的值。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 6, g_Args_tb + 0)\
    _MAKE( 68, "表单_置填表框架", Form_SetFrame, "设置框架以后,所有的 表单_ 填表操作都是在这个框架内部进行,索引小于1,表示清除当前选择框架", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 69, "表单_取当前框架数量", Form_GetFrameCount, "获取当前网页中框架(iframe)的数量。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 70, "表单_Input点击", wke_Input_Click, "取指定元素属性的值。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 71, "表单_Input读属性", wke_Input_ReadAttrValue, "读取表单中指定input元素的属性值。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 0)\
    _MAKE( 72, "表单_Input写属性", wke_Input_WriteAttrVal, "向指定INPUT元素写入属性值,如果属性存在则更新该属性的值,不存在则增加一个属性。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 6, g_Args_tb + 0)\
    _MAKE( 73, "表单_Input移除属性", wke_Input_RemoveAttrValue, "移除指定表单元素中的指定属性。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 0)\
    _MAKE( 74, "表单_Input选择框置选中状态", wke_Input_SetCheckBoxState, "表单_Input选择框置选中状态,为真选中,为假取消选中 假。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 6)\
    _MAKE( 75, "表单_Input单选框置选中状态", wke_Input_SetRadioChecked, "单选框置选中状态,为真选中,为假取消选中 假。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 6)\
    _MAKE( 76, "表单_Input组合框置选中项", wke_Input_SetComboxIndex, "组合框置选中状态,为真选中,为假取消选中 假。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 11)\
    _MAKE( 77, "表单_取表单元素数量", Form_GetSubCount, "获取指定表单下的所有表单元素个数,只有表单元素才会计数。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 78, "表单_提交", Form_Submit, "提交指定表单,请注意如果提交不成功,请确认网页中没有屏蔽这个submit的过程。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 79, "文档_置标题", wke_DocSetTitle, "通过JS设置网页文档标题。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 16)\
    _MAKE( 80, "文档_置缩放", wke_DocSetZoom, "设置文档缩放。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 18)\
    _MAKE( 81, "文档_取缩放", wke_DocGetZoom, "取文档缩放阀值。", -1, _CMD_OS(__OS_WIN), SDT_FLOAT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 18)\
    _MAKE( 82, "文档_取文档区域宽度", wke_DocGetWidth, "文档_取文档区域宽度。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 83, "文档_取文档区域高度", wke_DocGetHeight, "文档_取文档区域高度。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 84, "文档_取Body区域宽度", wke_DocGetBodyWidth, "文档_取Body区域宽度。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 85, "文档_取Body区域高度", wke_DocGetBodyHeight, "文档_取Body区域高度。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 86, "文档_取纵向滚动条位置", wke_DocGetScollY, "取纵向滚动条位置。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 87, "文档_置纵向滚动条位置", wke_DocSetScollY, "设置纵向滚动条位置。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 20)\
    _MAKE( 88, "文档_置横向滚动条位置", wke_DocSetScollX, "设置横向滚动条位置。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 22)\
    _MAKE( 89, "文档_取编码", wke_DocGetEncoding, "获取当前网页编码。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 90, "文档_取根域名", DocGetDomain, "wke_获取网页根域名。", -1, _CMD_OS(__OS_WIN), SDT_TEXT , 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 91, "文档_取选中文本", wke_DocGetSelectText, "获取当前选中的文本。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 92, "文档_取元素内容", GetElementHTML, "取指定元素内容 innerHTML。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 93, "文档_进入编辑模式", wke_DocEnableEditModel, "进入编辑模式。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 24)\
    _MAKE( 94, "文档_复制", DocEditCopy, "编辑模式复制。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 95, "文档_剪切", DocEditCut, "编辑模式剪切。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 96, "文档_粘贴", DocEditPaste, "编辑模式粘贴。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 97, "文档_撤销", DocEditPaste, "编辑模式撤销。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 98, "文档_全选", DocSelectedAll, "编辑模式全选。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 99, "文档_取消全选", DocCancelSelect, "编辑模式取消全选。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE(100, "文档_重置", DocEditRedo, "编辑模式重置。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE(101, "文档_标记所有连接", wke_MarkerAllLinks, "标记所有连接。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 26)\
    _MAKE(102, "文档_标记所有文本框", wke_MarkerAllInputText, "标记所有文本框。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 26)\
    _MAKE(103, "文档_标记所有按钮", wke_MarkerAllButton, "标记所有按钮。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 26)\
    _MAKE(104, "文档_Jquery是否已加载", wke_JqueryIsLoding, "文档_Jquery是否已加载。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE(105, "文档_执行JS方法", JSCall, "调用。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 28)\
    _MAKE(106, "文档_取图片地址", wke_GetImageElemSrc, "文档_图片取地址。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(107, "文档_取链接地址", wke_GetLinkhref, "文档_链接取地址。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(108, "元素_取标题", wke_GetElemTitle, "获取元素的title属性值。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(109, "元素_取内联样式", wke_GetElemStyleStr, "元素_取内联样式。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(110, "元素_取类名列表", wke_GetClassList, "元素_取类名列表。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(111, "元素_闪烁标记", wke_SetElementFlag, "标记指定元素。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(112, "元素_置可视状态", wke_SetElementVisableState, "设置元素可见状态。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 30)\
    _MAKE(113, "元素_取横坐标", wke_GetElementPointX, "取元素横坐标。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 35)\
    _MAKE(114, "元素_取纵坐标", wke_GetElementPointY, "取元素纵坐标。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 35)\
    _MAKE(115, "元素_取矩形信息", GetElementRect, "取元素矩形,元素的矩形信息 左边 右边 顶边 底边 宽 高。", -1, _CMD_OS(__OS_WIN), SDT_TYPE_TYPERECT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(116, "元素_触发指定事件", CallEvent, "触发指定元素的指定事件,可以传递事件参数。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 7, g_Args_tb + 40)\
    _MAKE(117, "特殊功能初始化", NETIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(118, "特殊功能赋值", NETCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_COPY_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(119, "特殊功能销毁", NETDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_FREE_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(120, "NPAPI插件开启关闭", wke_NPAPIEnable, "该浏览器内核支持NPAPI插件，借助NPAPI插件，可以实现例如FLASH播放的功能。真开启，假关闭", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 0)\
    _MAKE(121, "爬虫模式开启关闭", wke_SpiderEnable, "开启或关闭网页渲染,提高网页加载速度 适用于爬虫。注意：如果关闭后，网页不再进行渲染，但内容依然存在。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 2)\
    _MAKE(122, "Cookie开启关闭", wke_SetCookieEnable, "Cookie开启和禁用，如果关闭，浏览器将不再带有Cookie。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 4)\
    _MAKE(123, "Cookie是否可用", wke_CookieIsEnable, "Cookie是否已经开启。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 6)\
    _MAKE(124, "跨域检查开启关闭", wke_CspCheckEnable, "跨域检查是否开启 如果设置为真，则检查跨域操作，跨域操作将无权执行，如果设置为假，则允许跨域操作。默认值为假。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 7)\
    _MAKE(125, "拦截网络请求", HookRequest, "可以 Url载入开始 事件中调用,Hook指定资源。必须调用此方法后，Url载入结束事件才会被调用", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 9)\
    _MAKE(126, "修改HTTP头字段信息", wke_NetSetHTTPHeaderField, "可以 Url载入开始 事件中调用，表示设置http请求（或者file:///协议）的 HTTP头字段信息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 10)\
    _MAKE(127, "修改请求MIME类型", wke_NetSetMIMEType, "可以在 URL载入开始 事件中调用 表示设置http请求的MIME type。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 13)\
    _MAKE(128, "修改请求URL", wke_NetChangeRequestUrl, "可以在 URL载入开始 事件中调用 可以修改一个网络请求的url。", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 15)\
    _MAKE(129, "修改拦截数据", wke_SetRequestData, "在 Url载入开始 事件里调用，表示设置拦截后缓存的数据。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 17)\
    _MAKE(130, "开启触屏模式", wke_SetTouchEnabled, "开启后，鼠标消息将自动转换成触屏消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 20)\
    _MAKE(131, "开关鼠标消息", wke_SetMouseEnabled, "开启关闭鼠标消息，可以在开启触屏后，关闭鼠标消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 22)\
    _MAKE(132, "调用DevTool", wke_ShowDevTool, "开启一些试验型功能。 例如开启开发者工具。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 24)\
    _MAKE(133, "取主框架ID", wke_GetMainFrameId, "取主框架ID。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 27)\
    _MAKE(134, "是否为主框架", wke_IsMainFrame, "是否为主框架。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 28)\
    _MAKE(135, "取框架URL", wke_GetFrameUrl, "按框架ID取框架URL。", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 30)\
    _MAKE(136, "鼠标移动", wke_MBMouseMove, "发送鼠标消息,模拟移动到指定位置。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 32)\
    _MAKE(137, "鼠标左键按下", wke_MouseLButtonDown, "发送鼠标左键按下消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 35)\
    _MAKE(138, "鼠标左键抬起", wke_MouseLButtonUP, "发送鼠标左键抬起消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 38)\
    _MAKE(139, "鼠标中键按下", wke_MouseMButtonDown, "发送鼠标中键按下消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 41)\
    _MAKE(140, "鼠标中键抬起", wke_MouseMButtonUP, "发送鼠标中键抬起消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 44)\
    _MAKE(141, "鼠标右键按下", wke_MouseRButtonDown, "发送鼠标右键按下消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 47)\
    _MAKE(142, "鼠标右键抬起", wke_MouseRButtonUP, "发送鼠标右键抬起消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 50)\
    _MAKE(143, "按键_按下", wke_KeyDownEvent, "发送按键消息到MB。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 53)\
    _MAKE(144, "按键_抬起", wke_KeyUpEvent, "发送按键消息到MB。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 55)\
    _MAKE(145, "按键_字符", wke_KeyPressEvent, "发送WM_CHAR消息。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 57)\
    _MAKE(146, "取消该网络请求", wke_CancelByReuqest, "可以在 URL载入开始事件中 取消指定的网络请求。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 59)\
    _MAKE(147, "wke_设置dll路径", wke_setDllPath, "设置node.dll的完整路径,如果程序运行目录下没有node.dll,则必须在窗口载入之前调用,如果程序运行目录下有node.dll可以忽略该命令,默认会从目录下加载。", 1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 0 )\
    _MAKE(148, "wke_AnsiToUtf8", wke_A2U, "把ansi编码的文本转换成utf8编码的文本,成功返回转换后的文本,失败返回空文本。", 2, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 2 )\
    _MAKE(149, "wke_AnsiToUnicode", wke_A2W, "把ansi编码的文本转换成Unicode编码的文本,成功返回转换后的Unicode字节集,失败返回空字节集。", 2, _CMD_OS(__OS_WIN), SDT_BIN, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 2 )\
    _MAKE(150, "wke_Utf8ToAnsi", wke_U2A, "把utf8编码的文本转换成ansi编码的文本,成功返回转换后的文本,失败返回空文本。", 2, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 1 )\
    _MAKE(151, "wke_Utf8ToUnicode", wke_U2W, "把utf8编码的文本转换成Unicode编码的文本,成功返回转换后的Unicode字节集,失败返回空字节集。", 2, _CMD_OS(__OS_WIN), SDT_BIN, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 1 )\
    _MAKE(152, "wke_UnicodeToAnsi", wke_W2A, "把Unicode编码的文本转换成ansi编码的文本,成功返回转换后的文本,失败返回空文本。", 2, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 3 )\
    _MAKE(153, "wke_UnicodeToUtf8", wke_W2U, "把Unicode编码的文本转换成utf8编码的文本,成功返回转换后的文本,失败返回空文本。", 2, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 3 )\
    _MAKE(154, "延时回收垃圾", wkeGC, "延迟让miniblink垃圾回收。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 12)\
    _MAKE(155, "wke_取版本号", wke_GetVersion, "获取目前api版本号。", 1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0)\
    _MAKE(156, "wke_取版本文本", wke_GetVersionString, "获取版本字符串。", 1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 0, 0)\
    _MAKE(157, "置用户数据", wke_SetUserKeyValue, "把数据和webView绑定。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 13)\
    _MAKE(158, "取用户数据", wke_GetUserKeyValue, "取出 置用户数据() 设置的值。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 15)\
    _MAKE(159, "取网页句柄", wke_GetWindowHandle, "取出 miniblink 的窗口句柄。", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0)\
    _MAKE(160,  "取对象属性", wke_GetObjectProp, "取指定对象的属性JSValue 请使用相应转换命令得到最终结果，如果object不是正确的类型，则返回jsUndefined。本命令为高级对象成员命令。", -1, _CMD_OS(__OS_WIN) , SDT_INT64, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 61 )\
    _MAKE(161,  "设置Cookie_单条_此命令已弃用_请调用_设置cookie_CURL_来设置_设置cookie_CURL是node_dll提供的接口_没有任何二次封装", wke_SetSingleCookie, "支持库不提供任何针对cookie进行二次封装的命令, 所有cookie相关的命令都是原封调用node.dll\r\n""        设置cookie请调用 设置cookie_CURL(), 该命令原封调用node.dll的wkeSetCookie接口\r\n", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 16 )\
    _MAKE(162,  "文档_取横向滚动条位置", wke_DocGetScollX, "获取横向滚动条位置。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0 )\
    _MAKE(163,  "表单_Input选择框取选中状态", wke_Input_GetCheckBoxState, "取选择框选中状态。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0 )\
    _MAKE(164,  "表单_Input单选框取选中状态", wke_Input_GetRadioChecked, "取单选框选中状态。", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0 )\
    _MAKE(165,  "表单_Input组合框取选中项", wke_Input_GetComboxIndex, "取组合框选中项索引。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0 )\
    _MAKE(166,  "清除所有cookie", wke_clearCookie, "清除当前wke的所有cookie。", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(167,  "获取请求头数据", wke_NetGetRawHttpHead, "获取发送的请求头的数据。", -1, _CMD_OS(__OS_WIN) | CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 59 )\
    _MAKE(168,  "允许新窗打开", wke_IsEnableNewWnd, "不设置默认为假,都在本窗口打开,不触发 \"即将导航到新窗口\" 事件\r\n"\
                "    为真时会触发 \"即将导航到新窗口\" 事件\r\n"\
                "    如果网页用js hook了点击事件,然后用window.open打开,那么 禁止新窗打开() 对这个无效,禁止后还是会弹出新窗口\r\n"\
                "    不需要新窗口打开的可以在 即将导航到新窗口 事件下返回 \"假\",不让他弹出\r\n"\
                "    为空则取当前状态, 不为空时返回值无意义。\r\n", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 18 )\
    _MAKE(169,  "表单_取表单数量", wke_GetFormLength, "获取指定框架下的所有form表单个数,只有表单才会计数。", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb)\
    _MAKE(170,  "wke_取CPU占用", wke_GetCpu, "取自进程CPU占用率,用于测试挂机记录程序运行状态。\r\n""【请注意】该功能是测试功能,会根据用户需求决定是否删除该命令", 1, _CMD_OS(__OS_WIN), SDT_DOUBLE, 0, LVL_SIMPLE, 0, 0, 2, g_Args_All + 4)\
    _MAKE(171,  "截图", wke_screenshot, "截图指定区域或者整个浏览器", -1, _CMD_OS(__OS_WIN), SDT_BIN, 0, LVL_SIMPLE, 0, 0, 4, g_Args_jywebkit + 19)\
    _MAKE(172,  "取请求模式", wke_NetGetRequestMethod, "返回当前的请求模式, 请使用 #请求模式_ 开头的常量\r\n""无法修改post数据,只能取", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 60)\
    _MAKE(173,  "取post数据", wke_NetGetPostBody, "获取post数据", -1, _CMD_OS(__OS_WIN), SDT_TYPE_POSTELEMENTS, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 60)\
    _MAKE(174,  "创建post数据", wke_NetCreatePostBodyElement, "创建单条post数据", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_BOOL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 61)\
    _MAKE(175,  "释放post数据", wke_NetFreePostBodyElement, "【传入的必须是 创建post数据()】 返回的值", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 63)\
    _MAKE(176,  "创建post数据组", wke_NetCreatePostBodyElements, "创建一个新的post数据组,记得不用时自己调用 特殊功能.释放post数据组() 来释放", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 61)\
    _MAKE(177,  "释放post数据组", wke_NetFreePostBodyElements, "【传入的必须是 创建post数据组()】 返回的值\r\n在[Url载入开始]事件里判断是post时，可以通过 特殊功能.创建post数据组() 来创建一个新的post数据包。""然后调用 特殊功能.释放post数据组() 来释放原post数据。", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 62)\
    _MAKE(178,  "异步请求", wke_NetHoldJobToAsynCommit, "高级用法。在[Url载入开始]回调里调用。 有时候，[Url载入开始]事件里拦截到一个请求后，"\
            "不能马上判断出结果。此时可以调用本接口，然后在 异步的某个时刻，调用 特殊功能.继续请求() 来让此请求继续进行\r\n"\
            "返回真代表成功，假代表调用失败，不能再调用 特殊功能.继续请求() 了", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 60)\
    _MAKE(179,  "继续请求", wke_NetContinueJob, "高级用法。配合 特殊功能.异步请求() 使用", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 60)\
    _MAKE(180,  "取网页文本", wke_GetInnerText, "取指定框架指定元素或者取整个html的文本,不包含html标记", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_jywebkit + 23)\
    _MAKE(181,  "元素_取子元素数量", GetElementCount, "取指定元素的子元素数量", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(182,  "附加", Attach, "将一个webView附加到本对象中,附加后可以使用本对象的任何方法, 成功返回真, 失败返回假", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 27 )\
    _MAKE(183, "新窗口构造函数", newWndIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(184, "新窗口复制构造函数", newWndCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_COPY_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(185, "新窗口析构函数", newWndDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_FREE_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(186, "是否已创建", newWndIsCreate, "", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(187, "销毁", wke_DestroyWebView, "用于销毁新弹出的窗口", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0)\
    _MAKE(188, "设置cookie_CURL", wke_SetCookieCURL, "调用node.dll的 wkeSetCookie, 不对参数做任何修改, 支持库所有cookie相关的命令都是原封调用node.dll, 不会做任何修改", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 28)\
    _MAKE(189,  "模拟硬件设备环境", wke_SetDeviceParameter, "设置mb模拟的硬件设备环境。主要用在伪装手机设备场景", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 4, g_Args_jywebkit + 30 )\
    _MAKE(190,  "挂接事件", wke_Event, "根据事件类型挂接不同的事件, 事件类型请使用 浏览器事件_ 开头的常量", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_jywebkit + 34 )\
    _MAKE(191,  "获取所有Cookie", wke_GetAllCookie, "通过访问器visitor访问所有cookie", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 2, g_Args_jywebkit + 37 )\
    _MAKE(192,  "备用命令", wke_format_1, "c/c++里的格式化字符串", 1, _CMD_OS(__OS_WIN) | CT_ALLOW_APPEND_NEW_ARG | CT_IS_HIDED, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 39 )\
    _MAKE(193,  "生成字符串", wke_makeString, "生成字符串, 把所有能转换到文本的类型都转成文本并连接在一起, 暂时没处理日期时间型和数组", 1, _CMD_OS(__OS_WIN) | CT_ALLOW_APPEND_NEW_ARG, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 40 )\
    _MAKE(194,  "赋值", wke_assign, "把另一个 WKE_填表 内部的数据赋值到当前 WKE_填表 里", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 47 )\
    _MAKE(195,  "清空", wke_clear, "清空当前 WKE_填表内的数据", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(196,  "获取响应头", wke_NetGetRawResponseHead, "获取原始响应头, 在 Url载入结束 事件中使用", -1, _CMD_OS(__OS_WIN) | CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 9 )\
    _MAKE(197,  "post", wke_PostURL, "post", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 65 )\
    _MAKE(198,  "清除cookie", wke_ClearCookie, "清除cookie", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(199,  "取编辑框游标位置", wke_GetCaretRect, "获取编辑框的那个游标的位置", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0 )\
    _MAKE(200,  "获取请求MIME类型", wke_NetGetMIMEType, "在 URL载入开始 事件里调用, 表示设置http请求的MIME type", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 9 )\
    _MAKE(201,  "获取HTTP头字段信息", wke_NetGetHTTPHeaderField, "在 URL载入开始 事件里调用, 表示设置http请求（或者file:///协议）的 http header field", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 68 )\
    _MAKE(202,  "获取响应HTTP头字段信息", wke_NetGetHTTPHeaderFieldFromResponse, "在 URL载入结束 事件里调用", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 68 )\
    _MAKE(203,  "取网页图标", wke_NetGetFavicon, "必须在 文档载入完毕 事件里调用", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(204,  "取参数类型", wke_jsArgType, "取参数类型", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_JavaScript + 64 )\
    _MAKE(205,  "取参数值", wke_jsArg, "取参数值", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_SIMPLE, 0, 0, 2, g_Args_JavaScript + 64 )\
    _MAKE(206,  "是否为数值", wke_jsIsNumber, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(207,  "是否为字符串", wke_jsIsString, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(208,  "是否为逻辑值", wke_jsIsBoolean, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(209,  "是否为对象", wke_jsIsObject, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(210,  "是否为函数", wke_jsIsFunction, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(211,  "是否为Undefined", wke_jsIsUndefined, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(212,  "是否为空", wke_jsIsNull, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(213,  "是否为数组", wke_jsIsArray, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(214,  "是否为真", wke_jsIsTrue, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(215,  "是否为假", wke_jsIsFalse, "判断值对象是否为该类型", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(216,  "创建", wke_Create, "创建一个浏览框, 创建成功返回窗口句柄, 失败返回0, 窗口句柄和webView是不一样的, 请严格传递参数", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 6, g_Args_jywebkit + 54 )\
    _MAKE(217,  "消息循环", wke_MessageLoop, "消息循环, 如果没有创建窗口则返回假, 否则直到窗口收到 WM_QUIT 消息时此方法才返回真", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 51 )\
    _MAKE(218,  "wke_消息循环", wke_MsgLoop, "消息循环, 在窗口创建完毕事件下调用, 调用此命令后直到调用wke_取消循环() 才返回, 窗口销毁时需要调用 wke_取消循环(), 否则程序无法退出\r\n"\
                                                "此方法是为了处理web浏览器组件无法按tab键切换焦点的问题,"\
                                                "\r\n【注意】调用此方法后不会走易语言的消息循环, 按tab键后不会自动切组件换焦点, 同时组件能收到tan键按下放开消息", 0, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 52 )\
    _MAKE(219,  "wke_取消循环", wke_CancelMsgLoop, "取消消息循环, 取消后才能使 wke_消息循环() 返回, 此命令会调用PostQuitMessage", 0, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(220,  "取wke窗口句柄", wke_GetWindow, "取当前wke的窗口句柄", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(221,  "置调试信息", wke_SetDebugConfig, "置调试信息", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 3, g_Args_SpecialFunction + 24 )\
    _MAKE(222,  "wke_格式化文本", wke_format, "利用c函数 sprintf来实现, 此命令不对参数进行校验", 1, _CMD_OS(__OS_WIN) | CT_ALLOW_APPEND_NEW_ARG, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_All + 6 )\
    _MAKE(223,  "wke_格式化文本W", wke_formatW, "利用c函数 swprintf来实现, Unicode版, 此命令不对参数进行校验", 1, _CMD_OS(__OS_WIN) | CT_ALLOW_APPEND_NEW_ARG, SDT_BIN, 0, LVL_SIMPLE, 0, 0, 2, g_Args_All + 6 )
