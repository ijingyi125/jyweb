#pragma once
#if _MSC_VER > 1200
#define __NO_EXCEPT noexcept
#else
#define __NO_EXCEPT throw()
#endif
namespace mystruct
{
    template<typename _char> struct hash_key
    {
    private:
        //typedef char _char;
        typedef _char* _PSTR;
        typedef const _char* _CPSTR;
        _PSTR m_buffer;
        size_t m_len;
        inline void free()
        {
            if (m_buffer)
                delete m_buffer;
            m_buffer = 0;
            m_len = 0;
        }
        inline hash_key* GetThis() { return this; }
        inline static size_t _strlen(_CPSTR s)
        {
            if (!s)return 0;
            size_t len = 0;
            while (*s++)
                ++len;
            return len;
        }
    private:
#if _MSC_VER > 1200
    #if defined(_WIN64)
        static constexpr size_t _FNV_offset_basis1 = 14695981039346656037ULL;
    #else
        static constexpr size_t _FNV_offset_basis1 = 2166136261U;
    #endif
#else
        static const size_t _FNV_offset_basis1;
#endif

    public:
        template <class _Kty>
        inline static size_t _Hash_representation_(const _Kty& _Keyval) __NO_EXCEPT {
            //return _Fnv1a_append_value(_FNV_offset_basis1, _Keyval);
            return 0;
        }

        //template <class _Kty>
        //inline static size_t _Fnv1a_append_value_(
        //    const size_t _Val, const _Kty& _Keyval) __NO_EXCEPT {
        //    static_assert(is_trivial_v<_Kty>, "Only trivial types can be directly hashed.");
        //    return _Fnv1a_append_bytes_(_Val, &reinterpret_cast<const unsigned char&>(_Keyval), sizeof(_Kty));
        //}

        //inline static size_t _Fnv1a_append_bytes_(size_t _Val, const unsigned char* const _First,
        //    const size_t _Count) __NO_EXCEPT {
        //    for (size_t _Idx = 0; _Idx < _Count; ++_Idx) {
        //        _Val ^= static_cast<size_t>(_First[_Idx]);
        //        _Val *= _FNV_prime;
        //    }

        //    return _Val;
        //}
    public:
        hash_key() :m_buffer(0), m_len(0) { ; }
        ~hash_key() { free(); }
        hash_key(_CPSTR str) :m_buffer(0), m_len(0)
        {
            operator=(str);
        }
        //inline operator _PSTR () const __NO_EXCEPT { return m_buffer; }
        inline operator _CPSTR () const __NO_EXCEPT { return m_buffer; }
        hash_key(const hash_key& obj) :m_buffer(0), m_len(0)
        {
            if (!obj.m_buffer || obj.m_len == 0)return;
            m_len = obj.m_len;
            m_buffer = new _char[m_len + 1];
            memcpy(m_buffer, obj.m_buffer, m_len * sizeof(_char) + sizeof(_char));
        }
#if _MSC_VER > 1200
        hash_key(hash_key&& obj) __NO_EXCEPT :m_buffer(0), m_len(0)
        {
            m_len = obj.m_len;
            m_buffer = obj.m_buffer;
            obj.m_buffer = 0;
            obj.m_len = 0;
        }
        inline hash_key& operator=(hash_key&& str) __NO_EXCEPT
        {
            if (this == str.GetThis())return *this;
            if (!m_buffer)  // 赋值时本对象没有初始化, 直接把传递进来的对象指针赋值给本对象
            {
                m_buffer = str.m_buffer;
                m_len = str.m_len;
                str.m_buffer = 0;
                str.m_len = 0;
                return *this;
            }

            // 走到这表示赋值时本对象以及初始化, 对比一下哪个缓冲区大, 哪个大用哪个
            if (!str.m_buffer || str.m_len == 0)
            {
                // 传入的对象没有初始化, 给本对象清0
                m_buffer[0] = 0;
                m_len = 0;
                return *this;
            }

            // 走到这传入的对象和本对象都不为空
            if (m_len > str.m_len)  // 本对象的缓冲区比较大
            {
                memcpy(m_buffer, str.m_buffer, str.m_len * sizeof(_char) + sizeof(_char));
                m_len = str.m_len;  // 传入的对象缓冲区比较小, 则把传入对象的内容拷贝到本对象, 不处理传入的对象
                return *this;
            }
            _PSTR ptr = str.m_buffer;
            size_t len = str.m_len;
            str.m_buffer = m_buffer;
            str.m_len = m_len;
            m_buffer = ptr;
            m_len = len;
            return *this;
        }
#endif
        inline _CPSTR c_str() const  { return m_buffer; }
        inline hash_key& operator=(const _CPSTR str)
        {
            if (!str)
            {
                if (!m_buffer)
                    return *this;
                m_buffer[0] = 0;
                m_len = 0;
                return *this;
            }
            size_t len = _strlen(str);
            if (len < m_len)
            {
                memcpy(m_buffer, str, len * sizeof(_char) + sizeof(_char));
                m_len = len;
                return *this;
            }
            if (m_buffer)
                delete m_buffer;
            m_len = len;
            m_buffer = new _char[m_len + 1];
            memcpy(m_buffer, str, m_len * sizeof(_char) + sizeof(_char));
            return *this;
        }
        inline hash_key& operator=(const hash_key& str)
        {
            return operator=(str.m_buffer);
        }

    public:

        inline static size_t HashFun(_CPSTR key)
        {
#if 0
            if (!key)return 0;
            const size_t BitsInUnsignedInt = (size_t)(4 * 8);
            const size_t ThreeQuarters = (size_t)((BitsInUnsignedInt * 3) / 4);
            const size_t OneEighth = (size_t)(BitsInUnsignedInt / 8);
            const size_t HighBits = (size_t)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
            size_t hash = 0;
            size_t test = 0;
            const size_t len = _strlen(key);
            for (size_t i = 0; i < len; i++)
            {
                hash = (hash << OneEighth) + key[i];
                test = (hash & HighBits);
                if (test != 0)
                {
                    hash = ((hash ^ (test >> ThreeQuarters))& (~HighBits));
            }
        }
            return hash;
#else
            size_t hash = 0;
            size_t x = 0;
            const size_t len = _strlen(key);
            for (size_t i = 0; i < len; i++)
            {
                hash = (hash << 4) + key[i];
                if ((x = hash & 0xF0000000L) != 0)
                {
                    hash ^= (x >> 24);
                }
                hash &= ~x;
            }
            return hash;
#endif
        }
    };
#if _MSC_VER < 1201
#if defined(_WIN64)
    template<typename _char>const size_t hash_key<_char>::_FNV_offset_basis1 = 14695981039346656037ULL;
#else
    template<typename _char>const size_t hash_key<_char>::_FNV_offset_basis1 = 2166136261U;
#endif
#endif

