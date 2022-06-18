/*
    ��Ȩ������
    ���ļ���ȨΪ������������������, ����Ȩ����������������������֧�ֿ�, ��ֹ���������κγ��ϡ�
*/

//����Ԫ��ʹ��MFC��, �ɹ���д��ƽ̨��֧�ֿ��Ǵ������֧�ֿ�ʹ��

#ifndef __FN_SHARE_H
#define __FN_SHARE_H

#include "lib2.h"
typedef INT(cdecl* PFN_ON_SYS_NOTIFY) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
#ifndef _private
#define _private  //��ʶΪֻ˽��
#endif




// ��������ide������Ϣ
#define NotifySys __LIB2_DEFFUNNAME(jy_NotifySys)
INT WINAPI NotifySys(INT nMsg, DWORD dwParam1, DWORD dwParam2);


// ���������������ڴ�, ��λΪ�ֽ�
#define ealloc __LIB2_DEFFUNNAME(jy_ealloc)
inline void* ealloc(int size)
{
    void* pMem = (void*)NotifySys(NRS_MALLOC, size, 0);
    memset(pMem, 0, size);
    return (void*)pMem;
}

// �ͷŴ���������������ڴ�
#define efree __LIB2_DEFFUNNAME(jy_efree)
inline void efree(void* p)
{
    NotifySys(NRS_MFREE, (DWORD)p, 0);
}



// �Ƿ�Ϊ���԰�, ���ֵ��֧�ֿ����ʱȡһ��
#define isDebugVer __LIB2_DEFFUNNAME(jy_GetVer)
bool isDebugVer(int* r); // ��ȡ��ǰ�汾�Ƿ�Ϊ�����


// ��������ideͨѶ�ӳ���
#define ProcessNotifyLib __LIB2_DEFFUNNAME(jy_ProcessNotifyLib)
INT WINAPI ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2);


// �û��Լ������֪ͨ����, �û���ʹ�����´��뼴�ɱ�֤���޸ı��ļ�, ���ﵽ��ʱ����ϵͳͨѶ��Ŀ�ģ�
#define SetUserSysNotify __LIB2_DEFFUNNAME(jy_NotifySys)
PFN_NOTIFY_SYS WINAPI SetUserSysNotify(PFN_NOTIFY_SYS pfn);


// �����ı�, ��ʹ��ʱ��Ҫ���� efree() ���ͷ�
// nTextLen����ָ���ı����ֵĳ���(������������)
// ���Ϊ0, ��ȡps��ȫ������
#define CloneTextData __LIB2_DEFFUNNAME(jy_CloneTextData)
inline char* CloneTextData(const char* ps, INT nTextLen = 0)
{
    if (ps == NULL || *ps == '\0') return NULL;
    if (nTextLen == 0) nTextLen = lstrlenA(ps);
    if (nTextLen == 0) return NULL;
    char* pd = (char*)ealloc(nTextLen + 1);
    memcpy(pd, ps, nTextLen);
    pd[nTextLen] = '\0';
    return pd;
}

// �����ֽڼ�, ���������Ը�ʽ���ֽڼ�,1ά����
#define CloneBinData __LIB2_DEFFUNNAME(jy_CloneBinData)
inline LPBYTE CloneBinData(LPBYTE pData, INT nDataSize)
{
    if (nDataSize == 0)
        return NULL;

    LPBYTE pd = (LPBYTE)ealloc(sizeof(INT) * 2 + nDataSize);
    *(LPINT)pd = 1;
    *(LPINT)(pd + sizeof(INT)) = nDataSize;
    memcpy(pd + sizeof(INT) * 2, pData, nDataSize);
    return pd;
}

// ����W���ı�, ��ʹ��ʱ��Ҫ���� efree() ���ͷ�
// nTextLen����ָ���ı����ֵĳ���(������������)
// ���Ϊ0, ��ȡps��ȫ������
#define CloneTextDataW __LIB2_DEFFUNNAME(jy_CloneTextDataW)
inline LPBYTE CloneTextDataW(LPCWSTR ps, INT nTextLen = 0)
{
    if ( ps == NULL || *ps == '\0' ) return NULL;
    if ( nTextLen == 0 ) nTextLen = (int)wcslen(ps);
    if ( nTextLen == 0 ) return NULL;

    int size = nTextLen * sizeof(wchar_t) + sizeof(wchar_t) + 8;
    LPINT pd = (LPINT)ealloc(size);
    pd[0] = 1;
    pd[1] = size - 8;
    memcpy(&pd[2], ps, nTextLen * sizeof(wchar_t));
    return (LPBYTE)pd;
}



