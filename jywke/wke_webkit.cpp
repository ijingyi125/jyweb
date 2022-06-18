#include "wke_webkit_header.h"
static wstr s_path;


INT WINAPI wke_PropNotifyReceiver_webkit(INT nMsg, DWORD dwParam1, DWORD dwParam2);
BOOL WINAPI wke_PropKetInfo_webkit(HUNIT hUnit, WORD wKey);


HUNIT WINAPI wke_ControlCreate_Webkit(
    LPBYTE pAllPropertyData,            //   指向本窗口单元的已有属性数据，由本窗口单元的ITF_GET_PROPERTY_DATA接口产生，如果没有数据则为NULL。
    INT nAllPropertyDataSize,           //   提供pAllPropertyData所指向数据的尺寸，如果没有则为0。
    DWORD dwStyle,                      //   预先设置的窗口风格。
    HWND hParentWnd,                    //   父窗口句柄。
    UINT uID,                           //   在父窗口中的ID。
    HMENU hMenu,                        //   未使用。
    INT x, INT y, INT cx, INT cy,       //   指定位置及尺寸。
    DWORD dwWinFormID, DWORD dwUnitID,  //   本窗口单元所在窗口及本身的ID，用作通知到系统。
    HWND hDesignWnd,					//   如果blInDesignMode为真，则hDesignWnd提供所设计窗口的窗口句柄。
    BOOL blInDesignMode);  				//   说明是否被易语言IDE调用以进行可视化设计，运行时为假。

// 精易Web浏览器  下的组件交互方法
EXTERN_C PFN_INTERFACE WINAPI wke_GetInterface_webkit(INT nInterfaceNO)
{
    switch ( nInterfaceNO )
    {
    case ITF_CREATE_UNIT:
    {
        // 创建组件
        return (PFN_INTERFACE)wke_ControlCreate_Webkit;
    }
    case ITF_PROPERTY_UPDATE_UI:
    {
        // 说明属性目前可否被修改
        return (PFN_INTERFACE)wke_PropUpDate_Webkit;
    }
    case ITF_DLG_INIT_CUSTOMIZE_DATA:
    {
        // 使用对话框设置自定义数据
        return (PFN_INTERFACE)wke_PropPopDlg_Webkit;
    }
    case ITF_NOTIFY_PROPERTY_CHANGED:
    {
        // 通知某属性数据被用户修改
        return (PFN_INTERFACE)wke_PropChanged_Webkit;
    }
    case ITF_GET_ALL_PROPERTY_DATA:
    {
        // 取全部属性数据
        return (PFN_INTERFACE)wke_PropGetDataAll_Webkit;
    }
    case ITF_GET_PROPERTY_DATA:
    {
        // 取某属性数据
        return (PFN_INTERFACE)wke_PropGetData_Webkit;
    }
    case ITF_GET_ICON_PROPERTY_DATA:
    {
        // 取窗口的图标属性数据(仅用于窗口)
        break;
    }
    case ITF_IS_NEED_THIS_KEY:
    {
        // 询问单元是否需要指定的按键信息, 用作窗口单元
        return (PFN_INTERFACE)wke_PropKetInfo_webkit;
    }
    case ITF_LANG_CNV:
    {
        // 组件数据语言转换
        break;
    }
    case ITF_MSG_FILTER:
    {
        // 消息过滤
        break;
    }
    case ITF_GET_NOTIFY_RECEIVER:
    {
        // 取组件的附加通知接收者(PFN_ON_NOTIFY_UNIT)
        return (PFN_INTERFACE)wke_PropNotifyReceiver_webkit;
    }
    default:
        return NULL;
    }
    return NULL;
}


