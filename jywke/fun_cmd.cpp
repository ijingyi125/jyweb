#include "wke_typedef.h"
#include "wke_webkit_header.h"
#include <CPUusage.h>

// 不是类里边命令的实现部分




// 调用格式: _SDT_NULL wke_设置dll路径, 命令说明: "设置node.dll的完整路径,如果程序运行目录下没有node.dll,则必须在窗口载入之前调用,如果程序运行目录下有node.dll可以忽略该命令,默认会从目录下加载。"
// 参数<1>: dll路径 SDT_TEXT, 参数说明: "node.dll的完整路径"
EXTERN_C void WKE_NAME(147, wke_setDllPath)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wke_SetDllPath(pArgInf[0].m_pText);
}
DEF_EXECUTE_CMD(tmp_____)
{
}

// 调用格式: SDT_TEXT wke_AnsiToUtf8, 命令说明: "把ansi编码的文本转换成utf8编码的文本,成功返回转换后的文本,失败返回空文本。"
// 参数<1>: ansi文本 SDT_TEXT, 参数说明: "ansi编码的文本"
EXTERN_C void WKE_NAME(148, wke_A2U)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    LPSTR retStr = NULL;
    _str szStr = wstr::A2W(pArgInf[0].m_pText).w2u();
    if (szStr != "")
    {
        retStr = CloneTextData(szStr.c_str());
    }
    pRetData->m_pText = retStr;
}

// 调用格式: SDT_BIN wke_AnsiToUnicode, 命令说明: "把ansi编码的文本转换成Unicode编码的文本,成功返回转换后的Unicode字节集,失败返回空字节集。"
// 参数<1>: ansi文本 SDT_TEXT, 参数说明: "ansi编码的文本"
EXTERN_C void WKE_NAME(149, wke_A2W)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    LPBYTE retStr = NULL;
    wstr szStr = wstr::A2W(pArgInf[0].m_pText);
    if (szStr != L"")
    {
        retStr = CloneBinData((LPBYTE)szStr.c_str(), lstrlenW(szStr.c_str()) * 2 + 2);
    }
    pRetData->m_pBin = retStr;
}

// 调用格式: SDT_TEXT wke_Utf8ToAnsi, 命令说明: "把utf8编码的文本转换成ansi编码的文本,成功返回转换后的文本,失败返回空文本。"
// 参数<1>: utf8文本 _SDT_ALL, 参数说明: "utf8编码的文本,只支持文本指针,文本型,和字节集"
EXTERN_C void WKE_NAME(150, wke_U2A)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str szStr;
    LPSTR retStr = NULL;
    int dwLen = 0;
    switch (pArgInf[0].m_dtDataType)
    {
    case SDT_BIN:
    {
        LPBYTE pData = GetBinData(pArgInf[0].m_pBin);
        szStr = wstr::U2A((LPCSTR)pData);
        efree(pData);
    }
    break;
    case SDT_TEXT:
        szStr = wstr::U2A(pArgInf[0].m_pText);
        break;
    case SDT_INT:
        if (!IsBadCodePtr((FARPROC)pArgInf[0].m_int))	//0=有效,非0=无效
        {
            //如果指针有效
            szStr = wstr::U2A((LPCSTR)pArgInf[0].m_int);
            break;
        }
        //指针无效就让他走到 default 里
    default:
        pRetData->m_pText = 0;
        return;
    }
    if (szStr != "")
    {
        retStr = CloneTextData(szStr.c_str());
    }
    pRetData->m_pText = retStr;
}

// 调用格式: SDT_BIN wke_Utf8ToUnicode, 命令说明: "把utf8编码的文本转换成Unicode编码的文本,成功返回转换后的Unicode字节集,失败返回空字节集。"
// 参数<1>: utf8文本 _SDT_ALL, 参数说明: "utf8编码的文本,只支持文本指针,文本型,和字节集"
EXTERN_C void WKE_NAME(151, wke_U2W)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wstr szStr;
    LPBYTE retStr = NULL;
    switch (pArgInf[0].m_dtDataType)
    {
    case SDT_BIN:
    {
        LPBYTE pData = GetBinData(pArgInf[0].m_pBin);
        szStr = wstr::U2W((LPCSTR)pData);
        efree(pData);
    }
    break;
    case SDT_TEXT:
        szStr = wstr::U2W(pArgInf[0].m_pText);
        break;
    case SDT_INT:
        if (!IsBadCodePtr((FARPROC)pArgInf[0].m_int))	//0=有效,非0=无效
        {
            //如果指针有效
            szStr = wstr::U2W((LPCSTR)pArgInf[0].m_int);
            break;
        }
        //指针无效就让他走到 default 里
    default:
        pRetData->m_pBin = 0;
        return;
    }
    if (szStr != L"")
    {
        retStr = CloneBinData((LPBYTE)szStr.c_str(), lstrlenW(szStr.c_str()) * 2 + 2);
    }
    pRetData->m_pBin = retStr;
}

