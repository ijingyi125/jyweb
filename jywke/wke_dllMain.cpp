#include "wke_version.h"
#include "wke_typedef.h"
#include "wke/MbE.h"

HINSTANCE g_hInst = 0;
EXTERN_C INT WINAPI wke_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2);



#ifndef __E_STATIC_LIB

//TODO dll程序入口点
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch ( ul_reason_for_call )
    {
    case DLL_PROCESS_ATTACH:    // 第一次被加载,LoadLibrary加载就触发
        g_hInst = hModule;
        break;
    case DLL_PROCESS_DETACH:    // DLL被释放
        break;
    case DLL_THREAD_ATTACH:     // 线程映射
        break;
    case DLL_THREAD_DETACH:     // 线程卸载
        break;
    }
    return TRUE;
}

// 定义易语言命令实现的函数地址
#define WKE_DEF_CMD_PTR(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    WKE_NAME(_index, _szEgName),

static PFN_EXECUTE_CMD g_CmdsFunc_web[] =
{
    WKE_DEF(WKE_DEF_CMD_PTR)
};


//TODO 易语言支持库接口数据类型定义
static LIB_INFO s_libInfo =
{
    /*m_dwLibFormatVer*/        LIB_FORMAT_VER, // 库格式号, 应该等于LIB_FORMAT_VER
    /*m_szGuid*/                "{6EC0A773-ABA1-49F4-AFD2-977EA30C0D4E}", // 对应于本库的唯一GUID串, 不能为NULL或空, 库的所有版本此串都应相同
    /*m_nMajorVersion*/         WKE_MAJORVERSION, // 本库的主版本号, 必须大于0
    /*m_nMinorVersion*/         WKE_MINORVERSION, // 本库的次版本号
    /*m_nBuildNumber*/          WKE_BUILDVERSION, // 构建版本号, 无需对此版本号作任何处理

    /*m_nRqSysMajorVer*/        3, // 所需要的易语言系统的主版本号
    /*m_nRqSysMinorVer*/        0, // 所需要的易语言系统的次版本号
    /*m_nRqSysKrnlLibMajorVer*/ 3, // 所需要的系统核心支持库的主版本号
    /*m_nRqSysKrnlLibMinorVer*/ 0, // 所需要的系统核心支持库的次版本号

    /*m_szName*/                "精易Web浏览器", // 库名, 不能为NULL或空
    /*m_nLanguage*/             __GBK_LANG_VER, // 库所支持的语言
    /*m_szExplain*/             "精易Web浏览器支持库(miniblink内核)，本支持库为易语言提供了wke浏览器组件，方便了易语言直接调用。\r\n    本支持库完全免费\r\n"
                                "    本支持库目前处于测试版。如果需要正式版，请看：https://bbs.125.la/thread-14410959-1-1.html", // 库详细解释

    /*m_dwState*/               _LIB_OS(OS_ALL), // _LIB_OS() | LBS_ 开头常量, 如果是插件,必须包含 LBS_IDE_PLUGIN
    /*m_szAuthor*/              "揭阳精易科技有限公司", // 作者
    /*m_szZipCode*/             "515500", // 邮编
    /*m_szAddress*/             "广东省揭阳市揭东区玉湖镇", // 地址
    /*m_szPhoto*/               "0663-3422125", // 联系电话
    /*m_szFax*/                 "11903273", // 传真
    /*m_szEmail*/               "800073686@b.qq.com ", // 邮箱
    /*m_szHomePage*/            "http://bbs.125.la/ ", // 主页
    /*m_szOther*/               "测试版反馈渠道： \r\n          在群内直接@项目部006回复。\r\n          ①群: 已满\r\n          ②群：746829283", // 其他信息

    /*m_nDataTypeCount*/        g_DataType_wke_global_var_count, // 本库中自定义数据类型的数目
    /*m_pDataType*/             g_DataType_wke_global_var, // 本库中所有的自定义数据类型


    /*m_nCategoryCount*/        2, // 全局命令类别数目, 可为0
    /*m_szzCategory*/           "0000精易web浏览器\0"
                                "0000编码转换\0"
                                "\0", // 全局命令类别数目, 可为0

    /*m_nCmdCount*/             g_cmdInfo_wke_global_var_count, // 本库中提供的所有命令(全局命令及对象命令)的数目, 可为0
    /*m_pBeginCmdInfo*/         g_cmdInfo_wke_global_var, // 本库中提供的所有命令

    /*m_pCmdsFunc*/             g_CmdsFunc_web, // 指向每个命令的实现代码首地址, 可为NULL

    /*m_pfnRunAddInFn*/         NULL, // 可为NULL,易语言IDE系统添加辅助功能, 所提供功能会被自动添加到IDE的“工具”菜单中
                                            // 有关AddIn功能的说明, 两个字符串说明一个功能。第一个为功能名称
                                            // (仅限一行20字符, 如果希望自行初始位置而不被自动加入到工具菜单, 则
                                            // 名称应该以@开始, 此时会接收到值为 -(nAddInFnIndex + 1) 的调用通知), 
                                            // 第二个为功能详细介绍(仅限一行60字符), 最后由两个空串结束。
    /*m_szzAddInFnInfo*/        NULL, // 功能详细介绍(仅限一行60字符), 最后由两个空串结束

    /*m_pfnNotify*/             wke_ProcessNotifyLib, // 不能为NULL,和易语言通讯的子程序

    /*m_pfnSuperTemplate*/      NULL, // 模板 可为NULL
                                            //  有关SuperTemplate的说明, 两个字符串说明一个SuperTemplate。
                                            //  第一个为SuperTemplate名称(仅限一行30字符), 第二个为详细介绍(不限), 
                                            //  最后由两个空串结束。
    /*m_szzSuperTemplateInfo*/  NULL, // 模板 可为NULL


    /*m_nLibConstCount*/        g_ConstInfo_wke_global_var_count, // 本库预先定义的所有常量数量
    /*m_pLibConst*/             g_ConstInfo_wke_global_var, // 本库预先定义的所有常量

    /*m_szzDependFiles*/        NULL // 可为NULL, 本库正常运行所需要依赖的其他支持文件
};




