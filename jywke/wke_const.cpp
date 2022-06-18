#include "wke_typedef.h"

LIB_CONST_INFO g_ConstInfo_wke_global_var[] =
{
    {"JS类型_数值型", "Number", "JS中数值类型", 1, CT_NUM, NULL, 0},
    {"JS类型_文本型", "String", "JS中String", 1, CT_NUM, NULL, 1},
    {"JS类型_逻辑型", "Boolean", "JS中boolean", 1, CT_NUM, NULL, 2},
    {"JS类型_对象", "Object", "JS中的对象类型", 1, CT_NUM, NULL, 3},
    {"JS类型_函数", "Function", "JS中的函数类型", 1, CT_NUM, NULL, 4},
    {"JS类型_未定义", "UNDEFINED", "JS中的函数类型", 1, CT_NUM, NULL, 5},
    {"代理类型_无代理", "WKE_PROXY_NONE", "没有代理", 1, CT_NUM, NULL, 0},
    {"代理类型_HTTP代理", "WKE_PROXY_HTTP", "HTTP代理", 1, CT_NUM, NULL, 1},
    {"代理类型_SOCKS4代理", "WKE_PROXY_SOCKS4", "SOCKS4代理", 1, CT_NUM, NULL, 2},
    {"代理类型_SOCKS4A代理", "WKE_PROXY_SOCKS4A", "SOCKS4A代理", 1, CT_NUM, NULL, 3},
    {"代理类型_SOCKS5代理", "WKE_PROXY_SOCKS5", "SOCKS5代理", 1, CT_NUM, NULL, 4},
    {"代理类型_SOCKS5HOSTNAME代理", "WKE_PROXY_SOCKS5HOSTNAME", "SOCKS5HOSTNAME代理", 1, CT_NUM, NULL, 5},
    {"消息级别_LOG", "wkeLevelLog", "消息级别日志", 1, CT_NUM, NULL, 1},
    {"消息级别_WARNING", "wkeLevelWarning", "消息级别警告", 1, CT_NUM, NULL, 2},
    {"消息级别_ERROR", "wkeLevelError", "消息级别错误", 1, CT_NUM, NULL, 3},
    {"消息级别_DEBUG", "wkeLevelDebuge", "消息级别调试信息", 1, CT_NUM, NULL, 4},
    {"消息级别_INFO", "wkeLevelINFO", "消息级别信息", 1, CT_NUM, NULL, 5},
    {"消息级别_REVOKEDERROR", "wkeLevelREVOKEDERROR", "消息级别错误", 1, CT_NUM, NULL, 6},
    {"填表模式_精易模块", "jymk", "以精易模块的填表方式填表, 如 id==myid class==myclass  xxxx==xx", 1, CT_NUM, NULL, 1},
    {"填表模式_JS表达式", "jscon", "更灵活自己写JS选择表达式,支持 如 #id  .class  [name=xxx]  div.myclass>ul>li", 1, CT_NUM, NULL, 2},
    {"事件_获得焦点", "wke_focus", "触发获得焦点事件", 1, CT_TEXT, "focus", NULL},
    {"事件_失去焦点", "wke_blur", "触发失去焦点事件", 1, CT_TEXT, "blur", NULL},
    {"事件_单击", "wke_click", "触发鼠标单击事件", 1, CT_TEXT, "click", NULL},
    {"事件_双击", "wke_dblclick", "触发鼠标双击事件", 1, CT_TEXT, "dblclick", NULL},
    {"事件_鼠标按下", "wke_mousedown", "", 1, CT_TEXT, "mousedown", NULL},
    {"事件_鼠标抬起", "wke_mouseup", "", 1, CT_TEXT, "mouseup", NULL},
    {"事件_鼠标移动", "wke_mousemove", "", 1, CT_TEXT, "mousemove", NULL},
    {"事件_鼠标移入", "wke_mouseover", "", 1, CT_TEXT, "mouseover", NULL},
    {"事件_鼠标移出", "wke_mouseout", "", 1, CT_TEXT, "mouseout", NULL},
    {"事件_某键按下", "wke_keydown", "", 1, CT_TEXT, "keydown", NULL},
    {"事件_某键抬起", "wke_keyup", "", 1, CT_TEXT, "keyup", NULL},
    {"事件_单击某键", "wke_keypress", "", 1, CT_TEXT, "keypress", NULL},
    {"事件_内容发生改变", "wke_onchange", "", 1, CT_TEXT, "onchange", NULL},
    {"事件_重置表单", "wke_reset", "", 1, CT_TEXT, "reset", NULL},
    {"事件_表单提交", "wke_submit", "", 1, CT_TEXT, "submit", NULL},
    {"事件_滚动条位置变化", "wke_scroll", "", 1, CT_TEXT, "scroll", NULL},
    {"事件_文本被选中", "wke_select", "", 1, CT_TEXT, "select", NULL},
    {"事件_复制", "wke_copy", "", 1, CT_TEXT, "copy", NULL},
    {"事件_剪切", "wke_cut", "", 1, CT_TEXT, "cut", NULL},
    {"事件_粘贴", "wke_Paste", "", 1, CT_TEXT, "Paste", NULL},
    {"弃用_请勿使用该常量_后期此常量会被修改3", "", "如果使用了该常量, 请改用 #事件_复制, 此常量后期可能会变动\r\n由于易语言没有提供隐藏常量功能, 并且不能删除, 一旦删除源码就会提示支持库版本低, 为了使支持库能正常运行而不得不保留该常量", 1, CT_TEXT, "copy", NULL},
    {"事件_菜单被弹出", "wke_ContextMenu", "", 1, CT_TEXT, "contextMenu", NULL},
    {"载入状态_成功", "wke_LoadStateOK", "文档载入完毕 事件下载入状态,网页载入成功", 1, CT_NUM, NULL, 0},
    {"载入状态_失败", "wke_LoadStateError", "文档载入失败 事件下载入状态,网页载入失败", 1, CT_NUM, NULL, 1},
    {"载入状态_取消载入", "wke_LoadStateCancel", "文档载入完毕 事件下载入状态,网页被取消载入", 1, CT_NUM, NULL, 2},

    {"请求类型_无效", "KWkeRequestTypeInvalidation", "精易Web浏览器.取请求模式() 返回的状态,获取失败或者不是一个合法的请求", 1, CT_NUM, NULL, 0},
    {"请求类型_GET", "kWkeRequestTypeGet", "精易Web浏览器.取请求模式() 返回的状态,该请求为GET请求", 1, CT_NUM, NULL, 1},
    {"请求类型_POST", "kWkeRequestTypePost", "精易Web浏览器.取请求模式() 返回的状态,该请求为POST请求", 1, CT_NUM, NULL, 2},
    {"请求类型_PUT", "kWkeRequestTypePut", "精易Web浏览器.取请求模式() 返回的状态,该请求为PUT请求", 1, CT_NUM, NULL, 3},

    {"元素类型_数据", "wkeHttBodyElementTypeData", "特殊功能.取POST数据() 返回的类型", 1, CT_NUM, NULL, 0},
    {"元素类型_文件", "wkeHttBodyElementTypeFile", "特殊功能.取POST数据() 返回的类型", 1, CT_NUM, NULL, 1},

    {"弃用_请勿使用该常量_后期此常量会被修改1", 0, "由于易语言没有提供隐藏常量功能, 并且不能删除, 一旦删除源码就会提示支持库版本低, 为了使支持库能正常运行而不得不保留该常量", 1, CT_NUM, NULL, 0},
    {"弃用_请勿使用该常量_后期此常量会被修改2", 0, "由于易语言没有提供隐藏常量功能, 并且不能删除, 一旦删除源码就会提示支持库版本低, 为了使支持库能正常运行而不得不保留该常量", 1, CT_NUM, NULL, 0},

    {"浏览器事件_文档就绪", 0, "无返回值 文档就绪(整数型 webView, 整数型 参数, 整数型 就绪框架ID); 文档就绪时触发", 1, CT_NUM, NULL, 1},
    {"浏览器事件_标题被改变", 0, "无返回值 标题被改变(整数型 webView, 整数型 参数, 文本型 网页标题); 网页标题被改变时触发此事件", 1, CT_NUM, NULL, 2},
    {"浏览器事件_URL被改变", 0, "无返回值 URL被改变(整数型 webView, 整数型 参数, 文本型 url, 整数型 所属框架ID); URL被改变时触发", 1, CT_NUM, NULL, 3},
    {"浏览器事件_即将导航到新地址", 0, "逻辑型 即将导航到新地址(整数型 webView, 整数型 参数, 整数型 导航类型, 文本型 URL); 返回真允许导航到新地址, 返回假不允许. 将要导航到新的网址前触发", 1, CT_NUM, NULL, 4},
    {"浏览器事件_即将导航到新窗口", 0, "【弃用】请使用组件事件来接收该回调,调用传递该常量不会执行任何功能.  逻辑型 即将导航到新窗口(整数型 webView, 整数型 参数, 整数型 导航类型, 文本型 URL); 即将导航到新窗口,返回(真) 在新窗口打开网址,返回(假) 自行处理", 1, CT_NUM, NULL, 5},
    {"浏览器事件_文档载入完毕", 0, "无返回值 文档载入完毕(整数型 webView, 整数型 参数, 文本型 载入URL, 整数型 载入状态, 文本型 失败原因); 网页文档载入完毕时触发", 1, CT_NUM, NULL, 6},
    {"浏览器事件_控台消息输出", 0, "无返回值 控台消息输出(整数型 webView, 整数型 参数, 整数型 级别, 整数型 行号, 文本型 消息, 文本型 来源名称, 文本型 堆栈跟踪); 当产生控制台消息时触发", 1, CT_NUM, NULL, 7},
    {"浏览器事件_Alert将被调用", 0, "无返回值 Alert将被调用(整数型 webView, 整数型 参数, 文本型 消息); 当网页中的alert被调用的时候触发", 1, CT_NUM, NULL, 8},
    {"浏览器事件_Confirm将被调用", 0, "逻辑型 Confirm将被调用(整数型 webView, 整数型 参数, 文本型 消息); 当网页中的Confirm被调用的时候触发", 1, CT_NUM, NULL, 9},
    {"浏览器事件_Prompt将被调用", 0, "逻辑型 Prompt将被调用(整数型 webView, 整数型 参数, 文本型 消息); 当网页中的Prompt被调用的时候触发", 1, CT_NUM, NULL, 10},
    {"浏览器事件_正在下载文件", 0, "逻辑型 正在下载文件(整数型 webView, 整数型 参数, 文本型 文件URL); 正在下载文件时触发本事件", 1, CT_NUM, NULL, 11},
    {"浏览器事件_Url载入开始", 0, "逻辑型 Url载入开始(整数型 webView, 整数型 参数, 文本型 Url, 整数型 Job); 返回真表示不处理此网络请求(既不会发送网络请求). 返回假,表示mb依然会发送网络请求. Url开始载入, 任何网络请求发起前会触发此事件", 1, CT_NUM, NULL, 12},
    {"浏览器事件_Url载入结束", 0, "无返回值 Url载入结束(整数型 webView, 整数型 参数, 文本型 Url, 整数型 Job, 整数型 数据字节集指针, 整数型 数据长度); Url载入结束, 注意事项请查看 精易web浏览器 组件的 URL载入结束说明", 1, CT_NUM, NULL, 13},
    {"浏览器事件_鼠标移入链接", 0, "无返回值 鼠标移入链接(整数型 webView, 整数型 参数, 文本型 Url); 鼠标移动到A元素范围内时触发,并传入A元素连接", 1, CT_NUM, NULL, 14},
    {"浏览器事件_左键按下", 0, "逻辑型 左键按下(整数型 webView, 整数型 参数, 整数型 x, 整数型 y, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 15},
    {"浏览器事件_左键放开", 0, "逻辑型 左键放开(整数型 webView, 整数型 参数, 整数型 x, 整数型 y, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 16},
    {"浏览器事件_左键双击", 0, "逻辑型 左键双击(整数型 webView, 整数型 参数, 整数型 x, 整数型 y, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 17},
    {"浏览器事件_右键按下", 0, "逻辑型 右键按下(整数型 webView, 整数型 参数, 整数型 x, 整数型 y, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 18},
    {"浏览器事件_右键放开", 0, "逻辑型 右键放开(整数型 webView, 整数型 参数, 整数型 x, 整数型 y, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 19},
    {"浏览器事件_鼠标移动", 0, "逻辑型 鼠标移动(整数型 webView, 整数型 参数, 整数型 x, 整数型 y, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 20},
    {"浏览器事件_焦点获取", 0, "无返回值 焦点获取(整数型 webView, 整数型 参数); \r\n"
        "   当对象获得输入焦点时产生本事件。所谓\"输入焦点\", 即当前用户按键操作所对应的目标对象。"
        "   譬如：用户正在编辑框中输入文本, 那么此编辑框就具有输入焦点, 因为它将获得目前用户所进行的所有按键操作。"
        "   所谓\"获得\"或者\"失去\"输入焦点, 即当前用户按键操作所对应的目标对象发生转移。"
        "   譬如：现在用户正在编辑框1中输入文本, 突然使用鼠标或其它方法切换到了编辑框2上去继续输入。"
        "   那么此时, 编辑框1就\"失去\"了输入焦点, 编辑框2就\"得到\"了输入焦点, "
        "   因为在此以后用户所进行的所有按键操作都将被编辑框2所获得。", 1, CT_NUM, NULL, 21},
    {"浏览器事件_焦点消失", 0, "无返回值 焦点消失(整数型 webView, 整数型 参数); 当对象失去输入焦点时产生本事件", 1, CT_NUM, NULL, 22},
    {"浏览器事件_某键按下", 0, "逻辑型 某键按下(整数型 webView, 整数型 参数, 整数型 键代码, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 23},
    {"浏览器事件_某键放开", 0, "逻辑型 某键放开(整数型 webView, 整数型 参数, 整数型 键代码, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 24},
    {"浏览器事件_输入字符", 0, "整数型 输入字符(整数型 webView, 整数型 参数, 整数型 字符代码); "
        "   当用户按下和松开一个字符键时发生此事件。字符键包括任何可打印的键盘字符及回车(Enter)和退格(BackSpace)键。"
        "   在用户事件处理子程序中, 将事件处理完毕后可返回一个字符代码, 用于替换将继续传递到所属对象上字符键事件中的字符代码;"
        "   如果返回 0, 则取消此事件, 不再将此字符输入事件传递到所属对象上去", 1, CT_NUM, NULL, 25},
    {"浏览器事件_滚轮滚动", 0, "逻辑型 滚轮滚动(整数型 webView, 整数型 参数, 整数型 滚动距离, 整数型 功能键状态); 处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去", 1, CT_NUM, NULL, 26},
    {"浏览器事件_绘画事件", 0, "逻辑型 滚轮滚动(整数型 webView, 整数型 参数, 整数型 hdc, 整数型 左边, 整数型 顶边, 整数型 宽度, 整数型 高度);\r\n"
            "        返回是否拦截, 返回真则不使用内部的绘画, 返回假内部绘画, 目前返回值暂时未使用\r\n"
            "        hdc是当前浏览器的绘画dc, 在收到此事件时已经将浏览器需要显示的内容绘画到的这个dc上", 1, CT_NUM, NULL, 27},
    //{"浏览器事件_打开对话框", 0, "【弃用, 打开文件对话框是全局的, 请使用第一个精易web浏览器组件的\"打开文件对话框\"事件】逻辑型 打开对话框(整数型 参数, 文本型参考 地址); 返回假则不弹出对话框, 直接使用参数\"地址\"的值", 1, CT_NUM, NULL, 27},
    //{"浏览器事件_保存对话框", 0, "【弃用, 保存文件对话框是全局的, 请使用第一个精易web浏览器组件的\"保存文件对话框\"事件】逻辑型 保存对话框(整数型 参数, 文本型参考 地址); 返回假则不弹出对话框, 直接使用参数\"地址\"的值", 1, CT_NUM, NULL, 28},

};

int g_ConstInfo_wke_global_var_count = sizeof(g_ConstInfo_wke_global_var) / sizeof(g_ConstInfo_wke_global_var[0]);

