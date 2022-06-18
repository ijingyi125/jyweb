#pragma once

#include "pch.h"
#include "interface.h"
#include "ArgInfos.h"

HUNIT WINAPI ControlCreate1(
    LPBYTE pAllPropertyData,            //   指向本窗口单元的已有属性数据，由本窗口单元的
    // ITF_GET_PROPERTY_DATA接口产生，如果没有数据则为NULL。
    INT nAllPropertyDataSize,           //   提供pAllPropertyData所指向数据的尺寸，如果没有则为0。
    DWORD dwStyle,                      //   预先设置的窗口风格。
    HWND hParentWnd,                    //   父窗口句柄。
    UINT uID,                           //   在父窗口中的ID。
    HMENU hMenu,                        //   未使用。
    INT x, INT y, INT cx, INT cy,       //   指定位置及尺寸。
    DWORD dwWinFormID, DWORD dwUnitID,  //   本窗口单元所在窗口及本身的ID，用作通知到系统。
    HWND hDesignWnd,                //   如果blInDesignMode为真，则hDesignWnd提供所设计窗口的窗口句柄。
    BOOL blInDesignMode)  			//   说明是否被易语言IDE调用以进行可视化设计，运行时为假。
    ;

EVENT_INFO2 g_eventInfo_web[] =	//精易Web浏览器  下的事件
{
    //1=事件名称,2=事件详细解释,3=返回值类型,EV_RETURN_ 绝对不能定义成返回文本、字节集、复合类型等需要空间释放代码的数据类型。
    //4=事件的参数数目,5=事件参数,6=返回值类型

    {"文档就绪", "文档就绪时触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 0, (DATA_TYPE)_SDT_NULL},
    {"标题被改变", "网页标题被改变时触发此事件", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 1, (DATA_TYPE)_SDT_NULL},
    {"URL被改变", "URL被改变时触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 2, (DATA_TYPE)_SDT_NULL},
    {"即将导航到新地址", "将要导航到新的网址前触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 4, (DATA_TYPE)_SDT_NULL},
    {"即将导航到新窗口", "即将导航到新窗口,返回(真) 在当前窗口打开网址,返回(假) 自行处理", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 6, (DATA_TYPE)SDT_BOOL},
    {"文档载入完毕", "网页文档载入完毕时触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, g_argInfo_web + 8, (DATA_TYPE)_SDT_NULL},
    {"控台消息输出", "当产生控制台消息时触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 5, g_argInfo_web + 11, (DATA_TYPE)_SDT_NULL},
    {"Alert将被调用", "当网页中的alert被调用的时候触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 16, (DATA_TYPE)_SDT_NULL},
    {"Confirm将被调用", "当网页中的alert被调用的时候触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 17, (DATA_TYPE)SDT_BOOL},
    {"Prompt将被调用", "当网页中的Prompt被调用的时候触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 18, (DATA_TYPE)SDT_TEXT},
    {"正在下载文件", "正在下载文件时触发本事件", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 20, (DATA_TYPE)SDT_BOOL},
    {"Url载入开始", "Url开始载入", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 21, (DATA_TYPE)SDT_BOOL},
    {"Url载入结束", "Url载入结束", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 4, g_argInfo_web + 23, (DATA_TYPE)_SDT_NULL},
    {"鼠标移入链接", "鼠标移动到A元素范围内时触发,并传入A元素连接", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 27, (DATA_TYPE)_SDT_NULL},
};