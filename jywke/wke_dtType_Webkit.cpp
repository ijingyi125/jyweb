#include "wke_webkit_header.h"
#include "Resource.h"

//����Web�����  �µķ�������
static INT s_dtCmdIndexiext_Webkit_static_var_04[] =
{
    220, 0,   1,   2,   3,   4,   5,   6,   7,    8,   180, 9,
    10,  188, 161, 166, 11,  12,  13,  168, 14,   15,  16,  17,  18,  19,
    20,  154, 157, 158, 171, 189, 191, 198, 203,
};
// ����Web��������
static int s_dtCmdIndexiext_Webkit_static_var_count_04 = sizeof(s_dtCmdIndexiext_Webkit_static_var_04) / sizeof(s_dtCmdIndexiext_Webkit_static_var_04[0]);

// �´���  �µķ�������
static INT s_dtCmdIndexiext_NewWindow_static_var_09[] =
{
    216, 220, 217, 182, 186, 183, 184, 185, 0,   1,   2,   3,   4,   5,   6,   7,    8,   180,   9,
    10,  188, 161, 166, 11,  12,  13,  168, 14,  15,  16,  17,  18,  19,
    20,  154, 157, 158, 171, 187, 189, 190, 191, 198, 203,
};
// �´��ڷ�������
static int s_dtCmdIndexiext_NewWindow_static_var_count_09 = sizeof(s_dtCmdIndexiext_NewWindow_static_var_09) / sizeof(s_dtCmdIndexiext_NewWindow_static_var_09[0]);


