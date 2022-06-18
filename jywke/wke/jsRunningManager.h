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
    ��ȡҳ����frame��jsExecState��jsExecState��ʲô����������
    ���Ǻ���Ҫ��һ�������������ܹ�ȡ�õ�ǰwebview��jses��
    */
    inline jsExecState  GetJsExec() { return wkeGlobalExec(m_webView); }

    //����һ��js������js��ֵjsValue��jsValue�Ǹ���װ���ڲ�v8�������͵��࣬�����Ҫ��ȡ��ϸ��Ϣ����jsXXX��ؽӿڿ��Ե��á�������
    //ע��:ִ�е�js��Ҳ����script������һ���հ���
    inline jsValue RunJS(const utf8* script) { return wkeRunJS(m_webView, script); }
    inline jsValue RunJSW(const wchar_t* script) { return wkeRunJSW(m_webView, script); }

    inline static jsValue RunJs(wkeWebView view, const utf8* script) { return wkeRunJS(view, script); }
    inline static jsValue RunJSW(wkeWebView view, const wchar_t* script) { return wkeRunJSW(view, script); }

    //����js��ָ����frame�ϣ�ͨ��frameId
    //������isInClosure��ʾ�Ƿ���������function() {}��ʽ�ıհ�
    //ע�⣺�����Ҫ����ֵ����isInClosureΪtrueʱ����Ҫдreturn��Ϊfalse����
    inline jsValue RunJsByFrame(wkeWebFrameHandle frameId, const utf8* script, bool isInClosure) { return wkeRunJsByFrame(m_webView, frameId, script, isInClosure); }

    //////////////////////////////////////////////////////////////////////////

    //��ȡes���Ĳ���������һ�����ڰ󶨵�js����c++�ص���ʹ�ã��ж�js�����˶��ٲ�����c++
    inline int GetArgCount() { return jsArgCount(GetJsExec()); }
    inline static int GetArgCount(jsExecState es) { return jsArgCount(es); }

    //�жϵ�argIdx�������Ĳ������͡�argIdx���Ǹ�0��ʼ������ֵ���������jsArgCount���ص�ֵ������������
    inline jsType GetArgType(int argidx) { return jsArgType(GetJsExec(), argidx); }
    inline static jsType GetArgType(jsExecState es, int argidx) { return jsArgType(es, argidx); }

    //��ȡ��argIdx��Ӧ�Ĳ�����jsValueֵ��
    inline jsValue GetArg(int argidx) { return jsArg(GetJsExec(), argidx); }
    inline static jsValue GetArg(jsExecState es, int argidx) { return jsArg(es, argidx); }

    //////////////////////////////////////////////////////////////////////////

    //��ȡv��Ӧ�����͡�
    inline jsType TypeOf(jsValue v) { return jsTypeOf(v); }

    inline bool IsNumber(jsValue v) { return jsIsNumber(v); }

    inline bool IsString(jsValue v) { return jsIsString(v); }

    inline bool IsBoolean(jsValue v) { return jsIsBoolean(v); }

    //��v�������֡��ַ�����undefined��null��������ʱ�򣬴˽ӿڷ���true
    inline bool IsObject(jsValue v) { return jsIsObject(v); }

    //���v�Ǹ����λ��߸��㣬������Ӧֵ������Ǹ��㣬����ȡ�����ֵ����������������ͣ�����0������ע�⣩
    inline int ToInt(jsValue v) { return jsToInt(GetJsExec(), v); }
    inline static int ToInt(jsExecState es, jsValue v) { return jsToInt(es, v); }

    //���v�Ǹ������Σ�������Ӧֵ��������������ͣ�����0.0������ע�⣩
    inline double ToDouble(jsValue v) { return jsToDouble(GetJsExec(), v); }
    inline static double ToDouble(jsExecState es, jsValue v) { return jsToDouble(es, v); }

    //���v�Ǹ��ַ�����������Ӧֵ��������������ͣ�����L""������ע�⣩ ���⣬���ص��ַ�������Ҫ�ⲿ�ͷš�mb������һ֡�Զ��ͷ�
    inline const utf8* ToTempString(jsValue v) { return jsToTempString(GetJsExec(), v); }
    inline static const utf8* ToTempString(jsExecState es, jsValue v) { return jsToTempString(es, v); }

    inline const wchar_t* ToTempStringW(jsValue v) { return jsToTempStringW(GetJsExec(), v); }
    inline static const wchar_t* ToTempStringW(jsExecState es, jsValue v) { return jsToTempStringW(es, v); }

    //////////////////////////////////////////////////////////////////////////

    jsValue GetValue(const char* prop, jsValue obj = NULL);

    ValueType jsValue2ValueType(jsValue val);
    jsValue CallJsFunc(const char* funcName, ValueType* params, int argCount, jsValue obj = NULL);

public:
    //��C++������ʱ�򣬱����ڴ���webView֮ǰ�������֮����ܻ�����ʧ�ܡ�
    static void BindJsFunc(const char* funcName, wkeJsNativeFunction fn, void* param, int nArgCount)
    {
        wkeJsBindFunction(funcName, fn, param, nArgCount);
    }

private:
    wkeWebView m_webView;
};
