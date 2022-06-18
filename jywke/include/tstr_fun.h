#pragma once

template<typename T> inline void tstr_free(T* p)
{
    if ( p )delete[] p;
}
template<typename T> inline T* tstr_alloc(int size)
{
    return new T[size];
}
// 重新分配内存, 不把旧数据写入新分配的内存里, 返回新分配的内存, 释放旧的内存
template<typename T> inline T* tstr_realloc(T*& p, int size)
{
    tstr_free(p);
    p = tstr_alloc<T>(size);
    return p;
}

namespace tstr_hide
{
    inline int tstr_vsnprintf_s(char* const _Buffer, size_t const _BufferCount, char const* const _Format, va_list _ArgList)
    {
#if _MSC_VER > 1200
        return _vsnprintf_s(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
#else
        typedef int(__cdecl* fn_vsnprintf_s)( char* const _Buffer, size_t const _BufferCount, size_t const _MaxCount, char const* const _Format, va_list _ArgList );
        static fn_vsnprintf_s fnFun;
        if ( fnFun )
            return fnFun(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
        HMODULE hModule = GetModuleHandleW(L"msvcrt.dll");
        if ( !hModule )
        {
            hModule = LoadLibraryW(L"msvcrt.dll");
            if ( !hModule )
                return vsprintf(_Buffer, _Format, _ArgList);
        }
        fnFun = (fn_vsnprintf_s)GetProcAddress(hModule, "_vsnprintf_s");
        if ( !fnFun )
            return vsprintf(_Buffer, _Format, _ArgList);
        return fnFun(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
#endif
    }

    inline int tstr_vsnwprintf_s(wchar_t* const _Buffer, size_t const _BufferCount, wchar_t const* const _Format, va_list _ArgList)
    {
#if _MSC_VER > 1200
        return _vsnwprintf_s(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
#else
        typedef int(__cdecl* fn_vsnwprintf_s)( wchar_t* const _Buffer, size_t const _BufferCount, size_t const _MaxCount, wchar_t const* const _Format, va_list _ArgList );
        static fn_vsnwprintf_s fnFun;
        if ( fnFun )
            return fnFun(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
        HMODULE hModule = GetModuleHandleW(L"msvcrt.dll");
        if ( !hModule )
        {
            hModule = LoadLibraryW(L"msvcrt.dll");
            if ( !hModule )
                return vswprintf(_Buffer, _Format, _ArgList);
        }

        fnFun = (fn_vsnwprintf_s)GetProcAddress(hModule, "_vsnwprintf_s");
        if ( !fnFun )
            return vswprintf(_Buffer, _Format, _ArgList);
        return fnFun(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
#endif
    }

};


// 格式化文本
template<typename T>
inline static int tstr_vsnprintf(T* const _Buffer, const size_t _bufferSize, const T* const _Format, va_list _ArgList)
{
    if ( sizeof(T) == 1 )
        return tstr_hide::tstr_vsnprintf_s((char*)_Buffer, _bufferSize, (char*)_Format, _ArgList);
    return tstr_hide::tstr_vsnwprintf_s((wchar_t*)_Buffer, _bufferSize, (wchar_t*)_Format, _ArgList);
}

template<typename T>
inline static int tstr_sprintf(T* const _Buffer, const size_t _bufferSize, const T* const _Format, ...)
{
    va_list aptr;
    va_start(aptr, _Format);
    int r = tstr_vsnprintf(_Buffer, _bufferSize, _Format, aptr);
    va_end(aptr);
    return r;
}


// 获取格式化文本, 返回文本地址, 返回的文本需要调用 tstr_free() 释放
// pSize = 接收文本长度, _vsnprintf_s 的返回值
// fmt = 格式化文本
// list = 参数列表
template<typename T> inline T* tstr_GetFormat(int* pSize, const T* fmt, va_list list)
{
    int bufferSize = 260;
    T* buffer = tstr_alloc<T>(bufferSize);
    int r = tstr_vsnprintf(buffer, bufferSize, fmt, list);
    while ( r == -1 )
    {
        bufferSize *= 2;
        buffer = tstr_realloc(buffer, bufferSize);
        r = tstr_vsnprintf(buffer, bufferSize, fmt, list);
    }
    if ( pSize )*pSize = r;
    return buffer;
}

// 获取格式化文本, 返回文本地址, 返回的文本需要调用 tstr_free() 释放
// pSize = 接收文本长度, _vsnprintf_s 的返回值
// fmt = 格式化文本
// list = 参数列表
template<typename T> inline T* tstr_GetFormat(int* pSize, const T* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    T* ret = tstr_GetFormat(pSize, fmt, list);
    va_end(list);
    return ret;
}

template<typename T>
inline int tstr_MessageBoxTimeout(HWND hWnd, const T* lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds, const T* fmt, va_list list)
{
    HMODULE hUser32 = GetModuleHandleW(L"user32.dll");
    if ( !hUser32 )return 0;

    typedef int( WINAPI* PFN_MSGBOX )( HWND hWnd, const T* lpText, const T* lpCaption,
                                      UINT uType, WORD wLanguageId, DWORD dwMilliseconds );
    PFN_MSGBOX pfn = (PFN_MSGBOX)GetProcAddress(hUser32, sizeof(T) == 1 ? "MessageBoxTimeoutA" : "MessageBoxTimeoutW");
    if ( !pfn ) return 0;

    T* text = tstr_GetFormat(0, fmt, list);
    int ret = pfn(hWnd, text, lpCaption, uType, wLanguageId, dwMilliseconds);
    delete[] text;
    return ret;
}

template<typename T>
inline int tstr_MessageBoxTimeout(HWND hWnd, const T* lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds, const T* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    int ret = tstr_MessageBoxTimeout(hWnd, lpCaption, uType, wLanguageId, dwMilliseconds, fmt, list);
    va_end(list);
    return ret;
}

template<typename T>
inline int tstr_MessageBoxEx(HWND hWnd, const T* lpCaption, UINT uType, WORD wLanguageId, const T* fmt, va_list list)
{
    return tstr_MessageBoxTimeout(hWnd, lpCaption, uType, wLanguageId, 0, fmt, list);
}

template<typename T>
inline int tstr_MessageBoxEx(HWND hWnd, const T* lpCaption, UINT uType, WORD wLanguageId, const T* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    int ret = tstr_MessageBoxTimeout(hWnd, lpCaption, uType, wLanguageId, 0, fmt, list);
    va_end(list);
    return ret;
}

template<typename T>
inline int tstr_MessageBox(HWND hWnd, const T* lpCaption, UINT uType, const T* fmt, va_list list)
{
    return tstr_MessageBoxTimeout(hWnd, lpCaption, uType, 0, 0, fmt, list);
}

template<typename T>
inline int tstr_MessageBox(HWND hWnd, const T* lpCaption, UINT uType, const T* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    int ret = tstr_MessageBoxTimeout(hWnd, lpCaption, uType, 0, 0, fmt, list);
    va_end(list);
    return ret;
}

template<typename T> inline void tstr_OutputDebugString(const T* fmt, va_list list)
{
    T* text = tstr_GetFormat(0, fmt, list);
    if ( sizeof(T) == 1 )
        OutputDebugStringA((char*)text);
    else
        OutputDebugStringW((wchar_t*)text);
    tstr_free(text);
}
template<typename T> inline void tstr_OutputDebugString(const T* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    tstr_OutputDebugString(fmt, list);
    va_end(list);
}

// 调试输出, 调试版编译版都会执行
template<typename T> inline void tstr_debug(const T* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    tstr_OutputDebugString(fmt, list);
    va_end(list);
}

// 有定义 _DEBUG 才会执行这个函数的内容, 否则这个函数说明也不做, 总的来说就是调试版才执行
template<typename T> inline void tstr_dbg(const T* fmt, ...)
{
#ifdef _DEBUG
    va_list list;
    va_start(list, fmt);
    tstr_OutputDebugString(fmt, list);
    va_end(list);
#endif
}





template<typename T>
inline static int tstr_cmp(const T* s1, const T* s2)
{
    if ( sizeof(T) == 1 )
        return strcmp((char*)s1, (char*)s2);
    return wcscmp((wchar_t*)s1, (wchar_t*)s2);
}

template<typename T>
inline static int tstr_ncmp(const T* s1, const T* s2, size_t count)
{
    if ( sizeof(T) == 1 )
        return strncmp((char*)s1, (char*)s2, count);
    return wcsncmp((wchar_t*)s1, (wchar_t*)s2, count);
}

template<typename T>
inline static int tstr_icmp(const T* s1, const T* s2)
{
#if _MSC_VER > 1200
    if ( sizeof(T) == 1 )
        return _stricmp((char*)s1, (char*)s2);
    return _wcsicmp((wchar_t*)s1, (wchar_t*)s2);
#else
    if ( sizeof(T) == 1 )
        return stricmp((char*)s1, (char*)s2);
    return wcsicmp((wchar_t*)s1, (wchar_t*)s2);
#endif
}

template<typename T>
inline static int tstr_nicmp(const T* s1, const T* s2, size_t count)
{
#if _MSC_VER > 1200
    if ( sizeof(T) == 1 )
        return _strnicmp((char*)s1, (char*)s2, count);
    return _wcsnicmp((wchar_t*)s1, (wchar_t*)s2, count);
#else
    if ( sizeof(T) == 1 )
        return strnicmp((char*)s1, (char*)s2, count);
    return wcsnicmp((wchar_t*)s1, (wchar_t*)s2, count);
#endif
}


template<typename T> inline static T tstr_str(T s1, T s2)
{
    if ( sizeof(T) == 1 )
        return strstr((char*)s1, (char*)s2);
    return wcsstr((wchar_t*)s1, (wchar_t*)s2);
}

template<typename T> inline static T tstr_rstr(T s1, T s2)
{
    if ( sizeof(T) == 1 )
        return strrchr((char*)s1, (char*)s2);
    return strrchr((wchar_t*)s1, (wchar_t*)s2);
}

template<typename T> inline static int tstr_vsscanf(const T* buffer, const T* fmt, va_list list)
{
#if _MSC_VER > 1200
#define _fun_a vsscanf_s
#define _fun_w vswscanf_s
#else
#define _fun_a vsscanf
#define _fun_w vswscanf
#endif
    if ( sizeof(T) == 1 )
        return _fun_a((const char*)buffer, (const char*)fmt, list);
    return _fun_w((const wchar_t*)buffer, (const wchar_t*)fmt, list);
#undef _fun_a
#undef _fun_w
}


template<typename T> inline static int tstr_sscanf(const T* buffer, const T* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    int ret = tstr_vsscanf(buffer, fmt, list);
    va_end(list);
    return ret;
}


template<typename T> inline static int tstr_len(const T* s)
{
    if ( !s )return 0;
    if ( sizeof(T) == 1 )
        return strlen((char*)s);
    return wcslen((wchar_t*)s);
}


template<typename T> inline static T* tstr_tok(T* s, const T* substr, T** next_token)
{
#if _MSC_VER > 1200
    if ( sizeof(T) == 1 )
        return (T*)strtok_s((char*)s, (char*)substr, (char**)next_token);
    return (T*)wcstok_s((wchar_t*)s, (wchar_t*)substr, (wchar_t**)next_token);

#else
    if ( sizeof(T) == 1 )
        return (T*)strtok((char*)s1, (char*)substr);
    return (T*)wcstok((wchar_t*)s1, (wchar_t*)substr);
#endif
}


template<typename T> inline static double tstr_stold(const T* val)
{
    if ( sizeof(T) == 1 )
        return (val && val[0]) ? stold((char*)val) : 0.0;
    
    wchar_t* _Eptr;
    return (!val || !val[0]) ? 0.0 : wcstod((wchar_t*)val, &_Eptr);
}

template<typename T> inline static double tstr_stod(const T* val)
{
    if ( sizeof(T) == 1 )
        return ( val && val[0] ) ? atof((char*)val) : 0.0;

    wchar_t* _Eptr;
    return ( !val || !val[0] ) ? 0.0 : wcstod((wchar_t*)val, &_Eptr);
}

template<typename T> inline static float tstr_stof(const T* val)
{
    return (float)tstr_stod(val);
}
