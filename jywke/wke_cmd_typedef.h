#pragma once

#define __WKE_NAME(_index, _name) __LIB2_FNE_NAME_LEFT(__E_FNENAME)##_##_name##_##_index##_

// ���ݺ�����������, ƴ�ӳ� �������_����_���_�������, ���� wke_test_0_wke
#define WKE_NAME(_index, _name) __LIB2_FNE_NAME_LEFT(__WKE_NAME(_index, _name))__LIB2_FNE_NAME_LEFT(__E_FNENAME)

// ���ݺ�����������, ƴ�ӳ� "�������_����_���_�������", ���� "wke_test_0_wke"
#define WKE_NAME_STR(_index, _name) ______E_FNENAME(WKE_NAME(_index, _name))

// ����궨�������е�����, �Ժ���Ҫ����������, ���������, ������ʹ�������
#define WKE_DEF(_MAKE) \
    _MAKE(  0, "�����ҳ", SetUrl, "���ָ����ҳ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 0)\
    _MAKE(  1, "ȡ��ҳURL", GetUrl, "��ȡ��ǰ��ҳURL��ַ��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  2, "����HTML�ı�", wke_LoadHtml, "����HTML�����ı���ע�⣬�����ҳ��������Ҫ���룬����Ҫ���н��б���ת����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 1)\
    _MAKE(  3, "����HTML�ļ�", wke_LoadFile, "����HTML�ļ���", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 2)\
    _MAKE(  4, "ǰ��", wke_GoForward, "�����ǰ�����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  5, "����", wke_CanGoBack, "������������", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  6, "ֹͣ����", wke_StopLoading, "ֹͣ���ص�ǰ��ҳ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  7, "��������", wke_Reload, "�������뵱ǰ��ҳ,�൱��ˢ�����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(  8, "ȡ��ҳԴ��", GetWebPageSource, "���ص�ǰ��ҳԴ��,�����������,��ʹ�� \"wke_Utf8ToAnsi()\" ת����", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_jywebkit + 23)\
    _MAKE(  9, "��ȡCookie", wke_GetCookie, "��ȡ��ǰ��ҳ��Cookie��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 10, "����Cookie_������������_�����_����cookie_CURL_������_����cookie_CURL��node_dll�ṩ�Ľӿ�_û���κζ��η�װ", wke_SetCookie, "֧�ֿⲻ�ṩ�κ����cookie���ж��η�װ������, ����cookie��ص������ԭ�����node.dll\r\n""        ����cookie����� ����cookie_CURL(), ������ԭ�����node.dll��wkeSetCookie�ӿ�\r\n", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 3)\
    _MAKE( 11, "ִ��Cookie����", wke_ExecuteCookeCommand, "ִ��cookie������", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 5)\
    _MAKE( 12, "����UserAgent", wke_SetUserAgent, "���������Ĭ�ϵ�UserAgent��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 6)\
    _MAKE( 13, "���ô���", SetProxy, "Ϊָ����webView���ô���", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_jywebkit + 7)\
    _MAKE( 14, "������ҳ����", SetWebVolume, "", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_FLOAT, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 15, "����ý������", SetMediVolume, "������ҳý��������", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 11)\
    _MAKE( 16, "ȡWebView", GetWebView, "����WebViewָ�롣", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 17, "�Ƿ����ǰ��", IsGoRorward, "����������Ƿ����ִ��ǰ�����", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 18, "�Ƿ���Ժ���", CanGoBack, "����������Ƿ����ִ�к������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 19, "�Ƿ�������", IsLodingCompleted, "������ҳ�Ƿ������ɡ�", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 20, "�ĵ��Ƿ����", IsDocumentReady, "�����ĵ��Ƿ��Ѿ�����", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 21, "Ajax��ʼ��", AJAXIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 22, "Ajax��ֵ", AJAXCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_COPY_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 23, "AJAX����", AJAXDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_FREE_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 24, "����Http����ͷ", SetHttpHeader, "����Http����ͷ,�ڵ���Get��Post����������ͷ������ա�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_ajax + 0)\
    _MAKE( 25, "GET����", AjaxGet, "����ҳ��ע��ajax�ű�����ʵ��Get����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_ajax + 2)\
    _MAKE( 26, "POST����", AjaxPost, "����ҳ��ע��ajax�ű�����ʵ��Post����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 5, g_Args_ajax + 5)\
    _MAKE( 27, "JS��ʼ��", JSIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 28, "JS��ֵ", JSCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_COPY_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 29, "JS����", JSDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_FREE_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 30, "��������", JSGC, "wke_JSGC , �������ա�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 31, "ȡ����", wke_GetType, "��ȡJS��������,����ִ�н������ ����ֵ�ο� #JS����_ ��صĳ�����", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0)\
    _MAKE( 32, "ָ���������JS", wke_RunJsByFrame, "ָ���������JS��", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_SECONDARY, 0, 0, 4, g_Args_JavaScript + 1)\
    _MAKE( 33, "����JS_�ı�_�ѷ���", wke_RunJsToStr, "����javascript�ű�,�з���ֵ�򷵻���Ӧ���,���򷵻ؿ��ı���", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 3, g_Args_JavaScript + 5)\
    _MAKE( 34, "����JS_ֵ����", wke_RunJsToJsValue, "����javascript�ű�,�������н��ָ��(JsVlaue,ֵ����),��ȡ���Ľ����Ҫʹ�� ȡ�����_xx ������ȡֵ��", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 8)\
    _MAKE( 35, "������ʽ_�ı�", wke_Eval_Str, "ʹ��eval��������js���ʽ,�����ı��ͽ�� mb�ڲ��Զ���������һ��function(){}�С�����ʹ�õı����ᱻ���� Ҫ��ȡ����ֵ����дreturn��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 10)\
    _MAKE( 36, "������ʽ_ֵ����", wke_Eval_JsValue, "ʹ��eval��������js���ʽ,�������н��ָ��(JsVlaue,ֵ����),��ȡ���Ľ����Ҫʹ�� ȡ�����_xx ������ȡֵ mb�ڲ��Զ���������һ��function(){}�С�����ʹ�õı����ᱻ���롣", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_SIMPLE, 0, 0, 2, g_Args_JavaScript + 13)\
    _MAKE( 37, "ȡJSִ��״̬", wke_CreateGlobalState, "��ȡָ��view��JSִ��״̬,�󲿷���Ҫ��ȡ����ֵ��JS��������Ҫ��״̬��", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 15)\
    _MAKE( 38, "��JS����ָ��", wke_ToJsFunc, "���������е��ӳ���ת����JS���õķ���ָ�롣", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 16)\
    _MAKE( 39, "ȡȫ�ֶ�������", wke_GetGlobalObject, "ȡȫ�ֶ�������JSValue ��ʹ����Ӧת������õ����ս����", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 18)\
    _MAKE( 40, "��ȫ�ֶ�������", wke_SetGlobalObject, "Ϊָ��ȫ�ֶ�����������ֵ,�����ں�����,ȫ�ֱ�����ֵ�ȵȡ�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 20)\
    _MAKE( 41, "����ȫ�ֺ���", wke_CallGlobal, "����jsȫ�ֺ�����", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 23)\
    _MAKE( 42, "���ö�����", wke_Call, "����jsȫ�ֺ���,����ָ��this��", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 4, g_Args_JavaScript + 26)\
    _MAKE( 43, "ȡȫ�ֶ���", wke_GetGlobal, "ȡȫ�ֶ���,window��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 30)\
    _MAKE( 44, "���ӳ���", wke_BindFunc, "JS�еĺ������������ӳ�����а�,��JS�к���������ʱ����Զ��ص��������е��ӳ���,��������Ӧ�Ĳ�����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 31)\
    _MAKE( 45, "ȡ��������", wke_ParamsCount, "ȡ�ص���������������", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 34)\
    _MAKE( 46, "ȡ�����Ͳ���", wke_ParamToInt, "�����Ͳ���ȡֵ��", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 35)\
    _MAKE( 47, "ȡ�ı��Ͳ���", wke_ParamToText, "�ı��Ͳ���ȡֵ��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 37)\
    _MAKE( 48, "ȡ�߼��Ͳ���", wke_ParamToBool, "�߼��Ͳ���ȡֵ��", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 39)\
    _MAKE( 49, "ȡС���Ͳ���", wke_ParamToFloat, "С���Ͳ���ȡֵ��", -1, _CMD_OS(__OS_WIN), SDT_FLOAT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 41)\
    _MAKE( 50, "ȡ˫����С���Ͳ���", wke_ParamToDouble, "˫����С���Ͳ���ȡֵ��", -1, _CMD_OS(__OS_WIN), SDT_DOUBLE, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 43)\
    _MAKE( 51, "ȡִ�н��������", wke_ResultToInt, "ȡ�����͵�ִ�н����", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 45)\
    _MAKE( 52, "ȡִ�н�����ı�", wke_ResultToText, "ȡ�ı��͵�ִ�н����", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 47)\
    _MAKE( 53, "ȡִ�н�����߼�", wke_ResultToBool, "ȡ�߼��͵�ִ�н����", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 49)\
    _MAKE( 54, "ȡִ�н����С��", wke_ResultToFloat, "ȡС���͵�ִ�н����", -1, _CMD_OS(__OS_WIN), SDT_FLOAT, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 51)\
    _MAKE( 55, "ȡִ�н����˫����", wke_ResultToDouble, "ȡ˫����С���͵�ִ�н����", -1, _CMD_OS(__OS_WIN), SDT_DOUBLE, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 53)\
    _MAKE( 56, "�÷���ֵ������", wke_SetRetTypeByInt, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 55)\
    _MAKE( 57, "�÷���ֵ�ı���", wke_SetRetTypeByText, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 2, g_Args_JavaScript + 56)\
    _MAKE( 58, "�÷���ֵ�߼���", wke_SetRetTypeByBool, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 58)\
    _MAKE( 59, "�÷���ֵС����", wke_SetRetTypeByFloat, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 59)\
    _MAKE( 60, "�÷���ֵ˫����С����", wke_SetRetTypeByDouble, "", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_HIGH, 0, 0, 1, g_Args_JavaScript + 60)\
    _MAKE( 61, "����ʼ��", TBIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_CONSTURCT_CMD, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 62, "���ֵ", TBCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_COPY_CMD, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 63, "�������", TBDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED | CT_IS_OBJ_FREE_CMD, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE( 64, "Ԫ�ص��", wke_ElementClick, "Ԫ�ص����", -1, _CMD_OS(__OS_WIN) , _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 65, "Ԫ���ý���", wke_SetElementFouce, "Ԫ���ý��㡣", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 66, "ȡԪ������ֵ", wke_GetAttribute, "ȡָ��Ԫ�����Ե��á�", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 0)\
    _MAKE( 67, "��Ԫ������ֵ", wke_SetAttribute, "����ָ��Ԫ�ص�ֵ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 6, g_Args_tb + 0)\
    _MAKE( 68, "��_�������", Form_SetFrame, "���ÿ���Ժ�,���е� ��_ �������������������ڲ�����,����С��1,��ʾ�����ǰѡ����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 69, "��_ȡ��ǰ�������", Form_GetFrameCount, "��ȡ��ǰ��ҳ�п��(iframe)��������", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 70, "��_Input���", wke_Input_Click, "ȡָ��Ԫ�����Ե�ֵ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 71, "��_Input������", wke_Input_ReadAttrValue, "��ȡ����ָ��inputԪ�ص�����ֵ��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 0)\
    _MAKE( 72, "��_Inputд����", wke_Input_WriteAttrVal, "��ָ��INPUTԪ��д������ֵ,������Դ�������¸����Ե�ֵ,������������һ�����ԡ�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 6, g_Args_tb + 0)\
    _MAKE( 73, "��_Input�Ƴ�����", wke_Input_RemoveAttrValue, "�Ƴ�ָ����Ԫ���е�ָ�����ԡ�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 0)\
    _MAKE( 74, "��_Inputѡ�����ѡ��״̬", wke_Input_SetCheckBoxState, "��_Inputѡ�����ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� �١�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 6)\
    _MAKE( 75, "��_Input��ѡ����ѡ��״̬", wke_Input_SetRadioChecked, "��ѡ����ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� �١�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 6)\
    _MAKE( 76, "��_Input��Ͽ���ѡ����", wke_Input_SetComboxIndex, "��Ͽ���ѡ��״̬,Ϊ��ѡ��,Ϊ��ȡ��ѡ�� �١�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 11)\
    _MAKE( 77, "��_ȡ��Ԫ������", Form_GetSubCount, "��ȡָ�����µ����б�Ԫ�ظ���,ֻ�б�Ԫ�زŻ������", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 78, "��_�ύ", Form_Submit, "�ύָ����,��ע������ύ���ɹ�,��ȷ����ҳ��û���������submit�Ĺ��̡�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 79, "�ĵ�_�ñ���", wke_DocSetTitle, "ͨ��JS������ҳ�ĵ����⡣", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 16)\
    _MAKE( 80, "�ĵ�_������", wke_DocSetZoom, "�����ĵ����š�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 18)\
    _MAKE( 81, "�ĵ�_ȡ����", wke_DocGetZoom, "ȡ�ĵ����ŷ�ֵ��", -1, _CMD_OS(__OS_WIN), SDT_FLOAT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 18)\
    _MAKE( 82, "�ĵ�_ȡ�ĵ�������", wke_DocGetWidth, "�ĵ�_ȡ�ĵ������ȡ�", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 83, "�ĵ�_ȡ�ĵ�����߶�", wke_DocGetHeight, "�ĵ�_ȡ�ĵ�����߶ȡ�", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 84, "�ĵ�_ȡBody������", wke_DocGetBodyWidth, "�ĵ�_ȡBody�����ȡ�", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 85, "�ĵ�_ȡBody����߶�", wke_DocGetBodyHeight, "�ĵ�_ȡBody����߶ȡ�", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 86, "�ĵ�_ȡ���������λ��", wke_DocGetScollY, "ȡ���������λ�á�", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 87, "�ĵ�_�����������λ��", wke_DocSetScollY, "�������������λ�á�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 20)\
    _MAKE( 88, "�ĵ�_�ú��������λ��", wke_DocSetScollX, "���ú��������λ�á�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 22)\
    _MAKE( 89, "�ĵ�_ȡ����", wke_DocGetEncoding, "��ȡ��ǰ��ҳ���롣", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 90, "�ĵ�_ȡ������", DocGetDomain, "wke_��ȡ��ҳ��������", -1, _CMD_OS(__OS_WIN), SDT_TEXT , 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 91, "�ĵ�_ȡѡ���ı�", wke_DocGetSelectText, "��ȡ��ǰѡ�е��ı���", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 92, "�ĵ�_ȡԪ������", GetElementHTML, "ȡָ��Ԫ������ innerHTML��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE( 93, "�ĵ�_����༭ģʽ", wke_DocEnableEditModel, "����༭ģʽ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 24)\
    _MAKE( 94, "�ĵ�_����", DocEditCopy, "�༭ģʽ���ơ�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 95, "�ĵ�_����", DocEditCut, "�༭ģʽ���С�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 96, "�ĵ�_ճ��", DocEditPaste, "�༭ģʽճ����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 97, "�ĵ�_����", DocEditPaste, "�༭ģʽ������", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 98, "�ĵ�_ȫѡ", DocSelectedAll, "�༭ģʽȫѡ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE( 99, "�ĵ�_ȡ��ȫѡ", DocCancelSelect, "�༭ģʽȡ��ȫѡ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE(100, "�ĵ�_����", DocEditRedo, "�༭ģʽ���á�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE(101, "�ĵ�_�����������", wke_MarkerAllLinks, "����������ӡ�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 26)\
    _MAKE(102, "�ĵ�_��������ı���", wke_MarkerAllInputText, "��������ı���", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 26)\
    _MAKE(103, "�ĵ�_������а�ť", wke_MarkerAllButton, "������а�ť��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 26)\
    _MAKE(104, "�ĵ�_Jquery�Ƿ��Ѽ���", wke_JqueryIsLoding, "�ĵ�_Jquery�Ƿ��Ѽ��ء�", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0)\
    _MAKE(105, "�ĵ�_ִ��JS����", JSCall, "���á�", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_tb + 28)\
    _MAKE(106, "�ĵ�_ȡͼƬ��ַ", wke_GetImageElemSrc, "�ĵ�_ͼƬȡ��ַ��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(107, "�ĵ�_ȡ���ӵ�ַ", wke_GetLinkhref, "�ĵ�_����ȡ��ַ��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(108, "Ԫ��_ȡ����", wke_GetElemTitle, "��ȡԪ�ص�title����ֵ��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(109, "Ԫ��_ȡ������ʽ", wke_GetElemStyleStr, "Ԫ��_ȡ������ʽ��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(110, "Ԫ��_ȡ�����б�", wke_GetClassList, "Ԫ��_ȡ�����б�", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(111, "Ԫ��_��˸���", wke_SetElementFlag, "���ָ��Ԫ�ء�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(112, "Ԫ��_�ÿ���״̬", wke_SetElementVisableState, "����Ԫ�ؿɼ�״̬��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 30)\
    _MAKE(113, "Ԫ��_ȡ������", wke_GetElementPointX, "ȡԪ�غ����ꡣ", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 35)\
    _MAKE(114, "Ԫ��_ȡ������", wke_GetElementPointY, "ȡԪ�������ꡣ", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 5, g_Args_tb + 35)\
    _MAKE(115, "Ԫ��_ȡ������Ϣ", GetElementRect, "ȡԪ�ؾ���,Ԫ�صľ�����Ϣ ��� �ұ� ���� �ױ� �� �ߡ�", -1, _CMD_OS(__OS_WIN), SDT_TYPE_TYPERECT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(116, "Ԫ��_����ָ���¼�", CallEvent, "����ָ��Ԫ�ص�ָ���¼�,���Դ����¼�������", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 7, g_Args_tb + 40)\
    _MAKE(117, "���⹦�ܳ�ʼ��", NETIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(118, "���⹦�ܸ�ֵ", NETCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_COPY_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(119, "���⹦������", NETDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_FREE_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(120, "NPAPI��������ر�", wke_NPAPIEnable, "��������ں�֧��NPAPI���������NPAPI���������ʵ������FLASH���ŵĹ��ܡ��濪�����ٹر�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 0)\
    _MAKE(121, "����ģʽ�����ر�", wke_SpiderEnable, "������ر���ҳ��Ⱦ,�����ҳ�����ٶ� ���������档ע�⣺����رպ���ҳ���ٽ�����Ⱦ����������Ȼ���ڡ�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 2)\
    _MAKE(122, "Cookie�����ر�", wke_SetCookieEnable, "Cookie�����ͽ��ã�����رգ�����������ٴ���Cookie��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 4)\
    _MAKE(123, "Cookie�Ƿ����", wke_CookieIsEnable, "Cookie�Ƿ��Ѿ�������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 6)\
    _MAKE(124, "�����鿪���ر�", wke_CspCheckEnable, "�������Ƿ��� �������Ϊ�棬�����������������������Ȩִ�У��������Ϊ�٣���������������Ĭ��ֵΪ�١�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 7)\
    _MAKE(125, "������������", HookRequest, "���� Url���뿪ʼ �¼��е���,Hookָ����Դ��������ô˷�����Url��������¼��Żᱻ����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 9)\
    _MAKE(126, "�޸�HTTPͷ�ֶ���Ϣ", wke_NetSetHTTPHeaderField, "���� Url���뿪ʼ �¼��е��ã���ʾ����http���󣨻���file:///Э�飩�� HTTPͷ�ֶ���Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 10)\
    _MAKE(127, "�޸�����MIME����", wke_NetSetMIMEType, "������ URL���뿪ʼ �¼��е��� ��ʾ����http�����MIME type��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 13)\
    _MAKE(128, "�޸�����URL", wke_NetChangeRequestUrl, "������ URL���뿪ʼ �¼��е��� �����޸�һ�����������url��", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 15)\
    _MAKE(129, "�޸���������", wke_SetRequestData, "�� Url���뿪ʼ �¼�����ã���ʾ�������غ󻺴�����ݡ�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 17)\
    _MAKE(130, "��������ģʽ", wke_SetTouchEnabled, "�����������Ϣ���Զ�ת���ɴ�����Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 20)\
    _MAKE(131, "���������Ϣ", wke_SetMouseEnabled, "�����ر������Ϣ�������ڿ��������󣬹ر������Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 22)\
    _MAKE(132, "����DevTool", wke_ShowDevTool, "����һЩ�����͹��ܡ� ���翪�������߹��ߡ�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 24)\
    _MAKE(133, "ȡ�����ID", wke_GetMainFrameId, "ȡ�����ID��", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 27)\
    _MAKE(134, "�Ƿ�Ϊ�����", wke_IsMainFrame, "�Ƿ�Ϊ����ܡ�", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 28)\
    _MAKE(135, "ȡ���URL", wke_GetFrameUrl, "�����IDȡ���URL��", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 30)\
    _MAKE(136, "����ƶ�", wke_MBMouseMove, "���������Ϣ,ģ���ƶ���ָ��λ�á�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 32)\
    _MAKE(137, "����������", wke_MouseLButtonDown, "����������������Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 35)\
    _MAKE(138, "������̧��", wke_MouseLButtonUP, "����������̧����Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 38)\
    _MAKE(139, "����м�����", wke_MouseMButtonDown, "��������м�������Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 41)\
    _MAKE(140, "����м�̧��", wke_MouseMButtonUP, "��������м�̧����Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 44)\
    _MAKE(141, "����Ҽ�����", wke_MouseRButtonDown, "��������Ҽ�������Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 47)\
    _MAKE(142, "����Ҽ�̧��", wke_MouseRButtonUP, "��������Ҽ�̧����Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 50)\
    _MAKE(143, "����_����", wke_KeyDownEvent, "���Ͱ�����Ϣ��MB��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 53)\
    _MAKE(144, "����_̧��", wke_KeyUpEvent, "���Ͱ�����Ϣ��MB��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 55)\
    _MAKE(145, "����_�ַ�", wke_KeyPressEvent, "����WM_CHAR��Ϣ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 57)\
    _MAKE(146, "ȡ������������", wke_CancelByReuqest, "������ URL���뿪ʼ�¼��� ȡ��ָ������������", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 59)\
    _MAKE(147, "wke_����dll·��", wke_setDllPath, "����node.dll������·��,�����������Ŀ¼��û��node.dll,������ڴ�������֮ǰ����,�����������Ŀ¼����node.dll���Ժ��Ը�����,Ĭ�ϻ��Ŀ¼�¼��ء�", 1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 0 )\
    _MAKE(148, "wke_AnsiToUtf8", wke_A2U, "��ansi������ı�ת����utf8������ı�,�ɹ�����ת������ı�,ʧ�ܷ��ؿ��ı���", 2, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 2 )\
    _MAKE(149, "wke_AnsiToUnicode", wke_A2W, "��ansi������ı�ת����Unicode������ı�,�ɹ�����ת�����Unicode�ֽڼ�,ʧ�ܷ��ؿ��ֽڼ���", 2, _CMD_OS(__OS_WIN), SDT_BIN, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 2 )\
    _MAKE(150, "wke_Utf8ToAnsi", wke_U2A, "��utf8������ı�ת����ansi������ı�,�ɹ�����ת������ı�,ʧ�ܷ��ؿ��ı���", 2, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 1 )\
    _MAKE(151, "wke_Utf8ToUnicode", wke_U2W, "��utf8������ı�ת����Unicode������ı�,�ɹ�����ת�����Unicode�ֽڼ�,ʧ�ܷ��ؿ��ֽڼ���", 2, _CMD_OS(__OS_WIN), SDT_BIN, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 1 )\
    _MAKE(152, "wke_UnicodeToAnsi", wke_W2A, "��Unicode������ı�ת����ansi������ı�,�ɹ�����ת������ı�,ʧ�ܷ��ؿ��ı���", 2, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 3 )\
    _MAKE(153, "wke_UnicodeToUtf8", wke_W2U, "��Unicode������ı�ת����utf8������ı�,�ɹ�����ת������ı�,ʧ�ܷ��ؿ��ı���", 2, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_All + 3 )\
    _MAKE(154, "��ʱ��������", wkeGC, "�ӳ���miniblink�������ա�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 12)\
    _MAKE(155, "wke_ȡ�汾��", wke_GetVersion, "��ȡĿǰapi�汾�š�", 1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0)\
    _MAKE(156, "wke_ȡ�汾�ı�", wke_GetVersionString, "��ȡ�汾�ַ�����", 1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 0, 0)\
    _MAKE(157, "���û�����", wke_SetUserKeyValue, "�����ݺ�webView�󶨡�", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 13)\
    _MAKE(158, "ȡ�û�����", wke_GetUserKeyValue, "ȡ�� ���û�����() ���õ�ֵ��", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 15)\
    _MAKE(159, "ȡ��ҳ���", wke_GetWindowHandle, "ȡ�� miniblink �Ĵ��ھ����", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0)\
    _MAKE(160,  "ȡ��������", wke_GetObjectProp, "ȡָ�����������JSValue ��ʹ����Ӧת������õ����ս�������object������ȷ�����ͣ��򷵻�jsUndefined��������Ϊ�߼������Ա���", -1, _CMD_OS(__OS_WIN) , SDT_INT64, 0, LVL_HIGH, 0, 0, 3, g_Args_JavaScript + 61 )\
    _MAKE(161,  "����Cookie_����_������������_�����_����cookie_CURL_������_����cookie_CURL��node_dll�ṩ�Ľӿ�_û���κζ��η�װ", wke_SetSingleCookie, "֧�ֿⲻ�ṩ�κ����cookie���ж��η�װ������, ����cookie��ص������ԭ�����node.dll\r\n""        ����cookie����� ����cookie_CURL(), ������ԭ�����node.dll��wkeSetCookie�ӿ�\r\n", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 16 )\
    _MAKE(162,  "�ĵ�_ȡ���������λ��", wke_DocGetScollX, "��ȡ���������λ�á�", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0 )\
    _MAKE(163,  "��_Inputѡ���ȡѡ��״̬", wke_Input_GetCheckBoxState, "ȡѡ���ѡ��״̬��", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0 )\
    _MAKE(164,  "��_Input��ѡ��ȡѡ��״̬", wke_Input_GetRadioChecked, "ȡ��ѡ��ѡ��״̬��", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0 )\
    _MAKE(165,  "��_Input��Ͽ�ȡѡ����", wke_Input_GetComboxIndex, "ȡ��Ͽ�ѡ����������", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0 )\
    _MAKE(166,  "�������cookie", wke_clearCookie, "�����ǰwke������cookie��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(167,  "��ȡ����ͷ����", wke_NetGetRawHttpHead, "��ȡ���͵�����ͷ�����ݡ�", -1, _CMD_OS(__OS_WIN) | CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 59 )\
    _MAKE(168,  "�����´���", wke_IsEnableNewWnd, "������Ĭ��Ϊ��,���ڱ����ڴ�,������ \"�����������´���\" �¼�\r\n"\
                "    Ϊ��ʱ�ᴥ�� \"�����������´���\" �¼�\r\n"\
                "    �����ҳ��js hook�˵���¼�,Ȼ����window.open��,��ô ��ֹ�´���() �������Ч,��ֹ���ǻᵯ���´���\r\n"\
                "    ����Ҫ�´��ڴ򿪵Ŀ����� �����������´��� �¼��·��� \"��\",����������\r\n"\
                "    Ϊ����ȡ��ǰ״̬, ��Ϊ��ʱ����ֵ�����塣\r\n", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 18 )\
    _MAKE(169,  "��_ȡ������", wke_GetFormLength, "��ȡָ������µ�����form������,ֻ�б��Ż������", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb)\
    _MAKE(170,  "wke_ȡCPUռ��", wke_GetCpu, "ȡ�Խ���CPUռ����,���ڲ��Թһ���¼��������״̬��\r\n""����ע�⡿�ù����ǲ��Թ���,������û���������Ƿ�ɾ��������", 1, _CMD_OS(__OS_WIN), SDT_DOUBLE, 0, LVL_SIMPLE, 0, 0, 2, g_Args_All + 4)\
    _MAKE(171,  "��ͼ", wke_screenshot, "��ͼָ������������������", -1, _CMD_OS(__OS_WIN), SDT_BIN, 0, LVL_SIMPLE, 0, 0, 4, g_Args_jywebkit + 19)\
    _MAKE(172,  "ȡ����ģʽ", wke_NetGetRequestMethod, "���ص�ǰ������ģʽ, ��ʹ�� #����ģʽ_ ��ͷ�ĳ���\r\n""�޷��޸�post����,ֻ��ȡ", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 60)\
    _MAKE(173,  "ȡpost����", wke_NetGetPostBody, "��ȡpost����", -1, _CMD_OS(__OS_WIN), SDT_TYPE_POSTELEMENTS, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 60)\
    _MAKE(174,  "����post����", wke_NetCreatePostBodyElement, "��������post����", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_BOOL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 61)\
    _MAKE(175,  "�ͷ�post����", wke_NetFreePostBodyElement, "������ı����� ����post����()�� ���ص�ֵ", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 63)\
    _MAKE(176,  "����post������", wke_NetCreatePostBodyElements, "����һ���µ�post������,�ǵò���ʱ�Լ����� ���⹦��.�ͷ�post������() ���ͷ�", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 61)\
    _MAKE(177,  "�ͷ�post������", wke_NetFreePostBodyElements, "������ı����� ����post������()�� ���ص�ֵ\r\n��[Url���뿪ʼ]�¼����ж���postʱ������ͨ�� ���⹦��.����post������() ������һ���µ�post���ݰ���""Ȼ����� ���⹦��.�ͷ�post������() ���ͷ�ԭpost���ݡ�", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 62)\
    _MAKE(178,  "�첽����", wke_NetHoldJobToAsynCommit, "�߼��÷�����[Url���뿪ʼ]�ص�����á� ��ʱ��[Url���뿪ʼ]�¼������ص�һ�������"\
            "���������жϳ��������ʱ���Ե��ñ��ӿڣ�Ȼ���� �첽��ĳ��ʱ�̣����� ���⹦��.��������() ���ô������������\r\n"\
            "���������ɹ����ٴ������ʧ�ܣ������ٵ��� ���⹦��.��������() ��", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 60)\
    _MAKE(179,  "��������", wke_NetContinueJob, "�߼��÷������ ���⹦��.�첽����() ʹ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 1, g_Args_SpecialFunction + 60)\
    _MAKE(180,  "ȡ��ҳ�ı�", wke_GetInnerText, "ȡָ�����ָ��Ԫ�ػ���ȡ����html���ı�,������html���", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_jywebkit + 23)\
    _MAKE(181,  "Ԫ��_ȡ��Ԫ������", GetElementCount, "ȡָ��Ԫ�ص���Ԫ������", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 4, g_Args_tb + 0)\
    _MAKE(182,  "����", Attach, "��һ��webView���ӵ���������,���Ӻ����ʹ�ñ�������κη���, �ɹ�������, ʧ�ܷ��ؼ�", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 27 )\
    _MAKE(183, "�´��ڹ��캯��", newWndIntialize, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_CONSTURCT_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(184, "�´��ڸ��ƹ��캯��", newWndCopy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_COPY_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(185, "�´�����������", newWndDestroy, "", -1, _CMD_OS(__OS_WIN) | CT_IS_OBJ_FREE_CMD | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(186, "�Ƿ��Ѵ���", newWndIsCreate, "", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 0, NULL)\
    _MAKE(187, "����", wke_DestroyWebView, "���������µ����Ĵ���", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0)\
    _MAKE(188, "����cookie_CURL", wke_SetCookieCURL, "����node.dll�� wkeSetCookie, ���Բ������κ��޸�, ֧�ֿ�����cookie��ص������ԭ�����node.dll, �������κ��޸�", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 28)\
    _MAKE(189,  "ģ��Ӳ���豸����", wke_SetDeviceParameter, "����mbģ���Ӳ���豸��������Ҫ����αװ�ֻ��豸����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 4, g_Args_jywebkit + 30 )\
    _MAKE(190,  "�ҽ��¼�", wke_Event, "�����¼����͹ҽӲ�ͬ���¼�, �¼�������ʹ�� ������¼�_ ��ͷ�ĳ���", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_jywebkit + 34 )\
    _MAKE(191,  "��ȡ����Cookie", wke_GetAllCookie, "ͨ��������visitor��������cookie", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 2, g_Args_jywebkit + 37 )\
    _MAKE(192,  "��������", wke_format_1, "c/c++��ĸ�ʽ���ַ���", 1, _CMD_OS(__OS_WIN) | CT_ALLOW_APPEND_NEW_ARG | CT_IS_HIDED, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 39 )\
    _MAKE(193,  "�����ַ���", wke_makeString, "�����ַ���, ��������ת�����ı������Ͷ�ת���ı���������һ��, ��ʱû��������ʱ���ͺ�����", 1, _CMD_OS(__OS_WIN) | CT_ALLOW_APPEND_NEW_ARG, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 40 )\
    _MAKE(194,  "��ֵ", wke_assign, "����һ�� WKE_��� �ڲ������ݸ�ֵ����ǰ WKE_��� ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 47 )\
    _MAKE(195,  "���", wke_clear, "��յ�ǰ WKE_����ڵ�����", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(196,  "��ȡ��Ӧͷ", wke_NetGetRawResponseHead, "��ȡԭʼ��Ӧͷ, �� Url������� �¼���ʹ��", -1, _CMD_OS(__OS_WIN) | CT_RETRUN_ARY_TYPE_DATA, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 9 )\
    _MAKE(197,  "post", wke_PostURL, "post", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 3, g_Args_SpecialFunction + 65 )\
    _MAKE(198,  "���cookie", wke_ClearCookie, "���cookie", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(199,  "ȡ�༭���α�λ��", wke_GetCaretRect, "��ȡ�༭����Ǹ��α��λ��", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_tb + 0 )\
    _MAKE(200,  "��ȡ����MIME����", wke_NetGetMIMEType, "�� URL���뿪ʼ �¼������, ��ʾ����http�����MIME type", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_SpecialFunction + 9 )\
    _MAKE(201,  "��ȡHTTPͷ�ֶ���Ϣ", wke_NetGetHTTPHeaderField, "�� URL���뿪ʼ �¼������, ��ʾ����http���󣨻���file:///Э�飩�� http header field", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 68 )\
    _MAKE(202,  "��ȡ��ӦHTTPͷ�ֶ���Ϣ", wke_NetGetHTTPHeaderFieldFromResponse, "�� URL������� �¼������", -1, _CMD_OS(__OS_WIN), SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_SpecialFunction + 68 )\
    _MAKE(203,  "ȡ��ҳͼ��", wke_NetGetFavicon, "������ �ĵ�������� �¼������", -1, _CMD_OS(__OS_WIN) | CT_IS_HIDED, SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(204,  "ȡ��������", wke_jsArgType, "ȡ��������", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_JavaScript + 64 )\
    _MAKE(205,  "ȡ����ֵ", wke_jsArg, "ȡ����ֵ", -1, _CMD_OS(__OS_WIN), SDT_INT64, 0, LVL_SIMPLE, 0, 0, 2, g_Args_JavaScript + 64 )\
    _MAKE(206,  "�Ƿ�Ϊ��ֵ", wke_jsIsNumber, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(207,  "�Ƿ�Ϊ�ַ���", wke_jsIsString, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(208,  "�Ƿ�Ϊ�߼�ֵ", wke_jsIsBoolean, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(209,  "�Ƿ�Ϊ����", wke_jsIsObject, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(210,  "�Ƿ�Ϊ����", wke_jsIsFunction, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(211,  "�Ƿ�ΪUndefined", wke_jsIsUndefined, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(212,  "�Ƿ�Ϊ��", wke_jsIsNull, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(213,  "�Ƿ�Ϊ����", wke_jsIsArray, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(214,  "�Ƿ�Ϊ��", wke_jsIsTrue, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(215,  "�Ƿ�Ϊ��", wke_jsIsFalse, "�ж�ֵ�����Ƿ�Ϊ������", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_JavaScript + 0 )\
    _MAKE(216,  "����", wke_Create, "����һ�������, �����ɹ����ش��ھ��, ʧ�ܷ���0, ���ھ����webView�ǲ�һ����, ���ϸ񴫵ݲ���", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 6, g_Args_jywebkit + 54 )\
    _MAKE(217,  "��Ϣѭ��", wke_MessageLoop, "��Ϣѭ��, ���û�д��������򷵻ؼ�, ����ֱ�������յ� WM_QUIT ��Ϣʱ�˷����ŷ�����", -1, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 1, g_Args_jywebkit + 51 )\
    _MAKE(218,  "wke_��Ϣѭ��", wke_MsgLoop, "��Ϣѭ��, �ڴ��ڴ�������¼��µ���, ���ô������ֱ������wke_ȡ��ѭ��() �ŷ���, ��������ʱ��Ҫ���� wke_ȡ��ѭ��(), ��������޷��˳�\r\n"\
                                                "�˷�����Ϊ�˴���web���������޷���tab���л����������,"\
                                                "\r\n��ע�⡿���ô˷����󲻻��������Ե���Ϣѭ��, ��tab���󲻻��Զ������������, ͬʱ������յ�tan�����·ſ���Ϣ", 0, _CMD_OS(__OS_WIN), SDT_BOOL, 0, LVL_SIMPLE, 0, 0, 2, g_Args_jywebkit + 52 )\
    _MAKE(219,  "wke_ȡ��ѭ��", wke_CancelMsgLoop, "ȡ����Ϣѭ��, ȡ�������ʹ wke_��Ϣѭ��() ����, ����������PostQuitMessage", 0, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(220,  "ȡwke���ھ��", wke_GetWindow, "ȡ��ǰwke�Ĵ��ھ��", -1, _CMD_OS(__OS_WIN), SDT_INT, 0, LVL_SIMPLE, 0, 0, 0, 0 )\
    _MAKE(221,  "�õ�����Ϣ", wke_SetDebugConfig, "�õ�����Ϣ", -1, _CMD_OS(__OS_WIN), _SDT_NULL, 0, LVL_HIGH, 0, 0, 3, g_Args_SpecialFunction + 24 )\
    _MAKE(222,  "wke_��ʽ���ı�", wke_format, "����c���� sprintf��ʵ��, ������Բ�������У��", 1, _CMD_OS(__OS_WIN) | CT_ALLOW_APPEND_NEW_ARG, SDT_TEXT, 0, LVL_SIMPLE, 0, 0, 2, g_Args_All + 6 )\
    _MAKE(223,  "wke_��ʽ���ı�W", wke_formatW, "����c���� swprintf��ʵ��, Unicode��, ������Բ�������У��", 1, _CMD_OS(__OS_WIN) | CT_ALLOW_APPEND_NEW_ARG, SDT_BIN, 0, LVL_SIMPLE, 0, 0, 2, g_Args_All + 6 )
