#include "wke_typedef.h"
#include "Resource.h"

#ifndef __E_STATIC_LIB
//WKE_���  �µķ�������
static INT s_dtCmdIndexiext_Autofill_static_var_00[] =
{
    61,  62,  63,  64,  65,   66,  67,  68,  69,      
    70,  71,  72,  73,  163,  74,  164, 75,  165, 76,  169,  77,  78,  79,
    80,  81,  82,  83,  84,   85,  86,  87,  162, 88,  89,
    90,  91,  92,  93,  94,   95,  96,  97,  98,  99,
    100, 101, 102, 103, 104, 105,  106, 107, 108, 181, 109,
    110, 111, 112, 113, 114, 115,  116, 194, 195, 199,
};

static int s_dtCmdIndexiext_Autofill_static_var_count_00 = sizeof(s_dtCmdIndexiext_Autofill_static_var_00) / sizeof(s_dtCmdIndexiext_Autofill_static_var_00[0]);


// Ajax  �µķ�������
static INT s_dtCmdIndexiext_ajax_static_var_01[] =    
{
    21,    22,    23,    24,    25,    26,
};
static int s_dtCmdIndexiext_ajax_static_var_count_01 = sizeof(s_dtCmdIndexiext_ajax_static_var_01) / sizeof(s_dtCmdIndexiext_ajax_static_var_01[0]);

//Javascript  �µķ�������
static INT s_dtCmdIndexiext_javaScript_static_var_02[] =
{
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    204,   205,   206,   207,   208,   209,   210,   211,   212,   213, 214, 215,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    160,
};
static int s_dtCmdIndexiext_javaScript_static_var_count_02 = sizeof(s_dtCmdIndexiext_javaScript_static_var_02) / sizeof(s_dtCmdIndexiext_javaScript_static_var_02[0]);

static INT s_dtCmdIndexiext_SpecialFuncs_static_var_03[] =    //���⹦��  �µķ�������
{
    117,    118,    119,    120,    121,    122,    123,    124,    125,    172,
    173,    174,    175,    176,    177,    178,    179,
    126,    201,    202,    127,    200,    128,    129,    130,    131,    132,    133,    134,    135,
    136,    137,    138,    139,    140,    141,    142,    143,    144,    145,
    146,    167,    196,    197,    221,
};
static int s_dtCmdIndexiext_SpecialFuncs_static_var_count_03 = sizeof(s_dtCmdIndexiext_SpecialFuncs_static_var_03) / sizeof(s_dtCmdIndexiext_SpecialFuncs_static_var_03[0]);


LIB_DATA_TYPE_ELEMENT g_DataType_RECT[] =
{
    //1=��������,2=����ָ�����������Ϊ���飬��ֵΪNULL 3=������,4=Ӣ����,5=��ϸ����,6=��־LES_,7=Ĭ��ֵ
    {SDT_INT, 0, "���", "left", "���", 0, 0},
    {SDT_INT, 0, "����", "top", "����", 0, 0},
    {SDT_INT, 0, "�ұ�", "right", "�ұ�", 0, 0},
    {SDT_INT, 0, "�ױ�", "bottom", "�ױ�", 0, 0},
    {SDT_INT, 0, "���", "width", "���", 0, 0},
    {SDT_INT, 0, "�߶�", "height", "�߶�", 0, 0},
};

LIB_DATA_TYPE_ELEMENT g_DataType_MEMBUFFER[] =
{
    //1=��������,2=����ָ�����������Ϊ���飬��ֵΪNULL 3=������,4=Ӣ����,5=��ϸ����,6=��־LES_,7=Ĭ��ֵ
    {SDT_INT, 0, "�ṹ��С", "size", "�ṹ��С", 0, 0},
    {SDT_INT, 0, "����ָ��", "data", "����ָ��", 0, 0},
    {SDT_INT, 0, "���ݳ���", "length", "���ݳ���", 0, 0},
};

LIB_DATA_TYPE_ELEMENT g_DataType_POSTELEMENT[] =
{
    //1=��������,2=����ָ�����������Ϊ���飬��ֵΪNULL 3=������,4=Ӣ����,5=��ϸ����,6=��־LES_,7=Ĭ��ֵ
    {SDT_INT, 0, "�ṹ��С", "size", "�ṹ��С", 0, 0},
    {SDT_INT, 0, "����", "type", "Ԫ������_", 0, 0},
    {SDT_BIN, 0, "����", "MemBuf", "����", 0, 0},
    {SDT_TEXT, 0, "�ļ�·��", "filePath", "�ļ�·��", 0, 0},
    {SDT_INT64, 0, "�ļ���ʼλ��", "fileStart", "�ļ���ʼλ��", 0, 0},
    {SDT_INT64, 0, "�ļ�����", "fileLength", "-1 ��ʾ�ļ�ĩβ", 0, 0},
};


