#include <iostream>
#include <string>
using namespace std;

#include <time.h>
#include"../jywke/wke/wke.h"


#define IDMENU_1	1101
#define IDMENU_2	1102
#define IDMENU_3	1103

#define IDMENU_SETTIMER		1104
#define IDMENU_KILLTIMER	1105

#include <DbgHelp.h>
#pragma comment(lib, "DbgHelp.lib")


class mb;

mb* g_mb;
UINT_PTR			g_timerID;
HWND				hWndList;

wstring				randStr(int count);
int					rand(int min, int max);
void				handleWindowDestroy(wkeWebView webWindow, void* param);
void	CALLBACK	Timerproc(HWND Arg1, UINT nIDEvent, UINT_PTR uElapse, DWORD lpTimerFunc);
LRESULT CALLBACK	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


int GenerateMiniDump(PEXCEPTION_POINTERS pExceptionPointers)
{


	HANDLE hDumpFile = CreateFileW(L"d:\\mbMemory.dmp", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE | FILE_SHARE_READ, 0, CREATE_ALWAYS, 0, 0);

	// 写入 dmp 文件
	MINIDUMP_EXCEPTION_INFORMATION expParam = { 0 };
	expParam.ThreadId = GetCurrentThreadId();
	expParam.ExceptionPointers = pExceptionPointers;
	expParam.ClientPointers = FALSE;
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
		hDumpFile, MiniDumpWithDataSegs, (pExceptionPointers ? &expParam : NULL), NULL, NULL);
	// 释放文件
	CloseHandle(hDumpFile);
	return EXCEPTION_EXECUTE_HANDLER;
}

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo)
{
	// 这里做一些异常的过滤或提示
	if (IsDebuggerPresent())
	{
		return EXCEPTION_CONTINUE_SEARCH;
	}
	return GenerateMiniDump(lpExceptionInfo);
}


class mb
{
private:
	wkeWebView webview;
public:
	mb() { webview = 0; }
	~mb() { ; }
	void create(HWND hWndParent)
	{
		webview = wkeCreateWebWindow(WKE_WINDOW_TYPE_CONTROL, hWndParent, 0, 0, 0, 0);
		wkeShowWindow(webview, true);
		wkeOnLoadUrlBegin(webview, OnwkeLoadUrlBegin, webview);
		wkeOnLoadUrlEnd(webview, OnwkeLoadUrlEnd, webview);
	}
	wkeWebView getWebView() { return webview; }
	void LoadURL(const wstring& url) { wkeLoadURLW(webview, url.c_str()); }
	void reLoad() { wkeReload(webview); }
	void move(int x, int y, int cx, int cy) { wkeMoveWindow(webview, x, y, cx, cy); }
	void SetUA(const char* UA) {
		wkeSetUserAgent(webview, UA);
	}
	//任何网络请求发起前会触发此回调
	static bool OnwkeLoadUrlBegin(wkeWebView webView, void* param, const char* url, void* job)
	{
		//参数：typedef bool(*wkeLoadUrlBeginCallback)(wkeWebView webView, void* param, const char *url, void *job)
		//注意：
		//1，此回调功能强大，在回调里，如果对job设置了wkeNetHookRequest，则表示mb会缓存获取到的网络数据，并在这次网络请求 结束后调用wkeOnLoadUrlEnd设置的回调，同时传递缓存的数据。在此期间，mb不会处理网络数据。
		//2，如果在wkeLoadUrlBeginCallback里没设置wkeNetHookRequest，则不会触发wkeOnLoadUrlEnd回调。
		//3，如果wkeLoadUrlBeginCallback回调里返回true，表示mb不处理此网络请求（既不会发送网络请求）。返回false，表示mb依然会发送网络请求。
		srand(time(0));
		int r = rand(1, 3);
		if (r == 1)
		{
			wkeNetHookRequest(job);
			return true;
		}
		return false;
	}


	static void OnwkeLoadUrlEnd(wkeWebView webView, void* param, const char* url, void* job, void* buf, int len)
	{
		
	}

};



int WINAPI wWinMain(
	__in HINSTANCE hInstance,
	__in_opt HINSTANCE hPrevInstance,
	__in LPWSTR lpCmdLine,
	__in int nCmdShow
)
{
	int a = PROC_THREAD_ATTRIBUTE_HANDLE_LIST;
	SetUnhandledExceptionFilter(ExceptionFilter);
	WNDCLASSEXW wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEXA);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"测试内存泄漏";
	RegisterClassExW(&wcex);
	HWND hWnd = CreateWindowW(L"测试内存泄漏", L"测试内存泄漏, 右键点击标题可以停止测试", WS_TILEDWINDOW, 0, 0, 800, 600, 0, 0, 0, 0);
	if (!hWnd)
		return 0;

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//g_timerID = SetTimer(0, 0, 3000, Timerproc);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	wkeFinalize();
	return msg.wParam;
}