    template<typename T> struct struct_hashfun {};
    template<typename T> struct struct_equalkey {};

    template<> struct struct_hashfun<const void*> {
        inline size_t operator()(const void* key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };

    template<> struct struct_hashfun<void*> {
        inline size_t operator()(void* key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };

    template<> struct struct_hashfun<const char*> {
        inline size_t operator()(const char* key) const __NO_EXCEPT {
            return (size_t)hash_key<char>::HashFun(key);
        }
    };

    template<> struct struct_hashfun<char*> {
        inline size_t operator()(char* key) const __NO_EXCEPT {
            return (size_t)hash_key<char>::HashFun(key);
        }
    };

    template<> struct struct_hashfun<const wchar_t*> {
        inline size_t operator()(const wchar_t* key) const __NO_EXCEPT {
            return (size_t)hash_key<wchar_t>::HashFun(key);
        }
    };

    template<> struct struct_hashfun<wchar_t*> {
        inline size_t operator()(const wchar_t* key) const __NO_EXCEPT {
            return (size_t)hash_key<wchar_t>::HashFun(key);
        }
    };

    template<> struct struct_hashfun<hash_key<wchar_t> > {
        inline size_t operator()(const hash_key<wchar_t>& key) const __NO_EXCEPT {
            return (size_t)hash_key<wchar_t>::HashFun(key.c_str());
        }
    };

    template<> struct struct_hashfun<hash_key<char> > {
        inline size_t operator()(const hash_key<char>& key) const __NO_EXCEPT {
            return (size_t)hash_key<char>::HashFun(key.c_str());
        }
    };

    template<> struct struct_hashfun<short> {
        inline size_t operator()(short key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };

    template<> struct struct_hashfun<unsigned short> {
        inline size_t operator()(unsigned short key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };

    template<> struct struct_hashfun<int> {
        inline size_t operator()(int key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };

    template<> struct struct_hashfun<long> {
        inline size_t operator()(long key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };

    template<> struct struct_hashfun<unsigned long> {
        inline size_t operator()(unsigned long key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };

    template<> struct struct_hashfun<__int64> {
        inline size_t operator()(__int64 key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };

    template<> struct struct_hashfun<unsigned __int64> {
        inline size_t operator()(unsigned __int64 key) const __NO_EXCEPT {
            return (size_t)key;
        }
    };


    template<> struct struct_hashfun<float> {
        inline size_t operator()(float key) const __NO_EXCEPT {
            return (size_t)hash_key<char>::_Hash_representation_(key == 0.0F ? 0.0F : key);
        }
    };

    template<> struct struct_hashfun<double> {
        inline size_t operator()(double key) const __NO_EXCEPT {
            return (size_t)hash_key<char>::_Hash_representation_(key == 0.0F ? 0.0F : key);
        }
    };

    template<> struct struct_hashfun<long double> {
        inline size_t operator()(long double key) const __NO_EXCEPT {
            return (size_t)hash_key<char>::_Hash_representation_(key == 0.0F ? 0.0F : key);
        }
    };





    template<> struct struct_equalkey<const void*> {
        inline bool operator()(const void* key1, const void* key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<void*> {
        inline bool operator()(void* key1, void* key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<const char*> {
        inline bool operator()(const char* key1, const char* key2) const __NO_EXCEPT {
            return strcmp(key1, key2) == 0;
        }
    };

    template<> struct struct_equalkey<char*> {
        inline bool operator()(char* key1, char* key2) const __NO_EXCEPT {
            return strcmp(key1, key2) == 0;
        }
    };

    template<> struct struct_equalkey<const wchar_t*> {
        inline bool operator()(const wchar_t* key1, const wchar_t* key2) const __NO_EXCEPT {
            return wcscmp(key1, key2) == 0;
        }
    };

    template<> struct struct_equalkey<wchar_t*> {
        inline bool operator()(wchar_t* key1, wchar_t* key2) const __NO_EXCEPT {
            return wcscmp(key1, key2) == 0;
        }
    };

    template<> struct struct_equalkey<hash_key<wchar_t> > {
        inline bool operator()(const hash_key<wchar_t>& key1, const hash_key<wchar_t>& key2) const __NO_EXCEPT {
            return wcscmp(key1, key2) == 0;
        }
    };

    template<> struct struct_equalkey<hash_key<char> > {
        inline bool operator()(const hash_key<char>& key1, const hash_key<char>& key2) const __NO_EXCEPT {
            return strcmp(key1, key2) == 0;
        }
    };

    template<> struct struct_equalkey<short> {
        inline bool operator()(short key1, short key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<unsigned short> {
        inline bool operator()(unsigned short key1, unsigned short key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<int> {
        inline bool operator()(int key1, int key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<unsigned int> {
        inline bool operator()(unsigned int key1, unsigned int key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<long> {
        inline bool operator()(long key1, long key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<unsigned long> {
        inline bool operator()(unsigned long key1, unsigned long key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<__int64> {
        inline bool operator()(__int64 key1, __int64 key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<unsigned __int64> {
        inline bool operator()(unsigned __int64 key1, unsigned __int64 key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<float> {
        inline bool operator()(float key1, float key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<double> {
        inline bool operator()(double key1, double key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };

    template<> struct struct_equalkey<long double> {
        inline bool operator()(long double key1, long double key2) const __NO_EXCEPT {
            return key1 == key2;
        }
    };
}