// 调用格式: SDT_TEXT wke_UnicodeToAnsi, 命令说明: "把Unicode编码的文本转换成ansi编码的文本,成功返回转换后的文本,失败返回空文本。"
// 参数<1>: Unicode文本 SDT_BIN, 参数说明: "Unicode编码的文本"
EXTERN_C void WKE_NAME(152, wke_W2A)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str szStr;
    LPSTR retStr = NULL;
    int dwLen = 0;
    LPBYTE pData = GetBinData(pArgInf[0].m_pBin);
    szStr = wstr::W2A((LPWSTR)pData);
    efree(pData);
    if (szStr != "")
    {
        retStr = CloneTextData(szStr.c_str());
    }
    pRetData->m_pText = retStr;
}

// 调用格式: SDT_TEXT wke_UnicodeToUtf8, 命令说明: "把Unicode编码的文本转换成utf8编码的文本,成功返回转换后的文本,失败返回空文本。"
// 参数<1>: Unicode文本 SDT_BIN, 参数说明: "Unicode编码的文本"
EXTERN_C void WKE_NAME(153, wke_W2U)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str szStr;
    LPSTR retStr = NULL;
    pRetData->m_dtDataType = SDT_TEXT;
    int dwLen = 0;
    LPBYTE pData = GetBinData(pArgInf[0].m_pBin);
    szStr = wstr::W2U((LPWSTR)pData);
    efree(pData);
    if (szStr != "")
    {
        retStr = CloneTextData(szStr.c_str());
    }
    pRetData->m_pText = retStr;
}








//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


// 调用格式: SDT_INT wke_取版本号, 命令说明: "获取目前api版本号。"
// 无参数
EXTERN_C void WKE_NAME(155, wke_GetVersion)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_int = wkeVersion();
}

// 调用格式: SDT_TEXT wke_取版本文本, 命令说明: "获取版本字符串。"
// 无参数
EXTERN_C void WKE_NAME(156, wke_GetVersionString)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str str = wstr::U2A(wkeVersionString());
    pRetData->m_pText = CloneTextData(str.c_str());
}

// 调用格式: SDT_DOUBLE wke_取CPU占用, 命令说明: "取自进程CPU占用率,用于测试挂机记录程序运行状态。\r\n【请注意】该功能是测试功能,会根据用户需求决定是否删除该命令"
// 参数<1>: [&工作集大小 SDT_INT], 参数说明: "返回程序当前工作集的内存大小,单位为字节"
// 参数<2>: [&峰值工作集 SDT_INT], 参数说明: "返回程序峰值工作集的内存大小,单位为字节"
EXTERN_C void WKE_NAME(170, wke_GetCpu)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    static CPUusage usg(GetCurrentProcess());
    pRetData->m_double = usg.get_cpu_usage();
    if ( pRetData->m_double <= 0 )
    {
        pRetData->m_double = usg.get_cpu_usage();
        if ( pRetData->m_double < 0 )
            pRetData->m_double = 0;
    }
    int PeakWorkingSetSize = 0;
    int WorkingSetSize = usg.get_mem(PeakWorkingSetSize);

    if ( pArgInf[0].m_dtDataType != _SDT_NULL && pArgInf[0].m_pInt )
    {
        *pArgInf[0].m_pInt = WorkingSetSize;
    }
    if ( pArgInf[1].m_dtDataType != _SDT_NULL && pArgInf[1].m_pInt )
    {
        *pArgInf[1].m_pInt = PeakWorkingSetSize;
    }
    if ( pRetData->m_double > 100 ) pRetData->m_double = 0;

}

