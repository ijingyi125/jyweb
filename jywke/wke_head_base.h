#pragma once

typedef struct WKE_STRUCT_BASE
{
    LONG                controlType;    // 组件类型, 绑定数据都是一样的操作, 就根据这个确定是什么组件了, CONTROLTYPE_ 开头常量
    WNDPROC             oldProc;        // 窗口原过程
    HFONT               hFont;          // 字体
    HWND                hDesignWnd;     // 如果blInDesignMode为真, 则hDesignWnd是设计窗口的窗口句柄, 否则为0
    HWND                hWndParent;     // 组件父窗口句柄
    HWND                hWnd;           // 组件句柄
    DWORD               hUnit;          // 易语言返回的一个CWnd类指针
    UINT                id;             // 组件的ID
    DWORD               dwWinFormID;    // 本窗口单元所在窗口及本身的ID, 用作通知到系统
    DWORD               dwUnitID;       // 本窗口单元所在窗口及本身的ID, 用作通知到系统。
    BOOL                blInDesignMode; // 是否被易语言IDE调用以进行可视化设计, 运行时为假
    LONG                flags;          // 组件的一些标志, 自己组件自己定义
    DWORD               style;          // 组件的样式, 在 WM_STYLECHANGED 里修改
    DWORD               styleEx;        // 组件的扩展样式, 在 WM_STYLECHANGED 里修改
    DWORD               styleCtl;       // 组件专属扩展样式

}*PWKE_STRUCT_BASE;

// 在组件被创建的回调下使用, 把一些必要的参数记录起来
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