HUNIT WINAPI wke_ControlCreate_Webkit(
    LPBYTE pAllPropertyData,            //   指向本窗口单元的已有属性数据, 由本窗口单元的ITF_GET_PROPERTY_DATA接口产生, 如果没有数据则为NULL。
    INT nAllPropertyDataSize,           //   提供pAllPropertyData所指向数据的尺寸, 如果没有则为0。
    DWORD dwStyle,                      //   预先设置的窗口风格。
    HWND hParentWnd,                    //   父窗口句柄。
    UINT uID,                           //   在父窗口中的ID。
    HMENU hMenu,                        //   未使用。
    INT x, INT y, INT cx, INT cy,       //   指定位置及尺寸。
    DWORD dwWinFormID, DWORD dwUnitID,  //   本窗口单元所在窗口及本身的ID, 用作通知到系统。
    HWND hDesignWnd,                    //   如果blInDesignMode为真, 则hDesignWnd提供所设计窗口的窗口句柄。
    BOOL blInDesignMode)                //   说明是否被易语言IDE调用以进行可视化设计, 运行时为假。
{
    // 开始创建组件窗口
    if ( s_path.empty() )
    {
        if ( !wke_SetDllPath() )
            return 0;
    }

    static bool isInit;
    if ( !isInit )
    {
        if ( !MbE::Initialize() )
            return 0;
        isInit = true;
    }

    PWEBKIT_PROPERTYEX data = 0;
    HUNIT hUnit = GethUnitFromId(dwWinFormID, dwUnitID, (PVOID*)&data);
    if ( InitDataEx(data) )
    {
        //TODO 有申请了内存, 需要把地址记录起来, 等结束的时候释放, 目前就让他泄漏吧
    }
    bool isDefProp = false; // 是否需要默认属性
    try
    {
        isDefProp = ParsePropData_webkit(data, pAllPropertyData, nAllPropertyDataSize) == 0;
    }
    catch ( ... )
    {
        isDefProp = true;
    }

    // 记录组件的一些信息
    SET_DATA_DEFVALUE(data);

    data->hWnd = data->pCtl->create(hParentWnd, dwStyle | WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | 256, uID, x, y, cx, cy, data);
    if ( !data->hWnd )
    {
        // 创建组件失败, 需要测试是什么问题
        wstr dbg;
        dbg.Format(L"创建 精易web浏览器 组件失败\n错误码 = %d", GetLastError());
        MessageBoxW(hParentWnd, dbg.c_str(), L"创建组件失败", MB_ICONERROR);
        delete data;
        return 0;
    }

    WEBKIT_PROPERTY& prop = data->prop;

    if ( prop.pszUserAgent && prop.pszUserAgent[0] )
        data->pCtl->SetUserAgent(prop.pszUserAgent);    //设置UA

    if ( prop.DisableCookie )
        data->pCtl->SetCookieEnabled(false);    // 禁用cookie

    if ( !data->blInDesignMode )    //不是设计模式才设置目录信息
    {
        wstr pathBuffer(260);

        char exePath[MAX_PATH] = { 0 };
        NotifySys(NAS_GET_PATH, 2001, (DWORD)exePath);
        prop.runPath = data->bufPool->AddStringWFromAnsi(exePath);   // 运行路径, 如果不是运行状态, 那路径为空

        if ( prop.pszCachePathW[0] )
        {
            // 有缓存目录, 判断目录是否是绝对路径
            if ( wcsncmp(prop.pszCachePathW + 1, L":\\", 2) != 0 )
            {
                // 不是完整路径, 需要加处理一下
                pathBuffer.assign(prop.runPath);
            }
            pathBuffer.append(prop.pszCachePathW);
            if ( pathBuffer.back() != L'\\' )
                pathBuffer.push_back(L'\\');
            data->pCtl->SetLocalStorageFullPath(pathBuffer.c_str());    //设置缓存目录
        }

        if ( prop.pszCookiePathW[0] )
        {
            // 有缓存目录, 判断目录是否是绝对路径
            if ( wcsncmp(prop.pszCookiePathW + 1, L":\\", 2) != 0 )
            {
                // 不是完整路径, 需要加处理一下
                pathBuffer.assign(prop.runPath);
            }
            pathBuffer.append(prop.pszCookiePathW);
            if ( pathBuffer.back() != L'\\' )
                pathBuffer.push_back(L'\\');
            data->pCtl->SetCookieJarPath(pathBuffer.c_str());    //设置cookie目录
        }


        if ( prop.urlW[0] )
        {
            data->pCtl->GoUrl(prop.urlW);    //不是设计模式下就跳转到属性里的url
        }
        wkeSetNavigationToNewWindowEnable(data->pCtl->GetWkeWebView(), prop.isNewWnd);
        data->flags |= EVENT_PTR_E;
        OnwkeCallbackAll(data->pCtl->GetWkeWebView(), data);    //设置回调
    }
    else
    {
        // 设计模式, 需要根据是否预览加载页面
        if ( prop.debugShow && prop.urlW[0] )
            data->pCtl->GoUrl(prop.urlW);    //不是设计模式下就跳转到属性里的url
    }

    //SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, )
    return CreateUnit(data);
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    return 0;
}


INT WINAPI wke_PropNotifyReceiver_webkit(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
    switch ( nMsg )
    {
    case NU_GET_CREATE_SIZE_IN_DESIGNER:
        // 取设计时组件被单击放置到窗体上时的默认创建尺寸.
        // dwParam1: 类型: INT*, 返回宽度(单位像素)
        // dwParam2: 类型: INT*, 返回高度(单位像素)
        // 成功返回1,失败返回0.
        *( (int*)dwParam1 ) = 200;
        *( (int*)dwParam2 ) = 100;
        return 1;
    }
    return 0;
}

BOOL WINAPI wke_PropKetInfo_webkit(HUNIT hUnit, WORD wKey)
{
    // 询问单元是否需要指定的按键信息, 如果需要, 返回真, 否则返回假。
    if ( hUnit == NULL )  return FALSE;
    BOOL bRet = FALSE;
    //PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);
    //assert(wkectrl->m_hWnd != NULL);

    // 现在精易web浏览器组件没有需要禁止的属性

    return bRet;
}

