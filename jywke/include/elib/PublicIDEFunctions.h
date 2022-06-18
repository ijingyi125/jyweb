
#ifndef __PUBLIC_IDE_FUNCTIONS_H__
#define __PUBLIC_IDE_FUNCTIONS_H__

// IDE�ӿڹ��ܱ�
// ע��: ���й��ܾ�ͨ�� NES_RUN_FUNC ֪ͨ����(��lib2.h),����ù��ܱ���������,δ�������򷵻ؼ�.

//-------------------------------------------------------------------  ������ݽṹ�ͺ궨��

// FN_REPLACE_ALL2����ʹ��
typedef struct
{
    const char* m_szFind;  // ����Ѱ�ҵ��ı�
    const char* m_szReplace;  // �����滻���ı�
    BOOL m_blCase;  // �Ƿ�������ĸ��Сд
}
REPLACE_ALL2_PARAM;

// FN_ADD_TAB����ʹ��
typedef struct
{
    HWND m_hWnd;
    HICON m_hIcon;
    LPTSTR m_szCaption;
    LPTSTR m_szToolTip;
}
ADD_TAB_INF;

//------------------------------------  FN_GET_PRG_TEXT��FN_GET_PRG_HELP����ʹ��

#define VT_DLL_CMD_NAME              51  // DllCmd����
#define VT_DLL_CMD_RET_TYPE          52  // DllCmd����ֵ����
#define VT_DLL_CMD_EXPLAIN           53  // DllCmd��ע
#define VT_DLL_CMD_EXPORT            54  // DllCmd����
#define VT_DLL_CMD_DEFINE_BEGIN      VT_DLL_CMD_NAME
#define VT_DLL_CMD_DEFINE_END        VT_DLL_CMD_EXPORT
#define VT_DLL_LIB_FILE_NAME         VT_DLL_CMD_DEFINE_END + 50   // Dll���ļ���
#define VT_DLL_CMD_IN_LIB_NAME       VT_DLL_LIB_FILE_NAME + 51    // DllCmd�ڿ��е�����
#define VT_DLL_CMD_ARG_NAME          VT_DLL_CMD_IN_LIB_NAME + 51  // DllCmd��������
#define VT_DLL_CMD_ARG_TYPE          VT_DLL_CMD_IN_LIB_NAME + 52  // DllCmd��������
#define VT_DLL_CMD_ARG_POINTER_TYPE  VT_DLL_CMD_IN_LIB_NAME + 53  // DllCmd�����ο�����
#define VT_DLL_CMD_ARG_ARY_TYPE      VT_DLL_CMD_IN_LIB_NAME + 54  // DllCmd������������
#define VT_DLL_CMD_ARG_EXPLAIN       VT_DLL_CMD_IN_LIB_NAME + 55  // DllCmd������ע
#define VT_DLL_CMD_ARG_DEFINE_BEGIN  VT_DLL_CMD_ARG_NAME
#define VT_DLL_CMD_ARG_DEFINE_END    VT_DLL_CMD_ARG_EXPLAIN

#define VT_USER_TYPE_NAME            VT_DLL_CMD_ARG_DEFINE_END + 51  // �Զ���������������
#define VT_USER_TYPE_EXPLAIN         VT_DLL_CMD_ARG_DEFINE_END + 52  // �Զ����������ͱ�ע
#define VT_USER_TYPE_EXPORT          VT_DLL_CMD_ARG_DEFINE_END + 53  // �Զ����������͹���
#define VT_USER_TYPE_DEFINE_BEGIN    VT_USER_TYPE_NAME
#define VT_USER_TYPE_DEFINE_END      VT_USER_TYPE_EXPORT
#define VT_ELEMENT_NAME              VT_USER_TYPE_DEFINE_END + 50  // �������ͳ�Ա����
#define VT_ELEMENT_TYPE              VT_USER_TYPE_DEFINE_END + 51  // �������ͳ�Ա����
#define VT_ELEMENT_ARY_TYPE          VT_USER_TYPE_DEFINE_END + 52  // �������ͳ�Ա��������
#define VT_ELEMENT_EXPLAIN           VT_USER_TYPE_DEFINE_END + 53  // �������ͳ�Ա��ע
#define VT_ELEMENT_POINTER_TYPE      VT_USER_TYPE_DEFINE_END + 54  // �������ͳ�Ա�ο�����
#define VT_ELEMENT_DEFINE_BEGIN      VT_ELEMENT_NAME
#define VT_ELEMENT_DEFINE_END        VT_ELEMENT_POINTER_TYPE

#define VT_GLOBAL_VAR_NAME           VT_ELEMENT_DEFINE_END + 50  // ȫ�ֱ�������
#define VT_GLOBAL_VAR_TYPE           VT_ELEMENT_DEFINE_END + 51  // ȫ�ֱ�������
#define VT_GLOBAL_VAR_ARY_TYPE       VT_ELEMENT_DEFINE_END + 52  // ȫ�ֱ�����������
#define VT_GLOBAL_VAR_EXPLAIN        VT_ELEMENT_DEFINE_END + 53  // ȫ�ֱ�����ע
#define VT_GLOBAL_VAR_EXPORT         VT_ELEMENT_DEFINE_END + 54  // ȫ�ֱ�������
#define VT_GLOBAL_VAR_DEFINE_BEGIN   VT_GLOBAL_VAR_NAME
#define VT_GLOBAL_VAR_DEFINE_END     VT_GLOBAL_VAR_EXPORT

