#pragma once
#include <tstr.h>
#include <elib/lib2.h>
#include <elib/lang.h>
#include <elib/fnshare.h>
#include "wke_cmd_typedef.h"
#include "wke_head_base.h"
#include <CStringBuffer.h>


// 缓冲池, 单位是字节
typedef CStringBufferA  BUFFER_POOL, * PBUFFER_POOL;

extern HINSTANCE WKE_NAME(0, g_hInst);
#define g_hInst WKE_NAME(0, g_hInst)

#define FREEARR_ARG(_index) if(pArgInf[_index].m_ppAryData) NotifySys(NRS_FREE_ARY, (DWORD)pArgInf[_index].m_dtDataType, (DWORD)* (pArgInf[_index].m_ppAryData))


#define SDT_TYPE_WKE_TB         MAKELONG (0x01, 0) // WKE_填表
#define SDT_TYPE_WKE_AJAX       MAKELONG (0x02, 0) // ajax
#define SDT_TYPE_WKE_JS         MAKELONG (0x03, 0) // Javascript
#define SDT_TYPE_WKE_SPECISL    MAKELONG (0x04, 0) // 特殊功能
#define SDT_TYPE_WKE_WEBKIT     MAKELONG (0x05, 0) // 精易Web浏览器 组件
#define SDT_TYPE_TYPERECT       MAKELONG (0x06, 0) // 矩形
#define SDT_TYPE_MEMBUFFER      MAKELONG (0x07, 0) // 内存缓冲区
#define SDT_TYPE_POSTELEMENT    MAKELONG (0x08, 0) // POST元素
#define SDT_TYPE_POSTELEMENTS   MAKELONG (0x09, 0) // POST元素集
#define SDT_TYPE_POPWND         MAKELONG (0x0A, 0) // 弹出窗口操作


#ifndef __E_STATIC_LIB
extern LIB_DATA_TYPE_INFO g_DataType_wke_global_var[];  // 数据类型数组
extern int g_DataType_wke_global_var_count;             // 数据类型成员数

extern LIB_CONST_INFO g_ConstInfo_wke_global_var[];     // 常量信息数组
extern int g_ConstInfo_wke_global_var_count;            // 常量信息成员数

extern CMD_INFO g_cmdInfo_wke_global_var[];             // 命令信息数组
extern int g_cmdInfo_wke_global_var_count;              // 命令信息成员数

#endif

#define __query(_a, _b) ( ((_a) & (_b)) == (_b)  )
#define _DBG_BREAK_TOSTR1(_num) #_num
#define _DBG_BREAK_TOSTR2(_num) _DBG_BREAK_TOSTR1(_num)
#define _DBG_BREAK_MSG(_s) { MessageBoxA(0, "行数: " _DBG_BREAK_TOSTR2(__LINE__) "\r\n文件: " __FILE__ \
                                "\r\n看到此信息框请截图发给006\r\n\r\n点击确定后程序将触发异常, 如果没有调试器, 则程序会崩溃"\
                                , _s, 0); __debugbreak(); }


// 定义易语言命令实现的函数声明
#define WKE_DEF_CMD(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    extern "C" void WKE_NAME(_index, _szEgName)(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf);

WKE_DEF(WKE_DEF_CMD)    // 命令实现声明

// 通过id获取hUnit, 第三个参数可以参考返回绑定的数据
HUNIT GethUnitFromId(DWORD dwWinFormID, DWORD dwUnitID, PVOID * pRet = 0);
// 通过参数里的第一个成员获取hUnit, 第二个参数可以参考返回绑定的数据
HUNIT GethUnitFromArgInf(PMDATA_INF pInf, PVOID * pRet = 0);
// 从hUnit里获取绑定的数据
PVOID GetDataFromHunit(HUNIT hUnit);
// 更新数据, 如果没有就直接返回
PVOID UpdateDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, PVOID pData);
// 绑定数据, 如果ID有相同的, 那会把 hUnit和 pData 覆盖进去, 否则会新建一个保存
PVOID SetDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, PVOID pData);

// 精易Web浏览器  下的组件交互方法
EXTERN_C PFN_INTERFACE WINAPI wke_GetInterface_webkit(INT nInterfaceNO);
bool init_webkit();


// 定义 精易web浏览器 这个类型
void head_dtType_Webkit(LIB_DATA_TYPE_INFO & dtType);

// 定义 弹出窗口 这个类型
void head_dtType_NewWnd(LIB_DATA_TYPE_INFO & dtType);

// 根据窗口创建CWnd指针
inline DWORD CreateUnit(PWKE_STRUCT_BASE data)
{
    // 每次都创建一个, 调用这个函数前已经有处理销毁的问题了
    data->hUnit = NotifySys(NAS_CREATE_CWND_OBJECT_FROM_HWND, (DWORD)data->hWnd, 0);
    SetDataFromIdUnit(data->dwWinFormID, data->dwUnitID, data->hUnit, data);
    return data->hUnit;
}

#define PROP_WNDUNIT L"{478011B2-E06D-4B4B-A323-5B4AD8F78DE6}"
inline void SetWndUnit(PWKE_STRUCT_BASE data, bool isClose)
{
    ::SetPropW(data->hWnd, PROP_WNDUNIT, (HANDLE)data->hUnit);
    if ( isClose )
        ::PostMessageW(data->hWnd, WM_CLOSE, 0, 0);
}