// ������������ݲ����׵�ַ����Ա��Ŀ�� ���صĵ�ַ����Ҫ�����ͷ�
#define GetAryElementInf __LIB2_DEFFUNNAME(jy_GetAryElementInf)
inline LPBYTE GetAryElementInf(void* pAryData, LPINT pnElementCount)
{
    if (pnElementCount)*pnElementCount = 0;
    if (!pAryData)return 0;
    LPINT pnData = (LPINT)pAryData;
    INT nArys = *pnData++;  // ȡ��ά����
    // �����Ա��Ŀ��
    INT nElementCount = 1;
    while (nArys > 0)
    {
        nElementCount *= *pnData++;
        nArys--;
    }

    if (pnElementCount)
        *pnElementCount = nElementCount;
    return (LPBYTE)pnData;
}


// ���ֽڼ��������ȡ�ֽڼ�����, ���ص��ֽڼ���2���ֽڱ���\0\0,��������ַ���,���Բ�ʹ�����, ��ʹ��ʱ��Ҫ���� efree() ���ͷ�
#define GetBinData __LIB2_DEFFUNNAME(jy_GetBinData)
inline LPBYTE GetBinData(LPBYTE pBin, int* len = 0)
{
    if (len)*len = 0;
    if (!pBin)return 0;
    int dwLen = 0;
    LPBYTE pData = GetAryElementInf(pBin, &dwLen);
    LPBYTE pMem = (LPBYTE)ealloc(dwLen + 2);
    memcpy(pMem, pData, dwLen);
    if (len)*len = dwLen + 2;
    return pMem;
}

// ȡ���������͵����
#define GetDataTypeType __LIB2_DEFFUNNAME(jy_GetDataTypeType)
inline INT GetDataTypeType(DATA_TYPE dtDataType)
{
#define DTT_IS_NULL_DATA_TYPE   0
#define DTT_IS_SYS_DATA_TYPE    1
#define DTT_IS_USER_DATA_TYPE   2
#define DTT_IS_LIB_DATA_TYPE    3
    if (dtDataType == _SDT_NULL)
        return DTT_IS_NULL_DATA_TYPE;

    DWORD dw = dtDataType & 0xC0000000;
    return dw == DTM_SYS_DATA_TYPE_MASK ? DTT_IS_SYS_DATA_TYPE :
        dw == DTM_USER_DATA_TYPE_MASK ? DTT_IS_USER_DATA_TYPE :
        DTT_IS_LIB_DATA_TYPE;
}

// ��������, ���ݵڶ��������������ֽ���, Ĭ��Ϊ4�ֽ�
#define allocArray __LIB2_DEFFUNNAME(jy_allocArray)
inline LPBYTE allocArray(int nCount, int elementSize = sizeof(int))
{
    if (elementSize <= 0 || elementSize > 8)elementSize = 4;
    int len = (2 * sizeof(int)) + elementSize * nCount;
    int* p = (int*)ealloc(len);
    p[0] = 1;  // ����ά����   
    p[1] = nCount;
    return (LPBYTE)p;
}

//�����ױ���汾����Ĭ�ϵĵȿ�����
#define wkeSetLogfont_CompileLanVer __LIB2_DEFFUNNAME(jy_wkeSetLogfont_CompileLanVer)
inline void wkeSetLogfont_CompileLanVer(LPLOGFONTA pLogfont) //�����ױ���汾����Ĭ�ϵĵȿ�����
{
    ::GetObjectA(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONTA), pLogfont);
#ifndef __COMPILE_LANG_VER
    //  #error *** lang.h must be imported!
#endif
//#pragma setlocale(_T("en"))
#if (__COMPILE_LANG_VER == __BIG5_LANG_VER)
    /* �ڷ����Windows��DEFAULT_GUI_FONT�е��������ǡ��¼����w��, 
       ���������Ǳ���, ���Ա���ǿ�Ƹ�Ϊ�������w����
       ����Ϊ�����wBIG5���롣Ϊ�˱��ⱻת�������滻, ���������ָ�ʽд�������С� */
#if _MSC_VER < 1201
    strcpy(pLogfont->lfFaceName, "\xB2\xD3\xA9\xFA\xC5\xE9");
#else
    strcpy_s(pLogfont->lfFaceName, sizeof(pLogfont->lfFaceName) / sizeof(pLogfont->lfFaceName[0]), "\xB2\xD3\xA9\xFA\xC5\xE9");
#endif
#elif (__COMPILE_LANG_VER == __SJIS_JP_LANG_VER)
    /* �����İ�Windows��DEFAULT_GUI_FONT�е��������ǡ�MS UI Gothic��, 
       ���������Ǳ���, ���Ա���ǿ�Ƹ�Ϊ��MS Gothic����*/
    pLogfont->lfCharSet = SHIFTJIS_CHARSET;
    strcat(pLogfont->lfFaceName, "MS Gothic");
