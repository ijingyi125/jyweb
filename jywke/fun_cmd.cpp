#include "wke_typedef.h"
#include "wke_webkit_header.h"
#include <CPUusage.h>

// ��������������ʵ�ֲ���




// ���ø�ʽ: _SDT_NULL wke_����dll·��, ����˵��: "����node.dll������·��,�����������Ŀ¼��û��node.dll,������ڴ�������֮ǰ����,�����������Ŀ¼����node.dll���Ժ��Ը�����,Ĭ�ϻ��Ŀ¼�¼��ء�"
// ����<1>: dll·�� SDT_TEXT, ����˵��: "node.dll������·��"
EXTERN_C void WKE_NAME(147, wke_setDllPath)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wke_SetDllPath(pArgInf[0].m_pText);
}
DEF_EXECUTE_CMD(tmp_____)
{
}

// ���ø�ʽ: SDT_TEXT wke_AnsiToUtf8, ����˵��: "��ansi������ı�ת����utf8������ı�,�ɹ�����ת������ı�,ʧ�ܷ��ؿ��ı���"
// ����<1>: ansi�ı� SDT_TEXT, ����˵��: "ansi������ı�"
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

// ���ø�ʽ: SDT_BIN wke_AnsiToUnicode, ����˵��: "��ansi������ı�ת����Unicode������ı�,�ɹ�����ת�����Unicode�ֽڼ�,ʧ�ܷ��ؿ��ֽڼ���"
// ����<1>: ansi�ı� SDT_TEXT, ����˵��: "ansi������ı�"
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

// ���ø�ʽ: SDT_TEXT wke_Utf8ToAnsi, ����˵��: "��utf8������ı�ת����ansi������ı�,�ɹ�����ת������ı�,ʧ�ܷ��ؿ��ı���"
// ����<1>: utf8�ı� _SDT_ALL, ����˵��: "utf8������ı�,ֻ֧���ı�ָ��,�ı���,���ֽڼ�"
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
        if (!IsBadCodePtr((FARPROC)pArgInf[0].m_int))	//0=��Ч,��0=��Ч
        {
            //���ָ����Ч
            szStr = wstr::U2A((LPCSTR)pArgInf[0].m_int);
            break;
        }
        //ָ����Ч�������ߵ� default ��
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

// ���ø�ʽ: SDT_BIN wke_Utf8ToUnicode, ����˵��: "��utf8������ı�ת����Unicode������ı�,�ɹ�����ת�����Unicode�ֽڼ�,ʧ�ܷ��ؿ��ֽڼ���"
// ����<1>: utf8�ı� _SDT_ALL, ����˵��: "utf8������ı�,ֻ֧���ı�ָ��,�ı���,���ֽڼ�"
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
        if (!IsBadCodePtr((FARPROC)pArgInf[0].m_int))	//0=��Ч,��0=��Ч
        {
            //���ָ����Ч
            szStr = wstr::U2W((LPCSTR)pArgInf[0].m_int);
            break;
        }
        //ָ����Ч�������ߵ� default ��
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

// ���ø�ʽ: SDT_TEXT wke_UnicodeToAnsi, ����˵��: "��Unicode������ı�ת����ansi������ı�,�ɹ�����ת������ı�,ʧ�ܷ��ؿ��ı���"
// ����<1>: Unicode�ı� SDT_BIN, ����˵��: "Unicode������ı�"
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

// ���ø�ʽ: SDT_TEXT wke_UnicodeToUtf8, ����˵��: "��Unicode������ı�ת����utf8������ı�,�ɹ�����ת������ı�,ʧ�ܷ��ؿ��ı���"
// ����<1>: Unicode�ı� SDT_BIN, ����˵��: "Unicode������ı�"
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


// ���ø�ʽ: SDT_INT wke_ȡ�汾��, ����˵��: "��ȡĿǰapi�汾�š�"
// �޲���
EXTERN_C void WKE_NAME(155, wke_GetVersion)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    pRetData->m_int = wkeVersion();
}

// ���ø�ʽ: SDT_TEXT wke_ȡ�汾�ı�, ����˵��: "��ȡ�汾�ַ�����"
// �޲���
EXTERN_C void WKE_NAME(156, wke_GetVersionString)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str str = wstr::U2A(wkeVersionString());
    pRetData->m_pText = CloneTextData(str.c_str());
}

// ���ø�ʽ: SDT_DOUBLE wke_ȡCPUռ��, ����˵��: "ȡ�Խ���CPUռ����,���ڲ��Թһ���¼��������״̬��\r\n����ע�⡿�ù����ǲ��Թ���,������û���������Ƿ�ɾ��������"
// ����<1>: [&��������С SDT_INT], ����˵��: "���س���ǰ���������ڴ��С,��λΪ�ֽ�"
// ����<2>: [&��ֵ������ SDT_INT], ����˵��: "���س����ֵ���������ڴ��С,��λΪ�ֽ�"
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

