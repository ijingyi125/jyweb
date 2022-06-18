#include "wke_typedef.h"
#include "WKECtrl.h"

// javascript�������ʵ���ļ�




// ���ø�ʽ: _SDT_NULL (Javascript).JS��ʼ��, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(27, JSIntialize)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// ���ø�ʽ: _SDT_NULL (Javascript).JS��ֵ, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(28, JSCopy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// ���ø�ʽ: _SDT_NULL (Javascript).JS����, ����˵��: NULL
// �޲���
EXTERN_C void WKE_NAME(29, JSDestroy)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// ���ø�ʽ: _SDT_NULL (Javascript).��������, ����˵��: "wke_JSGC , �������ա�"
// �޲���
EXTERN_C void WKE_NAME(30, JSGC)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	jsGC();
}

// ���ø�ʽ: SDT_INT (Javascript).ȡ����, ����˵��: "��ȡJS��������,����ִ�н������ ����ֵ�ο� #JS����_ ��صĳ�����"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(31, wke_GetType)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

	jsType nRet = jsTypeOf((jsValue)pArgInf[1].m_int64);
	pRetData->m_dtDataType = SDT_INT;
	pRetData->m_int = nRet;
}

// ���ø�ʽ: SDT_INT64 (Javascript).ָ���������JS, ����˵��: "ָ���������JS��"
// ����<1>: webView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ID SDT_INT, ����˵��: "���ID"
// ����<3>: script SDT_TEXT, ����˵��: "javascript�ű�"
// ����<4>: �Ƿ������Function��ִ�� SDT_BOOL, ����˵��: "script�������mb�ڲ��Զ���������һ��function(){}�С�����ʹ�õı����ᱻ����,�˴�ȷ���Ƿ������function��"
EXTERN_C void WKE_NAME(32, wke_RunJsByFrame)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	jsValue value = wkeRunJsByFrame((wkeWebView)pArgInf[1].m_int, (wkeWebFrameHandle)pArgInf[2].m_int, (LPCSTR)pArgInf[3].m_pText, (bool)pArgInf[4].m_bool);
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = value;
}

// ���ø�ʽ: SDT_TEXT (Javascript).����JS_�ı�_�ѷ���, ����˵��: "����javascript�ű�,�з���ֵ�򷵻���Ӧ���,���򷵻ؿ��ı���"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: script SDT_TEXT, ����˵��: "�����еĽű�"
// ����<3>: �Ƿ��з���ֵ SDT_BOOL, ����˵��: "JS�Ƿ��з���ֵ"
EXTERN_C void WKE_NAME(33, wke_RunJsToStr)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_TEXT;
	pRetData->m_pText = 0;
}

// ���ø�ʽ: SDT_INT64 (Javascript).����JS_ֵ����, ����˵��: "����javascript�ű�,�������н��ָ��(JsVlaue,ֵ����),��ȡ���Ľ����Ҫʹ�� ȡ�����_xx ������ȡֵ��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: script SDT_TEXT, ����˵��: "�����еĽű�"
EXTERN_C void WKE_NAME(34, wke_RunJsToJsValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wstr szScript = wstr::A2W(pArgInf[2].m_pText);
	jsValue value = wkeRunJSW((wkeWebView)pArgInf[1].m_int, szScript.c_str());
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = value;
}

// ���ø�ʽ: SDT_TEXT (Javascript).������ʽ_�ı�, ����˵��: "ʹ��eval��������js���ʽ,�����ı��ͽ�� mb�ڲ��Զ���������һ��function(){}�С�����ʹ�õı����ᱻ���� Ҫ��ȡ����ֵ����дreturn��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
// ����<2>: ���ʽ SDT_TEXT, ����˵��: "������ı��ʽ"
// ����<3>: �Ƿ��з���ֵ SDT_BOOL, ����˵��: "JS�Ƿ��з���ֵ"
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

// ���ø�ʽ: SDT_INT64 (Javascript).������ʽ_ֵ����, ����˵��: "ʹ��eval��������js���ʽ,�������н��ָ��(JsVlaue,ֵ����),��ȡ���Ľ����Ҫʹ�� ȡ�����_xx ������ȡֵ mb�ڲ��Զ���������һ��function(){}�С�����ʹ�õı����ᱻ���롣"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ"
// ����<2>: ���ʽ SDT_TEXT, ����˵��: "������ı��ʽ"
EXTERN_C void WKE_NAME(36, wke_Eval_JsValue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wstr wzStr = wstr::A2W(pArgInf[2].m_pText);
	jsValue value = jsEvalW((jsExecState)pArgInf[1].m_int, wzStr.c_str());
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = value;
}

