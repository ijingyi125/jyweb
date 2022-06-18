#pragma once

#include "pch.h"
#include "interface.h"
#include "ArgInfos.h"

HUNIT WINAPI ControlCreate1(
    LPBYTE pAllPropertyData,            //   ָ�򱾴��ڵ�Ԫ�������������ݣ��ɱ����ڵ�Ԫ��
    // ITF_GET_PROPERTY_DATA�ӿڲ��������û��������ΪNULL��
    INT nAllPropertyDataSize,           //   �ṩpAllPropertyData��ָ�����ݵĳߴ磬���û����Ϊ0��
    DWORD dwStyle,                      //   Ԥ�����õĴ��ڷ��
    HWND hParentWnd,                    //   �����ھ����
    UINT uID,                           //   �ڸ������е�ID��
    HMENU hMenu,                        //   δʹ�á�
    INT x, INT y, INT cx, INT cy,       //   ָ��λ�ü��ߴ硣
    DWORD dwWinFormID, DWORD dwUnitID,  //   �����ڵ�Ԫ���ڴ��ڼ������ID������֪ͨ��ϵͳ��
    HWND hDesignWnd,                //   ���blInDesignModeΪ�棬��hDesignWnd�ṩ����ƴ��ڵĴ��ھ����
    BOOL blInDesignMode)  			//   ˵���Ƿ�������IDE�����Խ��п��ӻ���ƣ�����ʱΪ�١�
    ;

EVENT_INFO2 g_eventInfo_web[] =	//����Web�����  �µ��¼�
{
    //1=�¼�����,2=�¼���ϸ����,3=����ֵ����,EV_RETURN_ ���Բ��ܶ���ɷ����ı����ֽڼ����������͵���Ҫ�ռ��ͷŴ�����������͡�
    //4=�¼��Ĳ�����Ŀ,5=�¼�����,6=����ֵ����

    {"�ĵ�����", "�ĵ�����ʱ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 0, (DATA_TYPE)_SDT_NULL},
    {"���ⱻ�ı�", "��ҳ���ⱻ�ı�ʱ�������¼�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 1, (DATA_TYPE)_SDT_NULL},
    {"URL���ı�", "URL���ı�ʱ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 2, (DATA_TYPE)_SDT_NULL},
    {"�����������µ�ַ", "��Ҫ�������µ���ַǰ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 4, (DATA_TYPE)_SDT_NULL},
    {"�����������´���", "�����������´���,����(��) �ڵ�ǰ���ڴ���ַ,����(��) ���д���", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 6, (DATA_TYPE)SDT_BOOL},
    {"�ĵ��������", "��ҳ�ĵ��������ʱ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, g_argInfo_web + 8, (DATA_TYPE)_SDT_NULL},
    {"��̨��Ϣ���", "����������̨��Ϣʱ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 5, g_argInfo_web + 11, (DATA_TYPE)_SDT_NULL},
    {"Alert��������", "����ҳ�е�alert�����õ�ʱ�򴥷�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 16, (DATA_TYPE)_SDT_NULL},
    {"Confirm��������", "����ҳ�е�alert�����õ�ʱ�򴥷�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 17, (DATA_TYPE)SDT_BOOL},
    {"Prompt��������", "����ҳ�е�Prompt�����õ�ʱ�򴥷�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 18, (DATA_TYPE)SDT_TEXT},
    {"���������ļ�", "���������ļ�ʱ�������¼�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 20, (DATA_TYPE)SDT_BOOL},
    {"Url���뿪ʼ", "Url��ʼ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, g_argInfo_web + 21, (DATA_TYPE)SDT_BOOL},
    {"Url�������", "Url�������", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 4, g_argInfo_web + 23, (DATA_TYPE)_SDT_NULL},
    {"�����������", "����ƶ���AԪ�ط�Χ��ʱ����,������AԪ������", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, g_argInfo_web + 27, (DATA_TYPE)_SDT_NULL},
};