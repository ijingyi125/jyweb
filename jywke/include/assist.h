#pragma once
#include <windows.h>
#include <wincrypt.h>
#include <tchar.h>
#include <tstr.h>
#if _MSC_VER < 1201
#include <assist/crypt_API.h>
#endif

// ��Ҫ����������� srand();
inline int rand(int min, int max) { return (rand() % (max - min + 1)) + min; }

inline BOOL GetRegValue(HKEY hKey, LPCWSTR path, LPCWSTR name, void* buffer, DWORD& len)
{
    HKEY _hKey;
    BOOL bRet = FALSE;
    int status = RegOpenKeyExW(hKey, path, 0, KEY_READ, &_hKey);
    if (ERROR_SUCCESS == status)
    {
        status = RegQueryValueExW(_hKey, name, 0, NULL, (LPBYTE)buffer, &len);
        if (ERROR_SUCCESS == status)
        {
            bRet = TRUE;
        }

        RegCloseKey(_hKey);
    }
    return bRet;
}

inline BOOL SetRegValue(HKEY hKey, LPCWSTR path, LPCWSTR name, const void* data, int dataLen)
{
    HKEY _hKey;
    BOOL bRet = FALSE;
    int status = RegOpenKeyExW(hKey, path, 0, KEY_SET_VALUE, &_hKey);
    if (ERROR_SUCCESS == status)
    {
        status = RegSetValueExW(_hKey, name, NULL, REG_BINARY, (LPBYTE)data, dataLen);
        if (ERROR_SUCCESS == status)
        {
            bRet = TRUE;
        }

        RegCloseKey(_hKey);
    }
    return bRet;
}

inline BOOL DeleteRegKey(HKEY hKey, LPCWSTR lpSubKey)
{
#if _MSC_VER < 1201
    return ERROR_SUCCESS == RegDeleteKeyW(hKey, lpSubKey);
#else
    return ERROR_SUCCESS == RegDeleteKeyExW(hKey, lpSubKey, KEY_WOW64_32KEY, 0);
#endif
}

inline BOOL GetMd5(LPBYTE pData, int size, wstr& MD5)
{
    MD5 = L"";
    if ( !pData || !size ) return false;
    HCRYPTPROV hProv = NULL;
    if (!CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))return FALSE;       //���CSP��һ����Կ�����ľ��

    HCRYPTPROV hHash = NULL;
    //��ʼ������������hash, ����������һ����CSP��hash������صľ��������������������    CryptHashData���á�

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))return FALSE;

    if (!CryptHashData(hHash, pData, size, 0))return FALSE;      //hash�ļ�  


    unsigned char* pbHash;
    DWORD dwHashLen = sizeof(DWORD);
    if (!CryptGetHashParam(hHash, HP_HASHVAL, NULL, &dwHashLen, 0))return FALSE; //��Ҳ��֪��ΪʲôҪ����������CryptGetHashParam, ����ǲ��յ�msdn       

    pbHash = (unsigned char*)malloc(dwHashLen);
    if (!pbHash)return FALSE;
    if (CryptGetHashParam(hHash, HP_HASHVAL, pbHash, &dwHashLen, 0))//���md5ֵ 
    {
        for (DWORD i = 0; i < dwHashLen; i++)         //���md5ֵ 
        {
            WCHAR str[3] = { 0 };
            unsigned char tmp = pbHash[i];
#if _MSC_VER < 1201
            swprintf(str, L"%02x", tmp);
#else
            swprintf_s(str, L"%02x", tmp);
#endif
            MD5 += str;
        }
    }

    //�ƺ���
    if (!CryptDestroyHash(hHash))return FALSE;          //����hash����  
    if (!CryptReleaseContext(hProv, 0))return FALSE;

    return TRUE;
}


inline void WaitForSingleObjectAndMsg_d(HANDLE hHandle)    // �ȴ��ź�
{
    while (TRUE)
    {
        DWORD result;
        MSG msg = { 0 };

        result = MsgWaitForMultipleObjects(1, &hHandle, FALSE, INFINITE, QS_ALLINPUT);

        if (result == (WAIT_OBJECT_0))break;    // HANDLE���������,��ʾ����յ��ź�
        if (result == WAIT_TIMEOUT)break;        // ��ʱ
        if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
            if (msg.message == WM_DESTROY || msg.message == WM_QUIT)
                return;
        }
    }
}

// ����_��ʱ
inline void WINAPI sleep(DWORD time)
{
    if (time <= 0)time = 1000;
#if _MSC_VER < 1201
    HANDLE hTime = CreateWaitableTimerW_d(NULL, FALSE, NULL);
    if (!hTime)return;
    LARGE_INTEGER d = { 0 };
    d.QuadPart = (LONGLONG)((LONGLONG)(-10) * (LONGLONG)time * (LONGLONG)1000);
    SetWaitableTimer_d(hTime, (LARGE_INTEGER_d*)&d, NULL, NULL, NULL, FALSE);
    WaitForSingleObjectAndMsg_d(hTime);
#else
    HANDLE hTime = CreateWaitableTimerW(NULL, FALSE, NULL);
    if (!hTime)return;
    LARGE_INTEGER d = { 0 };
    d.QuadPart = (LONGLONG)((LONGLONG)(-10) * (LONGLONG)time * (LONGLONG)1000);
    SetWaitableTimer(hTime, (LARGE_INTEGER*)&d, NULL, NULL, NULL, FALSE);
    WaitForSingleObjectAndMsg_d(hTime);
#endif

    CloseHandle(hTime);
}





inline BOOL SetClipboard(LPCSTR str, int size = -1)
{
    if (!str) return FALSE;
    if (size == -1)
        size = (int)(LONG_PTR)strlen(str);
    size_t len = size + 1;
    HGLOBAL hMem = GlobalAlloc(GHND, len);
    if (!hMem)
        return FALSE;
    void* p = GlobalLock(hMem);
    if (p)
    {
        memcpy(p, str, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        //GlobalFree(hMem);
        CloseClipboard();
    }
    return TRUE;
}
inline BOOL SetClipboard(LPCWSTR str, int size = -1)
{
    if (!str) return FALSE;
    if (size == -1)
        size = (int)(LONG_PTR)wcslen(str);
    size_t len = size + 1;
    HGLOBAL hMem = GlobalAlloc(GHND, len * 2);
    if (!hMem)
        return FALSE;
    void* p = GlobalLock(hMem);
    if (p)
    {
        memcpy(p, str, len * 2);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_UNICODETEXT, hMem);
        //GlobalFree(hMem);
        CloseClipboard();
    }
    return TRUE;
}
inline wstr GetClipboard()
{
    OpenClipboard(0);

    if (IsClipboardFormatAvailable(CF_UNICODETEXT))
    {
        HANDLE hMem = GetClipboardData(CF_UNICODETEXT);
        void* lpData = GlobalLock(hMem);
        SIZE_T nSize = GlobalSize(hMem);
        if (lpData)
        {
            wstr ret(nSize);
            memcpy(ret.data(), lpData, nSize);
            GlobalUnlock(hMem);
            CloseClipboard();
            ret.Addref();
            return ret;
        }
    }
    CloseClipboard();
    return wstr();
}
inline _str GetClipboardA()
{
    wstr w = GetClipboard();
    _str a = w.w2a();
    a.Addref();
    return a;
}
inline BOOL zjjbwb(LPCSTR str, int size = -1) { return SetClipboard(str, size); }
inline BOOL zjjbwb(LPCWSTR str, int size = -1) { return SetClipboard(str, size); }