// ���ø�ʽ: SDT_INT (Javascript).ȡJSִ��״̬, ����˵��: "��ȡָ��view��JSִ��״̬,�󲿷���Ҫ��ȡ����ֵ��JS��������Ҫ��״̬��"
// ����<1>: WebView SDT_INT, ����˵��: "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ"
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

// ���ø�ʽ: SDT_INT64 (Javascript).��JS����ָ��, ����˵��: "���������е��ӳ���ת����JS���õķ���ָ�롣"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ"
// ����<2>: ��ת���ӳ��� SDT_SUB_PTR, ����˵��: "�������е��ӳ���ָ��"
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

// ���ø�ʽ: SDT_INT64 (Javascript).ȡȫ�ֶ�������, ����˵��: "ȡȫ�ֶ�������JSValue ��ʹ����Ӧת������õ����ս����"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ"
// ����<2>: �������� SDT_TEXT, ����˵��: "������������"
EXTERN_C void WKE_NAME(39, wke_GetGlobalObject)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsValue value = jsGetGlobal((jsExecState)pArgInf[1].m_int, pArgInf[2].m_pText);
	pRetData->m_dtDataType = SDT_INT64;
	pRetData->m_int64 = value;
}

// ���ø�ʽ: _SDT_NULL (Javascript).��ȫ�ֶ�������, ����˵��: "Ϊָ��ȫ�ֶ�����������ֵ,�����ں�����,ȫ�ֱ�����ֵ�ȵȡ�"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ"
// ����<2>: �������� SDT_TEXT, ����˵��: "������������"
// ����<3>: ����ֵ SDT_INT64, ����˵��: "������������"
EXTERN_C void WKE_NAME(40, wke_SetGlobalObject)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsSetGlobal((jsExecState)pArgInf[1].m_int, pArgInf[2].m_pText, (jsValue)pArgInf[3].m_int64);
}

// ���ø�ʽ: SDT_INT64 (Javascript).����ȫ�ֺ���, ����˵��: "����jsȫ�ֺ�����"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ"
// ����<2>: js���� SDT_INT64, ����˵��: "js����"
// ����<3>: [�������� ���� SDT_INT64], ����˵��: "����Ĳ�������"
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

// ���ø�ʽ: SDT_INT64 (Javascript).���ö�����, ����˵��: "����jsȫ�ֺ���,����ָ��this��"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ"
// ����<2>: js���� SDT_INT64, ����˵��: "js����"
// ����<3>: this���� SDT_INT64, ����˵��: "������this����"
// ����<4>: [�������� ���� SDT_INT64], ����˵��: "����Ĳ�������"
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

// ���ø�ʽ: _SDT_NULL (Javascript).ȡȫ�ֶ���, ����˵��: "ȡȫ�ֶ���,window��"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ"
EXTERN_C void WKE_NAME(43, wke_GetGlobal)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsGlobalObject((jsExecState)pArgInf[1].m_int);
}

typedef __int64 (CALLBACK* CALLFUNC)(int);

jsValue NativeCallBackFunc(jsExecState es, void* param)
{
	//MessageBox(0, "NativeCallBackFunc", "N", MB_OK);
	//param �Ǵ��ݹ������������ӳ���ָ�롣

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

// ���ø�ʽ: _SDT_NULL (Javascript).���ӳ���, ����˵��: "JS�еĺ������������ӳ�����а�,��JS�к���������ʱ����Զ��ص��������е��ӳ���,��������Ӧ�Ĳ�����"
// ����<1>: Js�������� SDT_TEXT, ����˵��: "js�к���������"
// ����<2>: �������ӳ���ָ�� SDT_SUB_PTR, ����˵��: "�������е��ӳ���ָ�롣 ���ӳ�����һ���������Ͳ�������ʾjs�����������س������͡���������򷵻�ֵ���󣬳��򽫻��������"
// ����<3>: �������� SDT_INT, ����˵��: "����Ĳ�������"
EXTERN_C void WKE_NAME(44, wke_BindFunc)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
	//char szLog[1024] = { 0 };
	//sprintf(szLog, "wke_BindFunc\nNativeCallBackFunc:%d , threadId:%d", NativeCallBackFunc, ::GetCurrentThreadId());

	//MessageBox(0, szLog, pArgInf[1].m_pText, MB_OK);

	wkeJsBindFunction(pArgInf[1].m_pText, NativeCallBackFunc, (void*)(pArgInf[2].m_dwSubCodeAdr), pArgInf[3].m_int);
}