LPBYTE tmpfun()
{
    int len = 6;
    int* a = new int[len];
    memset(a, 0, len * sizeof(int));
    a[0] = 1;    // ���ȷ��������ά��
    return (LPBYTE)a;
}
static LIB_DATA_TYPE_ELEMENT g_DataType_POSTELEMENTS[] =
{
    //1=��������,2=����ָ�����������Ϊ���飬��ֵΪNULL 3=������,4=Ӣ����,5=��ϸ����,6=��־LES_,7=Ĭ��ֵ

    { SDT_INT, 0, "�ṹ��С", "size", "�ṹ��С", 0, 0},
    { SDT_TYPE_POSTELEMENT, tmpfun(), "Ԫ����", "wkePostElement", "��¼post��Ԫ������", 0, 0},
    { SDT_INT, 0, "Ԫ������", "ElementCount", "Ԫ�ص�����,Ԫ����ĳ�Ա��", 0, 0},
    { SDT_INT, 0, "�Ƿ�ı�", "isDirty", "�Ƿ�ı�", 0, 0},
    { SDT_INT, 0, "ԭʼ����", 0, "һ�㲻��Ҫ�������ֵ", 0, 0},
};


LIB_DATA_TYPE_INFO g_DataType_wke_global_var[] =
{
    //1=��������,2=Ӣ������,3=��ϸ����,4=��������,5=����ֵ,6=��־ LDT_
    //����Ϊ���ڻ�˵����ʱ��Ч 7=��ԴID,8=�¼�����,9=����¼�����,10=������  11=�������� 12=��������ӳ���
    //��Ϊ���ڡ��˵������Ϊö����������ʱ����Ч 13=��Ա����,14=��Ա��������

/*000*/ { "WKE_���", "WKE_TB", 0, 
            s_dtCmdIndexiext_Autofill_static_var_count_00, s_dtCmdIndexiext_Autofill_static_var_00, _DT_OS(__OS_WIN),
            0, 0, 0,
            0, 0,
            0, 0, 0
        },
/*001*/ { "Ajax", "Wke_AJAX", 0, 
            s_dtCmdIndexiext_ajax_static_var_count_01, s_dtCmdIndexiext_ajax_static_var_01, _DT_OS(__OS_WIN) | 0, 
            0, 0, 0, 
            0, 0, 
            0, 0, 0
        },
/*002*/ { "Javascript", "Javascript", 0, 
            s_dtCmdIndexiext_javaScript_static_var_count_02, s_dtCmdIndexiext_javaScript_static_var_02, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            0, 0, 0
        },
/*003*/ {"���⹦��", "SpecialFunction", 0, 
            s_dtCmdIndexiext_SpecialFuncs_static_var_count_03, s_dtCmdIndexiext_SpecialFuncs_static_var_03, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            0, 0,0},
/*004*/ {"����Web�����", "webkit", "������̳�����",   //! �������Ϣ�������ط�ȥ���
            0, 0, _DT_OS(__OS_WIN) | LDT_WIN_UNIT, 
            0, 0, 0, 
            0, 0, 
            0, 0,0
        },
/*005*/ {"Ԫ�ؾ���", "ElementRect", "ͨ��ȡԪ�ؾ��������ȡ", 
            0, 0, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            NULL, sizeof(g_DataType_RECT) / sizeof(g_DataType_RECT[0]), g_DataType_RECT
        },

/*006*/ {"�ڴ滺����", "MemBuf", "", 
            0, 0, _DT_OS(__OS_WIN) | LDT_IS_HIDED, 
            0, 0, 0, 
            0, 0, 
            NULL, sizeof(g_DataType_MEMBUFFER) / sizeof(g_DataType_MEMBUFFER[0]), g_DataType_MEMBUFFER},

/*007*/ {"POSTԪ��", "Element", "", 
            0, 0, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            NULL, sizeof(g_DataType_POSTELEMENT) / sizeof(g_DataType_POSTELEMENT[0]), g_DataType_POSTELEMENT},

/*008*/ {"POSTԪ�ؼ�", "Elements", "", 
            0, 0, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            NULL, sizeof(g_DataType_POSTELEMENTS) / sizeof(g_DataType_POSTELEMENTS[0]), g_DataType_POSTELEMENTS
        },
/*009*/ {"�������ڲ���", "newWindow", "���ڲ����µ����Ĵ���",   //! �������Ϣ�������ط�ȥ���
            0, 0, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            0, 0, 0
        },
};
int g_DataType_wke_global_var_count = sizeof(g_DataType_wke_global_var) / sizeof(g_DataType_wke_global_var[0]);

#endif