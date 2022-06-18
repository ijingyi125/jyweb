/*
*
* wolar@qq.com
* http://miniblink.net
* https://github.com/weolar/miniblink49
* https://weolar.github.io/miniblink/doc-main.html api�ĵ���ַ
* licence Apache-2.0
*
*/

#ifndef MB_DEFINE_H
#define MB_DEFINE_H

#include <windows.h>

//////////////////////////////////////////////////////////////////////////

#define MB_CALL_TYPE __stdcall

typedef struct _mbRect {
    int x;
    int y;
    int w;
    int h;
} mbRect;

typedef struct _mbPoint {
    int x;
    int y;
} mbPoint;

typedef struct _mbSize {
    int w;
    int h;
} mbSize;

typedef enum {
    MB_LBUTTON = 0x01,
    MB_RBUTTON = 0x02,
    MB_SHIFT = 0x04,
    MB_CONTROL = 0x08,
    MB_MBUTTON = 0x10,
} mbMouseFlags;

typedef enum {
    MB_EXTENDED = 0x0100,
    MB_REPEAT = 0x4000,
} mbKeyFlags;

typedef enum {
    MB_MSG_MOUSEMOVE = 0x0200,
    MB_MSG_LBUTTONDOWN = 0x0201,
    MB_MSG_LBUTTONUP = 0x0202,
    MB_MSG_LBUTTONDBLCLK = 0x0203,
    MB_MSG_RBUTTONDOWN = 0x0204,
    MB_MSG_RBUTTONUP = 0x0205,
    MB_MSG_RBUTTONDBLCLK = 0x0206,
    MB_MSG_MBUTTONDOWN = 0x0207,
    MB_MSG_MBUTTONUP = 0x0208,
    MB_MSG_MBUTTONDBLCLK = 0x0209,
    MB_MSG_MOUSEWHEEL = 0x020A,
} mbMouseMsg;

#if !defined(__cplusplus)
#ifndef HAVE_WCHAR_T
typedef unsigned short wchar_t;
#endif
#endif

#include <stdbool.h>

#if defined(__cplusplus)
#define MB_EXTERN_C extern "C"
#else
#define MB_EXTERN_C
#endif

typedef char utf8;

typedef enum {
    MB_PROXY_NONE,
    MB_PROXY_HTTP,
    MB_PROXY_SOCKS4,
    MB_PROXY_SOCKS4A,
    MB_PROXY_SOCKS5,
    MB_PROXY_SOCKS5HOSTNAME
} mbProxyType;

typedef struct {
    mbProxyType type;
    char hostname[100];
    unsigned short port;
    char username[50];
    char password[50];
} mbProxy;

typedef enum _mbSettingMask {
    MB_SETTING_PROXY = 1,
    MB_ENABLE_NODEJS = 1 << 3,
    MB_ENABLE_DISABLE_H5VIDEO = 1 << 4,
} mbSettingMask;

typedef void(MB_CALL_TYPE* mbOnBlinkThreadInitCallback)(void* param);

typedef struct _mbSettings {
    mbProxy proxy;
    unsigned int mask;
    mbOnBlinkThreadInitCallback blinkThreadInitCallback;
    void* blinkThreadInitCallbackParam;
} mbSettings;

typedef struct _mbViewSettings {
    int size;
    unsigned int bgColor;
} mbViewSettings;

typedef void* mbWebFrameHandle;
typedef void* mbNetJob;

#if defined(__cplusplus)
namespace mb { class MbWebView; };
typedef mb::MbWebView* mbWebView;
#else
struct _tagMbWebView;
typedef struct _tagMbWebView* MBWebView;
#endif

typedef BOOL(*mbCookieVisitor)(
    void* params,
    const char* name,
    const char* value,
    const char* domain,
    const char* path, // If |path| is non-empty only URLs at or below the path will get the cookie value.
    int secure, // If |secure| is true the cookie will only be sent for HTTPS requests.
    int httpOnly, // If |httponly| is true the cookie will only be sent for HTTP requests.
    int* expires // The cookie expiration date is only valid if |has_expires| is true.
    );

typedef enum {
    mbCookieCommandClearAllCookies,
    mbCookieCommandClearSessionCookies,
    mbCookieCommandFlushCookiesToFile,
    mbCookieCommandReloadCookiesFromFile,
} mbCookieCommand;

typedef enum {
    MB_NAVIGATION_TYPE_LINKCLICK,
    MB_NAVIGATION_TYPE_FORMSUBMITTE,
    MB_NAVIGATION_TYPE_BACKFORWARD,
    MB_NAVIGATION_TYPE_RELOAD,
    MB_NAVIGATION_TYPE_FORMRESUBMITT,
    MB_NAVIGATION_TYPE_OTHER
} mbNavigationType;

typedef enum {
    kMbCursorInfoPointer,
    kMbCursorInfoCross,
    kMbCursorInfoHand,
    kMbCursorInfoIBeam,
    kMbCursorInfoWait,
    kMbCursorInfoHelp,
    kMbCursorInfoEastResize,
    kMbCursorInfoNorthResize,
    kMbCursorInfoNorthEastResize,
    kMbCursorInfoNorthWestResize,
    kMbCursorInfoSouthResize,
    kMbCursorInfoSouthEastResize,
    kMbCursorInfoSouthWestResize,
    kMbCursorInfoWestResize,
    kMbCursorInfoNorthSouthResize,
    kMbCursorInfoEastWestResize,
    kMbCursorInfoNorthEastSouthWestResize,
    kMbCursorInfoNorthWestSouthEastResize,
    kMbCursorInfoColumnResize,
    kMbCursorInfoRowResize,
    kMbCursorInfoMiddlePanning,
    kMbCursorInfoEastPanning,
    kMbCursorInfoNorthPanning,
    kMbCursorInfoNorthEastPanning,
    kMbCursorInfoNorthWestPanning,
    kMbCursorInfoSouthPanning,
    kMbCursorInfoSouthEastPanning,
    kMbCursorInfoSouthWestPanning,
    kMbCursorInfoWestPanning,
    kMbCursorInfoMove,
    kMbCursorInfoVerticalText,
    kMbCursorInfoCell,
    kMbCursorInfoContextMenu,
    kMbCursorInfoAlias,
    kMbCursorInfoProgress,
    kMbCursorInfoNoDrop,
    kMbCursorInfoCopy,
    kMbCursorInfoNone,
    kMbCursorInfoNotAllowed,
    kMbCursorInfoZoomIn,
    kMbCursorInfoZoomOut,
    kMbCursorInfoGrab,
    kMbCursorInfoGrabbing,
    kMbCursorInfoCustom
} mbCursorInfoType;

