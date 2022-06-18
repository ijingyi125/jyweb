// pch.cpp: ��Ԥ�����ͷ��Ӧ��Դ�ļ�

#include "pch.h"
struct _ASSIST_ID
{
    DWORD dwWinFormID;
    DWORD dwUnitID;
    HUNIT hUnit;
    PVOID pData;
};

// ����ûʹ�� vector, ����ʲô��ͻ....
static _ASSIST_ID* s_arr_id;    // ��¼id��Ӧ������, Ŀǰֻ�м��뵽����, û��ɾ��, �����˭���ϵ��Ϸ�һ�����Ȼ��ɾ��һֱ�ظ�, ���ڴ�᲻������
static int s_arr_count;         // ����ʹ�õ�����, �����Ļ���Ҫ���·���
static int s_arr_count_buf;     // ���黺������Ա��


inline void _init_arr()
{
    if ( !s_arr_count_buf )
    {
        s_arr_count_buf = 100;
        s_arr_id = new _ASSIST_ID[s_arr_count_buf];
        memset(s_arr_id, 0, sizeof(_ASSIST_ID) * s_arr_count_buf);
    }
}

// ͨ��id��ȡhUnit, �������������Բο����ذ󶨵�����
HUNIT GethUnitFromId(DWORD dwWinFormID, DWORD dwUnitID, PVOID* pRet)
{
    _init_arr();
    if ( pRet ) *pRet = 0;
    for ( int i = 0; i < s_arr_count; ++i )
    {
        _ASSIST_ID& item = s_arr_id[i];
        if ( dwWinFormID == item.dwWinFormID && dwUnitID == item.dwUnitID )
        {
            if ( pRet ) *pRet = item.pData;
            return item.hUnit;
        }
    }
    return 0;
}

// ͨ��������ĵ�һ����Ա��ȡhUnit, �ڶ����������Բο����ذ󶨵�����
HUNIT GethUnitFromArgInf(PMDATA_INF pInf, PVOID* pRet)
{
    return GethUnitFromId(pInf->m_unit.m_dwFormID, pInf->m_unit.m_dwUnitID, pRet);
}

// ��hUnit���ȡ�󶨵�����
PVOID GetDataFromHunit(HUNIT hUnit)
{
    _init_arr();
    for ( int i = 0; i < s_arr_count; ++i )
    {
        _ASSIST_ID& item = s_arr_id[i];
        if ( hUnit == item.hUnit )
        {
            return item.pData;
        }
    }
    return 0;
}

// ������, ���ID����ͬ��, �ǻ�� hUnit�� pData ���ǽ�ȥ, ������½�һ������
PVOID SetDataFromIdUnit(DWORD dwWinFormID, DWORD dwUnitID, HUNIT hUnit, PVOID pData)
{
    _init_arr();
    int n = 0;
    for ( int i = 0; i < s_arr_count; ++i )
    {
        _ASSIST_ID& item = s_arr_id[i];
        if ( dwWinFormID == item.dwWinFormID && dwUnitID == item.dwUnitID )
        {
            PVOID ret = item.pData;
            item.hUnit = hUnit;
            item.pData = pData;
            return ret;
        }
    }

    // ���뵽������
    if ( s_arr_count >= s_arr_count_buf )
    {
        // ���·�������
        int newCount = s_arr_count_buf * 2;
        _ASSIST_ID* newArr = new _ASSIST_ID[newCount];
        memset(newArr, 0, sizeof(_ASSIST_ID) * newCount);
        memcpy(newArr, s_arr_id, sizeof(_ASSIST_ID) * s_arr_count_buf);
        delete[] s_arr_id;
        s_arr_id = newArr;
    }

    _ASSIST_ID& item = s_arr_id[s_arr_count++];
    item.dwWinFormID = dwWinFormID;
    item.dwUnitID = dwUnitID;
    item.hUnit = hUnit;
    item.pData = pData;
    return pData;
}
