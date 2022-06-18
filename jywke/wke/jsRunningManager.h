#pragma once
#include "MbECommon.h"

class ValueType
{
public:
    union paramValue
    {
        const char* str;
        int		num;
        double	   number;
        bool	boolean;
    };

    enum ArgType
    {
        TEXT,
        INT,
        DOUBULE,
        BOOL
    };

    paramValue	param;
    ArgType	type;
};

class jsRunningManager
{
public:
    jsRunningManager() :m_webView(0) { }
    ~jsRunningManager() { }

    void	SetWebView(wkeWebView webview) { m_webView = webview; }

    /*
    获取页面主frame的jsExecState。jsExecState是什么，见下述。
    这是很重要的一个方法，用它能够取得当前webview的jses。
    */
    inline jsExecState  GetJsExec() { return wkeGlobalExec(m_webView); }

    //运行一段js。返回js的值jsValue。jsValue是个封装了内部v8各种类型的类，如果需要获取详细信息，有jsXXX相关接口可以调用。见下述
    //注意:执行的js，也就是script，是在一个闭包中
    inline jsValue RunJS(const utf8* script) { return wkeRunJS(m_webView, script); }
    inline jsValue RunJSW(const wchar_t* script) { return wkeRunJSW(m_webView, script); }

    inline static jsValue RunJs(wkeWebView view, const utf8* script) { return wkeRunJS(view, script); }
    inline static jsValue RunJSW(wkeWebView view, const wchar_t* script) { return wkeRunJSW(view, script); }

    //运行js在指定的frame上，通过frameId
    //参数：isInClosure表示是否在外层包个function() {}形式的闭包
    //注意：如果需要返回值，在isInClosure为true时，需要写return，为false则不用
    inline jsValue RunJsByFrame(wkeWebFrameHandle frameId, const utf8* script, bool isInClosure) { return wkeRunJsByFrame(m_webView, frameId, script, isInClosure); }

    //////////////////////////////////////////////////////////////////////////

    //获取es里存的参数个数。一般是在绑定的js调用c++回调里使用，判断js传递了多少参数给c++
    inline int GetArgCount() { return jsArgCount(GetJsExec()); }
    inline static int GetArgCount(jsExecState es) { return jsArgCount(es); }

    //判断第argIdx个参数的参数类型。argIdx从是个0开始计数的值。如果超出jsArgCount返回的值，将发生崩溃
    inline jsType GetArgType(int argidx) { return jsArgType(GetJsExec(), argidx); }
    inline static jsType GetArgType(jsExecState es, int argidx) { return jsArgType(es, argidx); }

    //获取第argIdx对应的参数的jsValue值。
    inline jsValue GetArg(int argidx) { return jsArg(GetJsExec(), argidx); }
    inline static jsValue GetArg(jsExecState es, int argidx) { return jsArg(es, argidx); }

    //////////////////////////////////////////////////////////////////////////

    //获取v对应的类型。
    inline jsType TypeOf(jsValue v) { return jsTypeOf(v); }

    inline bool IsNumber(jsValue v) { return jsIsNumber(v); }

    inline bool IsString(jsValue v) { return jsIsString(v); }

    inline bool IsBoolean(jsValue v) { return jsIsBoolean(v); }

    //当v不是数字、字符串、undefined、null、函数的时候，此接口返回true
    inline bool IsObject(jsValue v) { return jsIsObject(v); }

    //如果v是个整形或者浮点，返回相应值（如果是浮点，返回取整后的值）。如果是其他类型，返回0（这里注意）
    inline int ToInt(jsValue v) { return jsToInt(GetJsExec(), v); }
    inline static int ToInt(jsExecState es, jsValue v) { return jsToInt(es, v); }

    //如果v是个浮点形，返回相应值。如果是其他类型，返回0.0（这里注意）
    inline double ToDouble(jsValue v) { return jsToDouble(GetJsExec(), v); }
    inline static double ToDouble(jsExecState es, jsValue v) { return jsToDouble(es, v); }

    //如果v是个字符串，返回相应值。如果是其他类型，返回L""（这里注意） 另外，返回的字符串不需要外部释放。mb会在下一帧自动释放
    inline const utf8* ToTempString(jsValue v) { return jsToTempString(GetJsExec(), v); }
    inline static const utf8* ToTempString(jsExecState es, jsValue v) { return jsToTempString(es, v); }

    inline const wchar_t* ToTempStringW(jsValue v) { return jsToTempStringW(GetJsExec(), v); }
    inline static const wchar_t* ToTempStringW(jsExecState es, jsValue v) { return jsToTempStringW(es, v); }

    //////////////////////////////////////////////////////////////////////////

    jsValue GetValue(const char* prop, jsValue obj = NULL);

    ValueType jsValue2ValueType(jsValue val);
    jsValue CallJsFunc(const char* funcName, ValueType* params, int argCount, jsValue obj = NULL);

public:
    //绑定C++方法的时候，必须在创建webView之前，如果在之后可能会设置失败。
    static void BindJsFunc(const char* funcName, wkeJsNativeFunction fn, void* param, int nArgCount)
    {
        wkeJsBindFunction(funcName, fn, param, nArgCount);
    }

private:
    wkeWebView m_webView;
};