inline HUNIT GetWndUnit(HWND hWnd)
{
    //return (HUNIT)GetPropW(hWnd, PROP_WNDUNIT);
    return (HUNIT)RemovePropW(hWnd, PROP_WNDUNIT);
}

// 初始化data结构, 如果没有创建, 那就new一个, 如果已经创建, 那就从map里把data对应的窗口删除, 返回是否new了data
template<typename T>
inline bool InitDataEx(T*& data)
{
    if ( !data )
    {
        // 不是重新创建的窗口才初始化属性信息, 已经创建的窗口属性都有记录了
        data = new T;
        data->clear();
        data->init();
        return true;
    }

    if ( data->hUnit )
    {
        //HWND hWndOld = (HWND)NotifySys(NAS_DETACH_CWND_OBJECT, (DWORD)data->hUnit, 0);
        SetWndUnit(data, true);
        //data->pCtl->Destroy();
    }
    return false;
}

// 把数据写入缓冲区, 内部会判断是否越界, 越界后重新分配内存
// 写入后, pBuffer会增加nSize个字节, 返回写入的字节数
inline int write_data(_str & buffer, LPCVOID pData, int nSize)
{
    if ( nSize == 0 )
        return 0;
#ifdef _DEBUG
    if ( nSize < 0 )
        _DBG_BREAK_MSG("写入数据, 数据尺寸小于0");
#endif
    buffer.append((LPCSTR)pData, nSize);
    return nSize;
}
// 写入整数
inline int write_int32(_str & buffer, int number)
{
    return write_data(buffer, &number, sizeof(number));
}
// 把字符串写入缓冲区, 并把地址增加, 返回增加的字节数
inline int write_str_A(_str & buffer, LPCSTR pstr, size_t strLen = 0)
{
    if ( strLen == 0 )
        strLen = strlen(pstr);
    size_t len = strLen;  // 不包含结束的字节

    write_data(buffer, pstr, len);   // 这里把字符串写入, 不包含结束标志
    buffer.push_back(0);    // 写入结束标志, 1个字节0
    len++;
    return len;
}
// 把字符串写入缓冲区, 并把地址增加, 返回增加的字节数
inline int write_str_W(_str& buffer, LPCWSTR pstr, size_t strLen = 0)
{
    if ( !pstr )pstr = L"";
    if ( strLen == 0 )
        strLen = wcslen(pstr);
    size_t len = strLen * sizeof(wchar_t);  // 不包含结束的字节

    write_data(buffer, pstr, len);   // 这里把字符串写入, 不包含结束标志
    buffer.push_back(0);    // 写入结束标志, 两个字节, 都是0
    buffer.push_back(0);

    len += sizeof(wchar_t);
}


inline int read_int32(LPBYTE & buf)
{
    int ret = ( (LPINT)buf )[0];
    buf += sizeof(int);
    return ret;
}
// 读取字符串, 返回字符串地址, 同时地址增加, retSize接收地址增加多少个字节
inline LPCSTR read_str_A(LPBYTE& buf, int* retSize = 0)
{
    LPCSTR str = (LPCSTR)buf;
    size_t len = strlen(str) + 1;
    buf += len;
    if ( retSize )*retSize = (int)len;
    return str;
}
// 读取字符串, 返回字符串地址, 同时地址增加, retSize接收地址增加多少个字节
inline LPCWSTR read_str_W(LPBYTE& buf, int* retSize = 0)
{
    LPCWSTR str = (LPCWSTR)buf;
    size_t len = wcslen(str) * sizeof(wchar_t) + sizeof(wchar_t);
    buf += len;
    if ( retSize )*retSize = (int)len;
    return str;
}

// 往缓冲池里写入文本, 如果原来的文本足够存放, 那就继续存放, 不够就申请空间存放, 返回是否重新分配了内存
inline bool _set_buf_text(CStringBufferA* buf, LPCWSTR* ppszText, LPCWSTR text)
{
    if ( !text ) text = L"";
    LPWSTR pstr = (LPWSTR)*ppszText;
    if ( !pstr )
    {
        pstr = (LPWSTR)L"";
        *ppszText = pstr;
    }
    if ( !text[0] && !pstr[0] )
        return false;   // 两个都是空字符串, 不处理
    if ( wcscmp(text, pstr) == 0 )
        return false;   // 两个字符串一样, 不处理

    size_t len1 = wcslen(pstr);
    size_t len2 = wcslen(text);
    if ( len1 >= len2 )
    {
        // 够存放, 直接存放进去
        memcpy(pstr, text, len2 * sizeof(wchar_t) + sizeof(wchar_t));
        return false;
    }
    else
    {
        // 不够存放, 创建新的缓冲区存放
        *ppszText = buf->AddStringW(text, len2);
        return true;
    }
}
// 往缓冲池里写入文本, 如果原来的文本足够存放, 那就继续存放, 不够就申请空间存放, 返回是否重新分配了内存
inline bool _set_buf_text(CStringBufferA* buf, LPCSTR* ppszText, LPCSTR text)
{
    LPSTR pstr = (LPSTR)*ppszText;
    if ( !pstr[0] && !text[0] )
        return false;
    size_t len1 = strlen(pstr);
    size_t len2 = strlen(text);
    if ( len1 >= len2 )
    {
        // 够存放, 直接存放进去
        memcpy(pstr, text, len2 * sizeof(char) + sizeof(char));
        return false;
    }
    else
    {
        // 不够存放, 创建新的缓冲区存放
        *ppszText = buf->AddStringA(text, len2);
        return true;
    }
}