#elif (__COMPILE_LANG_VER == __ENGLISH_LANG_VER)
    strcat(pLogfont->lfFaceName, "Courier New");
#endif
}








//������liigo���

/*
//!!! ���º�����������������֮��Աȫ��ΪINT����(��ͬ��ռ��4���ֽ�)
//index: 0..*/

inline _private void* _GetPointerByIndex(void* pBase, int index)
{
    return (void*)((INT)pBase + index * sizeof(INT));
}

inline _private INT _GetIntByIndex(void* pBase, INT index)
{
    return *((INT*)_GetPointerByIndex(pBase, index));
}

inline _private void _SetIntByIndex(void* pBase, INT index, INT value)
{
    *((INT*)_GetPointerByIndex(pBase, index)) = value;
}

inline INT _GetIntByIndex(PMDATA_INF pArgInf, INT index)
{
    return _GetIntByIndex(pArgInf->m_pCompoundData, index);
}

inline void SetIntByIndex(PMDATA_INF pArgInf, INT index, INT value)
{
    _SetIntByIndex(pArgInf->m_pCompoundData, index, value);
}

inline void* GetPointerByIndex(PMDATA_INF pArgInf, INT index)
{
    return _GetPointerByIndex(pArgInf->m_pCompoundData, index);
}






//������Ϣռλ��
#define CMD_INFO_MASK_1 \
        {\
        /*ccname*/    _T("???"),\
        /*egname*/    _T("???"),\
        /*explain*/    NULL,\
        /*category*/-1,\
        /*state*/    CT_IS_HIDED,\
        /*ret*/        _SDT_NULL,\
        /*reserved*/0,\
        /*level*/    LVL_SIMPLE,\
        /*bmp inx*/    0,\
        /*bmp num*/    0,\
        /*ArgCount*/0,\
        /*arg lp*/    NULL,\
        }
#define CMD_INFO_MASK_2        CMD_INFO_MASK_1,CMD_INFO_MASK_1
#define CMD_INFO_MASK_3        CMD_INFO_MASK_2,CMD_INFO_MASK_1
#define CMD_INFO_MASK_4        CMD_INFO_MASK_3,CMD_INFO_MASK_1
#define CMD_INFO_MASK_5        CMD_INFO_MASK_4,CMD_INFO_MASK_1
#define CMD_INFO_MASK_6        CMD_INFO_MASK_5,CMD_INFO_MASK_1
#define CMD_INFO_MASK_7        CMD_INFO_MASK_6,CMD_INFO_MASK_1
#define CMD_INFO_MASK_8        CMD_INFO_MASK_7,CMD_INFO_MASK_1
#define CMD_INFO_MASK_9        CMD_INFO_MASK_8,CMD_INFO_MASK_1
#define CMD_INFO_MASK_10    CMD_INFO_MASK_9,CMD_INFO_MASK_1

#define MASK_CMD_INFO_1        CMD_INFO_MASK_1
#define MASK_CMD_INFO_2        CMD_INFO_MASK_2
#define MASK_CMD_INFO_3        CMD_INFO_MASK_3
#define MASK_CMD_INFO_4        CMD_INFO_MASK_4
#define MASK_CMD_INFO_5        CMD_INFO_MASK_5
#define MASK_CMD_INFO_6        CMD_INFO_MASK_6
#define MASK_CMD_INFO_7        CMD_INFO_MASK_7
#define MASK_CMD_INFO_8        CMD_INFO_MASK_8
#define MASK_CMD_INFO_9        CMD_INFO_MASK_9
#define MASK_CMD_INFO_10    CMD_INFO_MASK_10

//��������ռλ��
#define DATATYPE_INFO_MASK_1 \
    {\
    /*m_szName*/            _T(""),\
    /*m_szEgName*/            _T(""),\
    /*m_szExplain*/            NULL,\
    /*m_nCmdCount*/            0,\
    /*m_pnCmdsIndex*/        NULL,\
    /*m_dwState*/            NULL,\
    /*m_dwUnitBmpID*/        0,\
    /*m_nEventCount*/        0,\
    /*m_pEventBegin*/        NULL,\
    /*m_nPropertyCount*/    0,\
    /*m_pPropertyBegin*/    NULL,\
    /*m_pfnGetInterface*/    NULL,\
    /*m_nElementCount*/        0,\
    /*m_pElementBegin*/        NULL,\
    }
