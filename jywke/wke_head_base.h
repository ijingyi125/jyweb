#pragma once

typedef struct WKE_STRUCT_BASE
{
    LONG                controlType;    // �������, �����ݶ���һ���Ĳ���, �͸������ȷ����ʲô�����, CONTROLTYPE_ ��ͷ����
    WNDPROC             oldProc;        // ����ԭ����
    HFONT               hFont;          // ����
    HWND                hDesignWnd;     // ���blInDesignModeΪ��, ��hDesignWnd����ƴ��ڵĴ��ھ��, ����Ϊ0
    HWND                hWndParent;     // ��������ھ��
    HWND                hWnd;           // ������
    DWORD               hUnit;          // �����Է��ص�һ��CWnd��ָ��
    UINT                id;             // �����ID
    DWORD               dwWinFormID;    // �����ڵ�Ԫ���ڴ��ڼ������ID, ����֪ͨ��ϵͳ
    DWORD               dwUnitID;       // �����ڵ�Ԫ���ڴ��ڼ������ID, ����֪ͨ��ϵͳ��
    BOOL                blInDesignMode; // �Ƿ�������IDE�����Խ��п��ӻ����, ����ʱΪ��
    LONG                flags;          // �����һЩ��־, �Լ�����Լ�����
    DWORD               style;          // �������ʽ, �� WM_STYLECHANGED ���޸�
    DWORD               styleEx;        // �������չ��ʽ, �� WM_STYLECHANGED ���޸�
    DWORD               styleCtl;       // ���ר����չ��ʽ

}*PWKE_STRUCT_BASE;

// ������������Ļص���ʹ��, ��һЩ��Ҫ�Ĳ�����¼����
#define SET_DATA_DEFVALUE(_data) \
    _data->hDesignWnd        = hDesignWnd;      \
    _data->hWndParent        = hParentWnd;      \
    _data->id                = uID;             \
    _data->dwWinFormID       = dwWinFormID;     \
    _data->dwUnitID          = dwUnitID;        \
    _data->blInDesignMode    = blInDesignMode;  \
    _data->style             = dwStyle;         \
    _data->styleCtl          = 0;               \
    _data->styleEx           = 0;               \
    _data->hUnit             = hUnit