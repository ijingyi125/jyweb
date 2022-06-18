#pragma once

#include <windows.h>
#include <stdio.h>
#include <new>
#include <charset.h>
#include <base64.h>
#include <tstr_fun.h>


#include <struct_hashfun.h>

#ifdef _DEBUG
#include <assert.h>
#else
  #ifndef assert
    #define assert(_a) 
  #endif
#endif
//#undef _MSC_VER
//#define _MSC_VER 1200


#if _MSC_VER > 1200
#include <type_traits>
//#include "traits.h"
#include <vcruntime_exception.h>
#include <iostream>
#define sscanf_api                                  sscanf_s
#define swscanf_api                                 swscanf_s
#define vsscanf_api                                 vsscanf_s
#define vswscanf_api                                vswscanf_s
#define stricmp_api                                 _stricmp
#define wcsicmp_api                                 _wcsicmp
#define strnicmp_api                                _strnicmp
#define wcsnicmp_api                                _wcsnicmp
#define strtok_api(_s, _d, _c)                      strtok_s(_s, _d, _c)
#define wcstok_api(_s, _d, _c)                      wcstok_s(_s, _d, _c)
#define sprintf_api(_buf, _size, _fmt, _vl)         sprintf_s(_buf, _size, _fmt, _vl) 
#define swprintf_api(_buf, _size, _fmt, _vl)        swprintf_s(_buf, _size, _fmt, _vl) 
#define strcpy_api(_buf, _size, _s)                 strcpy_s(_buf, _size, _s) 
#define wcscpy_api(_buf, _size, _s)                 wcscpy_s(_buf, _size, _s) 
#define strcat_api(_buf, _size, _s)                 strcat_s(_buf, _size, _s) 
#define wcscat_api(_buf, _size, _s)                 wcscat_s(_buf, _size, _s) 

#define _itow_api(_int, _buf, _size, _radix)        _itow_s(_int, _buf, _size, _radix) 
#define _itoa_api(_int, _buf, _size, _radix)        _itoa_s(_int, _buf, _size, _radix) 


#else
#pragma warning(disable:4068)
#pragma warning(disable:4800)
#define sscanf_api                                  sscanf
#define swscanf_api                                 swscanf
#define vsscanf_api                                 vsscanf
#define vswscanf_api                                vswscanf
#define stricmp_api                                 stricmp
#define wcsicmp_api                                 wcsicmp
#define strnicmp_api                                strnicmp
#define wcsnicmp_api                                wcsnicmp
#define strtok_api(_s, _d, _c)                      strtok(_s, _d)
#define wcstok_api(_s, _d, _c)                      wcstok(_s, _d)
#define sprintf_api(_buf, _size, _fmt, _vl)         sprintf(_buf, _fmt, _vl)
#define swprintf_api(_buf, _size, _fmt, _vl)        swprintf(_buf, _fmt, _vl)
#define strcpy_api(_buf, _size, _s)                 strcpy(_buf, _s) 
#define wcscpy_api(_buf, _size, _s)                 wcscpy(_buf, _s) 
#define strcat_api(_buf, _size, _s)                 strcat(_buf, _s) 
#define wcscat_api(_buf, _size, _s)                 wcscat(_buf, _s) 
#define _itow_api(_int, _buf, _size, _radix)        _itow(_int, _buf, _radix) 
#define _itoa_api(_int, _buf, _size, _radix)        _itoa(_int, _buf, _radix) 

#endif
template <typename _Elem> class str_base;