void CALLBACK Timerproc(HWND hWnd, UINT nIDEvent, UINT_PTR uElapse, DWORD lpTimerFunc)
{
	//static HANDLE hFile;
	//if (!hFile)
	//{
	//	hFile = CreateFileW(L"d:\mbMemory.txt", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	//	int err = GetLastError();
	//	if (INVALID_HANDLE_VALUE == hFile)
	//		return;
	//}

	srand(time(NULL));
	int n = rand(1, 10);
	int i = rand(1, 4) - 1;
	static int num;
	num++;
	wstring url;
	WCHAR buf[520] = { 0 };
	int index = 0;
	switch (n)
	{
	case 1:
		g_mb[i].reLoad();
		swprintf_s(buf, L"%d, 第 %d 个浏览器重新加载", num, i + 1);
		index = SendMessageW(hWndList, LB_ADDSTRING, 0, (LPARAM)buf);
		SendMessageW(hWndList, LB_SETTOPINDEX, index, 0);
		return;
	case 2:
		url = L"http://baidu.com";
		break;
	case 3:
		url = L"http://taobao.com";
		break;
	case 4:
		url = L"http://qq.com";
		break;
	case 5:
		url = L"http://miniblink.net/views/doc/api.html";
		break;
	case 6:
		url = L"https://docs.microsoft.com/en-us/windows/win32/controls/window-controls";
		break;
	default:
		url = L"http://" + randStr(rand(2, 4)) + L".com";
		break;
	}
	url = L"http://ip138.com";
	g_mb[i].LoadURL(url);

	swprintf_s(buf, L"%d, 第 %d 个浏览器浏览网页\"%s\"", num, i + 1, url.c_str());
	index = SendMessageW(hWndList, LB_ADDSTRING, 0, (LPARAM)buf);
	SendMessageW(hWndList, LB_SETTOPINDEX, index, 0);

}


void wke_OnNetGetFaviconCallback(wkeWebView webView, void* param, const utf8* url, wkeMemBuf* buf)
{
    return;
}
void OnwkeLoadingFinish(wkeWebView webView, void* param, const wkeString url, wkeLoadingResult result, const wkeString failedReason)
{
    wkeNetGetFavicon(webView, wke_OnNetGetFaviconCallback, param);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		wkeSetWkeDllPath(L"E:\\易语言正式版\\node.dll");
		wkeInit();
		g_mb = new mb[3];
		g_mb[0].create(hWnd);
		g_mb[1].create(hWnd);
		g_mb[2].create(hWnd);
		
        wkeOnLoadingFinish(g_mb[0].getWebView(), OnwkeLoadingFinish, 0);			// 文档载入完毕
		wkeOnWindowDestroy(g_mb[0].getWebView(), handleWindowDestroy, 0);
        g_mb[0].LoadURL(L"https://ip138.com/");
        //g_mb[0].LoadURL(L"http://baidu.com");
        hWndList = CreateWindowW(L"listBox", 0, WS_CHILD | WS_VISIBLE | LBS_NOINTEGRALHEIGHT | WS_VSCROLL | LBS_NOTIFY, 0, 0, 0, 0, hWnd, 0, 0, 0);
		SendMessageW(hWndList, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);
		{
			HMENU hMenu = GetSystemMenu(hWnd, FALSE);
			AppendMenuW(hMenu, MF_SEPARATOR, 0, 0);
			AppendMenuW(hMenu, MF_STRING, IDMENU_SETTIMER, L"开启时钟,每3秒刷新一次");
			AppendMenuW(hMenu, MF_STRING, IDMENU_KILLTIMER, L"关闭时钟");
			AppendMenuW(hMenu, MF_SEPARATOR, 0, 0);

			AppendMenuW(hMenu, MF_STRING, IDMENU_1, L"浏览器1置为空页面");
			AppendMenuW(hMenu, MF_STRING, IDMENU_2, L"浏览器2置为空页面");
			AppendMenuW(hMenu, MF_STRING, IDMENU_3, L"浏览器3置为空页面");

		}
		break;
	case WM_DESTROY:
		delete[] g_mb;
		g_mb = 0;
		PostQuitMessage(0);
		break;
	case WM_SIZE:
	{
		int cxClient = LOWORD(lParam), cyClient = HIWORD(lParam);
		int n = cxClient / 4;
		g_mb[0].move(n * 0, 0, n, cyClient);
		g_mb[1].move(n * 1, 0, n, cyClient);
		g_mb[2].move(n * 2, 0, n, cyClient);
		MoveWindow(hWndList, n * 3, 0, n, cyClient, TRUE);
	}
	break;
	case WM_SYSCOMMAND:
	case WM_COMMAND:
	{
		int id = LOWORD(wParam);
		switch (id)
		{
		case IDMENU_1:
			g_mb[0].SetUA("Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");
			g_mb[0].LoadURL(L"http://www.weibo.com");
			return 0;
		case IDMENU_2:
			g_mb[1].LoadURL(L"about:blank");
			return 0;
		case IDMENU_3:
			g_mb[2].LoadURL(L"about:blank");
			return 0;
		case IDMENU_SETTIMER:
		{
			g_timerID = SetTimer(0, g_timerID, 3000, Timerproc);
			int index = SendMessageW(hWndList, LB_ADDSTRING, 0, (LPARAM)L"时钟已开启,每3秒随机访问一个网页");
			SendMessageW(hWndList, LB_SETTOPINDEX, index, 0);
		}
		break;
		case IDMENU_KILLTIMER:
		{
			KillTimer(0, g_timerID);
			g_timerID = 0;
			int index = SendMessageW(hWndList, LB_ADDSTRING, 0, (LPARAM)L"时钟已停止");
			SendMessageW(hWndList, LB_SETTOPINDEX, index, 0);
		}
		break;
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);

		}
		break;
	}
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}


int rand(int min, int max)
{
	return rand() % (max - min) + min;
}

void handleWindowDestroy(wkeWebView webWindow, void* param)
{
	PostQuitMessage(0);
}

wstring randStr(int count)
{
	srand(time(NULL));
	wstring str;
	str.resize(count);
	for (int i = 0; i < count; i++)
	{
		str[i] = rand('a', 'z');
	}
	str[count] = '\0';
	return str;
}