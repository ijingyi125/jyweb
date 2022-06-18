#pragma once
#define _CHARSET_BEGIN namespace charset {
#define _CHARSET_END   }
_CHARSET_BEGIN

// Unicodeתansi, ���صĽ����Ҫ���� delete[] �ͷ�
inline char* UnicodeToAnsi(const wchar_t* const unicode, size_t len = 0, int cp = 936)
{
    if (!unicode)return 0;
    if (len <= 0)len = wcslen(unicode);
    if (len <= 0)return 0;
    int aLen = WideCharToMultiByte(cp, 0, unicode, (int)len, 0, 0, 0, 0) + 1;
    if (aLen < 1) return 0;

    char* szStr = new char[aLen];
    memset(szStr, 0, aLen);
    WideCharToMultiByte(cp, 0, unicode, (int)len, szStr, aLen, 0, 0);
    return szStr;
}

// ansiתUnicode, ���صĽ����Ҫ���� delete[] �ͷ�
inline wchar_t* AnsiToUnicode(const char* const ansi, size_t len = 0, int cp = 936)
{
    if (!ansi)return 0;
    if (len <= 0)len = strlen(ansi);
    if (len <= 0)return 0;

    int uLen = MultiByteToWideChar(cp, 0, ansi, (int)len, NULL, 0) + 1;
    if (uLen < 1) return 0;

    wchar_t* wzStr = new wchar_t[uLen];
    memset(wzStr, 0, uLen * sizeof(wchar_t));
    uLen = MultiByteToWideChar(cp, 0, ansi, (int)len, wzStr, uLen);
    return wzStr;
}

// unicodeתUTF8, ���صĽ����Ҫ���� delete[] �ͷ�
inline char* UnicodeToUtf8(const wchar_t* const str, size_t len = 0)
{
    return UnicodeToAnsi(str, len, CP_UTF8);
}

// UTF8תunicode, ���صĽ����Ҫ���� delete[] �ͷ�
inline wchar_t* Utf8ToUnicode(const char* const str, size_t len = 0)
{
    return AnsiToUnicode(str, len, CP_UTF8);
}

// UTF8תansi, ���صĽ����Ҫ���� delete[] �ͷ�
inline char* Utf8ToAnsi(const char* const utf8, size_t len = 0)
{
    // �Ȱ�utf8�ı�ת��unicode, �ڰ�unicodeת��ansi
    if (!utf8)return 0;
    wchar_t* unicode = Utf8ToUnicode(utf8, len);
    if (!unicode) return 0;

    char* ansi = UnicodeToAnsi(unicode, wcslen(unicode));
    delete[] unicode;
    return ansi;
}

// ansiתUTF8, ���صĽ����Ҫ���� delete[] �ͷ�
inline char* AnsiToUtf8(const char* const ansi, size_t len = 0)
{
    // �Ȱ�ansi�ı�ת��unicode, �ڰ�unicodeת��utf8
    if (!ansi)return 0;
    wchar_t* unicode = AnsiToUnicode(ansi, len);
    if (!unicode) return 0;

    char* utf8 = UnicodeToAnsi(unicode, wcslen(unicode), CP_UTF8);
    delete[] unicode;
    return utf8;
}

_CHARSET_END