typedef struct {
    int x;
    int y;
    int width;
    int height;

    BOOL menuBarVisible;
    BOOL statusBarVisible;
    BOOL toolBarVisible;
    BOOL locationBarVisible;
    BOOL scrollbarsVisible;
    BOOL resizable;
    BOOL fullscreen;
} mbWindowFeatures;

typedef struct _mbPrintSettings {
    int structSize;
    int dpi;
    int width;
    int height;
    int marginTop;
    int marginBottom;
    int marginLeft;
    int marginRight;
    BOOL isPrintPageHeadAndFooter;
    BOOL isPrintBackgroud;
} mbPrintSettings;

struct mbString;
typedef mbString* mbStringPtr;

typedef struct _mbMemBuf {
    int size;
    void* data;
    size_t length;
} mbMemBuf;

typedef struct {
    struct Item {
        enum mbStorageType {
            // String data with an associated MIME type. Depending on the MIME type, there may be
            // optional metadata attributes as well.
            StorageTypeString,
            // Stores the name of one file being dragged into the renderer.
            StorageTypeFilename,
            // An image being dragged out of the renderer. Contains a buffer holding the image data
            // as well as the suggested name for saving the image to.
            StorageTypeBinaryData,
            // Stores the filesystem URL of one file being dragged into the renderer.
            StorageTypeFileSystemFile,
        } storageType;

        // Only valid when storageType == StorageTypeString.
        mbMemBuf* stringType;
        mbMemBuf* stringData;

        // Only valid when storageType == StorageTypeFilename.
        mbMemBuf* filenameData;
        mbMemBuf* displayNameData;

        // Only valid when storageType == StorageTypeBinaryData.
        mbMemBuf* binaryData;

        // Title associated with a link when stringType == "text/uri-list".
        // Filename when storageType == StorageTypeBinaryData.
        mbMemBuf* title;

        // Only valid when storageType == StorageTypeFileSystemFile.
        mbMemBuf* fileSystemURL;
        long long fileSystemFileSize;

        // Only valid when stringType == "text/html".
        mbMemBuf* baseURL;
    };

    struct Item* m_itemList;
    int m_itemListLength;

    int m_modifierKeyState; // State of Shift/Ctrl/Alt/Meta keys.
    mbMemBuf* m_filesystemId;
} mbWebDragData;

typedef enum {
    mbWebDragOperationNone = 0,
    mbWebDragOperationCopy = 1,
    mbWebDragOperationLink = 2,
    mbWebDragOperationGeneric = 4,
    mbWebDragOperationPrivate = 8,
    mbWebDragOperationMove = 16,
    mbWebDragOperationDelete = 32,
    mbWebDragOperationEvery = 0xffffffff
} mbWebDragOperation;

typedef mbWebDragOperation mbWebDragOperationsMask;

typedef enum {
    MB_RESOURCE_TYPE_MAIN_FRAME = 0,       // top level page
    MB_RESOURCE_TYPE_SUB_FRAME = 1,        // frame or iframe
    MB_RESOURCE_TYPE_STYLESHEET = 2,       // a CSS stylesheet
    MB_RESOURCE_TYPE_SCRIPT = 3,           // an external script
    MB_RESOURCE_TYPE_IMAGE = 4,            // an image (jpg/gif/png/etc)
    MB_RESOURCE_TYPE_FONT_RESOURCE = 5,    // a font
    MB_RESOURCE_TYPE_SUB_RESOURCE = 6,     // an "other" subresource.
    MB_RESOURCE_TYPE_OBJECT = 7,           // an object (or embed) tag for a plugin,
                                            // or a resource that a plugin requested.
                                            MB_RESOURCE_TYPE_MEDIA = 8,            // a media resource.
                                            MB_RESOURCE_TYPE_WORKER = 9,           // the main resource of a dedicated
                                                                                    // worker.
                                                                                    MB_RESOURCE_TYPE_SHARED_WORKER = 10,   // the main resource of a shared worker.
                                                                                    MB_RESOURCE_TYPE_PREFETCH = 11,        // an explicitly requested prefetch
                                                                                    MB_RESOURCE_TYPE_FAVICON = 12,         // a favicon
                                                                                    MB_RESOURCE_TYPE_XHR = 13,             // a XMLHttpRequest
                                                                                    MB_RESOURCE_TYPE_PING = 14,            // a ping request for <a ping>
                                                                                    MB_RESOURCE_TYPE_SERVICE_WORKER = 15,  // the main resource of a service worker.
                                                                                    MB_RESOURCE_TYPE_LAST_TYPE
} mbResourceType;

typedef enum _mbRequestType {
    kMbRequestTypeInvalidation,
    kMbRequestTypeGet,
    kMbRequestTypePost,
    kMbRequestTypePut,
} mbRequestType;

typedef enum _mbMenuItemId {
    kMbMenuSelectedAllId = 1 << 1,
    kMbMenuSelectedTextId = 1 << 2,
    kMbMenuUndoId = 1 << 3,
    kMbMenuCopyImageId = 1 << 4,
    kMbMenuInspectElementAtId = 1 << 5,
    kMbMenuCutId = 1 << 6,
    kMbMenuPasteId = 1 << 7,
    kMbMenuPrintId = 1 << 8,
    kMbMenuGoForwardId = 1 << 9,
    kMbMenuGoBackId = 1 << 10,
    kMbMenuReloadId = 1 << 11,
} mbMenuItemId;

