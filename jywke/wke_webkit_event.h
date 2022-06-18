#pragma once
#include "wke_webkit_header.h"

#define EVENT_DOCUMENTREADY         0   // 文档就绪
#define EVENT_TITLECHANGE           1   // 标题改变事件
#define EVENT_URLCHANGE             2   // url改变事件
#define EVENT_NAVIGATION            3   // 导航到新地址改变事件
#define EVENT_CREATEWENVIEW         4   // 导航到新窗口,会创建一个新窗口
#define EVENT_DOCUMENTED            5   // 文档载入完毕
#define EVENT_CONSOLE               6   // 控制台消息输出
#define EVENT_ALERTBOX              7   // Alert被调用
#define EVENT_CONFIRMBOX            8   // Confirm被调用
#define EVENT_PROMPTBOX             9   // Prompt被调用
#define EVENT_DOWNLOAD              10  // 正在下载文件
#define EVENT_LOADURLING            11  // url载入开始
#define EVENT_LOADURLEND            12  // url载入结束
#define EVENT_MOUSEHOVERURL         13  // 鼠标移入链接

#define EVENT_LDOWN                 14  // 左键按下
#define EVENT_LUP                   15  // 左键放开
#define EVENT_LDBLCLK               16  // 左键双击
#define EVENT_RDOWN                 17  // 右键按下
#define EVENT_RUP                   18  // 右键放开
#define EVENT_MOUSEMOVE             19  // 鼠标移动
#define EVENT_SETFOCUS              20  // 获得焦点
#define EVENT_KILLFOCUS             21  // 失去焦点
#define EVENT_KEYDOWN               22  // 某键按下
#define EVENT_KEYUP                 23  // 某键弹起
#define EVENT_CHAR                  24  // 字符输入
#define EVENT_SCROLL                25  // 滚动信息

#define EVENT_NEWWNDCREATEING       26  // 新窗口即将创建
#define EVENT_NEWWNDCREATEEND       27  // 新窗口创建完毕
#define EVENT_NEWWNDCLOSE           28  // 新窗口可否关闭
#define EVENT_NEWWNDDESTROY         29  // 新窗口即将销毁

#define EVENT_DLGCREATEING          30  // 即将打开对话框
#define EVENT_ICONCHANGED           31  // 网页图标改变

#define EVENT_OPENFILENAME          32  // 打开文件对话框即将打开
#define EVENT_SAVEFILENAME          33  // 保存文件对话框即将打开




// 填充结构, 子类化, 记录原窗口过程,窗口句柄,webView
void __fill_wnd_data(PWEBKIT_PROPERTYEX data, wkeWebView webView);

LRESULT CALLBACK CBTProc(int nCode, WPARAM wParam, LPARAM lParam);




//标题改变回调
void OnwkeTitleChanged(wkeWebView webView, void* param, const wkeString title);

//URL改变回调
void OnwkeURLChanged(wkeWebView webView, void* param, const wkeString url);
void OnwkeURLChanged2(wkeWebView webView, void* param, wkeWebFrameHandle frameId, const wkeString url);//这个和上面这个回调一样,只是多了一个参数

//页面有任何需要刷新的地方，将调用此回调
void OnwkePaintUpdated(wkeWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy);
void OnwkePaintBitUpdated(wkeWebView webView, void* param, const void* buffer, const wkeRect* r, int width, int height);

//网页调用alert会走到这个接口填入的回调
void OnwkeAlertBox(wkeWebView webView, void* param, const wkeString message);
//ConfirmBox指定消息和 OK 及取消按钮的对话框
bool OnwkeConfirmBox(wkeWebView webView, void* param, const wkeString msg);
bool OnwkePromptBox(wkeWebView webView, void* param, const wkeString msg, const wkeString defaultResult, wkeString result);

//网页开始浏览将触发回调, 即将导航到新地址
bool OnwkeNavigation(wkeWebView webView, void* param, wkeNavigationType navigationType, wkeString url);

//网页点击a标签创建新窗口时将触发回调, 即将导航到新窗口
wkeWebView OnwkeCreateView(wkeWebView webView, void* param, wkeNavigationType navigationType, const wkeString url, const wkeWindowFeatures* windowFeatures);

//对应js里的body onload事件
void OnwkeDocumentReady(wkeWebView webView, void* param);
void OnwkeDocumentReady2(wkeWebView webView, void* param, wkeWebFrameHandle frameId);

//文档载入完毕
void OnwkeLoadingFinish(wkeWebView webView, void* param, const wkeString url, wkeLoadingResult result, const wkeString failedReason);

//页面下载事件回调。点击某些链接，触发下载会调用
bool OnwkeDownload(wkeWebView webView, void* param, const char* url);

//一个网络请求发送后，收到服务器response触发回调
bool OnwkeNetResponse(wkeWebView webView, void* param, const utf8* url, wkeNetJob job);

//网页调用console触发
void OnConsoleMessage(wkeWebView webView, void* param, wkeConsoleLevel level, const wkeString message, const wkeString sourceName, unsigned sourceLine, const wkeString stackTrace);

//暂时未实现
void OnwkeCallUiThread(wkeWebView webView, wkeOnCallUiThread func, void* param);

//任何网络请求发起前会触发此回调
bool OnwkeLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job);

//载入url完毕
void OnwkeLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len);

//video等多媒体标签创建时触发此回调
void OnwkeWillMediaLoad(wkeWebView webView, void* param, const char* url, wkeMediaLoadInfo* info);

//鼠标划过的元素，如果是，则调用此回调，并发送a标签的url
void OnwkeMouseOverUrlChanged(wkeWebView webView, void* param, const wkeString url);

//javascript的v8执行环境被创建时触发此回调, 注意：每个frame创建时都会触发此回调
void OnwkeDidCreateScriptContext(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int extensionGroup, int worldId);

//每个frame的javascript的v8执行环境被关闭时触发此回调
void OnwkeWillReleaseScriptContext(wkeWebView webView, void* param, wkeWebFrameHandle frameId, void* context, int worldId);

// 新载入窗口可否关闭
bool handleWindowClosing(wkeWebView webWindow, void* param);

// 新载入窗口即将销毁
void handleWindowDestroy(wkeWebView webWindow, void* param);

void wke_SubWebviewWindow(PWEBKIT_PROPERTYEX data);