// ���ø�ʽ: SDT_TEXT ��������, ����˵��: "c/c++��ĸ�ʽ���ַ���"
// ����<1>: ��ʽ���ı��� SDT_TEXT, ����˵��: "��ʽ���ı���"
// ����<2>: ���� _SDT_ALL, ����˵��: "����ʱ������ʹ�� %s, �ڲ���ת���� \"2020-01-01 01:01:01\" ���ָ�ʽ\r\n\t�ֽڼ����߼���Ҳʹ�� %s, �ڲ���ת���ı�ʹ��, ����û��˵��������, �Ͱ�c/c++��ʽ���ַ�������"
EXTERN_C void WKE_NAME(192, wke_format_1)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{

}

// ���ø�ʽ: SDT_TEXT �����ַ���, ����˵��: "�����ַ���, ��������ת�����ı������Ͷ�ת���ı���������һ��, ��ʱû��������ʱ���ͺ�����"
// ����<1>: ���� _SDT_ALL, ����˵��: "����ʱ������ʹ�� %s, �ڲ���ת���� \"2020-01-01 01:01:01\" ���ָ�ʽ\r\n\t�ֽڼ����߼���Ҳʹ�� %s, �ڲ���ת���ı�ʹ��, ����û��˵��������, �Ͱ�c/c++��ʽ���ַ�������"
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
            buffer.append(pArgInf[i].m_bool ? "��" : "��");
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
// ���ø�ʽ: SDT_BOOL wke_��Ϣѭ��, ����˵��: "��Ϣѭ��, �ڴ��ڴ�������¼��µ���, ���ô������ֱ������wke_ȡ��ѭ��() �ŷ���, ��������ʱ��Ҫ���� wke_ȡ��ѭ��(), ��������޷��˳�\r\n�˷�����Ϊ�˴���web���������޷���tab���л����������,\r\n��ע�⡿���ô˷����󲻻��������Ե���Ϣѭ��, ��tab���󲻻��Զ������������, ͬʱ������յ�tan�����·ſ���Ϣ"
// ����<1>: [���ھ�� SDT_INT], ����˵��: "Ŀǰ����2Ϊ��ʱ�ò�����Ч"
// ����<2>: [��ʾ���� SDT_BOOL], ����˵��: "�Ƿ���ʾ����, Ϊ��������ʾ�����ڵ�����Ϣѭ��, ����ֱ�ӵ�����Ϣѭ��"
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

// ���ø�ʽ: _SDT_NULL wke_ȡ��ѭ��, ����˵��: "ȡ����Ϣѭ��, ȡ�������ʹ wke_��Ϣѭ��() ����, ����������PostQuitMessage"
// �޲���
EXTERN_C void WKE_NAME(219, wke_CancelMsgLoop)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    if ( s_bMsgLoop )
    {
        PostQuitMessage(0);
        s_bMsgLoop = false;
    }
}













//ȡ���ڲ���,����1Ϊֻ�����ڲ��ֵ�DATE����
//1899��12��30��0ʱ00��00�� Ϊ0��׼,��λΪ������С��ֵ


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
        case SDT_BYTE:		// �ֽ�
        case SDT_SHORT:		// ������
        case SDT_INT:		// ����
        case SDT_SUB_PTR:	// �ӳ���ָ��
        case SDT_TEXT:		// �ı�
        case SDT_FLOAT:		// С��
        case SDT_BOOL:		// �߼�
            arr[n++] = pArgInf[i].m_int;
            break;
        case SDT_INT64:		// ������
        case SDT_DOUBLE:	// ˫����С��
            memcpy(&arr[n], &pArgInf[i].m_int64, sizeof(pArgInf[i].m_int64));
            n += 2;
            break;
        case SDT_DATE_TIME:	// ����ʱ��
        {
            dateBuf.resize(260);
            DateTimeFormat(dateBuf.data(), 260, pArgInf[i].m_date, 0);
            arr[n++] = (int)dateBuf.copy();
            break;
        }
        case SDT_BIN:		// �ֽڼ�
            arr[n++] = (int)GetAryElementInf(pArgInf[i].m_pAryData, 0);
            break;
        default:            // ����ֵ��ֱ��д������
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

// ���ø�ʽ: SDT_TEXT wke_��ʽ���ı�, ����˵��: "����c���� sprintf��ʵ��, ������Բ�������У��"
// ����<1>: ��ʽ SDT_TEXT, ����˵��: "������鿴c���Խ���, ���õ�%s=�ı�(����ʱ����), %d=����,%u=�޷�������,%p=ָ��,%x16=����,%%=%...."
// ����<2>: ���� _SDT_ALL, ����˵��: NULL
EXTERN_C void WKE_NAME(222, wke_format)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    _str ret;
    __format_wke(nArgCount, pArgInf, &ret, false);
    pRetData->m_pText = CloneTextData(ret.c_str());
}

// ���ø�ʽ: SDT_BIN wke_��ʽ���ı�W, ����˵��: "����c���� swprintf��ʵ��, Unicode��, ������Բ�������У��"
// ����<1>: ��ʽ SDT_TEXT, ����˵��: "������鿴c���Խ���, ���õ�%s=�ı�(����ʱ����), %d=����,%u=�޷�������,%p=ָ��,%x16=����,%%=%...."
// ����<2>: ���� _SDT_ALL, ����˵��: NULL
EXTERN_C void WKE_NAME(223, wke_formatW)( PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf )
{
    wstr ret;
    __format_wke(nArgCount, pArgInf, &ret, true);
    pRetData->m_pBin = CloneBinData((LPBYTE)ret.c_str(), ret.size());
}