// ����Web�����  �µ�����
static UNIT_PROPERTY s_objPropertyiext_Webkit_static_var_00[] =
{
    // FIXED_WIN_UNIT_PROPERTY,    // ������ϴ˺�, ����ֱ��չ��, �����չ��
    //1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�����
    /*000*/ {"���", "left", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
    /*001*/ {"����", "top", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
    /*002*/ {"���", "width", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
    /*003*/ {"�߶�", "height", NULL, UD_INT, _PROP_OS(OS_ALL), NULL},
    /*004*/ {"���", "tag", NULL, UD_TEXT, _PROP_OS(OS_ALL), NULL},
    /*005*/ {"����", "visible", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
    /*006*/ {"��ֹ", "disable", NULL, UD_BOOL, _PROP_OS(OS_ALL), NULL},
    /*007*/ {"���ָ��", "MousePointer", NULL, UD_CURSOR, _PROP_OS(OS_ALL), NULL},


    //1=������, 2=Ӣ��������, 3=���Խ���, 4=���Ե���������UD_,5=���Եı�־, 6=˳���¼���еı�ѡ�ı�UW_(����UD_FILE_NAME), ��һ���մ�������
    {"URL", "GetCurrentPageUrl", "��ת��ָ��url,���߻�ȡ���õ�url\r\n"
        "        ȡֵ��ȡ�����õ�ֵ,�����Ҫ��ȡ��ǰ�������ʵ��url,��ʹ�� \"����Web�����.ȡ��ҳURL()\" ����ȡ\r\n"
        "        �������� \"����Web�����.�����ҳ()\" Ψһ��������,�����Ի��¼���õ�url��ַ,�Ҳ�����url��ַ�ı䡣", UD_TEXT, _PROP_OS(__OS_WIN), 0},
    {"��ҳ����", "GetCurrentPageTitle", "��ǰ��ҳ����", UD_TEXT, _PROP_OS(__OS_WIN) | UW_ONLY_READ, 0},
    {"��ֹF5ˢ��", "CancelF5Reload", "��ֹF5ˢ��", UD_BOOL, _PROP_OS(__OS_WIN), 0},
    {"��ֹCookies", "IsEnableCookie", "��ֹCookie", UD_BOOL, _PROP_OS(__OS_WIN), 0},
    {"����Ŀ¼", "CachePath", "����Ŀ¼", UD_TEXT, _PROP_OS(__OS_WIN), 0 },
    {"CookieĿ¼", "CookiePath", "Cookie���Ŀ¼", UD_TEXT, _PROP_OS(__OS_WIN), 0},
    {"UserAgent", "UserAgent", "�����UA,\r\n\r\nע��: �����UA���ܻ�Ӱ�쵽ĳ����ҳ����������,�������UA���ĳ����ҳ���ֱ�������,�뻻һ��UA", UD_EDIT_PICK_TEXT, _PROP_OS(__OS_WIN), \
    "Ĭ��UA\0""iPhone X\0""iPad Pro\0""��׿Galaxy S5\0""Winsows Safari\0""Winsows Chrome\0""Winsows Firefox\0""Winsows Opera\0""Winsows IE9\0""\0"},//"Winsows IE8\0""Winsows IE7\0"
    {"�������ʱԤ��", 0, \
    "�����Խ��ڵ�ǰ����ڼ���Ч, ��ÿ�δ���������������Դ���ļ�ʱ��Ĭ�ϻ�ԭΪ�١��˾ټȿɷ����û�������ڼ�ʵʱԤ����ҳ(�Ա���������С������), ������Ч��ֹԤ�������趨�Ĳ���ȫ��ҳ��",\
    UD_BOOL, _PROP_OS(__OS_WIN), 0},
    {"�����´��ڴ�", "newWindow", "Ĭ��Ϊ��,���ڱ����ڴ�,������ \"�����������´���\" �¼�\r\n"
    "        Ϊ��ʱ�ᴥ�� \"�����������´���\" �¼�", UD_BOOL, _PROP_OS(__OS_WIN), 0},

};
const int s_objPropertyiext_Webkit_static_var_count_00 = sizeof(s_objPropertyiext_Webkit_static_var_00) / sizeof(s_objPropertyiext_Webkit_static_var_00[0]);


// ����Web������µ��¼�����
static EVENT_ARG_INFO2 s_eventArgInfo_iext_Webkit[] =
{
    //1=��������,2=��������,3=�Ƿ�ο�,4=��������SDT_

    /*000*/    {"�������ID", "��ҳ�ĵ��������ڲ���ܾ���ʱ����", 0, SDT_INT},

    /*001*/    {"����", "��ҳ���ⱻ����ʱ����", 0, SDT_TEXT},

    /*002*/    {"URL", "�ı��URL", 0, SDT_TEXT},
    /*003*/    {"�������ID", "��ǰURL�����ĸ����ID", 0, SDT_INT},

    /*004*/    {"��������", "��������������  0==��������(���a��ǩ����) 1==���ύ(���form����) 2==ǰ�����˴��� 3==��������(ˢ��) 4==���¼��ش���  5==��������", 0, SDT_INT},
    /*005*/    {"URL", "����������URL", 0, SDT_TEXT},

    /*006*/    {"��������", "��������������  0==�������� 1==���ύ 2==���� 3==��������(ˢ��) 4==�������ύ  5==��������", 0, SDT_INT},
    /*007*/    {"URL", "����������URL", 0, SDT_TEXT},

    /*008*/    {"����URL", "������ϵ�URL", 0, SDT_TEXT},
    /*009*/    {"����״̬", "�����״̬,����ʹ�� #����״̬_ ��ͷ�ĳ����ж�, 0==����ɹ� 1==����ʧ�� 2==ȡ������", 0, SDT_INT},
    /*010*/    {"ʧ��ԭ��", "���ĵ�����ʧ��ʱ,���ʧ��ԭ��", 0, SDT_TEXT},

    /*011*/    {"����", "��Ϣ���� , #��Ϣ����_ ��ͷ�ĳ���", 0, SDT_INT},
    /*012*/    {"�к�", "��Ϣ�������к�", 0, SDT_INT},
    /*013*/    {"��Ϣ", "����̨��Ϣ", 0, SDT_TEXT},
    /*014*/    {"��Դ����", "��Դ����", 0, SDT_TEXT},
    /*015*/    {"��ջ����", "��ջ����", 0, SDT_TEXT},

    /*016*/    {"��Ϣ", "������������Ϣ", 0, SDT_TEXT},

    /*017*/    {"��Ϣ", "������������Ϣ", 0, SDT_TEXT},

    /*018*/    {"��ʾ��Ϣ", "��������ʾ��Ϣ", 0, SDT_TEXT},
    /*019*/    {"Ĭ��ֵ", "������Ĭ��ֵ", 0, SDT_TEXT},

    /*020*/    {"�ļ�URL", "׼�����ص��ļ�URL", 0, SDT_TEXT},

    /*021*/    {"Url", "Ҫ�����URL", 0, SDT_TEXT},
    /*022*/    {"Job", "Job", 0, SDT_INT},

    /*023*/    {"Url", "Ҫ�����URL", 0, SDT_TEXT},
    /*024*/    {"Job", "Job", 0, SDT_INT},
    /*025*/    {"�����ֽڼ�ָ��", "��ʹ�� ָ�뵽�ֽڼ�() �����ȡ", 0, SDT_INT},
    /*026*/    {"���ݳ���", "���ݳ���", 0, SDT_INT},

    /*027*/    {"Url", "����ƶ���AԪ�ط�Χ��ʱ����,������AԪ������", 0, SDT_TEXT},

    /*028*/    {"������", "Ϊ������ֵ���磺��#F1��������#�س����� �ȵȡ��������еļ��������ⳣ����\r\n", 0, SDT_INT},
    /*029*/    {"���ܼ�״̬", "���ڲ鿴�ڰ��±�����ͬʱ�����ܼ��Ƿ�ͬʱ���¡�����Ϊ���³���ֵ����ͣ� "
                    "1��#Ctrl��״̬�� 2��#Shift��״̬�� 4��#Alt��״̬��Ҫ�ж��Ƿ�ͬʱ������ĳ�����ܼ���"
                    "�ڴ˲�����ֵ����Ҫ��֪�Ĺ��ܼ���״̬����ֵ֮��ʹ�á�λ�롱������бȽϡ�������õĽ����Ϊ�㣬���ʾͬʱ�����˴˹��ܼ���\r\n", 0, SDT_INT},


    /*030*/    {"����λ��", "ָʾ����ڵ�ǰ������������еĺ���λ�á�", 0, SDT_INT},
    /*031*/    {"����λ��", "ָʾ����ڵ�ǰ������������е�����λ�á�", 0, SDT_INT},
    /*032*/    {"���ܼ�״̬", "���ڲ鿴�ڰ��±�����ͬʱ�����ܼ��Ƿ�ͬʱ���¡�����Ϊ���³���ֵ����ͣ�"
                    "1��#Ctrl��״̬�� 2��#Shift��״̬�� 4��#Alt��״̬��Ҫ�ж��Ƿ�ͬʱ������ĳ�����ܼ���"
                    "�ڴ˲�����ֵ����Ҫ��֪�Ĺ��ܼ���״̬����ֵ֮��ʹ�á�λ�롱������бȽϡ�������õĽ����Ϊ�㣬���ʾͬʱ�����˴˹��ܼ���", 0, SDT_INT},

    /*033*/    {"�ַ�����", "���������µ��ַ�������Ӧ���ַ����룬����ʹ�á��ַ�������ȡ������Ӧ�ľ����ַ���", 0, SDT_INT},


    /*034*/    {"��������", "�����������������ľ��룬�������ʾ��ǰ������С�����ʾ��������", 0, SDT_INT},
    /*035*/    {"���ܼ�״̬", "���ڲ鿴�����ܼ��Ƿ�ͬʱ���¡�����Ϊ���³���ֵ����ͣ� 1��#Ctrl��״̬�� 2��#Shift��״̬�� 4��#Alt��״̬��"
                        "Ҫ�ж��Ƿ�ͬʱ������ĳ�����ܼ����ڴ˲�����ֵ����Ҫ��֪�Ĺ��ܼ���״̬����ֵ֮��ʹ�á�λ�롱������бȽϡ�"
                        "������õĽ����Ϊ�㣬���ʾͬʱ�����˴˹��ܼ���", 0, SDT_INT},

    /*036*/    {"��������", "��������������  0==�������� 1==���ύ 2==���� 3==��������(ˢ��) 4==�������ύ  5==��������", 0, SDT_INT},
    /*037*/    {"URL", "����������URL", 0, SDT_TEXT},
    /*038*/    {"windowFeatures", "�ò��������� ����Web�����.�����´���()", 0, SDT_INT},

    /*039*/    {"webView", "�����´��ڵ�webView", 0, SDT_INT},

    /*040*/    {"�����ھ��", "�����´��ڵĸ����ھ��,�����Ч������ʧ��,Ĭ��Ϊ��,�޸�����\r\n"
                    "    �ṩ�����ھ����,������Ĵ�����Զ���ڸ����ڵĶ���,�������Ե� \"����()\" �ڶ���������д������һ����Ч��", EAS_BY_REF, SDT_INT},
    /*041*/    {"�����", "�����´��ڵ����λ��,�����Ļ���ꡣĬ��Ϊ CW_USEDEFAULT == -2147483648", EAS_BY_REF, SDT_INT},
    /*042*/    {"�¶���", "�����´��ڵĶ���λ��,�����Ļ���ꡣĬ��Ϊ CW_USEDEFAULT == -2147483648", EAS_BY_REF, SDT_INT},
    /*043*/    {"�¿��", "�����´��ڵĿ��,�����Ļ���ꡣĬ��Ϊ CW_USEDEFAULT == -2147483648", EAS_BY_REF, SDT_INT},
    /*044*/    {"�¸߶�", "�����´��ڵĸ߶�,�����Ļ���ꡣĬ��Ϊ CW_USEDEFAULT == -2147483648", EAS_BY_REF, SDT_INT},


    /*045*/    {"���ھ��", "������Ի���Ĵ��ھ��", 0, SDT_INT},
    /*046*/    {"��������", "#��������_ ��ͷ����", 0, SDT_INT},
    /*047*/    {"����", "���ò���,ֵΪ0", 0, SDT_INT},

    /*048*/    {"url", "�ı�ͼ�����ҳ", 0, SDT_TEXT},
    /*049*/    {"ͼ��ָ��", "ָ��ͼ�����ݵĵ�ַ, �п���Ϊ0, ��ֵ�����ж��Ƿ�Ϊ��ָ��", 0, SDT_INT},
    /*050*/    {"ͼ�곤��", "ͼ�곤��", 0, SDT_INT},

    /*051*/    {"�ļ�·��", "���ļ����ļ�·��", EAS_BY_REF, SDT_TEXT},
    /*052*/    {"����", "���ò���,ֵΪ0", 0, SDT_INT},
    /*053*/    {"�ļ�·��", "�����ļ����ļ�·��", EAS_BY_REF, SDT_TEXT},
    /*054*/    {"����", "���ò���,ֵΪ0", 0, SDT_INT},


};

//����Web�����  �µ��¼�
static EVENT_INFO2 s_objEventiext_Webkit_static_var_00[] =
{
    //1=�¼�����,2=�¼���ϸ����,3=����ֵ����,EV_RETURN_ ���Բ��ܶ���ɷ����ı����ֽڼ����������͵���Ҫ�ռ��ͷŴ�����������͡�
    //4=�¼��Ĳ�����Ŀ,5=�¼�����,6=����ֵ����

    {"�ĵ�����", "�ĵ�����ʱ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 0, _SDT_NULL},
    {"���ⱻ�ı�", "��ҳ���ⱻ�ı�ʱ�������¼�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 1, _SDT_NULL},
    {"URL���ı�", "URL���ı�ʱ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 2, _SDT_NULL},
    {"�����������µ�ַ", "��Ҫ�������µ���ַǰ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 4, SDT_BOOL},
    {"�����������´���", "�����������´���,����(��) ���´��ڴ���ַ,����(��) ���д���", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 6, SDT_BOOL},
    {"�ĵ��������", "��ҳ�ĵ��������ʱ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 8, _SDT_NULL},
    {"��̨��Ϣ���", "����������̨��Ϣʱ����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 5, s_eventArgInfo_iext_Webkit + 11, _SDT_NULL},
    {"Alert��������", "����ҳ�е�alert�����õ�ʱ�򴥷�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 16, _SDT_NULL},
    {"Confirm��������", "����ҳ�е�Confirm�����õ�ʱ�򴥷�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 17, SDT_BOOL},
    {"Prompt��������", "����ҳ�е�Prompt�����õ�ʱ�򴥷�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 18, SDT_BOOL},
    {"���������ļ�", "���������ļ�ʱ�������¼�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 20, SDT_BOOL},
    {"Url���뿪ʼ", "Url��ʼ����,�κ�����������ǰ�ᴥ�����¼�.\r\n"\
    "�˻ص�����ǿ��, �ڻص���, ����Բ���job������\"���⹦��.������������ (Job)\", ���ʾ�ں˻Ỻ���ȡ������������, ��������������� ���������\"Url�������\", ͬʱ���ݻ�������ݡ��ڴ��ڼ�, �ں˲��ᴦ���������ݡ� ������¼�������, ���ʾ���ᷢ���������� ������ؼ�, ���ʾ����������",\
    _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 21, SDT_BOOL},
    {"Url�������", "Url�������, ע�⣡���û����\"Url���뿪ʼ\"ʱ����\"���⹦��.������������ (Job)\", ��ûص����ᱻ������", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 4, s_eventArgInfo_iext_Webkit + 23, SDT_BOOL},
    {"�����������", "����ƶ���AԪ�ط�Χ��ʱ����,������AԪ������", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 27, _SDT_NULL},


    {"�������", "�����¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ����¼����ݵ�����������ȥ;���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"����ſ�", "�����¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ����¼����ݵ�����������ȥ;���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"���˫��", "�����¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ����¼����ݵ�����������ȥ;���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"�Ҽ�����", "�����¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ����¼����ݵ�����������ȥ;���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"�Ҽ��ſ�", "�����¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ����¼����ݵ�����������ȥ;���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"����ƶ�", "�����¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ����¼����ݵ�����������ȥ;���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 30, SDT_BOOL},
    {"�����ȡ", "�����������뽹��ʱ�������¼�����ν\"���뽹��\", ����ǰ�û�������������Ӧ��Ŀ�����"
        "Ʃ�磺�û����ڱ༭���������ı�, ��ô�˱༭��;������뽹��, ��Ϊ�������Ŀǰ�û������е����а���������"
        "��ν\"���\"����\"ʧȥ\"���뽹��, ����ǰ�û�������������Ӧ��Ŀ�������ת�ơ�"
        "Ʃ�磺�����û����ڱ༭��1�������ı�, ͻȻʹ���������������л����˱༭��2��ȥ�������롣"
        "��ô��ʱ, �༭��1��\"ʧȥ\"�����뽹��, �༭��2��\"�õ�\"�����뽹��, "
        "��Ϊ�ڴ��Ժ��û������е����а��������������༭��2����á�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 0, 0, _SDT_NULL},
    {"������ʧ", "������ʧȥ���뽹��ʱ�������¼���", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 0, 0, _SDT_NULL},
    {"ĳ������", "���¼����û�����һ����ʱ�����������¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ��˰����¼����ݵ�����������ȥ;"
        "���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 28, SDT_BOOL},
    {"ĳ���ſ�", "���¼����û��ſ���ǰ���µ�һ����ʱ�����������¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ����¼����ݵ�����������ȥ;"
        "���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 28, SDT_BOOL},
    {"�����ַ�", "���û����º��ɿ�һ���ַ���ʱ�������¼����ַ��������κοɴ�ӡ�ļ����ַ����س�(Enter)���˸�(BackSpace)����"
        "���û��¼������ӳ�����, ���¼�������Ϻ�ɷ���һ���ַ�����, �����滻���������ݵ������������ַ����¼��е��ַ�����;"
        "������� 0, ��ȡ�����¼�, ���ٽ����ַ������¼����ݵ�����������ȥ;"
        "����¼�������Ϻ�û�з���ֵ, �򽫱��ַ����¼�����ԭ�����ݵ�����������ȥ��",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 33, SDT_INT},
    {"���ֹ���", "���û�����������ʱ�������¼��������¼����ӳ���������ؼ�, ��ȡ�����¼�, ���ٽ����¼����ݵ�����������ȥ;"
        "���������ֵ�򷵻���, �򽫴��¼��������ݵ�����������ȥ��", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 2, s_eventArgInfo_iext_Webkit + 34, SDT_BOOL},

    {"�´��ڼ���������", "�����������´����¼��¼������´���", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 5, s_eventArgInfo_iext_Webkit + 40, _SDT_NULL},
    {"�´��ڴ������", "�����������´����¼��´򿪵��´��ڴ������", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 39, _SDT_NULL},
    {"�´��ڿɷ�ر�", "�����������´����¼��´򿪵��´��ڿɷ񱻹ر�,���ؼ�������ر�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 39, SDT_BOOL},
    {"�´��ڱ�����", "�����������´����¼��´򿪵��´��ڱ�����", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 39, _SDT_NULL},

    {"���������Ի���", "���������Ի���ʱ����,�ֽ׶�ֻ�ᴥ����/�����ļ��Ի���\r\n"
        "        �������¼�ʱ,�Ѵ�������,��������δȷ�������մ�С��λ��,���ҿ�����δ�����丸����.������δ�յ�WM_NCCREATE��WM_CREATE��Ϣ, �����Խ���Ϣ���͵��´����Ĵ���",
        _EVENT_OS(__OS_WIN) | EV_IS_VER2 | EV_IS_HIDED, 3, s_eventArgInfo_iext_Webkit + 45, SDT_BOOL},
    {"��ҳͼ��ı�", "��ҳͼ��ı�ʱ�������¼�", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 3, s_eventArgInfo_iext_Webkit + 48, _SDT_NULL},
    {"���ļ��Ի���", "����ҳ�����򿪴��ļ��Ի���ʱ����, ���ؼ��򲻵����Ի���, ��ע��, ���¼���ȫ��, ֻ�е�һ������web���������Żᴥ�����¼���", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 51, SDT_BOOL},
    {"�����ļ��Ի���", "����ҳ����������ļ��Ի���ʱ����, ���ؼ��򲻵����Ի���, ��ע��, ���¼���ȫ��, ֻ�е�һ������web���������Żᴥ�����¼���", _EVENT_OS(__OS_WIN) | EV_IS_VER2, 1, s_eventArgInfo_iext_Webkit + 53, SDT_BOOL},
};

const int s_objEventiext_Webkit_static_var_count_00 = sizeof(s_objEventiext_Webkit_static_var_00) / sizeof(s_objEventiext_Webkit_static_var_00[0]);

void head_dtType_Webkit(LIB_DATA_TYPE_INFO& dtType)
{
    dtType.m_szName             = "����Web�����";
    dtType.m_szEgName           = "webkit";
    dtType.m_szExplain          = "������̳�����";
    dtType.m_nCmdCount          = s_dtCmdIndexiext_Webkit_static_var_count_04;
    dtType.m_pnCmdsIndex        = s_dtCmdIndexiext_Webkit_static_var_04;    // ������������
    dtType.m_dwState            = _DT_OS(__OS_WIN) | LDT_WIN_UNIT;
    dtType.m_dwUnitBmpID        = IDB_BITMAP_ICON;

    dtType.m_nEventCount        = s_objEventiext_Webkit_static_var_count_00;
    dtType.m_pEventBegin        = s_objEventiext_Webkit_static_var_00;  // �¼�

    dtType.m_nPropertyCount     = s_objPropertyiext_Webkit_static_var_count_00;
    dtType.m_pPropertyBegin     = s_objPropertyiext_Webkit_static_var_00;   // ����
    dtType.m_pfnGetInterface    = wke_GetInterface_webkit;  // �ӿ�, ���������� ����_ + GetInterface + _�����
    dtType.m_nElementCount      = 0;
    dtType.m_pElementBegin      = 0;
}
void head_dtType_NewWnd(LIB_DATA_TYPE_INFO& dtType)
{
    dtType.m_szName             = "�������ڲ���";
    dtType.m_szEgName           = "newWindow";
    dtType.m_szExplain          = "���ڲ����µ����Ĵ���";
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