#define DATATYPE_INFO_MASK_2    DATATYPE_INFO_MASK_1,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_3    DATATYPE_INFO_MASK_2,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_4    DATATYPE_INFO_MASK_3,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_5    DATATYPE_INFO_MASK_4,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_6    DATATYPE_INFO_MASK_5,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_7    DATATYPE_INFO_MASK_6,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_8    DATATYPE_INFO_MASK_7,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_9    DATATYPE_INFO_MASK_8,DATATYPE_INFO_MASK_1
#define DATATYPE_INFO_MASK_10    DATATYPE_INFO_MASK_9,DATATYPE_INFO_MASK_1

#define MASK_DATATYPE_INFO_1    DATATYPE_INFO_MASK_1
#define MASK_DATATYPE_INFO_2    DATATYPE_INFO_MASK_2
#define MASK_DATATYPE_INFO_3    DATATYPE_INFO_MASK_3
#define MASK_DATATYPE_INFO_4    DATATYPE_INFO_MASK_4
#define MASK_DATATYPE_INFO_5    DATATYPE_INFO_MASK_5
#define MASK_DATATYPE_INFO_6    DATATYPE_INFO_MASK_6
#define MASK_DATATYPE_INFO_7    DATATYPE_INFO_MASK_7
#define MASK_DATATYPE_INFO_8    DATATYPE_INFO_MASK_8
#define MASK_DATATYPE_INFO_9    DATATYPE_INFO_MASK_9
#define MASK_DATATYPE_INFO_10    DATATYPE_INFO_MASK_10

//�������ͳ�Առλ��
#define DATATYPE_ELEMENT_MASK_1 \
    {\
/*m_dtType*/    SDT_INT,\
/*m_pArySpec*/    NULL,\
/*m_szName*/    _WT(""),\
/*m_szEgName*/    _WT(""),\
/*m_szExplain*/    NULL,\
/*m_dwState*/    LES_HIDED,\
/*m_nDefault*/    0,\
    }

#define DATATYPE_ELEMENT_MASK_2        DATATYPE_ELEMENT_MASK_1,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_3        DATATYPE_ELEMENT_MASK_2,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_4        DATATYPE_ELEMENT_MASK_3,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_5        DATATYPE_ELEMENT_MASK_4,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_6        DATATYPE_ELEMENT_MASK_5,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_7        DATATYPE_ELEMENT_MASK_6,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_8        DATATYPE_ELEMENT_MASK_7,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_9        DATATYPE_ELEMENT_MASK_8,DATATYPE_ELEMENT_MASK_1
#define DATATYPE_ELEMENT_MASK_10    DATATYPE_ELEMENT_MASK_9,DATATYPE_ELEMENT_MASK_1

#define MASK_DATATYPE_ELEMENT_1        DATATYPE_ELEMENT_MASK_1
#define MASK_DATATYPE_ELEMENT_2        DATATYPE_ELEMENT_MASK_2
#define MASK_DATATYPE_ELEMENT_3        DATATYPE_ELEMENT_MASK_3
#define MASK_DATATYPE_ELEMENT_4        DATATYPE_ELEMENT_MASK_4
#define MASK_DATATYPE_ELEMENT_5        DATATYPE_ELEMENT_MASK_5
#define MASK_DATATYPE_ELEMENT_6        DATATYPE_ELEMENT_MASK_6
#define MASK_DATATYPE_ELEMENT_7        DATATYPE_ELEMENT_MASK_7
#define MASK_DATATYPE_ELEMENT_8        DATATYPE_ELEMENT_MASK_8
#define MASK_DATATYPE_ELEMENT_9        DATATYPE_ELEMENT_MASK_9
#define MASK_DATATYPE_ELEMENT_10    DATATYPE_ELEMENT_MASK_10

//�հ׺���ָ��ռλ��
#define NULL_1     NULL
#define NULL_2     NULL,NULL
#define NULL_3     NULL_2,NULL_1
#define NULL_4     NULL_3,NULL_1
#define NULL_5     NULL_4,NULL_1
#define NULL_6     NULL_5,NULL_1
#define NULL_7     NULL_6,NULL_1
#define NULL_8     NULL_7,NULL_1
#define NULL_9     NULL_8,NULL_1
#define NULL_10     NULL_9,NULL_1

#define    MASK_NULL_1        NULL_1
#define MASK_NULL_2        NULL_2
#define MASK_NULL_3        NULL_3
#define MASK_NULL_4        NULL_4
#define MASK_NULL_5        NULL_5
#define MASK_NULL_6        NULL_6
#define MASK_NULL_7        NULL_7
#define MASK_NULL_8        NULL_8
#define MASK_NULL_9        NULL_9
#define MASK_NULL_10    NULL_10

#endif //__FN_SHARE_H
