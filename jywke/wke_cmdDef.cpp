#include "wke_typedef.h"


#if !defined(__E_STATIC_LIB)

static ARG_INFO g_Args_jywebkit[] =
{
    //以下为 精易web浏览器 方法下的参数

    // 1=参数名称, 2=参数详细解释, 3=指定图像索引,从1开始,0表示无, 4=图像数目(用作动画)
    // 5=参数类型, 6=参数默认值,   7=参数标志 AS_ 开头常量


    /*000*/    {"URL地址", "即将浏览的URL地址,如果url地址有中文,请传递utf8编码文本.", 0, 0, SDT_TEXT, 0, NULL},

    /*001*/    {"HTML文本", "一段HTML文本,请传递与网页相同编码的文本.", 0, 0, SDT_TEXT, 0, NULL},

    /*002*/    {"HTML文件", "HTML文件名,如果路径有中文,请传递utf8编码文本.", 0, 0, SDT_TEXT, 0, NULL},

    /*003*/    {"URL", "待设置cookie的网站域名,如果url地址有中文,请传递utf8编码文本.", 0, 0, SDT_TEXT, 0, NULL},
    /*004*/    {"COOKIE", "要设置的Cookie，多个cookie使用;隔开，例如： a=1;b=2;c=3;d=4;", 0, 0, SDT_TEXT, 0, NULL},

    /*005*/    {"操作类型", "0 = 清空所有Cookie , 1 = 清空所有session , 2 = 刷新cookie文件  3= 重新载入cookie文件", 0, 0, SDT_INT, 0, NULL},

    /*006*/    {"UserAgent", "UserAgent文本,如果url地址有中文,请传递utf8编码文本.", 0, 0, SDT_TEXT, 0, NULL},

    /*007*/    {"代理类型", "#代理类型_开头的常量", 0, 0, SDT_INT, 0, NULL},
    /*008*/    {"代理地址", "代理ip与端口,如 122.132.123.123:666", 0, 0, SDT_TEXT, 0, NULL},
    /*009*/    {"用户名", "代理用户名,没有请留空", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*010*/    {"密码", "代理密码,没有请留空", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*011*/    {"音量", "欲设置的音量", 0, 0, SDT_INT, 0, NULL},

    /*012*/    {"延时时长", "单位毫秒,延迟让miniblink垃圾回收", 0, 0, SDT_INT, 0, NULL},

    /*013*/    {"键名", "设置键名后可通过这个键名取到设置的值", 0, 0, SDT_TEXT, 0, NULL},
    /*014*/    {"键值", "需要设置的键值", 0, 0, SDT_INT, 0, NULL},

    /*015*/    {"键名", "置用户数据() 里设置的键名", 0, 0, SDT_TEXT, 0, NULL},

    /*016*/    {"URL", "待设置cookie的网站域名,如果url地址有中文,请传递utf8编码文本.", 0, 0, SDT_TEXT, 0, NULL},
    /*017*/    {"COOKIE", "要设置的Cookie，格式需要相与curl的格式。例如：abc=1;expires=Monday, 1-Jun-2019 00:01:01 GMT; path=/; secure", 0, 0, SDT_TEXT, 0, NULL},

    /*018*/    {"是否禁止", "真 = 禁止, 假 = 不禁止, 留空 = 取值, 该参数不为空时返回值无意义。", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*019*/    {"左边", "留空或者小于0 = 0, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*020*/    {"顶边", "留空或者小于0 = 0, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*021*/    {"宽度", "留空或者小于0 = 浏览器宽度,默认为浏览器宽度", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*022*/    {"高度", "留空或者小于0 = 浏览器高度,默认为浏览器高度", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*023*/    {"框架ID", "ID从1开始,为空或者小于0,默认取主框架", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    ///*023*/    {"框架ID", "框架,比如 window.frames[0] = 第一个框架,为空则取主框架文本", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*024*/    {"填表模式", "默认为 #填表模式_JS表达式, 请使用 #填表模式_ 开头的常量,具体看常量说明", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*025*/    {"选择表达式", "为空则取整个网页,选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*026*/    {"元素下标", "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*027*/    {"weiView", "为空或者为0,则清除附加,非0值如果不是一个webView则调用失败,新窗口创建完毕 事件中的webView,或者其他方式获取到的webView", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*028*/    {"url", "待设置cookie的网站域名,如果url地址有中文,请传递utf8编码文本.", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*029*/    {"cookie", "待设置的cookie, cookie必须符合curl的cookie写法", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*030*/    {"设备字符串", "设备的字符串。可取值有：\r\n"\
                    "	1. \"navigator.maxTouchPoints\"此时 \"整数参数\" 需要被设置，表示 touch 的点数。\r\n"\
                    "	2. \"navigator.platform\"此时 \"文本参数\" 需要被设置，表示js里获取的 navigator.platform字符串。\r\n"\
                    "	3. \"navigator.hardwareConcurrency\"此时 \"整数参数\" 需要被设置，表示js里获取的 navigator.hardwareConcurrency 整数值。\r\n"\
                    "	4. \"screen.width\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.width 整数值。\r\n"\
                    "	5. \"screen.height\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.height 整数值。\r\n"
                    "	6. \"screen.availWidth\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.availWidth 整数值。\r\n"\
                    "	7. \"screen.availHeight\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.availHeight 整数值。\r\n"\
                    "	8. \"screen.pixelDepth\"此时 \"整数参数\" 需要被设置，表示js里获取的 screen.pixelDepth 整数值。\r\n"\
                    "	9. \"screen.pixelDepth\"目前等价于\"screen.pixelDepth\"。\r\n"\
                    "	10.\"window.devicePixelRatio\"同上", 0, 0, SDT_TEXT, 0, 0},
    /*031*/    {"文本参数", "文本参数", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*032*/    {"整数参数", "整数参数", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*033*/    {"浮点参数", "浮点参数", 0, 0, SDT_FLOAT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*034*/    {"事件类型", "浏览器事件_ 开头常量, 需要的子程序参数和返回值请参考常量说明", 0, 0, SDT_INT, 0, 0},
    /*035*/    {"回调地址", "详细定义请查看常量, 为空则取消该事件", 0, 0, SDT_SUB_PTR, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*036*/    {"参数", "传入回调的参数", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*037*/    {"访问器", "逻辑型 回调函数(整数型 参数, 文本型 cookie名, 文本型 cookie值, 文本型 域名, 文本型 路径, 整数型 仅发送https请求, 整数型 仅发送http请求, 整数型传址 是否设置cookie过期事件); ", 0, 0, SDT_SUB_PTR, 0, NULL},
    /*038*/    {"参数", "访问器参数, 传入参数1回调地址中的值", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*039*/    {"格式化文本串", "格式化文本串", 0, 0, SDT_TEXT, 0, NULL},
    /*040*/    {"参数", "日期时间型请使用 %s, 内部会转换成 \"2020-01-01 01:01:01\" 这种格式\r\n"
                "	字节集和逻辑型也使用 %s, 内部会转成文本使用, 其他没有说明的类型, 就按c/c++格式化字符串传递", 0, 0, _SDT_ALL, 0, NULL},

    /*041*/    {"数据", "把所有能转换成文本的都转换成文本", 0, 0, SDT_TEXT, 0, NULL},

    /*042*/    {"回调函数", "接收获取网页图标的回调, 无返回值 回调(文本型 url, 整数型 图标指针, 整数型 图标长度)", 0, 0, SDT_SUB_PTR, 0, NULL},

    /*043*/    {"父窗口句柄", "创建新浏览器的父窗口句柄, 如果句柄为0或无效句柄, 则创建一个弹出式窗口, 如果当前程序没有消息循环, 则需要自己处理消息循环", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*044*/    {"左", "创建浏览框左边的位置, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*045*/    {"顶", "创建浏览框顶边的位置, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*046*/    {"宽", "创建浏览框的宽度, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*047*/    {"高", "创建浏览框的高度, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*048*/    {"存在销毁", "如果当前类已经创建了浏览框, 则先销毁在创建, 否则返回假, 默认为真, 销毁后创建", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*049*/    {"子类化函数", "提供一个子程序, 接收窗口的消息过程 函数原型为: 整数型 窗口过程(整数型 窗口句柄, 整数型 消息值, 整数型 参数1, 整数型 参数2)", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*050*/    {"旧窗口过程", "参数7不为空时有效, 接收原窗口消息过程", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*051*/    {"窗口销毁退出消息循环", "如果为真, 则该窗口收到 WM_DESTROY 消息时会调用 PostQuitMessage() 退出消息循环, 如果有自己子类化, 则在收到 WM_DESTROY 消息时需要调用 CallWindowProcW() 把消息转到原过程, 或者自己调用 PostQuitMessage(), 否则该函数不会返回", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*052*/    {"窗口句柄", "目前参数2为空时该参数无效", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*053*/    {"显示窗口", "是否显示窗口, 为真则先显示窗口在调用消息循环, 否则直接调用消息循环", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*054*/    {"父窗口句柄", "创建新浏览器的父窗口句柄, 如果当前程序没有消息循环, 则需要自己处理消息循环", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*055*/    {"左", "创建浏览框左边的位置, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*056*/    {"顶", "创建浏览框顶边的位置, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*057*/    {"宽", "创建浏览框的宽度, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*058*/    {"高", "创建浏览框的高度, 默认为0", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*059*/    {"存在销毁", "如果当前类已经创建了浏览框, 则先销毁在创建, 否则返回假, 默认为真, 销毁后创建", 0, 0, SDT_BOOL, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*060*/    {"窗口类型", "0=弹出式窗口, 1=分层窗口, 其他=子窗口, 请按照类型填写, 分层窗口需要挂接绘画事件自行绘制到你要显示的地方", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

};

static ARG_INFO g_Args_ajax[] =
{
    //ajax方法下的参数
    /*000*/    {"Key", "http请求头字段名称,如 Content-Type UserAgent Referer 等等", 0, 0, SDT_TEXT, 0, NULL},
    /*001*/    {"Value", "http请求头字段对应的值", 0, 0, SDT_TEXT, 0, NULL},

    /*002*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*003*/    {"url", "请求的URL", 0, 0, SDT_TEXT, 0, NULL},
    /*004*/    {"回调方法", "当Ajax与服务器交互完成将调用此方法,成功返回服务器返回文本,错误返回状态码", 0, 0, SDT_SUB_PTR, 0, NULL},

    /*005*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*006*/    {"url", "请求的URL", 0, 0, SDT_TEXT, 0, NULL},
    /*007*/    {"是否是JSON", "提交的数据格式是否是JSON", 0, 0, SDT_BOOL, 0, NULL},
    /*008*/    {"提交数据", "要提交的POST数据", 0, 0, SDT_TEXT, 0, NULL},
    /*009*/    {"回调方法", "当Ajax与服务器交互完成将调用此方法,成功返回服务器返回文本,错误返回状态码", 0, 0, SDT_SUB_PTR, 0, NULL},
};

static ARG_INFO g_Args_JavaScript[] =
{
    //JavaScript 方法下的参数
    /*000*/    {"值对象", "值对象,执行结果指针", 0, 0, SDT_INT64, 0, NULL},

    /*001*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*002*/    {"框架ID", "框架ID", 0, 0, SDT_INT, 0, NULL},
    /*003*/    {"script", "javascript脚本", 0, 0, SDT_TEXT, 0, NULL},
    /*004*/    {"是否包含在Function中执行", "script代码会在mb内部自动被包裹在一个function(){}中。所以使用的变量会被隔离,此处确定是否包裹在function中", 0, 0, SDT_BOOL, 0, NULL},

    /*005*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*006*/    {"script", "待运行的脚本", 0, 0, SDT_TEXT, 0, NULL},
    /*007*/    {"是否有返回值", "JS是否有返回值", 0, 0, SDT_BOOL, 0, NULL},

    /*008*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*009*/    {"script", "待运行的脚本", 0, 0, SDT_TEXT, 0, NULL},

    /*010*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*011*/    {"表达式", "待计算的表达式", 0, 0, SDT_TEXT, 0, NULL},
    /*012*/    {"是否有返回值", "JS是否有返回值", 0, 0, SDT_BOOL, 0, NULL},

    /*013*/    {"执行状态", "请使用 全局创建JS执行状态() 获取", 0, 0, SDT_INT, 0, NULL},
    /*014*/    {"表达式", "待计算的表达式", 0, 0, SDT_TEXT, 0, NULL},

    /*015*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},

    /*016*/    {"执行状态", "请使用 全局创建JS执行状态() 获取", 0, 0, SDT_INT, 0, NULL},
    /*017*/    {"待转换子程序", "易语言中的子程序指针", 0, 0, SDT_SUB_PTR, 0, NULL},

    /*018*/    {"执行状态", "请使用 全局创建JS执行状态() 获取", 0, 0, SDT_INT, 0, NULL},
    /*019*/    {"属性名称", "对象属性名称", 0, 0, SDT_TEXT, 0, NULL},

    /*020*/    {"执行状态", "请使用 全局创建JS执行状态() 获取", 0, 0, SDT_INT, 0, NULL},
    /*021*/    {"属性名称", "对象属性名称", 0, 0, SDT_TEXT, 0, NULL},
    /*022*/    {"属性值", "对象属性名称", 0, 0, SDT_INT64, 0, NULL},

    /*023*/    {"执行状态", "请使用 全局创建JS执行状态() 获取", 0, 0, SDT_INT, 0, NULL},
    /*024*/    {"js函数", "js函数", 0, 0, SDT_INT64, 0, NULL},
    /*025*/    {"参数数组", "传入的参数数组", 0, 0, SDT_INT64, 0, AS_RECEIVE_ARRAY_DATA | AS_DEFAULT_VALUE_IS_EMPTY},

    /*026*/    {"执行状态", "请使用 全局创建JS执行状态() 获取", 0, 0, SDT_INT, 0, NULL},
    /*027*/    {"js函数", "js函数", 0, 0, SDT_INT64, 0, NULL},
    /*028*/    {"this对象", "函数的this对象", 0, 0, SDT_INT64, 0, NULL},
    /*029*/    {"参数数组", "传入的参数数组", 0, 0, SDT_INT64, 0, AS_RECEIVE_ARRAY_DATA | AS_DEFAULT_VALUE_IS_EMPTY},

    /*030*/    {"执行状态", "请使用 全局创建JS执行状态() 获取", 0, 0, SDT_INT, 0, NULL},

    /*031*/    {"Js函数名称", "js中函数的名称", 0, 0, SDT_TEXT, 0, NULL},
    /*032*/    {"易语言子程序指针", "易语言中的子程序指针。 该子程序有一个长整数型参数（表示js环境），返回长整数型。如果参数或返回值错误，程序将会崩溃！！", 0, 0, SDT_SUB_PTR, 0, NULL},
    /*033*/    {"参数个数", "传入的参数个数", 0, 0, SDT_INT, 0, NULL},

    /*034*/    {"执行状态", "执行状态,回调函数第一个参数", 0, 0, SDT_INT, 0, NULL},

    /*035*/    {"执行状态", "执行状态,回调函数第一个参数", 0, 0, SDT_INT, 0, NULL},
    /*036*/    {"参数序号", "参数下标,从0开始计算", 0, 0, SDT_INT, 0, NULL},

    /*037*/    {"执行状态", "执行状态,回调函数第一个参数", 0, 0, SDT_INT, 0, NULL},
    /*038*/    {"参数序号", "参数下标,从0开始计算", 0, 0, SDT_INT, 0, NULL},

    /*039*/    {"执行状态", "执行状态,回调函数第一个参数", 0, 0, SDT_INT, 0, NULL},
    /*040*/    {"参数序号", "参数下标,从0开始计算", 0, 0, SDT_INT, 0, NULL},

    /*041*/    {"执行状态", "执行状态,回调函数第一个参数", 0, 0, SDT_INT, 0, NULL},
    /*042*/    {"参数序号", "参数下标,从0开始计算", 0, 0, SDT_INT, 0, NULL},

    /*043*/    {"执行状态", "执行状态,回调函数第一个参数", 0, 0, SDT_INT, 0, NULL},
    /*044*/    {"参数序号", "参数下标,从0开始计算", 0, 0, SDT_INT, 0, NULL},

    /*045*/    {"执行状态", "执行状态", 0, 0, SDT_INT, 0, NULL},
    /*046*/    {"值对象", "值对象,执行结果指针", 0, 0, SDT_INT64, 0, NULL},

    /*047*/    {"执行状态", "执行状态", 0, 0, SDT_INT, 0, NULL},
    /*048*/    {"值对象", "值对象,执行结果指针", 0, 0, SDT_INT64, 0, NULL},

    /*049*/    {"执行状态", "执行状态", 0, 0, SDT_INT, 0, NULL},
    /*050*/    {"值对象", "值对象,执行结果指针", 0, 0, SDT_INT64, 0, NULL},

    /*051*/    {"执行状态", "执行状态", 0, 0, SDT_INT, 0, NULL},
    /*052*/    {"值对象", "值对象,执行结果指针", 0, 0, SDT_INT64, 0, NULL},

    /*053*/    {"执行状态", "执行状态", 0, 0, SDT_INT, 0, NULL},
    /*054*/    {"值对象", "值对象,执行结果指针", 0, 0, SDT_INT64, 0, NULL},

    /*055*/    {"待设置值", "待设置值", 0, 0, SDT_INT, 0, NULL},

    /*056*/    {"执行状态", "执行状态", 0, 0, SDT_INT, 0, NULL},
    /*057*/    {"待设置值", "待设置值", 0, 0, SDT_TEXT, 0, NULL},

    /*058*/    {"待设置值", "待设置值", 0, 0, SDT_BOOL, 0, NULL},

    /*059*/    {"待设置值", "待设置值", 0, 0, SDT_FLOAT, 0, NULL},

    /*060*/    {"待设置值", "待设置值", 0, 0, SDT_DOUBLE, 0, NULL},


    /*061*/    {"执行状态", "请使用 全局创建JS执行状态() 获取", 0, 0, SDT_INT, 0, NULL},
    /*062*/    {"object对象", "js的object", 0, 0, SDT_INT64, 0, NULL},
    /*063*/    {"要取的属性名称", "属性名", 0, 0, SDT_TEXT, 0, 0},

    /*064*/    {"执行状态", "执行状态", 0, 0, SDT_INT, 0, NULL},
    /*065*/    {"参数序号", "参数下标,从0开始计算", 0, 0, SDT_INT, 0, NULL},
};

static ARG_INFO g_Args_tb[] =
{
    //填表方法下的参数
    /*000*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*001*/    {"填表模式", "请使用 #填表模式_ 开头的常量,具体看常量说明", 0, 0, SDT_INT, 0, NULL},
    /*002*/    {"选择表达式", "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*003*/    {"元素下标", "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*004*/    {"属性名称", "需要获取属性值的名称 如: name", 0, 0, SDT_TEXT, 0, NULL},
    /*005*/    {"属性值", "需要获取属性值的名称 如: name", 0, 0, SDT_TEXT, 0, NULL},

    /*006*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*007*/    {"填表模式", "请使用 #填表模式_ 开头的常量,具体看常量说明", 0, 0, SDT_INT, 0, NULL},
    /*008*/    {"选择表达式", "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*009*/    {"元素下标", "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*010*/    {"选中状态", "设置为真代表选中该选择框,为假则取消选中", 0, 0, SDT_BOOL, 0, NULL},

    /*011*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*012*/    {"填表模式", "请使用 #填表模式_ 开头的常量,具体看常量说明", 0, 0, SDT_INT, 0, NULL},
    /*013*/    {"选择表达式", "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*014*/    {"元素下标", "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*015*/    {"选中项", "选中组合框中的第几项,序号从0开始", 0, 0, SDT_INT, 0, NULL},


    /*016*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*017*/    {"标题", "标题", 0, 0, SDT_TEXT, 0, NULL},

    /*018*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*019*/    {"缩放阀值", "缩放阀值", 0, 0, SDT_FLOAT, 0, NULL},

    /*020*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*021*/    {"纵向位置", "设置纵向滚动条位置", 0, 0, SDT_INT, 0, NULL},

    /*022*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*023*/    {"横向位置", "设置横向滚动条位置", 0, 0, SDT_INT, 0, NULL},


    /*024*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*025*/    {"是否开启编辑状态", "为真则打开编辑模式 为假则关闭", 0, 0, SDT_BOOL, 0, NULL},

    /*026*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*027*/    {"frameid", "框架ID , 1是当前网页主框架", 0, 0, SDT_INT, 0, NULL},


    /*028*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*029*/    {"方法名称", "比如 getContent() setContent('content') 或 sc.getContent('aaaa')", 0, 0, SDT_TEXT, 0, NULL},

    /*030*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*031*/    {"填表模式", "请使用 #填表模式_ 开头的常量,具体看常量说明", 0, 0, SDT_INT, 0, NULL},
    /*032*/    {"选择表达式", "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*033*/    {"元素下标", "如果选择表达式返回的结果为多个的时候,默认点击第一个元素,此处可以指定点击元素的下标,下标从1开始,默认为1", 0, 0, SDT_INT, 1, AS_HAS_DEFAULT_VALUE},
    /*034*/    {"是否可视", "真=可视,假=不可视", 0, 0, SDT_BOOL, 1, NULL},

    /*035*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*036*/    {"填表模式", "请使用 #填表模式_ 开头的常量,具体看常量说明", 0, 0, SDT_INT, 0, NULL},
    /*037*/    {"选择表达式", "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*038*/    {"偏移", "方法会计算元素所有父级的横坐标叠加,但鼠标模拟操作可能会对元素范围内不同的点进行操作.用以达到更好的模拟效果", 0, 0, SDT_INT, 0, AS_HAS_DEFAULT_VALUE},
    /*039*/    {"下标", "如果返回的元素大于1个,可以使用该下标指定元素下标 ,如使用这个选择器 div.myclass>ul>li  则会返回类型名为 myclass 的DIV下的UL下的li集合 ,此处就可以指定取第几个LI,下标从1开始,默认为1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*040*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*041*/    {"填表模式", "请使用 #填表模式_ 开头的常量,具体看常量说明", 0, 0, SDT_INT, 0, NULL},
    /*042*/    {"选择表达式", "选择表达式,与选择填表模式相关,精易模块模式 id==xxx class==xxx xxx=xxx, JS模式 #id .class div.myclass>ul>li.active", 0, 0, SDT_TEXT, 0, NULL},
    /*043*/    {"下标", "如果返回的元素大于1个,可以使用该下标指定元素下标 ,如使用这个选择器 div.myclass>ul>li  则会返回类型名为 myclass 的DIV下的UL下的li集合 ,此处就可以指定取第几个LI,下标从1开始,默认为1", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},
    /*044*/    {"事件名称", "请使用 #事件_ 开头的常量", 0, 0, SDT_TEXT, 0, NULL},
    /*045*/    {"关闭事件冒泡", "关闭冒泡请设置为 真", 0, 0, SDT_BOOL, 0, AS_HAS_DEFAULT_VALUE},
    /*046*/    {"事件参数", "可以触发时间时传递事件对象参数,可为空", 0, 0, SDT_TEXT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*047*/    {"WKE_TB", "另一个WKE_填表 变量", 0, 0, SDT_TYPE_WKE_TB, 0, NULL},
};

static ARG_INFO g_Args_SpecialFunction[] =
{
    //特殊功能方法下的参数
    /*000*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*001*/    {"是否开启", "真 代表开启 , 假关闭  默认开启", 0, 0, SDT_BOOL, 0, NULL},

    /*002*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*003*/    {"是否开启", "真 代表开启 , 假关闭  默认开启", 0, 0, SDT_BOOL, 0, NULL},

    /*004*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*005*/    {"是否开启", "真 代表开启 , 假关闭  默认开启", 0, 0, SDT_BOOL, 0, NULL},

    /*006*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},

    /*007*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*008*/    {"是否开启", "真 代表开启 , 假关闭  默认开启", 0, 0, SDT_BOOL, 0, NULL},

    /*009*/    {"Job", "Url载入开始 中传入的参数", 0, 0, SDT_INT, 0, NULL},

    /*010*/    {"Job", "Url载入开始 中传入的参数", 0, 0, SDT_INT, 0, NULL},
    /*011*/    {"HTTP头名称", "Http头字段名称 如 Accept , Content-Type 等...", 0, 0, SDT_TEXT, 0, NULL},
    /*012*/    {"HTTP头值", "Http头字段对应值, 如: text/javascript , appliction/json 等...", 0, 0, SDT_TEXT, 0, NULL},

    /*013*/    {"Job", "Url载入开始 中传入的参数", 0, 0, SDT_INT, 0, NULL},
    /*014*/    {"MIME类型", "MIMEType...", 0, 0, SDT_TEXT, 0, NULL},

    /*015*/    {"Job", "Url载入开始 中传入的参数", 0, 0, SDT_INT, 0, NULL},
    /*016*/    {"Url", "URL...", 0, 0, SDT_TEXT, 0, NULL},

    /*017*/    {"Job", "Url载入开始 中传入的参数", 0, 0, SDT_INT, 0, NULL},
    /*018*/    {"数据", "数据", 0, 0, SDT_BIN, 0,   NULL},
    /*019*/    {"数据长度", "数据长度", 0, 0, SDT_INT, 0, AS_DEFAULT_VALUE_IS_EMPTY},

    /*020*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*021*/    {"是否开启", "真 代表开启 , 假关闭  默认开启", 0, 0, SDT_BOOL, 0, NULL},

    /*022*/    {"WebView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*023*/    {"是否开启", "真 代表开启 , 假关闭  默认开启", 0, 0, SDT_BOOL, 0, NULL},

    /*024*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*025*/    {"debugString", "showDevTools ", 0, 0, SDT_TEXT, 0, NULL},
    /*026*/    {"configParam", ", 注意param此时必须是utf8编码", 0, 0, SDT_TEXT, 0, NULL},

    /*027*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},

    /*028*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*029*/    {"frameid", "框架ID", 0, 0, SDT_INT, 0, NULL},

    /*030*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*031*/    {"frameid", "框架ID", 0, 0, SDT_INT, 0, NULL},

    /*032*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*033*/    {"x", "横坐标", 0, 0, SDT_INT, 0, NULL},
    /*034*/    {"y", "纵坐标", 0, 0, SDT_INT, 0, NULL},

    /*035*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*036*/    {"x", "横坐标", 0, 0, SDT_INT, 0, NULL},
    /*037*/    {"y", "纵坐标", 0, 0, SDT_INT, 0, NULL},

    /*038*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*039*/    {"x", "横坐标", 0, 0, SDT_INT, 0, NULL},
    /*040*/    {"y", "纵坐标", 0, 0, SDT_INT, 0, NULL},

    /*041*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*042*/    {"x", "横坐标", 0, 0, SDT_INT, 0, NULL},
    /*043*/    {"y", "纵坐标", 0, 0, SDT_INT, 0, NULL},

    /*044*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*045*/    {"x", "横坐标", 0, 0, SDT_INT, 0, NULL},
    /*046*/    {"y", "纵坐标", 0, 0, SDT_INT, 0, NULL},

    /*047*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*048*/    {"x", "横坐标", 0, 0, SDT_INT, 0, NULL},
    /*049*/    {"y", "纵坐标", 0, 0, SDT_INT, 0, NULL},

    /*050*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*051*/    {"x", "横坐标", 0, 0, SDT_INT, 0, NULL},
    /*052*/    {"y", "纵坐标", 0, 0, SDT_INT, 0, NULL},

    /*053*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*054*/    {"键代码", "键代码请使用 如 #退格键....", 0, 0, SDT_INT, 0, NULL},

    /*055*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*056*/    {"键代码", "键代码请使用 如 #K键 #A键....", 0, 0, SDT_INT, 0, NULL},

    /*057*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*058*/    {"键代码", "键代码请使用 如 #K键 #A键....", 0, 0, SDT_INT, 0, NULL},

    /*059*/    {"Job", "Url载入开始 中传入的参数", 0, 0, SDT_INT, 0, NULL},
    /*060*/    {"Job", "Url载入开始 中传入的参数", 0, 0, SDT_INT, 0, NULL},

    /*061*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*062*/    {"元素组", "元素组", 0, 0, SDT_TYPE_POSTELEMENTS, 0, NULL},

    /*063*/    {"post数据", "创建post数据返回的值", 0, 0, SDT_INT, 0, NULL},
    /*064*/    {"post数据", "创建post数据组返回的值", 0, 0, SDT_INT, 0, NULL},

    /*065*/    {"webView", "WebView指针,请使用 精易WEB浏览器.取WebView()  获取", 0, 0, SDT_INT, 0, NULL},
    /*066*/    {"url", "post的url", 0, 0, SDT_TEXT, 0, NULL},
    /*067*/    {"post数据", "post的数据", 0, 0, SDT_BIN, 0, NULL},

    /*068*/    { "Job", "事件里的参数", 0, 0, SDT_INT, 0, NULL },
    /*069*/    { "key", "要获取哪个头", 0, 0, SDT_TEXT, 0, NULL },


};

//所有命令的参数定义
static ARG_INFO g_Args_All[] =
{
    // 1=参数名称, 2=参数详细解释, 3=指定图像索引,从1开始,0表示无, 4=图像数目(用作动画)
    // 5=参数类型, 6=参数默认值,   7=参数标志 AS_ 开头常量

    /*000*/    {"dll路径", "node.dll的完整路径", 0, 0, SDT_TEXT, 0, NULL},
    /*001*/    {"utf8文本", "utf8编码的文本,只支持文本指针,文本型,和字节集", 0, 0, _SDT_ALL, 0, NULL},
    /*002*/    {"ansi文本", "ansi编码的文本", 0, 0, SDT_TEXT, 0, NULL},
    /*003*/    {"Unicode文本", "Unicode编码的文本", 0, 0, SDT_BIN, 0, NULL},
    /*004*/    {"工作集大小", "返回程序当前工作集的内存大小,单位为字节", 0, 0, SDT_INT, 0, AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY},
    /*005*/    {"峰值工作集", "返回程序峰值工作集的内存大小,单位为字节", 0, 0, SDT_INT, 0, AS_RECEIVE_VAR | AS_DEFAULT_VALUE_IS_EMPTY},
    /*006*/    {"格式", "详情请查看c语言介绍, 常用的%s=文本(日期时间型), %d=整数,%u=无符号整数,%p=指针,%x16=进制,%%=%....", 0, 0, SDT_TEXT, 0,  0},
    /*007*/    {"参数", "", 0, 0, _SDT_ALL, 0, 0},

};

// 定义易语言需要的命令信息数组
#define WKE_DEF_CMDINFO(_index, _szName, _szEgName, _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo) \
    { _szName, ______E_FNENAME(_szEgName), _szExplain, _shtCategory, _wState, _dtRetValType, _wReserved, _shtUserLevel, _shtBitmapIndex, _shtBitmapCount, _nArgCount, _pBeginArgInfo },


CMD_INFO g_cmdInfo_wke_global_var[] =
{
    WKE_DEF(WKE_DEF_CMDINFO)
};

int g_cmdInfo_wke_global_var_count = sizeof(g_cmdInfo_wke_global_var) / sizeof(g_cmdInfo_wke_global_var[0]);



#endif