inline int ___vsnprintf_s(char* const _Buffer, size_t const _BufferCount, char const* const _Format, va_list _ArgList)
{
#if _MSC_VER > 1200
    return _vsnprintf_s(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
#else
    typedef int(__cdecl* fn_vsnprintf_s)(char* const _Buffer, size_t const _BufferCount, size_t const _MaxCount, char const* const _Format, va_list _ArgList);
    static fn_vsnprintf_s fnFun;
    if (fnFun)
        return fnFun(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
    HMODULE hModule = GetModuleHandleA("msvcrt.dll");
    if (!hModule)
    {
        hModule = LoadLibraryW(L"msvcrt.dll");
        if (!hModule)
            return vsprintf(_Buffer, _Format, _ArgList);
    }
    fnFun = (fn_vsnprintf_s)GetProcAddress(hModule, "_vsnprintf_s");
    if (!fnFun)
        return vsprintf(_Buffer, _Format, _ArgList);
    return fnFun(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
#endif
}

inline int ___vsnwprintf_s(wchar_t* const _Buffer, size_t const _BufferCount, wchar_t const* const _Format, va_list _ArgList)
{
#if _MSC_VER > 1200
    return _vsnwprintf_s(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
#else
    typedef int(__cdecl* fn_vsnwprintf_s)(wchar_t* const _Buffer, size_t const _BufferCount, size_t const _MaxCount, wchar_t const* const _Format, va_list _ArgList);
    static fn_vsnwprintf_s fnFun;
    if (fnFun)
        return fnFun(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
    HMODULE hModule = GetModuleHandleA("msvcrt.dll");
    if (!hModule)
    {
        hModule = LoadLibraryW(L"msvcrt.dll");
        if (!hModule)
            return vswprintf(_Buffer, _Format, _ArgList);
    }

    fnFun = (fn_vsnwprintf_s)GetProcAddress(hModule, "_vsnwprintf_s");
    if (!fnFun)
        return vswprintf(_Buffer, _Format, _ArgList);
    return fnFun(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
#endif
}


template <typename _Elem>
struct tagSTRARRDATA
{
    size_t* arr;    // 数组偏移
    size_t count;   // 数组成员数
    size_t len;     // str 字符串长度
    _Elem* str;     // 记录分割结果, 分割的字符串用\0代替, 用偏移指向字符串
};

template <typename _Elem>
class strArr
{
    friend class str_base<_Elem>;
    typedef tagSTRARRDATA<_Elem> STRARRDATA;
    typedef tagSTRARRDATA<_Elem>* LPSTRARRDATA;
public:
    //friend class str_base<_Elem>;

    strArr() { p = 0; }

    // 复制构造函数, 深层复制, 会拷贝一份新的数据出来
    strArr(const strArr& arrObj)
    {
        p = new STRARRDATA;
        memset(p, 0, sizeof(STRARRDATA));

        // 把字符串拷贝一份
        p->str = new _Elem[arrObj.p->len + 1];
        memset(p->str, 0, (arrObj.p->len + 1) * sizeof(_Elem));

        // 把数组偏移拷贝一份, 数组成员 = str + arr[index]
        p->arr = new size_t[arrObj.p->count];   
        memset(p->arr, 0, arrObj.p->count * sizeof(size_t));
        memcpy(p->arr, arrObj.p->arr, arrObj.p->count * sizeof(size_t));
    }
    ~strArr() { free(); }

    
    // 取指定成员的字符串, _index越界返回0, 返回的地址不可修改
    const _Elem* operator[](const size_t _index) const { return at(_index); }
    const _Elem* at(const size_t _index) const
    {
        if (!p || _index > p->count - 1)return 0;
        _Elem* ret = (_Elem*)(p->str + p->arr[_index]);
        return ret;
    }
    // 取数组成员数
    inline size_t count() { return size(); }
    inline size_t size() { return p ? p->count : 0; }
    inline bool Attach(LPSTRARRDATA ptr) { if (ptr)p = ptr; return ptr != 0; }
    // 释放数组, 释放后不能在使用, 本对象在析构时会自动释放
    inline void free()
    {
        if (!p)return;
        if (p->arr)delete[] p->arr;
        if (p->str)delete[] p->str;
        delete p;
        p = 0;
    }
private:
    LPSTRARRDATA p;
   
};





template <class _Mystr>
//typedef str_base<char> _Mystr;
class _str_base_iterator
{
    _Mystr m_data;
public:
#if _MSC_VER > 1200
    using value_type        = typename _Mystr::value_type;
    using reference         = typename _Mystr::reference;
    using pointer           = typename _Mystr::pointer;
#else
    typedef _Mystr::value_type      value_type;
    typedef _Mystr::reference       reference;
    typedef _Mystr::pointer         pointer;

#endif
};




//typedef wchar_t _Elem;
template <typename _Elem>
class str_base
{
public:

#if _MSC_VER > 1200
    //using allocator_type    = _Alloc;

    using value_type        = typename std::remove_cv<_Elem>::type;
    using pointer           = value_type*;
    using const_pointer     = const value_type*;
    using reference         = value_type&;
    using const_reference   = const value_type&;
    using iterator          = _str_base_iterator<str_base<_Elem>>;

    static constexpr auto npos{ static_cast<size_t>(-1) };
#else
    //typedef _Alloc                              allocator_type;

    typedef _Elem                               value_type;
    typedef value_type*                         pointer;
    typedef const value_type*                   const_pointer;
    typedef value_type&                         reference;
    typedef const value_type&                   const_reference;
    typedef _str_base_iterator<str_base<_Elem> > iterator;

    static const size_t npos;
#endif

private:
#define _STR_BUFFER_SIZE 4096
    typedef tagSTRARRDATA<value_type>  STRARRDATA;
    typedef tagSTRARRDATA<value_type>* LPSTRARRDATA;
    typedef struct _tagSTRMEMORYDATA
    {
        size_t  len;        // 字符串长度
        int     Addref;     // 引用计数, 只有手动增加, 在析构时做过值为0则释放, 在复制构造函数里这个值大于1时浅层拷贝, 等于1时深层拷贝
        pointer pData;      // 储存字符串的起始位置
        size_t  bufferLen;  // 本对象申请的缓冲区总长度
    }STRMEMORYDATA, * LPSTRMEMORYDATA;

    // 这个类只提供给字符串类使用
    class str_base_AutoFreePtr
    {
    private:
        pointer p;
    public:
        str_base_AutoFreePtr()                  { p = 0; }
        str_base_AutoFreePtr(pointer ptr)       { p = ptr; }
        ~str_base_AutoFreePtr()                 { if (p) ::free(p);  p = 0; }
        reference operator*() const             { return *p; }
        operator pointer () const __NO_EXCEPT   { return p; }
        pointer* operator&() __NO_EXCEPT        { return &p; }
        void operator=(pointer ptr)             { if (p)::free(p); p = ptr; }
    };



    // 如果第一个参数不是第二个参数里的指针, 那就不做任何处理
    // 判断第一个参数是否是第二个参数里的指针
    // 如果是, 那就新申请一块内存保存参数1的数据, 然后把参数1修改成新申请的这块内存地址, 并且把新申请的内存赋值给参数3, 参数3会自动释放
    inline static void autoFree_copy(const_pointer& s, const str_base* ptr, str_base_AutoFreePtr& __freeptr)
    {
        LPBYTE pTmpStart = (LPBYTE)(ptr->m_ptr);
        if (!pTmpStart) return;

        LPBYTE pTmpEnd = pTmpStart + sizeof(STRMEMORYDATA) + (ptr->m_ptr)->bufferLen * sizeof(value_type);
        if ((LPBYTE)s >= pTmpStart && (LPBYTE)s <= pTmpEnd)
        {
            __freeptr = copy(s);
            s = __freeptr;
        }
    }
    


    LPSTRMEMORYDATA  m_ptr;

public:
   

    // BJ 本对象的构造函数
    str_base() : m_ptr(0) { ; }
    explicit str_base(size_t _count) : m_ptr(0) { setstr(_count); if (m_ptr)m_ptr->len = 0; }
    str_base(const_pointer const s, size_t len = 0) : m_ptr(0) { setstr(s, len); }
    str_base(size_t _count, const value_type s) : m_ptr(0) { setstr(_count, s); }
#if _MSC_VER > 1200
    // 移动构造函数
    str_base(str_base&& s) noexcept : m_ptr(0)
    {
        swap(s);
        if (m_ptr && m_ptr->Addref > 1)
            m_ptr->Addref--;
    }
#endif
    // 复制构造函数
    str_base(const str_base& s) : m_ptr(0)
    {
        if (s.m_ptr && s.m_ptr->Addref > 1)    // 引用计数大于1则只做浅层拷贝
        {
            m_ptr = s.m_ptr;
            //m_flag = 0;
            return;

        }
        setstr(s.c_str(), s.size());
    }

    // 析构函数
    ~str_base() 
    { 
        Release();
        m_ptr = 0;
    }

protected:

    // 释放之前的文本, 把当前文本替换成设置的文本
    inline void setstr(const_pointer s, size_t len = 0)
    {
        if (s && m_ptr && s == m_ptr->pData)    // 传入的地址和本对象内的字符串首地址一样, 修改长度就行
        {
            if (!len)return;    // 没有传递长度, 那就是自己赋值给自己
            if (len >= m_ptr->bufferLen)
                len = m_ptr->bufferLen - 1;
            m_ptr->pData[len] = 0;
            m_ptr->len = len;
            return;
        }
        size_t strlen = 0;
        if (s)
            strlen = tstr_len(s);
        if (len == 0)
            len = strlen;
        
        
        pointer p = realloc(len);
        str_base_AutoFreePtr __freeptr;
        autoFree_copy(s, this, __freeptr);

        memset(p, 0, m_ptr->bufferLen * sizeof(value_type));
        if (s)
            memcpy(p, s, len * sizeof(value_type));
        m_ptr->len = len;
    }
    // 释放之前的文本, 把当前文本替换成指定数量的字符
    inline void setstr(size_t _count, value_type s = 0)
    {
        if (_count == npos) _count = 0;
        pointer p = realloc(_count);
        if (s)
        {
            size_t i;
            for (i = 0; i < _count; i++)
                p[i] = s;
        }
        m_ptr->len = _count;
    }

private:
    inline const str_base* __get_this()const  __NO_EXCEPT
    {
        return this;
    }
public:
    // BJ 本对象的重载运算符
#pragma region _operator

    // 重新分配缓冲区, 不会修改原有字符串长度和数据
    inline bool operator()(size_t count)
    {
        if (!m_ptr || m_ptr->bufferLen > count)return false;
        return realloc(count) != 0;
    }
    // 如果对象未初始化, 则返回一个空引用
    reference operator*() const
    {
        // 应该设计成抛出异常还是返回空类型?
        return m_ptr ? *m_ptr->pData : *((pointer)0);
    }

    //pointer* operator&() __NO_EXCEPT
    //{
    //    return m_ptr ? &m_ptr->pData : 0;
    //}
    //const_pointer* operator&()const  __NO_EXCEPT
    //{
    //    return m_ptr ? &m_ptr->pData : 0;
    //}

    //// 重载类型
    //inline operator pointer() const
    //{
    //    return m_ptr ? m_ptr->pData : 0;
    //}
    // 通过下标索引到指定的字符,返回引用,可以修改值, 下标越界抛出异常, 类型为 size_t 值为 传入的下标
    inline reference operator[](size_t _off)
    {
        if (!m_ptr || _off >= m_ptr->len) throw _off;
        return m_ptr->pData[_off];
    }

    // 通过下标索引到指定的字符,返回值,不可修改, 下标越界抛出异常, 类型为 size_t 值为 传入的下标
    inline const value_type operator[](size_t _off)const
    {
        if (!m_ptr || _off >= m_ptr->len) throw _off;
        return m_ptr->pData[_off];
    }

    // 赋值,返回本对象的引用
    inline str_base& operator=(const str_base& s)
    {
        if (this == s.__get_this())
            return *this;
        return assign(s);
    }

    // 赋值,返回本对象的引用
    inline str_base& operator=(const_pointer s)
    {
        if (m_ptr && s == m_ptr->pData)return *this;    // 赋值的指针就算是本对象的指针
        return assign(s);
    }
#if _MSC_VER > 1200
    friend std::ostream& operator <<(std::ostream& out, const str_base& obj)
    {
        if (obj.m_ptr)
            std::cout << obj.m_ptr->pData;
        return out;
    }
    // 赋值,返回本对象的引用, 右值引用版
    inline str_base& operator=(str_base&& s) __NO_EXCEPT
    {
        return assign(std::move(s));
    }
    // 加入文本, 返回本对象的引用, 右值引用版
    inline str_base& operator+(str_base&& s) noexcept
    {
        return append(std::move(s));
    }
#endif
    // 字符相加,两个操作数至少有一个是本类对象,返回相加后的对象
    inline str_base operator+(const value_type s)
    {
        str_base tmp;
        if (!m_ptr)    // 原字符串没有初始化
        {
            tmp.assign(s);
        }
        else
        {
            tmp.resize(m_ptr->len + 1);
            tmp.assign(m_ptr->pData, m_ptr->len).append(s);
        }
        
        tmp.Addref();
        return tmp;
    }

    // 字符串相加,两个操作数至少有一个是本类对象,返回相加后的对象
    inline str_base operator+(const str_base& s)
    {
        if (!m_ptr)
            return s;    // 原字符串没有初始化直接返回被加的字符串
        str_base ret = operator+(s.c_str());
        ret.Addref();
        return ret;
    }
    // 字符串相加,两个操作数至少有一个是本类对象,返回相加后的对象
    inline str_base operator+(const_pointer s)
    {
        if (!m_ptr) return s;   // 原字符串没有初始化直接返回被加的字符串
        if (!s)return m_ptr->pData;

        str_base ret(m_ptr->len + tstr_len(s));
        ret.assign(m_ptr->pData, m_ptr->len).append(s);
        ret.Addref();
        return ret;
    }
    // 将字符串连接到本对象字符串的后面
    inline void operator+=(const str_base& s)           { append(s); }
    // 将字符串连接到本对象字符串的后面
    inline void operator+=(const value_type s)          { append(1, s); }
    // 将字符串连接到本对象字符串的后面
    inline void operator+=(const_pointer s)             { append(s); }

    // 本对象的字符串是否小于另一个字符串
    inline bool operator<(const str_base& s2)const      { return operator<(s2.c_str()); }
    inline bool operator<(const_pointer s2)const        { return compare(s2, true) < 0; }


    // 本对象的字符串是否大于另一个字符串
    inline bool operator>(const str_base& s2)const      { return operator>(s2.c_str()); }
    inline bool operator>(const_pointer s2)const        { return compare(s2, true) > 0; }

    // 本对象的字符串是否等于另一个字符串
    inline bool operator==(const str_base& s2)const     { return operator==(s2.c_str()); }
    inline bool operator==(const_pointer s2)const       { return compare(s2, true) == 0; }


    // 本对象的字符串是否不等于另一个字符串
    inline bool operator!=(const str_base& s2)const     { return operator!=(s2.c_str()); }
    inline bool operator!=(const_pointer s2)const       { return compare(s2, true) != 0; }

#pragma endregion
private:
    template <typename T>
    inline str_base& NumberToString(const_pointer format, T value, bool isAppend, bool isFloat)
    {
        value_type ret[50] = { 0 };
        int len = 0;
        if (sizeof(value_type) == 2)
            len = swprintf_api((LPWSTR)ret, 50, (LPCWSTR)format, value);
        else
            len = sprintf_api((LPSTR)ret, 50, (LPCSTR)format, value);
        if (isFloat && len > 0)
        {
            while (len && ret[len - 1] == '0')
                --len;
            if (ret[len - 1] == '.')
                --len;
        }
        if (isAppend)
            return append(ret, len);
        return assign(ret, len);
    }
    

    inline static int __debug(str_base* pstr, size_t bufferSize, const_pointer format, va_list list)
    {
        if (bufferSize == 0)bufferSize = 260;
        str_base buf(bufferSize);

        pointer buffer = buf.data();
        //pointer buffer = realloc(bufferSize, true);
        int r = tstr_vsnprintf(buffer, bufferSize, format, list);
        while (r == -1)
        {
            bufferSize *= 2;
            buf.resize(bufferSize);
            buffer = buf.data();
            r = tstr_vsnprintf(buffer, bufferSize, format, list);
        }
        outputDebugString(buffer);
        buf.resize(r);
        if (pstr)
            pstr->swap(buf);
        return r;
    }
public:
    // assign append 
#pragma region _append_assign
#if _MSC_VER > 1200
    inline str_base& append(str_base&& s) noexcept
    {
        if (!m_ptr) // 加入时本对象没有初始化, 直接把传递进来的对象指针赋值给本对象
        {
            m_ptr = s.m_ptr;
            s.m_ptr = 0;
            return *this;
        }
        // 走到这表示赋值时本对象已经初始化, 判断传入的对象有没有初始化
        STRMEMORYDATA* ptr = s.m_ptr;
        if (!ptr)
        {
            // 传入的对象没有初始化, 直接返回本对象
            return *this;
        }

        // 走到这传入的对象和本对象都不为空, 对比一下哪个缓冲区大, 哪个大用哪个
        if (m_ptr->bufferLen > ptr->bufferLen)  // 本对象的缓冲区比较大, 拷贝到本对象内
        {
            return append(ptr->pData, ptr->len);   // 直接往后加入字符串
        }
        if (ptr->len + m_ptr->len > ptr->bufferLen) // 传入对象的缓冲区不足以存放两个字符串的结果
        {
            return append(ptr->pData, ptr->len);   // 直接往后加入字符串
        }

        // 走到这传入的对象缓冲区比本对象要大, 且能存放结果
        // 用传入对象的后半部分作为临时缓冲区, 记录本对象的数据
        pointer pData = (ptr->pData + ptr->bufferLen) - ptr->len;               // 记录临时对象的临时缓冲区
        memcpy(pData, ptr->pData, ptr->len * sizeof(value_type));               // 把传入对象的数据临时记录到临时缓冲区的尾部
        memcpy(ptr->pData, m_ptr->pData, m_ptr->len * sizeof(value_type));      // 把本对象的数据拷贝到传入的对象
        memcpy(ptr->pData + m_ptr->len, pData, ptr->len * sizeof(value_type));  // 把临时缓冲区的数据拷贝到字符串的尾部
        ptr->len += m_ptr->len;
        ptr->pData[ptr->len] = 0;
        s.m_ptr = m_ptr;
        m_ptr = ptr;
        return *this;
    }
#endif
    // 加入文本到最后, len = 0则以\0结尾
    str_base& append(const_pointer _ptr, const size_t _len = 0)
    {
        if (_ptr == 0) return *this;
        size_t len = _len;
        if (len == 0) len = tstr_len(_ptr);
        if (len == 0) return *this;

        pointer p = 0;
        if (!m_ptr) p = realloc(len + _STR_BUFFER_SIZE);    // 原字符串没有初始化则初始化一下

        size_t newLen = len + m_ptr->len;
        if (newLen <= m_ptr->bufferLen)    // 缓冲区还足够存放新数据
        {
            memcpy(m_ptr->pData + m_ptr->len, _ptr, len * sizeof(value_type));    // 直接拷贝到字符串缓冲区里面
            m_ptr->pData[newLen] = 0;
            m_ptr->len = newLen;
            return *this;
        }

        // 走到这就是缓冲区不够大, 需要重新申请
        size_t bufferSize = newLen + _STR_BUFFER_SIZE;    // 缓冲区需要多申请长度
        p = realloc(bufferSize);
        memcpy(m_ptr->pData + m_ptr->len, _ptr, len * sizeof(value_type));    // 直接拷贝到字符串缓冲区里面
        m_ptr->pData[newLen] = 0;
        m_ptr->len = newLen;    // 新字符串的长度
        return *this;
    }
    // 加入一个字符
    inline str_base& append(value_type _ch) { return append(&_ch, 1); }
    // 加入一段重复字符的文本, _count = 重复数量, _ch = 字符
    inline str_base& append(const size_t _count, const value_type _ch)
    {
        if (_count == 0) return *this;
        str_base_AutoFreePtr p(alloc(_count, _ch));
        return append(p, _count);
    }

    inline str_base& append(int Val)
    {
        const value_type format[] = { '%', 'd', '\0' };
        return NumberToString(format, Val, true, false);
    }
    inline str_base& append(unsigned int Val)
    {
        const value_type format[] = { '%', 'u', '\0' };
        return NumberToString(format, Val, true, false);
    }
    inline str_base& append(long Val)
    {
        const value_type format[] = { '%', 'l', 'd' ,'\0' };
        return NumberToString(format, Val, true, false);
    }
    inline str_base& append(unsigned long Val)
    {
        const value_type format[] = { '%','l', 'u' ,'\0' };
        return NumberToString(format, Val, true, false);
    }

    inline str_base& append(__int64 Val)
    {
        const value_type format[] = { '%','l', 'l', 'd' ,'\0' };
        return NumberToString(format, Val, true, false);
    }

    inline str_base& append(unsigned __int64 Val)
    {
        const value_type format[] = { '%','l', 'l', 'u' ,'\0' };
        return NumberToString(format, Val, true, false);
    }

    inline str_base& append(float Val)
    {
        const value_type format[] = { '%','f' ,'\0' };
        return NumberToString(format, Val, true, true);
    }
    inline str_base& append(double Val)
    {
        const value_type format[] = { '%','f' ,'\0' };
        return NumberToString(format, Val, true, true);
    }

    // 第二个参数区分指针和其他, 第二个参数没有使用, 填0或者任意指针都可以
    inline str_base& append(const void* Val, const void* b)
    {
        const value_type format[] = { '%','p' ,'\0' };
        return NumberToString(format, Val, true, false);
    }

    inline str_base& append(long double Val)
    {
        const value_type format[] = { '%','l' ,'f' ,'\0' };
        return NumberToString(format, Val, true, true);
    }


    // 加入一段重复的文本, _count = 重复数量, 等于0不操作, _ptr = 重复的文本, _len = 加入文本的长度, 为0则 _ptr必须以\0为结尾
    inline str_base& append(const size_t _count, const_pointer _ptr, const size_t _len = 0)
    {
        if (!_ptr)return *this;
        size_t count = _count;
        if (count == 0)return *this;

        size_t len = _len;
        if (len == 0) len = tstr_len(_ptr);
        if (!m_ptr) realloc(len + _STR_BUFFER_SIZE);    // 原字符串没有初始化则初始化一下

        pointer buffer = 0;
        size_t newLen = _count * len;
        size_t oldLen = m_ptr->bufferLen - m_ptr->len;
        if (oldLen > newLen)    // 旧缓冲区足够存放
            buffer = m_ptr->pData;
        else
            buffer = realloc(newLen + m_ptr->len + _STR_BUFFER_SIZE);   // 不够存放则重新分配内存
        
        buffer += +m_ptr->len;  // 指向字符串尾部
        size_t i;
        for (i = 0; i < _count; i++)
            memcpy(buffer + len * i, _ptr, len * sizeof(value_type));
        m_ptr->len += newLen;
        m_ptr->pData[m_ptr->len] = 0;
        return *this;
    }

    // 加入一段重复文本, _count 小于1则设置为1
    inline str_base& append(const size_t _count, const str_base& str, size_t _len = 0)
    {
        size_t count = _count;
        if (count == 0)count = 1;
        if (_len == 0)_len = str.size();
        return append(_count, str.c_str(), _len);
    }

    // 加入一段重复文本, _count 小于1则设置为1
    inline str_base& append(const str_base& _str, const size_t _count = 1)
    {
        size_t count = _count;
        if (count == 0)count = 1;
        return append(_count, _str.c_str(), _str.size());
    }


#if _MSC_VER > 1200
    inline str_base& assign(str_base&& s)
    {
        if (!m_ptr) // 赋值时本对象没有初始化, 直接把传递进来的对象指针赋值给本对象
        {
            m_ptr = s.m_ptr;
            s.m_ptr = 0;
            return *this;
        }
        // 走到这表示赋值时本对象以及初始化, 对比一下哪个缓冲区大, 哪个大用哪个
        STRMEMORYDATA* ptr = s.m_ptr;
        if (!ptr)
        {
            // 传入的对象没有初始化, 给本对象清0
            m_ptr->pData[0] = 0;
            m_ptr->len = 0;
            return *this;
        }

        // 走到这传入的对象和本对象都不为空
        if (m_ptr->bufferLen > ptr->bufferLen)  // 本对象的缓冲区比较大
        {
            memcpy(m_ptr->pData, ptr->pData, ptr->len * sizeof(value_type) + sizeof(value_type));
            m_ptr->len = ptr->len;  // 传入的对象缓冲区比较小, 则把传入对象的内容拷贝到本对象, 不处理传入的对象
            return *this;
        }
        // 走到这传入的对象缓冲区比本对象要大, 两个对象交换一下
        swap(s);
        return *this;
    }
#endif
    // 赋值, len = 0则以\0结尾
    inline str_base& assign(const_pointer _ptr, size_t len = 0)
    {
        setstr(_ptr, len);
        return *this;
    }
    // 赋值为一段重复字符的文本, _count = 重复数量, _ch = 字符
    inline str_base& assign(size_t _count, value_type _ch)
    {
        str_base_AutoFreePtr p(alloc(_count, _ch));
        return assign(p, _count);
    }
    // 赋值为一段重复的文本, _count = 重复数量, 等于0不操作, _ptr = 重复的文本
    inline str_base& assign(size_t _count, const_pointer _ptr, size_t strLen)
    {
        if (_count == 0)return *this;
        if (strLen == 0) strLen = tstr_len(_ptr);
        size_t newLen = _count * strLen;
        size_t oldLen = m_ptr ? m_ptr->bufferLen : 0;
        pointer buffer = m_ptr ? m_ptr->pData : 0;
        if (oldLen <= newLen)    // 缓冲区不够存放
            buffer = realloc(newLen);

        size_t i;
        for (i = 0; i < _count; i++)
            memcpy(buffer + strLen * i, _ptr, strLen * sizeof(value_type));
        buffer[newLen] = 0;
        m_ptr->len = newLen;
        return *this;
    }
    // 赋值为一段重复文本, _count 小于1则设置为1
    inline str_base& assign(const str_base& _str, const size_t _count = 1)
    {
        size_t count = _count;
        if (count == 0)count = 1;
        return assign(count, _str.c_str(), _str.size());
    }

    inline str_base& assign(int Val)
    {
        const value_type format[] = { '%', 'd', '\0' };
        return NumberToString(format, Val, false, false);
    }
    inline str_base& assign(unsigned int Val)
    {
        const value_type format[] = { '%', 'u', '\0' };
        return NumberToString(format, Val, false, false);
    }
    inline str_base& assign(long Val)
    {
        const value_type format[] = { '%', 'l', 'd', '\0' };
        return NumberToString(format, Val, false, false);
    }
    inline str_base& assign(unsigned long Val)
    {
        const value_type format[] = { '%', 'l', 'u', '\0' };
        return NumberToString(format, Val, false, false);
    }

    inline str_base& assign(__int64 Val)
    {
        const value_type format[] = { '%', 'l', 'l', 'd', '\0' };
        return NumberToString(format, Val, false, false);
    }

    inline str_base& assign(unsigned __int64 Val)
    {
        const value_type format[] = { '%', 'l', 'l', 'u', '\0' };
        return NumberToString(format, Val, false, false);
    }

    inline str_base& assign(float Val)
    {
        const value_type format[] = { '%', 'f', '\0' };
        return NumberToString(format, Val, false, true);
    }
    inline str_base& assign(double Val)
    {
        const value_type format[] = { '%', 'f', '\0' };
        return NumberToString(format, Val, false, true);
    }
    inline str_base& assign(long double Val)
    {
        const value_type format[] = { '%', 'l', 'f', '\0' };
        return NumberToString(format, Val, false, true);
    }



#pragma endregion

    // 文本常用操作, 重置大小, 格式化, 比较, 到大小写
#pragma region text_resize_format_cmp_toup_tolo

    // 根据要求追加或删除元素, 为字符串指定新的大小
    // 重新调整尺寸, 之前的数据不清除, 调用后字符串长度 = 设置的长度
    // _ch = 用于填充的数据, 如果为0,则保留原数据, 多余部分用0填充, 不为0则清除原数据并用该字符填充
    inline void resize(size_t newsize, value_type _ch = 0)
    {
        if (!m_ptr)
        {
            setstr(newsize, _ch);
            return;
        }
        if (m_ptr->bufferLen < newsize)    // 缓冲区不够存放新数据
        {
            realloc(m_ptr->bufferLen + newsize + _STR_BUFFER_SIZE);
        }

        m_ptr->len = newsize;
        for (size_t i = newsize; i < m_ptr->bufferLen; i++)
            m_ptr->pData[i] = _ch;    // 超出部分用指定字符填充
        return;
    }

    // 重新设置当前字符串对象的字符串长度, 不会修改任何内存, 只修改\0之前有多少个字符
    inline size_t resize_strlen()
    {
        if (!m_ptr) return 0;
        m_ptr->len = tstr_len(m_ptr->pData);
        return m_ptr->len;
    }

    // 重新调整缓冲区尺寸, 不会改变原数据大小, 之前的数据不清除, 如果新尺寸小于当前已占用尺寸则返回false
    inline bool reserve(size_t newsize)
    {
        size_t oldLen = 0;
        if (m_ptr)oldLen = m_ptr->len;
        if (newsize < oldLen) return false;
        resize(newsize);
        m_ptr->len = oldLen;
        return true;
    }

    // 取指定位置的字节, 该函数不抛出异常, 但会返回一个空引用 operator[] 会抛出异常, 下标越界和未初始化都返回空引用
    inline reference at(const size_t off) __NO_EXCEPT
    {
        if (!m_ptr || off >= m_ptr->len) return *((pointer)0);
        return m_ptr->pData[off];
    }
    // 取指定位置的字节, 该函数不抛出异常, 下标越界和未初始化都返回空引用
    inline const_reference at(const size_t off)const __NO_EXCEPT
    {
        if (!m_ptr || off >= m_ptr->len) return *((pointer)0);
        return m_ptr->pData[off];
    }

    // 返回字符串中第一个元素的引用
    inline reference front()
    {
        if (!m_ptr || !m_ptr->len) return *((pointer)0);
        return m_ptr->pData[0];
    }

    // 返回字符串中第一个元素的引用
    inline const_reference front() const
    {
        if (!m_ptr || !m_ptr->len) return *((pointer)0);
        return m_ptr->pData[0];
    }


    // 返回字符串中最后一个元素的引用
    inline reference back()
    {
        if (!m_ptr || !m_ptr->len) return *((pointer)0);
        return m_ptr->pData[m_ptr->len - 1];
    }

    // 返回字符串中最后一个元素的引用
    inline const_reference back() const
    {
        if (!m_ptr || !m_ptr->len) return *((pointer)0);
        return m_ptr->pData[m_ptr->len - 1];
    }
    
    // Debug 和 Release版本都会输出
    // pstr = 接收输出的文本
    inline static void debug(str_base* pstr, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        __debug(pstr, 260, format, aptr);
        va_end(aptr);
        return;
    }
    // Debug 和 Release版本都会输出
    inline static void debug(const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        __debug(0, 260, format, aptr);
        va_end(aptr);
        return;
    }
    // Release版不会编译, 如果编译后也需要输出的, 请调用 debug
    inline static void dbg(const_pointer format, ...)
    {
#ifdef _DEBUG
        va_list aptr;
        va_start(aptr, format);
        __debug(0, 260, format, aptr);
        va_end(aptr);
        return;
#endif
    }
    // Release版不会编译, 如果编译后也需要输出的, 请调用 debug
    // pstr = 接收输出的文本, 如果为Release版不会处理此参数
    inline static void dbg(str_base* pstr, const_pointer format, ...)
    {
#ifdef _DEBUG
        va_list aptr;
        va_start(aptr, format);
        __debug(pstr, 260, format, aptr);
        va_end(aptr);
        return;
#endif
    }
    // Release版不会编译, 如果编译后也需要输出的, 请调用 debug
    inline static void tssc(const_pointer format, ...)
    {
#ifdef _DEBUG
        va_list aptr;
        va_start(aptr, format);
        __debug(0, 260, format, aptr);
        va_end(aptr);
        return;
#endif
    }
    inline static void outputDebugString(const char* s)
    {
        OutputDebugStringA(s);
    }
    inline static void outputDebugString(const wchar_t* s)
    {
        OutputDebugStringW(s);
    }

    // 获取格式化文本, 缓冲区尺寸为260, 缓冲区不够时会扩充
    inline static str_base GetFormat(const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        str_base ret = GetFormatEx(260, format, aptr);
        va_end(aptr);
        return ret;
    }

    // 获取格式化文本, 自定义缓冲区大小, 缓冲区不够时会扩充
    inline static str_base GetFormat(size_t bufferSize, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        str_base ret = GetFormatEx(bufferSize, format, aptr);
        va_end(aptr);
        return ret;
    }

    // 生成格式化文本, 缓冲区尺寸为260, 缓冲区不够时会扩充
    // bufferSize = 缓冲区长度, 如果为0则设置为260
    // format 格式化字符串
    // list = 参数列表
    inline static str_base GetFormatEx(size_t bufferSize, const_pointer format, va_list list)
    {
        if (bufferSize == 0)
            bufferSize = 260;
        str_base buf(bufferSize);
        pointer buffer = buf.data();
        int r = tstr_vsnprintf(buffer, bufferSize, format, list);
        while (r == -1)
        {
            bufferSize *= 2;
            buf.resize(bufferSize);
            buffer = buf.data();
            r = tstr_vsnprintf(buffer, bufferSize, format, list);
        }
        buf.resize(r);
        buf.Addref();
        return buf;
    }

    
    // 格式化文本, 缓冲区尺寸为260, 缓冲区不够时会扩充
    inline int FormatEx(size_t bufferSize, const_pointer format, va_list list)
    {
        str_base buf = GetFormatEx(bufferSize, format, list);

        if (!m_ptr) // 本对象没有初始化, 直接把临时对象指针赋值给本对象
        {
            swap(buf);
            return (int)buf.size();
        }

        if (m_ptr->bufferLen > bufferSize)  // 本对象的缓冲区比较大
        {
            assign(buf);    // 传入的对象缓冲区比较小, 则把传入对象的内容拷贝到本对象, 不处理传入的对象
            return (int)buf.size();
        }
        // 走到这传入的对象缓冲区比本对象要大, 两个对象交换一下
        swap(buf);
        return (int)buf.size();
    }

    // 格式化文本, 缓冲区尺寸为260, 缓冲区不够时会扩充
    inline int Format(const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        int r = FormatEx(260, format, aptr);
        va_end(aptr);
        return r;
    }

    // 格式化文本, 自定义缓冲区大小, 缓冲区不够时会扩充
    inline int Format(size_t bufferSize, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        int r = FormatEx(bufferSize, format, aptr);
        va_end(aptr);
        return r;
    }

    // 格式化一段文本并加入到当前字符串内
    // 格式化文本缓冲区尺寸为260, 缓冲区不够时会扩充
    inline str_base& AppendFormat(const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        append(GetFormatEx(260, format, aptr));
        va_end(aptr);
        return *this;
    }

    // 格式化一段文本并加入到当前字符串内
    // 自定义格式化文本缓冲区大小, 缓冲区不够时会扩充
    inline str_base& AppendFormat(size_t bufferSize, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        append(GetFormatEx(bufferSize, format, aptr));
        va_end(aptr);
        return *this;
    }

    // 将当前对象的文本按 format 的格式取出来放到后面的参数里, 失败返回-1, 支持 %[a-z]
    // ... 参数接收变量地址
    // 比如把 2020-01-01 01:01:01 把年月日时分秒都取出来, 那format就是 %d-%d-%d %d:%d:%d
    inline int sscanf(const_pointer format, ...)
    {
        if (empty())return -1;
        va_list aptr;
        va_start(aptr, format);
        int ret = tstr_vsscanf(m_ptr->pData, format, aptr);
        va_end(aptr);
        return ret;
    }

    // 将 buffer 的文本按 format 的格式取出来放到后面的参数里, 失败返回-1, 支持 %[a-z]
    // ... 参数接收变量地址
    // 比如把 2020-01-01 01:01:01 把年月日时分秒都取出来, 那format就是 %d-%d-%d %d:%d:%d
    inline static int sscanf(const_pointer buffer, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        int ret = tstr_vsscanf(buffer, format, aptr);
        va_end(aptr);
        return ret;
    }

    // 将错误码转成错误文本
    // errCode 错误码
    // lpszModule = 错误码所在的模块, 为0则自动搜索当前进程文件的消息资源
    inline static str_base FormatMsg(DWORD errCode, const_pointer lpszModule = 0)
    {
        HMODULE hModule = 0;
        bool isFree = false;
        if (lpszModule)
        {
            hModule = __GetModuleHandle(lpszModule);
            if (!hModule)
            {
                hModule = __LoadLibrary(lpszModule);
                if (hModule) isFree = true;
            }
        }
        
        str_base ret = FormatMsg(errCode, hModule);
        if (isFree)FreeLibrary(hModule);

        ret.Addref();
        return ret;
    }

    // 将错误码转成错误文本
    // errCode 错误码
    // hModule = 错误码所在的模块句柄, 为0则自动搜索当前进程文件的消息资源
    inline static str_base FormatMsg(DWORD errCode, HMODULE hModule = 0)
    {
        pointer pBuffer = NULL;
        DWORD dwFlags = 0;
        if (hModule) dwFlags = FORMAT_MESSAGE_FROM_HMODULE;

        //lpSource = dwFlags指定了FORMAT_MESSAGE_FROM_HMODULE的话, 此参数表示模块的HANDLE 

        DWORD size = __FormatMessage(
            /*DWORD dwFlags*/       FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | dwFlags,
            /*LPCVOID lpSource*/    hModule,
            /*DWORD dwMessageId*/   errCode,
            /*DWORD dwLanguageId*/  0,
            /*LPWSTR lpBuffer*/     (LPWSTR)&pBuffer,
            /*DWORD nSize*/         0,
            /*va_list* Arguments*/  NULL);
        if (size == 0)return str_base();
        str_base ret(pBuffer);
        ret.Addref();
        LocalFree(pBuffer);
        return ret;
    }

    // 使用指定的消息和变量格式化消息字符串参数列表
    LPWSTR GetFormattedMessage(LPWSTR pMessage, ...)
    {
        LPWSTR pBuffer = NULL;

        va_list args = NULL;
        va_start(args, pMessage);

        FormatMessageW(FORMAT_MESSAGE_FROM_STRING |
            FORMAT_MESSAGE_ALLOCATE_BUFFER,
            pMessage,
            0,
            0,
            (LPWSTR)&pBuffer,
            0,
            &args);

        va_end(args);

        return pBuffer;
    }

    // 把当前字符串转成小写, 返回替换的字符数
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回0
    inline str_base tolower(const size_t _off = 0, const size_t _count = size_t(-1)) const
    {
        if (_count == 0 || !m_ptr)return str_base();
        str_base ret;
        tolowerEx(ret, m_ptr->pData, m_ptr->len, _off, _count);
        ret.Addref();
        return ret;
    }

    // 把当前字符串转成小写, 返回替换的字符数
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回0
    inline int tolowerEx(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_count == 0 || !m_ptr)return 0;
        return tolowerEx(*this, m_ptr->pData, m_ptr->len, _off, _count);
    }

    // 把当前字符串转成大写, _off=起始位置, _count=转换的字符数, 返回替换的字符数
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回0
    inline str_base toupper(const size_t _off = 0, const size_t _count = size_t(-1)) const
    {
        if (_count == 0 || m_ptr == 0)return str_base();
        str_base ret;
        toupperEx(ret, m_ptr->pData, m_ptr->len, _off, _count);
        ret.Addref();
        return ret;
    }

    // 把当前字符串转成大写, _off=起始位置, _count=转换的字符数, 返回替换的字符数
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回0
    inline int toupperEx(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_count == 0 || m_ptr == 0)return 0;
        return toupperEx(*this, m_ptr->pData, m_ptr->len, _off, _count);
    }
    // 文本倒序, _off=起始位置, _count=转换的字符数, ansi版也是字符数, ansi版在内部转成Unicode在转换, ansi版不建议使用
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回false
    inline bool reverse(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_count == 0 || m_ptr == 0)return 0;
        return reverseEx(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // 判断当前文本指定位置和数量的文本是否为数字, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline bool isNumber(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isNumber(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // 判断当前文本指定位置和数量的文本是否为小写字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline bool isLower(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isLower(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // 判断当前文本指定位置和数量的文本是否为大写字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline bool isUpper(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isUpper(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // 判断当前文本指定位置和数量的文本是否为字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline bool isLetter(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isLetter(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // 分割字符串, 返回成员数
    // arr = 接收分割结果指针, 可以为NULL
    // _substr = 用作分割的字符串, 为空则按换行 "\r\n"进行分割
    // _count = 要返回的子文本成员数, 为0则返回不进行操作
    inline size_t split(strArr<value_type>* arr, const_pointer _substr, const size_t _count = size_t(-1))
    {
        if (!m_ptr) return 0;
        return strtok(m_ptr->pData, arr, _substr, _count);
    }

    // 分割字符串, 返回成员数
    // arr = 接收分割结果指针, 可以为NULL
    // _substr = 用作分割的字符串, 为空则按换行 "\r\n"进行分割
    // _count = 要返回的子文本成员数, 为0则返回不进行操作
    inline size_t strtok(strArr<value_type>* arr, const_pointer _substr, const size_t _count = size_t(-1))
    {
        if (!m_ptr) return 0;
        return strtok(m_ptr->pData, arr, _substr, _count);
    }
    // 文本比较, 相等返回0, 小于返回负数, 大于返回正数
    // _dst    = 被比较的文本
    // _start    = 开始比较的位置, 越界从0开始
    // _count    = 比较的字符数,Unicode版为字符, 多字节版为字节, 为0则以\0位结束标志
    // isCase    = 是否区分大小写, true = 区分, false = 不区分
    inline int compare(const str_base& s2, const size_t _start = 0, const size_t _len = 0, bool isCase = false)const
    {
        return compare(m_ptr ? m_ptr->pData : 0, s2.c_str(), _start, _len, isCase);
    }

    // 子文本比较, 相等返回0, 小于返回负数, 大于返回正数
    // _dst    = 被比较的文本
    // _start    = 开始比较的位置, 越界从0开始
    // _count    = 被比较文本的字符数,Unicode版为字符, 多字节版为字节, 为0则以\0位结束标志
    // isCase    = 是否区分大小写, true = 区分, false = 不区分
    inline int compare(const_pointer s2, const size_t _start = 0, const size_t _len = 0, bool isCase = true)const
    {
        return compare(m_ptr ? m_ptr->pData : 0, s2, _start, _len, isCase);
    }
    inline static int compare(const_pointer s1, const_pointer s2, const size_t _start, const size_t _cmplen, bool isCase)
    {
        size_t len1 = 0;
        size_t len2 = 0;
        size_t cmpLen = _cmplen;
        if (s1)len1 = tstr_len(s1);
        if (s2)len2 = tstr_len(s2);

        if (len1 < _cmplen || len2 < _cmplen)   // 比较的文本长度不够, 哪个长返回哪个大
        {
            return len1 < len2 ? 1 : -1;
        }

        if (((s1 == 0 || s2 == 0)
            && len1 == 0 && len2 == 0)
            || s1 == s2) return 0;                  // 两个文本其中一个为0, 并且两个文本长度都是0, 返回相等, 或者两个指针一样
        if (s1 == 0 && s2 == 0)return 0;            // 两个文本都为空, 相等
        if (s1 == 0 && s2)return -1;                // 第一个文本小于第二个文本
        if (s1 && s2 == 0)return 1;                 // 第一个文本大于第二个文本

        // 走到这两个文本都不为空
        size_t max_len = len1 < len2 ? len1 : len2; // 最大比较长度, 取两个文本最短的一个

        //! 1. 先设置比较长度, 如果比较长度等于0, 或者大于最大文本长度, 则设置为最大文本长度
        if (cmpLen == 0)   cmpLen = max_len;
        if (cmpLen > max_len) cmpLen = max_len;     // 设置被比较文本长度

        //! 2. 在设置起始比较位置, 如果起始位置 + 比较长度 > 最大文本长度, 则设置起始位置为 最大长度 - 比较长度
        size_t start = _start;                      // 起始比较位置  
        if (start + cmpLen >= len1)                 // 起始位置 + 比较长度 > 文本1
            start = len1 - cmpLen;                  // 起始位置 = 文本1 - 比较长度

        //! 3. 设置两个被比较文本, 
        const_pointer p1 = s1 + start;
        const_pointer p2 = s2;

        if (isCase)    // 区分大小写
            return tstr_ncmp(p1, p2, cmpLen);
        return tstr_nicmp(p1, p2, cmpLen);
    }
    // 文本比较, 相等返回0, 小于返回负数, 大于返回正数
    // _dst    = 被比较的文本
    // isCase    = 是否区分大小写, true = 区分, false = 不区分
    inline int compare(const str_base& s2, bool isCase = false)const
    {
        return compare(m_ptr ? m_ptr->pData : 0, s2.c_str(), isCase);
    }
    // 文本比较, 相等返回0, 小于返回负数, 大于返回正数
    // _dst    = 被比较的文本
    // isCase    = 是否区分大小写, true = 区分, false = 不区分
    inline int compare(const_pointer s2, bool isCase = false)const
    {
        return compare(m_ptr ? m_ptr->pData : 0, s2, isCase);
    }
    inline static int compare(const_pointer s1, const_pointer s2, bool isCase)
    {
        size_t len1 = 0;
        size_t len2 = 0;
        if (s1)len1 = tstr_len(s1);
        if (s2)len2 = tstr_len(s2);

        if (((s1 == 0 || s2 == 0)
            && len1 == 0 && len2 == 0)
            || s1 == s2) return 0;                  // 两个文本其中一个为0, 并且两个文本长度都是0, 返回相等, 或者两个指针一样
        if (s1 == 0 && s2 == 0)return 0;            // 两个文本都为空, 相等
        if (s1 == 0 && s2)return -1;                // 第一个文本小于第二个文本
        if (s1 && s2 == 0)return 1;                 // 第一个文本大于第二个文本

        // 走到这两个都不为空
        if (isCase)    // 区分大小写
            return tstr_cmp(s1, s2);
        return tstr_icmp(s1, s2);
    }
    //friend ostream& operator << (ostream &out  ,str_base & s)
    //{
    //    out << s.c_str();
    //    return out;
    //}
#pragma endregion
private:
    template<typename T>
    inline static str_base NumberToString_to_string(const_pointer format, T Val, bool isFloat)
    {
        str_base ret;
        ret.resize(50);
        int len = 0;
        if (sizeof(value_type) == 2)
            len = swprintf_api((LPWSTR)ret.data(), 50, (LPCWSTR)format, Val);
        else
            len = sprintf_api((LPSTR)ret.data(), 50, (LPCSTR)format, Val);
        ret.resize(len);
        if (isFloat)
        {
            while (len && ret[len - 1] == '0')
                ret.resize(--len);
            if (ret[len - 1] == '.')
                ret.resize(--len);
        }
        ret.Addref();   // 本方法析构释放一次, to_string 析构释放一次
        ret.Addref();   // 所以需要增加两次引用
        return ret;
    }
public:
    // BJ 本对象公开的方法,一些基本的字符串操作


    // 字符串交换
    inline void swap(str_base& s)
    {
        if (&s == this) return;
        LPSTRMEMORYDATA p = s.m_ptr;
        s.m_ptr = m_ptr;
        m_ptr = p;
    }

    // 文本数值互转
#pragma region _num_sring
    // 到双精度浮点数
    inline double stod()const       { return m_ptr ? stod(m_ptr->pData) : 0; }
    // 到单精度浮点数
    inline float stof()const        { return m_ptr ? stof(m_ptr->pData) : 0; }
    // 到长浮点型
    inline long double stold()const { return m_ptr ? stold(m_ptr->pData) : 0; }

    // 到整数 int
    inline int stoi()const          { return m_ptr ? stoi(m_ptr->pData) : 0; }

    // 到整数 long
    inline long stol()const         { return m_ptr ? stol(m_ptr->pData) : 0; }

    // 到长整数 long long
    inline __int64 stoll()const     { return m_ptr ? stoll(m_ptr->pData) : 0; }
    
    inline static str_base to_string(int Val)
    {
        const value_type format[] = { '%', 'd', '\0' };
        return NumberToString_to_string(format, Val, false);
    }
    inline static str_base to_string(unsigned int Val)
    {
        const value_type format[] = { '%', 'u', '\0' };
        return NumberToString_to_string(format, Val, false);
    }
    inline static str_base to_string(long Val)
    {
        const value_type format[] = { '%', 'l', 'd', '\0' };
        return NumberToString_to_string(format, Val, false);
    }
    inline static str_base to_string(unsigned long Val)
    {
        const value_type format[] = { '%', 'l', 'u', '\0' };
        return NumberToString_to_string(format, Val, false);
    }

    inline static str_base to_string(__int64 Val)
    {
        const value_type format[] = { '%', 'l', 'l', 'd', '\0' };
        return NumberToString_to_string(format, Val, false);
    }
    inline static str_base to_string(unsigned __int64 Val)
    {
        const value_type format[] = { '%', 'l', 'l', 'u', '\0' };
        return NumberToString_to_string(format, Val, false);
    }

    inline static str_base to_string(float Val)
    {
        const value_type format[] = { '%', 'f', '\0' };
        return NumberToString_to_string(format, Val, true);
    }
    inline static str_base to_string(double Val)
    {
        const value_type format[] = { '%', 'f', '\0' };
        return NumberToString_to_string(format, Val, true);
    }
    inline static str_base to_string(long double Val)
    {
        const value_type format[] = { '%', 'l', 'f', '\0' };
        return NumberToString_to_string(format, Val, true);
    }

#pragma endregion
    // 字符串是否为空, 字符串长度为0, 返回真, 成员函数等效于 size == 0
    inline bool empty()const { return (m_ptr == 0) || (m_ptr->len == 0); }

    // 清除字符串的所有元素, 不会释放字符串缓冲区, 会把字符串清除, 并赋值长度为0
    inline void clear()
    {
        if (!m_ptr) return;
        memset(m_ptr->pData, 0, m_ptr->bufferLen);
        //m_ptr->pData[0] = '\0';
        m_ptr->len = 0;
    }

public:
    // 字符串增删改查操作

    // 检查字符串是否以指定的字符开头
    // c = 要查找的单字符前缀
    // isCase = 是否区分大小写
    inline bool starts_with(value_type c, bool isCase = true) const
    {
        if (empty())return false;
        return starts_with(m_ptr->pData, c, isCase);
    }

    // 检查字符串是否以指定的字符开头
    // c = 以NULL结尾的字符串, 其中包含要查找的前缀
    // isCase = 是否区分大小写
    inline bool starts_with(const_pointer x, bool isCase = true) const
    {
        if (!x || !x[0] || empty())return false;
        size_t len = tstr_len(x);
        if (len > m_ptr->len)return false;  // 传入的字符串比本对象字符串还长, 那就一定不匹配

        if (!isCase)
        {
            return tstr_nicmp(m_ptr->pData, x, len) == 0;
        }
        return tstr_ncmp(m_ptr->pData, x, len) == 0;
    }

    // 检查字符串是否以指定的字符开头
    // c = 要查找的单字符前缀
    // isCase = 是否区分大小写
    inline static bool starts_with(const_pointer _string, value_type c, bool isCase = true)
    {
        if (!_string || !_string[0])return false;
        value_type ch = _string[0];
        if (!isCase)
        {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')   // 是字母, 需要转换比较
                c |= 32;
            if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')   // 是字母, 需要转换比较
                ch |= 32;
        }
        return ch == c;
    }

    // 检查字符串是否以指定的字符开头
    // c = 以NULL结尾的字符串, 其中包含要查找的前缀
    // isCase = 是否区分大小写
    inline static bool starts_with(const_pointer _string, const_pointer x, bool isCase = true)
    {
        if (!_string || !_string[0] || !x || !x[0])return false;
        const size_t strLen = tstr_len(_string);
        const size_t len = tstr_len(x);
        if (len > strLen)return false;  // 传入的字符串比本对象字符串还长, 那就一定不匹配

        if (!isCase)
        {
            return tstr_nicmp(_string, x, len) == 0;
        }
        return tstr_ncmp(_string, x, len) == 0;
    }

    // 检查字符串是否以指定的字符结尾
    // c = 要查找的单字符后缀
    // isCase = 是否区分大小写
    inline bool ends_with(value_type c, bool isCase = true) const
    {
        if (empty())return false;
        value_type ch = m_ptr->pData[m_ptr->len - 1];
        if (!isCase)
        {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')   // 是字母, 需要转换比较
                c |= 32;
            if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')   // 是字母, 需要转换比较
                ch |= 32;
        }
        return ch == c;
    }

    // 检查字符串是否以指定的字符串结尾
    // x = 以NULL结尾的字符串, 其中包含要查找的后缀
    // isCase = 是否区分大小写
    inline bool ends_with(const_pointer x, bool isCase = true) const
    {
        if (!x || !x[0] || empty())return false;
        size_t len = tstr_len(x);
        if (len > m_ptr->len)return false;  // 传入的字符串比本对象字符串还长, 那就一定不匹配

        const_pointer _start = m_ptr->pData + (m_ptr->len - len);
        if (!isCase)
        {
            return tstr_icmp(_start, x) == 0;
        }
        return tstr_cmp(_start, x) == 0;
    }

    // 检查字符串是否以指定的字符结尾
    // c = 要查找的单字符后缀
    // isCase = 是否区分大小写
    inline static bool ends_with(const_pointer _string, value_type c, bool isCase = true)
    {
        if (!_string || !_string[0])return false;
        size_t len = tstr_len(_string);
        value_type ch = _string[len - 1];

        if (!isCase)
        {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')   // 是字母, 需要转换比较
                c |= 32;
            if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')   // 是字母, 需要转换比较
                ch |= 32;
        }
        return ch == c;
    }

    // 检查字符串是否以指定的字符串结尾
    // x = 以NULL结尾的字符串, 其中包含要查找的后缀
    // isCase = 是否区分大小写
    inline static bool ends_with(const_pointer _string, const_pointer x, bool isCase = true)
    {
        if (!_string || !_string[0] || !x || !x[0])return false;
        size_t strLen = tstr_len(_string);
        size_t len = tstr_len(x);
        if (len > strLen)return false;  // 传入的字符串比本对象字符串还长, 那就一定不匹配

        const_pointer _start = _string + (strLen - len);
        if (!isCase)
        {
            return tstr_icmp(_start, x) == 0;
        }
        return tstr_cmp(_start, x) == 0;
    }

    // 查找, 删除, 替换, 取左边右边中间
#pragma region _find_erase_replace_left_right_
    // 查找字符, 返回找到位置, 没有找到返回str_base::npos
    // _off = 查找位置, 默认为最前面查找
    inline size_t find(const value_type _ch, const size_t _off = 0) const
    {
        if (empty())return npos;
        return find(m_ptr->pData, _ch, _off);
    }

    // 寻找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _substr    = 寻找的文本
    // _off    = 寻找的位置, 0 = 从头开始寻找
    // c    = 是否区分大小写,true=区分,false=不区分
    inline size_t find(const str_base& _substr, const size_t pos = 0, bool c = true)const
    {
        if (empty())return npos;
        return findEx(m_ptr->pData, _substr.c_str(), m_ptr->len, _substr.size(), pos, c);
    }

    // 寻找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _substr    = 寻找的文本
    // _off    = 寻找的位置, 0 = 从头开始寻找
    // c    = 是否区分大小写,true=区分,false=不区分
    inline size_t find(const_pointer _substr, const size_t pos, bool c = true)const
    {
        if (empty())return npos;
        return findEx(m_ptr->pData, _substr, m_ptr->len, tstr_len(_substr), pos, c);
    }
    // 寻找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _substr = 寻找的文本
    // _strlen = 寻找文本的长度, 为0则 _substr必须以\0结尾
    // _off    = 寻找的位置
    // c    = 是否区分大小写,true=区分,false=不区分
    inline size_t findEx(const_pointer _substr, const size_t _strlen, const size_t pos, bool c)const
    {
        if (empty())return npos;
        return findEx(m_ptr->pData, _substr, m_ptr->len, _strlen, pos, c);
    }

    // 倒找字符, 返回找到位置, 没有找到返回str_base::npos
    // _ch    = 查找的字符
    // _off = 查找位置, 默认为最后面查找
    inline size_t rfind(const value_type _ch, const size_t _off = size_t(-1))
    {
        if (empty())return npos;
        return rfind(m_ptr->pData, _ch, _off);
    }

    // 倒找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _substr = 寻找的文本
    // _off    = 寻找的位置, str_base::npos = 从结尾开始寻找
    // c    = 是否区分大小写,true=区分,false=不区分
    inline size_t rfind(const str_base& _substr, const size_t pos = size_t(-1), bool c = true)const
    {
        if (empty())return npos;
        return rfindEx(m_ptr->pData, _substr.c_str(), _substr.size(), pos, c);
    }
    // 倒找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _substr = 寻找的文本
    // _off    = 寻找的位置, str_base::npos = 从结尾开始寻找
    // isCase  = 是否区分大小写,true=区分,false=不区分
    inline size_t rfind(const_pointer _substr, const size_t pos = size_t(-1), bool isCase = true)const
    {
        if (empty())return npos;
        return rfindEx(m_ptr->pData, _substr, tstr_len(_substr), pos, isCase);
    }
    // 倒找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _substr = 寻找的文本
    // _strlen = 寻找文本的长度, 为0则 _substr必须以\0结尾
    // _off    = 寻找的位置, str_base::npos = 从结尾开始寻找
    // isCase  = 是否区分大小写,true=区分,false=不区分
    inline size_t rfindEx(const_pointer _substr, const size_t _strlen, const size_t pos, bool isCase)const
    {
        if (empty())return npos;
        return rfindEx(m_ptr->pData, _substr, _strlen, pos, isCase);
    }

    

    // 字符替换替换, 不会改变原有字符串长度, 如果修改为字符0, 内部字符串长度不会变
    // _ch = 被替换的字符串
    // _subch = 替换成
    // _off = 替换的起始位置,默认为0, 起始位置大于字符串长度时返回FALSSE
    // count = 替换次数, 为0则不操作
    inline bool replace(const value_type _ch, const value_type _subch, const size_t _off = 0, size_t count = size_t(-1))
    {
        if (!m_ptr || m_ptr->len == 0 || _ch == 0 || count == 0) return false;
        return replaceEx(*this, m_ptr->pData, _ch, _subch, _off, count);
    }

    // 子文本替换
    // s        = 被替换的字符串
    // sub      = 替换成
    // _off     = 替换的起始位置,默认为0
    // count    = 替换次数,<= 0 = 整数最大值
    // isCase   = 是否区分大小写
    inline bool replace(const str_base& s, const str_base& sub, const size_t pos = 0, const size_t count = size_t(-1), bool isCase = true)
    {
        if (!m_ptr || s.empty())return false;
        return replaceEx(*this, m_ptr->pData, s.c_str(), sub.c_str(), s.size(), sub.size(), pos, count, isCase);
    }

    // 子文本替换
    // _string  = 被替换的字符串
    // _substr  = 替换成
    // _off     = 替换的起始位置,默认为0
    // count    = 替换次数,<= 0 = 整数最大值
    // isCase   = 是否区分大小写
    inline bool replace(const_pointer _string, const_pointer _substr, const size_t _off = 0, size_t count = size_t(-1), bool isCase = true)
    {
        if (!m_ptr || !_string)return false;
        return replaceEx(*this, m_ptr->pData, _string, _substr, tstr_len(_string), 0, _off, count, isCase);
    }

    // 子文本替换
    // _string  = 被替换的字符串
    // _substr  = 替换成
    // _strlen  = _string的长度, 如果此值为0, 则_string必须为\0结尾
    // _sublen  = _substr的长度, 如果此值为0, 则_substr必须为\0结尾
    // _off     = 替换的起始位置,默认为0
    // count    = 替换次数,<= 0 = 整数最大值
    // isCase   = 是否区分大小写
    inline bool replaceEx(const_pointer _string, const_pointer _substr, const size_t _strlen, const size_t _sublen, const size_t _off, size_t count, bool isCase)
    {
        if (!m_ptr)return false;
        return replaceEx(*this, m_ptr->pData, _string, _substr, _strlen, _sublen, _off, count, isCase);
    }

    // 删除子文本
    // _off    = 起始位置
    // count = 删除字符数,多字节单位为字节,Unicode为字符, 0=从起始位置删除到结束
    inline str_base erase(const size_t _off, const size_t _count = size_t(-1))
    {
        str_base ret = erase(m_ptr->pData, _off, _count);
        ret.Addref();
        return ret;
    }
    // 删除子文本, 结果保存到本字符串里
    // _off    = 起始位置
    // count= 删除字符数,多字节单位为字节,Unicode为字符, 0=从起始位置删除到结束
    inline bool eraseEx(const size_t _off, const size_t _count = size_t(-1))
    {
        return eraseEx(*this, m_ptr->pData, _off, _count);
    }
    // 删除子文本
    // _str     = 被删除的文本
    // _off     = 起始位置
    // count    = 删除字符数,多字节单位为字节,Unicode为字符, 0=从起始位置删除到结束
    inline static str_base erase(const_pointer _str, const size_t _off, const size_t _count = size_t(-1))
    {
        str_base ret;
        eraseEx(ret, _str, _off, _count);
        ret.Addref();
        return ret;
    }
    // 删除子文本
    // ret      = 结果结果字符串
    // _str     = 被删除的文本
    // _off     = 起始位置
    // count    = 删除字符数,多字节单位为字节,Unicode为字符, 为0则不操作
    static bool eraseEx(str_base& ret, const_pointer _string, const size_t _off, const size_t _count = size_t(-1))
    {
        if (!_string || _count == 0)
            return false;
        size_t len = tstr_len(_string);
        if (_off >= len)
            return false;

        str_base_AutoFreePtr __freeptr;
        autoFree_copy(_string, ret.__get_this(), __freeptr);


        size_t count = _count;
        if (count > len)
            count = len - _off;         // 删除的长度

        size_t newLen = len - count;    // 总长度 - 被删除的长度 = 新文本长度

        ret.resize(newLen);
        if (_off)
            ret.assign(_string, _off);     // 先拷贝左边文本
        else ret.clear();   // 如果左边没有文本则清空字符串

        if (newLen - _off)
            ret.append(_string + _off + count, newLen - _off);   // 在拷贝右边
        ret.Addref();
        return true;
    }
    // 删除最后一个字符, 返回被删除的字符
    inline value_type pop_back()
    {
        if (!m_ptr || m_ptr->len == 0)return 0;
        value_type ret = m_ptr->pData[--m_ptr->len];
        m_ptr->pData[m_ptr->len] = 0;
        return ret;
    }
    // 添加一个字符到字符串末尾
    inline void push_back(const value_type _ch)
    {
        if (!m_ptr)return;
        if (m_ptr->len + 1 >= m_ptr->bufferLen)    // 缓冲区不够大
        {
            realloc(m_ptr->bufferLen + _STR_BUFFER_SIZE);
        }
        m_ptr->pData[m_ptr->len++] = _ch;
        m_ptr->pData[m_ptr->len] = 0;
    }

    // 往指定位置插入一段指定数量的字符, _count 为0则不操作
    // _off = 插入的位置, 从0开始, Unicode版单位为字符, 多字节版为字节, 越界则加入到末尾
    // _count = 插入的数量
    // _ch  = 插入的字符
    inline str_base& insert(const size_t _off, const size_t _count, const value_type _ch)
    {
        if (m_ptr == 0 || _off >= m_ptr->len)
            return append(_count, _ch);
        if (_count == 0)return *this;
        str_base_AutoFreePtr p(alloc(_count, _ch));
        return insert(_off, p, _count, 1);
    }
    // 往指定位置插入一段文本 _len为0时以\0为结束符
    // _off = 插入的位置, 从0开始, Unicode版单位为字符, 多字节版为字节, 越界则加入到末尾
    // _str = 要插入的字符串
    // _len = _ptr 字符串长度, 为0则必须以\0为结束标志
    // _count = 插入次数, 默认为1此, 为0时置为1
    inline str_base& insert(const size_t _off, const_pointer _str, const size_t _len = 0, const size_t _count = 1)
    {
        if (m_ptr == 0 || _off >= m_ptr->len) return append(_str, _len);
        size_t count = _count ? _count : 1;
        size_t len = _len ? _len : tstr_len(_str);
        size_t newLen = m_ptr->len + len * count;
        pointer p = 0;
        if (newLen >= m_ptr->bufferLen)    // 缓冲区不够大
            p = realloc(newLen + _STR_BUFFER_SIZE);
        else
            p = m_ptr->pData;
        
        size_t offset = _off;
        size_t i;

        if (m_ptr->len - _off)    // 还有数据才拷贝, 原字符串长度 - 增加的起始位置 > 0 表示后面还有数据
            memcpy(p + offset + len, p + _off, (m_ptr->len - _off) * sizeof(value_type));    // 在拷贝原字符串后面部分

        for (i = 0; i < count; i++)
        {
            memcpy(p + offset, _str, len * sizeof(value_type));        // 在把新文本拷贝进去
            offset += len;
        }

        m_ptr->len = newLen;
        return *this;
    }

    // 往指定位置插入一段指定数量的文本, _count 为0则不操作
    // _off = 插入的位置, 从0开始, Unicode版单位为字符, 多字节版为字节
    // _str = 要插入的字符串
    // _len = _str 字符串长度, 为0则加入整个 _str
    // _count = 插入次数, 默认为1此, 为0时置为1
    inline str_base& insert(const size_t _off, const str_base& _str, const size_t _len = 0, const size_t _count = 0)
    {
        return insert(_off, _str.c_str(), _len, _count);
    }

    // 插入一段重复文本到最后, _count为0则设置为1
    inline str_base& insert(const str_base& _str, const size_t _count = 1)
    {
        size_t count = (_count == 0 ? 1 : _count);
        return append(count, _str.c_str(), _str.size());
    }


    // 取文本左边
    // count    = 取出字符数,多字节单位为字节,Unicode为字符
    str_base left(const size_t _count)const
    {
        if (!m_ptr)return str_base();
        size_t newLen = (_count > m_ptr->len ? m_ptr->len : _count);
        str_base tmp;
        tmp.resize(newLen);
        pointer p = tmp.data();;
        memcpy(p, m_ptr->pData, newLen * sizeof(value_type));
        tmp.Addref();
        return tmp;
    }

    // 取文本左边,取指定字符串左边的文本串
    // _string = 取这个字符串左边的文本串,返回的文本串不包含该字符串
    // _off = 起始查找参数1的位置
    str_base left(const str_base& _string, const size_t _off = 0)const
    {
        str_base ret = left(_string.c_str(), _off);
        ret.Addref();
        return ret;
    }
    // 取文本左边,取指定字符串左边的文本串
    // _string = 取这个字符串左边的文本串,返回的文本串不包含该字符串
    // _off = 起始查找参数1的位置
    str_base left(const_pointer _string, const size_t _off = 0)const
    {
        size_t count = str_base::find(_string, _off);
        if (count == str_base::npos)return str_base();

        str_base ret = left(count);
        ret.Addref();
        return ret;
    }

    // 取文本右边
    // count    = 取出字符数,多字节单位为字节,Unicode为字符
    str_base right(const size_t _count)const
    {
        if (!m_ptr || _count == 0)return str_base();
        size_t count = _count;
        if (count > m_ptr->len) return *this;
        size_t newLen = count;

        str_base tmp;
        tmp.resize(newLen);
        pointer p = tmp.data();
        size_t pos = m_ptr->len - count;
        memcpy(p, m_ptr->pData + pos, count * sizeof(value_type));
        tmp.Addref();
        return tmp;
    }

    // 取文本右边,取指定字符串右边的文本串
    // s    = 取这个字符串右边的文本串,返回的文本串不包含该字符串
    // b    = 是否保留被查找字符串
    // _off    = 起始查找位置, 默认从最尾部查找, 0为从首部查找
    str_base right(const str_base& s, bool b = false, const size_t _off = size_t(-1))const
    {
        if (!m_ptr)return str_base();
        size_t pos = str_base::rfind(s, _off);
        //int count = str_base::find(s);
        if (pos == str_base::npos) return str_base();
        str_base ret = right(m_ptr->len - pos - (b ? 0 : s.size()));
        ret.Addref();
        return ret;
    }
    // 取文本右边,取指定字符串右边的文本串
    // s    = 取这个字符串右边的文本串,返回的文本串不包含该字符串
    // b    = 是否保留被查找字符串
    // _off    = 起始查找位置, 默认从最尾部查找, 0为从首部查找
    str_base right(const_pointer s, bool b = false, const size_t _off = size_t(-1))const
    {
        if (!m_ptr)return str_base();
        size_t len = tstr_len(s);
        size_t pos = str_base::rfind(s, _off);
        //int count = str_base::find(s);
        if (pos == str_base::npos)return str_base();
        str_base ret = right(m_ptr->len - pos - (b ? 0 : len));
        ret.Addref();
        return ret;
    }


    // 取文本中间
    // _off    = 起始取出位置
    // count    = 取出字符数,多字节版单位的是字节,Unicode取的是字符
    str_base substr(size_t pos, size_t count = size_t(-1))const
    {
        if (!m_ptr)return str_base();
        if (count > m_ptr->len)count = m_ptr->len;
        if (pos >= m_ptr->len)return str_base();
        if (pos + count > m_ptr->len) count = m_ptr->len - pos;
        size_t newLen = count;
        str_base tmp(m_ptr->pData + pos, newLen);
        tmp.Addref();
        return tmp;
    }

    // 取文本中间,提供两个字符串,取这两个字符串中间的文本,失败返回空文本
    // s1    = 前面的字符串,未找到这个字符串会返回空
    // s2    = 后面的字符串,未找到这个字符串会返回空
    // b     = 是否保留前后字符串
    str_base substr(const str_base& s1, const str_base& s2, const size_t _off = 0, bool b = false)const
    {
        size_t pos1 = find(s1, _off);        // 寻找第一个字符串
        if (pos1 == str_base::npos)return str_base();

        size_t pos2 = find(s2, pos1 + 1);    // 第二个位置从第一个找到的位置开始
        if (pos2 == str_base::npos)    // 起始位置或者结束位置没有找到, 返回空文本
        {
            return str_base();
        }
        if (pos2 - pos1 <= 0)return str_base();
        if (b)
        {
            str_base ret = substr(pos1, pos2 - pos1 + s2.size());
            ret.Addref();
            return ret;
        }

        pos1 += s1.size();        // 不保留前后字符串, 找到位置 + 前面字符串长度
        str_base ret = substr(pos1, pos2 - pos1);
        ret.Addref();
        return ret;
    }

    // 取文本中间,提供两个字符串,取这两个字符串中间的文本,失败返回空文本
    // s1    = 前面的字符串,未找到这个字符串会返回空
    // s2    = 后面的字符串,未找到这个字符串会返回空
    // b    = 是否保留前后字符串
    str_base substr(const_pointer s1, const_pointer s2, const size_t _off = 0, bool b = false)const
    {
        if (!s1 || !s1[0] || !s2 || !s2[0])return str_base();
        size_t pos1 = find(s1, _off);        // 寻找第一个字符串
        if (pos1 == str_base::npos)return str_base();

        size_t len1 = tstr_len(s1);
        size_t len2 = tstr_len(s2);

        size_t pos2 = find(s2, (size_t)pos1 + len1 + 1);    // 第二个位置从第一个找到的位置开始
        if (pos1 == str_base::npos || pos2 == str_base::npos)    // 起始位置或者结束位置没有找到, 返回空文本
        {
            return str_base();
        }
        if (pos2 - pos1 <= 0)return str_base();
        
        if (b)
        {
            str_base ret = substr(pos1, pos2 - pos1 + len2);
            ret.Addref();
            return ret;
        }

        pos1 += (int)len1;        // 不保留前后字符串, 找到位置 + 前面字符串长度
        str_base ret = substr(pos1, (size_t)pos2 - (size_t)pos1);
        ret.Addref();
        return ret;
    }

    // 删除全部指定字符, 默认为空格, 返回删除后的文本
    str_base TrimAll(const value_type _ch = ' ') const
    {
        if (!m_ptr || m_ptr->len == 0)return str_base();
        pointer pStr = m_ptr->pData;
        while (*pStr == _ch) // 循环从头开始每个字符判断是不是指定字符,因为已经确定m_str 这个字符串是\0结尾,所以不需要判断指针越界
            pStr++;        // 剩下的都是取出前面的指定字符,如果为0, 就是全部是指定字符
        size_t len = tstr_len(pStr);    // 这里是去掉了左边的指定字符
        size_t i;
        str_base tmp;
        tmp.resize(len);
        pointer p = tmp.data();
        int newLen = 0;
        for (i = 0; i < len; i++)    // 一个循环把不是指定字符的都加入到新文本里
        {
            if (pStr[i] != _ch)
            {
                p[newLen] = pStr[i];
                newLen++;
            }
        }

        tmp.resize(newLen);
        tmp.Addref();
        return tmp;
    }

    // 删首尾字符, 默认删除空格, 返回删除后的字符串,不会修改原字符串
    str_base trim(const value_type _ch = ' ')const
    {
        if (!m_ptr || m_ptr->len == 0)return str_base();
        pointer pStr = m_ptr->pData;

        while (*pStr == _ch) // 循环从头开始每个字符判断是不是空格,因为已经确定m_str 这个字符串是\0结尾,所以不需要判断指针越界
            pStr++;        // 剩下的都是取出前面的空格,如果为0, 就是全部是空格

        pointer p1 = pStr;

        size_t nLen = tstr_len(pStr);

        pStr = pStr + nLen - 1;    // 指向最后一个字符
        while (*pStr == _ch && pStr != p1)    // 判断指针越界,如果pStr == m_str , 那就是已经找到第一个字符了,跳出循环
            pStr--;

        if (pStr == p1 && *pStr == _ch)
            nLen = 0;    // 相等表示已经遍历到了第一个字符,并且第一个字符也是空格,那删完后就没字符了
        else
            nLen = pStr - p1 + 1;    // 找到位置的时候已经多减了一次,所以要+1
        str_base ret = str_base(p1, nLen);
        ret.Addref();
        return ret;
        //str_base str;
        //str = LTrim();
        //str = str.RTrim();
        //return str;
    }

    // 删首字符, 默认删除空格, 返回删除后的字符串,不会修改原字符串
    str_base LTrim(const value_type _ch = ' ')const
    {
        if (!m_ptr || m_ptr->len == 0)return str_base();
        pointer pStr = m_ptr->pData;

        while (*pStr == _ch) // 循环从头开始每个字符判断是不是空格,因为已经确定m_str 这个字符串是\0结尾,所以不需要判断指针越界
            pStr++;        // 剩下的都是取出前面的空格,如果为0, 就是全部是空格

        str_base ret = str_base(pStr);
        ret.Addref();
        return ret;
    }
    // 删尾字符, 默认删除空格, 返回删除后的字符串,不会修改原字符串
    str_base RTrim(const value_type _ch = ' ')const
    {
        if (!m_ptr || m_ptr->len == 0)return str_base();
        size_t nLen = m_ptr->len;
        if (m_ptr->len == 0)return str_base();

        pointer pStr = m_ptr->pData + m_ptr->len - 1;    // 指向最后一个字符
        while (*pStr == _ch && pStr != m_ptr->pData)    // 判断指针越界,如果pStr == m_str , 那就是已经找到第一个字符了,跳出循环
            pStr--;

        if (pStr == m_ptr->pData && *pStr == _ch)
            nLen = 0;    // 相等表示已经遍历到了第一个字符,并且第一个字符也是空格,那删完后就没字符了
        else
            nLen = pStr - m_ptr->pData + 1;    // 找到位置的时候已经多减了一次,所以要+1
        str_base ret = str_base(m_ptr->pData, nLen);
        ret.Addref();
        return ret;
    }
#pragma endregion


    // 随机字符, 文本出现次数
#pragma region _rand_static

    // 取文本出现次数
    // _sub = 出现的文本
    // _sublen = 文本长度, 如果此值留空, _string 必须是\0结尾
    // isCase = 是否区分大小写
    inline size_t GetStringCount(const_pointer _sub, const size_t _sublen = 0, bool isCase = true)
    {
        if (empty())return 0;
        return GetStringCount(m_ptr->pData, _sub, _sublen, isCase);
    }
    // 取文本出现次数, 此函数功能与 GetStringCount() 完全一样
    // _sub = 出现的文本
    // _sublen = 文本长度, 如果此值留空, _string 必须是\0结尾
    // isCase = 是否区分大小写
    inline size_t GetAppearCount(const_pointer _sub, const size_t _sublen = 0, bool isCase = true)const
    {
        if (empty())return 0;
        return GetStringCount(m_ptr->pData, _sub, _sublen, isCase);
    }

    // 取文本出现次数
    // _string = 源文本
    // _sub = 出现的文本
    // _sublen = 文本长度, 如果此值留空, _string 必须是\0结尾
    // isCase = 是否区分大小写
    static size_t GetStringCount(const_pointer _string, const_pointer _sub, const size_t _sublen = 0, bool isCase = true)
    {
        if (!_string || !_string[0])return 0;

        size_t len = _sublen;
        if (len == 0) len = tstr_len(_sub);

        size_t pos = findEx(_string, _sub, 0, len, 0, isCase);
        size_t n = 0;
        while (pos != str_base::npos)
        {
            n++;
            pos = findEx(_string, _sub, 0, len, pos + 1, isCase);
        }
        return n;
    }

    // 取文本出现次数, 此函数功能与 GetStringCount() 完全一样
    // _string = 源文本
    // _sub = 出现的文本
    // _sublen = 文本长度, 如果此值留空, _string 必须是\0结尾
    // isCase = 是否区分大小写
    static size_t GetAppearCount(const_pointer _string, const_pointer _sub, const size_t _sublen = 0, bool isCase = true)
    {
        return GetStringCount(_string, _sub, _sublen, isCase);
    }

    // 取随机中国汉字, 调用前需要调用srand()设置随机数种子
    static str_base randChinese(const size_t _count)
    {
        str_base str;
        if (_count == 0)return str;
        str.resize(_count * (2 / sizeof(value_type)));    // ansi版需要多一倍的字节

        LPBYTE p = (LPBYTE)str.data();
        for (size_t i = 0; i < _count; i++)
        {
            p[i * 2] = 0 - __rand(38, 80);
            p[i * 2 + 1] = 0 - __rand(38, 80);
        }
        str.Addref();
        return str;
    }
    // 取指定数量的随机字符, 不包含汉字, 包含特殊字符, 大小写字母, 数字,需要在外部调用 srand()
    // _mode = 获取模式, 1=数字, 2=小写字母, 4=大写字母, 8=特殊字符, 16=中国汉字(未实现), 32=忽略其他标志,返回随机字符(包括不可视字符)
    // 需要多个组合用位或或起来, 默认为1, 只返回数字
    static str_base randStr(const size_t _count, int _mode)
    {
        str_base str;
        str.resize(_count);
        pointer p = str.GetPtr();
        if ((_mode & 32) == 32)
        {
            for (size_t i = 0; i < _count; i++)
                p[i] = (char)rand();
            str.Addref();
            return str;
        }

        // 过滤可能传递过来的没有标志, 没有就设置为只取数字
        int tmp = 0;
        if (_mode & 1) tmp |= 1;
        if (_mode & 2) tmp |= 2;
        if (_mode & 4) tmp |= 4;
        if (_mode & 8) tmp |= 8;
        //if (_mode & 16) tmp |= 16;
        if (tmp == 0)  tmp = 1;
        _mode = tmp;
        value_type buffer[129] = { 0 };
        size_t bufferSize = 0;
        if (_mode & 1)
        {
            if (sizeof(value_type) == 2)
                memcpy(buffer, L"0123456789", 10 * sizeof(value_type));
            else
                memcpy(buffer, "0123456789", 10);
            bufferSize += 10;
        }
        if (_mode & 2)
        {
            if (sizeof(value_type) == 2)
                memcpy(buffer + bufferSize, L"abcdefghijklmnopqrstuvwxyz", 26 * sizeof(value_type));
            else
                memcpy(buffer + bufferSize, "abcdefghijklmnopqrstuvwxyz", 26);
            bufferSize += 26;
        }
        if (_mode & 4)
        {
            if (sizeof(value_type) == 2)
                memcpy(buffer + bufferSize, L"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26 * sizeof(value_type));
            else
                memcpy(buffer + bufferSize, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26);
            bufferSize += 26;
        }
        if (_mode & 8)
        {
            if (sizeof(value_type) == 2)
                memcpy(buffer + bufferSize, L" !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", 33 * sizeof(value_type));
            else
                memcpy(buffer + bufferSize, " !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", 33);
            bufferSize += 33;
        }
        bufferSize--;
        for (size_t i = 0; i < _count; i++)
        {
            int r = __rand(0, (int)(DWORD)(LONG_PTR)bufferSize);
            p[i] = buffer[r];
        }
        str.Addref();
        return str;
    }


    // 取个随机数转成文本, 取指定范围内的数字, 范围最大值为 max - min = 32767, 调用前需要调用srand()设置随机数种子
    // min = 随机数字最小值
    // max = 随机数字最大值
    static str_base randNumber(const int min = 0, const int max = 0)
    {
        str_base str;
        size_t _count = 20;
        const value_type tmpStr[] = { '%','d','\0' };
        str.Format(20, tmpStr, __rand(min, max));
        str.Addref();
        return str;
    }
    // 取随机数字, 取指定范围内的数字, 范围最大值为 max - min = 32767, 不指定范围则给min和max赋值为0, 不指定范围数值不受限制, 指定范围限制在整数范围内
    // 调用前需要调用 srand() 设置随机数种子
    // _count = 取出数量
    // mode = 选择模式, 0=单双, 1=单, 其他=双
    // min = 随机数字最小值
    // max = 随机数字最大值
    static str_base randNumber(const size_t _count, const int mode = 0, const int min = 0, const int max = 0)
    {
        str_base str;
        str.resize(_count);
        pointer p = str.GetPtr();
        for (size_t i = 0; i < _count; i++)
        {
            switch (mode)
            {
            case 0:
                p[i] = __rand(i == 0 ? '1' : '0', '9');
                break;
            case 1:
                switch (__rand(1, 5))
                {
                case 1:    p[i] = '1'; break;
                case 2:    p[i] = '3'; break;
                case 3:    p[i] = '5'; break;
                case 4:    p[i] = '7'; break;
                default:   p[i] = '9'; break;
                }
                break;
            default:
                switch (__rand(1, 5))
                {
                case 1:    p[i] = '0'; break;
                case 2:    p[i] = '2'; break;
                case 3:    p[i] = '4'; break;
                case 4:    p[i] = '6'; break;
                default:   p[i] = '8'; break;
                }
                break;
            }
        }

        if (!(max == min && max == 0))
        {
            int number = str.stoi();
            number = (number % (max - min + 1)) + min;
            const value_type tmpStr[] = { '%','d','\0' };
            str.Format(20, tmpStr, number);
        }
        str.Addref();
        return str;
    }

    // 取随机姓氏, 调用前需要调用srand()设置随机数种子
    static str_base randSurname()
    {
#define _var_bjx_str_l(quote) L##quote      // r_winnt
#define _var_bjx_str    "赵钱孙李" "周吴郑王" "冯陈褚卫" "蒋沈韩杨" "朱秦尤许" "何吕施张" "孔曹严华"\
                        "金魏陶姜" "戚谢邹喻" "柏水窦章" "云苏潘葛" "奚范彭郎" "鲁韦昌马" "苗凤花方"\
                        "俞任袁柳" "酆鲍史唐" "费廉岑薛" "雷贺倪汤" "滕殷罗毕" "郝邬安常" "乐于时傅"\
                        "皮卞齐康" "伍余元卜" "顾孟平黄" "和穆萧尹" "姚邵湛汪" "祁毛禹狄" "米贝明臧"\
                        "计伏成戴" "谈宋茅庞" "熊纪舒屈" "项祝董梁" "杜阮蓝闵" "席季麻强" "贾路娄危"\
                        "江童颜郭" "梅盛林刁" "钟徐邱骆" "高夏蔡田" "樊胡凌霍" "虞万支柯" "昝管卢莫"\
                        "柯房裘缪" "干解应宗" "丁宣贲邓" "郁单杭洪" "包诸左石" "崔吉钮龚" "程嵇邢滑"\
                        "裴陆荣翁" "荀羊于惠" "甄曲家封" "芮羿储靳" "汲邴糜松" "井段富巫" "乌焦巴弓"\
                        "牧隗山谷" "车侯宓蓬" "全郗班仰" "秋仲伊宫" "宁仇栾暴" "甘钭历戎" "祖武符刘"\
                        "景詹束龙" "叶幸司韶" "郜黎蓟溥" "印宿白怀" "蒲邰从鄂" "索咸籍赖" "卓蔺屠蒙"\
                        "池乔阳郁" "胥能苍双" "闻莘党翟" "谭贡劳逄" "姬申扶堵" "冉宰郦雍" "却璩桑桂"\
                        "濮牛寿通" "边扈燕冀" "浦尚农温" "别庄晏柴" "瞿阎充慕" "连茹习宦" "艾鱼容向"\
                        "古易慎戈" "廖庾终暨" "居衡步都" "耿满弘匡" "国文寇广" "禄阙东欧" "殳沃利蔚"\
                        "越夔隆师" "巩厍聂晁" "勾敖融冷" "訾辛阚那" "简饶空曾" "毋沙乜养" "鞠须丰巢"\
                        "关蒯相查" "后荆红游" "竺权逮盍" "益桓公"

#define _var_bjx(_s) const LPCWSTR bjxW = _var_bjx_str_l(_s); const LPCSTR bjxA = _s
        _var_bjx(_var_bjx_str);
        int r = __rand(0, 406);
        str_base str(2);
        if (sizeof(value_type) == 2)
        {
            str[0] = bjxW[r];
            str.resize(1);
        }
        else
        {
            str.resize(2);
            str[0] = bjxA[r * 2];
            str[1] = bjxA[r * 2 + 1];
        }
        str.Addref();
        return str;
    }


#pragma endregion


    // 编码转换, 从本字符串里转换成其他编码
#pragma region _a2w_w2a_a2u_u2a_u2w_w2u
    // 转换字符串, 原始字符不是Unicode则 返回空文本
    str_base<char> w2a(int cp = 936)const
    {
        if (!m_ptr || sizeof(value_type) == 1)return str_base<char>();
        LPSTR p = UnicodeToAnsi((LPWSTR)m_ptr->pData, m_ptr->len, cp);
        str_base<char> sz(p, lstrlenA(p));
        delete[] p;
        sz.Addref();
        return sz;
    }
    // 转换字符串, 原始字符不是Unicode则 返回空文本
    str_base<char> w2u(int cp = CP_UTF8)const
    {
        if (!m_ptr || sizeof(value_type) == 1)return str_base<char>();
        LPSTR p = UnicodeToAnsi((LPWSTR)m_ptr->pData, m_ptr->len, cp);
        str_base<char> sz(p, lstrlenA(p));
        delete[] p;
        sz.Addref();
        return sz;
    }
    // 转换字符串, 原始字符是Unicode则 返回空文本
    str_base<wchar_t> a2w(int cp = 936)const
    {
        if (!m_ptr || sizeof(value_type) == 2)return str_base<wchar_t>();
        LPWSTR p = AnsiToUnicode((LPSTR)m_ptr->pData, m_ptr->len, cp);
        str_base<wchar_t> sz(p, lstrlenW(p));
        delete[] p;
        sz.Addref();
        return sz;
    }

    // 转换字符串, 原始字符是Unicode则 返回空文本
    str_base<wchar_t> u2w(int cp = CP_UTF8)const
    {
        if (!m_ptr || sizeof(value_type) == 2)return str_base<wchar_t>();
        LPWSTR p = AnsiToUnicode((LPSTR)m_ptr->pData, m_ptr->len, cp);
        str_base<wchar_t> sz(p, lstrlenW(p));
        delete[] p;
        sz.Addref();
        return sz;
    }


#pragma endregion

public:


    // 取当前字符串长度,不包含结束标志
    inline size_t size()const           { return m_ptr ? m_ptr->len : 0; }
    // 取当前字符串缓冲区长度, 以字符为单位
    inline size_t bufSize()const        { return m_ptr ? m_ptr->bufferLen : 0; }
    // 取当前字符串长度,不包含结束标志, 此成员函数与size()相同
    inline size_t length()const         { return m_ptr ? m_ptr->len : 0; }
    // 取当前字符串的地址,返回的地址只可读,不可写
    inline const_pointer c_str()const   { return m_ptr ? m_ptr->pData : 0; }
    // 获取当前字符串可以修改的地址
    inline pointer GetPtr()const        { return m_ptr ? m_ptr->pData : 0; }
    // 获取当前字符串可以修改的地址
    inline pointer data()const          { return m_ptr ? m_ptr->pData : 0; }
    // 获取当前字符串结尾地址, 指向结束字符, 如果字符串为空, 则返回0
    inline const_pointer rdata()const   { return m_ptr ? m_ptr->pData + m_ptr->len : 0; }
    // 获取当前字符串结尾地址, 指向结束字符, 如果字符串为空, 则返回0
    inline const_pointer rc_str()const  { return rdata(); }



    // 将字符串拷贝到一个新的内存空间,需要自己调用本对象的free()释放, 如果起始位置大于长度则起始位置置为0, 当前字符串未初始化时返回0
    // _off = 起始复制位置
    // _count = 复制的字符数, ansi版为字节数
    inline pointer copy(const size_t _off = 0, const size_t _count = size_t(-1))const
    {
        if (!m_ptr)return 0;
        size_t pos = _off;
        size_t len = _count;
        if (len > m_ptr->len) len = m_ptr->len;
        if (pos >= m_ptr->len)pos = 0;
        if (len + pos > m_ptr->len)len = m_ptr->len - pos;

        pointer p = alloc(len);
        memcpy(p, m_ptr->pData + pos, len * sizeof(value_type));
        return p;
    }

    // 增加一次引用计数, 成功返回引用计数, 失败返回0, 未初始化返回0
    // 不知道用途不建议使用该函数, 增加后必须释放两次才能成功释放该字符串, 不释放两次就泄漏了
    // 一般在返回这个字符串时增加一次引用, 这样函数释放时这个字符串不会被释放, 减少一次申请和释放的操作
    // 只要调用了这个方法, 那么这个对象复制给任意一个对象时, 都只是浅层复制
    inline DWORD Addref()
    {
        if (!m_ptr) return 0;
        return ++m_ptr->Addref;
    }
    inline DWORD Release()
    {
        if (m_ptr)
        {
            DWORD ret = --m_ptr->Addref;
            if (ret == 0)
            {
                free(m_ptr);
                m_ptr = 0;
            }
            return ret;
        }
        return 0;
    }
    // 附加指针, 析构时不会释放该指针, 如果需要释放则调用 obj.free()
    // 只能附加本类.data(), GetPtr() 返回的值, 附加其他值会崩溃
    // 返回原字符串数据, 可以调用 Attach() 进行附加, 如果原字符串为空, 则返回0
    // 会增加一次引用计数
    inline pointer Attach(pointer ptr)
    {
        pointer ret = 0;
        if (m_ptr)
            ret = m_ptr->pData;
        if (!ptr)
        {
            m_ptr = 0;
            return ret;
        }
        LPSTRMEMORYDATA p = (LPSTRMEMORYDATA)(((LPBYTE)ptr) - sizeof(STRMEMORYDATA));
        p->Addref++;
        m_ptr = p;
        return ret;
    }

    // 申请指定字符串缓冲区, 会增加一个结束标志,长度只需要输入字符串实际长度就可以了
    // 不使用时必须调用本对象的 free() 释放
    inline static pointer alloc(size_t size, value_type fill = 0)
    {
        if (size == 0) size = 1;
        size_t len = size + 1;
        for (;;)
        {
            size_t bufSize = len * sizeof(value_type);
            pointer p = (pointer)malloc(bufSize);
            if (p)
            {
                memset(p, 0, bufSize);
                if (fill)
                {
                    size_t i;
                    for (i = 0; i < size; i++)
                    {
                        p[i] = fill;
                    }
                }
                return p;
            }
#if _MSC_VER > 1200
            if (_callnewh(len) == 0)
            {
                if (len == SIZE_MAX)
                    throw std::bad_array_new_length{};
                else
                    throw std::bad_alloc{};
            }
#else
            return 0;
#endif
        }

        
    }
private:

    // 内部使用, 取字符串长度, 重新分配缓冲区, 分割, 格式化, 比较

#pragma region __inside_static_private
    // 内部使用, 直接修改 m_ptr
    // 重新分配STRMEMORYDATA::m_str结构内存, 新内存会拷贝原内存的数据, 调用后不会修改字符串长度
    // 会给缓冲区新尺寸赋值
    // 原对象字符串为空时新申请内存
    // 原对象字符串不为空时根据缓冲区长度来决定要不要重新分配大小
    // size = 新的文本缓冲区大小, 调用后会修改当前字符串缓冲区大小, 字符串长度不改变
    // isClear = 是否清除内存数据, 此参数为 true时会把字符串长度修改为0
    pointer realloc(size_t size, bool isClear = false)
    {
        size_t len = size + 1 + sizeof(STRMEMORYDATA);
        LPSTRMEMORYDATA pData = 0;
        if (m_ptr == 0)        // 原字符串是空的, 新申请数据
        {
            pData = (LPSTRMEMORYDATA)alloc(len);
            pData->Addref = 1;
            pData->bufferLen = size + 1;
            //pData->len = size;
            pData->pData = (pointer)(((LPBYTE)pData) + sizeof(STRMEMORYDATA));
            m_ptr = pData;
        }
        else if (size + 1 <= m_ptr->bufferLen)  // 原数据不为空, 判断缓冲区长度, 如果新缓冲区长度比旧缓冲区长度小, 不重新申请
        {
            // 不修改字符串长度
            //if (m_ptr->len < size)
            //    m_ptr->len = size;              // 原字符串长度小于当前新申请的字节, 设置为新申请的长度
            if (isClear) clear();
        }
        else
        {
            pData = (LPSTRMEMORYDATA)alloc(len);
            pData->Addref = 1;
            if (!isClear)       // 不清除内存时把原来的数据拷贝到新数据中
                memcpy(pData, m_ptr, (m_ptr->bufferLen + sizeof(STRMEMORYDATA)) * sizeof(value_type));

            pData->pData = (pointer)(((LPBYTE)pData) + sizeof(STRMEMORYDATA));

            free(m_ptr);
            m_ptr = pData;    // 释放原地址, 并重新赋值
            m_ptr->bufferLen = size + 1;    // 新缓冲区大小
        }
       
        return m_ptr->pData;
    }


    inline static DWORD __FormatMessage(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId, LPWSTR lpBuffer, DWORD nSize, va_list* Arguments) {
        return FormatMessageW(dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments);
    }

    inline static DWORD __FormatMessage(DWORD dwFlags, LPCVOID lpSource, DWORD dwMessageId, DWORD dwLanguageId, LPSTR lpBuffer, DWORD nSize, va_list* Arguments) {
        return FormatMessageA(dwFlags, lpSource, dwMessageId, dwLanguageId, lpBuffer, nSize, Arguments);
    }

    inline static HMODULE __GetModuleHandle(LPCWSTR lpModuleName) {
        return GetModuleHandleW(lpModuleName);
    }

    inline static HMODULE __GetModuleHandle(LPCSTR lpModuleName) {
        return GetModuleHandleA(lpModuleName);
    }

    inline static HMODULE __LoadLibrary(LPCWSTR lpLibFileName) {
        return LoadLibraryW(lpLibFileName);
    }

    inline static HMODULE __LoadLibrary(LPCSTR lpLibFileName) {
        return LoadLibraryA(lpLibFileName);
    }
    


#pragma endregion
public:
    // Unicode转ansi, 返回的结果需要调用 delete[] 释放
    inline static char* UnicodeToAnsi(const wchar_t* const unicode, size_t len = 0, int cp = 936)
    {
        return charset::UnicodeToAnsi(unicode, len, cp);
    }

    // ansi转Unicode, 返回的结果需要调用 delete[] 释放
    inline static wchar_t* AnsiToUnicode(const char* const ansi, size_t len = 0, int cp = 936)
    {
        return charset::AnsiToUnicode(ansi, len, cp);
    }

    // unicode转UTF8, 返回的结果需要调用 delete[] 释放
    inline static char* UnicodeToUtf8(const wchar_t* const unicode, size_t len = 0)
    {
        return charset::UnicodeToUtf8(unicode, len);
    }

    // UTF8转unicode, 返回的结果需要调用 delete[] 释放
    inline static wchar_t* Utf8ToUnicode(const char* const utf8, size_t len = 0)
    {
        return charset::Utf8ToUnicode(utf8, len);
    }

    // UTF8转ansi, 返回的结果需要调用 delete[] 释放
    inline static char* Utf8ToAnsi(const char* const utf8, size_t len = 0)
    {
        return charset::Utf8ToAnsi(utf8, len);
    }

    // ansi转UTF8, 返回的结果需要调用 delete[] 释放
    inline static char* AnsiToUtf8(const char* const ansi, size_t len = 0)
    {
        return charset::AnsiToUtf8(ansi, len);
    }

    // Unicode转ansi
    inline static str_base<char> (W2A)(LPCWSTR str, int len = 0, int cp = 936)
    {
        if (!str)return str_base<char>();
        if (len <= 0)len = (int)wcslen(str);
        if (len <= 0)return str_base<char>();
        int aLen = WideCharToMultiByte(cp, 0, str, (int)len, 0, 0, 0, 0) + 1;
        if (aLen < 1) return str_base<char>();

        str_base<char> ret;
        ret.resize(aLen);
        LPSTR szStr = ret.data();
        memset(szStr, 0, aLen);
        aLen = WideCharToMultiByte(cp, 0, str, (int)len, szStr, aLen, 0, 0);
        ret.resize(aLen);
        ret.Addref();
        return ret;
    }

    // ansi转Unicode
    inline static str_base<wchar_t> (A2W)(LPCSTR str, int len = 0, int cp = 936)
    {
        if (!str)return str_base<wchar_t>();
        if (len <= 0)len = (int)strlen(str);
        if (len <= 0)return str_base<wchar_t>();

        int uLen = MultiByteToWideChar(cp, 0, str, (int)len, NULL, 0) + 1;
        if (uLen < 1) return str_base<wchar_t>();

        str_base<wchar_t> ret;
        ret.resize(uLen);
        LPWSTR wzStr = ret.data();
        memset(wzStr, 0, uLen * sizeof(WCHAR));
        uLen = MultiByteToWideChar(cp, 0, str, (int)len, wzStr, uLen);
        ret.resize(uLen);
        ret.Addref();
        return ret;
    }
    // ansi转UTF-8
    inline static str_base<char> (A2U)(LPCSTR str, int len = 0)
    {
        str_base<wchar_t> ws = (A2W)(str, len);
        str_base<char>ret = (W2A)(ws.c_str(), len, CP_UTF8);
        ret.Addref();
        return ret;
    }
    // UTF-8转ansi
    inline static str_base<char> (U2A)(LPCSTR str, int len = 0)
    {
        str_base<wchar_t> ws = (A2W)(str, len, CP_UTF8);
        str_base<char>ret = (W2A)(ws.c_str(), len);
        ret.Addref();
        return ret;
    }
    // UTF-8转Unicode
    inline static str_base<wchar_t> (U2W)(LPCSTR str, int len = 0)
    {
        str_base<wchar_t>ret = (A2W)(str, len, CP_UTF8);
        ret.Addref();
        return ret;
    }
    // Unicode转UTF-8
    inline static str_base<char> (W2U)(LPCWSTR str, int len = 0)
    {
        str_base<char>ret = (W2A)(str, len, CP_UTF8);
        ret.Addref();
        return ret;
    }
    // ansi转OLE
    inline static str_base<wchar_t> (A2O)(LPCSTR str, int len = 0)
    {
        str_base<wchar_t>ret = (A2W)(str, len, CP_ACP);
        ret.Addref();
        return ret;
    }
    // OLE转ansi
    inline static str_base<char> (O2A)(LPCWSTR str, int len = 0)
    {
        str_base<char>ret = (W2A)(str, len, CP_ACP);
        ret.Addref();
        return ret;
    }
    // 把字符串转成小写, _off=起始位置, _count=转换的字符数, 返回替换的字符数
    // _string = 被转换的字符串
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static str_base tolower(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base ret = tolower(_string.c_str(), _string.size(), _off, _count);
        ret.Addref();
        return ret;
    }

    // 把字符串转成小写, _off=起始位置, _count=转换的字符数, 返回替换的字符数
    // _string = 被转换的字符串
    // _strlen = 被转换字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static str_base tolower(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base sRet;
        if (!_string || _count == 0)
            return sRet;
        tolowerEx(sRet, _string, _strlen, _off, _count);
        sRet.Addref();
        return sRet;
    }
    

    // 把字符串转成小写, _off=起始位置, _count=转换的字符数, 返回替换的字符数
    // _string = 被转换的字符串, 结果保存到这里
    // _strlen = 被转换字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static int tolowerEx(str_base& ret, const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (!_string || !_count)return 0;
        str_base_AutoFreePtr __freeptr;
        autoFree_copy(_string, ret.__get_this(), __freeptr);
        size_t len = _strlen;
        size_t strLen = tstr_len(_string);
        if (len == 0)
            len = strLen;
        ret.assign(_string);
        pointer pStr = ret.data();

        size_t pos = _off;
        if (pos > len)pos = 0;

        if (_count == 0 || _count < len)
        {
            len = _count;
        }
        if (pos + len > strLen)    // 起始位置+转换的字符数 > 总字符数
        {
            len = strLen - pos;
        }
        int n = 0;
        for (size_t i = pos; i < pos + len; i++)
        {
            if (pStr[i] >= 'A' && pStr[i] <= 'Z')
            {
                n++;
                pStr[i] |= 32;
            }
        }
        return n;
    }


    // 把当前字符串转成大写, _off=起始位置, _count=转换的字符数, 返回替换的字符数
    // _string = 被转换的字符串
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static str_base toupper(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base ret = toupper(_string.c_str(), _string.size(), _off, _count);
        ret.Addref();
        return ret;
    }
    // 把当前字符串转成大写, _off=起始位置, _count=转换的字符数, 返回替换的字符数
    // _string = 被转换的字符串
    // _strlen = 被转换字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static str_base toupper(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base sRet;
        if (_string == 0 || _count == 0)
            return sRet;
        toupperEx(sRet, _string, _strlen, _off, _count);
        sRet.Addref();
        return sRet;
    }

    // 把当前字符串转成大写, _off=起始位置, _count=转换的字符数, 返回替换的字符数
    // _string = 被转换的字符串, 结果保存到这里
    // _strlen = 被转换字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static int toupperEx(str_base& ret, const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_string == 0 || _count == 0)
            return 0;
        str_base_AutoFreePtr __freeptr;
        autoFree_copy(_string, ret.__get_this(), __freeptr);
        size_t len = _strlen;
        size_t strLen = tstr_len(_string);
        if (len == 0)len = strLen;
        ret.assign(_string, len);
        pointer pStr = ret.data();

        size_t pos = _off;
        if (pos > len)pos = 0;

        if (_count == 0 || _count < len)
        {
            len = _count;
        }
        if (pos + len > strLen)    // 起始位置+转换的字符数 > 总字符数
        {
            len = strLen - pos;
        }

        int n = 0;
        for (size_t i = pos; i < pos + len; i++)
        {
            if (pStr[i] >= 'a' && pStr[i] <= 'z')
            {
                n++;
                pStr[i] &= ~32;
            }
        }
        return n;
    }
    // 文本倒序, _off=起始位置, _count=转换的字符数, ansi版也是字符数, ansi版在内部转成Unicode在转换, ansi版不建议使用
    // _string = 被转换的字符串
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static str_base reverse(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base ret(_string);
        reverseEx(ret.data(), ret.size(), _off, _count);
        ret.Addref();
        return ret;
    }
    // 文本倒序, _off=起始位置, _count=转换的字符数, ansi版也是字符数, ansi版在内部转成Unicode在转换, ansi版不建议使用
    // _string = 被转换的字符串
    // _strlen = 被转换字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static str_base reverse(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base sRet;
        if (_string == 0 || _count == 0)return sRet;
        size_t strLen = tstr_len(_string);
        sRet.assign(_string, strLen);
        reverseEx(sRet.data(), _strlen, _off, _count);
        sRet.Addref();
        return sRet;
    }

    // 文本倒序, _off=起始位置, _count=转换的字符数, ansi版也是字符数, ansi版在内部转成Unicode在转换, ansi版不建议使用
    // _string = 被转换的字符串
    // _strlen = 被转换字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 转换的字符数, 默认为文本长度, 为0则返回空文本
    inline static bool reverseEx(pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_string == 0 || _count == 0)return false;

        size_t len = _strlen;
        size_t strLen = tstr_len(_string);
        if (len == 0)len = strLen;

        size_t pos = _off;
        if (pos > len)pos = 0;

        if (_count == 0 || _count < len)
        {
            len = _count;
        }
        if (pos + len > strLen)    // 起始位置+转换的字符数 > 总字符数
        {
            len = strLen - pos;
        }

        LPWSTR wzStr = 0;
        if (sizeof(value_type) == 1)
            wzStr = AnsiToUnicode((LPCSTR)_string, strLen, 936);
        else
            wzStr = (LPWSTR)_string;    // 是Unicode版, Unicode版直接操作传进来的字符串指针
        
        LPWSTR p = wzStr + pos;
        for (size_t i = 0; i < len / 2; i++)    // 倒序全部按Unicode来操作
        {
            size_t n = len - i - 1;
            p[i] ^= p[n];
            p[n] ^= p[i];
            p[i] ^= p[n];
        }

        if (sizeof(value_type) == 1)    // ansi版转完后需要转回来
        {
            LPSTR tmp = UnicodeToAnsi(wzStr, strLen);
            memcpy(_string, tmp, strlen(tmp) + 1);
            delete[] tmp;
        }
        return true;
    }

    // 判断当前文本指定位置和数量的文本是否为数字, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _string = 被查询的字符串
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline static bool isNumber(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isNumber(_string.c_str(), _string.size(), _off, _count);
    }
    // 判断当前文本指定位置和数量的文本是否为数字, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _string = 被查询的字符串
    // _strlen = 被查询字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline static bool isNumber(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base sRet;
        if (_string == 0 || _count == 0)return false;

        size_t len = _strlen;
        size_t strLen = tstr_len(_string);
        if (len == 0)len = strLen;
        if (len == 0)return false;

        size_t pos = _off;
        if (pos > len)pos = 0;

        if (_count == 0 || _count < len)
        {
            len = _count;
        }
        if (pos + len > strLen)    // 起始位置+转换的字符数 > 总字符数
        {
            len = strLen - pos;
        }
        for (size_t i = pos; i < pos + len; i++)
        {
            if (_string[i] < '0' || _string[i]>'9')
                return false;
        }
        return true;
    }

    // 判断当前文本指定位置和数量的文本是否为小写字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _string = 被查询的字符串
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline static bool isLower(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isLower(_string.c_str(), _string.size(), _off, _count);
    }
    // 判断当前文本指定位置和数量的文本是否为小写字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _string = 被查询的字符串
    // _strlen = 被查询字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline static bool isLower(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_string == 0 || _count == 0)return false;
        size_t len = _strlen;
        size_t strLen = tstr_len(_string);
        if (len == 0)len = strLen;
        if (len == 0)return false;

        size_t pos = _off;
        if (pos > len)pos = 0;

        if (_count == 0 || _count < len)
        {
            len = _count;
        }
        if (pos + len > strLen)    // 起始位置+转换的字符数 > 总字符数
        {
            len = strLen - pos;
        }
        for (size_t i = pos; i < pos + len; i++)
        {
            if (_string[i] < 'a' || _string[i]>'z')
                return false;
        }
        return true;
    }

    // 判断当前文本指定位置和数量的文本是否为大写字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _string = 被查询的字符串
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline static bool isUpper(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isUpper(_string.c_str(), _string.size(), _off, _count);
    }
    // 判断当前文本指定位置和数量的文本是否为大写字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _string = 被查询的字符串
    // _strlen = 被查询字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline static bool isUpper(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_string == 0 || _count == 0)return false;
        size_t len = _strlen;
        size_t strLen = tstr_len(_string);
        if (len == 0)len = strLen;
        if (len == 0)return false;

        size_t pos = _off;
        if (pos > len)pos = 0;

        if (_count == 0 || _count < len)
        {
            len = _count;
        }
        if (pos + len > strLen)    // 起始位置+转换的字符数 > 总字符数
        {
            len = strLen - pos;
        }
        for (size_t i = pos; i < pos + len; i++)
        {
            if (_string[i] < 'A' || _string[i]>'Z')
                return false;
        }
        return true;
    }

    // 判断当前文本指定位置和数量的文本是否为字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _string = 被查询的字符串
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline static bool isLetter(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isLetter(_string.c_str(), _string.size(), _off, _count);
    }
    // 判断当前文本指定位置和数量的文本是否为字母, _off=起始位置, _count=转换的字符数, ansi版为字节
    // _string = 被查询的字符串
    // _strlen = 被查询字符串长度, 如果此值为0, 那_string必须以\0为结尾
    // _off = 起始位置, 默认为0
    // _count = 查询的字符数, 默认为文本长度, 为0则返回false
    inline static bool isLetter(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_string == 0 || _count == 0)return false;
        size_t len = _strlen;
        size_t strLen = tstr_len(_string);
        if (len == 0)len = strLen;
        if (len == 0)return false;

        size_t pos = _off;
        if (pos > len)pos = 0;

        if (_count == 0 || _count < len)
        {
            len = _count;
        }
        if (pos + len > strLen)    // 起始位置+转换的字符数 > 总字符数
        {
            len = strLen - pos;
        }
        for (size_t i = pos; i < pos + len; i++)
        {
            if ((_string[i] < 'a' || _string[i] > 'z') && (_string[i] < 'A' || _string[i]>'Z'))
                return false;
        }
        return true;
    }

    // 分割字符串, 返回成员数
    // arr = 接收分割结果指针, 可以为NULL
    // _substr = 用作分割的字符串, 为空则按换行 "\r\n"进行分割
    // _count = 要返回的子文本成员数, 为0则返回不进行操作
    static size_t split(const_pointer str, strArr<value_type>* arr, const_pointer _substr, const size_t _count = size_t(-1))
    {
        return strtok(str, arr, _substr, _count);
    }

    // 分割字符串, 返回成员数
    // arr = 接收分割结果指针, 可以为NULL
    // _substr = 用作分割的字符串, 为空则按换行 "\r\n"进行分割
    // _count = 要返回的子文本成员数, 为0则返回不进行操作
    static size_t strtok(const_pointer str, strArr<value_type>* arr, const_pointer _substr, const size_t _count = size_t(-1))
    {
        if (_count == 0 || str == 0)return 0;
        if (!_substr)
        {
            const value_type tmp[3] = { '\r', '\n', '\0' };
            _substr = tmp;
        }
        size_t arrCount = tstr_len(str);

        LPSTRARRDATA p = new STRARRDATA;
        p->len = arrCount;
        p->arr = new size_t[arrCount];      // 申请存放分割结果的数组, 应该是足够用了, 逐字分割也够用了
        memset(p->arr, 0, arrCount * sizeof(size_t));
        p->str = copy(str);                 // 新缓冲区保存字符串
        size_t n = 0;                       // 已存放的成员数
        pointer next_token = 0;
        pointer ptr = tstr_tok<value_type>(p->str, _substr, &next_token);
        
        while (ptr)
        {
            if (n > arrCount - 1)
            {
                arrCount += p->len;
                size_t* tmpArr = new size_t[arrCount];    // 缓冲区不够大, 重新申请存放分割结果的数组
                memset(tmpArr, 0, arrCount * sizeof(size_t));
                delete[] p->arr;
                p->arr = tmpArr;
            }

            p->arr[n++] = ptr - p->str;     // 记录偏移, 到时候复制构造函数就容易复制了
            if (n >= _count)                // 返回成员数
                break;

            ptr = tstr_tok<value_type>(NULL, _substr, &next_token);
        }
        p->count = n;
        if (!arr)
        {
            if (p->arr)delete[] p->arr;
            if (p->str)delete[] p->str;
            delete p;
            p = 0;
            return n;
        }
        arr->free();
        arr->Attach(p);    // 由这个类进行释放操作
        return n;
    }

    // 复制指定字符串, 返回字符串地址, 此地址不能附加, 不适用时需要调用 free() 释放
    inline static pointer copy(const_pointer str, const size_t _size = 0)
    {
        size_t len = _size;
        if (len == 0)len = tstr_len(str);
        pointer p = alloc(len);
        memcpy(p, str, len * sizeof(value_type));
        return p;
    }
    // 释放由 copy 返回的字符串
    inline static void free(void* p)
    {
        if (p)
            ::free(p);
    }
    // 查找字符, 返回找到位置, 没有找到返回 str_base::npos
    // _off = 查找位置, 默认为最前面查找
    inline static size_t find(const_pointer _str, const value_type _ch, const size_t _off = 0)
    {
        if (!_str)return str_base::npos;
        size_t _strlen = tstr_len(_str);
        if (_off >= _strlen)return str_base::npos;
        size_t i, len = _strlen;

        for (i = _off; i < len; i++)
        {
            if (_str[i] == _ch)
                return i;
        }
        return str_base::npos;
    }

    // 寻找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回 str_base::npos
    // _substr    = 寻找的文本
    // _off    = 寻找的位置, str_base::npos = 从头开始寻找
    // _off    = 寻找的位置
    // isCase    = 是否区分大小写,true=区分,false=不区分
    inline static size_t find(const str_base& _str, const str_base& _substr, const size_t pos = 0, bool isCase = true)
    {
        return findEx(_str.c_str(), _substr.c_str(), _str.size(), _substr.size(), pos, isCase);
    }

    // 寻找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回 str_base::npos
    // _substr    = 寻找的文本
    // _off    = 寻找的位置, str_base::npos = 从头开始寻找
    // isCase    = 是否区分大小写,true=区分,false=不区分
    inline static size_t find(const_pointer _str, const_pointer _substr, const size_t pos, bool isCase = true)
    {
        return findEx(_str, _substr, tstr_len(_str), tstr_len(_substr), pos, isCase);
    }
    // 寻找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回 str_base::npos
    // _substr = 寻找的文本
    // _substrLen = 寻找文本的长度, 为0则 _substr必须以\0结尾
    // _off    = 寻找的位置
    // isCase    = 是否区分大小写,true=区分,false=不区分
    static size_t findEx(const_pointer _str, const_pointer _substr, const size_t _strLen, const size_t _substrLen, const size_t pos, bool isCase)
    {
        if (!_str)return str_base::npos;
        const size_t nArgStrLen = tstr_len(_str);
        const size_t nArgSubstrLen = tstr_len(_substr);

        const size_t nSubLen = _substrLen ? (_substrLen > nArgSubstrLen ? nArgSubstrLen : _substrLen) : nArgSubstrLen;
        const size_t nStrLen = _strLen ? (_strLen > nArgStrLen ? nArgStrLen : _strLen) : nArgStrLen;

        const_pointer pDst = _substr;
        if (nStrLen == 0 || nSubLen == 0 || nSubLen > nStrLen || pos >= nStrLen)return str_base::npos;

        size_t nStart = pos;
        size_t nEnd = nStrLen - nSubLen;

        if (nStart > (nEnd + 1))return str_base::npos;
        const_pointer pStart = _str + nStart;
        const_pointer pEnd = _str + nEnd;
        while (pStart <= pEnd)
        {
            bool bCmp;
            if (isCase)
                bCmp = tstr_ncmp(pStart, pDst, nSubLen) == 0;
            else
                bCmp = tstr_nicmp(pStart, pDst, nSubLen) == 0;
            if (bCmp)
            {
                nStart = pStart - _str;
                return nStart;
            }
            ++pStart;
        }
        return str_base::npos;
    }

    // 倒找字符, 返回找到位置, 没有找到返回str_base::npos
    // _off = 查找位置, 默认为最后面查找
    inline static size_t rfind(const_pointer _str, const value_type _ch, const size_t _off = size_t(-1))
    {
        size_t off = _off;
        if (!_str)return str_base::npos;
        size_t _strlen = tstr_len(_str);
        if (off >= _strlen)off = _strlen - 1;

        size_t nEnd = off;
        if (nEnd > _strlen) nEnd = _strlen - 1;
        int i;
        for (i = (int)nEnd; i >= 0; i--)
        {
            if (_str[i] == _ch) return i;
        }
        return str_base::npos;
    }

    // 倒找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _str    = 被寻找的文本
    // _substr = 寻找的文本
    // _off    = 寻找的位置, str_base::npos = 从结尾开始寻找
    // c    = 是否区分大小写,true=区分,false=不区分
    inline static size_t rfind(const_pointer _str, const str_base& _substr, const size_t pos = size_t(-1), bool c = true)
    {
        return rfindEx(_str, _substr.c_str(), _substr.size(), pos, c);
    }
    // 倒找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _substr = 寻找的文本
    // _off    = 寻找的位置, str_base::npos = 从结尾开始寻找
    // c    = 是否区分大小写,true=区分,false=不区分
    inline static size_t rfind(const_pointer _str, const_pointer _substr, const size_t pos = size_t(-1), bool c = true)
    {
        return rfindEx(_str, _substr, tstr_len(_substr), pos, c);
    }
    // 倒找字符串,从一个字符串中寻找一个字符串,成功返回找到位置,失败返回str_base::npos
    // _substr = 寻找的文本
    // _strlen = 寻找文本的长度, 为0则 _substr必须以\0结尾
    // _off    = 寻找的位置, str_base::npos = 从结尾开始寻找
    // c    = 是否区分大小写,true=区分,false=不区分
    static size_t rfindEx(const_pointer _str, const_pointer _substr, const size_t _strlen, const size_t pos, bool c)
    {
        if (!_str)return str_base::npos;
        size_t strLen = _strlen;
        if (strLen == 0)strLen = tstr_len(_substr);
        size_t len = tstr_len(_str);

        size_t nSubLen = strLen; // 要搜索的字符串长度
        if (len == 0 || nSubLen == 0 || nSubLen > len)return str_base::npos;

        size_t nStart = pos;    // 起始位置
        size_t nEnd = len - nSubLen; // 最后位置

        if (nStart > len) nStart = nEnd; //寻找的位置小于0则从最后寻找
        if (nStart > nEnd) nStart = nEnd;

        const_pointer pStart = _str + nStart; // 指向被搜索字符串的末尾

        while (pStart >= _str)    // 如果当前指向的位置大于字符串的起始位置,就循环判断
        {
            bool bCmp = 0;
            if (c) //区分大小写
                bCmp = tstr_ncmp(pStart, _substr, nSubLen) == 0;    // 区分大小写
            else
                bCmp = tstr_nicmp(pStart, _substr, nSubLen) == 0;    // 不区分大小写

            if (bCmp)
            {
                nStart = pStart - _str;    // 找到字符串,当前指向位置 - 字符串起始位置 = 找到位置
                return nStart;
            }
            pStart--;
        }
        return str_base::npos;        // 没找到返回 str_base::npos
    }


    // 取文本左边
    // str      = 源字符串
    // _strlen  = 字符串长度, 为了和非静态方法区分
    // count    = 取出字符数,多字节单位为字节,Unicode为字符
    inline static str_base left(const_pointer str, size_t _strlen, const size_t _count)
    {
        if (!str)return str_base();
        str_base ret;
        leftEx(ret, str, _strlen, _count);
        ret.Addref();
        return ret;
    }
    // 取文本左边
    // str      = 源字符串
    // _strlen  = 字符串长度, 为了和非静态方法区分
    // count    = 取出字符数,多字节单位为字节,Unicode为字符
    inline static bool leftEx(str_base& ret, const_pointer str, size_t _strlen, const size_t _count)
    {
        if (!str)
            return false;
        str_base_AutoFreePtr __freeptr;
        autoFree_copy(str, ret.__get_this(), __freeptr);
        _strlen = _strlen ? _strlen : tstr_len(str);
        size_t newLen = _count ? _count : _strlen;
        ret.resize(newLen);
        ret.assign(str, newLen);
        return true;
    }
    // 取文本左边,取指定字符串左边的文本串
    // str      = 源字符串
    // _string = 取这个字符串左边的文本串,返回的文本串不包含该字符串
    // _off = 起始查找参数1的位置
    inline static str_base left(const str_base& str, const str_base& _string, const size_t _off = 0)
    {
        str_base ret = left(str.c_str(), _string.c_str(), _off);
        ret.Addref();
        return ret;
    }
    // 取文本左边,取指定字符串左边的文本串
    // str      = 源字符串
    // _string  = 取这个字符串左边的文本串,返回的文本串不包含该字符串
    // _off     = 起始查找参数1的位置
    inline static str_base left(const_pointer str, const_pointer _string, const size_t _off = 0)
    {
        size_t count = str_base::find(str, _string, _off);
        if (count == str_base::npos)return str_base();

        str_base ret;
        leftEx(ret, str, 0, count);
        ret.Addref();
        return ret;
    }

    // 取文本右边
    // str      = 源字符串
    // count    = 取出字符数,多字节单位为字节,Unicode为字符
    inline static str_base right(const_pointer str, const size_t _count)
    {
        if (!str)return str_base();
        size_t _strLen = tstr_len(str);
        size_t count = _count;
        if (count > _strLen) return str;

        str_base ret;
        rightEx(ret, str, _count);
        ret.Addref();
        return ret;
    }
    // 取文本右边
    // ret      = 接收结果字符串
    // str      = 源字符串
    // count    = 取出字符数,多字节单位为字节,Unicode为字符
    inline static bool rightEx(str_base& ret, const_pointer str, const size_t _count)
    {
        if (!str)return false;
        str_base_AutoFreePtr __freeptr;
        autoFree_copy(str, ret.__get_this(), __freeptr);
        size_t _strLen = tstr_len(str);
        size_t count = _count;
        if (count > _strLen) return str;

        size_t pos = _strLen - count;
        ret.assign(str + pos, count);
        return true;
    }
    // 取文本右边,取指定字符串右边的文本串
    // s    = 取这个字符串右边的文本串,返回的文本串不包含该字符串
    // b    = 是否保留被查找字符串
    // _off = 起始查找位置, 默认从最尾部查找, 0为从首部查找
    inline static str_base right(const str_base& str, const str_base& s, bool b = false, const size_t _off = size_t(-1))
    {
        str_base ret = right(str.c_str(), s.c_str(), b, _off);
        ret.Addref();
        return ret;
    }
    // 取文本右边,取指定字符串右边的文本串
    // s    = 取这个字符串右边的文本串,返回的文本串不包含该字符串
    // b    = 是否保留被查找字符串
    // _off = 起始查找位置, 默认从最尾部查找, 0为从首部查找
    inline static str_base right(const_pointer str, const_pointer s, bool b = false, const size_t _off = size_t(-1))
    {
        if (!str || !s)return str_base();
        size_t len1 = tstr_len(str);
        size_t len2 = tstr_len(s);
        size_t pos = str_base::rfind(str, s, _off);
        //int count = str_base::find(s);
        if (pos == str_base::npos)return str_base();
        str_base ret = right(str, len1 - pos - (b ? 0 : len2));
        ret.Addref();
        return ret;
    }


    // 子文本替换
    // s    = 被替换的字符串
    // sub    = 替换成
    // _off    = 替换的起始位置,默认为0
    // count    = 替换次数,<= 0 = 整数最大值
    // c    = 是否区分大小写
    inline static str_base replace(const_pointer _str, const str_base& s, const str_base& sub, const size_t _off = 0, const size_t count = size_t(-1), bool c = true)
    {
        str_base ret;
        replaceEx(ret, _str, s.c_str(), sub.c_str(), s.size(), sub.size(), _off, count, c);
        ret.Addref();
        return ret;
    }

    // 字符替换, 不会改变原有字符串长度, 如果修改为字符0, 内部字符串长度不会变
    // _ch = 被替换的字符串
    // _subch = 替换成
    // _off = 替换的起始位置,默认为0, 起始位置大于字符串长度时返回FALSSE
    // count = 替换次数, 为0则不操作
    inline static str_base replace(const_pointer _str, const value_type _ch, const value_type _subch, const size_t _off = 0, size_t count = size_t(-1))
    {
        str_base ret;
        replaceEx(ret, _str, _ch, _subch, _off, count);
        ret.Addref();
        return ret;
    }
    // 字符替换, 不会改变原有字符串长度, 如果修改为字符0, 内部字符串长度不会变
    // ret      = 接收结果字符串
    // _ch      = 被替换的字符串
    // _subch   = 替换成
    // _off     = 替换的起始位置,默认为0, 起始位置大于字符串长度时返回FALSSE
    // count    = 替换次数, 为0则不操作
    inline static bool replaceEx(str_base& ret, const_pointer _str, const value_type _ch, const value_type _subch, const size_t _off = 0, size_t count = size_t(-1))
    {
        if (!_str)return false;
        size_t _dstLen = tstr_len(_str);
        if (_dstLen == 0 || _ch == 0 || count == 0) false;

        size_t pos = _off;
        if (pos >= _dstLen) return false;
        str_base_AutoFreePtr __freeptr;
        autoFree_copy(_str, ret.__get_this(), __freeptr);

        size_t len = count;
        if (len > _dstLen)len = _dstLen;
        ret.assign(_str, _dstLen);
        pointer p = ret.data();
        size_t i;
        for (i = pos; i < len; i++)
        {
            if (p[i] == _ch)
                p[i] = _subch;
        }
        return true;
    }
    // 子文本替换
    // _string = 被替换的字符串
    // _substr = 替换成
    // _off    = 替换的起始位置,默认为0
    // count    = 替换次数,<= 0 = 整数最大值
    // c    = 是否区分大小写
    inline static str_base replace(const_pointer _str, const_pointer _string, const_pointer _substr, const size_t _off = 0, size_t count = size_t(-1), bool c = true)
    {
        if (!_string)return str_base();
        size_t len = 0;
        if (_substr)
            len = tstr_len(_substr);
        str_base ret;
        replaceEx(ret, _str, _string, _substr, tstr_len(_string), len, _off, count, c);
        ret.Addref();
        return ret;
    }
    
    // 子文本替换
    // _string = 被替换的字符串
    // _substr = 替换成
    // _strlen = _string的长度, 如果此值为0, 则_string必须为\0结尾
    // _sublen = _substr的长度, 如果此值为0, 则_substr必须为\0结尾
    // _off    = 替换的起始位置,默认为0
    // count    = 替换次数,<= 0 = 整数最大值
    // c    = 是否区分大小写
    inline static str_base replace(const_pointer _str, const_pointer _string, const_pointer _substr, const size_t _strlen, const size_t _sublen, const size_t _off, size_t count, bool c)
    {
        str_base ret;
        replaceEx(ret, _str, _string, _substr, _strlen, _sublen, _off, count, c);
        ret.Addref();
        return ret;
    }

    // 子文本替换
    // ret      = 参考替换后的文本
    // _str     = 替换的源文本
    // _string  = 被替换的字符串
    // _substr  = 替换成
    // _strlen  = _string的长度, 如果此值为0, 则_string必须为\0结尾
    // _sublen  = _substr的长度, 如果此值为0, 则_substr必须为\0结尾
    // _off     = 替换的起始位置,默认为0
    // count    = 替换次数,<= 0 = 整数最大值
    // isCase   = 是否区分大小写
    static bool replaceEx(str_base& ret, const_pointer _str, const_pointer _string, const_pointer _substr, size_t _strlen, size_t _sublen, size_t _off, size_t count, bool isCase)
    {
        if (!_str || !_string)return false; // 源字符串和被替换的字符串都为空, 不处理

        size_t _destLen = tstr_len(_str);  // 源字符串字符串长度
        if (_destLen == 0) return false;    // 源文本为空

        size_t strLen = _strlen;            // 需要替换的文本长度
        if (strLen == 0)
            strLen = tstr_len(_string);
        if (strLen == 0) return false;      // 要替换的文本为空

        size_t subLen = _sublen;            // 替换成的文本长度, 替换成的文本可以为空, 为空代表删除
        if (subLen == 0 && _substr)
            subLen = tstr_len(_substr);


        size_t nStart = _off;               // 替换的起始位置
        size_t nRplCount = (count == 0) ? size_t(-1) : count;    // 替换次数

        size_t nEnd = _destLen - strLen;
        if (nStart > nEnd + 1 || nRplCount <= 0 || nStart < 0)    //寻找的文本长于开始寻找位置 或 没有替换次数
            return false;


        str_base_AutoFreePtr __freeptr;
        autoFree_copy(_str, ret.__get_this(), __freeptr);
        {
            size_t bufferLen = subLen - strLen; // 替换成的文本长度 - 用来替换的文本长度
            int cmpLen = (int)bufferLen;
            // 预测缓冲区长度, 最大为 字符串长度 * (替换成的文本长度 - 用来替换的文本长度), 这是最理想状态, 一定够存放
            if (cmpLen < 0)         bufferLen = _destLen;       // 最大需要的缓冲区大小为 被替换文本的长度, 最差的情况就是没有一个匹配, 替换后和原字符串一样长
            else if (cmpLen > 0)    bufferLen *= _destLen;      // 最理想长度, 就算每个字符都替换都足够存放
            else                    bufferLen = _destLen;       // 否则被替换的文本长度和替换成的文本长度一样, 替换后不会改变长度
            if (bufferLen > _destLen * 2 + _STR_BUFFER_SIZE)    // 为避免浪费内存, 做个限制, 并不是每个字符都会替换
                bufferLen = _destLen * 2 + _STR_BUFFER_SIZE;

            ret.realloc(bufferLen, true);
        }
        const_pointer pStart = _str + nStart;
        const_pointer pEnd = _str + nEnd;
        size_t nFind = 0;
        const_pointer pSrc = _str;

        while (pStart <= pEnd)
        {
            bool bCmp;
            if (isCase) bCmp = tstr_ncmp(pStart, _string, strLen) == 0;
            else        bCmp = tstr_nicmp(pStart, _string, strLen) == 0;

            if (bCmp)
            {
                size_t nStr = pStart - pSrc;
                if (nStr)
                    ret.append(pSrc, nStr);
                if (_substr && subLen > 0)    // 加入替换的文本
                    ret.append(_substr, subLen);

                pStart += strLen;
                pSrc = pStart; //到下一段;
                if (++nFind == nRplCount)
                    break;
            }
            else
            {
                pStart = pStart + ((*pStart < 0) ? 2 : 1);
            }
        }

        if (pSrc == _str)   // 循环完第一段数据和原始文本数据一样, 那就是没有替换任何文本
        {
            ret.assign(_str, _destLen);
        }
        else if (pStart > pEnd && pSrc < pEnd) // 枚举到最后一个字符了
        {
            ret.append(pSrc, tstr_len(pSrc));
        }
        else if (((size_t)(pStart - _str)) <= _destLen)  // pStart是每次寻找增加, 如果小于文本长度, 表示循环出来了后面还有字符
        {
            ret.append(pSrc, tstr_len(pSrc));
        }
        return true;
    }

    // 将数值添加千分位分隔
    inline static str_base ToMoney(unsigned __int64 num)
    {
        wchar_t tmp[100] = { 0 };
        int len = swprintf_api(tmp, 50, L"%d", size);

        str_base ret = to_string(num);

        pointer end = ret.data() + 98;
        const_pointer ptr = tmp + len - 1;
        len = 0;
        int i = 0;

        while (*ptr)
        {
            ++i; ++len;
            *end-- = *ptr--;
            if (ptr < tmp)break;
            if (i % 3 == 0)
            {
                *end-- = ',';
                ++len;
            }
        }
        ++end; if (*end == ',')++end;
        ret.Addref();
        return ret;
    }
    
    // 到双精度浮点数
    inline static double        stod(const str_base<char>& val)     { return stod(val.c_str()); }
    inline static double        stod(const str_base<wchar_t>& val)  { return stod(val.c_str()); }
    inline static double        stod(const char* const val)         { return (!val || !val[0]) ? 0 : atof(val); }
    inline static double        stod(const wchar_t* const val)      { wchar_t* _Eptr; return (!val || !val[0]) ? 0 : wcstod(val, &_Eptr); }
    // 到单精度浮点数
    static float                stof(const str_base<char>& val)     { return stof(val.c_str()); }
    static float                stof(const str_base<wchar_t>& val)  { return stof(val.c_str()); }
    inline static float         stof(const char* const val)         { return (!val || !val[0]) ? 0 : atof(val); }
    inline static float         stof(const wchar_t* const val)      { wchar_t* _Eptr; return (!val || !val[0]) ? 0 : (float)wcstod(val, &_Eptr); }
    // 到长浮点型
    inline static long double   stold(const str_base<char>& val)    { return stold(val.c_str()); }
    inline static long double   stold(const str_base<wchar_t>& val) { return stold(val.c_str()); }
    inline static long double   stold(const char* const val)        { char* _Eptr; return (!val || !val[0]) ? 0 : strtold(val, &_Eptr); }
    inline static long double   stold(const wchar_t* const val)     { wchar_t* _Eptr; return (!val || !val[0]) ? 0 : wcstold(val, &_Eptr);  }

    // 到整数 int
    inline static int           stoi(const str_base<char>& val)     { return stoi(val.c_str()); }
    inline static int           stoi(const str_base<wchar_t>& val)  { return stoi(val.c_str()); }
    inline static int           stoi(const char* const val)         { return (!val || !val[0]) ? 0 : atoi(val); }
    inline static int           stoi(const wchar_t* const val)      { return (!val || !val[0]) ? 0 : _wtoi(val); }
    // 到整数 long
    inline static long          stol(const str_base<char>& val)     { return stol(val.c_str()); }
    inline static long          stol(const str_base<wchar_t>& val)  { return stol(val.c_str()); }
    inline static long          stol(const char* const val)         { return (!val || !val[0]) ? 0 : atol(val); }
    inline static long          stol(const wchar_t* const val)      { return (!val || !val[0]) ? 0 : _wtol(val); }
    // 到长整数 long long
    inline static __int64       stoll(const str_base<char>& val)    { return stoll(val.c_str()); }
    inline static __int64       stoll(const str_base<wchar_t>& val) { return stoll(val.c_str()); }
    inline static __int64       stoll(const char* const val)        { return (!val || !val[0]) ? 0 : atoll(val); }
    inline static __int64       stoll(const wchar_t* const val)     { return (!val || !val[0]) ? 0 : _wtoll(val); }