#define VT_CONST_RES_NAME            VT_GLOBAL_VAR_DEFINE_END + 50  // ������Դ����
#define VT_CONST_RES_VAULE           VT_GLOBAL_VAR_DEFINE_END + 51  // ������Դֵ
#define VT_CONST_RES_EXPLAIN         VT_GLOBAL_VAR_DEFINE_END + 52  // ������Դ��ע
#define VT_CONST_RES_EXPORT          VT_GLOBAL_VAR_DEFINE_END + 53  // ������Դ����
#define VT_CONST_RES_DEFINE_BEGIN    VT_CONST_RES_NAME
#define VT_CONST_RES_DEFINE_END      VT_CONST_RES_EXPORT

#define VT_PIC_RES_NAME              VT_CONST_RES_DEFINE_END + 50  // ͼƬ��Դ����
#define VT_PIC_RES_VAULE             VT_CONST_RES_DEFINE_END + 51  // ͼƬ��Դ����
#define VT_PIC_RES_EXPLAIN           VT_CONST_RES_DEFINE_END + 52  // ͼƬ��Դ��ע
#define VT_PIC_RES_EXPORT            VT_CONST_RES_DEFINE_END + 53  // ͼƬ��Դ����
#define VT_PIC_RES_DEFINE_BEGIN      VT_PIC_RES_NAME
#define VT_PIC_RES_DEFINE_END        VT_PIC_RES_EXPORT

#define VT_SOUND_RES_NAME            VT_PIC_RES_DEFINE_END + 50  // ������Դ����
#define VT_SOUND_RES_VAULE           VT_PIC_RES_DEFINE_END + 51  // ������Դ����
#define VT_SOUND_RES_EXPLAIN         VT_PIC_RES_DEFINE_END + 52  // ������Դ��ע
#define VT_SOUND_RES_EXPORT          VT_PIC_RES_DEFINE_END + 53  // ������Դ����
#define VT_SOUND_RES_DEFINE_BEGIN    VT_SOUND_RES_NAME
#define VT_SOUND_RES_DEFINE_END      VT_SOUND_RES_EXPORT

#define VT_MOD_NAME                  VT_SOUND_RES_DEFINE_END + 50  // ��������
#define VT_MOD_EXPLAIN               VT_SOUND_RES_DEFINE_END + 51  // ���򼯱�ע
#define VT_MOD_BASE_CLASS            VT_SOUND_RES_DEFINE_END + 52  // ����
#define VT_MOD_EXPORT                VT_SOUND_RES_DEFINE_END + 53  // ���
#define VT_MOD_DEFINE_BEGIN          VT_MOD_NAME
#define VT_MOD_DEFINE_END            VT_MOD_EXPORT

#define VT_MOD_VAR_NAME              VT_MOD_DEFINE_END + 49  // ���򼯱�������
#define VT_MOD_VAR_TYPE              VT_MOD_DEFINE_END + 50  // ���򼯱�������
#define VT_MOD_VAR_ARY_TYPE          VT_MOD_DEFINE_END + 51  // ���򼯱�����������
#define VT_MOD_VAR_EXPLAIN           VT_MOD_DEFINE_END + 52  // ���򼯱�����ע
#define VT_MOD_VAR_DEFINE_BEGIN      VT_MOD_VAR_NAME
#define VT_MOD_VAR_DEFINE_END        VT_MOD_VAR_EXPLAIN

#define VT_SUB_NAME                  VT_MOD_VAR_DEFINE_END + 51  // �ӳ�������
#define VT_SUB_RET_TYPE              VT_MOD_VAR_DEFINE_END + 52  // �ӳ��򷵻�ֵ����
#define VT_SUB_EPK_NAME              VT_MOD_VAR_DEFINE_END + 53  // �ӳ��������װ�����
#define VT_SUB_EXPLAIN               VT_MOD_VAR_DEFINE_END + 54  // �ӳ���ע
#define VT_SUB_EXPORT                VT_MOD_VAR_DEFINE_END + 55  // ���ӳ����Ƿ����
#define VT_SUB_DEFINE_BEGIN          VT_SUB_NAME
#define VT_SUB_DEFINE_END            VT_SUB_EXPORT

#define VT_SUB_ARG_NAME              VT_SUB_DEFINE_END + 50  // �ӳ����������
#define VT_SUB_ARG_TYPE              VT_SUB_DEFINE_END + 51  // �ӳ����������
#define VT_SUB_ARG_POINTER_TYPE      VT_SUB_DEFINE_END + 52  // �ӳ�������ο�����
#define VT_SUB_ARG_NULL_TYPE         VT_SUB_DEFINE_END + 53  // �ӳ������NULL����
#define VT_SUB_ARG_ARY_TYPE          VT_SUB_DEFINE_END + 54  // �ӳ��������������
#define VT_SUB_ARG_EXPLAIN           VT_SUB_DEFINE_END + 55  // �ӳ��������ע
#define VT_SUB_ARG_DEFINE_BEGIN      VT_SUB_ARG_NAME
#define VT_SUB_ARG_DEFINE_END        VT_SUB_ARG_EXPLAIN

#define VT_SUB_VAR_NAME              VT_SUB_ARG_DEFINE_END + 51  // �ӳ���ֲ���������
#define VT_SUB_VAR_TYPE              VT_SUB_ARG_DEFINE_END + 52  // �ӳ���ֲ���������
#define VT_SUB_VAR_STATIC_TYPE       VT_SUB_ARG_DEFINE_END + 53  // �ӳ���ֲ�������̬����
#define VT_SUB_VAR_ARY_TYPE          VT_SUB_ARG_DEFINE_END + 54  // �ӳ���ֲ�������������
#define VT_SUB_VAR_EXPLAIN           VT_SUB_ARG_DEFINE_END + 55  // �ӳ���ֲ�������ע
#define VT_SUB_VAR_DEFINE_BEGIN      VT_SUB_VAR_NAME
#define VT_SUB_VAR_DEFINE_END        VT_SUB_VAR_EXPLAIN
#define VT_SUB_PRG_ITEM              VT_SUB_VAR_DEFINE_END + 51  // �ӳ����е�����������.

