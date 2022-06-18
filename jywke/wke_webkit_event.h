#pragma once
#include "wke_webkit_header.h"

#define EVENT_DOCUMENTREADY         0   // �ĵ�����
#define EVENT_TITLECHANGE           1   // ����ı��¼�
#define EVENT_URLCHANGE             2   // url�ı��¼�
#define EVENT_NAVIGATION            3   // �������µ�ַ�ı��¼�
#define EVENT_CREATEWENVIEW         4   // �������´���,�ᴴ��һ���´���
#define EVENT_DOCUMENTED            5   // �ĵ��������
#define EVENT_CONSOLE               6   // ����̨��Ϣ���
#define EVENT_ALERTBOX              7   // Alert������
#define EVENT_CONFIRMBOX            8   // Confirm������
#define EVENT_PROMPTBOX             9   // Prompt������
#define EVENT_DOWNLOAD              10  // ���������ļ�
#define EVENT_LOADURLING            11  // url���뿪ʼ
#define EVENT_LOADURLEND            12  // url�������
#define EVENT_MOUSEHOVERURL         13  // �����������

#define EVENT_LDOWN                 14  // �������
#define EVENT_LUP                   15  // ����ſ�
#define EVENT_LDBLCLK               16  // ���˫��
#define EVENT_RDOWN                 17  // �Ҽ�����
#define EVENT_RUP                   18  // �Ҽ��ſ�
#define EVENT_MOUSEMOVE             19  // ����ƶ�
#define EVENT_SETFOCUS              20  // ��ý���
#define EVENT_KILLFOCUS             21  // ʧȥ����
#define EVENT_KEYDOWN               22  // ĳ������
#define EVENT_KEYUP                 23  // ĳ������
#define EVENT_CHAR                  24  // �ַ�����
#define EVENT_SCROLL                25  // ������Ϣ

#define EVENT_NEWWNDCREATEING       26  // �´��ڼ�������
#define EVENT_NEWWNDCREATEEND       27  // �´��ڴ������
#define EVENT_NEWWNDCLOSE           28  // �´��ڿɷ�ر�
#define EVENT_NEWWNDDESTROY         29  // �´��ڼ�������

#define EVENT_DLGCREATEING          30  // �����򿪶Ի���
#define EVENT_ICONCHANGED           31  // ��ҳͼ��ı�

#define EVENT_OPENFILENAME          32  // ���ļ��Ի��򼴽���
#define EVENT_SAVEFILENAME          33  // �����ļ��Ի��򼴽���




// ���ṹ, ���໯, ��¼ԭ���ڹ���,���ھ��,webView
void __fill_wnd_data(PWEBKIT_PROPERTYEX data, wkeWebView webView);

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam);




//����ı�ص�
void OnwkeTitleChanged(wkeWebView webView, void* param, const wkeString title);

//URL�ı�ص�
void OnwkeURLChanged(wkeWebView webView, void* param, const wkeString url);
void OnwkeURLChanged2(wkeWebView webView, void* param, wkeWebFrameHandle frameId, const wkeString url);//�������������ص�һ��,ֻ�Ƕ���һ������

//ҳ�����κ���Ҫˢ�µĵط��������ô˻ص�
void OnwkePaintUpdated(wkeWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy);
void OnwkePaintBitUpdated(wkeWebView webView, void* param, const void* buffer, const wkeRect* r, int width, int height);

//��ҳ����alert���ߵ�����ӿ�����Ļص�
void OnwkeAlertBox(wkeWebView webView, void* param, const wkeString message);
//ConfirmBoxָ����Ϣ�� OK ��ȡ����ť�ĶԻ���
bool OnwkeConfirmBox(wkeWebView webView, void* param, const wkeString msg);
bool OnwkePromptBox(wkeWebView webView, void* param, const wkeString msg, const wkeString defaultResult, wkeString result);

//��ҳ��ʼ����������ص�, �����������µ�ַ
bool OnwkeNavigation(wkeWebView webView, void* param, wkeNavigationType navigationType, wkeString url);

//��ҳ���a��ǩ�����´���ʱ�������ص�, �����������´���
wkeWebView OnwkeCreateView(wkeWebView webView, void* param, wkeNavigationType navigationType, const wkeString url, const wkeWindowFeatures* windowFeatures);

//��Ӧjs���body onload�¼�
void OnwkeDocumentReady(wkeWebView webView, void* param);
void OnwkeDocumentReady2(wkeWebView webView, void* param, wkeWebFrameHandle frameId);

//�ĵ��������
void OnwkeLoadingFinish(wkeWebView webView, void* param, const wkeString url, wkeLoadingResult result, const wkeString failedReason);

//ҳ�������¼��ص������ĳЩ���ӣ��������ػ����
bool OnwkeDownload(wkeWebView webView, void* param, const char* url);

//һ�����������ͺ��յ�������response�����ص�
bool OnwkeNetResponse(wkeWebView webView, void* param, const utf8* url, wkeNetJob job);

//��ҳ����console����
void OnConsoleMessage(wkeWebView webView, void* param, wkeConsoleLevel level, const wkeString message, const wkeString sourceName, unsigned sourceLine, const wkeString stackTrace);

//��ʱδʵ��
void OnwkeCallUiThread(wkeWebView webView, wkeOnCallUiThread func, void* param);

//�κ�����������ǰ�ᴥ���˻ص�
bool OnwkeLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job);

//����url���
void OnwkeLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len);

//video�ȶ�ý���ǩ����ʱ�����˻ص�
void OnwkeWillMediaLoad(wkeWebView webView, void* param, const char* url, wkeMediaLoadInfo* info);

//��껮����Ԫ�أ�����ǣ�����ô˻ص���������a��ǩ��url
void OnwkeMouseOverUrlChanged(wkeWebView webView, void* param, const wkeString url);

//javascript��v8ִ�л���������ʱ�����˻ص�, ע�⣺ÿ��frame����ʱ���ᴥ���˻ص�
void OnwkeDidCreateScriptContext(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId);

//ÿ��frame��javascript��v8ִ�л������ر�ʱ�����˻ص�
void OnwkeWillReleaseScriptContext(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int worldId);

// �����봰�ڿɷ�ر�
bool handleWindowClosing(wkeWebView webWindow, void* param);

// �����봰�ڼ�������
void handleWindowDestroy(wkeWebView webWindow, void* param);

void wke_SubWebviewWindow(PWEBKIT_PROPERTYEX data);

