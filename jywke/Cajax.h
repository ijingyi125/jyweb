#pragma once
#include "pch.h"
#include "wke/wke.h"
#include "wke/MbE.h"

typedef __int64 ( CALLBACK* ajax_userFunc )( jsExecState es, int nArgCount );
typedef void ( CALLBACK* ajax_callE )( LPCSTR str );
struct _jsDataEx : public jsData
{
    ajax_userFunc userfunc;
};

class Cajax
{
#define AjaxGetModel "var xhr = new XMLHttpRequest();xhr.open('{method}', '{url}', true);"\
"{HttpHeader}xhr.onreadystatechange = function () {if (xhr.readyState == 4) {"\
"if (xhr.status == 200 || xhr.status == 304) {ajaxFun(xhr.responseText);} else {"\
"ajaxFun(xhr.status);}}};xhr.send({data});"

#define SETHTTPHEADER  "xhr.setRequestHeader(\"{key}\", \"{value}\");"

private:
    _str _header;

public:
	inline void SetHttpHeader(LPSTR key, LPSTR value)
	{
        _str tmp = SETHTTPHEADER;

        int nPos = 0;

        tmp.replace("{key}", key);
        tmp.replace("{value}", value);

        _header = _header + tmp + "\r\n";
	}
    inline void Get(wkeWebView webView, LPSTR url, ajax_userFunc callback)
    {
        _str str = AjaxGetModel;
        const _str method("GET");
        const _str data("");

        str.replace("{url}", url);
        str.replace("{method}", method);
        str.replace("{data}", data);
        str.replace("{HttpHeader}", _header);

        _header = "";
        jsFun(webView, str, (jsValue)callback, ajax_get, "callbackGet");
    }
	inline void Post(wkeWebView webView, LPSTR url, BOOL isJson, LPSTR data, ajax_userFunc callback)
    {
        if ( isJson )
        {
            if ( _header.find("application/Json") == -1 )
            {
                SetHttpHeader("Content-Type", "application/Json");
            }
        }
        else
        {
            if ( _header.find("application/x-www-form-urlencoded") == -1 )
            {
                SetHttpHeader("Content-Type", "application/x-www-form-urlencoded");
            }
        }


        _str str = AjaxGetModel;

        const _str method("POST");
        _str szData = data;

        str.replace("{url}", url);
        str.replace("{method}", method);
        if ( szData != "" )
        {
            szData = _str("'") + szData + "'";
        }
        str.replace("{data}", szData);
        str.replace("{HttpHeader}", _header);

        _header = "";

        jsFun(webView, str, (jsValue)callback, ajax_post, "callbackPOST");

    }

private:

    static void jsFun(wkeWebView webView, _str js, jsValue callback, ajax_userFunc fun, LPCSTR prop)
    {
        jsExecState es = wkeGlobalExec(webView);

        _jsDataEx* _jsData = new _jsDataEx;
        memset(_jsData, 0, sizeof(_jsDataEx));
        strcpy(_jsData->typeName, "Function");

        _jsData->callAsFunction = __ajaxCallAsFunctionCallback;
        _jsData->finalize       = __ajaxFinalizeCallback;
        _jsData->propertyGet    = __ajaxGetPropertyCallback;
        _jsData->propertySet    = __ajaxSetPropertyCallback;
        _jsData->userfunc       = fun;

        jsValue fn = jsFunction(es, (jsData*)_jsData);
        jsSetGlobal(es, "ajaxFun", fn);
        jsSetGlobal(es, prop, jsInt((int)callback));

        wstr jsW = js.a2w();
        jsValue vl = wkeRunJSW(webView, jsW.c_str());
        vl = 0;
    }

    static INT64 CALLBACK ajax_get(jsExecState es, int nArgCount)
    {
        jsValue vl = jsArg(es, 0);
        LPCSTR szStr = jsToTempString(es, vl);

        vl = jsGetGlobal(es, "callbackGet");
        ajax_callE callE = (ajax_callE)jsToInt(es, vl);
        callE(szStr);
        //int callE = jsToInt(es, vl);
        //__asm
        //{
        //	push szStr
        //	call callE
        //}
        return 0;
    }

    static INT64 CALLBACK ajax_post(jsExecState es, int nArgCount)
    {
        jsValue vl = jsArg(es, 0);
        LPCSTR szStr = jsToTempString(es, vl);

        vl = jsGetGlobal(es, "callbackPOST");
        ajax_callE callE = (ajax_callE)jsToInt(es, vl);
        callE(szStr);
        //int callE = jsToInt(es, vl);
        //__asm
        //{
        //	push szStr
        //	call callE
        //}

        return 0;
    }


    static jsValue __ajaxGetPropertyCallback(jsExecState es, jsValue object, const char* propertyName)
    {
        return 0;
    }
    static bool __ajaxSetPropertyCallback(jsExecState es, jsValue object, const char* propertyName, jsValue value)
    {
        return false;
    }
    static jsValue __ajaxCallAsFunctionCallback(jsExecState es, jsValue object, jsValue* args, int argCount)
    {
        _jsDataEx* data = (_jsDataEx*)jsGetData(es, object);
        if ( data->userfunc != NULL && strcmp(data->typeName, "Function") == 0 )
        {
            return data->userfunc(es, argCount);
        }
        return 0;
    }
    static void __ajaxFinalizeCallback(struct tagjsData* data)
    {
        //TODO 销毁时会触发这个函数,如果在前面释放,那就会找不到这个函数而导致程序崩溃,前面调用几次这里会触发几次
        _jsDataEx* pData = (_jsDataEx*)data;
        delete pData;
    }

};