typedef struct
{
    int m_nRowIndex;   // ָ������ȡ�ı���������,Ϊ-1��ʾʹ�õ�ǰ���������.
    int m_nColIndex;   // ָ������ȡ�ı���������,Ϊ-1��ʾʹ�õ�ǰ���������.
    char* m_pBuf;      // �ṩһ����������ַ,ΪNULLʱ���ܽ���m_nBufSize�з������軺�����ĳߴ�.
    int m_nBufSize;    // ���m_pBuf��ΪNULL,�û���Ҫ�ڴ˴��ṩΪm_pBuf������׼���ĳߴ�,����������������軺�����ĳߴ�.
    int m_nType;       // �����з��ص�ǰλ����������,Ϊ���ϵ�"VT_xxx"��ֵ.
    BOOL m_blIsTitle;  // �����з��ص�ǰλ���Ƿ�Ϊ��������
}
GET_PRG_TEXT_PARAM;

//-------------------------------------------------------------------
// �������(���λ��¼�ù����Ƿ���Ҫ��¼,����ֽڵĺ�7λ��¼����,�θ��ֽڼ�¼����):

#define FNT_SYS  0x00000000
#define FNT_MOVE  0x01000000
    #define FNST_MOVE_CARET    (FNT_MOVE | 0x010000)
    #define FNST_SCROLL_WND    (FNT_MOVE | 0x020000)
#define FNT_EDIT  0x02000000
    #define FNST_BLOCK_OPER    (FNT_EDIT | 0x010000)
    #define FNST_MODIFY        (FNT_EDIT | 0x020000)
    #define FNST_OTHER_MODIFY  (FNT_EDIT | 0x030000)
#define FNT_DOCUMENT  0x03000000
    #define FNST_FILE          (FNT_DOCUMENT | 0x010000)
#define FNT_OTHER  0x04000000
    #define FNST_STATE_OPER    (FNT_OTHER | 0x010000)
    #define FNST_OTHER         (FNT_OTHER | 0x020000)
#define FNT_EAPP  0x05000000
    #define FNST_DEBUG         (FNT_EAPP | 0x010000)
    #define FNST_RUN           (FNT_EAPP | 0x020000)
    #define FNST_ADDIN         (FNT_EAPP | 0x030000)

#define GetFuncParentType(dwFuncNO)  ((dwFuncNO) & 0x7f000000)
#define GetFuncType(dwFuncNO)  ((dwFuncNO) & 0x7fff0000)

//-------------------------------------------------------------------  ���ܱ�

// �չ���:
#define FN_NULL  0

//------------------------------------  ����ƶ�����:

#define FN_MOVE_UP                  (FNST_MOVE_CARET | 1)   // �������һ��
#define FN_MOVE_DOWN                (FNST_MOVE_CARET | 2)   // �������һ��
#define FN_MOVE_TOP                 (FNST_MOVE_CARET | 3)   // ����Ƶ�����
#define FN_MOVE_BOTTOM              (FNST_MOVE_CARET | 4)   // ����Ƶ��ײ�
#define FN_MOVE_FIRST_COL           (FNST_MOVE_CARET | 5)   // ����Ƶ��������
#define FN_MOVE_LAST_COL            (FNST_MOVE_CARET | 6)   // ����Ƶ����β��
#define FN_MOVE_PREV_COL            (FNST_MOVE_CARET | 7)   // ����Ƶ����ǰһ��
#define FN_MOVE_NEXT_COL            (FNST_MOVE_CARET | 8)   // ����Ƶ�����һ��
#define FN_MOVE_SCROLL_UP           (FNST_MOVE_CARET | 9)   // �������Ϲ���һ��
#define FN_MOVE_SCROLL_DOWN         (FNST_MOVE_CARET | 10)  // �������¹���һ��
#define FN_MOVE_PAGEUP              (FNST_MOVE_CARET | 11)  // �������Ϸ�һҳ
#define FN_MOVE_PAGEDOWN            (FNST_MOVE_CARET | 12)  // �������·�һҳ
#define FN_MOVE_PAGE_HOME           (FNST_MOVE_CARET | 13)  // ��굽��ǰҳ�ײ�
#define FN_MOVE_PAGE_END            (FNST_MOVE_CARET | 14)  // ��굽��ǰҳ�ײ�
#define FN_MOVE_BLK_SEL_UP          (FNST_MOVE_CARET | 27)  // ͬ��,����������ѡ��.
#define FN_MOVE_BLK_SEL_DOWN        (FNST_MOVE_CARET | 28)
#define FN_MOVE_BLK_SEL_TOP         (FNST_MOVE_CARET | 29)
#define FN_MOVE_BLK_SEL_BOTTOM      (FNST_MOVE_CARET | 30)
#define FN_MOVE_BLK_SEL_PAGEUP      (FNST_MOVE_CARET | 31)
#define FN_MOVE_BLK_SEL_PAGEDOWN    (FNST_MOVE_CARET | 32)
#define FN_MOVE_BLK_SEL_PAGE_HOME   (FNST_MOVE_CARET | 33)
#define FN_MOVE_BLK_SEL_PAGE_END    (FNST_MOVE_CARET | 34)
#define FN_MOVE_BLK_SEL_ALL         (FNST_MOVE_CARET | 35)  // ȫ��ѡ��
#define FN_MOVE_TO_PARENT_CMD       (FNST_MOVE_CARET | 36)  // �ƶ���������
#define FN_MOVE_UP_FAR_ITEM         (FNST_MOVE_CARET | 38)  // �����׵�ǰһ��Զ�����
#define FN_MOVE_DOWN_FAR_ITEM       (FNST_MOVE_CARET | 39)  // �����׵ĺ�һ��Զ�����
#define FN_MOVE_OPEN_ARG            (FNST_MOVE_CARET | 40)  // ����������
#define FN_MOVE_CLOSE_ARG           (FNST_MOVE_CARET | 41)  // �ر���������
#define FN_MOVE_OPEN_SPEC_ROW_ARG   (FNST_MOVE_CARET | 42)  // ��ָ���е���������. ���ܲ���1: ��ָ��������λ��
#define FN_MOVE_CLOSE_SPEC_ROW_ARG  (FNST_MOVE_CARET | 43)  // �ر�ָ���е���������. ���ܲ���1: ��ָ��������λ��
#define FN_MOVE_OPEN_ALL_ARG        (FNST_MOVE_CARET | 44)  // �����в�����
#define FN_MOVE_PREV_UNIT           (FNST_MOVE_CARET | 45)  // ��ǰһ��Ԫ
#define FN_MOVE_NEXT_UNIT           (FNST_MOVE_CARET | 46)  // ����һ��Ԫ
#define FN_MOVE_SPEC_SUB            (FNST_MOVE_CARET | 47)  // ������ǰ����������õ��ӳ����DLL���
#define FN_MOVE_OPEN_SPEC_SUB       (FNST_MOVE_CARET | 48)  // �򿪵�ǰ��������ӳ���
#define FN_MOVE_CLOSE_SPEC_SUB      (FNST_MOVE_CARET | 49)  // �رյ�ǰ��������ӳ���
#define FN_MOVE_OPEN_SPEC_SUB_GRP   (FNST_MOVE_CARET | 50)  // �򿪵�ǰ��ѡ���������漰���������ӳ���
#define FN_MOVE_CLOSE_SPEC_SUB_GRP  (FNST_MOVE_CARET | 51)  // �رյ�ǰ��ѡ���������漰���������ӳ���
#define FN_MOVE_EDIT_CARET_PREV     (FNST_MOVE_CARET | 54)  // �������һ���ַ�
#define FN_MOVE_EDIT_CARET_NEXT     (FNST_MOVE_CARET | 55)  // �������һ���ַ�
#define FN_MOVE_EDIT_CARET_TO_BEGIN (FNST_MOVE_CARET | 56)  // ��굽����
#define FN_MOVE_EDIT_CARET_TO_END   (FNST_MOVE_CARET | 57)  // ��굽��β
#define FN_SKIP_LEFT_WORD           (FNST_MOVE_CARET | 58)  // ����һ������
#define FN_SKIP_RIGHT_WORD          (FNST_MOVE_CARET | 59)  // ����һ������
#define FN_MOVE_BLK_SEL_LEFT        (FNST_MOVE_CARET | 60)  // ͬ��,����������ѡ��.
#define FN_MOVE_BLK_SEL_RIGHT       (FNST_MOVE_CARET | 61)
#define FN_MOVE_BLK_SEL_HOME        (FNST_MOVE_CARET | 62)
#define FN_MOVE_BLK_SEL_END         (FNST_MOVE_CARET | 63)
#define FN_MOVE_BLK_SEL_LEFT_WORD   (FNST_MOVE_CARET | 64)
#define FN_MOVE_BLK_SEL_RIGHT_WORD  (FNST_MOVE_CARET | 65)
#define FN_MOVE_CARET               (FNST_MOVE_CARET | 66)  // ������ƶ���ָ��λ��. ���ܲ���1: ������λ��; ���ܲ���2: ������λ��.
#define FN_MOVE_BACK_SUB            (FNST_MOVE_CARET | 67)  // ������ǰ����FN_MOVE_SPEC_SUB��תǰ�������ӳ���

//------------------------------------  ���ڹ�������:

#define FN_SCROLL_LEFT              (FNST_SCROLL_WND | 1)
#define FN_SCROLL_RIGHT             (FNST_SCROLL_WND | 2)
#define FN_SCROLL_UP                (FNST_SCROLL_WND | 3)
#define FN_SCROLL_DOWN              (FNST_SCROLL_WND | 4)
#define FN_SCROLL_PAGELEFT          (FNST_SCROLL_WND | 5)
#define FN_SCROLL_PAGERIGHT         (FNST_SCROLL_WND | 6)
#define FN_SCROLL_PAGEUP            (FNST_SCROLL_WND | 7)
#define FN_SCROLL_PAGEDOWN          (FNST_SCROLL_WND | 8)
#define FN_SCROLL_SPEC_HORZ_POS     (FNST_SCROLL_WND | 9)
#define FN_SCROLL_SPEC_VERT_POS     (FNST_SCROLL_WND | 10)

//------------------------------------  ���������:

#define FN_BLK_ADD_DEF              (FNST_BLOCK_OPER | 1)  // ������ָ����ѡ������. ���ܲ���1: ����������λ��; ���ܲ���2: �ײ�������λ��.
#define FN_BLK_REMOVE_DEF           (FNST_BLOCK_OPER | 2)  // ɾ����ָ����ѡ������. ���ܲ���1: ����������λ��; ���ܲ���2: �ײ�������λ��.
#define FN_BLK_CLEAR_ALL_DEF        (FNST_BLOCK_OPER | 3)  // ɾ�����п�ѡ������

//------------------------------------  �����༭����(�����޸�):

#define FN_EDIT_COPY                (FNST_OTHER_MODIFY | 1)  // ���Ƶ�������

//------------------------------------  �༭����:

#define FN_INSERT_NEW               (FNST_MODIFY | 1)   // ����һ���µ�ǰ��Ԫ
#define FN_INSERT_NEW_AT_NEXT       (FNST_MODIFY | 2)   // �ں󷽲���һ���µ�ǰ��Ԫ
#define FN_REMOVE                   (FNST_MODIFY | 3)   // ɾ����굱ǰ�����ַ����ߵ�ǰ��ѡ���
#define FN_EDIT_CUT                 (FNST_MODIFY | 4)   // ���е�������
#define FN_EDIT_PASTE               (FNST_MODIFY | 5)   // ������������ճ������ǰ�������λ��
#define FN_INSERT_NEW_SUB           (FNST_MODIFY | 9)   // ����һ�����ӳ���
#define FN_INSERT_NEW_DATA_TYPE     (FNST_MODIFY | 10)  // ����һ�����û��Զ�����������
#define FN_INSERT_NEW_GLOBAL_VAR    (FNST_MODIFY | 11)  // ����һ����ȫ�ֱ���
#define FN_INSERT_NEW_DLL_CMD       (FNST_MODIFY | 12)  // ����һ����DLL����
#define FN_INSERT_NEW_MOD           (FNST_MODIFY | 13)  // ����һ���³���
#define FN_INSERT_NEW_ARG           (FNST_MODIFY | 14)  // ����һ�����ӳ������
#define FN_INSERT_NEW_LOCAL_VAR     (FNST_MODIFY | 15)  // ����һ���¾ֲ�����
#define FN_INSERT_NEW_CONST_RES     (FNST_MODIFY | 16)  // ����һ���³���
#define FN_INSERT_NEW_PIC_RES       (FNST_MODIFY | 17)  // ����һ����ͼƬ��Դ
#define FN_INSERT_NEW_SOUND_RES     (FNST_MODIFY | 18)  // ����һ����������Դ
#define FN_UNDO                     (FNST_MODIFY | 50)  // ����
#define FN_REDO                     (FNST_MODIFY | 51)  // ����
#define FN_FORCE_PROCESS            (FNST_MODIFY | 54)  // ǿ��Ԥ���뵱ǰ����������
#define FN_INSERT_NEW_WIN_FORM      (FNST_MODIFY | 55)  // ����һ���´���
#define FN_REMOVE_SPEC_UNIT         (FNST_MODIFY | 62)  // ɾ�������ϵ�ǰ���б�ѡ������
#define FN_MOVE_LEFT_ONE            (FNST_MODIFY | 63)  // �������ϵ�ǰ���б�ѡ����������һ������. ��ͬ.
#define FN_MOVE_RIGHT_ONE           (FNST_MODIFY | 64)
#define FN_MOVE_UP_ONE              (FNST_MODIFY | 65)
#define FN_MOVE_DOWN_ONE            (FNST_MODIFY | 66)
#define FN_MOVE_LEFT_ONE_GRID       (FNST_MODIFY | 67)
#define FN_MOVE_RIGHT_ONE_GRID      (FNST_MODIFY | 68)
#define FN_MOVE_UP_ONE_GRID         (FNST_MODIFY | 69)
#define FN_MOVE_DOWN_ONE_GRID       (FNST_MODIFY | 70)
#define FN_RESIZE_LEFT_ONE          (FNST_MODIFY | 71)  // �������ϵ�ǰ���б�ѡ������������չһ������. ��ͬ.
#define FN_RESIZE_RIGHT_ONE         (FNST_MODIFY | 72)
#define FN_RESIZE_UP_ONE            (FNST_MODIFY | 73)
#define FN_RESIZE_DOWN_ONE          (FNST_MODIFY | 74)
#define FN_RESIZE_LEFT_ONE_GRID     (FNST_MODIFY | 75)
#define FN_RESIZE_RIGHT_ONE_GRID    (FNST_MODIFY | 76)
#define FN_RESIZE_UP_ONE_GRID       (FNST_MODIFY | 77)
#define FN_RESIZE_DOWN_ONE_GRID     (FNST_MODIFY | 78)
#define FN_HORZ_CENTER              (FNST_MODIFY | 79)  // �������ϵ�ǰ���б�ѡ������ˮƽ����. ��ͬ
#define FN_VERT_CENTER              (FNST_MODIFY | 80)
#define FN_UNIT_GO_TOP              (FNST_MODIFY | 82)  // �������ϵ�ǰ���б�ѡ�������ƶ����ص�����Ķ���
#define FN_UNIT_GO_BOTTOM           (FNST_MODIFY | 83)  // �������ϵ�ǰ���б�ѡ�������ƶ����ص�����ĵײ�
#define FN_MENU_MODI                (FNST_MODIFY | 85)  // ������ǰ����Ĳ˵������
#define FN_INPUT_PRG                (FNST_MODIFY | 88)  // ѯ�ʳ����ļ���,���ó����ļ��ϲ�����ǰ����.
#define FN_APP_SETUP                (FNST_MODIFY | 89)  // ���ó������öԻ���
#define FN_ADD_FIELD_CONST          (FNST_MODIFY | 90)  // ��EDB���ݿ���ֶ���ת��Ϊ����
#define FN_LEFT_ALIGN               (FNST_MODIFY | 93)  // �������ϵ�ǰ���б�ѡ�����������. ��ͬ
#define FN_TOP_ALIGN                (FNST_MODIFY | 94)
#define FN_RIGHT_ALIGN              (FNST_MODIFY | 95)
#define FN_BOTTOM_ALIGN             (FNST_MODIFY | 96)
#define FN_HORZ_MIDDLE              (FNST_MODIFY | 97)
#define FN_VERT_MIDDLE              (FNST_MODIFY | 98)
#define FN_HORZ_AVG                 (FNST_MODIFY | 99)
#define FN_VERT_AVG                 (FNST_MODIFY | 100)
#define FN_EQU_WIDTH                (FNST_MODIFY | 101)
#define FN_EQU_HEIGHT               (FNST_MODIFY | 102)
#define FN_EQU_WIDTHHEIGHT          (FNST_MODIFY | 103)
#define FN_INSERT_NEW_CLASS_MOD     (FNST_MODIFY | 106)  // �����µ������
#define FN_INSERT_TEXT              (FNST_MODIFY | 109)  // �����ı�������༭���ڵĵ�ǰ��������ַ�λ��. ���ܲ���1(CHAR*): ָ���������ı���ָ��; ���ܲ���2(BOOL): ���ı��Ƿ�Ϊ�û��Ӽ�������
#define FN_PRE_COMPILE              (FNST_MODIFY | 112)  // Ԥ���뵱ǰ����. ���ܲ���1(BOOL*): ָ��һ��BOOL������ָ��,���������Ƿ�Ԥ����ɹ�.
#define FN_SET_AND_COMPILE_PRG_ITEM_TEXT  (FNST_MODIFY | 113)  // ���õ�ǰ�����������λ�õ���������. ���ܲ���1(CHAR*): ָ���������ı�; ���ܲ���2(BOOL): �Ƿ���������Ԥ����.
#define FN_REPLACE_ALL              (FNST_MODIFY | 114)
#define FN_REMARK_STATMENT          (FNST_MODIFY | 115)  // ע�͵�ǰ���
#define FN_UNREMARK_STATMENT        (FNST_MODIFY | 116)  // ȡ����ǰ����ע��
#define FN_INSERT_FILE_NAME         (FNST_MODIFY | 117)  // ѯ�ʲ������ļ����ı�����ǰ��괦
#define FN_LOCK_UNIT                (FNST_MODIFY | 118)  // ���������ϵ�ǰ��ѡ�����
#define FN_UNLOCK_UNIT              (FNST_MODIFY | 119)  // ���������ϵ�ǰ��ѡ�����
#define FN_REMOVE_SPEC_ECOM         (FNST_MODIFY | 122)  // ɾ��ָ������λ�ô������õ�ģ��. ���ܲ���1: ��ָ��ģ�������λ��
#define FN_INSERT_NEW_LONGTEXT      (FNST_MODIFY | 126)  // �����µĳ��ı���Դ(���ڳ����༭������Ч)
#define FN_HORZ_UNIT_MIDDLE         (FNST_MODIFY | 127)  // �������е����б�ѡ�����ˮƽ����. ��ͬ
#define FN_VERT_UNIT_MIDDLE         (FNST_MODIFY | 128)
#define FN_INPUT_PRG2               (FNST_MODIFY | 133)  // ����ָ�������ļ��ϲ�����ǰ����. ���ܲ���1: ָ�����ϲ������ĳ����ļ�·������
#define FN_REPLACE_ALL2             (FNST_MODIFY | 134)  // �滻��ǰ�༭�����ڵ�����ָ���ı�. ���ܲ���1(REPLACE_ALL2_PARAM*): ָ���滻����
#define FN_ADD_NEW_ECOM2            (FNST_MODIFY | 135)  // ������ָ���ļ�������ģ��. ���ܲ���1(char*): ��ָ����ģ���ļ���; ���ܲ���2(BOOL*): �ڸ�ָ���ڷ����Ƿ����ɹ�

//------------------------------------  �ļ�����:

#define FN_NEW_FILE                 (FNST_FILE | 1)  // �½��ļ�
#define FN_OPEN_FILE                (FNST_FILE | 2)  // ���ļ�
#define FN_CLOSE_FILE               (FNST_FILE | 3)  // �ر��ļ�
#define FN_SAVE_FILE                (FNST_FILE | 4)  // �����ļ�
#define FN_SAVE_AS_FILE             (FNST_FILE | 5)  // �ļ����Ϊ
#define _FN_AUTO_BAK_FILE           (FNST_FILE | 7)  // �Զ�����
#define FN_OPEN_FILE2               (FNST_FILE | 8)  // ����ָ�������ļ�. ���ܲ���1(char*): �����򿪵��ļ���

//------------------------------------  ����:

#define FN_ABOUT                    (FNST_OTHER | 1)   // ����
#define FN_SWITCH_WORK_BAR          (FNST_OTHER | 2)   // ���ع���������
#define FN_SWITCH_OUTPUT_BAR        (FNST_OTHER | 3)   // �������������
#define FN_SWITCH_CMB_BAR           (FNST_OTHER | 4)   // ������Ϲ�����
#define FN_SWITCH_UNIT_BAR          (FNST_OTHER | 5)   // ���ش������������
#define FN_VIEW_DATA_TYPE_TAB       (FNST_OTHER | 8)   // ���û��Զ����������ͱ༭����
#define FN_VIEW_GLOBAL_VAR_TAB      (FNST_OTHER | 9)   // ��ȫ�ֱ����༭����
#define FN_VIEW_DLLCMD_TAB          (FNST_OTHER | 10)  // ��DLL����༭����
#define FN_VIEW_CONST_TAB           (FNST_OTHER | 11)  // �򿪳����༭����
#define FN_VIEW_PIC_TAB             (FNST_OTHER | 12)  // ��ͼƬ��Դ�༭����
#define FN_VIEW_SOUND_TAB           (FNST_OTHER | 13)  // ��������Դ�༭����
#define FN_TEST_WIN                 (FNST_OTHER | 14)  // ����ƴ���Ԥ��
#define FN_SET_READONLY             (FNST_OTHER | 15)  // ��ת��ǰ�����ֻ��״̬
#define FN_SYS_SETUP                (FNST_OTHER | 16)  // ��ϵͳ���öԻ���
#define FN_FIND_BEGIN               (FNST_OTHER | 17)  // ��Ѱ�ҶԻ���
#define FN_FIND_NEXT                (FNST_OTHER | 18)  // Ѱ����һ��
#define FN_FIND_PREV                (FNST_OTHER | 20)  // Ѱ����һ��
#define FN_COPY_HELP_TO_CLIP        (FNST_OTHER | 21)  // ��֧�ֿ⹤�����е�ǰ��ѡ������İ����ı�������������
#define FN_WRITE_HELP_TO_FILE       (FNST_OTHER | 22)  // ��֧�ֿ⹤�����е�ǰ��ѡ������İ����ı�д���ļ�
#define FN_HELP                     (FNST_OTHER | 23)  // �򿪰���
#define FN_DBSTRUCT_MANGER          (FNST_OTHER | 25)  // �����ݿ�ṹ������
#define FN_DBREC_MANGER             (FNST_OTHER | 26)  // �����ݿ��¼������
#define FN_SHOW_PROPERTY            (FNST_OTHER | 27)  // ��ʾ���Թ�����
#define FN_DB_CNV                   (FNST_OTHER | 28)  // �����ݿ�ת������
#define FN_RPT_EDITOR               (FNST_OTHER | 29)  // �򿪱���༭������
#define FN_LIB_SETUP                (FNST_OTHER | 31)  // ��֧�ֿ����öԻ���
#define FN_LIB_MANGER               (FNST_OTHER | 32)  // ��֧�ֿ����������
#define FN_OCX_PACKAGER             (FNST_OTHER | 34)  // ��OCX��װ����
#define FN_REFRUSH_LIB              (FNST_OTHER | 35)  // ������������֧�ֿ�
#define FN_DB_LANG_CONV             (FNST_OTHER | 39)  // �����ݿ�����ת������
#define FN_DAY_HELP                 (FNST_OTHER | 40)  // ��ÿ�հ�������
#define FN_ESN                      (FNST_OTHER | 41)  // ��������֪ʶ��
#define FN_WIZARD_MANG              (FNST_OTHER | 42)  // ѯ�ʲ�ִ����ָ���ļ�����
#define FN_SEARCH_REPLACE           (FNST_OTHER | 43)  // ��Ѱ���滻�Ի���
#define FN_FIND_ALL                 (FNST_OTHER | 44)  // ��Ѱ�����жԻ���
#define FN_USER_RPT                 (FNST_OTHER | 45)
#define FN_TUTORIAL                 (FNST_OTHER | 47)  // �������Զ�ý��̳�
#define FN_SORT_LIB_TREE            (FNST_OTHER | 48)  // ����֧�ֿ⹤���е�����״̬
#define FN_GOTO_SPEC_UNIT_DATA_TYPE (FNST_OTHER | 49)  // ��֧�ֿ����������ת����ǰ�������������ѡ���������Ӧ������������Ŀ��
#define FN_RELINK                   (FNST_OTHER | 50)  // ���½������ƹ�������
#define FN_GOTO_LAST_MODI_PLACE     (FNST_OTHER | 51)  // ��ת�����һ�ν������޸Ĳ������ĵ�λ��
#define FN_SET_BOOKMARK             (FNST_OTHER | 52)  // ���ص�ǰ��������е���ǩ��־
#define FN_GOTO_BOOKMARK            (FNST_OTHER | 53)  // ����ǩ��ת�Ի���
#define FN_PREV_BOOKMARK            (FNST_OTHER | 54)  // ����һ����ǩ
#define FN_NEXT_BOOKMARK            (FNST_OTHER | 55)  // ����һ����ǩ
#define FN_EVA_DESIGNER             (FNST_OTHER | 56)
#define FN_EXTEND_ALL_SUB           (FNST_OTHER | 57)  // �����б����������ص��ӳ���
#define FN_VREPORT                  (FNST_OTHER | 58)

