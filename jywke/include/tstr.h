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
    size_t* arr;    // ����ƫ��
    size_t count;   // �����Ա��
    size_t len;     // str �ַ�������
    _Elem* str;     // ��¼�ָ���, �ָ���ַ�����\0����, ��ƫ��ָ���ַ���
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

    // ���ƹ��캯��, ��㸴��, �´��һ���µ����ݳ���
    strArr(const strArr& arrObj)
    {
        p = new STRARRDATA;
        memset(p, 0, sizeof(STRARRDATA));

        // ���ַ�������һ��
        p->str = new _Elem[arrObj.p->len + 1];
        memset(p->str, 0, (arrObj.p->len + 1) * sizeof(_Elem));

        // ������ƫ�ƿ���һ��, �����Ա = str + arr[index]
        p->arr = new size_t[arrObj.p->count];   
        memset(p->arr, 0, arrObj.p->count * sizeof(size_t));
        memcpy(p->arr, arrObj.p->arr, arrObj.p->count * sizeof(size_t));
    }
    ~strArr() { free(); }

    
    // ȡָ����Ա���ַ���, _indexԽ�緵��0, ���صĵ�ַ�����޸�
    const _Elem* operator[](const size_t _index) const { return at(_index); }
    const _Elem* at(const size_t _index) const
    {
        if (!p || _index > p->count - 1)return 0;
        _Elem* ret = (_Elem*)(p->str + p->arr[_index]);
        return ret;
    }
    // ȡ�����Ա��
    inline size_t count() { return size(); }
    inline size_t size() { return p ? p->count : 0; }
    inline bool Attach(LPSTRARRDATA ptr) { if (ptr)p = ptr; return ptr != 0; }
    // �ͷ�����, �ͷź�����ʹ��, ������������ʱ���Զ��ͷ�
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
        size_t  len;        // �ַ�������
        int     Addref;     // ���ü���, ֻ���ֶ�����, ������ʱ����ֵΪ0���ͷ�, �ڸ��ƹ��캯�������ֵ����1ʱǳ�㿽��, ����1ʱ��㿽��
        pointer pData;      // �����ַ�������ʼλ��
        size_t  bufferLen;  // ����������Ļ������ܳ���
    }STRMEMORYDATA, * LPSTRMEMORYDATA;

    // �����ֻ�ṩ���ַ�����ʹ��
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



    // �����һ���������ǵڶ����������ָ��, �ǾͲ����κδ���
    // �жϵ�һ�������Ƿ��ǵڶ����������ָ��
    // �����, �Ǿ�������һ���ڴ汣�����1������, Ȼ��Ѳ���1�޸ĳ������������ڴ��ַ, ���Ұ���������ڴ渳ֵ������3, ����3���Զ��ͷ�
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
   

    // BJ ������Ĺ��캯��
    str_base() : m_ptr(0) { ; }
    explicit str_base(size_t _count) : m_ptr(0) { setstr(_count); if (m_ptr)m_ptr->len = 0; }
    str_base(const_pointer const s, size_t len = 0) : m_ptr(0) { setstr(s, len); }
    str_base(size_t _count, const value_type s) : m_ptr(0) { setstr(_count, s); }
#if _MSC_VER > 1200
    // �ƶ����캯��
    str_base(str_base&& s) noexcept : m_ptr(0)
    {
        swap(s);
        if (m_ptr && m_ptr->Addref > 1)
            m_ptr->Addref--;
    }
#endif
    // ���ƹ��캯��
    str_base(const str_base& s) : m_ptr(0)
    {
        if (s.m_ptr && s.m_ptr->Addref > 1)    // ���ü�������1��ֻ��ǳ�㿽��
        {
            m_ptr = s.m_ptr;
            //m_flag = 0;
            return;

        }
        setstr(s.c_str(), s.size());
    }

    // ��������
    ~str_base() 
    { 
        Release();
        m_ptr = 0;
    }