public:
    // BJ 编码转换 base64
    // base64编码, 返回编码后的数据
    inline static str_base<char> base64_encode(const str_base<char>& str_data)
    {
        str_base<char> result;
        size_t slen = str_data.size();
        size_t n = slen / 3 + (slen % 3 != 0);

        size_t dlen = 4 * n + 1;

        result.resize(dlen);

        size_t olen = 0;
        int ret = charset::mbedtls_base64_encode((unsigned char*)result.data(), result.size(), &olen, (const unsigned char*)str_data.data(), str_data.size());
        result.resize(olen);
        ret = 0;
        return result;
    }

    // base64解码, 返回解码后的数据, 解码后的数据不一定是文本, size() 就是解码后数据的长度
    inline static str_base<char> base64_decode(const str_base<char>& str_encoded)
    {
        str_base<char> result;
        result.resize(str_encoded.size());
        size_t olen = 0;
        int ret = charset::mbedtls_base64_decode((unsigned char*)result.data(), result.size(), &olen, (const unsigned char*)str_encoded.GetPtr(), str_encoded.size());
        result.resize(olen);
        ret = 0;
        return result;
    }

private:
    inline static int __rand(int min, int max)                      { return (::rand() % (max - min + 1)) + min; }
};

#if _MSC_VER < 1201
template<typename _Elem>const size_t str_base<_Elem>::npos = -1;
#endif

typedef str_base<char>       _str;
typedef str_base<wchar_t>    wstr;
typedef str_base<TCHAR>      tstr;

typedef strArr<char>        strArrA;
typedef strArr<wchar_t>     strArrW;
typedef strArr<TCHAR>       strArrT;

template<> struct mystruct::struct_hashfun<_str> {
    inline size_t operator()(const _str& key) const __NO_EXCEPT {
        return (size_t)mystruct::hash_key<char>::HashFun(key.c_str());
    }
};

template<> struct mystruct::struct_hashfun<wstr> {
    inline size_t operator()(const wstr& key) const __NO_EXCEPT {
        return (size_t)mystruct::hash_key<wchar_t>::HashFun(key.c_str());
    }
};