//------------------------------------  ����:

#define FN_STEP_INTO                (FNST_DEBUG | 1)   // �������ٽ���
#define FN_STEP                     (FNST_DEBUG | 2)   // ��������
#define FN_STEP_OUT                 (FNST_DEBUG | 3)   // ��������
#define FN_RUN_TO_CURSOR            (FNST_DEBUG | 4)   // ִ�е���괦
#define FN_VIEW_VAR                 (FNST_DEBUG | 5)   // ��ʾ�����޸ĶԻ���
#define FN_SET_BREAK_POINTER        (FNST_DEBUG | 6)   // ���öϵ�
#define FN_CLEAR_ALL_BREAK_POINTER  (FNST_DEBUG | 7)   // ������жϵ�
#define FN_SHOW_NEXT_STATMENT       (FNST_DEBUG | 8)   // ������ǰ������ִ�е����
#define FN_ADV_BREAKPOINT           (FNST_DEBUG | 10)  // ���������ϵ�

//------------------------------------  ����:

#define FN_COMPILE                             (FNST_RUN | 1)   // ����
#define FN_COMPILE_AND_RUN                     (FNST_RUN | 2)   // ����ִ��
#define FN_END_RUN                             (FNST_RUN | 3)   // ����ִ��
#define FN_PUBLISH                             (FNST_RUN | 5)   // ���뷢��
#define FN_COMPILE_STANDARD                    (FNST_RUN | 6)   // ��������
#define FN_COMPILE_STATIC                      (FNST_RUN | 7)   // ��̬����
#define FN_COMPILE_EPACKAGE                    (FNST_RUN | 8)   // �����װ�
#define FN_COMPILE_WINDOWS_EXE_AND_RUN         (FNST_RUN | 9)   // ����ΪWindows����ִ��
#define FN_COMPILE_WINDOWS_CONOLE_EXE_AND_RUN  (FNST_RUN | 10)  // ����ΪWindows����̨����ִ��
#define FN_COMPILE_WINDOWS_DLL_AND_RUN         (FNST_RUN | 11)  // ����ΪWindows��̬���ӿⲢִ��
#define FN_COMPILE_WINDOWS_ECOM_AND_RUN        (FNST_RUN | 12)  // ����ΪWindows��ģ�鲢ִ��
#define FN_COMPILE_WINDOWS_EXE                 (FNST_RUN | 13)  // ����ΪWindows����
#define FN_COMPILE_WINDOWS_CONOLE_EXE          (FNST_RUN | 14)  // ����ΪWindows����̨����
#define FN_COMPILE_WINDOWS_DLL                 (FNST_RUN | 15)  // ����ΪWindows��̬���ӿ�
#define FN_COMPILE_WINDOWS_ECOM                (FNST_RUN | 16)  // ����ΪWindows��ģ��
#define FN_STATIC_COMPILE_WINDOWS_EXE          (FNST_RUN | 17)  // ��̬����ΪWindows����
#define FN_STATIC_COMPILE_WINDOWS_CONOLE_EXE   (FNST_RUN | 18)  // ��̬����ΪWindows����̨����
#define FN_STATIC_COMPILE_WINDOWS_DLL          (FNST_RUN | 19)  // ��̬����ΪWindows��̬���ӿ�

//------------------------------------  ����:

typedef ADD_TAB_INF* PADD_TAB_INF;
#define FN_ADD_TAB  (FNST_ADDIN | 1)  // �����������������һ��ָ���Ĺ�����. ���ܲ���1(ADD_TAB_INF*): ��������Ϣ

/* �� *(int*)���ܲ���1 �з��ص�ǰ��༭���ڵ�����,Ϊ����ֵ֮һ:
    0: ��
    1: ����
    2: �û��Զ�����������
    3: ȫ�ֱ���
    4: DLL����
    5: �������
    6: ������Դ
    7: ͼƬ��Դ
    8: ������Դ
���ܲ���1(int*): �ṩ��д�������ݵ�����������ַ  */
#define FN_GET_ACTIVE_WND_TYPE  (FNST_ADDIN | 2)

// ������ģ��
//   ���ܲ���1(char*): ���������ģ���ļ���
//   ���ܲ���2(BOOL*): �����з����Ƿ���ɹ�
#define FN_INPUT_ECOM  (FNST_ADDIN | 3)

// ���ָ���Ĺ���Ŀǰ�Ƿ����
//   ���ܲ���1: �����Ĺ��ܺ�
//   ���ܲ���2(BOOL*): �����з�������鹦���Ƿ����
#define FN_IS_FUNC_ENABLED  (FNST_ADDIN | 4)

// ��鵱ǰϵͳ���������Ƿ����׳�������
//   ���ܲ���1(int*): �����������з��ش���0�����ݳ���,���򷵻�0.
#define FN_CLIP_GET_EPRG_DATA_SIZE  (FNST_ADDIN | 5)

// �ӵ�ǰϵͳ�������ж����׳�������
//   ���ܲ���1(BYTE*): ָ�����ݽ��ջ�������ָ��,��ߴ�������ʹ��FN_CLIP_GET_EPRG_DATA_SIZE����õĳߴ�.
//   ���ܲ���2(BOOL*): �����з����Ƿ�����ɹ�
#define FN_CLIP_GET_EPRG_DATA  (FNST_ADDIN | 6)

// ���׳������ݴ�ŵ���ǰϵͳ��������
//   ���ܲ���1(BYTE*): ָ���׳������ݵ�ָ��.
//   ���ܲ���2: ���ݳߴ�.
#define FN_CLIP_SET_EPRG_DATA  (FNST_ADDIN | 7)

// ���ص�ǰ�������������λ��
//   ���ܲ���1(int*): ����������������λ��
#define FN_GET_CARET_ROW_INDEX  (FNST_ADDIN | 8)

// ���ص�ǰ�������������λ��
//   ���ܲ���1(int*): ����������������λ��
#define FN_GET_CARET_COL_INDEX  (FNST_ADDIN | 9)

// ������ָ��λ�ô������ͼ������ı�
// ���ܲ���1(GET_PRG_TEXT_PARAM*): �ṩ��ز�����Ϣ
#define FN_GET_PRG_TEXT  (FNST_ADDIN | 10)

// ������ָ��λ�ô������ͼ�������Ϣ�ı�
// ���ܲ���1(GET_PRG_TEXT_PARAM*): �ṩ��ز�����Ϣ
#define FN_GET_PRG_HELP  (FNST_ADDIN | 11)

// ���ص�ǰ���������������ģ����Ŀ
//   ���ܲ���1(int*): �ṩ��д�������ݵ�����������ַ
#define FN_GET_NUM_ECOM   (FNST_ADDIN | 12)

// ������ָ������λ�ô���ģ���ȫ·���ļ���
//   ���ܲ���1(int): �ṩ����ѯ��ģ�������λ��,������ڵ���0С��FN_GET_NUM_ECOM�ķ���ֵ.
//   ���ܲ���2(char*): �ṩ������д�����ı��Ļ�������ַ,�������ߴ������ڵ���256���ַ�.
#define FN_GET_ECOM_FILE_NAME  (FNST_ADDIN | 13)

// ���ص�ǰϵͳ���Ѿ�ѡ���֧�ֿ���Ŀ
//   ���ܲ���1(int*): �ṩ��д�������ݵ�����������ַ
#define FN_GET_NUM_LIB    (FNST_ADDIN | 14)

// ������ָ������λ�ô�֧�ֿ����Ϣ�ı�
//   ���ܲ���1(int): �ṩ����ѯ֧�ֿ������λ��,������ڵ���0С��FN_GET_NUM_LIB�ķ���ֵ.
//   ���ܲ���2(char**): �ṩ��д�����ı�ָ��ı�����ַ
#define FN_GET_LIB_INFO_TEXT  (FNST_ADDIN | 15)

#endif