// 调用格式: SDT_TEXT 备用命令, 命令说明: "c/c++里的格式化字符串"
// 参数<1>: 格式化文本串 SDT_TEXT, 参数说明: "格式化文本串"
// 参数<2>: 参数 _SDT_ALL, 参数说明: "日期时间型请使用 %s, 内部会转换成 \"2020-01-01 01:01:01\" 这种格式\r\n\t字节集和逻辑型也使用 %s, 内部会转成文本使用, 其他没有说明的类型, 就按c/c++格式化字符串传递"
EXTERN_C void WKE_NAME(192, wke_format_1)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// 调用格式: SDT_TEXT 生成字符串, 命令说明: "生成字符串, 把所有能转换到文本的类型都转成文本并连接在一起, 暂时没处理日期时间型和数组"
// 参数<1>: 参数 _SDT_ALL, 参数说明: "日期时间型请使用 %s, 内部会转换成 \"2020-01-01 01:01:01\" 这种格式\r\n\t字节集和逻辑型也使用 %s, 内部会转成文本使用, 其他没有说明的类型, 就按c/c++格式化字符串传递"
EXTERN_C void WKE_NAME(193, wke_makeString)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    int count = nArgCount;
    LPCSTR str = pArgInf[0].m_pText;
    _str buffer(4000);
    for (int i = 0; i < count; i++)
    {
        switch (pArgInf[i].m_dtDataType)
        {
        case SDT_BOOL:
            buffer.append(pArgInf[i].m_bool ? "真" : "假");
            break;
        case SDT_BYTE:
            buffer.append(pArgInf[i].m_byte);
            break;
        case SDT_DOUBLE:
            buffer.append(pArgInf[i].m_double);
            break;
        case SDT_FLOAT:
            buffer.append(pArgInf[i].m_float);
            break;
        case SDT_INT:
            buffer.append(pArgInf[i].m_int);
            break;
        case SDT_INT64:
            buffer.append(pArgInf[i].m_int64);
            break;
        case SDT_SHORT:
            buffer.append(pArgInf[i].m_short);
            break;
        case SDT_TEXT:
            buffer.append(pArgInf[i].m_pText);
            break;
        case SDT_BIN:
            buffer.append((LPCSTR)(GetAryElementInf(pArgInf[i].m_pBin, 0)));
            break;
        default:
            break;
        }
    }
    pRetData->m_pText = CloneTextData(buffer.c_str(), buffer.size());
}



static bool s_bMsgLoop;
// 调用格式: SDT_BOOL wke_消息循环, 命令说明: "消息循环, 在窗口创建完毕事件下调用, 调用此命令后直到调用wke_取消循环() 才返回, 窗口销毁时需要调用 wke_取消循环(), 否则程序无法退出\r\n此方法是为了处理web浏览器组件无法按tab键切换焦点的问题,\r\n【注意】调用此方法后不会走易语言的消息循环, 按tab键后不会自动切组件换焦点, 同时组件能收到tan键按下放开消息"
// 参数<1>: [窗口句柄 SDT_INT], 参数说明: "目前参数2为空时该参数无效"
// 参数<2>: [显示窗口 SDT_BOOL], 参数说明: "是否显示窗口, 为真则先显示窗口在调用消息循环, 否则直接调用消息循环"
EXTERN_C void WKE_NAME(218, wke_MsgLoop)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    if ( pArgInf[1].m_bool )
    {
        ShowWindow((HWND)pArgInf[0].m_int, SW_SHOW);
    }
    MSG msg = { 0 };
    s_bMsgLoop = true;
    while (GetMessageW(&msg, NULL, 0, 0) && s_bMsgLoop)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    s_bMsgLoop = false;
    pRetData->m_bool = true;
}

// 调用格式: _SDT_NULL wke_取消循环, 命令说明: "取消消息循环, 取消后才能使 wke_消息循环() 返回, 此命令会调用PostQuitMessage"
// 无参数
EXTERN_C void WKE_NAME(219, wke_CancelMsgLoop)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    if ( s_bMsgLoop )
    {
        PostQuitMessage(0);
        s_bMsgLoop = false;
    }
}













//取日期部分,参数1为只有日期部分的DATE数据
//1899年12月30日0时00分00秒 为0基准,单位为天数的小数值