//////////////////////////////////////////////////////////////////////////

typedef enum {
    kMbJsTypeNumber = 0,
    kMbJsTypeString = 1,
    kMbJsTypeBool = 2,
    //kMbJsTypeObject = 3,
    //kMbJsTypeFunction = 4,
    kMbJsTypeUndefined = 5,
    //kMbJsTypeArray = 6,
    kMbJsTypeNull = 7,
} mbJsType;

typedef long long int64_t;
typedef int64_t mbJsValue;
typedef void* mbJsExecState;

typedef void(MB_CALL_TYPE* mbOnGetPdfPageDataCallback)(mbWebView webView, void* param, void* data, size_t size);

typedef void(MB_CALL_TYPE* mbRunJsCallback)(mbWebView webView, void* param, mbJsExecState es, mbJsValue v);
typedef void(MB_CALL_TYPE* mbJsQueryCallback)(mbWebView webView, void* param, mbJsExecState es, int64_t queryId, int customMsg, const utf8* request);

typedef void(MB_CALL_TYPE* mbTitleChangedCallback)(mbWebView webView, void* param, const utf8* title);
typedef void(MB_CALL_TYPE* mbMouseOverUrlChangedCallback)(mbWebView webView, void* param, const utf8* url);
typedef void(MB_CALL_TYPE* mbURLChangedCallback)(mbWebView webView, void* param, const utf8* url, BOOL canGoBack, BOOL canGoForward);
typedef void(MB_CALL_TYPE* mbURLChangedCallback2)(mbWebView webView, void* param, mbWebFrameHandle frameId, const utf8* url);
typedef void(MB_CALL_TYPE* mbPaintUpdatedCallback)(mbWebView webView, void* param, const HDC hdc, int x, int y, int cx, int cy);
typedef void(MB_CALL_TYPE* mbPaintBitUpdatedCallback)(mbWebView webView, void* param, const void* buffer, const mbRect* r, int width, int height);
typedef void(MB_CALL_TYPE* mbAlertBoxCallback)(mbWebView webView, void* param, const utf8* msg);
typedef BOOL(MB_CALL_TYPE* mbConfirmBoxCallback)(mbWebView webView, void* param, const utf8* msg);
typedef mbStringPtr(MB_CALL_TYPE* mbPromptBoxCallback)(mbWebView webView, void* param, const utf8* msg, const utf8* defaultResult);
typedef BOOL(MB_CALL_TYPE* mbNavigationCallback)(mbWebView webView, void* param, mbNavigationType navigationType, const utf8* url);
typedef mbWebView(MB_CALL_TYPE* mbCreateViewCallback)(mbWebView webView, void* param, mbNavigationType navigationType, const utf8* url, const mbWindowFeatures* windowFeatures);
typedef void(MB_CALL_TYPE* mbDocumentReadyCallback)(mbWebView webView, void* param, mbWebFrameHandle frameId);
typedef BOOL(MB_CALL_TYPE* mbCloseCallback)(mbWebView webView, void* param, void* unuse);
typedef BOOL(MB_CALL_TYPE* mbDestroyCallback)(mbWebView webView, void* param, void* unuse);
typedef void(MB_CALL_TYPE* mbOnShowDevtoolsCallback)(mbWebView webView, void* param);

typedef enum {
    MB_LOADING_SUCCEEDED,
    MB_LOADING_FAILED,
    MB_LOADING_CANCELED
} mbLoadingResult;

typedef void(MB_CALL_TYPE* mbLoadingFinishCallback)(mbWebView webView, void* param, mbWebFrameHandle frameId, const utf8* url, mbLoadingResult result, const utf8* failedReason);
typedef BOOL(MB_CALL_TYPE* mbDownloadCallback)(mbWebView webView, void* param, mbWebFrameHandle frameId, const char* url, void* downloadJob);

typedef enum {
    mbLevelDebug = 4,
    mbLevelLog = 1,
    mbLevelInfo = 5,
    mbLevelWarning = 2,
    mbLevelError = 3,
    mbLevelRevokedError = 6,
    mbLevelLast = mbLevelInfo
} mbConsoleLevel;
typedef void(MB_CALL_TYPE* mbConsoleCallback)(mbWebView webView, void* param, mbConsoleLevel level, const utf8* message, const utf8* sourceName, unsigned sourceLine, const utf8* stackTrace);

typedef void(MB_CALL_TYPE* mbOnCallUiThread)(mbWebView webView, void* paramOnInThread);
typedef void(MB_CALL_TYPE* mbCallUiThread)(mbWebView webView, mbOnCallUiThread func, void* param);

//mbNet--------------------------------------------------------------------------------------
typedef BOOL(MB_CALL_TYPE* mbLoadUrlBeginCallback)(mbWebView webView, void* param, const char* url, void* job);
typedef void(MB_CALL_TYPE* mbLoadUrlEndCallback)(mbWebView webView, void* param, const char* url, void* job, void* buf, int len);
typedef void(MB_CALL_TYPE* mbDidCreateScriptContextCallback)(mbWebView webView, void* param, mbWebFrameHandle frameId, void* context, int extensionGroup, int worldId);
typedef void(MB_CALL_TYPE* mbWillReleaseScriptContextCallback)(mbWebView webView, void* param, mbWebFrameHandle frameId, void* context, int worldId);
typedef BOOL(MB_CALL_TYPE* mbNetResponseCallback)(mbWebView webView, void* param, const char* url, void* job);
typedef void(MB_CALL_TYPE* mbNetGetFaviconCallback)(mbWebView webView, void* param, const utf8* url, mbMemBuf* buf);

enum MbAsynRequestState {
    kMbAsynRequestStateOk = 0,
    kMbAsynRequestStateFail = 1,
};

