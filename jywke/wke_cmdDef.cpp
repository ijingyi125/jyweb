#include "wke_typedef.h"


#if !defined(__E_STATIC_LIB)

static ARG_INFO g_Args_jywebkit[] =
{
    //����Ϊ ����web����� �����µĲ���

    // 1=��������, 2=������ϸ����, 3=ָ��ͼ������,��1��ʼ,0��ʾ��, 4=ͼ����Ŀ(��������)
    // 5=��������, 6=����Ĭ��ֵ,   7=������־ AS_ ��ͷ����


    /*000*/    {"URL��ַ", "���������URL��ַ,���url��ַ������,�봫��utf8�����ı�.", 0, 0, SDT_TEXT, 0, NULL},

    /*001*/    {"HTML�ı�", "һ��HTML�ı�,�봫������ҳ��ͬ������ı�.", 0, 0, SDT_TEXT, 0, NULL},

    /*002*/    {"HTML�ļ�", "HTML�ļ���,���·��������,�봫��utf8�����ı�.", 0, 0, SDT_TEXT, 0, NULL},

    /*003*/    {"URL", "������cookie����վ����,���url��ַ������,�봫��utf8�����ı�.", 0, 0, SDT_TEXT, 0, NULL},
    /*004*/    {"COOKIE", "Ҫ���õ�Cookie�����cookieʹ��;���������磺 a=1;b=2;c=3;d=4;", 0, 0, SDT_TEXT, 0, NULL},

    /*005*/    {"��������", "0 = �������Cookie , 1 = �������session , 2 = ˢ��cookie�ļ�  3= ��������cookie�ļ�", 0, 0, SDT_INT, 0, NULL},

    /*006*/    {"UserAgent", "UserAgent�ı�,���url��ַ������,�봫��utf8�����ı�.", 0, 0, SDT_TEXT, 0, NULL},

    /*007*/    {"��������", "#��������_��ͷ�ĳ���", 0, 0, SDT_INT, 0, NULL},
    /*008*/    {"�����ַ", "����ip��˿�,�� 122.132.123.123:666", 0, 0, SDT_TEXT, 0, NULL},
    /*009*/    {"�û���", "�����û���,û��������", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*010*/    {"����", "��������,û��������", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*011*/    {"����", "�����õ�����", 0, 0, SDT_INT, 0, NULL},

    /*012*/    {"��ʱʱ��", "��λ����,�ӳ���miniblink��������", 0, 0, SDT_INT, 0, NULL},

    /*013*/    {"����", "���ü������ͨ���������ȡ�����õ�ֵ", 0, 0, SDT_TEXT, 0, NULL},
    /*014*/    {"��ֵ", "��Ҫ���õļ�ֵ", 0, 0, SDT_INT, 0, NULL},

    /*015*/    {"����", "���û�����() �����õļ���", 0, 0, SDT_TEXT, 0, NULL},

    /*016*/    {"URL", "������cookie����վ����,���url��ַ������,�봫��utf8�����ı�.", 0, 0, SDT_TEXT, 0, NULL},
    /*017*/    {"COOKIE", "Ҫ���õ�Cookie����ʽ��Ҫ����curl�ĸ�ʽ�����磺abc=1;expires=Monday, 1-Jun-2019 00:01:01 GMT; path=/; secure", 0, 0, SDT_TEXT, 0, NULL},

    /*018*/    {"�Ƿ��ֹ", "�� = ��ֹ, �� = ����ֹ, ���� = ȡֵ, �ò�����Ϊ��ʱ����ֵ�����塣", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*019*/    {"���", "���ջ���С��0 = 0, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*020*/    {"����", "���ջ���С��0 = 0, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*021*/    {"���", "���ջ���С��0 = ��������,Ĭ��Ϊ��������", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*022*/    {"�߶�", "���ջ���С��0 = ������߶�,Ĭ��Ϊ������߶�", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*023*/    {"���ID", "ID��1��ʼ,Ϊ�ջ���С��0,Ĭ��ȡ�����", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    ///*023*/    {"���ID", "���,���� window.frames[0] = ��һ�����,Ϊ����ȡ������ı�", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*024*/    {"���ģʽ", "Ĭ��Ϊ #���ģʽ_JS���ʽ, ��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*025*/    {"ѡ����ʽ", "Ϊ����ȡ������ҳ,ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*026*/    {"Ԫ���±�", "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*027*/    {"weiView", "Ϊ�ջ���Ϊ0,���������,��0ֵ�������һ��webView�����ʧ��,�´��ڴ������ �¼��е�webView,����������ʽ��ȡ����webView", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*028*/    {"url", "������cookie����վ����,���url��ַ������,�봫��utf8�����ı�.", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*029*/    {"cookie", "�����õ�cookie, cookie�������curl��cookieд��", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*030*/    {"�豸�ַ���", "�豸���ַ�������ȡֵ�У�\r\n"\
                    "	1. \"navigator.maxTouchPoints\"��ʱ \"��������\" ��Ҫ�����ã���ʾ touch �ĵ�����\r\n"\
                    "	2. \"navigator.platform\"��ʱ \"�ı�����\" ��Ҫ�����ã���ʾjs���ȡ�� navigator.platform�ַ�����\r\n"\
                    "	3. \"navigator.hardwareConcurrency\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� navigator.hardwareConcurrency ����ֵ��\r\n"\
                    "	4. \"screen.width\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.width ����ֵ��\r\n"\
                    "	5. \"screen.height\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.height ����ֵ��\r\n"
                    "	6. \"screen.availWidth\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.availWidth ����ֵ��\r\n"\
                    "	7. \"screen.availHeight\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.availHeight ����ֵ��\r\n"\
                    "	8. \"screen.pixelDepth\"��ʱ \"��������\" ��Ҫ�����ã���ʾjs���ȡ�� screen.pixelDepth ����ֵ��\r\n"\
                    "	9. \"screen.pixelDepth\"Ŀǰ�ȼ���\"screen.pixelDepth\"��\r\n"\
                    "	10.\"window.devicePixelRatio\"ͬ��", 0, 0, SDT_TEXT, 0, 0},
    /*031*/    {"�ı�����", "�ı�����", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*032*/    {"��������", "��������", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*033*/    {"�������", "�������", 0, 0, SDT_FLOAT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*034*/    {"�¼�����", "������¼�_ ��ͷ����, ��Ҫ���ӳ�������ͷ���ֵ��ο�����˵��", 0, 0, SDT_INT, 0, 0},
    /*035*/    {"�ص���ַ", "��ϸ������鿴����, Ϊ����ȡ�����¼�", 0, 0, SDT_SUB_PTR, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*036*/    {"����", "����ص��Ĳ���", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*037*/    {"������", "�߼��� �ص�����(������ ����, �ı��� cookie��, �ı��� cookieֵ, �ı��� ����, �ı��� ·��, ������ ������https����, ������ ������http����, �����ʹ�ַ �Ƿ�����cookie�����¼�); ", 0, 0, SDT_SUB_PTR, 0, NULL},
    /*038*/    {"����", "����������, �������1�ص���ַ�е�ֵ", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*039*/    {"��ʽ���ı���", "��ʽ���ı���", 0, 0, SDT_TEXT, 0, NULL},
    /*040*/    {"����", "����ʱ������ʹ�� %s, �ڲ���ת���� \"2020-01-01 01:01:01\" ���ָ�ʽ\r\n"
                "	�ֽڼ����߼���Ҳʹ�� %s, �ڲ���ת���ı�ʹ��, ����û��˵��������, �Ͱ�c/c++��ʽ���ַ�������", 0, 0, _SDT_ALL, 0, NULL},

    /*041*/    {"����", "��������ת�����ı��Ķ�ת�����ı�", 0, 0, SDT_TEXT, 0, NULL},

    /*042*/    {"�ص�����", "���ջ�ȡ��ҳͼ��Ļص�, �޷���ֵ �ص�(�ı��� url, ������ ͼ��ָ��, ������ ͼ�곤��)", 0, 0, SDT_SUB_PTR, 0, NULL},

    /*043*/    {"�����ھ��", "������������ĸ����ھ��, ������Ϊ0����Ч���, �򴴽�һ������ʽ����, �����ǰ����û����Ϣѭ��, ����Ҫ�Լ�������Ϣѭ��", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*044*/    {"��", "�����������ߵ�λ��, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*045*/    {"��", "��������򶥱ߵ�λ��, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*046*/    {"��", "���������Ŀ��, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*047*/    {"��", "���������ĸ߶�, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*048*/    {"��������", "�����ǰ���Ѿ������������, ���������ڴ���, ���򷵻ؼ�, Ĭ��Ϊ��, ���ٺ󴴽�", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*049*/    {"���໯����", "�ṩһ���ӳ���, ���մ��ڵ���Ϣ���� ����ԭ��Ϊ: ������ ���ڹ���(������ ���ھ��, ������ ��Ϣֵ, ������ ����1, ������ ����2)", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*050*/    {"�ɴ��ڹ���", "����7��Ϊ��ʱ��Ч, ����ԭ������Ϣ����", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*051*/    {"���������˳���Ϣѭ��", "���Ϊ��, ��ô����յ� WM_DESTROY ��Ϣʱ����� PostQuitMessage() �˳���Ϣѭ��, ������Լ����໯, �����յ� WM_DESTROY ��Ϣʱ��Ҫ���� CallWindowProcW() ����Ϣת��ԭ����, �����Լ����� PostQuitMessage(), ����ú������᷵��", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*052*/    {"���ھ��", "Ŀǰ����2Ϊ��ʱ�ò�����Ч", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*053*/    {"��ʾ����", "�Ƿ���ʾ����, Ϊ��������ʾ�����ڵ�����Ϣѭ��, ����ֱ�ӵ�����Ϣѭ��", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*054*/    {"�����ھ��", "������������ĸ����ھ��, �����ǰ����û����Ϣѭ��, ����Ҫ�Լ�������Ϣѭ��", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*055*/    {"��", "�����������ߵ�λ��, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*056*/    {"��", "��������򶥱ߵ�λ��, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*057*/    {"��", "���������Ŀ��, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*058*/    {"��", "���������ĸ߶�, Ĭ��Ϊ0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*059*/    {"��������", "�����ǰ���Ѿ������������, ���������ڴ���, ���򷵻ؼ�, Ĭ��Ϊ��, ���ٺ󴴽�", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*060*/    {"��������", "0=����ʽ����, 1=�ֲ㴰��, ����=�Ӵ���, �밴��������д, �ֲ㴰����Ҫ�ҽӻ滭�¼����л��Ƶ���Ҫ��ʾ�ĵط�", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

};

static ARG_INFO g_Args_ajax[] =
{
    //ajax�����µĲ���
    /*000*/    {"Key", "http����ͷ�ֶ�����,�� Content-Type UserAgent Referer �ȵ�", 0, 0, SDT_TEXT, 0, NULL},
    /*001*/    {"Value", "http����ͷ�ֶζ�Ӧ��ֵ", 0, 0, SDT_TEXT, 0, NULL},

    /*002*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*003*/    {"url", "�����URL", 0, 0, SDT_TEXT, 0, NULL},
    /*004*/    {"�ص�����", "��Ajax�������������ɽ����ô˷���,�ɹ����ط����������ı�,���󷵻�״̬��", 0, 0, SDT_SUB_PTR, 0, NULL},

    /*005*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*006*/    {"url", "�����URL", 0, 0, SDT_TEXT, 0, NULL},
    /*007*/    {"�Ƿ���JSON", "�ύ�����ݸ�ʽ�Ƿ���JSON", 0, 0, SDT_BOOL, 0, NULL},
    /*008*/    {"�ύ����", "Ҫ�ύ��POST����", 0, 0, SDT_TEXT, 0, NULL},
    /*009*/    {"�ص�����", "��Ajax�������������ɽ����ô˷���,�ɹ����ط����������ı�,���󷵻�״̬��", 0, 0, SDT_SUB_PTR, 0, NULL},
};

static ARG_INFO g_Args_JavaScript[] =
{
    //JavaScript �����µĲ���
    /*000*/    {"ֵ����", "ֵ����,ִ�н��ָ��", 0, 0, SDT_INT64, 0, NULL},

    /*001*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*002*/    {"���ID", "���ID", 0, 0, SDT_INT, 0, NULL},
    /*003*/    {"script", "javascript�ű�", 0, 0, SDT_TEXT, 0, NULL},
    /*004*/    {"�Ƿ������Function��ִ��", "script�������mb�ڲ��Զ���������һ��function(){}�С�����ʹ�õı����ᱻ����,�˴�ȷ���Ƿ������function��", 0, 0, SDT_BOOL, 0, NULL},

    /*005*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*006*/    {"script", "�����еĽű�", 0, 0, SDT_TEXT, 0, NULL},
    /*007*/    {"�Ƿ��з���ֵ", "JS�Ƿ��з���ֵ", 0, 0, SDT_BOOL, 0, NULL},

    /*008*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*009*/    {"script", "�����еĽű�", 0, 0, SDT_TEXT, 0, NULL},

    /*010*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*011*/    {"���ʽ", "������ı��ʽ", 0, 0, SDT_TEXT, 0, NULL},
    /*012*/    {"�Ƿ��з���ֵ", "JS�Ƿ��з���ֵ", 0, 0, SDT_BOOL, 0, NULL},

    /*013*/    {"ִ��״̬", "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*014*/    {"���ʽ", "������ı��ʽ", 0, 0, SDT_TEXT, 0, NULL},

    /*015*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},

    /*016*/    {"ִ��״̬", "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*017*/    {"��ת���ӳ���", "�������е��ӳ���ָ��", 0, 0, SDT_SUB_PTR, 0, NULL},

    /*018*/    {"ִ��״̬", "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*019*/    {"��������", "������������", 0, 0, SDT_TEXT, 0, NULL},

    /*020*/    {"ִ��״̬", "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*021*/    {"��������", "������������", 0, 0, SDT_TEXT, 0, NULL},
    /*022*/    {"����ֵ", "������������", 0, 0, SDT_INT64, 0, NULL},

    /*023*/    {"ִ��״̬", "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*024*/    {"js����", "js����", 0, 0, SDT_INT64, 0, NULL},
    /*025*/    {"��������", "����Ĳ�������", 0, 0, SDT_INT64, 0, AS_RECEIVE_ARRAY_DATA | AS_DEFAULT_VALUE_IS_EMPTY},

    /*026*/    {"ִ��״̬", "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*027*/    {"js����", "js����", 0, 0, SDT_INT64, 0, NULL},
    /*028*/    {"this����", "������this����", 0, 0, SDT_INT64, 0, NULL},
    /*029*/    {"��������", "����Ĳ�������", 0, 0, SDT_INT64, 0, AS_RECEIVE_ARRAY_DATA | AS_DEFAULT_VALUE_IS_EMPTY},

    /*030*/    {"ִ��״̬", "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ", 0, 0, SDT_INT, 0, NULL},

    /*031*/    {"Js��������", "js�к���������", 0, 0, SDT_TEXT, 0, NULL},
    /*032*/    {"�������ӳ���ָ��", "�������е��ӳ���ָ�롣 ���ӳ�����һ���������Ͳ�������ʾjs�����������س������͡���������򷵻�ֵ���󣬳��򽫻��������", 0, 0, SDT_SUB_PTR, 0, NULL},
    /*033*/    {"��������", "����Ĳ�������", 0, 0, SDT_INT, 0, NULL},

    /*034*/    {"ִ��״̬", "ִ��״̬,�ص�������һ������", 0, 0, SDT_INT, 0, NULL},

    /*035*/    {"ִ��״̬", "ִ��״̬,�ص�������һ������", 0, 0, SDT_INT, 0, NULL},
    /*036*/    {"�������", "�����±�,��0��ʼ����", 0, 0, SDT_INT, 0, NULL},

    /*037*/    {"ִ��״̬", "ִ��״̬,�ص�������һ������", 0, 0, SDT_INT, 0, NULL},
    /*038*/    {"�������", "�����±�,��0��ʼ����", 0, 0, SDT_INT, 0, NULL},

    /*039*/    {"ִ��״̬", "ִ��״̬,�ص�������һ������", 0, 0, SDT_INT, 0, NULL},
    /*040*/    {"�������", "�����±�,��0��ʼ����", 0, 0, SDT_INT, 0, NULL},

    /*041*/    {"ִ��״̬", "ִ��״̬,�ص�������һ������", 0, 0, SDT_INT, 0, NULL},
    /*042*/    {"�������", "�����±�,��0��ʼ����", 0, 0, SDT_INT, 0, NULL},

    /*043*/    {"ִ��״̬", "ִ��״̬,�ص�������һ������", 0, 0, SDT_INT, 0, NULL},
    /*044*/    {"�������", "�����±�,��0��ʼ����", 0, 0, SDT_INT, 0, NULL},

    /*045*/    {"ִ��״̬", "ִ��״̬", 0, 0, SDT_INT, 0, NULL},
    /*046*/    {"ֵ����", "ֵ����,ִ�н��ָ��", 0, 0, SDT_INT64, 0, NULL},

    /*047*/    {"ִ��״̬", "ִ��״̬", 0, 0, SDT_INT, 0, NULL},
    /*048*/    {"ֵ����", "ֵ����,ִ�н��ָ��", 0, 0, SDT_INT64, 0, NULL},

    /*049*/    {"ִ��״̬", "ִ��״̬", 0, 0, SDT_INT, 0, NULL},
    /*050*/    {"ֵ����", "ֵ����,ִ�н��ָ��", 0, 0, SDT_INT64, 0, NULL},

    /*051*/    {"ִ��״̬", "ִ��״̬", 0, 0, SDT_INT, 0, NULL},
    /*052*/    {"ֵ����", "ֵ����,ִ�н��ָ��", 0, 0, SDT_INT64, 0, NULL},

    /*053*/    {"ִ��״̬", "ִ��״̬", 0, 0, SDT_INT, 0, NULL},
    /*054*/    {"ֵ����", "ֵ����,ִ�н��ָ��", 0, 0, SDT_INT64, 0, NULL},

    /*055*/    {"������ֵ", "������ֵ", 0, 0, SDT_INT, 0, NULL},

    /*056*/    {"ִ��״̬", "ִ��״̬", 0, 0, SDT_INT, 0, NULL},
    /*057*/    {"������ֵ", "������ֵ", 0, 0, SDT_TEXT, 0, NULL},

    /*058*/    {"������ֵ", "������ֵ", 0, 0, SDT_BOOL, 0, NULL},

    /*059*/    {"������ֵ", "������ֵ", 0, 0, SDT_FLOAT, 0, NULL},

    /*060*/    {"������ֵ", "������ֵ", 0, 0, SDT_DOUBLE, 0, NULL},


    /*061*/    {"ִ��״̬", "��ʹ�� ȫ�ִ���JSִ��״̬() ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*062*/    {"object����", "js��object", 0, 0, SDT_INT64, 0, NULL},
    /*063*/    {"Ҫȡ����������", "������", 0, 0, SDT_TEXT, 0, 0},

    /*064*/    {"ִ��״̬", "ִ��״̬", 0, 0, SDT_INT, 0, NULL},
    /*065*/    {"�������", "�����±�,��0��ʼ����", 0, 0, SDT_INT, 0, NULL},
};

static ARG_INFO g_Args_tb[] =
{
    //������µĲ���
    /*000*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*001*/    {"���ģʽ", "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��", 0, 0, SDT_INT, 0, NULL},
    /*002*/    {"ѡ����ʽ", "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*003*/    {"Ԫ���±�", "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*004*/    {"��������", "��Ҫ��ȡ����ֵ������ ��: name", 0, 0, SDT_TEXT, 0, NULL},
    /*005*/    {"����ֵ", "��Ҫ��ȡ����ֵ������ ��: name", 0, 0, SDT_TEXT, 0, NULL},

    /*006*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*007*/    {"���ģʽ", "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��", 0, 0, SDT_INT, 0, NULL},
    /*008*/    {"ѡ����ʽ", "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*009*/    {"Ԫ���±�", "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*010*/    {"ѡ��״̬", "����Ϊ�����ѡ�и�ѡ���,Ϊ����ȡ��ѡ��", 0, 0, SDT_BOOL, 0, NULL},

    /*011*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*012*/    {"���ģʽ", "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��", 0, 0, SDT_INT, 0, NULL},
    /*013*/    {"ѡ����ʽ", "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*014*/    {"Ԫ���±�", "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*015*/    {"ѡ����", "ѡ����Ͽ��еĵڼ���,��Ŵ�0��ʼ", 0, 0, SDT_INT, 0, NULL},


    /*016*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*017*/    {"����", "����", 0, 0, SDT_TEXT, 0, NULL},

    /*018*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*019*/    {"���ŷ�ֵ", "���ŷ�ֵ", 0, 0, SDT_FLOAT, 0, NULL},

    /*020*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*021*/    {"����λ��", "�������������λ��", 0, 0, SDT_INT, 0, NULL},

    /*022*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*023*/    {"����λ��", "���ú��������λ��", 0, 0, SDT_INT, 0, NULL},


    /*024*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*025*/    {"�Ƿ����༭״̬", "Ϊ����򿪱༭ģʽ Ϊ����ر�", 0, 0, SDT_BOOL, 0, NULL},

    /*026*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*027*/    {"frameid", "���ID , 1�ǵ�ǰ��ҳ�����", 0, 0, SDT_INT, 0, NULL},


    /*028*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*029*/    {"��������", "���� getContent() setContent('content') �� sc.getContent('aaaa')", 0, 0, SDT_TEXT, 0, NULL},

    /*030*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*031*/    {"���ģʽ", "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��", 0, 0, SDT_INT, 0, NULL},
    /*032*/    {"ѡ����ʽ", "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*033*/    {"Ԫ���±�", "���ѡ����ʽ���صĽ��Ϊ�����ʱ��,Ĭ�ϵ����һ��Ԫ��,�˴�����ָ�����Ԫ�ص��±�,�±��1��ʼ,Ĭ��Ϊ1", 0, 0, SDT_INT, 1, AS_HAS_DEFAULT_VALUE},
    /*034*/    {"�Ƿ����", "��=����,��=������", 0, 0, SDT_BOOL, 1, NULL},

    /*035*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*036*/    {"���ģʽ", "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��", 0, 0, SDT_INT, 0, NULL},
    /*037*/    {"ѡ����ʽ", "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*038*/    {"ƫ��", "���������Ԫ�����и����ĺ��������,�����ģ��������ܻ��Ԫ�ط�Χ�ڲ�ͬ�ĵ���в���.���Դﵽ���õ�ģ��Ч��", 0, 0, SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
    /*039*/    {"�±�", "������ص�Ԫ�ش���1��,����ʹ�ø��±�ָ��Ԫ���±� ,��ʹ�����ѡ���� div.myclass>ul>li  ��᷵��������Ϊ myclass ��DIV�µ�UL�µ�li���� ,�˴��Ϳ���ָ��ȡ�ڼ���LI,�±��1��ʼ,Ĭ��Ϊ1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*040*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*041*/    {"���ģʽ", "��ʹ�� #���ģʽ_ ��ͷ�ĳ���,���忴����˵��", 0, 0, SDT_INT, 0, NULL},
    /*042*/    {"ѡ����ʽ", "ѡ����ʽ,��ѡ�����ģʽ���,����ģ��ģʽ id==xxx class==xxx xxx=xxx, JSģʽ #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*043*/    {"�±�", "������ص�Ԫ�ش���1��,����ʹ�ø��±�ָ��Ԫ���±� ,��ʹ�����ѡ���� div.myclass>ul>li  ��᷵��������Ϊ myclass ��DIV�µ�UL�µ�li���� ,�˴��Ϳ���ָ��ȡ�ڼ���LI,�±��1��ʼ,Ĭ��Ϊ1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*044*/    {"�¼�����", "��ʹ�� #�¼�_ ��ͷ�ĳ���", 0, 0, SDT_TEXT, 0, NULL},
    /*045*/    {"�ر��¼�ð��", "�ر�ð��������Ϊ ��", 0, 0, SDT_BOOL, 0, AS_HAS_DEFAULT_VALUE},
    /*046*/    {"�¼�����", "���Դ���ʱ��ʱ�����¼��������,��Ϊ��", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*047*/    {"WKE_TB", "��һ��WKE_��� ����", 0, 0, SDT_TYPE_WKE_TB, 0, NULL},
};

static ARG_INFO g_Args_SpecialFunction[] =
{
    //���⹦�ܷ����µĲ���
    /*000*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*001*/    {"�Ƿ���", "�� ������ , �ٹر�  Ĭ�Ͽ���", 0, 0, SDT_BOOL, 0, NULL},

    /*002*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*003*/    {"�Ƿ���", "�� ������ , �ٹر�  Ĭ�Ͽ���", 0, 0, SDT_BOOL, 0, NULL},

    /*004*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*005*/    {"�Ƿ���", "�� ������ , �ٹر�  Ĭ�Ͽ���", 0, 0, SDT_BOOL, 0, NULL},

    /*006*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},

    /*007*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*008*/    {"�Ƿ���", "�� ������ , �ٹر�  Ĭ�Ͽ���", 0, 0, SDT_BOOL, 0, NULL},

    /*009*/    {"Job", "Url���뿪ʼ �д���Ĳ���", 0, 0, SDT_INT, 0, NULL},

    /*010*/    {"Job", "Url���뿪ʼ �д���Ĳ���", 0, 0, SDT_INT, 0, NULL},
    /*011*/    {"HTTPͷ����", "Httpͷ�ֶ����� �� Accept , Content-Type ��...", 0, 0, SDT_TEXT, 0, NULL},
    /*012*/    {"HTTPͷֵ", "Httpͷ�ֶζ�Ӧֵ, ��: text/javascript , appliction/json ��...", 0, 0, SDT_TEXT, 0, NULL},

    /*013*/    {"Job", "Url���뿪ʼ �д���Ĳ���", 0, 0, SDT_INT, 0, NULL},
    /*014*/    {"MIME����", "MIMEType...", 0, 0, SDT_TEXT, 0, NULL},

    /*015*/    {"Job", "Url���뿪ʼ �д���Ĳ���", 0, 0, SDT_INT, 0, NULL},
    /*016*/    {"Url", "URL...", 0, 0, SDT_TEXT, 0, NULL},

    /*017*/    {"Job", "Url���뿪ʼ �д���Ĳ���", 0, 0, SDT_INT, 0, NULL},
    /*018*/    {"����", "����", 0, 0, SDT_BIN, 0,   NULL},
    /*019*/    {"���ݳ���", "���ݳ���", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*020*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*021*/    {"�Ƿ���", "�� ������ , �ٹر�  Ĭ�Ͽ���", 0, 0, SDT_BOOL, 0, NULL},

    /*022*/    {"WebView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*023*/    {"�Ƿ���", "�� ������ , �ٹر�  Ĭ�Ͽ���", 0, 0, SDT_BOOL, 0, NULL},

    /*024*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*025*/    {"debugString", "showDevTools ", 0, 0, SDT_TEXT, 0, NULL},
    /*026*/    {"configParam", ", ע��param��ʱ������utf8����", 0, 0, SDT_TEXT, 0, NULL},

    /*027*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},

    /*028*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*029*/    {"frameid", "���ID", 0, 0, SDT_INT, 0, NULL},

    /*030*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*031*/    {"frameid", "���ID", 0, 0, SDT_INT, 0, NULL},

    /*032*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*033*/    {"x", "������", 0, 0, SDT_INT, 0, NULL},
    /*034*/    {"y", "������", 0, 0, SDT_INT, 0, NULL},

    /*035*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*036*/    {"x", "������", 0, 0, SDT_INT, 0, NULL},
    /*037*/    {"y", "������", 0, 0, SDT_INT, 0, NULL},

    /*038*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*039*/    {"x", "������", 0, 0, SDT_INT, 0, NULL},
    /*040*/    {"y", "������", 0, 0, SDT_INT, 0, NULL},

    /*041*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*042*/    {"x", "������", 0, 0, SDT_INT, 0, NULL},
    /*043*/    {"y", "������", 0, 0, SDT_INT, 0, NULL},

    /*044*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*045*/    {"x", "������", 0, 0, SDT_INT, 0, NULL},
    /*046*/    {"y", "������", 0, 0, SDT_INT, 0, NULL},

    /*047*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*048*/    {"x", "������", 0, 0, SDT_INT, 0, NULL},
    /*049*/    {"y", "������", 0, 0, SDT_INT, 0, NULL},

    /*050*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*051*/    {"x", "������", 0, 0, SDT_INT, 0, NULL},
    /*052*/    {"y", "������", 0, 0, SDT_INT, 0, NULL},

    /*053*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*054*/    {"������", "��������ʹ�� �� #�˸��....", 0, 0, SDT_INT, 0, NULL},

    /*055*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*056*/    {"������", "��������ʹ�� �� #K�� #A��....", 0, 0, SDT_INT, 0, NULL},

    /*057*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*058*/    {"������", "��������ʹ�� �� #K�� #A��....", 0, 0, SDT_INT, 0, NULL},

    /*059*/    {"Job", "Url���뿪ʼ �д���Ĳ���", 0, 0, SDT_INT, 0, NULL},
    /*060*/    {"Job", "Url���뿪ʼ �д���Ĳ���", 0, 0, SDT_INT, 0, NULL},

    /*061*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*062*/    {"Ԫ����", "Ԫ����", 0, 0, SDT_TYPE_POSTELEMENTS, 0, NULL},

    /*063*/    {"post����", "����post���ݷ��ص�ֵ", 0, 0, SDT_INT, 0, NULL},
    /*064*/    {"post����", "����post�����鷵�ص�ֵ", 0, 0, SDT_INT, 0, NULL},

    /*065*/    {"webView", "WebViewָ��,��ʹ�� ����WEB�����.ȡWebView()  ��ȡ", 0, 0, SDT_INT, 0, NULL},
    /*066*/    {"url", "post��url", 0, 0, SDT_TEXT, 0, NULL},
    /*067*/    {"post����", "post������", 0, 0, SDT_BIN, 0, NULL},

    /*068*/    { "Job", "�¼���Ĳ���", 0, 0, SDT_INT, 0, NULL },
    /*069*/    { "key", "Ҫ��ȡ�ĸ�ͷ", 0, 0, SDT_TEXT, 0, NULL },


};

//��������Ĳ�������
static ARG_INFO g_Args_All[] =
{
    // 1=��������, 2=������ϸ����, 3=ָ��ͼ������,��1��ʼ,0��ʾ��, 4=ͼ����Ŀ(��������)
    // 5=��������, 6=����Ĭ��ֵ,   7=������־ AS_ ��ͷ����

    /*000*/    {"dll·��", "node.dll������·��", 0, 0, SDT_TEXT, 0, NULL},
    /*001*/    {"utf8�ı�", "utf8������ı�,ֻ֧���ı�ָ��,�ı���,���ֽڼ�", 0, 0, _SDT_ALL, 0, NULL},
    /*002*/    {"ansi�ı�", "ansi������ı�", 0, 0, SDT_TEXT, 0, NULL},
    /*003*/    {"Unicode�ı�", "Unicode������ı�", 0, 0, SDT_BIN, 0, NULL},
    /*004*/    {"��������С", "���س���ǰ���������ڴ��С,��λΪ�ֽ�", 0, 0, SDT_INT, 0, AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY},
    /*005*/    {"��ֵ������", "���س����ֵ���������ڴ��С,��λΪ�ֽ�", 0, 0, SDT_INT, 0, AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY},
    /*006*/    {"��ʽ", "������鿴c���Խ���, ���õ�%s=�ı�(����ʱ����), %d=����,%u=�޷�������,%p=ָ��,%x16=����,%%=%....", 0, 0, SDT_TEXT, 0,  0},
    /*007*/    {"����", "", 0, 0, _SDT_ALL, 0, 0},

};

// ������������Ҫ��������Ϣ����
#define WKE_DEF_CMDINFO(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    { _szName, ______E_FNENAME(_szEgName), _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo },


CMD_INFO g_cmdInfo_wke_global_var[] =
{
    WKE_DEF(WKE_DEF_CMDINFO)
};

int g_cmdInfo_wke_global_var_count = sizeof(g_cmdInfo_wke_global_var) / sizeof(g_cmdInfo_wke_global_var[0]);



#endif