EXTERN_C _declspec(dllexport) PLIB_INFO WINAPI GetNewInf()
{
    head_dtType_Webkit(g_DataType_wke_global_var[4]);   // 精易web浏览器 需要填充结构
    head_dtType_NewWnd(g_DataType_wke_global_var[9]);   // 弹出窗口类型需要填充结构


    return &s_libInfo;
}



// 定义易语言静态编译需要的命令名, 这个是实现功能的函数名, 静态编译后是以这个名字导出, 易语言会使用这个数组的名字去调用静态库
#define WKE_DEF_CMDNAME_STR(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    (DWORD) WKE_NAME_STR(_index, _szEgName), 

// 函数名, 这个给静态编译使用
static DWORD g_cmdNames[] =
{
    WKE_DEF(WKE_DEF_CMDNAME_STR)
};

#endif


//TODO 和易语言通讯的子程序
EXTERN_C INT WINAPI wke_ProcessNotifyLib(INT nMsg, DWORD dwParam1, DWORD dwParam2)
{
    static BOOL tmp = FALSE;
    int nRet = NR_OK;

    switch ( nMsg )
    {
#ifndef __E_STATIC_LIB
    case NL_GET_CMD_FUNC_NAMES:
        return (INT)g_cmdNames;
    case NL_GET_NOTIFY_LIB_FUNC_NAME:
        return (INT)"wke_ProcessNotifyLib";
    case NL_GET_DEPENDENT_LIBS:
        return (INT)"\0\0\0";
#endif

    // 告知库通知系统用的函数指针,在装载支持库前通知,可能有多次,后通知的值应该覆盖前面所通知的值,忽略返回值
    // 库可将此函数指针记录下来以便在需要时使用它通知信息到系统
    // dwParam1: (PFN_NOTIFY_SYS)
    case NL_SYS_NOTIFY_FUNCTION:
    {
        ProcessNotifyLib(nMsg, dwParam1, dwParam2);
        if ( !g_hInst )
            g_hInst = GetModuleHandleW(0);  //  为0的话那就是没走dllmain函数

        break;
    }
    case NL_FREE_LIB_DATA:      //IDE取消选中或者库即将释放
    case NL_UNLOAD_FROM_IDE:
    {
        //必须只执行一次
        tmp = TRUE;
        MbE::wkeUnInit_wke();
        return (INT)NULL;
    }
    default:
        nRet = NR_ERR;
        break;
    }
    return nRet;
}