inline static _str __format_strA(const char* format, int* arr)
{
    size_t bufSize = 4096;
    _str buf(bufSize);

    int ret;
    va_list list = (va_list)arr;

    while ((ret = ___vsnprintf_s(buf.data(), bufSize, format, list)) == -1)
    {
        bufSize *= 2;
        buf.resize(bufSize);
    }
    _str::dbg("");

    va_end(list);
    buf.resize(ret);
    buf.Addref();
    return buf;
}
inline static wstr __format_strW(const wchar_t* format, int* arr)
{
    size_t bufSize = 4096;
    wstr buf(bufSize);

    int ret;
    va_list list = (va_list)arr;

    while ((ret = ___vsnwprintf_s(buf.data(), bufSize, format, list)) == -1)
    {
        bufSize *= 2;
        buf.resize(bufSize);
    }

    va_end(list);
    buf.resize(ret);
    buf.Addref();
    return buf;
}
inline static void __format_wke(int nArgCount, PMDATA_INF pArgInf, void* ret, bool isUnicode)
{
    int len = nArgCount * 3;
    int* arr = new int[len];
    memset(arr, 0, sizeof(int) * len);
    _str dateBuf;
    int n = 0;
    for (int i = 1; i < nArgCount; i++)
    {
        switch (pArgInf[i].m_dtDataType)
        {
        case SDT_BYTE:		// 字节
        case SDT_SHORT:		// 短整数
        case SDT_INT:		// 整数
        case SDT_SUB_PTR:	// 子程序指针
        case SDT_TEXT:		// 文本
        case SDT_FLOAT:		// 小数
        case SDT_BOOL:		// 逻辑
            arr[n++] = pArgInf[i].m_int;
            break;
        case SDT_INT64:		// 长整数
        case SDT_DOUBLE:	// 双精度小数
            memcpy(&arr[n], &pArgInf[i].m_int64, sizeof(pArgInf[i].m_int64));
            n += 2;
            break;
        case SDT_DATE_TIME:	// 日期时间
        {
            dateBuf.resize(260);
            DateTimeFormat(dateBuf.data(), 260, pArgInf[i].m_date, 0);
            arr[n++] = (int)dateBuf.copy();
            break;
        }
        case SDT_BIN:		// 字节集
            arr[n++] = (int)GetAryElementInf(pArgInf[i].m_pAryData, 0);
            break;
        default:            // 其他值就直接写入数组
            arr[n++] = pArgInf[i].m_int;
            break;
        }
    }
    if (isUnicode)
    {
        LPWSTR tmp = (LPWSTR)GetBinData(pArgInf[0].m_pBin, 0);
        wstr format(tmp);
        efree(tmp);
        ((wstr*)ret)->assign(__format_strW(format.c_str(), arr));
    }
    else
    {
        ((_str*)ret)->assign(__format_strA(pArgInf[0].m_pText, arr));
    }
    delete[] arr;
}

// 调用格式: SDT_TEXT wke_格式化文本, 命令说明: "利用c函数 sprintf来实现, 此命令不对参数进行校验"
// 参数<1>: 格式 SDT_TEXT, 参数说明: "详情请查看c语言介绍, 常用的%s=文本(日期时间型), %d=整数,%u=无符号整数,%p=指针,%x16=进制,%%=%...."
// 参数<2>: 参数 _SDT_ALL, 参数说明: NULL
EXTERN_C void WKE_NAME(222, wke_format)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str ret;
    __format_wke(nArgCount, pArgInf, &ret, false);
    pRetData->m_pText = CloneTextData(ret.c_str());
}

// 调用格式: SDT_BIN wke_格式化文本W, 命令说明: "利用c函数 swprintf来实现, Unicode版, 此命令不对参数进行校验"
// 参数<1>: 格式 SDT_TEXT, 参数说明: "详情请查看c语言介绍, 常用的%s=文本(日期时间型), %d=整数,%u=无符号整数,%p=指针,%x16=进制,%%=%...."
// 参数<2>: 参数 _SDT_ALL, 参数说明: NULL
EXTERN_C void WKE_NAME(223, wke_formatW)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wstr ret;
    __format_wke(nArgCount, pArgInf, &ret, true);
    pRetData->m_pBin = CloneBinData((LPBYTE)ret.c_str(), ret.size());
}