// ���ø�ʽ: SDT_INT (Javascript).ȡ��������, ����˵��: "ȡ�ص���������������"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬,�ص�������һ������"
EXTERN_C void WKE_NAME(45, wke_ParamsCount)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT;
	pRetData->m_int = jsArgCount((jsExecState)(pArgInf[1].m_int));
}



// ���ø�ʽ: SDT_INT (Javascript).ȡ�����Ͳ���, ����˵��: "�����Ͳ���ȡֵ��"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬,�ص�������һ������"
// ����<2>: ������� SDT_INT, ����˵��: "�����±�,��0��ʼ����"
EXTERN_C void WKE_NAME(46, wke_ParamToInt)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

    pRetData->m_dtDataType = SDT_INT;
    jsValue val = jsArg((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int);
    pRetData->m_int = jsToInt((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int);
}

// ���ø�ʽ: SDT_TEXT (Javascript).ȡ�ı��Ͳ���, ����˵��: "�ı��Ͳ���ȡֵ��"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬,�ص�������һ������"
// ����<2>: ������� SDT_INT, ����˵��: "�����±�,��0��ʼ����"
EXTERN_C void WKE_NAME(47, wke_ParamToText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str str;
    pRetData->m_dtDataType = SDT_TEXT;
    jsValue val = jsArg((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int);
    const wchar_t* pWchar = jsToTempStringW((jsExecState)( pArgInf[1].m_int ), val);
    str = wstr::W2A((LPWSTR)pWchar);
    pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_BOOL (Javascript).ȡ�߼��Ͳ���, ����˵��: "�߼��Ͳ���ȡֵ��"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬,�ص�������һ������"
// ����<2>: ������� SDT_INT, ����˵��: "�����±�,��0��ʼ����"
EXTERN_C void WKE_NAME(48, wke_ParamToBool)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_BOOL;
    pRetData->m_bool = jsToBoolean((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// ���ø�ʽ: SDT_FLOAT (Javascript).ȡС���Ͳ���, ����˵��: "С���Ͳ���ȡֵ��"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬,�ص�������һ������"
// ����<2>: ������� SDT_INT, ����˵��: "�����±�,��0��ʼ����"
EXTERN_C void WKE_NAME(49, wke_ParamToFloat)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_FLOAT;
    pRetData->m_float = jsToFloat((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// ���ø�ʽ: SDT_DOUBLE (Javascript).ȡ˫����С���Ͳ���, ����˵��: "˫����С���Ͳ���ȡֵ��"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬,�ص�������һ������"
// ����<2>: ������� SDT_INT, ����˵��: "�����±�,��0��ʼ����"
EXTERN_C void WKE_NAME(50, wke_ParamToDouble)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_DOUBLE;
    pRetData->m_double = jsToDouble((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// ���ø�ʽ: SDT_INT (Javascript).ȡִ�н��������, ����˵��: "ȡ�����͵�ִ�н����"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬"
// ����<2>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(51, wke_ResultToInt)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT;
    pRetData->m_int = jsToInt((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// ���ø�ʽ: SDT_TEXT (Javascript).ȡִ�н�����ı�, ����˵��: "ȡ�ı��͵�ִ�н����"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬"
// ����<2>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
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

// ���ø�ʽ: SDT_BOOL (Javascript).ȡִ�н�����߼�, ����˵��: "ȡ�߼��͵�ִ�н����"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬"
// ����<2>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(53, wke_ResultToBool)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_BOOL;
    pRetData->m_bool = jsToBoolean((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// ���ø�ʽ: SDT_FLOAT (Javascript).ȡִ�н����С��, ����˵��: "ȡС���͵�ִ�н����"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬"
// ����<2>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(54, wke_ResultToFloat)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_FLOAT;
    pRetData->m_float = jsToFloat((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// ���ø�ʽ: SDT_DOUBLE (Javascript).ȡִ�н����˫����, ����˵��: "ȡ˫����С���͵�ִ�н����"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬"
// ����<2>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(55, wke_ResultToDouble)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_DOUBLE;
    pRetData->m_double = jsToDouble((jsExecState)( pArgInf[1].m_int ), pArgInf[2].m_int64);
}

// ���ø�ʽ: SDT_INT64 (Javascript).�÷���ֵ������, ����˵��: NULL
// ����<1>: ������ֵ SDT_INT, ����˵��: "������ֵ"
EXTERN_C void WKE_NAME(56, wke_SetRetTypeByInt)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = jsInt(pArgInf[1].m_int);
}

// ���ø�ʽ: SDT_INT64 (Javascript).�÷���ֵ�ı���, ����˵��: NULL
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬"
// ����<2>: ������ֵ SDT_TEXT, ����˵��: "������ֵ"
EXTERN_C void WKE_NAME(57, wke_SetRetTypeByText)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    wstr pWchar = wstr::A2W(pArgInf[2].m_pText);
    //pArgInf[2].m_pText
    pRetData->m_int64 = jsStringW((jsExecState)( pArgInf[1].m_int ), pWchar.c_str());
}

// ���ø�ʽ: SDT_INT64 (Javascript).�÷���ֵ�߼���, ����˵��: NULL
// ����<1>: ������ֵ SDT_BOOL, ����˵��: "������ֵ"
EXTERN_C void WKE_NAME(58, wke_SetRetTypeByBool)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = jsBoolean((bool)pArgInf[1].m_bool);
}

// ���ø�ʽ: SDT_INT64 (Javascript).�÷���ֵС����, ����˵��: NULL
// ����<1>: ������ֵ SDT_FLOAT, ����˵��: "������ֵ"
EXTERN_C void WKE_NAME(59, wke_SetRetTypeByFloat)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = jsFloat(pArgInf[1].m_float);
}

// ���ø�ʽ: SDT_INT64 (Javascript).�÷���ֵ˫����С����, ����˵��: NULL
// ����<1>: ������ֵ SDT_DOUBLE, ����˵��: "������ֵ"
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

// ���ø�ʽ: SDT_INT64 (Javascript).ȡ��������, ����˵��: "ȡָ�����������JSValue ��ʹ����Ӧת������õ����ս�������object������ȷ�����ͣ��򷵻�jsUndefined��������Ϊ�߼������Ա���"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ"
// ����<2>: object���� SDT_INT64, ����˵��: "js��object"
// ����<3>: Ҫȡ���������� SDT_TEXT, ����˵��: "������"
EXTERN_C void WKE_NAME(160, wke_GetObjectProp)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsValue value = jsGet((jsExecState)pArgInf[1].m_int, (jsValue)pArgInf[2].m_int64, pArgInf[3].m_pText);
    pRetData->m_dtDataType = SDT_INT64;
    pRetData->m_int64 = value;
}

// ���ø�ʽ: SDT_INT (Javascript).ȡ��������, ����˵��: "ȡ��������"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬"
// ����<2>: ������� SDT_INT, ����˵��: "�����±�,��0��ʼ����"
EXTERN_C void WKE_NAME(204, wke_jsArgType)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsType type = jsArgType((jsExecState)pArgInf[1].m_int, pArgInf[2].m_int);
    pRetData->m_int = (int)type;
}

// ���ø�ʽ: SDT_INT64 (Javascript).ȡ����ֵ, ����˵��: "ȡ����ֵ"
// ����<1>: ִ��״̬ SDT_INT, ����˵��: "ִ��״̬"
// ����<2>: ������� SDT_INT, ����˵��: "�����±�,��0��ʼ����"
EXTERN_C void WKE_NAME(205, wke_jsArg)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    jsValue type = jsArg((jsExecState)pArgInf[1].m_int, pArgInf[2].m_int);
    pRetData->m_int64 = (__int64)type;
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ��ֵ, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(206, wke_jsIsNumber)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsNumber((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ�ַ���, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(207, wke_jsIsString)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsString((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ�߼�ֵ, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(208, wke_jsIsBoolean)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsBoolean((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ����, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(209, wke_jsIsObject)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsObject((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ����, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(210, wke_jsIsFunction)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsFunction((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�ΪUndefined, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(211, wke_jsIsUndefined)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsUndefined((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ��, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(212, wke_jsIsNull)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsNull((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ����, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(213, wke_jsIsArray)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsArray((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ��, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(214, wke_jsIsTrue)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsTrue((jsValue)pArgInf[1].m_int64);
}

// ���ø�ʽ: SDT_BOOL (Javascript).�Ƿ�Ϊ��, ����˵��: "�ж�ֵ�����Ƿ�Ϊ������"
// ����<1>: ֵ���� SDT_INT64, ����˵��: "ֵ����,ִ�н��ָ��"
EXTERN_C void WKE_NAME(215, wke_jsIsFalse)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_bool = jsIsFalse((jsValue)pArgInf[1].m_int64);
}

