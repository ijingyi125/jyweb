#include "wke_webkit_header.h"
#include "Resource.h"

//精易Web浏览器  下的方法索引
static INT s_dtCmdIndexiext_Webkit_static_var_04[] =
{
    220, 0,   1,   2,   3,   4,   5,   6,   7,    8,   180, 9,
    10,  188, 161, 166, 11,  12,  13,  168, 14,   15,  16,  17,  18,  19,
    20,  154, 157, 158, 171, 189, 191, 198, 203,
};
// 精易Web方法数量
static int s_dtCmdIndexiext_Webkit_static_var_count_04 = sizeof(s_dtCmdIndexiext_Webkit_static_var_04) / sizeof(s_dtCmdIndexiext_Webkit_static_var_04[0]);

// 新窗口  下的方法索引
static INT s_dtCmdIndexiext_NewWindow_static_var_09[] =
{
    216, 220, 217, 182, 186, 183, 184, 185, 0,   1,   2,   3,   4,   5,   6,   7,    8,   180,   9,
    10,  188, 161, 166, 11,  12,  13,  168, 14,  15,  16,  17,  18,  19,
    20,  154, 157, 158, 171, 187, 189, 190, 191, 198, 203,
};
// 新窗口方法数量
static int s_dtCmdIndexiext_NewWindow_static_var_count_09 = sizeof(s_dtCmdIndexiext_NewWindow_static_var_09) / sizeof(s_dtCmdIndexiext_NewWindow_static_var_09[0]);