BOOL WINAPI wke_PropUpDate_Webkit(HUNIT hUnit, INT nPropertyIndex)    //精易Web浏览器  下的更新属性方法
{
    // 如果指定属性目前可以被操作, 返回真, 否则返回假。
    // 精易Web浏览器  下的更新属性方法
    //PWEBKIT_PROPERTYEX data = g_wke[pArgInf->m_unit.m_dwUnitID]
    //if (PROP_TITLE == nPropertyIndex)    //窗口标题不可操作
    //    return FALSE;
    
    // 现在精易web浏览器组件没有需要禁止的属性

    return TRUE;
}

BOOL WINAPI wke_PropPopDlg_Webkit(HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData)    //精易Web浏览器  下的弹出对话框方法
{
    // 用作设置类型为UD_CUSTOMIZE的单元属性。
    // 如果需要重新创建该单元才能修改单元外形, 请返回真。
    //pblModified 不为NULL, 请在其中返回是否被用户真正修改(便于易语言IDE建立UNDO记录)
    //PWEBKIT_PROPERTYEX data = GetWebkitDataFromHunit(hUnit);

    // 现在精易web浏览器组件没有需要打开对话框的属性
    return FALSE;
}




typedef BOOL(WINAPI* fun_PathFileExistsW)( LPCWSTR pszPath );
inline static BOOL __LIB2_DEFFUNNAME(PathFileExistsW)( LPCWSTR pszPath )
{
    static HMODULE hModule = 0;
    static fun_PathFileExistsW fun = 0;
    if ( !hModule )
    {
        hModule = LoadLibraryW(L"Shlwapi.dll");
        if ( !hModule )throw "获取Shlwapi.dll句柄失败";
        fun = (fun_PathFileExistsW)GetProcAddress(hModule, "PathFileExistsW");
    }
    if ( !fun )throw "PathFileExistsW函数获取失败";
    return fun(pszPath);
}
#define PathFileExistsW __LIB2_DEFFUNNAME(PathFileExistsW)


bool wke_SetDllPath()
{
    DWORD nRet = NotifySys(NRS_GET_PRG_TYPE, 0, 0);
    char szPath[MAX_PATH] = { 0 };
    //PT_DEBUG_RUN_VER（调试版） PT_RELEASE_RUN_VER（发布版）。
    if ( PT_RELEASE_RUN_VER == nRet )
    {
        //如果是编译版,并且没有被设置dll路径,那就取exe运行目录
        NotifySys(NAS_GET_PATH, 2001, (DWORD)szPath);
    }
    else
    {
        //否则调试版就取易语言工作路径,ide环境内取到 e.exe目录,F5 运行时取到的是 lib/ 目录
        NotifySys(NAS_GET_PATH, 1, (DWORD)szPath);
    }
    wstr path(260), file(260);
    path.assign(wstr::A2W(szPath));

    if ( path.substr(path.size() - 4, 3) == L"lib" )
        path.resize(path.size() - 4);
    
    file.assign(path).append(L"miniblink_4975_x32.dll");

#ifdef _DEBUG
    //::MessageBoxW(NULL, path.c_str(), nRet == PT_RELEASE_RUN_VER ? L"编译版" : L"调试版", MB_OK);
#endif

    // 一共判断4个路径, 全部都不存在就设置失败
    if ( !PathFileExistsW(file.c_str()) )
    {
        file.assign(path).append(L"miniblink_4957_x32.dll");
        if ( !PathFileExistsW(file.c_str()) )
        {
            file.assign(path).append(L"miniblink_4949_x32.dll");
            if ( !PathFileExistsW(file.c_str()) )
            {
                file.assign(path).append(L"node.dll");
                if ( !PathFileExistsW(file.c_str()) )
                {
                    WCHAR szLog[520] = { 0 };
                    swprintf(szLog, L"请把\"miniblink_4975_x32.dll\"\r\n"
                             L"或者 \"miniblink_4957_x32.dll\"\r\n"
                             L"或者 \"miniblink_4949_x32.dll\"\r\n"
                             L"或者 \"node.dll\"\r\n"
                             L"放在[%s]这个目下", path.c_str());
                    ::MessageBoxW(NULL, szLog, L"错误", MB_OK);
                    return false;
                }
            }
        }

    }
    wke_SetDllPath(file.c_str());
    return true;
}

bool wke_SetDllPath(LPCWSTR path)
{
    s_path = path;
    wkeSetWkeDllPath(s_path.c_str());
    return true;
}

bool wke_SetDllPath(LPCSTR path)
{
    wstr pathW = _str::A2W(path);
    bool ret = wke_SetDllPath(pathW.c_str());
    return ret;
}





