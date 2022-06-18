#include "wke_typedef.h"
#include "Resource.h"

#ifndef __E_STATIC_LIB
//WKE_填表  下的方法索引
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


// Ajax  下的方法索引
static INT s_dtCmdIndexiext_ajax_static_var_01[] =    
{
    21,    22,    23,    24,    25,    26,
};
static int s_dtCmdIndexiext_ajax_static_var_count_01 = sizeof(s_dtCmdIndexiext_ajax_static_var_01) / sizeof(s_dtCmdIndexiext_ajax_static_var_01[0]);

//Javascript  下的方法索引
static INT s_dtCmdIndexiext_javaScript_static_var_02[] =
{
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    204,   205,   206,   207,   208,   209,   210,   211,   212,   213, 214, 215,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    160,
};
static int s_dtCmdIndexiext_javaScript_static_var_count_02 = sizeof(s_dtCmdIndexiext_javaScript_static_var_02) / sizeof(s_dtCmdIndexiext_javaScript_static_var_02[0]);

static INT s_dtCmdIndexiext_SpecialFuncs_static_var_03[] =    //特殊功能  下的方法索引
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
    //1=数据类型,2=数组指定串，如果不为数组，此值为NULL 3=中文名,4=英文名,5=详细介绍,6=标志LES_,7=默认值
    {SDT_INT, 0, "左边", "left", "左边", 0, 0},
    {SDT_INT, 0, "顶边", "top", "顶边", 0, 0},
    {SDT_INT, 0, "右边", "right", "右边", 0, 0},
    {SDT_INT, 0, "底边", "bottom", "底边", 0, 0},
    {SDT_INT, 0, "宽度", "width", "宽度", 0, 0},
    {SDT_INT, 0, "高度", "height", "高度", 0, 0},
};

LIB_DATA_TYPE_ELEMENT g_DataType_MEMBUFFER[] =
{
    //1=数据类型,2=数组指定串，如果不为数组，此值为NULL 3=中文名,4=英文名,5=详细介绍,6=标志LES_,7=默认值
    {SDT_INT, 0, "结构大小", "size", "结构大小", 0, 0},
    {SDT_INT, 0, "数据指针", "data", "数据指针", 0, 0},
    {SDT_INT, 0, "数据长度", "length", "数据长度", 0, 0},
};

LIB_DATA_TYPE_ELEMENT g_DataType_POSTELEMENT[] =
{
    //1=数据类型,2=数组指定串，如果不为数组，此值为NULL 3=中文名,4=英文名,5=详细介绍,6=标志LES_,7=默认值
    {SDT_INT, 0, "结构大小", "size", "结构大小", 0, 0},
    {SDT_INT, 0, "类型", "type", "元素类型_", 0, 0},
    {SDT_BIN, 0, "数据", "MemBuf", "数据", 0, 0},
    {SDT_TEXT, 0, "文件路径", "filePath", "文件路径", 0, 0},
    {SDT_INT64, 0, "文件开始位置", "fileStart", "文件开始位置", 0, 0},
    {SDT_INT64, 0, "文件长度", "fileLength", "-1 表示文件末尾", 0, 0},
};


LPBYTE tmpfun()
{
    int len = 6;
    int* a = new int[len];
    memset(a, 0, len * sizeof(int));
    a[0] = 1;    // 这个确定是数组维数
    return (LPBYTE)a;
}
static LIB_DATA_TYPE_ELEMENT g_DataType_POSTELEMENTS[] =
{
    //1=数据类型,2=数组指定串，如果不为数组，此值为NULL 3=中文名,4=英文名,5=详细介绍,6=标志LES_,7=默认值

    { SDT_INT, 0, "结构大小", "size", "结构大小", 0, 0},
    { SDT_TYPE_POSTELEMENT, tmpfun(), "元素组", "wkePostElement", "记录post的元素数组", 0, 0},
    { SDT_INT, 0, "元素数量", "ElementCount", "元素的数量,元素组的成员数", 0, 0},
    { SDT_INT, 0, "是否改变", "isDirty", "是否改变", 0, 0},
    { SDT_INT, 0, "原始数据", 0, "一般不需要操作这个值", 0, 0},
};


LIB_DATA_TYPE_INFO g_DataType_wke_global_var[] =
{
    //1=中文名字,2=英文名字,3=详细解释,4=命令数量,5=索引值,6=标志 LDT_
    //类型为窗口或菜单组件时有效 7=资源ID,8=事件数量,9=组件事件数组,10=属性数  11=属性数组 12=组件交互子程序
    //不为窗口、菜单组件或为枚举数据类型时才有效 13=成员数量,14=成员数据数组

/*000*/ { "WKE_填表", "WKE_TB", 0, 
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
/*003*/ {"特殊功能", "SpecialFunction", 0, 
            s_dtCmdIndexiext_SpecialFuncs_static_var_count_03, s_dtCmdIndexiext_SpecialFuncs_static_var_03, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            0, 0,0},
/*004*/ {"精易Web浏览器", "webkit", "精易论坛浏览器",   //! 这里的信息让其他地方去填充
            0, 0, _DT_OS(__OS_WIN) | LDT_WIN_UNIT, 
            0, 0, 0, 
            0, 0, 
            0, 0,0
        },
/*005*/ {"元素矩形", "ElementRect", "通过取元素矩形命令获取", 
            0, 0, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            NULL, sizeof(g_DataType_RECT) / sizeof(g_DataType_RECT[0]), g_DataType_RECT
        },

/*006*/ {"内存缓冲区", "MemBuf", "", 
            0, 0, _DT_OS(__OS_WIN) | LDT_IS_HIDED, 
            0, 0, 0, 
            0, 0, 
            NULL, sizeof(g_DataType_MEMBUFFER) / sizeof(g_DataType_MEMBUFFER[0]), g_DataType_MEMBUFFER},

/*007*/ {"POST元素", "Element", "", 
            0, 0, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            NULL, sizeof(g_DataType_POSTELEMENT) / sizeof(g_DataType_POSTELEMENT[0]), g_DataType_POSTELEMENT},

/*008*/ {"POST元素集", "Elements", "", 
            0, 0, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            NULL, sizeof(g_DataType_POSTELEMENTS) / sizeof(g_DataType_POSTELEMENTS[0]), g_DataType_POSTELEMENTS
        },
/*009*/ {"弹出窗口操作", "newWindow", "用于操作新弹出的窗口",   //! 这里的信息让其他地方去填充
            0, 0, _DT_OS(__OS_WIN), 
            0, 0, 0, 
            0, 0, 
            0, 0, 0
        },
};
int g_DataType_wke_global_var_count = sizeof(g_DataType_wke_global_var) / sizeof(g_DataType_wke_global_var[0]);

#endif