typedef void(MB_CALL_TYPE* mbCanGoBackForwardCallback)(mbWebView webView, void* param, MbAsynRequestState state, BOOL b);
typedef void(MB_CALL_TYPE* mbGetCookieCallback)(mbWebView webView, void* param, MbAsynRequestState state, const utf8* cookie);

typedef void* v8ContextPtr;
typedef void* v8Isolate;

typedef void(MB_CALL_TYPE* mbGetMHTMLCallback)(mbWebView webView, void* param, const utf8* mhtml);
typedef void(MB_CALL_TYPE* mbGetContentAsMarkupCallback)(mbWebView webView, void* param, const utf8* content, size_t size);

typedef struct mbWebUrlRequest* mbWebUrlRequestPtr;
typedef struct mbWebUrlResponse* mbWebUrlResponsePtr;

typedef void(MB_CALL_TYPE* mbOnUrlRequestWillRedirectCallback)(mbWebView webView, void* param, mbWebUrlRequestPtr oldRequest, mbWebUrlRequestPtr request, mbWebUrlResponsePtr redirectResponse);
typedef void(MB_CALL_TYPE* mbOnUrlRequestDidReceiveResponseCallback)(mbWebView webView, void* param, mbWebUrlRequestPtr request, mbWebUrlResponsePtr response);
typedef void(MB_CALL_TYPE* mbOnUrlRequestDidReceiveDataCallback)(mbWebView webView, void* param, mbWebUrlRequestPtr request, const char* data, int dataLength);
typedef void(MB_CALL_TYPE* mbOnUrlRequestDidFailCallback)(mbWebView webView, void* param, mbWebUrlRequestPtr request, const utf8* error);
typedef void(MB_CALL_TYPE* mbOnUrlRequestDidFinishLoadingCallback)(mbWebView webView, void* param, mbWebUrlRequestPtr request, double finishTime);

typedef struct _mbUrlRequestCallbacks {
    mbOnUrlRequestWillRedirectCallback willRedirectCallback;
    mbOnUrlRequestDidReceiveResponseCallback didReceiveResponseCallback;
    mbOnUrlRequestDidReceiveDataCallback didReceiveDataCallback;
    mbOnUrlRequestDidFailCallback didFailCallback;
    mbOnUrlRequestDidFinishLoadingCallback didFinishLoadingCallback;
} mbUrlRequestCallbacks;

typedef enum _mbDownloadOpt {
    kMbDownloadOptCancel,
    kMbDownloadOptCacheData,
} mbDownloadOpt;

typedef void(MB_CALL_TYPE* mbNetJobDataRecvCallback)(void* ptr, mbNetJob job, const char* data, int length);
typedef void(MB_CALL_TYPE* mbNetJobDataFinishCallback)(void* ptr, mbNetJob job, mbLoadingResult result);

typedef struct _mbNetJobDataBind {
    void* param;
    mbNetJobDataRecvCallback recvCallback;
    mbNetJobDataFinishCallback finishCallback;
} mbNetJobDataBind;

typedef void(MB_CALL_TYPE* mbPopupDialogSaveNameCallback)(void* ptr, const wchar_t* filePath);

typedef struct _mbDownloadBind {
    void* param;
    mbNetJobDataRecvCallback recvCallback;
    mbNetJobDataFinishCallback finishCallback;
    mbPopupDialogSaveNameCallback saveNameCallback;
} mbDownloadBind;

typedef mbDownloadOpt(MB_CALL_TYPE* mbDownloadInBlinkThreadCallback)(
    mbWebView webView,
    void* param,
    size_t expectedContentLength,
    const char* url,
    const char* mime,
    const char* disposition,
    mbNetJob job,
    mbNetJobDataBind* dataBind
    );

typedef struct _mbPdfDatas {
    int count;
    size_t* sizes;
    const void** datas;
} mbPdfDatas;

typedef void(MB_CALL_TYPE* mbPrintPdfDataCallback)(mbWebView webview, void* param, const mbPdfDatas* datas);

typedef struct _mbScreenshotSettings {
    int structSize;
    int width;
    int height;
} mbScreenshotSettings;

typedef void(MB_CALL_TYPE* mbPrintBitmapCallback)(mbWebView webview, void* param, const char* data, size_t size);

typedef enum _mbHttBodyElementType {
    mbHttBodyElementTypeData,
    mbHttBodyElementTypeFile,
} mbHttBodyElementType;

typedef struct _mbPostBodyElement {
    int size;
    mbHttBodyElementType type;
    mbMemBuf* data;
    mbStringPtr filePath;
    __int64 fileStart;
    __int64 fileLength; // -1 means to the end of the file.
} mbPostBodyElement;

typedef struct _mbPostBodyElements {
    int size;
    mbPostBodyElement** element;
    size_t elementSize;
    bool isDirty;
} mbPostBodyElements;

//mbwindow-----------------------------------------------------------------------------------
typedef enum {
    MB_WINDOW_TYPE_POPUP,
    MB_WINDOW_TYPE_TRANSPARENT,
    MB_WINDOW_TYPE_CONTROL
} mbWindowType;

typedef BOOL(MB_CALL_TYPE* mbWindowClosingCallback)(mbWebView webview, void* param);
typedef void(MB_CALL_TYPE* mbWindowDestroyCallback)(mbWebView webview, void* param);

typedef struct _mbDraggableRegion {
    RECT bounds;
    BOOL draggable;
} mbDraggableRegion;
typedef void(MB_CALL_TYPE* mbDraggableRegionsChangedCallback)(mbWebView webview, void* param, const mbDraggableRegion* rects, int rectCount);

typedef enum _mbPrintintStep {
    kPrintintStepStart,
    kPrintintStepPreview,
    kPrintintStepPrinting,
} mbPrintintStep;

typedef struct _mbPrintintSettings {
    int dpi;
    int width;
    int height;
    float scale;
} mbPrintintSettings;