protected:

    // �ͷ�֮ǰ���ı�, �ѵ�ǰ�ı��滻�����õ��ı�
    inline void setstr(const_pointer s, size_t len = 0)
    {
        if (s && m_ptr && s == m_ptr->pData)    // ����ĵ�ַ�ͱ������ڵ��ַ����׵�ַһ��, �޸ĳ��Ⱦ���
        {
            if (!len)return;    // û�д��ݳ���, �Ǿ����Լ���ֵ���Լ�
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
    // �ͷ�֮ǰ���ı�, �ѵ�ǰ�ı��滻��ָ���������ַ�
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
    // BJ ����������������
#pragma region _operator

    // ���·��仺����, �����޸�ԭ���ַ������Ⱥ�����
    inline bool operator()(size_t count)
    {
        if (!m_ptr || m_ptr->bufferLen > count)return false;
        return realloc(count) != 0;
    }
    // �������δ��ʼ��, �򷵻�һ��������
    reference operator*() const
    {
        // Ӧ����Ƴ��׳��쳣���Ƿ��ؿ�����?
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

    //// ��������
    //inline operator pointer() const
    //{
    //    return m_ptr ? m_ptr->pData : 0;
    //}
    // ͨ���±�������ָ�����ַ�,��������,�����޸�ֵ, �±�Խ���׳��쳣, ����Ϊ size_t ֵΪ ������±�
    inline reference operator[](size_t _off)
    {
        if (!m_ptr || _off >= m_ptr->len) throw _off;
        return m_ptr->pData[_off];
    }

    // ͨ���±�������ָ�����ַ�,����ֵ,�����޸�, �±�Խ���׳��쳣, ����Ϊ size_t ֵΪ ������±�
    inline const value_type operator[](size_t _off)const
    {
        if (!m_ptr || _off >= m_ptr->len) throw _off;
        return m_ptr->pData[_off];
    }

    // ��ֵ,���ر����������
    inline str_base& operator=(const str_base& s)
    {
        if (this == s.__get_this())
            return *this;
        return assign(s);
    }

    // ��ֵ,���ر����������
    inline str_base& operator=(const_pointer s)
    {
        if (m_ptr && s == m_ptr->pData)return *this;    // ��ֵ��ָ������Ǳ������ָ��
        return assign(s);
    }
#if _MSC_VER > 1200
    friend std::ostream& operator <<(std::ostream& out, const str_base& obj)
    {
        if (obj.m_ptr)
            std::cout << obj.m_ptr->pData;
        return out;
    }
    // ��ֵ,���ر����������, ��ֵ���ð�
    inline str_base& operator=(str_base&& s) __NO_EXCEPT
    {
        return assign(std::move(s));
    }
    // �����ı�, ���ر����������, ��ֵ���ð�
    inline str_base& operator+(str_base&& s) noexcept
    {
        return append(std::move(s));
    }
#endif
    // �ַ����,����������������һ���Ǳ������,������Ӻ�Ķ���
    inline str_base operator+(const value_type s)
    {
        str_base tmp;
        if (!m_ptr)    // ԭ�ַ���û�г�ʼ��
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

    // �ַ������,����������������һ���Ǳ������,������Ӻ�Ķ���
    inline str_base operator+(const str_base& s)
    {
        if (!m_ptr)
            return s;    // ԭ�ַ���û�г�ʼ��ֱ�ӷ��ر��ӵ��ַ���
        str_base ret = operator+(s.c_str());
        ret.Addref();
        return ret;
    }
    // �ַ������,����������������һ���Ǳ������,������Ӻ�Ķ���
    inline str_base operator+(const_pointer s)
    {
        if (!m_ptr) return s;   // ԭ�ַ���û�г�ʼ��ֱ�ӷ��ر��ӵ��ַ���
        if (!s)return m_ptr->pData;

        str_base ret(m_ptr->len + tstr_len(s));
        ret.assign(m_ptr->pData, m_ptr->len).append(s);
        ret.Addref();
        return ret;
    }
    // ���ַ������ӵ��������ַ����ĺ���
    inline void operator+=(const str_base& s)           { append(s); }
    // ���ַ������ӵ��������ַ����ĺ���
    inline void operator+=(const value_type s)          { append(1, s); }
    // ���ַ������ӵ��������ַ����ĺ���
    inline void operator+=(const_pointer s)             { append(s); }

    // ��������ַ����Ƿ�С����һ���ַ���
    inline bool operator<(const str_base& s2)const      { return operator<(s2.c_str()); }
    inline bool operator<(const_pointer s2)const        { return compare(s2, true) < 0; }


    // ��������ַ����Ƿ������һ���ַ���
    inline bool operator>(const str_base& s2)const      { return operator>(s2.c_str()); }
    inline bool operator>(const_pointer s2)const        { return compare(s2, true) > 0; }

    // ��������ַ����Ƿ������һ���ַ���
    inline bool operator==(const str_base& s2)const     { return operator==(s2.c_str()); }
    inline bool operator==(const_pointer s2)const       { return compare(s2, true) == 0; }


    // ��������ַ����Ƿ񲻵�����һ���ַ���
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
        if (!m_ptr) // ����ʱ������û�г�ʼ��, ֱ�ӰѴ��ݽ����Ķ���ָ�븳ֵ��������
        {
            m_ptr = s.m_ptr;
            s.m_ptr = 0;
            return *this;
        }
        // �ߵ����ʾ��ֵʱ�������Ѿ���ʼ��, �жϴ���Ķ�����û�г�ʼ��
        STRMEMORYDATA* ptr = s.m_ptr;
        if (!ptr)
        {
            // ����Ķ���û�г�ʼ��, ֱ�ӷ��ر�����
            return *this;
        }

        // �ߵ��⴫��Ķ���ͱ����󶼲�Ϊ��, �Ա�һ���ĸ���������, �ĸ������ĸ�
        if (m_ptr->bufferLen > ptr->bufferLen)  // ������Ļ������Ƚϴ�, ��������������
        {
            return append(ptr->pData, ptr->len);   // ֱ����������ַ���
        }
        if (ptr->len + m_ptr->len > ptr->bufferLen) // �������Ļ����������Դ�������ַ����Ľ��
        {
            return append(ptr->pData, ptr->len);   // ֱ����������ַ���
        }

        // �ߵ��⴫��Ķ��󻺳����ȱ�����Ҫ��, ���ܴ�Ž��
        // �ô������ĺ�벿����Ϊ��ʱ������, ��¼�����������
        pointer pData = (ptr->pData + ptr->bufferLen) - ptr->len;               // ��¼��ʱ�������ʱ������
        memcpy(pData, ptr->pData, ptr->len * sizeof(value_type));               // �Ѵ�������������ʱ��¼����ʱ��������β��
        memcpy(ptr->pData, m_ptr->pData, m_ptr->len * sizeof(value_type));      // �ѱ���������ݿ���������Ķ���
        memcpy(ptr->pData + m_ptr->len, pData, ptr->len * sizeof(value_type));  // ����ʱ�����������ݿ������ַ�����β��
        ptr->len += m_ptr->len;
        ptr->pData[ptr->len] = 0;
        s.m_ptr = m_ptr;
        m_ptr = ptr;
        return *this;
    }
#endif
    // �����ı������, len = 0����\0��β
    str_base& append(const_pointer _ptr, const size_t _len = 0)
    {
        if (_ptr == 0) return *this;
        size_t len = _len;
        if (len == 0) len = tstr_len(_ptr);
        if (len == 0) return *this;

        pointer p = 0;
        if (!m_ptr) p = realloc(len + _STR_BUFFER_SIZE);    // ԭ�ַ���û�г�ʼ�����ʼ��һ��

        size_t newLen = len + m_ptr->len;
        if (newLen <= m_ptr->bufferLen)    // ���������㹻���������
        {
            memcpy(m_ptr->pData + m_ptr->len, _ptr, len * sizeof(value_type));    // ֱ�ӿ������ַ�������������
            m_ptr->pData[newLen] = 0;
            m_ptr->len = newLen;
            return *this;
        }

        // �ߵ�����ǻ�����������, ��Ҫ��������
        size_t bufferSize = newLen + _STR_BUFFER_SIZE;    // ��������Ҫ�����볤��
        p = realloc(bufferSize);
        memcpy(m_ptr->pData + m_ptr->len, _ptr, len * sizeof(value_type));    // ֱ�ӿ������ַ�������������
        m_ptr->pData[newLen] = 0;
        m_ptr->len = newLen;    // ���ַ����ĳ���
        return *this;
    }
    // ����һ���ַ�
    inline str_base& append(value_type _ch) { return append(&_ch, 1); }
    // ����һ���ظ��ַ����ı�, _count = �ظ�����, _ch = �ַ�
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

    // �ڶ�����������ָ�������, �ڶ�������û��ʹ��, ��0��������ָ�붼����
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


    // ����һ���ظ����ı�, _count = �ظ�����, ����0������, _ptr = �ظ����ı�, _len = �����ı��ĳ���, Ϊ0�� _ptr������\0Ϊ��β
    inline str_base& append(const size_t _count, const_pointer _ptr, const size_t _len = 0)
    {
        if (!_ptr)return *this;
        size_t count = _count;
        if (count == 0)return *this;

        size_t len = _len;
        if (len == 0) len = tstr_len(_ptr);
        if (!m_ptr) realloc(len + _STR_BUFFER_SIZE);    // ԭ�ַ���û�г�ʼ�����ʼ��һ��

        pointer buffer = 0;
        size_t newLen = _count * len;
        size_t oldLen = m_ptr->bufferLen - m_ptr->len;
        if (oldLen > newLen)    // �ɻ������㹻���
            buffer = m_ptr->pData;
        else
            buffer = realloc(newLen + m_ptr->len + _STR_BUFFER_SIZE);   // ������������·����ڴ�
        
        buffer += +m_ptr->len;  // ָ���ַ���β��
        size_t i;
        for (i = 0; i < _count; i++)
            memcpy(buffer + len * i, _ptr, len * sizeof(value_type));
        m_ptr->len += newLen;
        m_ptr->pData[m_ptr->len] = 0;
        return *this;
    }

    // ����һ���ظ��ı�, _count С��1������Ϊ1
    inline str_base& append(const size_t _count, const str_base& str, size_t _len = 0)
    {
        size_t count = _count;
        if (count == 0)count = 1;
        if (_len == 0)_len = str.size();
        return append(_count, str.c_str(), _len);
    }

    // ����һ���ظ��ı�, _count С��1������Ϊ1
    inline str_base& append(const str_base& _str, const size_t _count = 1)
    {
        size_t count = _count;
        if (count == 0)count = 1;
        return append(_count, _str.c_str(), _str.size());
    }


#if _MSC_VER > 1200
    inline str_base& assign(str_base&& s)
    {
        if (!m_ptr) // ��ֵʱ������û�г�ʼ��, ֱ�ӰѴ��ݽ����Ķ���ָ�븳ֵ��������
        {
            m_ptr = s.m_ptr;
            s.m_ptr = 0;
            return *this;
        }
        // �ߵ����ʾ��ֵʱ�������Լ���ʼ��, �Ա�һ���ĸ���������, �ĸ������ĸ�
        STRMEMORYDATA* ptr = s.m_ptr;
        if (!ptr)
        {
            // ����Ķ���û�г�ʼ��, ����������0
            m_ptr->pData[0] = 0;
            m_ptr->len = 0;
            return *this;
        }

        // �ߵ��⴫��Ķ���ͱ����󶼲�Ϊ��
        if (m_ptr->bufferLen > ptr->bufferLen)  // ������Ļ������Ƚϴ�
        {
            memcpy(m_ptr->pData, ptr->pData, ptr->len * sizeof(value_type) + sizeof(value_type));
            m_ptr->len = ptr->len;  // ����Ķ��󻺳����Ƚ�С, ��Ѵ����������ݿ�����������, ��������Ķ���
            return *this;
        }
        // �ߵ��⴫��Ķ��󻺳����ȱ�����Ҫ��, �������󽻻�һ��
        swap(s);
        return *this;
    }
#endif
    // ��ֵ, len = 0����\0��β
    inline str_base& assign(const_pointer _ptr, size_t len = 0)
    {
        setstr(_ptr, len);
        return *this;
    }
    // ��ֵΪһ���ظ��ַ����ı�, _count = �ظ�����, _ch = �ַ�
    inline str_base& assign(size_t _count, value_type _ch)
    {
        str_base_AutoFreePtr p(alloc(_count, _ch));
        return assign(p, _count);
    }
    // ��ֵΪһ���ظ����ı�, _count = �ظ�����, ����0������, _ptr = �ظ����ı�
    inline str_base& assign(size_t _count, const_pointer _ptr, size_t strLen)
    {
        if (_count == 0)return *this;
        if (strLen == 0) strLen = tstr_len(_ptr);
        size_t newLen = _count * strLen;
        size_t oldLen = m_ptr ? m_ptr->bufferLen : 0;
        pointer buffer = m_ptr ? m_ptr->pData : 0;
        if (oldLen <= newLen)    // �������������
            buffer = realloc(newLen);

        size_t i;
        for (i = 0; i < _count; i++)
            memcpy(buffer + strLen * i, _ptr, strLen * sizeof(value_type));
        buffer[newLen] = 0;
        m_ptr->len = newLen;
        return *this;
    }
    // ��ֵΪһ���ظ��ı�, _count С��1������Ϊ1
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

    // �ı����ò���, ���ô�С, ��ʽ��, �Ƚ�, ����Сд
#pragma region text_resize_format_cmp_toup_tolo

    // ����Ҫ��׷�ӻ�ɾ��Ԫ��, Ϊ�ַ���ָ���µĴ�С
    // ���µ����ߴ�, ֮ǰ�����ݲ����, ���ú��ַ������� = ���õĳ���
    // _ch = ������������, ���Ϊ0,����ԭ����, ���ಿ����0���, ��Ϊ0�����ԭ���ݲ��ø��ַ����
    inline void resize(size_t newsize, value_type _ch = 0)
    {
        if (!m_ptr)
        {
            setstr(newsize, _ch);
            return;
        }
        if (m_ptr->bufferLen < newsize)    // �������������������
        {
            realloc(m_ptr->bufferLen + newsize + _STR_BUFFER_SIZE);
        }

        m_ptr->len = newsize;
        for (size_t i = newsize; i < m_ptr->bufferLen; i++)
            m_ptr->pData[i] = _ch;    // ����������ָ���ַ����
        return;
    }

    // �������õ�ǰ�ַ���������ַ�������, �����޸��κ��ڴ�, ֻ�޸�\0֮ǰ�ж��ٸ��ַ�
    inline size_t resize_strlen()
    {
        if (!m_ptr) return 0;
        m_ptr->len = tstr_len(m_ptr->pData);
        return m_ptr->len;
    }

    // ���µ����������ߴ�, ����ı�ԭ���ݴ�С, ֮ǰ�����ݲ����, ����³ߴ�С�ڵ�ǰ��ռ�óߴ��򷵻�false
    inline bool reserve(size_t newsize)
    {
        size_t oldLen = 0;
        if (m_ptr)oldLen = m_ptr->len;
        if (newsize < oldLen) return false;
        resize(newsize);
        m_ptr->len = oldLen;
        return true;
    }

    // ȡָ��λ�õ��ֽ�, �ú������׳��쳣, ���᷵��һ�������� operator[] ���׳��쳣, �±�Խ���δ��ʼ�������ؿ�����
    inline reference at(const size_t off) __NO_EXCEPT
    {
        if (!m_ptr || off >= m_ptr->len) return *((pointer)0);
        return m_ptr->pData[off];
    }
    // ȡָ��λ�õ��ֽ�, �ú������׳��쳣, �±�Խ���δ��ʼ�������ؿ�����
    inline const_reference at(const size_t off)const __NO_EXCEPT
    {
        if (!m_ptr || off >= m_ptr->len) return *((pointer)0);
        return m_ptr->pData[off];
    }

    // �����ַ����е�һ��Ԫ�ص�����
    inline reference front()
    {
        if (!m_ptr || !m_ptr->len) return *((pointer)0);
        return m_ptr->pData[0];
    }

    // �����ַ����е�һ��Ԫ�ص�����
    inline const_reference front() const
    {
        if (!m_ptr || !m_ptr->len) return *((pointer)0);
        return m_ptr->pData[0];
    }


    // �����ַ��������һ��Ԫ�ص�����
    inline reference back()
    {
        if (!m_ptr || !m_ptr->len) return *((pointer)0);
        return m_ptr->pData[m_ptr->len - 1];
    }

    // �����ַ��������һ��Ԫ�ص�����
    inline const_reference back() const
    {
        if (!m_ptr || !m_ptr->len) return *((pointer)0);
        return m_ptr->pData[m_ptr->len - 1];
    }
    
    // Debug �� Release�汾�������
    // pstr = ����������ı�
    inline static void debug(str_base* pstr, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        __debug(pstr, 260, format, aptr);
        va_end(aptr);
        return;
    }
    // Debug �� Release�汾�������
    inline static void debug(const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        __debug(0, 260, format, aptr);
        va_end(aptr);
        return;
    }
    // Release�治�����, ��������Ҳ��Ҫ�����, ����� debug
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
    // Release�治�����, ��������Ҳ��Ҫ�����, ����� debug
    // pstr = ����������ı�, ���ΪRelease�治�ᴦ��˲���
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
    // Release�治�����, ��������Ҳ��Ҫ�����, ����� debug
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

    // ��ȡ��ʽ���ı�, �������ߴ�Ϊ260, ����������ʱ������
    inline static str_base GetFormat(const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        str_base ret = GetFormatEx(260, format, aptr);
        va_end(aptr);
        return ret;
    }

    // ��ȡ��ʽ���ı�, �Զ��建������С, ����������ʱ������
    inline static str_base GetFormat(size_t bufferSize, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        str_base ret = GetFormatEx(bufferSize, format, aptr);
        va_end(aptr);
        return ret;
    }

    // ���ɸ�ʽ���ı�, �������ߴ�Ϊ260, ����������ʱ������
    // bufferSize = ����������, ���Ϊ0������Ϊ260
    // format ��ʽ���ַ���
    // list = �����б�
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

    
    // ��ʽ���ı�, �������ߴ�Ϊ260, ����������ʱ������
    inline int FormatEx(size_t bufferSize, const_pointer format, va_list list)
    {
        str_base buf = GetFormatEx(bufferSize, format, list);

        if (!m_ptr) // ������û�г�ʼ��, ֱ�Ӱ���ʱ����ָ�븳ֵ��������
        {
            swap(buf);
            return (int)buf.size();
        }

        if (m_ptr->bufferLen > bufferSize)  // ������Ļ������Ƚϴ�
        {
            assign(buf);    // ����Ķ��󻺳����Ƚ�С, ��Ѵ����������ݿ�����������, ��������Ķ���
            return (int)buf.size();
        }
        // �ߵ��⴫��Ķ��󻺳����ȱ�����Ҫ��, �������󽻻�һ��
        swap(buf);
        return (int)buf.size();
    }

    // ��ʽ���ı�, �������ߴ�Ϊ260, ����������ʱ������
    inline int Format(const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        int r = FormatEx(260, format, aptr);
        va_end(aptr);
        return r;
    }

    // ��ʽ���ı�, �Զ��建������С, ����������ʱ������
    inline int Format(size_t bufferSize, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        int r = FormatEx(bufferSize, format, aptr);
        va_end(aptr);
        return r;
    }

    // ��ʽ��һ���ı������뵽��ǰ�ַ�����
    // ��ʽ���ı��������ߴ�Ϊ260, ����������ʱ������
    inline str_base& AppendFormat(const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        append(GetFormatEx(260, format, aptr));
        va_end(aptr);
        return *this;
    }

    // ��ʽ��һ���ı������뵽��ǰ�ַ�����
    // �Զ����ʽ���ı���������С, ����������ʱ������
    inline str_base& AppendFormat(size_t bufferSize, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        append(GetFormatEx(bufferSize, format, aptr));
        va_end(aptr);
        return *this;
    }

    // ����ǰ������ı��� format �ĸ�ʽȡ�����ŵ�����Ĳ�����, ʧ�ܷ���-1, ֧�� %[a-z]
    // ... �������ձ�����ַ
    // ����� 2020-01-01 01:01:01 ��������ʱ���붼ȡ����, ��format���� %d-%d-%d %d:%d:%d
    inline int sscanf(const_pointer format, ...)
    {
        if (empty())return -1;
        va_list aptr;
        va_start(aptr, format);
        int ret = tstr_vsscanf(m_ptr->pData, format, aptr);
        va_end(aptr);
        return ret;
    }

    // �� buffer ���ı��� format �ĸ�ʽȡ�����ŵ�����Ĳ�����, ʧ�ܷ���-1, ֧�� %[a-z]
    // ... �������ձ�����ַ
    // ����� 2020-01-01 01:01:01 ��������ʱ���붼ȡ����, ��format���� %d-%d-%d %d:%d:%d
    inline static int sscanf(const_pointer buffer, const_pointer format, ...)
    {
        va_list aptr;
        va_start(aptr, format);
        int ret = tstr_vsscanf(buffer, format, aptr);
        va_end(aptr);
        return ret;
    }

    // ��������ת�ɴ����ı�
    // errCode ������
    // lpszModule = ���������ڵ�ģ��, Ϊ0���Զ�������ǰ�����ļ�����Ϣ��Դ
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

    // ��������ת�ɴ����ı�
    // errCode ������
    // hModule = ���������ڵ�ģ����, Ϊ0���Զ�������ǰ�����ļ�����Ϣ��Դ
    inline static str_base FormatMsg(DWORD errCode, HMODULE hModule = 0)
    {
        pointer pBuffer = NULL;
        DWORD dwFlags = 0;
        if (hModule) dwFlags = FORMAT_MESSAGE_FROM_HMODULE;

        //lpSource = dwFlagsָ����FORMAT_MESSAGE_FROM_HMODULE�Ļ�, �˲�����ʾģ���HANDLE 

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

    // ʹ��ָ������Ϣ�ͱ�����ʽ����Ϣ�ַ��������б�
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

    // �ѵ�ǰ�ַ���ת��Сд, �����滻���ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�0
    inline str_base tolower(const size_t _off = 0, const size_t _count = size_t(-1)) const
    {
        if (_count == 0 || !m_ptr)return str_base();
        str_base ret;
        tolowerEx(ret, m_ptr->pData, m_ptr->len, _off, _count);
        ret.Addref();
        return ret;
    }

    // �ѵ�ǰ�ַ���ת��Сд, �����滻���ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�0
    inline int tolowerEx(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_count == 0 || !m_ptr)return 0;
        return tolowerEx(*this, m_ptr->pData, m_ptr->len, _off, _count);
    }

    // �ѵ�ǰ�ַ���ת�ɴ�д, _off=��ʼλ��, _count=ת�����ַ���, �����滻���ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�0
    inline str_base toupper(const size_t _off = 0, const size_t _count = size_t(-1)) const
    {
        if (_count == 0 || m_ptr == 0)return str_base();
        str_base ret;
        toupperEx(ret, m_ptr->pData, m_ptr->len, _off, _count);
        ret.Addref();
        return ret;
    }

    // �ѵ�ǰ�ַ���ת�ɴ�д, _off=��ʼλ��, _count=ת�����ַ���, �����滻���ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�0
    inline int toupperEx(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_count == 0 || m_ptr == 0)return 0;
        return toupperEx(*this, m_ptr->pData, m_ptr->len, _off, _count);
    }
    // �ı�����, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ҳ���ַ���, ansi�����ڲ�ת��Unicode��ת��, ansi�治����ʹ��
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline bool reverse(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        if (_count == 0 || m_ptr == 0)return 0;
        return reverseEx(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ����, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline bool isNumber(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isNumber(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�ΪСд��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline bool isLower(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isLower(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ��д��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline bool isUpper(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isUpper(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline bool isLetter(const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isLetter(m_ptr->pData, m_ptr->len, _off, _count);
    }

    // �ָ��ַ���, ���س�Ա��
    // arr = ���շָ���ָ��, ����ΪNULL
    // _substr = �����ָ���ַ���, Ϊ���򰴻��� "\r\n"���зָ�
    // _count = Ҫ���ص����ı���Ա��, Ϊ0�򷵻ز����в���
    inline size_t split(strArr<value_type>* arr, const_pointer _substr, const size_t _count = size_t(-1))
    {
        if (!m_ptr) return 0;
        return strtok(m_ptr->pData, arr, _substr, _count);
    }

    // �ָ��ַ���, ���س�Ա��
    // arr = ���շָ���ָ��, ����ΪNULL
    // _substr = �����ָ���ַ���, Ϊ���򰴻��� "\r\n"���зָ�
    // _count = Ҫ���ص����ı���Ա��, Ϊ0�򷵻ز����в���
    inline size_t strtok(strArr<value_type>* arr, const_pointer _substr, const size_t _count = size_t(-1))
    {
        if (!m_ptr) return 0;
        return strtok(m_ptr->pData, arr, _substr, _count);
    }
    // �ı��Ƚ�, ��ȷ���0, С�ڷ��ظ���, ���ڷ�������
    // _dst    = ���Ƚϵ��ı�
    // _start    = ��ʼ�Ƚϵ�λ��, Խ���0��ʼ
    // _count    = �Ƚϵ��ַ���,Unicode��Ϊ�ַ�, ���ֽڰ�Ϊ�ֽ�, Ϊ0����\0λ������־
    // isCase    = �Ƿ����ִ�Сд, true = ����, false = ������
    inline int compare(const str_base& s2, const size_t _start = 0, const size_t _len = 0, bool isCase = false)const
    {
        return compare(m_ptr ? m_ptr->pData : 0, s2.c_str(), _start, _len, isCase);
    }

    // ���ı��Ƚ�, ��ȷ���0, С�ڷ��ظ���, ���ڷ�������
    // _dst    = ���Ƚϵ��ı�
    // _start    = ��ʼ�Ƚϵ�λ��, Խ���0��ʼ
    // _count    = ���Ƚ��ı����ַ���,Unicode��Ϊ�ַ�, ���ֽڰ�Ϊ�ֽ�, Ϊ0����\0λ������־
    // isCase    = �Ƿ����ִ�Сд, true = ����, false = ������
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

        if (len1 < _cmplen || len2 < _cmplen)   // �Ƚϵ��ı����Ȳ���, �ĸ��������ĸ���
        {
            return len1 < len2 ? 1 : -1;
        }

        if (((s1 == 0 || s2 == 0)
            && len1 == 0 && len2 == 0)
            || s1 == s2) return 0;                  // �����ı�����һ��Ϊ0, ���������ı����ȶ���0, �������, ��������ָ��һ��
        if (s1 == 0 && s2 == 0)return 0;            // �����ı���Ϊ��, ���
        if (s1 == 0 && s2)return -1;                // ��һ���ı�С�ڵڶ����ı�
        if (s1 && s2 == 0)return 1;                 // ��һ���ı����ڵڶ����ı�

        // �ߵ��������ı�����Ϊ��
        size_t max_len = len1 < len2 ? len1 : len2; // ���Ƚϳ���, ȡ�����ı���̵�һ��

        //! 1. �����ñȽϳ���, ����Ƚϳ��ȵ���0, ���ߴ�������ı�����, ������Ϊ����ı�����
        if (cmpLen == 0)   cmpLen = max_len;
        if (cmpLen > max_len) cmpLen = max_len;     // ���ñ��Ƚ��ı�����

        //! 2. ��������ʼ�Ƚ�λ��, �����ʼλ�� + �Ƚϳ��� > ����ı�����, ��������ʼλ��Ϊ ��󳤶� - �Ƚϳ���
        size_t start = _start;                      // ��ʼ�Ƚ�λ��  
        if (start + cmpLen >= len1)                 // ��ʼλ�� + �Ƚϳ��� > �ı�1
            start = len1 - cmpLen;                  // ��ʼλ�� = �ı�1 - �Ƚϳ���

        //! 3. �����������Ƚ��ı�, 
        const_pointer p1 = s1 + start;
        const_pointer p2 = s2;

        if (isCase)    // ���ִ�Сд
            return tstr_ncmp(p1, p2, cmpLen);
        return tstr_nicmp(p1, p2, cmpLen);
    }
    // �ı��Ƚ�, ��ȷ���0, С�ڷ��ظ���, ���ڷ�������
    // _dst    = ���Ƚϵ��ı�
    // isCase    = �Ƿ����ִ�Сд, true = ����, false = ������
    inline int compare(const str_base& s2, bool isCase = false)const
    {
        return compare(m_ptr ? m_ptr->pData : 0, s2.c_str(), isCase);
    }
    // �ı��Ƚ�, ��ȷ���0, С�ڷ��ظ���, ���ڷ�������
    // _dst    = ���Ƚϵ��ı�
    // isCase    = �Ƿ����ִ�Сд, true = ����, false = ������
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
            || s1 == s2) return 0;                  // �����ı�����һ��Ϊ0, ���������ı����ȶ���0, �������, ��������ָ��һ��
        if (s1 == 0 && s2 == 0)return 0;            // �����ı���Ϊ��, ���
        if (s1 == 0 && s2)return -1;                // ��һ���ı�С�ڵڶ����ı�
        if (s1 && s2 == 0)return 1;                 // ��һ���ı����ڵڶ����ı�

        // �ߵ�����������Ϊ��
        if (isCase)    // ���ִ�Сд
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
        ret.Addref();   // �����������ͷ�һ��, to_string �����ͷ�һ��
        ret.Addref();   // ������Ҫ������������
        return ret;
    }
public:
    // BJ �����󹫿��ķ���,һЩ�������ַ�������


    // �ַ�������
    inline void swap(str_base& s)
    {
        if (&s == this) return;
        LPSTRMEMORYDATA p = s.m_ptr;
        s.m_ptr = m_ptr;
        m_ptr = p;
    }

    // �ı���ֵ��ת
#pragma region _num_sring
    // ��˫���ȸ�����
    inline double stod()const       { return m_ptr ? stod(m_ptr->pData) : 0; }
    // �������ȸ�����
    inline float stof()const        { return m_ptr ? stof(m_ptr->pData) : 0; }
    // ����������
    inline long double stold()const { return m_ptr ? stold(m_ptr->pData) : 0; }

    // ������ int
    inline int stoi()const          { return m_ptr ? stoi(m_ptr->pData) : 0; }

    // ������ long
    inline long stol()const         { return m_ptr ? stol(m_ptr->pData) : 0; }

    // �������� long long
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
    // �ַ����Ƿ�Ϊ��, �ַ�������Ϊ0, ������, ��Ա������Ч�� size == 0
    inline bool empty()const { return (m_ptr == 0) || (m_ptr->len == 0); }

    // ����ַ���������Ԫ��, �����ͷ��ַ���������, ����ַ������, ����ֵ����Ϊ0
    inline void clear()
    {
        if (!m_ptr) return;
        memset(m_ptr->pData, 0, m_ptr->bufferLen);
        //m_ptr->pData[0] = '\0';
        m_ptr->len = 0;
    }

public:
    // �ַ�����ɾ�Ĳ����

    // ����ַ����Ƿ���ָ�����ַ���ͷ
    // c = Ҫ���ҵĵ��ַ�ǰ׺
    // isCase = �Ƿ����ִ�Сд
    inline bool starts_with(value_type c, bool isCase = true) const
    {
        if (empty())return false;
        return starts_with(m_ptr->pData, c, isCase);
    }

    // ����ַ����Ƿ���ָ�����ַ���ͷ
    // c = ��NULL��β���ַ���, ���а���Ҫ���ҵ�ǰ׺
    // isCase = �Ƿ����ִ�Сд
    inline bool starts_with(const_pointer x, bool isCase = true) const
    {
        if (!x || !x[0] || empty())return false;
        size_t len = tstr_len(x);
        if (len > m_ptr->len)return false;  // ������ַ����ȱ������ַ�������, �Ǿ�һ����ƥ��

        if (!isCase)
        {
            return tstr_nicmp(m_ptr->pData, x, len) == 0;
        }
        return tstr_ncmp(m_ptr->pData, x, len) == 0;
    }

    // ����ַ����Ƿ���ָ�����ַ���ͷ
    // c = Ҫ���ҵĵ��ַ�ǰ׺
    // isCase = �Ƿ����ִ�Сд
    inline static bool starts_with(const_pointer _string, value_type c, bool isCase = true)
    {
        if (!_string || !_string[0])return false;
        value_type ch = _string[0];
        if (!isCase)
        {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')   // ����ĸ, ��Ҫת���Ƚ�
                c |= 32;
            if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')   // ����ĸ, ��Ҫת���Ƚ�
                ch |= 32;
        }
        return ch == c;
    }

    // ����ַ����Ƿ���ָ�����ַ���ͷ
    // c = ��NULL��β���ַ���, ���а���Ҫ���ҵ�ǰ׺
    // isCase = �Ƿ����ִ�Сд
    inline static bool starts_with(const_pointer _string, const_pointer x, bool isCase = true)
    {
        if (!_string || !_string[0] || !x || !x[0])return false;
        const size_t strLen = tstr_len(_string);
        const size_t len = tstr_len(x);
        if (len > strLen)return false;  // ������ַ����ȱ������ַ�������, �Ǿ�һ����ƥ��

        if (!isCase)
        {
            return tstr_nicmp(_string, x, len) == 0;
        }
        return tstr_ncmp(_string, x, len) == 0;
    }

    // ����ַ����Ƿ���ָ�����ַ���β
    // c = Ҫ���ҵĵ��ַ���׺
    // isCase = �Ƿ����ִ�Сд
    inline bool ends_with(value_type c, bool isCase = true) const
    {
        if (empty())return false;
        value_type ch = m_ptr->pData[m_ptr->len - 1];
        if (!isCase)
        {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')   // ����ĸ, ��Ҫת���Ƚ�
                c |= 32;
            if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')   // ����ĸ, ��Ҫת���Ƚ�
                ch |= 32;
        }
        return ch == c;
    }

    // ����ַ����Ƿ���ָ�����ַ�����β
    // x = ��NULL��β���ַ���, ���а���Ҫ���ҵĺ�׺
    // isCase = �Ƿ����ִ�Сд
    inline bool ends_with(const_pointer x, bool isCase = true) const
    {
        if (!x || !x[0] || empty())return false;
        size_t len = tstr_len(x);
        if (len > m_ptr->len)return false;  // ������ַ����ȱ������ַ�������, �Ǿ�һ����ƥ��

        const_pointer _start = m_ptr->pData + (m_ptr->len - len);
        if (!isCase)
        {
            return tstr_icmp(_start, x) == 0;
        }
        return tstr_cmp(_start, x) == 0;
    }

    // ����ַ����Ƿ���ָ�����ַ���β
    // c = Ҫ���ҵĵ��ַ���׺
    // isCase = �Ƿ����ִ�Сд
    inline static bool ends_with(const_pointer _string, value_type c, bool isCase = true)
    {
        if (!_string || !_string[0])return false;
        size_t len = tstr_len(_string);
        value_type ch = _string[len - 1];

        if (!isCase)
        {
            if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')   // ����ĸ, ��Ҫת���Ƚ�
                c |= 32;
            if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')   // ����ĸ, ��Ҫת���Ƚ�
                ch |= 32;
        }
        return ch == c;
    }

    // ����ַ����Ƿ���ָ�����ַ�����β
    // x = ��NULL��β���ַ���, ���а���Ҫ���ҵĺ�׺
    // isCase = �Ƿ����ִ�Сд
    inline static bool ends_with(const_pointer _string, const_pointer x, bool isCase = true)
    {
        if (!_string || !_string[0] || !x || !x[0])return false;
        size_t strLen = tstr_len(_string);
        size_t len = tstr_len(x);
        if (len > strLen)return false;  // ������ַ����ȱ������ַ�������, �Ǿ�һ����ƥ��

        const_pointer _start = _string + (strLen - len);
        if (!isCase)
        {
            return tstr_icmp(_start, x) == 0;
        }
        return tstr_cmp(_start, x) == 0;
    }

    // ����, ɾ��, �滻, ȡ����ұ��м�
#pragma region _find_erase_replace_left_right_
    // �����ַ�, �����ҵ�λ��, û���ҵ�����str_base::npos
    // _off = ����λ��, Ĭ��Ϊ��ǰ�����
    inline size_t find(const value_type _ch, const size_t _off = 0) const
    {
        if (empty())return npos;
        return find(m_ptr->pData, _ch, _off);
    }

    // Ѱ���ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _substr    = Ѱ�ҵ��ı�
    // _off    = Ѱ�ҵ�λ��, 0 = ��ͷ��ʼѰ��
    // c    = �Ƿ����ִ�Сд,true=����,false=������
    inline size_t find(const str_base& _substr, const size_t pos = 0, bool c = true)const
    {
        if (empty())return npos;
        return findEx(m_ptr->pData, _substr.c_str(), m_ptr->len, _substr.size(), pos, c);
    }

    // Ѱ���ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _substr    = Ѱ�ҵ��ı�
    // _off    = Ѱ�ҵ�λ��, 0 = ��ͷ��ʼѰ��
    // c    = �Ƿ����ִ�Сд,true=����,false=������
    inline size_t find(const_pointer _substr, const size_t pos, bool c = true)const
    {
        if (empty())return npos;
        return findEx(m_ptr->pData, _substr, m_ptr->len, tstr_len(_substr), pos, c);
    }
    // Ѱ���ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _substr = Ѱ�ҵ��ı�
    // _strlen = Ѱ���ı��ĳ���, Ϊ0�� _substr������\0��β
    // _off    = Ѱ�ҵ�λ��
    // c    = �Ƿ����ִ�Сд,true=����,false=������
    inline size_t findEx(const_pointer _substr, const size_t _strlen, const size_t pos, bool c)const
    {
        if (empty())return npos;
        return findEx(m_ptr->pData, _substr, m_ptr->len, _strlen, pos, c);
    }

    // �����ַ�, �����ҵ�λ��, û���ҵ�����str_base::npos
    // _ch    = ���ҵ��ַ�
    // _off = ����λ��, Ĭ��Ϊ��������
    inline size_t rfind(const value_type _ch, const size_t _off = size_t(-1))
    {
        if (empty())return npos;
        return rfind(m_ptr->pData, _ch, _off);
    }

    // �����ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _substr = Ѱ�ҵ��ı�
    // _off    = Ѱ�ҵ�λ��, str_base::npos = �ӽ�β��ʼѰ��
    // c    = �Ƿ����ִ�Сд,true=����,false=������
    inline size_t rfind(const str_base& _substr, const size_t pos = size_t(-1), bool c = true)const
    {
        if (empty())return npos;
        return rfindEx(m_ptr->pData, _substr.c_str(), _substr.size(), pos, c);
    }
    // �����ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _substr = Ѱ�ҵ��ı�
    // _off    = Ѱ�ҵ�λ��, str_base::npos = �ӽ�β��ʼѰ��
    // isCase  = �Ƿ����ִ�Сд,true=����,false=������
    inline size_t rfind(const_pointer _substr, const size_t pos = size_t(-1), bool isCase = true)const
    {
        if (empty())return npos;
        return rfindEx(m_ptr->pData, _substr, tstr_len(_substr), pos, isCase);
    }
    // �����ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _substr = Ѱ�ҵ��ı�
    // _strlen = Ѱ���ı��ĳ���, Ϊ0�� _substr������\0��β
    // _off    = Ѱ�ҵ�λ��, str_base::npos = �ӽ�β��ʼѰ��
    // isCase  = �Ƿ����ִ�Сд,true=����,false=������
    inline size_t rfindEx(const_pointer _substr, const size_t _strlen, const size_t pos, bool isCase)const
    {
        if (empty())return npos;
        return rfindEx(m_ptr->pData, _substr, _strlen, pos, isCase);
    }

    

    // �ַ��滻�滻, ����ı�ԭ���ַ�������, ����޸�Ϊ�ַ�0, �ڲ��ַ������Ȳ����
    // _ch = ���滻���ַ���
    // _subch = �滻��
    // _off = �滻����ʼλ��,Ĭ��Ϊ0, ��ʼλ�ô����ַ�������ʱ����FALSSE
    // count = �滻����, Ϊ0�򲻲���
    inline bool replace(const value_type _ch, const value_type _subch, const size_t _off = 0, size_t count = size_t(-1))
    {
        if (!m_ptr || m_ptr->len == 0 || _ch == 0 || count == 0) return false;
        return replaceEx(*this, m_ptr->pData, _ch, _subch, _off, count);
    }

    // ���ı��滻
    // s        = ���滻���ַ���
    // sub      = �滻��
    // _off     = �滻����ʼλ��,Ĭ��Ϊ0
    // count    = �滻����,<= 0 = �������ֵ
    // isCase   = �Ƿ����ִ�Сд
    inline bool replace(const str_base& s, const str_base& sub, const size_t pos = 0, const size_t count = size_t(-1), bool isCase = true)
    {
        if (!m_ptr || s.empty())return false;
        return replaceEx(*this, m_ptr->pData, s.c_str(), sub.c_str(), s.size(), sub.size(), pos, count, isCase);
    }

    // ���ı��滻
    // _string  = ���滻���ַ���
    // _substr  = �滻��
    // _off     = �滻����ʼλ��,Ĭ��Ϊ0
    // count    = �滻����,<= 0 = �������ֵ
    // isCase   = �Ƿ����ִ�Сд
    inline bool replace(const_pointer _string, const_pointer _substr, const size_t _off = 0, size_t count = size_t(-1), bool isCase = true)
    {
        if (!m_ptr || !_string)return false;
        return replaceEx(*this, m_ptr->pData, _string, _substr, tstr_len(_string), 0, _off, count, isCase);
    }

    // ���ı��滻
    // _string  = ���滻���ַ���
    // _substr  = �滻��
    // _strlen  = _string�ĳ���, �����ֵΪ0, ��_string����Ϊ\0��β
    // _sublen  = _substr�ĳ���, �����ֵΪ0, ��_substr����Ϊ\0��β
    // _off     = �滻����ʼλ��,Ĭ��Ϊ0
    // count    = �滻����,<= 0 = �������ֵ
    // isCase   = �Ƿ����ִ�Сд
    inline bool replaceEx(const_pointer _string, const_pointer _substr, const size_t _strlen, const size_t _sublen, const size_t _off, size_t count, bool isCase)
    {
        if (!m_ptr)return false;
        return replaceEx(*this, m_ptr->pData, _string, _substr, _strlen, _sublen, _off, count, isCase);
    }

    // ɾ�����ı�
    // _off    = ��ʼλ��
    // count = ɾ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�, 0=����ʼλ��ɾ��������
    inline str_base erase(const size_t _off, const size_t _count = size_t(-1))
    {
        str_base ret = erase(m_ptr->pData, _off, _count);
        ret.Addref();
        return ret;
    }
    // ɾ�����ı�, ������浽���ַ�����
    // _off    = ��ʼλ��
    // count= ɾ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�, 0=����ʼλ��ɾ��������
    inline bool eraseEx(const size_t _off, const size_t _count = size_t(-1))
    {
        return eraseEx(*this, m_ptr->pData, _off, _count);
    }
    // ɾ�����ı�
    // _str     = ��ɾ�����ı�
    // _off     = ��ʼλ��
    // count    = ɾ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�, 0=����ʼλ��ɾ��������
    inline static str_base erase(const_pointer _str, const size_t _off, const size_t _count = size_t(-1))
    {
        str_base ret;
        eraseEx(ret, _str, _off, _count);
        ret.Addref();
        return ret;
    }
    // ɾ�����ı�
    // ret      = �������ַ���
    // _str     = ��ɾ�����ı�
    // _off     = ��ʼλ��
    // count    = ɾ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�, Ϊ0�򲻲���
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
            count = len - _off;         // ɾ���ĳ���

        size_t newLen = len - count;    // �ܳ��� - ��ɾ���ĳ��� = ���ı�����

        ret.resize(newLen);
        if (_off)
            ret.assign(_string, _off);     // �ȿ�������ı�
        else ret.clear();   // ������û���ı�������ַ���

        if (newLen - _off)
            ret.append(_string + _off + count, newLen - _off);   // �ڿ����ұ�
        ret.Addref();
        return true;
    }
    // ɾ�����һ���ַ�, ���ر�ɾ�����ַ�
    inline value_type pop_back()
    {
        if (!m_ptr || m_ptr->len == 0)return 0;
        value_type ret = m_ptr->pData[--m_ptr->len];
        m_ptr->pData[m_ptr->len] = 0;
        return ret;
    }
    // ���һ���ַ����ַ���ĩβ
    inline void push_back(const value_type _ch)
    {
        if (!m_ptr)return;
        if (m_ptr->len + 1 >= m_ptr->bufferLen)    // ������������
        {
            realloc(m_ptr->bufferLen + _STR_BUFFER_SIZE);
        }
        m_ptr->pData[m_ptr->len++] = _ch;
        m_ptr->pData[m_ptr->len] = 0;
    }

    // ��ָ��λ�ò���һ��ָ���������ַ�, _count Ϊ0�򲻲���
    // _off = �����λ��, ��0��ʼ, Unicode�浥λΪ�ַ�, ���ֽڰ�Ϊ�ֽ�, Խ������뵽ĩβ
    // _count = ���������
    // _ch  = ������ַ�
    inline str_base& insert(const size_t _off, const size_t _count, const value_type _ch)
    {
        if (m_ptr == 0 || _off >= m_ptr->len)
            return append(_count, _ch);
        if (_count == 0)return *this;
        str_base_AutoFreePtr p(alloc(_count, _ch));
        return insert(_off, p, _count, 1);
    }
    // ��ָ��λ�ò���һ���ı� _lenΪ0ʱ��\0Ϊ������
    // _off = �����λ��, ��0��ʼ, Unicode�浥λΪ�ַ�, ���ֽڰ�Ϊ�ֽ�, Խ������뵽ĩβ
    // _str = Ҫ������ַ���
    // _len = _ptr �ַ�������, Ϊ0�������\0Ϊ������־
    // _count = �������, Ĭ��Ϊ1��, Ϊ0ʱ��Ϊ1
    inline str_base& insert(const size_t _off, const_pointer _str, const size_t _len = 0, const size_t _count = 1)
    {
        if (m_ptr == 0 || _off >= m_ptr->len) return append(_str, _len);
        size_t count = _count ? _count : 1;
        size_t len = _len ? _len : tstr_len(_str);
        size_t newLen = m_ptr->len + len * count;
        pointer p = 0;
        if (newLen >= m_ptr->bufferLen)    // ������������
            p = realloc(newLen + _STR_BUFFER_SIZE);
        else
            p = m_ptr->pData;
        
        size_t offset = _off;
        size_t i;

        if (m_ptr->len - _off)    // �������ݲſ���, ԭ�ַ������� - ���ӵ���ʼλ�� > 0 ��ʾ���滹������
            memcpy(p + offset + len, p + _off, (m_ptr->len - _off) * sizeof(value_type));    // �ڿ���ԭ�ַ������沿��

        for (i = 0; i < count; i++)
        {
            memcpy(p + offset, _str, len * sizeof(value_type));        // �ڰ����ı�������ȥ
            offset += len;
        }

        m_ptr->len = newLen;
        return *this;
    }

    // ��ָ��λ�ò���һ��ָ���������ı�, _count Ϊ0�򲻲���
    // _off = �����λ��, ��0��ʼ, Unicode�浥λΪ�ַ�, ���ֽڰ�Ϊ�ֽ�
    // _str = Ҫ������ַ���
    // _len = _str �ַ�������, Ϊ0��������� _str
    // _count = �������, Ĭ��Ϊ1��, Ϊ0ʱ��Ϊ1
    inline str_base& insert(const size_t _off, const str_base& _str, const size_t _len = 0, const size_t _count = 0)
    {
        return insert(_off, _str.c_str(), _len, _count);
    }

    // ����һ���ظ��ı������, _countΪ0������Ϊ1
    inline str_base& insert(const str_base& _str, const size_t _count = 1)
    {
        size_t count = (_count == 0 ? 1 : _count);
        return append(count, _str.c_str(), _str.size());
    }


    // ȡ�ı����
    // count    = ȡ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�
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

    // ȡ�ı����,ȡָ���ַ�����ߵ��ı���
    // _string = ȡ����ַ�����ߵ��ı���,���ص��ı������������ַ���
    // _off = ��ʼ���Ҳ���1��λ��
    str_base left(const str_base& _string, const size_t _off = 0)const
    {
        str_base ret = left(_string.c_str(), _off);
        ret.Addref();
        return ret;
    }
    // ȡ�ı����,ȡָ���ַ�����ߵ��ı���
    // _string = ȡ����ַ�����ߵ��ı���,���ص��ı������������ַ���
    // _off = ��ʼ���Ҳ���1��λ��
    str_base left(const_pointer _string, const size_t _off = 0)const
    {
        size_t count = str_base::find(_string, _off);
        if (count == str_base::npos)return str_base();

        str_base ret = left(count);
        ret.Addref();
        return ret;
    }

    // ȡ�ı��ұ�
    // count    = ȡ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�
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

    // ȡ�ı��ұ�,ȡָ���ַ����ұߵ��ı���
    // s    = ȡ����ַ����ұߵ��ı���,���ص��ı������������ַ���
    // b    = �Ƿ����������ַ���
    // _off    = ��ʼ����λ��, Ĭ�ϴ���β������, 0Ϊ���ײ�����
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
    // ȡ�ı��ұ�,ȡָ���ַ����ұߵ��ı���
    // s    = ȡ����ַ����ұߵ��ı���,���ص��ı������������ַ���
    // b    = �Ƿ����������ַ���
    // _off    = ��ʼ����λ��, Ĭ�ϴ���β������, 0Ϊ���ײ�����
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


    // ȡ�ı��м�
    // _off    = ��ʼȡ��λ��
    // count    = ȡ���ַ���,���ֽڰ浥λ�����ֽ�,Unicodeȡ�����ַ�
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

    // ȡ�ı��м�,�ṩ�����ַ���,ȡ�������ַ����м���ı�,ʧ�ܷ��ؿ��ı�
    // s1    = ǰ����ַ���,δ�ҵ�����ַ����᷵�ؿ�
    // s2    = ������ַ���,δ�ҵ�����ַ����᷵�ؿ�
    // b     = �Ƿ���ǰ���ַ���
    str_base substr(const str_base& s1, const str_base& s2, const size_t _off = 0, bool b = false)const
    {
        size_t pos1 = find(s1, _off);        // Ѱ�ҵ�һ���ַ���
        if (pos1 == str_base::npos)return str_base();

        size_t pos2 = find(s2, pos1 + 1);    // �ڶ���λ�ôӵ�һ���ҵ���λ�ÿ�ʼ
        if (pos2 == str_base::npos)    // ��ʼλ�û��߽���λ��û���ҵ�, ���ؿ��ı�
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

        pos1 += s1.size();        // ������ǰ���ַ���, �ҵ�λ�� + ǰ���ַ�������
        str_base ret = substr(pos1, pos2 - pos1);
        ret.Addref();
        return ret;
    }

    // ȡ�ı��м�,�ṩ�����ַ���,ȡ�������ַ����м���ı�,ʧ�ܷ��ؿ��ı�
    // s1    = ǰ����ַ���,δ�ҵ�����ַ����᷵�ؿ�
    // s2    = ������ַ���,δ�ҵ�����ַ����᷵�ؿ�
    // b    = �Ƿ���ǰ���ַ���
    str_base substr(const_pointer s1, const_pointer s2, const size_t _off = 0, bool b = false)const
    {
        if (!s1 || !s1[0] || !s2 || !s2[0])return str_base();
        size_t pos1 = find(s1, _off);        // Ѱ�ҵ�һ���ַ���
        if (pos1 == str_base::npos)return str_base();

        size_t len1 = tstr_len(s1);
        size_t len2 = tstr_len(s2);

        size_t pos2 = find(s2, (size_t)pos1 + len1 + 1);    // �ڶ���λ�ôӵ�һ���ҵ���λ�ÿ�ʼ
        if (pos1 == str_base::npos || pos2 == str_base::npos)    // ��ʼλ�û��߽���λ��û���ҵ�, ���ؿ��ı�
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

        pos1 += (int)len1;        // ������ǰ���ַ���, �ҵ�λ�� + ǰ���ַ�������
        str_base ret = substr(pos1, (size_t)pos2 - (size_t)pos1);
        ret.Addref();
        return ret;
    }

    // ɾ��ȫ��ָ���ַ�, Ĭ��Ϊ�ո�, ����ɾ������ı�
    str_base TrimAll(const value_type _ch = ' ') const
    {
        if (!m_ptr || m_ptr->len == 0)return str_base();
        pointer pStr = m_ptr->pData;
        while (*pStr == _ch) // ѭ����ͷ��ʼÿ���ַ��ж��ǲ���ָ���ַ�,��Ϊ�Ѿ�ȷ��m_str ����ַ�����\0��β,���Բ���Ҫ�ж�ָ��Խ��
            pStr++;        // ʣ�µĶ���ȡ��ǰ���ָ���ַ�,���Ϊ0, ����ȫ����ָ���ַ�
        size_t len = tstr_len(pStr);    // ������ȥ������ߵ�ָ���ַ�
        size_t i;
        str_base tmp;
        tmp.resize(len);
        pointer p = tmp.data();
        int newLen = 0;
        for (i = 0; i < len; i++)    // һ��ѭ���Ѳ���ָ���ַ��Ķ����뵽���ı���
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

    // ɾ��β�ַ�, Ĭ��ɾ���ո�, ����ɾ������ַ���,�����޸�ԭ�ַ���
    str_base trim(const value_type _ch = ' ')const
    {
        if (!m_ptr || m_ptr->len == 0)return str_base();
        pointer pStr = m_ptr->pData;

        while (*pStr == _ch) // ѭ����ͷ��ʼÿ���ַ��ж��ǲ��ǿո�,��Ϊ�Ѿ�ȷ��m_str ����ַ�����\0��β,���Բ���Ҫ�ж�ָ��Խ��
            pStr++;        // ʣ�µĶ���ȡ��ǰ��Ŀո�,���Ϊ0, ����ȫ���ǿո�

        pointer p1 = pStr;

        size_t nLen = tstr_len(pStr);

        pStr = pStr + nLen - 1;    // ָ�����һ���ַ�
        while (*pStr == _ch && pStr != p1)    // �ж�ָ��Խ��,���pStr == m_str , �Ǿ����Ѿ��ҵ���һ���ַ���,����ѭ��
            pStr--;

        if (pStr == p1 && *pStr == _ch)
            nLen = 0;    // ��ȱ�ʾ�Ѿ��������˵�һ���ַ�,���ҵ�һ���ַ�Ҳ�ǿո�,��ɾ����û�ַ���
        else
            nLen = pStr - p1 + 1;    // �ҵ�λ�õ�ʱ���Ѿ������һ��,����Ҫ+1
        str_base ret = str_base(p1, nLen);
        ret.Addref();
        return ret;
        //str_base str;
        //str = LTrim();
        //str = str.RTrim();
        //return str;
    }

    // ɾ���ַ�, Ĭ��ɾ���ո�, ����ɾ������ַ���,�����޸�ԭ�ַ���
    str_base LTrim(const value_type _ch = ' ')const
    {
        if (!m_ptr || m_ptr->len == 0)return str_base();
        pointer pStr = m_ptr->pData;

        while (*pStr == _ch) // ѭ����ͷ��ʼÿ���ַ��ж��ǲ��ǿո�,��Ϊ�Ѿ�ȷ��m_str ����ַ�����\0��β,���Բ���Ҫ�ж�ָ��Խ��
            pStr++;        // ʣ�µĶ���ȡ��ǰ��Ŀո�,���Ϊ0, ����ȫ���ǿո�

        str_base ret = str_base(pStr);
        ret.Addref();
        return ret;
    }
    // ɾβ�ַ�, Ĭ��ɾ���ո�, ����ɾ������ַ���,�����޸�ԭ�ַ���
    str_base RTrim(const value_type _ch = ' ')const
    {
        if (!m_ptr || m_ptr->len == 0)return str_base();
        size_t nLen = m_ptr->len;
        if (m_ptr->len == 0)return str_base();

        pointer pStr = m_ptr->pData + m_ptr->len - 1;    // ָ�����һ���ַ�
        while (*pStr == _ch && pStr != m_ptr->pData)    // �ж�ָ��Խ��,���pStr == m_str , �Ǿ����Ѿ��ҵ���һ���ַ���,����ѭ��
            pStr--;

        if (pStr == m_ptr->pData && *pStr == _ch)
            nLen = 0;    // ��ȱ�ʾ�Ѿ��������˵�һ���ַ�,���ҵ�һ���ַ�Ҳ�ǿո�,��ɾ����û�ַ���
        else
            nLen = pStr - m_ptr->pData + 1;    // �ҵ�λ�õ�ʱ���Ѿ������һ��,����Ҫ+1
        str_base ret = str_base(m_ptr->pData, nLen);
        ret.Addref();
        return ret;
    }
#pragma endregion


    // ����ַ�, �ı����ִ���
#pragma region _rand_static

    // ȡ�ı����ִ���
    // _sub = ���ֵ��ı�
    // _sublen = �ı�����, �����ֵ����, _string ������\0��β
    // isCase = �Ƿ����ִ�Сд
    inline size_t GetStringCount(const_pointer _sub, const size_t _sublen = 0, bool isCase = true)
    {
        if (empty())return 0;
        return GetStringCount(m_ptr->pData, _sub, _sublen, isCase);
    }
    // ȡ�ı����ִ���, �˺��������� GetStringCount() ��ȫһ��
    // _sub = ���ֵ��ı�
    // _sublen = �ı�����, �����ֵ����, _string ������\0��β
    // isCase = �Ƿ����ִ�Сд
    inline size_t GetAppearCount(const_pointer _sub, const size_t _sublen = 0, bool isCase = true)const
    {
        if (empty())return 0;
        return GetStringCount(m_ptr->pData, _sub, _sublen, isCase);
    }

    // ȡ�ı����ִ���
    // _string = Դ�ı�
    // _sub = ���ֵ��ı�
    // _sublen = �ı�����, �����ֵ����, _string ������\0��β
    // isCase = �Ƿ����ִ�Сд
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

    // ȡ�ı����ִ���, �˺��������� GetStringCount() ��ȫһ��
    // _string = Դ�ı�
    // _sub = ���ֵ��ı�
    // _sublen = �ı�����, �����ֵ����, _string ������\0��β
    // isCase = �Ƿ����ִ�Сд
    static size_t GetAppearCount(const_pointer _string, const_pointer _sub, const size_t _sublen = 0, bool isCase = true)
    {
        return GetStringCount(_string, _sub, _sublen, isCase);
    }

    // ȡ����й�����, ����ǰ��Ҫ����srand()�������������
    static str_base randChinese(const size_t _count)
    {
        str_base str;
        if (_count == 0)return str;
        str.resize(_count * (2 / sizeof(value_type)));    // ansi����Ҫ��һ�����ֽ�

        LPBYTE p = (LPBYTE)str.data();
        for (size_t i = 0; i < _count; i++)
        {
            p[i * 2] = 0 - __rand(38, 80);
            p[i * 2 + 1] = 0 - __rand(38, 80);
        }
        str.Addref();
        return str;
    }
    // ȡָ������������ַ�, ����������, ���������ַ�, ��Сд��ĸ, ����,��Ҫ���ⲿ���� srand()
    // _mode = ��ȡģʽ, 1=����, 2=Сд��ĸ, 4=��д��ĸ, 8=�����ַ�, 16=�й�����(δʵ��), 32=����������־,��������ַ�(�����������ַ�)
    // ��Ҫ��������λ�������, Ĭ��Ϊ1, ֻ��������
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

        // ���˿��ܴ��ݹ�����û�б�־, û�о�����Ϊֻȡ����
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


    // ȡ�������ת���ı�, ȡָ����Χ�ڵ�����, ��Χ���ֵΪ max - min = 32767, ����ǰ��Ҫ����srand()�������������
    // min = ���������Сֵ
    // max = ����������ֵ
    static str_base randNumber(const int min = 0, const int max = 0)
    {
        str_base str;
        size_t _count = 20;
        const value_type tmpStr[] = { '%','d','\0' };
        str.Format(20, tmpStr, __rand(min, max));
        str.Addref();
        return str;
    }
    // ȡ�������, ȡָ����Χ�ڵ�����, ��Χ���ֵΪ max - min = 32767, ��ָ����Χ���min��max��ֵΪ0, ��ָ����Χ��ֵ��������, ָ����Χ������������Χ��
    // ����ǰ��Ҫ���� srand() �������������
    // _count = ȡ������
    // mode = ѡ��ģʽ, 0=��˫, 1=��, ����=˫
    // min = ���������Сֵ
    // max = ����������ֵ
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

    // ȡ�������, ����ǰ��Ҫ����srand()�������������
    static str_base randSurname()
    {
#define _var_bjx_str_l(quote) L##quote      // r_winnt
#define _var_bjx_str    "��Ǯ����" "����֣��" "�������" "������" "��������" "����ʩ��" "�ײ��ϻ�"\
                        "��κ�ս�" "��л����" "��ˮ���" "�����˸�" "�ɷ�����" "³Τ����" "��ﻨ��"\
                        "����Ԭ��" "ۺ��ʷ��" "�����Ѧ" "�׺�����" "�����ޱ�" "��������" "����ʱ��"\
                        "Ƥ���뿵" "����Ԫ��" "����ƽ��" "��������" "Ҧ��տ��" "��ë���" "�ױ����"\
                        "�Ʒ��ɴ�" "̸��é��" "�ܼ�����" "��ף����" "��������" "ϯ����ǿ" "��·¦Σ"\
                        "��ͯ�չ�" "÷ʢ�ֵ�" "��������" "���Ĳ���" "�������" "����֧��" "�ù�¬Ī"\
                        "�·�����" "�ɽ�Ӧ��" "�����ڵ�" "��������" "������ʯ" "�޼�ť��" "�����ϻ�"\
                        "��½����" "�����ڻ�" "�����ҷ�" "���ഢ��" "��������" "���θ���" "�ڽ��͹�"\
                        "����ɽ��" "�������" "ȫۭ����" "��������" "�����ﱩ" "��������" "�������"\
                        "��ղ����" "Ҷ��˾��" "۬�輻��" "ӡ�ް׻�" "��ۢ�Ӷ�" "���̼���" "׿������"\
                        "��������" "���ܲ�˫" "��ݷ����" "̷������" "�������" "Ƚ��۪Ӻ" "ȴ�ɣ��"\
                        "�ţ��ͨ" "�����༽" "����ũ��" "��ׯ�̲�" "���ֳ�Ľ" "����ϰ��" "��������"\
                        "��������" "��������" "�Ӻⲽ��" "�������" "���Ŀܹ�" "»�ڶ�ŷ" "�����ε"\
                        "Խ��¡ʦ" "��������" "��������" "��������" "���Ŀ���" "��ɳؿ��" "����ᳲ"\
                        "�������" "�󾣺���" "��Ȩ����" "�滸��"

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


    // ����ת��, �ӱ��ַ�����ת������������
#pragma region _a2w_w2a_a2u_u2a_u2w_w2u
    // ת���ַ���, ԭʼ�ַ�����Unicode�� ���ؿ��ı�
    str_base<char> w2a(int cp = 936)const
    {
        if (!m_ptr || sizeof(value_type) == 1)return str_base<char>();
        LPSTR p = UnicodeToAnsi((LPWSTR)m_ptr->pData, m_ptr->len, cp);
        str_base<char> sz(p, lstrlenA(p));
        delete[] p;
        sz.Addref();
        return sz;
    }
    // ת���ַ���, ԭʼ�ַ�����Unicode�� ���ؿ��ı�
    str_base<char> w2u(int cp = CP_UTF8)const
    {
        if (!m_ptr || sizeof(value_type) == 1)return str_base<char>();
        LPSTR p = UnicodeToAnsi((LPWSTR)m_ptr->pData, m_ptr->len, cp);
        str_base<char> sz(p, lstrlenA(p));
        delete[] p;
        sz.Addref();
        return sz;
    }
    // ת���ַ���, ԭʼ�ַ���Unicode�� ���ؿ��ı�
    str_base<wchar_t> a2w(int cp = 936)const
    {
        if (!m_ptr || sizeof(value_type) == 2)return str_base<wchar_t>();
        LPWSTR p = AnsiToUnicode((LPSTR)m_ptr->pData, m_ptr->len, cp);
        str_base<wchar_t> sz(p, lstrlenW(p));
        delete[] p;
        sz.Addref();
        return sz;
    }

    // ת���ַ���, ԭʼ�ַ���Unicode�� ���ؿ��ı�
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


    // ȡ��ǰ�ַ�������,������������־
    inline size_t size()const           { return m_ptr ? m_ptr->len : 0; }
    // ȡ��ǰ�ַ�������������, ���ַ�Ϊ��λ
    inline size_t bufSize()const        { return m_ptr ? m_ptr->bufferLen : 0; }
    // ȡ��ǰ�ַ�������,������������־, �˳�Ա������size()��ͬ
    inline size_t length()const         { return m_ptr ? m_ptr->len : 0; }
    // ȡ��ǰ�ַ����ĵ�ַ,���صĵ�ַֻ�ɶ�,����д
    inline const_pointer c_str()const   { return m_ptr ? m_ptr->pData : 0; }
    // ��ȡ��ǰ�ַ��������޸ĵĵ�ַ
    inline pointer GetPtr()const        { return m_ptr ? m_ptr->pData : 0; }
    // ��ȡ��ǰ�ַ��������޸ĵĵ�ַ
    inline pointer data()const          { return m_ptr ? m_ptr->pData : 0; }
    // ��ȡ��ǰ�ַ�����β��ַ, ָ������ַ�, ����ַ���Ϊ��, �򷵻�0
    inline const_pointer rdata()const   { return m_ptr ? m_ptr->pData + m_ptr->len : 0; }
    // ��ȡ��ǰ�ַ�����β��ַ, ָ������ַ�, ����ַ���Ϊ��, �򷵻�0
    inline const_pointer rc_str()const  { return rdata(); }



    // ���ַ���������һ���µ��ڴ�ռ�,��Ҫ�Լ����ñ������free()�ͷ�, �����ʼλ�ô��ڳ�������ʼλ����Ϊ0, ��ǰ�ַ���δ��ʼ��ʱ����0
    // _off = ��ʼ����λ��
    // _count = ���Ƶ��ַ���, ansi��Ϊ�ֽ���
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

    // ����һ�����ü���, �ɹ��������ü���, ʧ�ܷ���0, δ��ʼ������0
    // ��֪����;������ʹ�øú���, ���Ӻ�����ͷ����β��ܳɹ��ͷŸ��ַ���, ���ͷ����ξ�й©��
    // һ���ڷ�������ַ���ʱ����һ������, ���������ͷ�ʱ����ַ������ᱻ�ͷ�, ����һ��������ͷŵĲ���
    // ֻҪ�������������, ��ô��������Ƹ�����һ������ʱ, ��ֻ��ǳ�㸴��
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
    // ����ָ��, ����ʱ�����ͷŸ�ָ��, �����Ҫ�ͷ������ obj.free()
    // ֻ�ܸ��ӱ���.data(), GetPtr() ���ص�ֵ, ��������ֵ�����
    // ����ԭ�ַ�������, ���Ե��� Attach() ���и���, ���ԭ�ַ���Ϊ��, �򷵻�0
    // ������һ�����ü���
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

    // ����ָ���ַ���������, ������һ��������־,����ֻ��Ҫ�����ַ���ʵ�ʳ��ȾͿ�����
    // ��ʹ��ʱ������ñ������ free() �ͷ�
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

    // �ڲ�ʹ��, ȡ�ַ�������, ���·��仺����, �ָ�, ��ʽ��, �Ƚ�

#pragma region __inside_static_private
    // �ڲ�ʹ��, ֱ���޸� m_ptr
    // ���·���STRMEMORYDATA::m_str�ṹ�ڴ�, ���ڴ�´��ԭ�ڴ������, ���ú󲻻��޸��ַ�������
    // ����������³ߴ縳ֵ
    // ԭ�����ַ���Ϊ��ʱ�������ڴ�
    // ԭ�����ַ�����Ϊ��ʱ���ݻ���������������Ҫ��Ҫ���·����С
    // size = �µ��ı���������С, ���ú���޸ĵ�ǰ�ַ�����������С, �ַ������Ȳ��ı�
    // isClear = �Ƿ�����ڴ�����, �˲���Ϊ trueʱ����ַ��������޸�Ϊ0
    pointer realloc(size_t size, bool isClear = false)
    {
        size_t len = size + 1 + sizeof(STRMEMORYDATA);
        LPSTRMEMORYDATA pData = 0;
        if (m_ptr == 0)        // ԭ�ַ����ǿյ�, ����������
        {
            pData = (LPSTRMEMORYDATA)alloc(len);
            pData->Addref = 1;
            pData->bufferLen = size + 1;
            //pData->len = size;
            pData->pData = (pointer)(((LPBYTE)pData) + sizeof(STRMEMORYDATA));
            m_ptr = pData;
        }
        else if (size + 1 <= m_ptr->bufferLen)  // ԭ���ݲ�Ϊ��, �жϻ���������, ����»��������ȱȾɻ���������С, ����������
        {
            // ���޸��ַ�������
            //if (m_ptr->len < size)
            //    m_ptr->len = size;              // ԭ�ַ�������С�ڵ�ǰ��������ֽ�, ����Ϊ������ĳ���
            if (isClear) clear();
        }
        else
        {
            pData = (LPSTRMEMORYDATA)alloc(len);
            pData->Addref = 1;
            if (!isClear)       // ������ڴ�ʱ��ԭ�������ݿ�������������
                memcpy(pData, m_ptr, (m_ptr->bufferLen + sizeof(STRMEMORYDATA)) * sizeof(value_type));

            pData->pData = (pointer)(((LPBYTE)pData) + sizeof(STRMEMORYDATA));

            free(m_ptr);
            m_ptr = pData;    // �ͷ�ԭ��ַ, �����¸�ֵ
            m_ptr->bufferLen = size + 1;    // �»�������С
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
    // Unicodeתansi, ���صĽ����Ҫ���� delete[] �ͷ�
    inline static char* UnicodeToAnsi(const wchar_t* const unicode, size_t len = 0, int cp = 936)
    {
        return charset::UnicodeToAnsi(unicode, len, cp);
    }

    // ansiתUnicode, ���صĽ����Ҫ���� delete[] �ͷ�
    inline static wchar_t* AnsiToUnicode(const char* const ansi, size_t len = 0, int cp = 936)
    {
        return charset::AnsiToUnicode(ansi, len, cp);
    }

    // unicodeתUTF8, ���صĽ����Ҫ���� delete[] �ͷ�
    inline static char* UnicodeToUtf8(const wchar_t* const unicode, size_t len = 0)
    {
        return charset::UnicodeToUtf8(unicode, len);
    }

    // UTF8תunicode, ���صĽ����Ҫ���� delete[] �ͷ�
    inline static wchar_t* Utf8ToUnicode(const char* const utf8, size_t len = 0)
    {
        return charset::Utf8ToUnicode(utf8, len);
    }

    // UTF8תansi, ���صĽ����Ҫ���� delete[] �ͷ�
    inline static char* Utf8ToAnsi(const char* const utf8, size_t len = 0)
    {
        return charset::Utf8ToAnsi(utf8, len);
    }

    // ansiתUTF8, ���صĽ����Ҫ���� delete[] �ͷ�
    inline static char* AnsiToUtf8(const char* const ansi, size_t len = 0)
    {
        return charset::AnsiToUtf8(ansi, len);
    }

    // Unicodeתansi
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

    // ansiתUnicode
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
    // ansiתUTF-8
    inline static str_base<char> (A2U)(LPCSTR str, int len = 0)
    {
        str_base<wchar_t> ws = (A2W)(str, len);
        str_base<char>ret = (W2A)(ws.c_str(), len, CP_UTF8);
        ret.Addref();
        return ret;
    }
    // UTF-8תansi
    inline static str_base<char> (U2A)(LPCSTR str, int len = 0)
    {
        str_base<wchar_t> ws = (A2W)(str, len, CP_UTF8);
        str_base<char>ret = (W2A)(ws.c_str(), len);
        ret.Addref();
        return ret;
    }
    // UTF-8תUnicode
    inline static str_base<wchar_t> (U2W)(LPCSTR str, int len = 0)
    {
        str_base<wchar_t>ret = (A2W)(str, len, CP_UTF8);
        ret.Addref();
        return ret;
    }
    // UnicodeתUTF-8
    inline static str_base<char> (W2U)(LPCWSTR str, int len = 0)
    {
        str_base<char>ret = (W2A)(str, len, CP_UTF8);
        ret.Addref();
        return ret;
    }
    // ansiתOLE
    inline static str_base<wchar_t> (A2O)(LPCSTR str, int len = 0)
    {
        str_base<wchar_t>ret = (A2W)(str, len, CP_ACP);
        ret.Addref();
        return ret;
    }
    // OLEתansi
    inline static str_base<char> (O2A)(LPCWSTR str, int len = 0)
    {
        str_base<char>ret = (W2A)(str, len, CP_ACP);
        ret.Addref();
        return ret;
    }
    // ���ַ���ת��Сд, _off=��ʼλ��, _count=ת�����ַ���, �����滻���ַ���
    // _string = ��ת�����ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
    inline static str_base tolower(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base ret = tolower(_string.c_str(), _string.size(), _off, _count);
        ret.Addref();
        return ret;
    }

    // ���ַ���ת��Сд, _off=��ʼλ��, _count=ת�����ַ���, �����滻���ַ���
    // _string = ��ת�����ַ���
    // _strlen = ��ת���ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
    inline static str_base tolower(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base sRet;
        if (!_string || _count == 0)
            return sRet;
        tolowerEx(sRet, _string, _strlen, _off, _count);
        sRet.Addref();
        return sRet;
    }
    

    // ���ַ���ת��Сд, _off=��ʼλ��, _count=ת�����ַ���, �����滻���ַ���
    // _string = ��ת�����ַ���, ������浽����
    // _strlen = ��ת���ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
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
        if (pos + len > strLen)    // ��ʼλ��+ת�����ַ��� > ���ַ���
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


    // �ѵ�ǰ�ַ���ת�ɴ�д, _off=��ʼλ��, _count=ת�����ַ���, �����滻���ַ���
    // _string = ��ת�����ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
    inline static str_base toupper(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base ret = toupper(_string.c_str(), _string.size(), _off, _count);
        ret.Addref();
        return ret;
    }
    // �ѵ�ǰ�ַ���ת�ɴ�д, _off=��ʼλ��, _count=ת�����ַ���, �����滻���ַ���
    // _string = ��ת�����ַ���
    // _strlen = ��ת���ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
    inline static str_base toupper(const_pointer _string, const size_t _strlen = 0, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base sRet;
        if (_string == 0 || _count == 0)
            return sRet;
        toupperEx(sRet, _string, _strlen, _off, _count);
        sRet.Addref();
        return sRet;
    }

    // �ѵ�ǰ�ַ���ת�ɴ�д, _off=��ʼλ��, _count=ת�����ַ���, �����滻���ַ���
    // _string = ��ת�����ַ���, ������浽����
    // _strlen = ��ת���ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
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
        if (pos + len > strLen)    // ��ʼλ��+ת�����ַ��� > ���ַ���
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
    // �ı�����, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ҳ���ַ���, ansi�����ڲ�ת��Unicode��ת��, ansi�治����ʹ��
    // _string = ��ת�����ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
    inline static str_base reverse(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        str_base ret(_string);
        reverseEx(ret.data(), ret.size(), _off, _count);
        ret.Addref();
        return ret;
    }
    // �ı�����, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ҳ���ַ���, ansi�����ڲ�ת��Unicode��ת��, ansi�治����ʹ��
    // _string = ��ת�����ַ���
    // _strlen = ��ת���ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
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

    // �ı�����, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ҳ���ַ���, ansi�����ڲ�ת��Unicode��ת��, ansi�治����ʹ��
    // _string = ��ת�����ַ���
    // _strlen = ��ת���ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ת�����ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻ؿ��ı�
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
        if (pos + len > strLen)    // ��ʼλ��+ת�����ַ��� > ���ַ���
        {
            len = strLen - pos;
        }

        LPWSTR wzStr = 0;
        if (sizeof(value_type) == 1)
            wzStr = AnsiToUnicode((LPCSTR)_string, strLen, 936);
        else
            wzStr = (LPWSTR)_string;    // ��Unicode��, Unicode��ֱ�Ӳ������������ַ���ָ��
        
        LPWSTR p = wzStr + pos;
        for (size_t i = 0; i < len / 2; i++)    // ����ȫ����Unicode������
        {
            size_t n = len - i - 1;
            p[i] ^= p[n];
            p[n] ^= p[i];
            p[i] ^= p[n];
        }

        if (sizeof(value_type) == 1)    // ansi��ת�����Ҫת����
        {
            LPSTR tmp = UnicodeToAnsi(wzStr, strLen);
            memcpy(_string, tmp, strlen(tmp) + 1);
            delete[] tmp;
        }
        return true;
    }

    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ����, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _string = ����ѯ���ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline static bool isNumber(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isNumber(_string.c_str(), _string.size(), _off, _count);
    }
    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ����, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _string = ����ѯ���ַ���
    // _strlen = ����ѯ�ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
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
        if (pos + len > strLen)    // ��ʼλ��+ת�����ַ��� > ���ַ���
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

    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�ΪСд��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _string = ����ѯ���ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline static bool isLower(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isLower(_string.c_str(), _string.size(), _off, _count);
    }
    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�ΪСд��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _string = ����ѯ���ַ���
    // _strlen = ����ѯ�ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
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
        if (pos + len > strLen)    // ��ʼλ��+ת�����ַ��� > ���ַ���
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

    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ��д��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _string = ����ѯ���ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline static bool isUpper(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isUpper(_string.c_str(), _string.size(), _off, _count);
    }
    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ��д��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _string = ����ѯ���ַ���
    // _strlen = ����ѯ�ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
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
        if (pos + len > strLen)    // ��ʼλ��+ת�����ַ��� > ���ַ���
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

    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _string = ����ѯ���ַ���
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
    inline static bool isLetter(const str_base& _string, const size_t _off = 0, const size_t _count = size_t(-1))
    {
        return isLetter(_string.c_str(), _string.size(), _off, _count);
    }
    // �жϵ�ǰ�ı�ָ��λ�ú��������ı��Ƿ�Ϊ��ĸ, _off=��ʼλ��, _count=ת�����ַ���, ansi��Ϊ�ֽ�
    // _string = ����ѯ���ַ���
    // _strlen = ����ѯ�ַ�������, �����ֵΪ0, ��_string������\0Ϊ��β
    // _off = ��ʼλ��, Ĭ��Ϊ0
    // _count = ��ѯ���ַ���, Ĭ��Ϊ�ı�����, Ϊ0�򷵻�false
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
        if (pos + len > strLen)    // ��ʼλ��+ת�����ַ��� > ���ַ���
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

    // �ָ��ַ���, ���س�Ա��
    // arr = ���շָ���ָ��, ����ΪNULL
    // _substr = �����ָ���ַ���, Ϊ���򰴻��� "\r\n"���зָ�
    // _count = Ҫ���ص����ı���Ա��, Ϊ0�򷵻ز����в���
    static size_t split(const_pointer str, strArr<value_type>* arr, const_pointer _substr, const size_t _count = size_t(-1))
    {
        return strtok(str, arr, _substr, _count);
    }

    // �ָ��ַ���, ���س�Ա��
    // arr = ���շָ���ָ��, ����ΪNULL
    // _substr = �����ָ���ַ���, Ϊ���򰴻��� "\r\n"���зָ�
    // _count = Ҫ���ص����ı���Ա��, Ϊ0�򷵻ز����в���
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
        p->arr = new size_t[arrCount];      // �����ŷָ���������, Ӧ�����㹻����, ���ַָ�Ҳ������
        memset(p->arr, 0, arrCount * sizeof(size_t));
        p->str = copy(str);                 // �»����������ַ���
        size_t n = 0;                       // �Ѵ�ŵĳ�Ա��
        pointer next_token = 0;
        pointer ptr = tstr_tok<value_type>(p->str, _substr, &next_token);
        
        while (ptr)
        {
            if (n > arrCount - 1)
            {
                arrCount += p->len;
                size_t* tmpArr = new size_t[arrCount];    // ������������, ���������ŷָ���������
                memset(tmpArr, 0, arrCount * sizeof(size_t));
                delete[] p->arr;
                p->arr = tmpArr;
            }

            p->arr[n++] = ptr - p->str;     // ��¼ƫ��, ��ʱ���ƹ��캯�������׸�����
            if (n >= _count)                // ���س�Ա��
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
        arr->Attach(p);    // �����������ͷŲ���
        return n;
    }

    // ����ָ���ַ���, �����ַ�����ַ, �˵�ַ���ܸ���, ������ʱ��Ҫ���� free() �ͷ�
    inline static pointer copy(const_pointer str, const size_t _size = 0)
    {
        size_t len = _size;
        if (len == 0)len = tstr_len(str);
        pointer p = alloc(len);
        memcpy(p, str, len * sizeof(value_type));
        return p;
    }
    // �ͷ��� copy ���ص��ַ���
    inline static void free(void* p)
    {
        if (p)
            ::free(p);
    }
    // �����ַ�, �����ҵ�λ��, û���ҵ����� str_base::npos
    // _off = ����λ��, Ĭ��Ϊ��ǰ�����
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

    // Ѱ���ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ��� str_base::npos
    // _substr    = Ѱ�ҵ��ı�
    // _off    = Ѱ�ҵ�λ��, str_base::npos = ��ͷ��ʼѰ��
    // _off    = Ѱ�ҵ�λ��
    // isCase    = �Ƿ����ִ�Сд,true=����,false=������
    inline static size_t find(const str_base& _str, const str_base& _substr, const size_t pos = 0, bool isCase = true)
    {
        return findEx(_str.c_str(), _substr.c_str(), _str.size(), _substr.size(), pos, isCase);
    }

    // Ѱ���ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ��� str_base::npos
    // _substr    = Ѱ�ҵ��ı�
    // _off    = Ѱ�ҵ�λ��, str_base::npos = ��ͷ��ʼѰ��
    // isCase    = �Ƿ����ִ�Сд,true=����,false=������
    inline static size_t find(const_pointer _str, const_pointer _substr, const size_t pos, bool isCase = true)
    {
        return findEx(_str, _substr, tstr_len(_str), tstr_len(_substr), pos, isCase);
    }
    // Ѱ���ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ��� str_base::npos
    // _substr = Ѱ�ҵ��ı�
    // _substrLen = Ѱ���ı��ĳ���, Ϊ0�� _substr������\0��β
    // _off    = Ѱ�ҵ�λ��
    // isCase    = �Ƿ����ִ�Сд,true=����,false=������
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

    // �����ַ�, �����ҵ�λ��, û���ҵ�����str_base::npos
    // _off = ����λ��, Ĭ��Ϊ��������
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

    // �����ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _str    = ��Ѱ�ҵ��ı�
    // _substr = Ѱ�ҵ��ı�
    // _off    = Ѱ�ҵ�λ��, str_base::npos = �ӽ�β��ʼѰ��
    // c    = �Ƿ����ִ�Сд,true=����,false=������
    inline static size_t rfind(const_pointer _str, const str_base& _substr, const size_t pos = size_t(-1), bool c = true)
    {
        return rfindEx(_str, _substr.c_str(), _substr.size(), pos, c);
    }
    // �����ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _substr = Ѱ�ҵ��ı�
    // _off    = Ѱ�ҵ�λ��, str_base::npos = �ӽ�β��ʼѰ��
    // c    = �Ƿ����ִ�Сд,true=����,false=������
    inline static size_t rfind(const_pointer _str, const_pointer _substr, const size_t pos = size_t(-1), bool c = true)
    {
        return rfindEx(_str, _substr, tstr_len(_substr), pos, c);
    }
    // �����ַ���,��һ���ַ�����Ѱ��һ���ַ���,�ɹ������ҵ�λ��,ʧ�ܷ���str_base::npos
    // _substr = Ѱ�ҵ��ı�
    // _strlen = Ѱ���ı��ĳ���, Ϊ0�� _substr������\0��β
    // _off    = Ѱ�ҵ�λ��, str_base::npos = �ӽ�β��ʼѰ��
    // c    = �Ƿ����ִ�Сд,true=����,false=������
    static size_t rfindEx(const_pointer _str, const_pointer _substr, const size_t _strlen, const size_t pos, bool c)
    {
        if (!_str)return str_base::npos;
        size_t strLen = _strlen;
        if (strLen == 0)strLen = tstr_len(_substr);
        size_t len = tstr_len(_str);

        size_t nSubLen = strLen; // Ҫ�������ַ�������
        if (len == 0 || nSubLen == 0 || nSubLen > len)return str_base::npos;

        size_t nStart = pos;    // ��ʼλ��
        size_t nEnd = len - nSubLen; // ���λ��

        if (nStart > len) nStart = nEnd; //Ѱ�ҵ�λ��С��0������Ѱ��
        if (nStart > nEnd) nStart = nEnd;

        const_pointer pStart = _str + nStart; // ָ�������ַ�����ĩβ

        while (pStart >= _str)    // �����ǰָ���λ�ô����ַ�������ʼλ��,��ѭ���ж�
        {
            bool bCmp = 0;
            if (c) //���ִ�Сд
                bCmp = tstr_ncmp(pStart, _substr, nSubLen) == 0;    // ���ִ�Сд
            else
                bCmp = tstr_nicmp(pStart, _substr, nSubLen) == 0;    // �����ִ�Сд

            if (bCmp)
            {
                nStart = pStart - _str;    // �ҵ��ַ���,��ǰָ��λ�� - �ַ�����ʼλ�� = �ҵ�λ��
                return nStart;
            }
            pStart--;
        }
        return str_base::npos;        // û�ҵ����� str_base::npos
    }


    // ȡ�ı����
    // str      = Դ�ַ���
    // _strlen  = �ַ�������, Ϊ�˺ͷǾ�̬��������
    // count    = ȡ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�
    inline static str_base left(const_pointer str, size_t _strlen, const size_t _count)
    {
        if (!str)return str_base();
        str_base ret;
        leftEx(ret, str, _strlen, _count);
        ret.Addref();
        return ret;
    }
    // ȡ�ı����
    // str      = Դ�ַ���
    // _strlen  = �ַ�������, Ϊ�˺ͷǾ�̬��������
    // count    = ȡ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�
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
    // ȡ�ı����,ȡָ���ַ�����ߵ��ı���
    // str      = Դ�ַ���
    // _string = ȡ����ַ�����ߵ��ı���,���ص��ı������������ַ���
    // _off = ��ʼ���Ҳ���1��λ��
    inline static str_base left(const str_base& str, const str_base& _string, const size_t _off = 0)
    {
        str_base ret = left(str.c_str(), _string.c_str(), _off);
        ret.Addref();
        return ret;
    }
    // ȡ�ı����,ȡָ���ַ�����ߵ��ı���
    // str      = Դ�ַ���
    // _string  = ȡ����ַ�����ߵ��ı���,���ص��ı������������ַ���
    // _off     = ��ʼ���Ҳ���1��λ��
    inline static str_base left(const_pointer str, const_pointer _string, const size_t _off = 0)
    {
        size_t count = str_base::find(str, _string, _off);
        if (count == str_base::npos)return str_base();

        str_base ret;
        leftEx(ret, str, 0, count);
        ret.Addref();
        return ret;
    }

    // ȡ�ı��ұ�
    // str      = Դ�ַ���
    // count    = ȡ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�
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
    // ȡ�ı��ұ�
    // ret      = ���ս���ַ���
    // str      = Դ�ַ���
    // count    = ȡ���ַ���,���ֽڵ�λΪ�ֽ�,UnicodeΪ�ַ�
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
    // ȡ�ı��ұ�,ȡָ���ַ����ұߵ��ı���
    // s    = ȡ����ַ����ұߵ��ı���,���ص��ı������������ַ���
    // b    = �Ƿ����������ַ���
    // _off = ��ʼ����λ��, Ĭ�ϴ���β������, 0Ϊ���ײ�����
    inline static str_base right(const str_base& str, const str_base& s, bool b = false, const size_t _off = size_t(-1))
    {
        str_base ret = right(str.c_str(), s.c_str(), b, _off);
        ret.Addref();
        return ret;
    }
    // ȡ�ı��ұ�,ȡָ���ַ����ұߵ��ı���
    // s    = ȡ����ַ����ұߵ��ı���,���ص��ı������������ַ���
    // b    = �Ƿ����������ַ���
    // _off = ��ʼ����λ��, Ĭ�ϴ���β������, 0Ϊ���ײ�����
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


    // ���ı��滻
    // s    = ���滻���ַ���
    // sub    = �滻��
    // _off    = �滻����ʼλ��,Ĭ��Ϊ0
    // count    = �滻����,<= 0 = �������ֵ
    // c    = �Ƿ����ִ�Сд
    inline static str_base replace(const_pointer _str, const str_base& s, const str_base& sub, const size_t _off = 0, const size_t count = size_t(-1), bool c = true)
    {
        str_base ret;
        replaceEx(ret, _str, s.c_str(), sub.c_str(), s.size(), sub.size(), _off, count, c);
        ret.Addref();
        return ret;
    }

    // �ַ��滻, ����ı�ԭ���ַ�������, ����޸�Ϊ�ַ�0, �ڲ��ַ������Ȳ����
    // _ch = ���滻���ַ���
    // _subch = �滻��
    // _off = �滻����ʼλ��,Ĭ��Ϊ0, ��ʼλ�ô����ַ�������ʱ����FALSSE
    // count = �滻����, Ϊ0�򲻲���
    inline static str_base replace(const_pointer _str, const value_type _ch, const value_type _subch, const size_t _off = 0, size_t count = size_t(-1))
    {
        str_base ret;
        replaceEx(ret, _str, _ch, _subch, _off, count);
        ret.Addref();
        return ret;
    }
    // �ַ��滻, ����ı�ԭ���ַ�������, ����޸�Ϊ�ַ�0, �ڲ��ַ������Ȳ����
    // ret      = ���ս���ַ���
    // _ch      = ���滻���ַ���
    // _subch   = �滻��
    // _off     = �滻����ʼλ��,Ĭ��Ϊ0, ��ʼλ�ô����ַ�������ʱ����FALSSE
    // count    = �滻����, Ϊ0�򲻲���
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
    // ���ı��滻
    // _string = ���滻���ַ���
    // _substr = �滻��
    // _off    = �滻����ʼλ��,Ĭ��Ϊ0
    // count    = �滻����,<= 0 = �������ֵ
    // c    = �Ƿ����ִ�Сд
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
    
    // ���ı��滻
    // _string = ���滻���ַ���
    // _substr = �滻��
    // _strlen = _string�ĳ���, �����ֵΪ0, ��_string����Ϊ\0��β
    // _sublen = _substr�ĳ���, �����ֵΪ0, ��_substr����Ϊ\0��β
    // _off    = �滻����ʼλ��,Ĭ��Ϊ0
    // count    = �滻����,<= 0 = �������ֵ
    // c    = �Ƿ����ִ�Сд
    inline static str_base replace(const_pointer _str, const_pointer _string, const_pointer _substr, const size_t _strlen, const size_t _sublen, const size_t _off, size_t count, bool c)
    {
        str_base ret;
        replaceEx(ret, _str, _string, _substr, _strlen, _sublen, _off, count, c);
        ret.Addref();
        return ret;
    }

    // ���ı��滻
    // ret      = �ο��滻����ı�
    // _str     = �滻��Դ�ı�
    // _string  = ���滻���ַ���
    // _substr  = �滻��
    // _strlen  = _string�ĳ���, �����ֵΪ0, ��_string����Ϊ\0��β
    // _sublen  = _substr�ĳ���, �����ֵΪ0, ��_substr����Ϊ\0��β
    // _off     = �滻����ʼλ��,Ĭ��Ϊ0
    // count    = �滻����,<= 0 = �������ֵ
    // isCase   = �Ƿ����ִ�Сд
    static bool replaceEx(str_base& ret, const_pointer _str, const_pointer _string, const_pointer _substr, size_t _strlen, size_t _sublen, size_t _off, size_t count, bool isCase)
    {
        if (!_str || !_string)return false; // Դ�ַ����ͱ��滻���ַ�����Ϊ��, ������

        size_t _destLen = tstr_len(_str);  // Դ�ַ����ַ�������
        if (_destLen == 0) return false;    // Դ�ı�Ϊ��

        size_t strLen = _strlen;            // ��Ҫ�滻���ı�����
        if (strLen == 0)
            strLen = tstr_len(_string);
        if (strLen == 0) return false;      // Ҫ�滻���ı�Ϊ��

        size_t subLen = _sublen;            // �滻�ɵ��ı�����, �滻�ɵ��ı�����Ϊ��, Ϊ�մ���ɾ��
        if (subLen == 0 && _substr)
            subLen = tstr_len(_substr);


        size_t nStart = _off;               // �滻����ʼλ��
        size_t nRplCount = (count == 0) ? size_t(-1) : count;    // �滻����

        size_t nEnd = _destLen - strLen;
        if (nStart > nEnd + 1 || nRplCount <= 0 || nStart < 0)    //Ѱ�ҵ��ı����ڿ�ʼѰ��λ�� �� û���滻����
            return false;


        str_base_AutoFreePtr __freeptr;
        autoFree_copy(_str, ret.__get_this(), __freeptr);
        {
            size_t bufferLen = subLen - strLen; // �滻�ɵ��ı����� - �����滻���ı�����
            int cmpLen = (int)bufferLen;
            // Ԥ�⻺��������, ���Ϊ �ַ������� * (�滻�ɵ��ı����� - �����滻���ı�����), ����������״̬, һ�������
            if (cmpLen < 0)         bufferLen = _destLen;       // �����Ҫ�Ļ�������СΪ ���滻�ı��ĳ���, �����������û��һ��ƥ��, �滻���ԭ�ַ���һ����
            else if (cmpLen > 0)    bufferLen *= _destLen;      // �����볤��, ����ÿ���ַ����滻���㹻���
            else                    bufferLen = _destLen;       // �����滻���ı����Ⱥ��滻�ɵ��ı�����һ��, �滻�󲻻�ı䳤��
            if (bufferLen > _destLen * 2 + _STR_BUFFER_SIZE)    // Ϊ�����˷��ڴ�, ��������, ������ÿ���ַ������滻
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
                if (_substr && subLen > 0)    // �����滻���ı�
                    ret.append(_substr, subLen);

                pStart += strLen;
                pSrc = pStart; //����һ��;
                if (++nFind == nRplCount)
                    break;
            }
            else
            {
                pStart = pStart + ((*pStart < 0) ? 2 : 1);
            }
        }

        if (pSrc == _str)   // ѭ�����һ�����ݺ�ԭʼ�ı�����һ��, �Ǿ���û���滻�κ��ı�
        {
            ret.assign(_str, _destLen);
        }
        else if (pStart > pEnd && pSrc < pEnd) // ö�ٵ����һ���ַ���
        {
            ret.append(pSrc, tstr_len(pSrc));
        }
        else if (((size_t)(pStart - _str)) <= _destLen)  // pStart��ÿ��Ѱ������, ���С���ı�����, ��ʾѭ�������˺��滹���ַ�
        {
            ret.append(pSrc, tstr_len(pSrc));
        }
        return true;
    }

    // ����ֵ���ǧ��λ�ָ�
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
    
    // ��˫���ȸ�����
    inline static double        stod(const str_base<char>& val)     { return stod(val.c_str()); }
    inline static double        stod(const str_base<wchar_t>& val)  { return stod(val.c_str()); }
    inline static double        stod(const char* const val)         { return (!val || !val[0]) ? 0 : atof(val); }
    inline static double        stod(const wchar_t* const val)      { wchar_t* _Eptr; return (!val || !val[0]) ? 0 : wcstod(val, &_Eptr); }
    // �������ȸ�����
    static float                stof(const str_base<char>& val)     { return stof(val.c_str()); }
    static float                stof(const str_base<wchar_t>& val)  { return stof(val.c_str()); }
    inline static float         stof(const char* const val)         { return (!val || !val[0]) ? 0 : atof(val); }
    inline static float         stof(const wchar_t* const val)      { wchar_t* _Eptr; return (!val || !val[0]) ? 0 : (float)wcstod(val, &_Eptr); }
    // ����������
    inline static long double   stold(const str_base<char>& val)    { return stold(val.c_str()); }
    inline static long double   stold(const str_base<wchar_t>& val) { return stold(val.c_str()); }
    inline static long double   stold(const char* const val)        { char* _Eptr; return (!val || !val[0]) ? 0 : strtold(val, &_Eptr); }
    inline static long double   stold(const wchar_t* const val)     { wchar_t* _Eptr; return (!val || !val[0]) ? 0 : wcstold(val, &_Eptr);  }

    // ������ int
    inline static int           stoi(const str_base<char>& val)     { return stoi(val.c_str()); }
    inline static int           stoi(const str_base<wchar_t>& val)  { return stoi(val.c_str()); }
    inline static int           stoi(const char* const val)         { return (!val || !val[0]) ? 0 : atoi(val); }
    inline static int           stoi(const wchar_t* const val)      { return (!val || !val[0]) ? 0 : _wtoi(val); }
    // ������ long
    inline static long          stol(const str_base<char>& val)     { return stol(val.c_str()); }
    inline static long          stol(const str_base<wchar_t>& val)  { return stol(val.c_str()); }
    inline static long          stol(const char* const val)         { return (!val || !val[0]) ? 0 : atol(val); }
    inline static long          stol(const wchar_t* const val)      { return (!val || !val[0]) ? 0 : _wtol(val); }
    // �������� long long
    inline static __int64       stoll(const str_base<char>& val)    { return stoll(val.c_str()); }
    inline static __int64       stoll(const str_base<wchar_t>& val) { return stoll(val.c_str()); }
    inline static __int64       stoll(const char* const val)        { return (!val || !val[0]) ? 0 : atoll(val); }
    inline static __int64       stoll(const wchar_t* const val)     { return (!val || !val[0]) ? 0 : _wtoll(val); }


public:
    // BJ ����ת�� base64
    // base64����, ���ر���������
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

    // base64����, ���ؽ���������, ���������ݲ�һ�����ı�, size() ���ǽ�������ݵĳ���
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