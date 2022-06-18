// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
struct _ASSIST_ID
{
    DWORD dwWinFormID;
    DWORD dwUnitID;
    HUNIT hUnit;
    PVOID pData;
};

// 这里没使用 vector, 怕有什么冲突....
static _ASSIST_ID* s_arr_id;    // 记录id对应的数据, 目前只有加入到里面, 没有删除, 如果有谁不断的拖放一个组件然后删除一直重复, 那内存会不断增加
static int s_arr_count;         // 数组使用的数量, 超过的话需要重新分配
static int s_arr_count_buf;     // 数组缓冲区成员数


inline void _init_arr()
{
    if ( !s_arr_count_buf )
    {
        s_arr_count_buf = 100;
        s_arr_id = new _ASSIST_ID[s_arr_count_buf];
        memset(s_arr_id, 0, sizeof(_ASSIST_ID) * s_arr_count_buf);
    }
}

// 通过id获取hUnit, 第三个参数可以参考返回绑定的数据
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

// 通过参数里的第一个成员获取hUnit, 第二个参数可以参考返回绑定的数据
HUNIT GethUnitFromArgInf(PMDATA_INF pInf, PVOID* pRet)
{
    return GethUnitFromId(pInf->m_unit.m_dwFormID, pInf->m_unit.m_dwUnitID, pRet);
}

// 从hUnit里获取绑定的数据
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

// 绑定数据, 如果ID有相同的, 那会把 hUnit和 pData 覆盖进去, 否则会新建一个保存
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

    // 加入到数组里
    if ( s_arr_count >= s_arr_count_buf )
    {
        // 重新分配数组
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