typedef BOOL(MB_CALL_TYPE* mbPrintingCallback)(mbWebView webview, void* param, mbPrintintStep step, HDC hDC, const mbPrintintSettings* settings, int pageCount);

//JavaScript Bind-----------------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////

#define MB_DEFINE_ITERATOR0(returnVal, name, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR1(returnVal, name, p1, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR2(returnVal, name, p1, p2, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR3(returnVal, name, p1, p2, p3, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR4(returnVal, name, p1, p2, p3, p4, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3, p4); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR5(returnVal, name, p1, p2, p3, p4, p5, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3, p4, p5); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR6(returnVal, name, p1, p2, p3, p4, p5, p6, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3, p4, p5, p6); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR7(returnVal, name, p1, p2, p3, p4, p5, p6, p7, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3, p4, p5, p6, p7); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR8(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3, p4, p5, p6, p7, p8); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR9(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3, p4, p5, p6, p7, p8, p9); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR10(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

#define MB_DEFINE_ITERATOR11(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, description) \
    typedef returnVal(MB_CALL_TYPE* FN_##name)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11); \
    __declspec(selectany) FN_##name name = ((FN_##name)0);

// ---

#define MB_DECLARE_ITERATOR0(returnVal, name, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name();

#define MB_DECLARE_ITERATOR1(returnVal, name, p1, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1);

#define MB_DECLARE_ITERATOR2(returnVal, name, p1, p2, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2);

#define MB_DECLARE_ITERATOR3(returnVal, name, p1, p2, p3, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3);

#define MB_DECLARE_ITERATOR4(returnVal, name, p1, p2, p3, p4, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3, p4);

#define MB_DECLARE_ITERATOR5(returnVal, name, p1, p2, p3, p4, p5, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3, p4, p5);

#define MB_DECLARE_ITERATOR6(returnVal, name, p1, p2, p3, p4, p5, p6, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3, p4, p5, p6);

#define MB_DECLARE_ITERATOR7(returnVal, name, p1, p2, p3, p4, p5, p6, p7, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3, p4, p5, p6, p7);

#define MB_DECLARE_ITERATOR8(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3, p4, p5, p6, p7, p8);

#define MB_DECLARE_ITERATOR9(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3, p4, p5, p6, p7, p8, p9);

#define MB_DECLARE_ITERATOR10(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);

#define MB_DECLARE_ITERATOR11(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, description) \
    MB_EXTERN_C __declspec(dllexport) returnVal MB_CALL_TYPE name(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);

// ---

#define MB_GET_PTR_ITERATOR(name) \
    name = (FN_##name)GetProcAddress(hMod, #name); \
    if (!name) \
        MessageBoxA(((HWND)0), "mb api not found", #name, 0);

#define MB_GET_PTR_ITERATOR0(returnVal, name, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR1(returnVal, name, p1, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR2(returnVal, name, p1, p2, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR3(returnVal, name, p1, p2, p3, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR4(returnVal, name, p1, p2, p3, p4, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR5(returnVal, name, p1, p2, p3, p4, p5, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR6(returnVal, name, p1, p2, p3, p4, p5, p6, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR7(returnVal, name, p1, p2, p3, p4, p5, p6, p7, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR8(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR9(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR10(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, description) \
    MB_GET_PTR_ITERATOR(name);

#define MB_GET_PTR_ITERATOR11(returnVal, name, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, description) \
    MB_GET_PTR_ITERATOR(name);

// ������mb�ĵ�����������ʽ���ա��������͡�������������������������
#define MB_FOR_EACH_DEFINE_FUNCTION(ITERATOR0, ITERATOR1, ITERATOR2, ITERATOR3, ITERATOR4, ITERATOR5, ITERATOR6, ITERATOR7, ITERATOR8, ITERATOR9, ITERATOR10, ITERATOR11) \
ITERATOR0(void, mbUninit, "") \
ITERATOR0(mbWebView, mbCreateWebView, "") \
ITERATOR1(void, mbDestroyWebView, mbWebView, "") \
ITERATOR6(mbWebView, mbCreateWebWindow, mbWindowType type, HWND parent, int x, int y, int width, int height, "") \
ITERATOR7(mbWebView, mbCreateWebCustomWindow, HWND parent, DWORD style, DWORD styleEx, int x, int y, int width, int height, "") \
ITERATOR1(void, mbMoveToCenter, mbWebView webview, "") \
\
ITERATOR2(mbStringPtr, mbCreateString, const utf8* str, size_t length, "") \
ITERATOR1(void, mbDeleteString, mbStringPtr, "") \
\
ITERATOR2(void, mbSetProxy, mbWebView webView, const mbProxy* proxy, "") \
ITERATOR3(void, mbSetDebugConfig, mbWebView webView, const char* debugString, const char* param, "") \
\
ITERATOR3(void, mbNetSetData, mbNetJob jobPtr, void* buf, int len, "���ô˺�����,������յ����ݻ�洢��һbuf��,����������ɺ���ӦOnLoadUrlEnd�¼�.#�˵�������Ӱ������,����" \
    "�˺�����mbNetSetData�������ǣ�mbNetHookRequest���ڽ��ܵ������������ݺ��ٵ��ûص���������ص��޸��������ݡ�"\
    "��mbNetSetData�����������ݻ�û���͵�ʱ���޸�") \
ITERATOR1(void, mbNetHookRequest, mbNetJob jobPtr, "") \
ITERATOR2(void, mbNetChangeRequestUrl, mbNetJob jobPtr, const char* url, "") \
ITERATOR1(void, mbNetContinueJob, mbNetJob jobPtr, "") \
ITERATOR1(void, mbNetHoldJobToAsynCommit, mbNetJob jobPtr, "") \
\
ITERATOR1(mbPostBodyElements*, mbNetGetPostBody, mbNetJob jobPtr, "") \
ITERATOR2(mbPostBodyElements*, mbNetCreatePostBodyElements, mbWebView webView, size_t length, "") \
ITERATOR1(void, mbNetFreePostBodyElements, mbPostBodyElements* elements, "") \
ITERATOR1(mbPostBodyElement*, mbNetCreatePostBodyElement, mbWebView webView, "") \
ITERATOR1(void, mbNetFreePostBodyElement, mbPostBodyElement* element, "") \
\
ITERATOR3(mbWebUrlRequestPtr, mbNetCreateWebUrlRequest, const utf8* url, const utf8* method, const utf8* mime, "")\
ITERATOR3(void, mbNetAddHTTPHeaderFieldToUrlRequest, mbWebUrlRequestPtr request, const utf8* name, const utf8* value, "")\
ITERATOR4(int, mbNetStartUrlRequest, mbWebView webView, mbWebUrlRequestPtr request, void* param, const mbUrlRequestCallbacks* callbacks, "")\
ITERATOR1(int, mbNetGetHttpStatusCode, mbWebUrlResponsePtr response, "")\
ITERATOR1(mbRequestType, mbNetGetRequestMethod, mbNetJob jobPtr, "")\
ITERATOR1(__int64, mbNetGetExpectedContentLength, mbWebUrlResponsePtr response, "")\
ITERATOR1(const utf8*, mbNetGetResponseUrl, mbWebUrlResponsePtr response, "")\
ITERATOR1(void, mbNetCancelWebUrlRequest, int requestId, "")\
ITERATOR2(void, mbNetSetMIMEType, mbNetJob jobPtr, const char* type, "") \
ITERATOR1(const char*, mbNetGetMIMEType, mbNetJob jobPtr, "ֻ����blink�̵߳��ã������̣߳�") \
ITERATOR3(const utf8*, mbNetGetHTTPHeaderField, mbNetJob job, const char* key, BOOL fromRequestOrResponse, "") \
ITERATOR4(void, mbNetSetHTTPHeaderField, mbNetJob jobPtr, const wchar_t* key, const wchar_t* value, BOOL response, "") \
\
ITERATOR2(void, mbSetMouseEnabled, mbWebView webView, bool b, "") \
ITERATOR2(void, mbSetTouchEnabled, mbWebView webView, bool b, "") \
ITERATOR2(void, mbSetContextMenuEnabled, mbWebView webView, bool b, "") \
ITERATOR2(void, mbSetNavigationToNewWindowEnable, mbWebView webView, BOOL b, "") \
ITERATOR2(void, mbSetHeadlessEnabled, mbWebView webView, BOOL b, "���Թر���Ⱦ") \
ITERATOR2(void, mbSetDragDropEnable, mbWebView webView, BOOL b, "���Թر���ק�ļ�������") \
ITERATOR2(void, mbSetDragEnable, mbWebView webView, BOOL b, "�ɹر��Զ���ӦWM_DROPFILES��Ϣ����ҳ���ر����ļ�") \
ITERATOR3(void, mbSetContextMenuItemShow, mbWebView webView, mbMenuItemId item, BOOL isShow, "����ĳ��menu�Ƿ���ʾ") \
\
ITERATOR2(void, mbSetHandle, mbWebView webView, HWND wnd, "") \
ITERATOR3(void, mbSetHandleOffset, mbWebView webView, int x, int y, "") \
ITERATOR1(HWND, mbGetHostHWND, mbWebView webView, "") \
\
ITERATOR2(void, mbSetCspCheckEnable, mbWebView webView, BOOL b, "") \
ITERATOR2(void, mbSetNpapiPluginsEnabled, mbWebView webView, BOOL b, "") \
ITERATOR2(void, mbSetMemoryCacheEnable, mbWebView webView, BOOL b, "") \
ITERATOR3(void, mbSetCookie, mbWebView webView, const utf8* url, const utf8* cookie, "cookie��ʽ������:PRODUCTINFO=webxpress; domain=.fidelity.com; path=/; secure") \
ITERATOR2(void, mbSetCookieEnabled, mbWebView webView, BOOL enable, "") \
ITERATOR2(void, mbSetCookieJarPath, mbWebView webView, const WCHAR* path, "") \
ITERATOR2(void, mbSetCookieJarFullPath, mbWebView webView, const WCHAR* path, "") \
ITERATOR2(void, mbSetLocalStorageFullPath, mbWebView webView, const WCHAR* path, "") \
ITERATOR1(const utf8*, mbGetTitle, mbWebView webView, "") \
ITERATOR1(const utf8*, mbGetUrl, mbWebView webView, "") \
ITERATOR2(void, mbAddPluginDirectory, mbWebView webView, const WCHAR* path, "") \
ITERATOR2(void, mbSetUserAgent, mbWebView webView, const utf8* userAgent, "") \
ITERATOR2(void, mbSetZoomFactor, mbWebView webView, float factor, "") \
ITERATOR1(float, mbGetZoomFactor, mbWebView webView, "") \
ITERATOR2(void, mbSetDiskCacheEnabled, mbWebView webView, BOOL enable, "") \
\
ITERATOR2(void, mbSetResourceGc, mbWebView webView, int intervalSec, "") \
\
ITERATOR3(void, mbCanGoForward, mbWebView webView, mbCanGoBackForwardCallback callback, void* param, "") \
ITERATOR3(void, mbCanGoBack, mbWebView webView, mbCanGoBackForwardCallback callback, void* param, "") \
ITERATOR3(void, mbGetCookie, mbWebView webView, mbGetCookieCallback callback, void* param, "") \
ITERATOR1(const utf8*, mbGetCookieOnBlinkThread, mbWebView webView, "") \
\
ITERATOR3(void, mbResize, mbWebView webView, int w, int h, "") \
\
ITERATOR3(void, mbOnNavigation, mbWebView webView, mbNavigationCallback callback, void* param, "") \
ITERATOR3(void, mbOnNavigationSync, mbWebView webView, mbNavigationCallback callback, void* param, "") \
ITERATOR3(void, mbOnCreateView, mbWebView webView, mbCreateViewCallback callback, void* param, "") \
ITERATOR3(void, mbOnDocumentReady, mbWebView webView, mbDocumentReadyCallback callback, void* param, "") \
ITERATOR3(void, mbOnPaintUpdated, mbWebView webView, mbPaintUpdatedCallback callback, void* callbackParam, "") \
ITERATOR3(void, mbOnLoadUrlBegin, mbWebView webView, mbLoadUrlBeginCallback callback, void* callbackParam, "") \
ITERATOR3(void, mbOnLoadUrlEnd, mbWebView webView, mbLoadUrlEndCallback callback, void* callbackParam, "") \
ITERATOR3(void, mbOnTitleChanged, mbWebView webView, mbTitleChangedCallback callback, void* callbackParam, "") \
ITERATOR3(void, mbOnURLChanged, mbWebView webView, mbURLChangedCallback callback, void* callbackParam, "") \
ITERATOR3(void, mbOnLoadingFinish, mbWebView webView, mbLoadingFinishCallback callback, void* param, "") \
ITERATOR3(void, mbOnDownload, mbWebView webView, mbDownloadCallback callback, void* param, "") \
ITERATOR3(void, mbOnDownloadInBlinkThread, mbWebView webView, mbDownloadInBlinkThreadCallback callback, void* param, "") \
ITERATOR3(void, mbOnAlertBox, mbWebView webView, mbAlertBoxCallback callback, void* param, "") \
ITERATOR3(void, mbOnConfirmBox, mbWebView webView, mbConfirmBoxCallback callback, void* param, "") \
ITERATOR3(void, mbOnPromptBox, mbWebView webView, mbPromptBoxCallback callback, void* param, "") \
ITERATOR3(void, mbOnNetGetFavicon, mbWebView webView, mbNetGetFaviconCallback callback, void* param, "") \
ITERATOR3(void, mbOnConsole, mbWebView webView, mbConsoleCallback callback, void* param, "") \
ITERATOR3(BOOL, mbOnClose, mbWebView webView, mbCloseCallback callback, void* param, "") \
ITERATOR3(BOOL, mbOnDestroy, mbWebView webView, mbDestroyCallback callback, void* param, "") \
ITERATOR3(BOOL, mbOnPrinting, mbWebView webView, mbPrintingCallback callback, void* param, "") \
\
ITERATOR1(void, mbGoBack, mbWebView webView, "") \
ITERATOR1(void, mbGoForward, mbWebView webView, "") \
ITERATOR1(void, mbStopLoading, mbWebView webView, "") \
ITERATOR1(void, mbReload, mbWebView webView, "") \
ITERATOR2(void, mbPerformCookieCommand, mbWebView webView, mbCookieCommand command, "") \
\
ITERATOR1(void, mbEditorSelectAll, mbWebView webView, "") \
ITERATOR1(void, mbEditorCopy, mbWebView webView, "") \
ITERATOR1(void, mbEditorCut, mbWebView webView, "") \
ITERATOR1(void, mbEditorPaste, mbWebView webView, "") \
ITERATOR1(void, mbEditorDelete, mbWebView webView, "") \
ITERATOR1(void, mbEditorUndo, mbWebView webView, "") \
\
ITERATOR5(BOOL, mbFireMouseEvent, mbWebView webView, unsigned int message, int x, int y, unsigned int flags, "") \
ITERATOR4(BOOL, mbFireContextMenuEvent, mbWebView webView, int x, int y, unsigned int flags, "") \
ITERATOR5(BOOL, mbFireMouseWheelEvent, mbWebView webView, int x, int y, int delta, unsigned int flags, "") \
ITERATOR4(BOOL, mbFireKeyUpEvent, mbWebView webView, unsigned int virtualKeyCode, unsigned int flags, BOOL systemKey, "") \
ITERATOR4(BOOL, mbFireKeyDownEvent, mbWebView webView, unsigned int virtualKeyCode, unsigned int flags, BOOL systemKey, "") \
ITERATOR4(BOOL, mbFireKeyPressEvent, mbWebView webView, unsigned int charCode, unsigned int flags, BOOL systemKey, "") \
ITERATOR6(BOOL, mbFireWindowsMessage, mbWebView webView, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result, "") \
\
ITERATOR1(void, mbSetFocus, mbWebView webView, "") \
ITERATOR1(void, mbKillFocus, mbWebView webView, "") \
\
ITERATOR2(void, mbShowWindow, mbWebView webview, BOOL show, "") \
\
ITERATOR2(void, mbLoadURL, mbWebView webView, const utf8* url, "") \
ITERATOR3(void, mbLoadHtmlWithBaseUrl, mbWebView webView, const utf8* html, const utf8* baseUrl, "") \
\
ITERATOR1(HDC, mbGetLockedViewDC, mbWebView webView, "") \
ITERATOR1(void, mbUnlockViewDC, mbWebView webView, "") \
\
ITERATOR1(void, mbWake, mbWebView webView, "") \
\
ITERATOR2(double, mbJsToDouble, mbJsExecState es, mbJsValue v, "") \
ITERATOR2(BOOL, mbJsToBoolean, mbJsExecState es, mbJsValue v, "") \
ITERATOR2(const utf8*, mbJsToString, mbJsExecState es, mbJsValue v, "") \
ITERATOR3(void, mbOnJsQuery, mbWebView webView, mbJsQueryCallback callback, void* param, "") \
ITERATOR4(void, mbResponseQuery, mbWebView webView, int64_t queryId, int customMsg, const utf8* response, "") \
ITERATOR7(void, mbRunJs, mbWebView webView, mbWebFrameHandle frameId, const utf8* script, BOOL isInClosure, mbRunJsCallback callback, void* param, void* unuse, "") \
ITERATOR4(mbJsValue, mbRunJsSync, mbWebView webView, mbWebFrameHandle frameId, const utf8* script, BOOL isInClosure, "") \
ITERATOR1(mbWebFrameHandle, mbWebFrameGetMainFrame, mbWebView webView, "") \
ITERATOR2(BOOL, mbIsMainFrame, mbWebView webView, mbWebFrameHandle frameId, "") \
ITERATOR2(void, mbSetNodeJsEnable, mbWebView webView, BOOL b, "") \
\
ITERATOR5(void, mbSetDeviceParameter, mbWebView webView, const char* device, const char* paramStr, int paramInt, float paramFloat, "") \
\
ITERATOR4(void, mbGetContentAsMarkup, mbWebView webView, mbGetContentAsMarkupCallback calback, void* param, mbWebFrameHandle frameId, "") \
ITERATOR3(void, mbUtilSerializeToMHTML, mbWebView webView, mbGetMHTMLCallback calback, void* param, "") \
ITERATOR1(const char*, mbUtilCreateRequestCode, const char* registerInfo, "") \
ITERATOR1(BOOL, mbUtilIsRegistered, const wchar_t* defaultPath, "") \
ITERATOR3(BOOL, mbUtilPrint, mbWebView webView, mbWebFrameHandle frameId, const mbPrintSettings* printParams, "") \
ITERATOR1(const utf8*, mbUtilBase64Encode, const utf8* str, "") \
ITERATOR1(const utf8*, mbUtilBase64Decode, const utf8* str, "") \
ITERATOR1(const utf8*, mbUtilDecodeURLEscape, const utf8* url, "") \
ITERATOR1(const utf8*, mbUtilEncodeURLEscape, const utf8* url, "") \
ITERATOR1(const mbMemBuf*, mbUtilCreateV8Snapshot, const utf8* str, "") \
ITERATOR5(void, mbUtilPrintToPdf, mbWebView webView, mbWebFrameHandle frameId, const mbPrintSettings* settings, mbPrintPdfDataCallback callback, void* param, "") \
ITERATOR5(void, mbUtilPrintToBitmap, mbWebView webView, mbWebFrameHandle frameId, const mbScreenshotSettings* settings, mbPrintBitmapCallback callback, void* param, "") \
\
ITERATOR3(BOOL, mbPopupDownloadMgr, mbWebView webView, const char* url, void* downloadJob, "") \
ITERATOR9(mbDownloadOpt, mbPopupDialogAndDownload, mbWebView webView, void* param, size_t contentLength, const char* url, \
    const char* mime, const char* disposition, mbNetJob job, mbNetJobDataBind* dataBind, mbDownloadBind* callbackBind, "") \
ITERATOR10(mbDownloadOpt, mbDownloadByPath, mbWebView webView, void* param, const WCHAR* path, size_t contentLength, const char* url, \
    const char* mime, const char* disposition, mbNetJob job, mbNetJobDataBind* dataBind, mbDownloadBind* callbackBind, "") \
\
ITERATOR3(void, mbGetPdfPageData, mbWebView webView, mbOnGetPdfPageDataCallback callback, void* param, "") \
\
ITERATOR1(void, mbFreeMemBuf, mbMemBuf* buf, "") \

#if ENABLE_MB == 1

MB_EXTERN_C __declspec(dllexport) void MB_CALL_TYPE mbInit(const mbSettings * settings);

MB_FOR_EACH_DEFINE_FUNCTION(MB_DECLARE_ITERATOR0, MB_DECLARE_ITERATOR1, MB_DECLARE_ITERATOR2, \
    MB_DECLARE_ITERATOR3, MB_DECLARE_ITERATOR4, MB_DECLARE_ITERATOR5, MB_DECLARE_ITERATOR6, MB_DECLARE_ITERATOR7, MB_DECLARE_ITERATOR8, MB_DECLARE_ITERATOR9, MB_DECLARE_ITERATOR10, MB_DECLARE_ITERATOR11)

#else

MB_FOR_EACH_DEFINE_FUNCTION(MB_DEFINE_ITERATOR0, MB_DEFINE_ITERATOR1, MB_DEFINE_ITERATOR2, \
    MB_DEFINE_ITERATOR3, MB_DEFINE_ITERATOR4, MB_DEFINE_ITERATOR5, MB_DEFINE_ITERATOR6, MB_DEFINE_ITERATOR7, MB_DEFINE_ITERATOR8, MB_DEFINE_ITERATOR9, MB_DEFINE_ITERATOR10, MB_DEFINE_ITERATOR11)

    typedef void (MB_CALL_TYPE* FN_mbInit)(const mbSettings* settings);

__declspec(selectany) const wchar_t* kMbDllPath = L"mb.dll";
__declspec(selectany) const wchar_t* kMbMainDllPath = L"node.dll";

inline void mbSetMbDllPath(const wchar_t* dllPath)
{
    kMbDllPath = dllPath;
}

inline void mbSetMbMainDllPath(const wchar_t* dllPath)
{
    kMbMainDllPath = dllPath;
}

inline void mbInit(const mbSettings* settings)
{
    LoadLibraryW(kMbMainDllPath);
    HMODULE hMod = LoadLibraryW(kMbDllPath);

    FN_mbInit mbInitExFunc = (FN_mbInit)GetProcAddress(hMod, "mbInit");
    mbInitExFunc(settings);

    MB_FOR_EACH_DEFINE_FUNCTION(MB_GET_PTR_ITERATOR0, MB_GET_PTR_ITERATOR1, MB_GET_PTR_ITERATOR2, MB_GET_PTR_ITERATOR3, \
        MB_GET_PTR_ITERATOR4, MB_GET_PTR_ITERATOR5, MB_GET_PTR_ITERATOR6, MB_GET_PTR_ITERATOR7, MB_GET_PTR_ITERATOR8, MB_GET_PTR_ITERATOR9, MB_GET_PTR_ITERATOR10, MB_GET_PTR_ITERATOR11);

    return;
}

#endif

#endif // MB_DEFINE_H
