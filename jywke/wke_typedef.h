#pragma once
#include <tstr.h>
#include <elib/lib2.h>
#include <elib/lang.h>
#include <elib/fnshare.h>
#include "wke_cmd_typedef.h"
#include "wke_head_base.h"
#include <CStringBuffer.h>


// �����, ��λ���ֽ�
typedef CStringBufferA  BUFFER_POOL, * PBUFFER_POOL;

extern HINSTANCE WKE_NAME(0, g_hInst);
#define g_hInst WKE_NAME(0, g_hInst)

#define FREEARR_ARG(_index) if(pArgInf[_index].m_ppAryData) NotifySys(NRS_FREE_ARY, (DWORD)pArgInf[_index].m_dtDataType, (DWORD)* (pArgInf[_index].m_ppAryData))


#define SDT_TYPE_WKE_TB         MAKELONG (0x01, 0) // WKE_���
#define SDT_TYPE_WKE_AJAX       MAKELONG (0x02, 0) // ajax
#define SDT_TYPE_WKE_JS         MAKELONG (0x03, 0) // Javascript
#define SDT_TYPE_WKE_SPECISL    MAKELONG (0x04, 0) // ���⹦��
#define SDT_TYPE_WKE_WEBKIT     MAKELONG (0x05, 0) // ����Web����� ���
#define SDT_TYPE_TYPERECT       MAKELONG (0x06, 0) // ����
#define SDT_TYPE_MEMBUFFER      MAKELONG (0x07, 0) // �ڴ滺����
#define SDT_TYPE_POSTELEMENT    MAKELONG (0x08, 0) // POSTԪ��
#define SDT_TYPE_POSTELEMENTS   MAKELONG (0x09, 0) // POSTԪ�ؼ�
#define SDT_TYPE_POPWND         MAKELONG (0x0A, 0) // �������ڲ���


#ifndef __E_STATIC_LIB
extern LIB_DATA_TYPE_INFO g_DataType_wke_global_var[];  // ������������
extern int g_DataType_wke_global_var_count;             // �������ͳ�Ա��

extern LIB_CONST_INFO g_ConstInfo_wke_global_var[];     // ������Ϣ����
extern int g_ConstInfo_wke_global_var_count;            // ������Ϣ��Ա��

extern CMD_INFO g_cmdInfo_wke_global_var[];             // ������Ϣ����
extern int g_cmdInfo_wke_global_var_count;              // ������Ϣ��Ա��

#endif

#define __query(_a, _b) ( ((_a) & (_b)) == (_b)  )
#define _DBG_BREAK_TOSTR1(_num) #_num
#define _DBG_BREAK_TOSTR2(_num) _DBG_BREAK_TOSTR1(_num)
#define _DBG_BREAK_MSG(_s) { MessageBoxA(0, "����: " _DBG_BREAK_TOSTR2(__LINE__) "\r\n�ļ�: " __FILE__ \
                                "\r\n��������Ϣ�����ͼ����006\r\n\r\n���ȷ������򽫴����쳣, ���û�е�����, ���������"\
                                , _s, 0); __debugbreak(); }


// ��������������ʵ�ֵĺ�������
#define WKE_DEF_CMD(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    extern "C" void WKE_NAME(_index, _szEgName)(PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf);

WKE_DEF(WKE_DEF_CMD)    // ����ʵ������

// ͨ��id��ȡhUnit, �������������Բο����ذ󶨵�����
HUNIT GethUnitFromId(DWORD dwWinFormID, DWORD dwUnitID, PVOID * pRet = 0);
// ͨ��������ĵ�һ����Ա��ȡhUnit, �ڶ����������Բο����ذ󶨵�����
HUNIT GethUnitFromArgInf(PMDATA_INF pInf, PVOID * pRet = 0);
// ��hUnit���ȡ�󶨵�����
PVOID GetDataFromHunit(HUNIT hUnit);
// ��������, ���û�о�ֱ�ӷ���
PVOID UpdateDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, PVOID pData);
// ������, ���ID����ͬ��, �ǻ�� hUnit�� pData ���ǽ�ȥ, ������½�һ������
PVOID SetDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, PVOID pData);

// ����Web�����  �µ������������
EXTERN_C PFN_INTERFACE WINAPI wke_GetInterface_webkit(INT nInterfaceNO);
bool init_webkit();


// ���� ����web����� �������
void head_dtType_Webkit(LIB_DATA_TYPE_INFO & dtType);

// ���� �������� �������
void head_dtType_NewWnd(LIB_DATA_TYPE_INFO & dtType);