// 精易Web浏览器  下的属性
static UNIT_PROPERTY s_objPropertyiext_Webkit_static_var_00[] =
{
    // FIXED_WIN_UNIT_PROPERTY,    // 必须加上此宏, 或者直接展开, 这里就展开
    //1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束
    /*000*/ {"左边", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
    /*001*/ {"顶边", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
    /*002*/ {"宽度", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
    /*003*/ {"高度", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
    /*004*/ {"标记", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
    /*005*/ {"可视", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
    /*006*/ {"禁止", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
    /*007*/ {"鼠标指针", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},


    //1=属性名, 2=英文属性名, 3=属性解释, 4=属性的数据类型UD_,5=属性的标志, 6=顺序记录所有的备选文本UW_(除开UD_FILE_NAME), 以一个空串结束。
    {"URL", "GetCurrentPageUrl", "跳转到指定url,或者获取设置的url\r\n"
        "        取值是取到设置的值,如果需要获取当前浏览器真实的url,请使用 \"精易Web浏览器.取网页URL()\" 来获取\r\n"
        "        本属性与 \"精易Web浏览器.浏览网页()\" 唯一的区别是,本属性会记录设置的url地址,且不跟随url地址改变。", UD_TEXT, _PROP_OS(__OS_WIN), 0},
    {"网页标题", "GetCurrentPageTitle", "当前网页标题", UD_TEXT, _PROP_OS(__OS_WIN) | UW_ONLY_READ, 0},
    {"禁止F5刷新", "CancelF5Reload", "禁止F5刷新", UD_BOOL, _PROP_OS(__OS_WIN), 0},
    {"禁止Cookies", "IsEnableCookie", "禁止Cookie", UD_BOOL, _PROP_OS(__OS_WIN), 0},
    {"缓存目录", "CachePath", "缓存目录", UD_TEXT, _PROP_OS(__OS_WIN), 0 },
    {"Cookie目录", "CookiePath", "Cookie存放目录", UD_TEXT, _PROP_OS(__OS_WIN), 0},
    {"UserAgent", "UserAgent", "浏览器UA,\r\n\r\n注意: 浏览器UA可能会影响到某个网页的正常加载,如果设置UA后打开某个网页出现崩溃现象,请换一个UA", UD_EDIT_PICK_TEXT, _PROP_OS(__OS_WIN), \
    "默认UA\0""iPhone X\0""iPad Pro\0""安卓Galaxy S5\0""Winsows Safari\0""Winsows Chrome\0""Winsows Firefox\0""Winsows Opera\0""Winsows IE9\0""\0"},//"Winsows IE8\0""Winsows IE7\0"
    {"允许设计时预览", 0, \
    "本属性仅在当前设计期间有效, 且每次创建组件或打开易语言源码文件时都默认还原为假。此举既可方便用户在设计期间实时预览网页(以便调整组件大小等属性), 又能有效阻止预览别人设定的不安全网页。",\
    UD_BOOL, _PROP_OS(__OS_WIN), 0},
    {"允许新窗口打开", "newWindow", "默认为假,都在本窗口打开,不触发 \"即将导航到新窗口\" 事件\r\n"
    "        为真时会触发 \"即将导航到新窗口\" 事件", UD_BOOL, _PROP_OS(__OS_WIN), 0},

};
const int s_objPropertyiext_Webkit_static_var_count_00 = sizeof(s_objPropertyiext_Webkit_static_var_00) / sizeof(s_objPropertyiext_Webkit_static_var_00[0]);


// 精易Web浏览器下的事件参数
static EVENT_ARG_INFO2 s_eventArgInfo_iext_Webkit[] =
{
    //1=参数名称,2=参数介绍,3=是否参考,4=参数类型SDT_

    /*000*/    {"就绪框架ID", "网页文档就绪或内部框架就绪时触发", 0, SDT_INT},

    /*001*/    {"标题", "网页标题被更改时触发", 0, SDT_TEXT},

    /*002*/    {"URL", "改变的URL", 0, SDT_TEXT},
    /*003*/    {"所属框架ID", "当前URL属于哪个框架ID", 0, SDT_INT},

    /*004*/    {"导航类型", "即将导航的类型  0==单击连接(点击a标签触发) 1==表单提交(点击form触发) 2==前进后退触发 3==重新载入(刷新) 4==重新加载触发  5==其他类型", 0, SDT_INT},
    /*005*/    {"URL", "即将导航的URL", 0, SDT_TEXT},

    /*006*/    {"导航类型", "即将导航的类型  0==单击连接 1==表单提交 2==后退 3==重新载入(刷新) 4==表单重新提交  5==其他类型", 0, SDT_INT},
    /*007*/    {"URL", "即将导航的URL", 0, SDT_TEXT},

    /*008*/    {"载入URL", "载入完毕的URL", 0, SDT_TEXT},
    /*009*/    {"载入状态", "载入的状态,可以使用 #载入状态_ 开头的常量判断, 0==载入成功 1==载入失败 2==取消载入", 0, SDT_INT},
    /*010*/    {"失败原因", "当文档载入失败时,输出失败原因", 0, SDT_TEXT},

    /*011*/    {"级别", "消息级别 , #消息级别_ 开头的常量", 0, SDT_INT},
    /*012*/    {"行号", "消息产生的行号", 0, SDT_INT},
    /*013*/    {"消息", "控制台消息", 0, SDT_TEXT},
    /*014*/    {"来源名称", "来源名称", 0, SDT_TEXT},
    /*015*/    {"堆栈跟踪", "堆栈跟踪", 0, SDT_TEXT},

    /*016*/    {"消息", "即将弹出的消息", 0, SDT_TEXT},

    /*017*/    {"消息", "即将弹出的消息", 0, SDT_TEXT},

    /*018*/    {"提示信息", "输入框的提示信息", 0, SDT_TEXT},
    /*019*/    {"默认值", "输入框的默认值", 0, SDT_TEXT},

    /*020*/    {"文件URL", "准备下载的文件URL", 0, SDT_TEXT},

    /*021*/    {"Url", "要载入的URL", 0, SDT_TEXT},
    /*022*/    {"Job", "Job", 0, SDT_INT},

    /*023*/    {"Url", "要载入的URL", 0, SDT_TEXT},
    /*024*/    {"Job", "Job", 0, SDT_INT},
    /*025*/    {"数据字节集指针", "请使用 指针到字节集() 命令获取", 0, SDT_INT},
    /*026*/    {"数据长度", "数据长度", 0, SDT_INT},

    /*027*/    {"Url", "鼠标移动到A元素范围内时触发,并传入A元素连接", 0, SDT_TEXT},

    /*028*/    {"键代码", "为键常量值，如：“#F1键”、“#回车键” 等等。具体所有的键常量见库常量表。\r\n", 0, SDT_INT},
    /*029*/    {"功能键状态", "用于查看在按下本键的同时各功能键是否被同时按下。可以为以下常量值或其和： "
                    "1、#Ctrl键状态； 2、#Shift键状态； 4、#Alt键状态。要判断是否同时按下了某个功能键，"
                    "在此参数的值与想要得知的功能键的状态常量值之间使用“位与”命令进行比较。如果所得的结果不为零，则表示同时按下了此功能键。\r\n", 0, SDT_INT},


    /*030*/    {"横向位置", "指示鼠标在当前所处窗口组件中的横向位置。", 0, SDT_INT},
    /*031*/    {"纵向位置", "指示鼠标在当前所处窗口组件中的纵向位置。", 0, SDT_INT},
    /*032*/    {"功能键状态", "用于查看在按下本键的同时各功能键是否被同时按下。可以为以下常量值或其和："
                    "1、#Ctrl键状态； 2、#Shift键状态； 4、#Alt键状态。要判断是否同时按下了某个功能键，"
                    "在此参数的值与想要得知的功能键的状态常量值之间使用“位与”命令进行比较。如果所得的结果不为零，则表示同时按下了此功能键。", 0, SDT_INT},

    /*033*/    {"字符代码", "表明所按下的字符键所对应的字符代码，可以使用“字符”命令取出所对应的具体字符。", 0, SDT_INT},


    /*034*/    {"滚动距离", "表明鼠标滚轮所滚动的距离，大于零表示向前滚动，小于零表示向后滚动。", 0, SDT_INT},
    /*035*/    {"功能键状态", "用于查看各功能键是否被同时按下。可以为以下常量值或其和： 1、#Ctrl键状态； 2、#Shift键状态； 4、#Alt键状态。"
                        "要判断是否同时按下了某个功能键，在此参数的值与想要得知的功能键的状态常量值之间使用“位与”命令进行比较。"
                        "如果所得的结果不为零，则表示同时按下了此功能键。", 0, SDT_INT},

    /*036*/    {"导航类型", "即将导航的类型  0==单击连接 1==表单提交 2==后退 3==重新载入(刷新) 4==表单重新提交  5==其他类型", 0, SDT_INT},
    /*037*/    {"URL", "即将导航的URL", 0, SDT_TEXT},
    /*038*/    {"windowFeatures", "该参数仅用于 精易Web浏览器.载入新窗口()", 0, SDT_INT},

    /*039*/    {"webView", "载入新窗口的webView", 0, SDT_INT},

    /*040*/    {"父窗口句柄", "载入新窗口的父窗口句柄,句柄无效则载入失败,默认为空,无父窗口\r\n"
                    "    提供父窗口句柄后,新载入的窗口永远会在父窗口的顶层,与易语言的 \"载入()\" 第二个参数填写父窗口一样的效果", EAS_BY_REF, SDT_INT},
    /*041*/    {"新左边", "载入新窗口的左边位置,相对屏幕坐标。默认为 CW_USEDEFAULT == -2147483648", EAS_BY_REF, SDT_INT},
    /*042*/    {"新顶边", "载入新窗口的顶边位置,相对屏幕坐标。默认为 CW_USEDEFAULT == -2147483648", EAS_BY_REF, SDT_INT},
    /*043*/    {"新宽度", "载入新窗口的宽度,相对屏幕坐标。默认为 CW_USEDEFAULT == -2147483648", EAS_BY_REF, SDT_INT},
    /*044*/    {"新高度", "载入新窗口的高度,相对屏幕坐标。默认为 CW_USEDEFAULT == -2147483648", EAS_BY_REF, SDT_INT},


    /*045*/    {"窗口句柄", "被载入对话框的窗口句柄", 0, SDT_INT},
    /*046*/    {"窗口类型", "#窗口类型_ 开头常量", 0, SDT_INT},
    /*047*/    {"备用", "备用参数,值为0", 0, SDT_INT},

    /*048*/    {"url", "改变图标的网页", 0, SDT_TEXT},
    /*049*/    {"图标指针", "指向图标数据的地址, 有可能为0, 此值必须判断是否为空指针", 0, SDT_INT},
    /*050*/    {"图标长度", "图标长度", 0, SDT_INT},

    /*051*/    {"文件路径", "打开文件的文件路径", EAS_BY_REF, SDT_TEXT},
    /*052*/    {"备用", "备用参数,值为0", 0, SDT_INT},
    /*053*/    {"文件路径", "保存文件的文件路径", EAS_BY_REF, SDT_TEXT},
    /*054*/    {"备用", "备用参数,值为0", 0, SDT_INT},


};

//精易Web浏览器  下的事件
static EVENT_INFO2 s_objEventiext_Webkit_static_var_00[] =
{
    //1=事件名称,2=事件详细解释,3=返回值类型,EV_RETURN_ 绝对不能定义成返回文本、字节集、复合类型等需要空间释放代码的数据类型。
    //4=事件的参数数目,5=事件参数,6=返回值类型

    {"文档就绪", "文档就绪时触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 0, _SDT_NULL},
    {"标题被改变", "网页标题被改变时触发此事件", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 1, _SDT_NULL},
    {"URL被改变", "URL被改变时触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 2, _SDT_NULL},
    {"即将导航到新地址", "将要导航到新的网址前触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 4, SDT_BOOL},
    {"即将导航到新窗口", "即将导航到新窗口,返回(真) 在新窗口打开网址,返回(假) 自行处理", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 6, SDT_BOOL},
    {"文档载入完毕", "网页文档载入完毕时触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 8, _SDT_NULL},
    {"控台消息输出", "当产生控制台消息时触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 5, s_eventArgInfo_iext_Webkit + 11, _SDT_NULL},
    {"Alert将被调用", "当网页中的alert被调用的时候触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 16, _SDT_NULL},
    {"Confirm将被调用", "当网页中的Confirm被调用的时候触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 17, SDT_BOOL},
    {"Prompt将被调用", "当网页中的Prompt被调用的时候触发", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 18, SDT_BOOL},
    {"正在下载文件", "正在下载文件时触发本事件", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 20, SDT_BOOL},
    {"Url载入开始", "Url开始载入,任何网络请求发起前会触发此事件.\r\n"\
    "此回调功能强大, 在回调里, 如果对参数job设置了\"特殊功能.拦截网络请求 (Job)\", 则表示内核会缓存获取到的网络数据, 并在这次网络请求 结束后调用\"Url载入结束\", 同时传递缓存的数据。在此期间, 内核不会处理网络数据。 如果本事件返回真, 则表示不会发送网络请求。 如果返回假, 则表示触发该请求。",\
    _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 21, SDT_BOOL},
    {"Url载入结束", "Url载入结束, 注意！如果没有在\"Url载入开始\"时设置\"特殊功能.拦截网络请求 (Job)\", 则该回调不会被触发。", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 4, s_eventArgInfo_iext_Webkit + 23, SDT_BOOL},
    {"鼠标移入链接", "鼠标移动到A元素范围内时触发,并传入A元素连接", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 27, _SDT_NULL},


    {"左键按下", "处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去;如果不返回值或返回真, 则将此事件继续传递到所属对象上去。",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"左键放开", "处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去;如果不返回值或返回真, 则将此事件继续传递到所属对象上去。",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"左键双击", "处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去;如果不返回值或返回真, 则将此事件继续传递到所属对象上去。",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"右键按下", "处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去;如果不返回值或返回真, 则将此事件继续传递到所属对象上去。",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"右键放开", "处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去;如果不返回值或返回真, 则将此事件继续传递到所属对象上去。",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"鼠标移动", "处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去;如果不返回值或返回真, 则将此事件继续传递到所属对象上去。",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"焦点获取", "当对象获得输入焦点时产生本事件。所谓\"输入焦点\", 即当前用户按键操作所对应的目标对象。"
        "譬如：用户正在编辑框中输入文本, 那么此编辑框就具有输入焦点, 因为它将获得目前用户所进行的所有按键操作。"
        "所谓\"获得\"或者\"失去\"输入焦点, 即当前用户按键操作所对应的目标对象发生转移。"
        "譬如：现在用户正在编辑框1中输入文本, 突然使用鼠标或其它方法切换到了编辑框2上去继续输入。"
        "那么此时, 编辑框1就\"失去\"了输入焦点, 编辑框2就\"得到\"了输入焦点, "
        "因为在此以后用户所进行的所有按键操作都将被编辑框2所获得。", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 0, 0, _SDT_NULL},
    {"焦点消失", "当对象失去输入焦点时产生本事件。", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 0, 0, _SDT_NULL},
    {"某键按下", "此事件当用户按下一个键时发生。处理本事件的子程序如果返回假, 则取消本事件, 不再将此按键事件传递到所属对象上去;"
        "如果不返回值或返回真, 则将此事件继续传递到所属对象上去。", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 28, SDT_BOOL},
    {"某键放开", "此事件当用户放开以前按下的一个键时发生。处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去;"
        "如果不返回值或返回真, 则将此事件继续传递到所属对象上去。", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 28, SDT_BOOL},
    {"输入字符", "当用户按下和松开一个字符键时发生此事件。字符键包括任何可打印的键盘字符及回车(Enter)和退格(BackSpace)键。"
        "在用户事件处理子程序中, 将事件处理完毕后可返回一个字符代码, 用于替换将继续传递到所属对象上字符键事件中的字符代码;"
        "如果返回 0, 则取消此事件, 不再将此字符输入事件传递到所属对象上去;"
        "如果事件处理完毕后没有返回值, 则将本字符键事件继续原样传递到所属对象上去。",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 33, SDT_INT},
    {"滚轮滚动", "当用户滚动鼠标滚轮时产生本事件。处理本事件的子程序如果返回假, 则取消本事件, 不再将此事件传递到所属对象上去;"
        "如果不返回值或返回真, 则将此事件继续传递到所属对象上去。", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 34, SDT_BOOL},

    {"新窗口即将被创建", "即将导航到新窗口事件下即将打开新窗口", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 5, s_eventArgInfo_iext_Webkit + 40, _SDT_NULL},
    {"新窗口创建完毕", "即将导航到新窗口事件下打开的新窗口创建完毕", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 39, _SDT_NULL},
    {"新窗口可否关闭", "即将导航到新窗口事件下打开的新窗口可否被关闭,返回假则不允许关闭", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 39, SDT_BOOL},
    {"新窗口被销毁", "即将导航到新窗口事件下打开的新窗口被销毁", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 39, _SDT_NULL},

    {"即将弹出对话框", "即将弹出对话框时触发,现阶段只会触发打开/保存文件对话框\r\n"
        "        触发此事件时,已创建窗口,但可能尚未确定其最终大小和位置,并且可能尚未建立其父窗口.尽管尚未收到WM_NCCREATE或WM_CREATE消息, 但可以将消息发送到新创建的窗口",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2 | EV_IS_HIDED, 3, s_eventArgInfo_iext_Webkit + 45, SDT_BOOL},
    {"网页图标改变", "网页图标改变时触发该事件", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 48, _SDT_NULL},
    {"打开文件对话框", "当网页即将打开打开文件对话框时弹出, 返回假则不弹出对话框, 【注意, 此事件是全局, 只有第一个精易web浏览器组件才会触发此事件】", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 51, SDT_BOOL},
    {"保存文件对话框", "当网页即将保存打开文件对话框时弹出, 返回假则不弹出对话框, 【注意, 此事件是全局, 只有第一个精易web浏览器组件才会触发此事件】", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 53, SDT_BOOL},
};

const int s_objEventiext_Webkit_static_var_count_00 = sizeof(s_objEventiext_Webkit_static_var_00) / sizeof(s_objEventiext_Webkit_static_var_00[0]);

void head_dtType_Webkit(LIB_DATA_TYPE_INFO& dtType)
{
    dtType.m_szName             = "精易Web浏览器";
    dtType.m_szEgName           = "webkit";
    dtType.m_szExplain          = "精易论坛浏览器";
    dtType.m_nCmdCount          = s_dtCmdIndexiext_Webkit_static_var_count_04;
    dtType.m_pnCmdsIndex        = s_dtCmdIndexiext_Webkit_static_var_04;    // 方法索引数组
    dtType.m_dwState            = _DT_OS(__OS_WIN) | LDT_WIN_UNIT;
    dtType.m_dwUnitBmpID        = IDB_BITMAP_ICON;

    dtType.m_nEventCount        = s_objEventiext_Webkit_static_var_count_00;
    dtType.m_pEventBegin        = s_objEventiext_Webkit_static_var_00;  // 事件

    dtType.m_nPropertyCount     = s_objPropertyiext_Webkit_static_var_count_00;
    dtType.m_pPropertyBegin     = s_objPropertyiext_Webkit_static_var_00;   // 属性
    dtType.m_pfnGetInterface    = wke_GetInterface_webkit;  // 接口, 命名规则是 库名_ + GetInterface + _组件名
    dtType.m_nElementCount      = 0;
    dtType.m_pElementBegin      = 0;
}
void head_dtType_NewWnd(LIB_DATA_TYPE_INFO& dtType)
{
    dtType.m_szName             = "弹出窗口操作";
    dtType.m_szEgName           = "newWindow";
    dtType.m_szExplain          = "用于操作新弹出的窗口";
    dtType.m_nCmdCount          = s_dtCmdIndexiext_NewWindow_static_var_count_09;
    dtType.m_pnCmdsIndex        = s_dtCmdIndexiext_NewWindow_static_var_09;
    dtType.m_dwState            = _DT_OS(__OS_WIN);
    dtType.m_dwUnitBmpID        = 0;
    dtType.m_nEventCount        = 0;
    dtType.m_pEventBegin        = 0;
    dtType.m_nPropertyCount     = 0;
    dtType.m_pPropertyBegin     = 0;
    dtType.m_pfnGetInterface    = 0;
    dtType.m_nElementCount      = 0;
    dtType.m_pElementBegin      = 0;
}