// ���ݴ��ڴ���CWndָ��
inline DWORD CreateUnit(PWKE_STRUCT_BASE data)
{
    // ÿ�ζ�����һ��, �����������ǰ�Ѿ��д������ٵ�������
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

// ��ʼ��data�ṹ, ���û�д���, �Ǿ�newһ��, ����Ѿ�����, �Ǿʹ�map���data��Ӧ�Ĵ���ɾ��, �����Ƿ�new��data
template<typename T>
inline bool InitDataEx(T*& data)
{
    if ( !data )
    {
        // �������´����Ĵ��ڲų�ʼ��������Ϣ, �Ѿ������Ĵ������Զ��м�¼��
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

// ������д�뻺����, �ڲ����ж��Ƿ�Խ��, Խ������·����ڴ�
// д���, pBuffer������nSize���ֽ�, ����д����ֽ���
inline int write_data(_str & buffer, LPCVOID pData, int nSize)
{
    if ( nSize == 0 )
        return 0;
#ifdef _DEBUG
    if ( nSize < 0 )
        _DBG_BREAK_MSG("д������, ���ݳߴ�С��0");
#endif
    buffer.append((LPCSTR)pData, nSize);
    return nSize;
}
// д������
inline int write_int32(_str & buffer, int number)
{
    return write_data(buffer, &number, sizeof(number));
}
// ���ַ���д�뻺����, ���ѵ�ַ����, �������ӵ��ֽ���
inline int write_str_A(_str & buffer, LPCSTR pstr, size_t strLen = 0)
{
    if ( strLen == 0 )
        strLen = strlen(pstr);
    size_t len = strLen;  // �������������ֽ�

    write_data(buffer, pstr, len);   // ������ַ���д��, ������������־
    buffer.push_back(0);    // д�������־, 1���ֽ�0
    len++;
    return len;
}
// ���ַ���д�뻺����, ���ѵ�ַ����, �������ӵ��ֽ���
inline int write_str_W(_str& buffer, LPCWSTR pstr, size_t strLen = 0)
{
    if ( !pstr )pstr = L"";
    if ( strLen == 0 )
        strLen = wcslen(pstr);
    size_t len = strLen * sizeof(wchar_t);  // �������������ֽ�

    write_data(buffer, pstr, len);   // ������ַ���д��, ������������־
    buffer.push_back(0);    // д�������־, �����ֽ�, ����0
    buffer.push_back(0);

    len += sizeof(wchar_t);
}


inline int read_int32(LPBYTE & buf)
{
    int ret = ( (LPINT)buf )[0];
    buf += sizeof(int);
    return ret;
}
// ��ȡ�ַ���, �����ַ�����ַ, ͬʱ��ַ����, retSize���յ�ַ���Ӷ��ٸ��ֽ�
inline LPCSTR read_str_A(LPBYTE& buf, int* retSize = 0)
{
    LPCSTR str = (LPCSTR)buf;
    size_t len = strlen(str) + 1;
    buf += len;
    if ( retSize )*retSize = (int)len;
    return str;
}
// ��ȡ�ַ���, �����ַ�����ַ, ͬʱ��ַ����, retSize���յ�ַ���Ӷ��ٸ��ֽ�
inline LPCWSTR read_str_W(LPBYTE& buf, int* retSize = 0)
{
    LPCWSTR str = (LPCWSTR)buf;
    size_t len = wcslen(str) * sizeof(wchar_t) + sizeof(wchar_t);
    buf += len;
    if ( retSize )*retSize = (int)len;
    return str;
}

// ���������д���ı�, ���ԭ�����ı��㹻���, �Ǿͼ������, ����������ռ���, �����Ƿ����·������ڴ�
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
        return false;   // �������ǿ��ַ���, ������
    if ( wcscmp(text, pstr) == 0 )
        return false;   // �����ַ���һ��, ������

    size_t len1 = wcslen(pstr);
    size_t len2 = wcslen(text);
    if ( len1 >= len2 )
    {
        // �����, ֱ�Ӵ�Ž�ȥ
        memcpy(pstr, text, len2 * sizeof(wchar_t) + sizeof(wchar_t));
        return false;
    }
    else
    {
        // �������, �����µĻ��������
        *ppszText = buf->AddStringW(text, len2);
        return true;
    }
}
// ���������д���ı�, ���ԭ�����ı��㹻���, �Ǿͼ������, ����������ռ���, �����Ƿ����·������ڴ�
inline bool _set_buf_text(CStringBufferA* buf, LPCSTR* ppszText, LPCSTR text)
{
    LPSTR pstr = (LPSTR)*ppszText;
    if ( !pstr[0] && !text[0] )
        return false;
    size_t len1 = strlen(pstr);
    size_t len2 = strlen(text);
    if ( len1 >= len2 )
    {
        // �����, ֱ�Ӵ�Ž�ȥ
        memcpy(pstr, text, len2 * sizeof(char) + sizeof(char));
        return false;
    }
    else
    {
        // �������, �����µĻ��������
        *ppszText = buf->AddStringA(text, len2);
        return true;
    }
}
