#ifndef __LIB_INF_H
#define __LIB_INF_H

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif


//!////////////////////////////////////////////////////////////////////////
//! �����Ǵ���̬����Ҫ�ĺ�, ��̬�⾡���ܵİѺ������ĳ�Ψһ��,������������ͻ��
//! ���ﶨ���˼����� ���������� __LIB2_DEFFUNNAME(fun_name)  ���ǰ� fun_name �滻����������, ��������Ҳ��Ҫ __LIB2_DEFFUNNAME(fun_name)(...) ���е���
//! ʵ��֧�ֿ������������ʹ�� DEF_EXECUTE_CMD(fun_name)
// TODO ����lib2.hǰ���붨�� __E_FNENAME �����, �������ǿ���ǰ׺, ���з�������ǰ����� ����_������_����

//#define __E_FNENAME ietb        // ����֧�ֿ�������, ��̬����Ҫ����

#define ____E_FNENAME(quote) #quote                    // ������
#define ______E_FNENAME(quote) ____E_FNENAME(quote)    // ������
#define __E_FNENAME_S ______E_FNENAME(__E_FNENAME)    // ��̬������ʱ��, ��Ҫƴ�ӳɷ������ַ���

#ifndef __E_FNENAME
#error "�����ȶ��� __E_FNENAME �����, ����������, ���� #define __E_FNENAME jywke"
#endif


#define __LIB2_FNE_NAME_LEFT(leftName) leftName
#define __LIB2_FNE_NAME_RIGHT(rightName) rightName

#define __LIB2_DEFFUNNAME__(fnName) __LIB2_FNE_NAME_LEFT(__E_FNENAME)##_##fnName##_
#define __LIB2_DEFFUNNAME(fnName)   __LIB2_DEFFUNNAME__(fnName)__LIB2_FNE_NAME_LEFT(__E_FNENAME)

// ��������ʹ�ú�,��������޶ȵĽ����̬������������ͻ����
#define DEF_EXECUTE_CMD(fnName) EXTERN_C void __LIB2_DEFFUNNAME(fnName) (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf)

#if defined(__E_STATIC_LIB) || defined(__COMPILE_FNR)
#define DEF_CMD(name)  __LIB2_DEFFUNNAME(name)  // ���ڲ�ͬ�Ŀ�, ������Ӧ�������޸�
#define DEF_NULL_CMD(name)  NULL
#else if defined(__cplusplus)
#define DEF_CMD(name)  _RecordCmdName (__LIB2_DEFFUNNAME(name), __E_FNENAME_S "_"#name"_" __E_FNENAME_S)    // ���ڲ�ͬ�Ŀ�, ������Ӧ�������޸�
#define DEF_CMD_NULL(name)  _RecordCmdName(NULL, NULL)                // ���������
#endif

//!////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////

// ����ϵͳ���

#define __OS_WIN        0x80000000
#define __OS_LINUX      0x40000000
#define __OS_UNIX       0x20000000

#define OS_ALL    (__OS_WIN | __OS_LINUX | __OS_UNIX)

//!////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <stdio.h>
#include <math.h>

//#include <windef.h>
//#include <tchar.h>
//#include <winnt.h>
//
/*

���ڿ����ϵͳ���֧�ּ���˵����

  1����֧�ֿ���Ҫ˵���������Щ����ϵͳ�汾,��֧�ֿ�����������������͡�
     �������ͷ��������������¼�����������������֧�ֵĲ���ϵͳ��������Щ��Ϣ,
     �ڸ�֧�ֿ������е����в���ϵͳ�汾�б���һ�¡�

  2��Ϊ�˺���ǰ��֧�ֿ������,����m_nRqSysMajorVer.m_nRqSysMinorVer�汾��
     С��3.6�Ķ�Ĭ��Ϊ֧��Windows����ϵͳ,�����ڲ�����������������͡�
     �������ͷ��������������¼��������������ԡ�

  3����������̶����Ժ͹̶��¼���֧�����в���ϵͳ��

  4�����ڴ����߿ⲻ���в���ϵͳ֧�ּ�顣

*/

#ifndef DOUBLE
typedef double DOUBLE;
#endif
#ifndef DATE
typedef double DATE;
#endif
#ifndef SHORT
typedef short SHORT;
#endif
#ifndef DWORD
typedef unsigned long       DWORD;
#endif

//!////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#include <assert.h>
#define CHKV_RET(epr)        \
            assert (epr);    \
            if (!(epr))  return;
#define CHKV_RET_VAL(epr,val)        \
            assert (epr);    \
            if (!(epr))  return val;
#define CHKV_BREAK(epr)        \
            assert (epr);    \
            if (!(epr))  break;
#define CHKV_CONTINUE(epr)        \
            assert (epr);    \
            if (!(epr))  continue;
#define DEFAULT_FAILD  default: assert (FALSE); break
#else
#define CHKV_RET(epr)        \
            if (!(epr))  return;
#define CHKV_RET_VAL(epr,val)        \
            if (!(epr))  return val;
#define CHKV_BREAK(epr)        \
            if (!(epr))  break;
#define CHKV_CONTINUE(epr)        \
            if (!(epr))  continue;
#define DEFAULT_FAILD
#endif

// ����֧�ֱ���fnr
#ifdef __COMPILE_FNR
#define _WT(text)                       _T("")
#define _CMDS_COUNT(CmdsCount)          0
#define _CMDS_PTR(CmdsPtr)              NULL
#define _EVENTS_COUNT(EventsCount)      0
#define _EVENTS_PTR(EventsPtr)          NULL
#define _ELEMENTS_COUNT(ElementsCount)  0
#define _ELEMENTS_PTR(ElementsPtr)      NULL
#define _FORM_BASE_CLASS                CWnd
#else
#define _WT(text)                       _T(text)
#define _CMDS_COUNT(CmdsCount)          CmdsCount
#define _CMDS_PTR(CmdsPtr)              CmdsPtr
#define _EVENTS_COUNT(EventsCount)      EventsCount
#define _EVENTS_PTR(EventsPtr)          ((PEVENT_INFO2)EventsPtr)
#define _ELEMENTS_COUNT(ElementsCount)  ElementsCount
#define _ELEMENTS_PTR(ElementsPtr)      ElementsPtr
#define _FORM_BASE_CLASS                CFrameWnd
#endif

typedef    SHORT    DTBOOL;             // SDT_BOOL���͵�ֵ����
typedef    DTBOOL*  PDTBOOL;
#define    BL_TRUE  -1                  // SDT_BOOL���͵���ֵ
#define    BL_FALSE 0                   // SDT_BOOL���͵ļ�ֵ

typedef DATE * PDATE;

//+////////////////////////////////////////////////////////////////////////

// ��������ϵͳ����Ļ�����������

#define        _SDT_NULL        (DATA_TYPE)0           // ������(�ڲ�ʹ��,����Ϊ��)

/*  �����ڿ������������򷵻�ֵ���������͡�
    1�������ڶ�����������ʱ,_SDT_ALL����ƥ��������������(�������ͱ������Ҫ��)��
    2�����ڶ���Ϊ����_SDT_ALL�������͵Ŀ��������������򸴺��������͵�����(���û�����Զ����������͵����������ڻ�˵����),
        ����_SDT_ALL���͵�����ֻ����Ϊ�������ϵͳ�������ͻ򴰿�������˵��������͡�*/
#define        _SDT_ALL        (DATA_TYPE)MAKELONG (MAKEWORD (0, 0), 0x8000)    // (�ڲ�ʹ��)

    // ��ֵ,ƥ��������������,�����ڿ�����������������ֵ���������͡�
//#define _SDT_NUM        (DATA_TYPE)MAKELONG (MAKEWORD (1, 0), 0x8000)        // (�ڲ�ʹ��),3.0�汾���Ѿ�������
#define SDT_BYTE        (DATA_TYPE)MAKELONG (MAKEWORD (1, 1), 0x8000)        // �ֽ�
#define SDT_SHORT       (DATA_TYPE)MAKELONG (MAKEWORD (1, 2), 0x8000)        // ������
#define SDT_INT         (DATA_TYPE)MAKELONG (MAKEWORD (1, 3), 0x8000)        // ����
#define SDT_INT64       (DATA_TYPE)MAKELONG (MAKEWORD (1, 4), 0x8000)        // ������
#define SDT_FLOAT       (DATA_TYPE)MAKELONG (MAKEWORD (1, 5), 0x8000)        // С��
#define SDT_DOUBLE      (DATA_TYPE)MAKELONG (MAKEWORD (1, 6), 0x8000)        // ˫����С��
#define SDT_BOOL        (DATA_TYPE)MAKELONG (MAKEWORD (2, 0), 0x8000)        // �߼�
#define SDT_DATE_TIME   (DATA_TYPE)MAKELONG (MAKEWORD (3, 0), 0x8000)        // ����ʱ��
#define SDT_TEXT        (DATA_TYPE)MAKELONG (MAKEWORD (4, 0), 0x8000)        // �ı�
#define SDT_BIN         (DATA_TYPE)MAKELONG (MAKEWORD (5, 0), 0x8000)        // �ֽڼ�
#define SDT_SUB_PTR     (DATA_TYPE)MAKELONG (MAKEWORD (6, 0), 0x8000)        // �ӳ���ָ��
//#define _SDT_VAR_REF    (DATA_TYPE)MAKELONG (MAKEWORD (7, 0), 0x8000)        // �ο�,3.0�汾���Ѿ�������

    
    /* 
    �������,�����ڿ��������������������͡������ݳ���Ϊ����INT,��һ����¼����ӳ����ַ,�ڶ�����¼������������ӳ���ı���ջ�ס�
    ע�����������������ʱ,��������������Խ������л�����������,���Ա��������жϴ���
    �������ӣ�
        if (pArgInf->m_dtDataType == SDT_BOOL)
            return pArgInf->m_bool;

        if (pArgInf->m_dtDataType == SDT_STATMENT)
        {
            DWORD dwEBP = pArgInf->m_statment.m_dwSubEBP;
            DWORD dwSubAdr = pArgInf->m_statment.m_dwStatmentSubCodeAdr;
            DWORD dwECX, dwEAX;

            _asm
            {
                mov eax, dwEBP
                call dwSubAdr
                mov dwECX, ecx
                mov dwEAX, eax
            }

            if (dwECX == SDT_BOOL)
                return dwEAX != 0;

            // �ͷ��ı����ֽڼ�������������ڴ档
            if (dwECX == SDT_TEXT || dwECX == SDT_BIN)
                MFree ((void*)dwEAX);
        }

        GReportError ("�������������жϵ���������ֻ�ܽ����߼�������");
    */
#define SDT_STATMENT    (DATA_TYPE)MAKELONG (MAKEWORD (8, 0),    0x8000)


//+////////////////////////////////////////////////////////////////////////

// ��������ϵͳ���͡��û��Զ������͡��ⶨ����������
#define DTM_SYS_DATA_TYPE_MASK          0x80000000
#define DTM_USER_DATA_TYPE_MASK         0x40000000
#define DTM_LIB_DATA_TYPE_MASK          0x00000000

// ����ϸ���û��Զ�����������
#define UDTM_USER_DECLARE_MASK          0x00000000    // �û��Զ��帴����������
#define UDTM_WIN_DECLARE_MASK           0x10000000    // �û��Զ��崰������


//+////////////////////////////////////////////////////////////////////////


// �����������е������־,���ĳ��������ֵ��λ��1,���ʾΪ���������͵����顣
// ����־������������ʱΪ����AS_RECEIVE_VAR_OR_ARRAY��AS_RECEIVE_ALL_TYPE_DATA
// ��־�Ŀ��������˵����Ϊ�Ƿ�Ϊ��������,�������Ͼ�δʹ�á���������ط������Ժ��Ա���־��
#define DT_IS_ARY                       0x20000000

// �����������еĴ�ַ��־,���ĳ��������ֵ��λ��1,���ʾΪ���������͵ı�����ַ��
// ����־������������ʱΪ����AS_RECEIVE_VAR_OR_OTHER��־�Ŀ��������˵����Ϊ�Ƿ�Ϊ
// ������ַ,�������Ͼ�δʹ�á���������ط������Ժ��Ա���־��
// ����־���ϱ�־���ܹ��档
#define DT_IS_VAR                       0x20000000

typedef DWORD DATA_TYPE;
typedef DATA_TYPE* PDATA_TYPE;

//+//////////////////////////////////////////////////////////////

// ����İ汾���ͺ�
#define PT_EDIT_VER                 1    // Ϊ�����༭�İ汾
#define PT_DEBUG_RUN_VER            2    // ΪDEBUG�������а汾
#define PT_RELEASE_RUN_VER          3    // ΪRELEASE�������а汾

// �����ѧϰ�Ѷȼ���
#define LVL_SIMPLE                  1    // ��������
#define LVL_SECONDARY               2    // �м�����
#define LVL_HIGH                    3    // �߼�����


//+////////////////////////////////////////////////////////////////////////

// ���������ṩ��ʽ�����֣�
//        1���������ṩ��ʽ(�������ڿ���û��Զ�������);
//        2����һ�����ṩ��ʽ(�ṩ�������Զ����������ͱ�������������Ԫ�ء� �Զ�������ĳ�Ա������);
//        3���������������ṩ��ʽ(�ṩ�����������������Ԫ��);
//        4�����������ṩ��ʽ(������ķ���ֵ���ṩ��������)��
typedef struct
{
    LPCSTR          m_szName;               // ��������
    LPCSTR          m_szExplain;            // ������ϸ����
    SHORT           m_shtBitmapIndex;       // ָ��ͼ������,��1��ʼ,0��ʾ��.
    SHORT           m_shtBitmapCount;       // ͼ����Ŀ(��������).

    DATA_TYPE       m_dtType;

    // ϵͳ�������Ͳ�����Ĭ��ָ��ֵ(�ڱ༭����ʱ�ѱ�����,����ʱ�����ٴ���)��
    //    1�������ͣ�ֱ��Ϊ����ֵ(��ΪС��,ֻ��ָ������������, ��Ϊ������,ֻ��ָ��������INT��ֵ�Ĳ���);
    //    2���߼��ͣ�1������,0���ڼ�;
    //    3���ı��ͣ���������ʱΪLPSTRָ��,ָ��Ĭ���ı���;
    //    4�������������Ͳ���(�����Զ�������)һ����Ĭ��ָ��ֵ��
    INT            m_nDefault;

#define AS_HAS_DEFAULT_VALUE            (1 << 0)    // ��������Ĭ��ֵ,Ĭ��ֵ��m_nDefault��˵�����������ڱ༭����ʱ�ѱ�����,����ʱ�����ٴ���
#define AS_DEFAULT_VALUE_IS_EMPTY       (1 << 1)    // ��������Ĭ��ֵ,Ĭ��ֵΪ��,��AS_HAS_DEFAULT_VALUE��־����,����ʱ�����ݹ����Ĳ����������Ϳ���Ϊ_SDT_NULL��
#define AS_RECEIVE_VAR                  (1 << 2)    // Ϊ�������ṩ����ʱֻ���ṩ��һ����,�������ṩ�����������顢�������������ֵ������ʱ�����ݹ����Ĳ������ݿ϶������ݲ�Ϊ����ı�����ַ��
#define AS_RECEIVE_VAR_ARRAY            (1 << 3)    // Ϊ�������ṩ����ʱֻ���ṩ������������,�������ṩ��һ�������������������ֵ��
#define AS_RECEIVE_VAR_OR_ARRAY         (1 << 4)    // Ϊ�������ṩ����ʱֻ���ṩ��һ������������������,�������ṩ�������������ֵ��������д˱�־,�򴫵ݸ�������������������ͽ���ͨ��DT_IS_ARY����־���Ƿ�Ϊ���顣
#define AS_RECEIVE_ARRAY_DATA           (1 << 5)    // Ϊ�������ṩ����ʱֻ���ṩ��������,�粻ָ������־,Ĭ��Ϊֻ���ṩ���������ݡ���ָ���˱���־,����ʱ�����ݹ����Ĳ������ݿ϶�Ϊ���顣
#define AS_RECEIVE_ALL_TYPE_DATA        (1 << 6)    // Ϊ�������ṩ����ʱ����ͬʱ�ṩ���������������,���ϱ�־���⡣������д˱�־,�򴫵ݸ�������������������ͽ���ͨ��DT_IS_ARY����־���Ƿ�Ϊ���顣
#define AS_RECEIVE_VAR_OR_OTHER         (1 << 9)    // Ϊ�������ṩ����ʱ�����ṩ��һ�������������������ֵ,�����ṩ���顣������д˱�־,�򴫵ݸ�������������������ͽ���ͨ��DT_IS_VAR����־���Ƿ�Ϊ������ַ��
    DWORD        m_dwState;                // ����MASK

}ARG_INFO, *PARG_INFO;

//////////////////////////////////////////////////////////////////////////

#ifndef __GCC_
struct CMD_INFO
#else
typedef struct
#endif
{
    LPCSTR          m_szName;           // ������������
    LPCSTR          m_szEgName;         // ����Ӣ������,����Ϊ�ջ�NULL��
    LPCSTR          m_szExplain;        // ������ϸ����
    SHORT           m_shtCategory;      // ȫ��������������,��1��ʼ�������Ա����Ĵ�ֵΪ-1��

#define CT_IS_HIDED                 (1 << 2)    // �������Ƿ�Ϊ��������(������Ҫ���û�ֱ�Ӳ��������,��ѭ�����������������Ϊ�˱��ּ�������Ҫ���ڵ�����)��
#define CT_IS_ERROR                 (1 << 3)    // �������ڱ����в���ʹ��,���д˱�־һ������,��Ҫ�����ڲ�ͬ���԰汾����ͬ����ʹ��, ����A������A���԰汾���п�����Ҫʵ�ֲ�ʹ��,����B���԰汾���п��ܾͲ���Ҫ�����������ʹ���˾��д˱�־������,��ֻ��֧�ָó������ͱ���,������֧�����С�����д˱�־,��������Բ�ʵ����ִ�в��֡�
#define CT_DISABLED_IN_RELEASE      (1 << 4)    // ��������RELEASE�汾�����в���ʹ��(�൱�ڿ�����),��������������޷���ֵ��
#define CT_ALLOW_APPEND_NEW_ARG     (1 << 5)    // �ڱ�����Ĳ������ĩβ�Ƿ��������µĲ���,�²�����ͬ�ڲ������е����һ������, ����������Ĳ�������������һ����
#define CT_RETRUN_ARY_TYPE_DATA     (1 << 6)    // ����˵��m_dtRetValType,˵���Ƿ�Ϊ�����������ݡ�

    /* ˵��������Ϊĳ�������͵ĸ��ƺ���(ִ�н���һͬ���������������ݸ��Ƶ�������ʱ����Ҫ�Ķ������,�ڱ�����������Ͷ���ĸ�ֵ���ʱ���������ͷŸö����ԭ������,
    Ȼ�����ɵ��ô�����Ĵ���,�����������������κγ��渳ֵ�����ƴ���)��
        1����������������һ��ͬ�������Ͳ������Ҳ������κ����ݡ�
        2��ִ�б�����ʱ�������������Ϊδ��ʼ��״̬,�����ڱ��븺���ʼ����ȫ����Ա���ݡ�
        3�����ṩ�����Ĵ������������Ͳ������ݿ���Ϊȫ��״̬(�ɱ������Զ����ɵĶ����ʼ��������), ����ʱ��Ҫ�Դ��������������
    */
#define CT_IS_OBJ_COPY_CMD          (1 << 7)    //! ע��ÿ�������������ֻ����һ���������д˱�ǡ�

    /* ˵��������Ϊĳ�������͵���������(ִ�е�������������������ʱ����Ҫ��ȫ������,
    �����󳬳�����������ʱ�������������ɵ��ô�����Ĵ���,�����������κγ������ٴ���)��
        1�����������û���κβ������Ҳ������κ����ݡ�
        2�������ִ��ʱ������������ݿ���Ϊȫ��״̬(�ɱ������Զ����ɵĶ����ʼ��������), �ͷ�ʱ��Ҫ�Դ��������������
    */
#define CT_IS_OBJ_FREE_CMD          (1 << 8)   //! ע��ÿ�������������ֻ����һ���������д˱�ǡ�

    /*
    ˵��������Ϊĳ�������͵Ĺ��캯��(ִ�е��������������ݳ�ʼ��ʱ����Ҫ��ȫ������,
        1�����������û���κβ������Ҳ������κ����ݡ�
        2�������ִ��ʱ�������������Ϊȫ��״̬��
        3��ָ�����ͳ�Ա(�����������ͳ�Ա�������Ա),���밴�ն�Ӧ��ʽ����������һ����ʼ����
    */
#define CT_IS_OBJ_CONSTURCT_CMD     (1 << 9)   //! ע��ÿ�������������ֻ����һ���������д˱�ǡ�
#define _CMD_OS(os)     ((os) >> 16)  // ����ת��os�����Ա���뵽m_wState��
#define _TEST_CMD_OS(m_wState,os)    ((_CMD_OS (os) & m_wState) != 0) // ��������ָ�������Ƿ�֧��ָ������ϵͳ��
    /* ! ǧ��ע�⣺�������ֵ����Ϊ _SDT_ALL , ���Բ��ܷ�������(��CT_RETRUN_ARY_TYPE_DATA
       ��λ)�򸴺��������͵�����(���û�����Զ����������͵����������ڻ�˵����),
       ��Ϊ�޷��Զ�ɾ������������������Ķ���ռ�(���ı��ͻ����ֽڼ��ͳ�Ա��).
       ����ͨ��������ֻ����ͨ���������,�������_SDT_ALL���͵�����ֻ����Ϊ�������
       ϵͳ�������ͻ򴰿�������˵��������͡�
   */
    WORD            m_wState;           // ���, CT_��ͷ����
    DATA_TYPE       m_dtRetValType;     // ����ֵ����,ʹ��ǰע��ת��HIWORDΪ0���ڲ���������ֵ��������ʹ�õ���������ֵ��
    WORD            m_wReserved;        // �����ֶ�
    SHORT           m_shtUserLevel;     // ������û�ѧϰ�Ѷȼ���,��������ֵΪ����ꡣ

#ifndef __GCC_
    BOOL IsInObj()
    {
        return m_shtCategory == -1;
    }
#endif

    SHORT           m_shtBitmapIndex;   // ָ��ͼ������,��1��ʼ,0��ʾ��.
    SHORT           m_shtBitmapCount;   // ͼ����Ŀ(��������).
    INT             m_nArgCount;        // ����Ĳ�����Ŀ
    PARG_INFO       m_pBeginArgInfo;    // ������ʼ��ַ
#ifndef __GCC_
};
#else
} CMD_INFO;
#endif
typedef CMD_INFO* PCMD_INFO;

//////////////////////////////////////////////////////////////////////////

// ��������ʹ�õĽṹ��
typedef struct
{
    DATA_TYPE   m_dtType;       // �������������������, ���λ��ö������������,�򱾳�Ա����ΪSDT_INT�� 
    LPBYTE      m_pArySpec;     // ����ָ����,�����Ϊ����,��ֵΪNULL��ע����Բ���ָ��ĳά������Ϊ0�����顣���λ��ö������������,�򱾳�Ա����ΪNULL��
    LPCSTR      m_szName;       // ��������������ı�������,�����������������ֻ��һ�����������,���ֵӦ��ΪNULL��
    LPCSTR      m_szEgName;     // �����������Ӣ�ı�������,����Ϊ�ջ�NULL��
    LPCSTR      m_szExplain;    // ��ϸ˵��


#define LES_HAS_DEFAULT_VALUE    (1 << 0)    //! ���λ��ö������������,�򱾳�ԱĬ�Ͼ���LES_HAS_DEFAULT_VALUE��ǡ������ݳ�Ա��Ĭ��ֵ,Ĭ��ֵ��m_nDefault��˵����
#define LES_HIDED                (1 << 1)    // �������ݳ�Ա�����ء�
    DWORD m_dwState;    //! ���λ��ö������������,�򱾳�ԱĬ�Ͼ���LES_HAS_DEFAULT_VALUE��ǡ������ݳ�Ա��Ĭ��ֵ,Ĭ��ֵ��m_nDefault��˵����

    // ϵͳ�����������������(������)��Ĭ��ָ��ֵ��
    //        1�������ͣ�ֱ��Ϊ����ֵ(��ΪС��,ֻ��ָ������������,��Ϊ������,ֻ��ָ��������INT��ֵ�Ĳ���);
    //        2���߼��ͣ�1������,0���ڼ�;
    //        3���ı��ͣ���������ʱΪLPSTRָ��,ָ��Ĭ���ı���;
    //        4�������������Ͳ���(�����Զ�������)һ����Ĭ��ָ��ֵ��
    INT m_nDefault;    // !!! ���λ��ö������������,�򱾳�ԱΪ�����ö����ֵ��

} LIB_DATA_TYPE_ELEMENT;
typedef LIB_DATA_TYPE_ELEMENT* PLIB_DATA_TYPE_ELEMENT;

//////////////////////////////////////////////////////////////////////////

// �̶����Ե���Ŀ
#define    FIXED_WIN_UNIT_PROPERTY_COUNT    8

// ÿ���̶����Զ���
#define    FIXED_WIN_UNIT_PROPERTY    \
    {    "���",    "left",        NULL,    UD_INT,     _PROP_OS (OS_ALL),    NULL },    \
    {    "����",    "top",         NULL,    UD_INT,     _PROP_OS (OS_ALL),    NULL },    \
    {    "���",    "width",       NULL,    UD_INT,     _PROP_OS (OS_ALL),    NULL },    \
    {    "�߶�",    "height",      NULL,    UD_INT,     _PROP_OS (OS_ALL),    NULL },    \
    {    "���",    "tag",         NULL,    UD_TEXT,    _PROP_OS (OS_ALL),    NULL },    \
    {    "����",    "visible",     NULL,    UD_BOOL,    _PROP_OS (OS_ALL),    NULL },    \
    {    "��ֹ",    "disable",     NULL,    UD_BOOL,    _PROP_OS (OS_ALL),    NULL },    \
    {    "���ָ��","MousePointer", NULL,    UD_CURSOR,  _PROP_OS (OS_ALL),    NULL }


// �������������,ע�ⲻҪ������������֧�֡�
typedef struct
{
    LPCSTR m_szName;    // ��������,ע��Ϊ���������Ա���ͬʱ���ö���������,�������Ʊ���߶�һ�¡�
    LPCSTR m_szEgName;    // ����Ӣ����
    LPCSTR m_szExplain;    // ���Խ��͡�

// ע�⣺���ݸ�ʽ����PFN_NOTIFY_PROPERTY_CHANGED������֪ͨ��
#define UD_PICK_SPEC_INT        1000    // ����ΪINTֵ,�û�ֻ��ѡ��,���ܱ༭��
#define UD_INT                  1001    // ����ΪINTֵ
#define UD_DOUBLE               1002    // ����ΪDOUBLEֵ
#define UD_BOOL                 1003    // ����ΪBOOLֵ
#define UD_DATE_TIME            1004    // ����ΪDATEֵ
#define UD_TEXT                 1005    // ����Ϊ�ַ���
#define UD_PICK_INT             1006    // ����ΪINTֵ,�û�ֻ��ѡ��,���ܱ༭��
#define UD_PICK_TEXT            1007    // ����Ϊ�ַ���,�û�ֻ��ѡ��,���ܱ༭��
#define UD_EDIT_PICK_TEXT       1008    // ����Ϊ�ַ���,�û����Ա༭��
#define UD_PIC                  1009    // ΪͼƬ�ļ�����
#define UD_ICON                 1010    // Ϊͼ���ļ�����
#define UD_CURSOR               1011    // ��һ��INT��¼���ָ������,����ֵ��LoadCursor��������Ϊ-1,��Ϊ�Զ������ָ��,��ʱ�����Ӧ���ȵ����ָ���ļ����ݡ�
#define UD_MUSIC                1012    // Ϊ�����ļ�����
#define UD_FONT                 1013    // Ϊһ��LOGFONT���ݽṹ,�����ٸġ�
#define UD_COLOR                1014    // ����ΪCOLORREFֵ��
#define UD_COLOR_TRANS          1015    // ����ΪCOLORREFֵ,����͸����ɫ(��CLR_DEFAULT����)��
#define UD_FILE_NAME            1016    // ����Ϊ�ļ����ַ�������ʱm_szzPickStr�е�����Ϊ: �Ի������\0 + �ļ���������\0 + Ĭ�Ϻ�׺\0 + "1"(ȡ�����ļ���)��"0"(ȡ�����ļ���)\0
#define UD_COLOR_BACK           1017    // ����ΪCOLORREFֵ,����ϵͳĬ�ϱ�����ɫ(��CLR_DEFAULT����)��
#define UD_IMAGE_LIST           1023    // ͼƬ��,���ݽṹΪ��DWORD: ��־���ݣ�Ϊ IMAGE_LIST_DATA_MARK, COLORREF: ͸����ɫ(����ΪCLR_DEFAULT), ����ΪͼƬ������.��CImageList::Read��CImageList::Write��д��
#define IMAGE_LIST_DATA_MARK    (MAKELONG ('IM', 'LT'))
#define UD_CUSTOMIZE            1024

#define UD_BEGIN                UD_PICK_SPEC_INT
#define UD_END                  UD_CUSTOMIZE

    SHORT m_shtType;    // ���Ե��������͡�

#define UW_HAS_INDENT           (1 << 0)    // �����Ա�����ʾʱ��������һ��,һ�����������ԡ�
#define UW_GROUP_LINE           (1 << 1)    // �����Ա��б���������ʾ����׷��ߡ�
#define UW_ONLY_READ            (1 << 2)    // ֻ������,���ʱ������,����ʱ����д��
#define UW_CANNOT_INIT          (1 << 3)    // ���ʱ������,������ʱ����������д�����ϱ�־���⡣
#define UW_IS_HIDED             (1 << 4)    // 3.2 ���� ���ص����á�
//!!! ע���λ���� __OS_xxxx ������ָ����������֧�ֵĲ���ϵͳ��
#define _PROP_OS(os)            ((os) >> 16)// ����ת��os�����Ա���뵽m_wState��
#define _TEST_PROP_OS(m_wState,os)    ((_PROP_OS (os) & m_wState) != 0) // ��������ָ�������Ƿ�֧��ָ������ϵͳ��
    WORD m_wState;        // UW_��ͷ����

    // ˳���¼���еı�ѡ�ı�(����UD_FILE_NAME),��һ���մ�������
    // ��m_nTypeΪUP_PICK_INT��UP_PICK_TEXT��UD_EDIT_PICK_TEXT��UD_FILE_NAMEʱ��ΪNULL��
    // ��m_nTypeΪUD_PICK_SPEC_INTʱ,ÿһ�ѡ�ı��ĸ�ʽΪ ��ֵ�ı� + "\0" + ˵���ı� + "\0" ��
    LPCSTR m_szzPickStr;
} UNIT_PROPERTY, * PUNIT_PROPERTY;

//////////////////////////////////////////////////////////////////////////


///////////////////////////////// 3.2 ��ǰ��ʹ�õ��¼�������Ϣ��һ���汾

typedef struct
{
#define EAS_IS_BOOL_ARG (1 << 0)    // Ϊ�߼��Ͳ���,���޴˱�־,Ĭ��Ϊ�����Ͳ���
    LPCSTR m_szName;        // ��������
    LPCSTR m_szExplain;     // ������ϸ����
    DWORD  m_dwState;       // EAS_IS_BOOL_ARG,Ϊ�߼��Ͳ���, ���޴˱�־,Ĭ��Ϊ�����Ͳ���
}EVENT_ARG_INFO, * PEVENT_ARG_INFO;

typedef struct
{
#define EV_IS_HIDED         (1 << 0)// ���¼��Ƿ�Ϊ�����¼�(�����ܱ�һ���û���ʹ�û򱻷�����Ϊ�˱��ּ�������Ҫ���ڵ��¼�)��
    //#define EV_IS_MOUSE_EVENT    (1 << 1)    // 3.2��������
#define EV_IS_KEY_EVENT     (1 << 2)
#define EV_RETURN_INT       (1 << 3)    // ����һ������
#define EV_RETURN_BOOL      (1 << 4)    // ����һ���߼�ֵ,���ϱ�־���⡣
#define _EVENT_OS(os)       ((os) >> 1)    //! ע���λ���� __OS_xxxx ������ָ�����¼���֧�ֵĲ���ϵͳ������ת��os�����Ա���뵽m_dwState��
#define _TEST_EVENT_OS(m_dwState,os) ((_EVENT_OS (os) & m_dwState) != 0) // ��������ָ���¼��Ƿ�֧��ָ������ϵͳ��
    LPCSTR m_szName;        // �¼�����
    LPCSTR m_szExplain;     // �¼���ϸ����
    DWORD  m_dwState;       // ����ֵ����, EV_ ��ͷ����, _EVENT_OS() ���Բ��ܶ���ɷ����ı����ֽڼ����������͵���Ҫ�ռ��ͷŴ�����������͡�
    INT    m_nArgCount;     // �¼��Ĳ�����Ŀ
    PEVENT_ARG_INFO m_pEventArgInfo;    // �¼�������ַ
}EVENT_INFO, * PEVENT_INFO;

//////////////////////////////////////////////////////////////////////////

///////////////////////////////// 3.2 ���Ժ���ʹ�õ��¼�������Ϣ�ڶ����汾

// ע���ײ�������ȫ���� EVENT_ARG_INFO ��
typedef struct
{
#define EAS_BY_REF (1 << 1)     // ��ʹ�� (1 << 0)
    LPCSTR m_szName;            // ��������
    LPCSTR m_szExplain;         // ������ϸ����
    DWORD  m_dwState;           // EAS_BY_REF, �Ƿ���Ҫ�Բο���ʽ��ֵ,�����λ,��֧�ֿ����׳��¼��Ĵ������ȷ�����ܹ���ϵͳ������(�������ڴ�ķ��������ݵĸ�ʽ�������Ҫ��)��
    DATA_TYPE m_dtDataType;     // ����
}EVENT_ARG_INFO2, * PEVENT_ARG_INFO2;


//////////////////////////////////////////////////////////////////////////
// ע���ײ�������ȫ���� EVENT_INFO ��
typedef struct
{
    LPCSTR m_szName;            // �¼�����
    LPCSTR m_szExplain;         // �¼���ϸ����
    // ���»���״ֵ̬���� EVENT_INFO �еĶ�����ͬ��
    // #define EV_IS_HIDED        (1 << 0)    // ���¼��Ƿ�Ϊ�����¼�(�����ܱ�һ���û���ʹ�û򱻷�����Ϊ�˱��ּ�������Ҫ���ڵ��¼�)��
    // #define EV_IS_KEY_EVENT    (1 << 2)    
    // ע���λ���� __OS_xxxx ������ָ�����¼���֧�ֵĲ���ϵͳ��
    // #define _EVENT_OS(os)    ((os) >> 1)  // ����ת��os�����Ա���뵽m_dwState��
    // #define _TEST_EVENT_OS(m_dwState,os)    ((_EVENT_OS (os) & m_dwState) != 0) // ��������ָ���¼��Ƿ�֧��ָ������ϵͳ��
#define EV_IS_VER2 (1 << 31)    // ��ʾ���ṹΪEVENT_INFO2,!!!ʹ�ñ��ṹʱ������ϴ�״ֵ̬��

    DWORD  m_dwState;           // ����ֵ����, ��ô��� EV_IS_VER2, EV_ ��ͷ����, _EVENT_OS() ���Բ��ܶ���ɷ����ı����ֽڼ����������͵���Ҫ�ռ��ͷŴ�����������͡�
    INT    m_nArgCount;         // �¼��Ĳ�����Ŀ
    PEVENT_ARG_INFO2 m_pEventArgInfo;   // �¼�����
    DATA_TYPE m_dtRetDataType;          //! ��������������ж����������Ҫ�ͷ�,��Ҫ��֧�ֿ����׳��¼��Ĵ��븺�����ͷš�
}EVENT_INFO2, *PEVENT_INFO2;

//////////////////////////////////////////////////////////////////////////

typedef DWORD  HUNIT;

// ͨ�ýӿ�ָ�롣
typedef void (WINAPI* PFN_INTERFACE) ();

// ȡָ���Ľӿڡ�
#define ITF_CREATE_UNIT                     1       // �������
#define ITF_PROPERTY_UPDATE_UI              2       // ָ������Ŀǰ�ɷ��޸�
#define ITF_DLG_INIT_CUSTOMIZE_DATA         3       // ʹ�öԻ������ø��Ӷ�������
#define ITF_NOTIFY_PROPERTY_CHANGED         4       // ֪ͨĳ�������ݱ��û��޸�
#define ITF_GET_ALL_PROPERTY_DATA           5       // ȡȫ����������
#define ITF_GET_PROPERTY_DATA               6       // ȡĳ��������
#define ITF_GET_ICON_PROPERTY_DATA          7       // ȡ���ڵ�ͼ����������(�����ڴ���)
#define ITF_IS_NEED_THIS_KEY                8       // ѯ������Ƿ���Ҫָ���İ�����Ϣ,��������ػ���Ĭ��Ϊϵͳ����İ���,��TAB��SHIFT+TAB��UP��DOWN�ȡ�
#define ITF_LANG_CNV                        9       // �����������ת��
#define ITF_MSG_FILTER                      11      // ��Ϣ����
#define ITF_GET_NOTIFY_RECEIVER             12      // ȡ����ĸ���֪ͨ������(PFN_ON_NOTIFY_UNIT)
typedef INT(WINAPI * PFN_ON_NOTIFY_UNIT) (INT nMsg, DWORD dwParam1, DWORD dwParam2);
#define NU_GET_CREATE_SIZE_IN_DESIGNER    0
// ȡ���ʱ������������õ�������ʱ��Ĭ�ϴ����ߴ�.
// dwParam1: ����: INT*, ���ؿ��(��λ����)
// dwParam2: ����: INT*, ���ظ߶�(��λ����)
// �ɹ�����1,ʧ�ܷ���0.
typedef PFN_INTERFACE(WINAPI * PFN_GET_INTERFACE) (INT nInterfaceNO);

//+////////////////////////////////////////////////////////////////////////

// �������,�ɹ�ʱ���ش��ھ��,phUnit�з���������,ʧ�ܷ���NULL��
// hDesignWnd����blInDesignModeΪ��ʱ����Ч,Ϊ��ƴ���Ĵ��ھ����
typedef HUNIT(WINAPI* PFN_CREATE_UNIT) (LPBYTE pAllData, INT nAllDataSize,
    DWORD dwStyle, HWND hParentWnd, UINT uID, HMENU hMenu, INT x, INT y, INT cx, INT cy,
    DWORD dwWinFormID, DWORD dwUnitID,            // ����֪ͨ��ϵͳ
    HWND hDesignWnd, BOOL blInDesignMode);


// dwState����Ϊ���º�ֵ����ϡ�
#define CNV_NULL        0
#define CNV_FONTNAME    (1 << 0)    // Ϊת��������������(���ڿ��ܱ䳤, ps�б��뱣֤���㹻�Ŀռ���ת�����������)��
typedef void (WINAPI * PFN_CNV)(char* ps, DWORD dwState, int nParam); 

// �����������ת��,���ذ���ת����������ݵ�HGLOBAL���,ʧ�ܷ���NULL��
// nParam����ԭֵ���ݸ�fnCnv�Ķ�Ӧ������
typedef HGLOBAL(WINAPI* PFN_LANG_CNV) (LPBYTE pAllData, LPINT pnAllDataSize, PFN_CNV fnCnv, int nParam);  

//! ���º����������ʱʹ�á�

// ���ָ������Ŀǰ���Ա�����,������,���򷵻ؼ١�
typedef BOOL(WINAPI* PFN_PROPERTY_UPDATE_UI) (HUNIT hUnit, INT nPropertyIndex);

// ���и��Ӷ�������,ʹ�öԻ���������Щ����,���������޸��ڲ����ݼ�����,
// �����Ҫ���´��������޸�����,�����档���pblModified��ΪNULL,�����з����޸�״̬��
typedef BOOL(WINAPI* PFN_DLG_INIT_CUSTOMIZE_DATA) (HUNIT hUnit, INT nPropertyIndex, BOOL* pblModified, LPVOID pResultExtraData);


// ������¼ĳ���Ե�����ֵ��
union UNIT_PROPERTY_VALUE
{
    INT         m_int;          // UD_INT��UD_PICK_INT��UD_PICK_SPEC_INT
    DOUBLE      m_double;       // UD_DOUBLE
    BOOL        m_bool;         // UD_BOOL
    DATE        m_dtDateTime;   // UD_DATE_TIME
    COLORREF    m_clr;          // UD_COLOR��UD_COLOR_TRANS��UD_COLOR_BACK
    LPCSTR      m_szText;       // UD_TEXT��UD_PICK_TEXT��UD_EDIT_PICK_TEXT��UD_DATA_SOURCE_NAME��UD_DATA_PROVIDER_NAME��UD_DSCOL_NAME��UD_ODBC_CONNECT_STR��UD_ODBC_SELECT_STR
    LPCSTR      m_szFileName;   // UD_FILE_NAME

    struct
    {
        LPBYTE m_pData;
        INT    m_nDataSize;
    } m_data;                // UD_PIC��UD_ICON��UD_CURSOR��UD_MUSIC��UD_FONT��UD_CUSTOMIZE��UD_IMAGE_LIST


#ifndef __GCC_
    UNIT_PROPERTY_VALUE()
    {
        memset(this, 0, sizeof(UNIT_PROPERTY_VALUE));
    }

    BOOL IsSame(INT nDataType, UNIT_PROPERTY_VALUE& val)
    {
        switch (nDataType)
        {
        case UD_INT:
        case UD_PICK_INT:
        case UD_PICK_SPEC_INT:
            return m_int == val.m_int;
        case UD_DOUBLE:
            return m_double == val.m_double;
        case UD_BOOL:
            return m_bool == val.m_bool;
        case UD_DATE_TIME:
            return m_dtDateTime == val.m_dtDateTime;
        case UD_COLOR:
        case UD_COLOR_TRANS:
        case UD_COLOR_BACK:
            return m_clr == val.m_clr;
        case UD_TEXT:
        case UD_PICK_TEXT:
        case UD_EDIT_PICK_TEXT:
            /*case UD_DATA_SOURCE_NAME:
            case UD_DATA_PROVIDER_NAME:
            case UD_DSCOL_NAME:
            case UD_ODBC_CONNECT_STR:
            case UD_ODBC_SELECT_STR:*/
            return m_szText == NULL && val.m_szText == NULL ||
                m_szText != NULL && val.m_szText != NULL &&
                strcmp(m_szText, val.m_szText) == 0;
        case UD_FILE_NAME:
            return m_szFileName == NULL && val.m_szFileName == NULL ||
                m_szFileName != NULL && val.m_szFileName != NULL &&
                strcmp(m_szFileName, val.m_szFileName) == 0;
        case UD_PIC:
        case UD_ICON:
        case UD_CURSOR:
        case UD_MUSIC:
        case UD_FONT:
        case UD_CUSTOMIZE:
        case UD_IMAGE_LIST:
            if (m_data.m_nDataSize == val.m_data.m_nDataSize)
            {
                if (m_data.m_nDataSize == 0)
                    return TRUE;
                else
                    return memcmp(m_data.m_pData, val.m_data.m_pData, m_data.m_nDataSize) == 0;
            }
            break;
        default:
#ifdef _DEBUG
            assert(FALSE);
#endif
            break;
        }

        return FALSE;
    }
#endif
};
typedef union UNIT_PROPERTY_VALUE* PUNIT_PROPERTY_VALUE;

// ֪ͨĳһ������(�Ƕ�������)���ݱ��û��޸�,���������޸��ڲ����ݼ�����,���ȷʵ��Ҫ���´��������޸�����,�����档�κ�������������Ӧ��ʾ��Ϣ,���ص�ppszTipText�С�
//! ע�⣺�������ֵ�ĺϷ���У�顣
typedef BOOL(WINAPI* PFN_NOTIFY_PROPERTY_CHANGED) (HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule, LPCSTR* ppszTipText);


// ȡĳ�������ݵ�pPropertyVaule��,�ɹ�������,���򷵻ؼ١�
// !! 1����������ʱ���ܱ��û������ı�(������ֱ�ӵ���API����)������,������ʱ����ȡ������ʵ��ֵ��
// !! 2������ȡ�ص��ı����ֽڼ��ȷ����ж����ڴ������ָ��,���������ͷ�,�׳��򲢲��Ὣ���ͷš�
typedef BOOL(WINAPI* PFN_GET_PROPERTY_DATA) (HUNIT hUnit, INT nPropertyIndex, PUNIT_PROPERTY_VALUE pPropertyVaule);

// ȡȫ����������
typedef HGLOBAL(WINAPI* PFN_GET_ALL_PROPERTY_DATA) (HUNIT hUnit);

// ȡ���ڵ�ͼ����������(�����ڴ���)
typedef HGLOBAL(WINAPI* PFN_GET_ICON_PROPERTY_DATA) (LPBYTE pAllData, INT nAllDataSize);

// ѯ������Ƿ���Ҫָ���İ�����Ϣ,�����Ҫ,������,���򷵻ؼ١�
typedef BOOL(WINAPI* PFN_IS_NEED_THIS_KEY) (HUNIT hUnit, WORD wKey);

// ��Ϣ����(������Ϣ���˴��������Ч,������LDT_MSG_FILTER_CONTROL���),�����˵�������,���򷵻ؼ١�
typedef BOOL(WINAPI* PFN_MESSAGE_FILTER) (void* pMsg); // Windows����ϵͳ��pMsgΪMSG*ָ�롣

//////////////////////////////////////////////////////////////////////////

#define    UNIT_BMP_SIZE                24                      // �����־λͼ�Ŀ�Ⱥ͸߶ȡ�
#define    UNIT_BMP_BACK_COLOR          (RGB(192, 192, 192))    // �����־λͼ�ı�����ɫ��

//! ע��m_pElementBegin��m_pPropertyBeginֻ����һ����ΪNULL,m_nElementCount��m_nPropertyCountֻ����һ����Ϊ0��
typedef struct  // �ⶨ���������ͽṹ
{
    LPCSTR m_szName;            // �������͵���������(�磺��������,���߾��������ȵ�)��
    LPCSTR m_szEgName;          // �������͵�Ӣ������(�磺��int��,��double���ȵ�),��Ϊ�ջ�NULL��
    LPCSTR m_szExplain;         // �������͵���ϸ����,�������ΪNULL��
    INT m_nCmdCount;            // ���������ṩ�ĳ�Ա�������Ŀ(��Ϊ0)��
    LPINT m_pnCmdsIndex;        // ˳���¼�����������г�Ա�����ڿ��������е�����ֵ,��ΪNULL��

#define LDT_IS_HIDED                (1 << 0)    // �������Ƿ�Ϊ��������(���������û�ֱ���������������,�类������Ϊ�˱��ּ�������Ҫ���ڵ�����)��
#define LDT_IS_ERROR                (1 << 1)    // �������ڱ����в���ʹ��,���д˱�־һ����������ʹ���д˱�־,�����͵���������Ҳ�����������塣
#define LDT_WIN_UNIT                (1 << 6)    // �Ƿ�Ϊ���ڻ���ڴ�����ʹ�õ����,��˱�־��λ��m_nElementCount��Ϊ0,
#define LDT_IS_CONTAINER            (1 << 7)    // �Ƿ�Ϊ�������,���д˱�־,LDT_WIN_UNIT����λ��
#define LDT_IS_TAB_UNIT             (1 << 8)    // �Ƿ�ΪTAB�ؼ�(ѡ���) 4.0����
#define LDT_IS_FUNCTION_PROVIDER    (1 << 15)   // �������ṩ���ܵĴ������(��ʱ��),��˱�־��λ��LDT_WIN_UNIT����λ�����д˱�־������ߴ�̶�Ϊ32*32,����������ʱ�޿������Ρ�
#define LDT_CANNOT_GET_FOCUS        (1 << 16)   // �������������,��˱�־��λ���ʾ��������ܽ������뽹��,����TAB��ͣ����
#define LDT_DEFAULT_NO_TABSTOP      (1 << 17)   // �������������,��˱�־��λ���ʾ�����Ĭ�ϲ�ͣ��TAB��,ʹ�ñ���־�����ϱ�־��λ��
#define LDT_ENUM                    (1 << 22)   // �Ƿ�Ϊö���������͡�3.7������
#define LDT_MSG_FILTER_CONTROL      (1 << 5)    // �Ƿ�Ϊ��Ϣ���������

#define _DT_OS(os)     (os)  //! ע���λ���� __OS_xxxx ������ָ��������������֧�ֵĲ���ϵͳ�� ����ת��os�����Ա���뵽m_dwState��
#define _TEST_DT_OS(m_dwState,os)    ((_DT_OS (os) & m_dwState) != 0) // ��������ָ�����������Ƿ�֧��ָ������ϵͳ��
    DWORD m_dwState;    // LDT_ ��ͷ���� _DT_OS() | LDT_

    ////////////////////////////////////////////
    //! ���±���ֻ����Ϊ���ڡ��˵�����Ҳ�Ϊö����������ʱ����Ч��
    DWORD               m_dwUnitBmpID;      // ָ���ڿ��е����ͼ����ԴID,0Ϊ�ޡ���OCX��װ����,m_dwUnitBmpIDָ������ͼ����ԴID��
    INT                 m_nEventCount;      // ����¼�����
    PEVENT_INFO2        m_pEventBegin;      // ���屾����������¼���
    INT                 m_nPropertyCount;   // �����������
    PUNIT_PROPERTY      m_pPropertyBegin;   // ָ��������������Ե�ַ
    PFN_GET_INTERFACE   m_pfnGetInterface;  // �����������

    ////////////////////////////////////////////
    //! ���±���ֻ���ڲ�Ϊ���ڡ��˵������Ϊö����������ʱ����Ч��
    INT    m_nElementCount;    // �������������������������Ŀ����Ϊ���ڡ��˵����,�˱���ֵ��Ϊ0��
    PLIB_DATA_TYPE_ELEMENT m_pElementBegin;  // ָ�������ݳ�Ա���顣
} LIB_DATA_TYPE_INFO, * PLIB_DATA_TYPE_INFO;



//////////////////////////////////////////////////////////////////////////

typedef struct  // �ⳣ�����ݽṹ
{
#define    CT_NULL 0
#define    CT_NUM  1    // value sample: 3.1415926
#define    CT_BOOL 2    // value sample: 1
#define    CT_TEXT 3    // value sample: "abc"
    LPCSTR m_szName;    // ������
    LPCSTR m_szEgName;  // Ӣ����
    LPCSTR m_szExplain; // ˵��
    SHORT  m_shtLayout; // ����Ϊ 1
    SHORT  m_shtType;   // ��������, CT_NULL=�ճ���, CT_NUM=��ֵ��,double����ֵ, CT_BOOL=�߼���, CT_TEXT=�ı���
    LPCSTR m_szText;    // CT_TEXT
    DOUBLE m_dbValue;   // CT_NUM��CT_BOOL
} LIB_CONST_INFO, * PLIB_CONST_INFO;

//+////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// �������ݽṹ��

typedef union
{
    BYTE    m_byte;
    SHORT   m_short;
    INT     m_int;
    INT64   m_int64;
    FLOAT   m_float;
    DOUBLE  m_double;
}SYS_NUM_VALUE, * PSYS_NUM_VALUE;

typedef struct
{
    DWORD m_dwFormID;
    DWORD m_dwUnitID;
}MUNIT, * PMUNIT;

typedef struct
{
    DWORD m_dwStatmentSubCodeAdr;    // ��¼���ص�������ӳ������Ľ����ַ��
    DWORD m_dwSubEBP;    // ��¼������������ӳ����EBPָ��,�Ա���ʸ��ӳ����еľֲ�������
}STATMENT_CALL_DATA, * PSTATMENT_CALL_DATA;

#ifndef __GCC_
#pragma pack (push, old_value)   // ����VC++�������ṹ�����ֽ�����
#pragma pack (1)    // ����Ϊ��һ�ֽڶ��롣
#endif

typedef struct
{
    union
    {
        BYTE   m_byte;            // SDT_BYTE
        SHORT  m_short;            // SDT_SHORT
        INT    m_int;            // SDT_INT
        DWORD  m_uint;            // (DWORD)SDT_INT
        INT64  m_int64;            // SDT_INT64
        FLOAT  m_float;            // SDT_FLOAT
        DOUBLE m_double;        // SDT_DOUBLE
        DATE   m_date;            // SDT_DATE_TIME
        BOOL   m_bool;            // SDT_BOOL
        char* m_pText;            // SDT_TEXT,������ΪNULL��Ϊ�˱����޸ĵ�������(m_pText�п���ָ����������)�е�����,ֻ�ɶ�ȡ�����ɸ������е�����
        LPBYTE m_pBin;            // SDT_BIN,������ΪNULL,ֻ�ɶ�ȡ�����ɸ������е����ݡ�
        DWORD  m_dwSubCodeAdr;    // SDT_SUB_PTR,��¼�ӳ�������ַ��
        STATMENT_CALL_DATA m_statment;    // SDT_STATMENT�������͡�
        MUNIT  m_unit;            // ����������˵��������͡�
        void* m_pCompoundData;    // ����������������ָ��,ָ����ָ�����ݵĸ�ʽ��� run.h ������ֱ�Ӹ������е����ݳ�Ա,���������Ҫ���������ͷŸó�Ա��
        void* m_pAryData;        // ��������ָ��,ָ����ָ�����ݵĸ�ʽ��� run.h ��ע�����Ϊ�ı����ֽڼ�����,���Ա����ָ�����ΪNULL��ֻ�ɶ�ȡ�����ɸ������е����ݡ�

        //! Ϊָ�������ַ��ָ��,�������������������ʵ�ֺ���ʱ�����á�
        BYTE*   m_pByte;    // SDT_BYTE*
        SHORT*  m_pShort;    // SDT_SHORT*
        INT*    m_pInt;        // SDT_INT*
        DWORD*  m_pUInt;    // ((DWORD)SDT_INT)*
        INT64*  m_pInt64;    // SDT_INT64*
        FLOAT*  m_pFloat;    // SDT_FLOAT*
        DOUBLE* m_pDouble;    // SDT_DOUBLE*
        DATE*   m_pDate;    // SDT_DATE_TIME*
        BOOL*   m_pBool;    // SDT_BOOL*
        char**  m_ppText;    // SDT_TEXT,*m_ppText����ΪNULL��ע��д����ֵ֮ǰ�����ͷ�ǰֵ,����MFree (*m_ppText)������ֱ�Ӹ���*m_ppText��ָ�������,ֻ���ͷ�ԭָ�������ָ�롣
        LPBYTE* m_ppBin;    // SDT_BIN,*m_ppBin����ΪNULL��ע��д����ֵ֮ǰ�����ͷ�ǰֵ,����MFree (*m_ppBin)������ֱ�Ӹ���*m_ppBin��ָ�������,ֻ���ͷ�ԭָ�������ָ�롣
        DWORD*  m_pdwSubCodeAdr;            // SDT_SUB_PTR,�ӳ�������ַ������
        PSTATMENT_CALL_DATA m_pStatment;    // SDT_STATMENT�������ͱ�����
        PMUNIT m_pUnit;                // ����������˵��������ͱ�����
        void** m_ppCompoundData;    // �����������ͱ���������ֱ�Ӹ������е����ݳ�Ա,���������Ҫ���������ͷŸó�Ա��
        void** m_ppAryData;            // �������ݱ���,ע�⣺1��д����ֵ֮ǰ�����ͷ�ԭֵ(ʹ��NRS_FREE_VAR֪ͨ)��2���������Ϊ�ı����ֽڼ�����,���Ա����ָ�����ΪNULL������ֱ�Ӹ���*m_ppAryData��ָ�������,ֻ���ͷ�ԭָ�������ָ�롣
    };

    // 1���������������ʱ,����ò������� AS_RECEIVE_VAR_OR_ARRAY ��AS_RECEIVE_ALL_TYPE_DATA ��־, ��Ϊ��������,����������־ DT_IS_ARY, ��Ҳ�� DT_IS_ARY ��־��Ψһʹ�ó��ϡ�
    // 2�����������ݲ�������ʱ,���Ϊ�հ�����,��Ϊ _SDT_NULL ��
    DATA_TYPE m_dtDataType;
} MDATA_INF;
typedef MDATA_INF* PMDATA_INF;

#ifndef __GCC_
#pragma pack (pop, old_value)    // �ָ�VC++�������ṹ�����ֽ�����
#endif


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// ֪ͨ�����ݽṹ��

/*/////////////*/
// �����֪ͨϵͳ����ֵ��

#ifndef __GCC_
struct MDATA
{
    MDATA()
    {
        m_pData = NULL;
        m_nDataSize = 0;
    }
#else
typedef struct
{
#endif

    LPBYTE    m_pData;
    INT        m_nDataSize;

#ifndef __GCC_
};
#else
} MDATA;
#endif
typedef MDATA* PMDATA;

// ������һ���¼�֪ͨ��
#ifndef __GCC_
struct EVENT_NOTIFY
#else
typedef struct
#endif
{
    // ��¼�¼�����Դ
    DWORD  m_dwFormID;        // ���� ID
    DWORD  m_dwUnitID;        // ������� ID
    INT    m_nEventIndex;    // �¼�����
    INT    m_nArgCount;        // �¼������ݵĲ�����Ŀ,��� 5 ����
    INT    m_nArgValue[5];    // ��¼������ֵ,SDT_BOOL �Ͳ���ֵΪ 1 �� 0��

    //!!! ע������������Ա��û�ж��巵��ֵ���¼���������Ч��
    BOOL  m_blHasRetVal;    // �û��¼������ӳ���������¼����Ƿ��з���ֵ
    INT   m_nRetVal;        // �û��¼������ӳ���������¼���ķ���ֵ,�߼�ֵ����ֵ 0(��) �� 1(��) ���ء�

    //////////////////////////////////////////////////////////////////////////

#ifndef __GCC_
    EVENT_NOTIFY(DWORD dwFormID, DWORD dwUnitID, INT nEventIndex)
    {
        memset(this, 0, sizeof(EVENT_NOTIFY));

        m_dwFormID = dwFormID;
        m_dwUnitID = dwUnitID;
        m_nEventIndex = nEventIndex;

        m_nArgCount = 0;
        m_blHasRetVal = FALSE;
        m_nRetVal = 0;
    }
    EVENT_NOTIFY()
    {
        memset(this, 0, sizeof(EVENT_NOTIFY));
    }
};
#else
} EVENT_NOTIFY;
#endif
typedef EVENT_NOTIFY* PEVENT_NOTIFY;

typedef struct
{
#define EAV_IS_POINTER  (1 << 0)
#define EAV_IS_WINUNIT  (1 << 1)    //! ����˵��m_inf.m_dtDataType���������Ƿ�Ϊ���ڵ�Ԫ, ע�����m_inf.m_dtDataTypeΪ���ڵ�Ԫ,�˱�Ǳ�����λ��
    MDATA_INF m_inf;

    //!!! ע����� m_inf.m_dtDataType Ϊ�ı��͡��ֽڼ��͡��ⶨ����������(�������ڵ�Ԫ���˵���������), ���봫��ָ��,������Ǳ�����λ��
    DWORD m_dwState;    // m_inf���Ƿ�Ϊָ�����ݡ�
}EVENT_ARG_VALUE, * PEVENT_ARG_VALUE;

// �����ڶ����¼�֪ͨ��
#ifndef __GCC_
struct EVENT_NOTIFY2
#else
typedef struct
#endif
{
    // ��¼�¼�����Դ
    DWORD m_dwFormID;    // ���� ID
    DWORD m_dwUnitID;    // ������� ID
    INT m_nEventIndex;    // �¼�����

#define MAX_EVENT2_ARG_COUNT    12
    INT m_nArgCount;    // �¼������ݵĲ�����Ŀ,��� MAX_EVENT2_ARG_COUNT ����
    EVENT_ARG_VALUE m_arg[MAX_EVENT2_ARG_COUNT];  // ��¼������ֵ��

    //!!! ע�������Ա��û�ж��巵��ֵ���¼���������Ч��
    BOOL m_blHasRetVal;        // �û��¼������ӳ���������¼����Ƿ��з���ֵ
    MDATA_INF m_infRetData;    // ��¼�û��¼������ӳ���������¼���ķ���ֵ,ע�����е�m_infRetData.m_dtDataType��Աδ��ʹ�á�

    //////////////////////////////////////////////////////////////////////////

#ifndef __GCC_
    EVENT_NOTIFY2(DWORD dwFormID, DWORD dwUnitID, INT nEventIndex)
    {
        memset(this, 0, sizeof(EVENT_NOTIFY2));
        m_dwFormID = dwFormID;
        m_dwUnitID = dwUnitID;
        m_nEventIndex = nEventIndex;
    }
    EVENT_NOTIFY2()
    {
        memset(this, 0, sizeof(EVENT_NOTIFY2));
    }
};
#else
} EVENT_NOTIFY2;
#endif
typedef EVENT_NOTIFY2* PEVENT_NOTIFY2;

typedef struct
{
    HICON m_hBigIcon;
    HICON m_hSmallIcon;
} APP_ICON, * PAPP_ICON;

//////////////////////////////////////////////////////////////////////////

//++ NES_ ��Ϊ�����ױ༭���������֪ͨ��

// ȡ�ױ༭���������ڵľ��,����֧��֧�ֿ��AddIn��
#define NES_GET_MAIN_HWND               1

// ֪ͨ�ױ༭��������ָ���Ĺ���,����һ��BOOLֵ��
// dwParam1Ϊ���ܺš�
// dwParam2Ϊһ��˫DWORD����ָ��,�ֱ��ṩ���ܲ���1��2��
#define NES_RUN_FUNC                    2

// ֪ͨ�ױ༭������ʾһ���Ի����г�ָ��ͼƬ���ڵ�����ͼƬ,�������û���ѡ��ͼƬ�������š�
//        dwParam1Ϊ�����������Ч��ͼƬ������
//        dwParam2�����ΪNULL,��ϵͳ��Ϊ��Ϊһ���༭��HWND���ھ��,���û�������Чѡ���,ϵͳ���Զ����Ĵ˱༭������ݲ�������ת����ȥ��
// �����û���ѡ��ͼƬ��������(-1��ʾ�û�ѡ����ͼƬ),����û�δѡ��,�򷵻�-2��
#define NES_PICK_IMAGE_INDEX_DLG        7


//++ NAS_ ��Ϊ�ȱ��ױ༭�����ֱ������л��������֪ͨ��

// ֪ͨϵͳ���������س����ͼ�ꡣ
// dwParam1ΪPAPP_ICONָ�롣
#define NAS_GET_APP_ICON                1000

// ����ָ���ⶨ���������͵�PLIB_DATA_TYPE_INFO������Ϣָ�롣
// dwParam1Ϊ�������������͡�
// ���������������Ч���߲�Ϊ�ⶨ����������,�򷵻�NULL,���򷵻�PLIB_DATA_TYPE_INFOָ�롣
#define NAS_GET_LIB_DATA_TYPE_INFO      1002

// dwParam1ΪͼƬ����ָ��,dwParam2ΪͼƬ���ݳߴ硣
// ����ɹ����ط�NULL��HBITMAP���(ע��ʹ����Ϻ��ͷ�),���򷵻�NULL��
#define NAS_GET_HBITMAP                 1003

// ���ص�ǰϵͳ�����л�����֧�ֵ�����ID,����IDֵ���lang.h
#define NAS_GET_LANG_ID                1004

// ���ص�ǰϵͳ�����л����İ汾��,LOWORDΪ���汾��,HIWORDΪ�ΰ汾�š�
#define NAS_GET_VER                    1005

/* ���ص�ǰ���������л�����ĳһ��Ŀ¼���ļ���,Ŀ¼���ԡ�\��������
    dwParam1: ָ������Ҫ��Ŀ¼,����Ϊ����ֵ��
        A�����������л����¾���Ч��Ŀ¼:
            1: ���������л���ϵͳ������Ŀ¼;
        B��������������Ч��Ŀ¼(��������������Ч):
            1001: ϵͳ���̺�֧�ֿ���������Ŀ¼��
            1002: ϵͳ��������Ŀ¼
            1003: ϵͳ������Ϣ����Ŀ¼
            1004: �������еǼǵ�ϵͳ����ģ���Ŀ¼
            1005: ֧�ֿ����ڵ�Ŀ¼
            1006: ��װ��������Ŀ¼
        C�����л�������Ч��Ŀ¼(�����л�������Ч):
            2001: �û�EXE�ļ�����Ŀ¼;
            2002: �û�EXE�ļ���;
    dwParam2: ���ջ�������ַ,�ߴ����ΪMAX_PATH��*/
#define NAS_GET_PATH                1006

// ͨ��ָ��HWND�������һ��CWND����,������ָ��,��ס��ָ�����ͨ������NRS_DELETE_CWND_OBJECT���ͷ�
// dwParam1ΪHWND���
// �ɹ�����CWnd*ָ��,ʧ�ܷ���NULL
#define NAS_CREATE_CWND_OBJECT_FROM_HWND    1007

// ɾ��ͨ��NRS_CREATE_CWND_OBJECT_FROM_HWND������CWND����
// dwParam1Ϊ��ɾ����CWnd����ָ��
#define NAS_DELETE_CWND_OBJECT              1008

// ȡ��ͨ��NRS_CREATE_CWND_OBJECT_FROM_HWND������CWND����������HWND�İ�
// dwParam1ΪCWnd����ָ��
// �ɹ�����HWND,ʧ�ܷ���0
#define NAS_DETACH_CWND_OBJECT              1009

// ��ȡͨ��NRS_CREATE_CWND_OBJECT_FROM_HWND������CWND�����е�HWND
// dwParam1ΪCWnd����ָ��
// �ɹ�����HWND,ʧ�ܷ���0
#define NAS_GET_HWND_OF_CWND_OBJECT         1010

// ��ָ��HWND��ͨ��NRS_CREATE_CWND_OBJECT_FROM_HWND������CWND���������
// dwParam1ΪHWND
// dwParam2ΪCWnd����ָ��
// �ɹ�����1,ʧ�ܷ���0
#define NAS_ATTACH_CWND_OBJECT              1011

// ���ָ������Ϊ�����Դ��ڻ����������,������,���򷵻ؼ١�
// dwParam1Ϊ�����Ե�HWND.
#define    NAS_IS_EWIN                            1014


//++ NRS_ ��Ϊ���ܱ������л��������֪ͨ��

// ֪ͨϵͳָ��������Ѿ������١�
// dwParam1ΪdwFormID
// dwParam2ΪdwUnitID
#define NRS_UNIT_DESTROIED                    2000

// ת��������ֵ��ʽ��������
// dwParam1Ϊ PMDATA_INF ָ��,�� m_dtDataType ����Ϊ��ֵ�͡�����ת���������ֵ��
#define NRS_CONVERT_NUM_TO_INT              2001

// ȡ��ǰ�������ı�
// �����������ı�ָ��,�п���Ϊ�մ���
#define NRS_GET_CMD_LINE_STR                2002

// ȡ��ǰִ���ļ�����Ŀ¼����
// ���ص�ǰִ���ļ�����Ŀ¼�ı�ָ�롣
#define NRS_GET_EXE_PATH_STR                2003

// ȡ��ǰִ���ļ�����
// ���ص�ǰִ���ļ������ı�ָ�롣
#define NRS_GET_EXE_NAME                    2004

// ȡ�������ָ��
// dwParam1ΪWinForm��ID
// dwParam2ΪWinUnit��ID
// �ɹ�������Ч���������CWnd*ָ��,ʧ�ܷ���0��
#define NRS_GET_UNIT_PTR                    2006

// ȡ�������ָ��
// dwParam1ΪWinForm��ID
// dwParam2ΪWinUnit��ID
// �ɹ�������Ч���������CWnd*ָ��,ʧ�ܱ�������ʱ�����˳�����
#define NRS_GET_AND_CHECK_UNIT_PTR            2007

// �Ե�һ�෽ʽ֪ͨϵͳ�������¼���
// dwParam1ΪPEVENT_NOTIFYָ�롣
// ������� 0 ,��ʾ���¼��ѱ�ϵͳ����,�����ʾϵͳ�Ѿ��ɹ����ݴ��¼����û��¼������ӳ���
#define NRS_EVENT_NOTIFY                    2008

// ֪ͨϵͳ�������д������¼���
#define    NRS_DO_EVENTS                        2018

// dwParam1ΪWinForm��ID
// dwParam2ΪWinUnit��ID
// �ɹ�������Ч�� DATA_TYPE ,ʧ�ܷ��� 0 ��
#define NRS_GET_UNIT_DATA_TYPE              2022

// �ͷ�ָ���������ݡ�
// dwParam1Ϊ�����ݵ�DATA_TYPE,ֻ��Ϊϵͳ�������͡�
// dwParam2Ϊָ����������ݵ�ָ�롣
#define NRS_FREE_ARY                        2023

// ����ָ���ռ���ڴ�,�������׳��򽻻����ڴ涼����ʹ�ñ�֪ͨ���䡣
// dwParam1Ϊ�������ڴ��ֽ�����
// dwParam2��Ϊ0,���������ʧ�ܾ��Զ���������ʱ���˳������粻Ϊ0,���������ʧ�ܾͷ���NULL�������������ڴ���׵�ַ��
#define NRS_MALLOC                          2024

// �ͷ��ѷ����ָ���ڴ档
// dwParam1Ϊ���ͷ��ڴ���׵�ַ��
#define NRS_MFREE                           2025

// ���·����ڴ档
// dwParam1Ϊ�����·����ڴ�ߴ���׵�ַ��
// dwParam2Ϊ�����·�����ڴ��ֽ�����
// ���������·����ڴ���׵�ַ,ʧ���Զ���������ʱ���˳�����
#define NRS_MREALLOC                        2026

// ֪ͨϵͳ�Ѿ���������ʱ����
// dwParam1Ϊchar*ָ��,˵�������ı���
#define    NRS_RUNTIME_ERR                        2027

// ֪ͨϵͳ�˳��û�����
// dwParam1Ϊ�˳�����,�ô��뽫�����ص�����ϵͳ��
#define    NRS_EXIT_PROGRAM                    2028

// ���ص�ǰ�û����������,ΪPT_DEBUG_RUN_VER(���԰�)��PT_RELEASE_RUN_VER(������)��
#define NRS_GET_PRG_TYPE                    2030

// �Եڶ��෽ʽ֪ͨϵͳ�������¼���
// dwParam1ΪPEVENT_NOTIFY2ָ�롣
// ������� 0 ,��ʾ���¼��ѱ�ϵͳ����,�����ʾϵͳ�Ѿ��ɹ����ݴ��¼����û��¼������ӳ���
#define NRS_EVENT_NOTIFY2                    2031

// ���ص�ǰ����Ĵ�����Ŀ��
#define NRS_GET_WINFORM_COUNT               2032

// ����ָ������Ĵ��ھ��,����ô�����δ������,����NULL��
// dwParam1Ϊ����������
#define NRS_GET_WINFORM_HWND                2033

// ����ָ��HBITMAP��ͼƬ����,�ɹ����ذ���BMPͼƬ���ݵ�HGLOBAL���,ʧ�ܷ���NULL��
// dwParam1Ϊ����ȡ��ͼƬ���ݵ�HBITMAP��
#define NRS_GET_BITMAP_DATA                 2034

// ֪ͨϵͳ�ͷ�ָ����DTP_COM_OBJECT����COM����
// dwParam1Ϊ��COM����ĵ�ַָ�롣
#define NRS_FREE_COMOBJECT                  2035

// ��ѡ����Ӽб��л���, ʹ�ñ���Ϣ֪ͨ��ϵͳ
#define NRS_CHK_TAB_VISIBLE                 2039


//////////////////////////////////////////////////////////////////////////
//++ ϵͳ����֪ͨ�����ֵ��

    // ��֪��֪ͨϵͳ�õĺ���ָ��,��װ��֧�ֿ�ǰ֪ͨ,�����ж��,��֪ͨ��ֵӦ�ø���ǰ����֪ͨ��ֵ,���Է���ֵ��
    // ��ɽ��˺���ָ���¼�����Ա�����Ҫʱʹ����֪ͨ��Ϣ��ϵͳ��
    // dwParam1: (PFN_NOTIFY_SYS)
#define NL_SYS_NOTIFY_FUNCTION              1

// ֪֧ͨ�ֿ��ͷ���Դ׼���˳����ͷ�ָ���ĸ������ݡ�
#define NL_FREE_LIB_DATA                    6

// ������������ʵ�ֺ����ĵĺ�����������(char*[]), ֧�־�̬����Ķ�̬����봦��
#define NL_GET_CMD_FUNC_NAMES               14

// ���ش���ϵͳ֪ͨ�ĺ�������(PFN_NOTIFY_LIB��������), ֧�־�̬����Ķ�̬����봦��
#define NL_GET_NOTIFY_LIB_FUNC_NAME         15

// ���ؾ�̬����������������̬���ļ����б�(��ʽΪ\0�ָ����ı�,��β����\0), ֧�־�̬����Ķ�̬����봦��
// kernel32.lib user32.lib gdi32.lib �ȳ��õ�ϵͳ�ⲻ��Ҫ���ڴ��б���
// ����NULL��NR_ERR��ʾ��ָ�������ļ�
#define NL_GET_DEPENDENT_LIBS               16

// ��֧�ֿ���IDE�б��û�ȡ��ѡ����ͱ�֪ͨ
#define NL_UNLOAD_FROM_IDE                  17

// ����NR_DELAY_FREE��ʾ��֧�ֿ���Ҫ���ӳ��ͷ�
#define NR_DELAY_FREE                       2015

// ��IDE�Ѿ�׼���ý����û�������,��֪ͨ�����͵����о���LBS_IDE_PLUGIN��־��֧�ֿ�.
// ע��: ���û���֧�ֿ����öԻ�����ȡ����ѡ��֧�ֿ��ѡ���µ�֧�ֿ��,��֪ͨ�ᱻ�ٴη���,֧�ֿ�����Ҫ����ô������.
#define NL_IDE_READY                    18

// ���û���IDE�е�������Ҽ����������˵�ǰ,��֪ͨ�����͵����о���LBS_IDE_PLUGIN��־��֧�ֿ�.
// dwParam1: �������˵����(HMENU)
// dwParam2: �������˵���������������(e.exe)�е���ԴID
#define NL_RIGHT_POPUP_MENU_SHOW        19

// ��IDE׼����ʾ�¼����Ա�Ի���֮ǰ,��֪ͨ�����͵����о���LBS_IDE_PLUGIN��־��֧�ֿ�.
// ����1��ʾ��֪ͨ��������IDE���ݷ������������ָ�����³�Ա,����2��ʾ��֪ͨ��������IDE��ֹ����³�Ա,����0��ʾδ������.
// dwParam1: �ṩ�������Ա������(ADD_NEW_ELEMENT_TYPE)
// dwParam2:
//   ���dwParam1ΪNAN_NEW_VAR,��Ϊһ��ָ��RES_NEW_VAR_INFO��ָ��;
//   ���dwParam1ΪNAN_NEW_SUB,��Ϊһ��ָ���������ӳ������Ƶ��ı�ָ��;
//   ���dwParam1ΪNAN_NEW_CONST_RES,��Ϊһ��ָ��RES_NEW_CONST_RES_INFO��ָ��.
#define NL_ADD_NEW_ELEMENT                20


typedef enum
{
    NAN_NEW_VAR,            // ����
    NAN_NEW_SUB,            // �ӳ���
    NAN_NEW_CONST_RES       // ������Դ
}
ADD_NEW_ELEMENT_TYPE;       // �������³�Ա������
typedef enum
{
    NVET_GLOBAL_VAR,        // ȫ�ֱ���
    NVET_MOD_VAR,           // ģ�����
    NVET_LOCAL_VAR          // �ֲ�����
}NEW_VAR_EXTENT_TYPE;       // �±����ķ�Χ����

typedef struct
{
    const TCHAR* m_szNewVarName;    // in �±���������
    DATA_TYPE m_dtNewVar;    // out ���������±�������������
    NEW_VAR_EXTENT_TYPE m_enNewVarExtentType;    // out ���������±����ķ�Χ����
}RES_NEW_VAR_INFO;

typedef struct
{
    const TCHAR* m_szNewConstName;          // in �³���������
    TCHAR m_acConstInitialValue[256];       // out ���������³����ĳ�ʼֵ
}RES_NEW_CONST_RES_INFO;

//+////////////////////////////////////////////////////////////////////////

#define NR_OK           0
#define NR_ERR          -1


typedef INT(WINAPI* PFN_NOTIFY_LIB) (INT nMsg, DWORD dwParam1, DWORD dwParam2);    // �˺�������ϵͳ֪ͨ���й��¼���
typedef INT(WINAPI* PFN_NOTIFY_SYS) (INT nMsg, DWORD dwParam1, DWORD dwParam2);    // �˺���������֪ͨϵͳ�й��¼���



/* ��������ͷ���ʵ�ֺ�����ԭ�͡�
   1�������� CDECL ���÷�ʽ;
   2��pRetData ������������;
   3�����ָ����������������Ͳ�Ϊ _SDT_ALL ,���Բ���� pRetData->m_dtDataType,���Ϊ _SDT_ALL ,�������д;
   4��pArgInf �ṩ�������ݱ���,��ָ��� MDATA_INF ����ÿ���������,��Ŀ��ͬ�� nArgCount ��*/
typedef void (*PFN_EXECUTE_CMD) (PMDATA_INF pRetData, INT nArgCount, PMDATA_INF pArgInf);

typedef INT(WINAPI* PFN_RUN_ADDIN_FN) (INT nAddInFnIndex);        // ����֧�ֿ���ADDIN���ܵĺ���
typedef INT(WINAPI* PFN_SUPER_TEMPLATE) (INT nTemplateIndex);    // ���������ṩ�ĳ���ģ�����ĺ���

//////////////////////////////////////////////////////////////////////////

#define LIB_FORMAT_VER    20000101    // ���ʽ��

typedef struct
{
    DWORD  m_dwLibFormatVer;        // ���ʽ��,Ӧ�õ���LIB_FORMAT_VER����Ҫ��;���£�Ʃ�� krnln.fnX ��,�����������ͬ����������ȫ��һ�µĿ�ʱ,Ӧ���ı�˸�ʽ��,�Է�ֹ����װ�ء�
    LPCSTR m_szGuid;                // ��Ӧ�ڱ����ΨһGUID��,����ΪNULL���,������а汾�˴���Ӧ��ͬ�����ΪActiveX�ؼ�,�˴���¼��CLSID��
    INT    m_nMajorVersion;         // ��������汾��,�������0��
    INT    m_nMinorVersion;         // ����Ĵΰ汾�š�
    INT    m_nBuildNumber;          // �����汾��,����Դ˰汾�����κδ������汾�Ž�����������ͬ��ʽ�汾�ŵ�ϵͳ���(Ʃ������޸��˼��� BUG,��ֵ��������ʽ�汾��ϵͳ���)���κι��������û�ʹ�õİ汾�乹���汾�Ŷ�Ӧ�ò�һ������ֵʱӦ��˳�������
    INT    m_nRqSysMajorVer;        // ����Ҫ��������ϵͳ�����汾�š�
    INT    m_nRqSysMinorVer;        // ����Ҫ��������ϵͳ�Ĵΰ汾�š�
    INT    m_nRqSysKrnlLibMajorVer; // ����Ҫ��ϵͳ����֧�ֿ�����汾�š�
    INT    m_nRqSysKrnlLibMinorVer; // ����Ҫ��ϵͳ����֧�ֿ�Ĵΰ汾�š�

    LPCSTR m_szName;    // ����,����ΪNULL��ա�
    INT    m_nLanguage;    // ����֧�ֵ����ԡ�
    LPCSTR m_szExplain;    // ����ϸ����

#define LBS_FUNC_NO_RUN_CODE        (1 << 2)    // �����Ϊ������,û�ж�Ӧ���ܵ�֧�ִ���,��˲������С�
#define LBS_NO_EDIT_INFO            (1 << 3)    // �������޹��༭�õ���Ϣ(�༭��Ϣ��ҪΪ���������ơ������ַ�����)��
#define LBS_IS_DB_LIB               (1 << 5)    // �����Ƿ�Ϊ���ݿ����֧�ֿ⡣
#define LBS_LIB_INFO2               (1 << 7)    // ����Ϣ�ṹʵ�����Ƿ�ΪLIB_INFO2
#define LBS_IDE_PLUGIN              (1 << 8)    // ��֧�ֿ��Ƿ�Ϊ������IDE���. ע��: ֻ�������˴˱�־��֧�ֿ�,�Ż���յ�����������IDE��NL_IDE_READY��NL_RIGHT_POPUP_MENU_SHOW�����֪ͨ.

//!!! ע���λ���� __OS_xxxx �����ڱ�����֧�ֿ���е����в���ϵͳ�汾��
#define _LIB_OS(os)     (os)    // ����ת��os�����Ա���뵽m_dwState��
#define _TEST_LIB_OS(m_dwState,os)    ((_LIB_OS (os) & m_dwState) != 0) // ��������֧�ֿ��Ƿ����ָ������ϵͳ�İ汾��
    DWORD  m_dwState;           // _LIB_OS() | LBS_ ��ͷ����, ����ǲ��,������� LBS_IDE_PLUGIN

    LPCSTR m_szAuthor;          // ����
    LPCSTR m_szZipCode;         // �ʱ�
    LPCSTR m_szAddress;         // ��ַ
    LPCSTR m_szPhoto;           // �绰
    LPCSTR m_szFax;             // ����
    LPCSTR m_szEmail;           // ����
    LPCSTR m_szHomePage;        // ��ҳ
    LPCSTR m_szOther;           // ������Ϣ

    //////////////////
    INT                 m_nDataTypeCount;   // �������Զ����������͵���Ŀ��
    PLIB_DATA_TYPE_INFO m_pDataType;        // ���������е��Զ����������͡����Բο�ʹ��ϵͳ����֧�ֿ��е��Զ�����������,ϵͳ����֧�ֿ��ڳ���Ŀ�Ǽ������е�����ֵ��1���ֵΪ1��
    INT                 m_nCategoryCount;   // ȫ�����������Ŀ,��Ϊ0��
    LPCSTR              m_szzCategory;      // ȫ���������˵����


    INT                 m_nCmdCount;        // �������ṩ����������(ȫ�������������)����Ŀ(��Ϊ0)��
    PCMD_INFO           m_pBeginCmdInfo;    // ��ΪNULL
    PFN_EXECUTE_CMD*    m_pCmdsFunc;        // ָ��ÿ�������ʵ�ִ����׵�ַ,��ΪNULL


    // �й�AddIn���ܵ�˵��,�����ַ���˵��һ�����ܡ���һ��Ϊ��������(����һ��20�ַ�,���ϣ�����г�ʼλ�ö������Զ����뵽���߲˵�,
    // ������Ӧ����@��ʼ,��ʱ����յ�ֵΪ -(nAddInFnIndex + 1) �ĵ���֪ͨ),
    // �ڶ���Ϊ������ϸ����(����һ��60�ַ�),����������մ�������
    PFN_RUN_ADDIN_FN    m_pfnRunAddInFn;    // ��ΪNULL
    LPCSTR              m_szzAddInFnInfo;   // ������ϸ���ܣ�����һ��60�ַ���������������մ�������

    PFN_NOTIFY_LIB      m_pfnNotify;        // ����ΪNULL,��������ͨѶ�ĺ���

    // ����ģ����ʱ�������á�
    // �й�SuperTemplate��˵��,�����ַ���˵��һ��SuperTemplate��
    // ��һ��ΪSuperTemplate����(����һ��30�ַ�),�ڶ���Ϊ��ϸ����(����),����������մ�������
    PFN_SUPER_TEMPLATE  m_pfnSuperTemplate;   // ��ΪNULL
    LPCSTR              m_szzSuperTemplateInfo;              // ��ϸ����(���޳���), ����������մ�������

    INT                 m_nLibConstCount;            // ����Ԥ�ȶ�������г���������
    PLIB_CONST_INFO     m_pLibConst;    // ����Ԥ�ȶ�������г�����

    LPCSTR              m_szzDependFiles;        // ��ΪNULL, ����������������Ҫ����������֧���ļ�

}LIB_INFO, * PLIB_INFO;

#define    FUNCNAME_GET_LIB_INFO        "GetNewInf"     // �����Ʊ���̶�(3.0��ǰΪ"GetLibInf")
typedef PLIB_INFO(WINAPI* PFN_GET_LIB_INFO) ();    // ȡ֧�ֿ���Ϣ����
typedef INT(*PFN_ADD_IN_FUNC) ();

// ��LBS_LIB_INFO2����λʱFUNCNAME_GET_LIB_INFOʵ�ʷ��ص��Ǵ���Ϣ�ṹ
typedef struct
{
    // ֧�ֿ���Ȩ��Ϣ
    LPCSTR m_szHardwareCode;  // // �ṩ��֧�ֿ⹺���ߵı������Ӳ��������,������ΪNULL����ı�.
    LPCSTR m_szBuyingTips;  // �ṩ��֧�ֿ⹺���ߵ���ʾ��Ϣ,������ΪNULL����ı�.
    LPCSTR m_szBuyingURL;  // �����ΪNULL����ı�,���ṩһ���������ܹ�����Ϣ��URL,�û�ѡ����֧�ֿ�ʱϵͳ���Զ�����������򿪴�URL,��������û���Ϣ�����������.
    LPCSTR m_szLicenseToUserName;  // ��֧�ֿ�����Ȩ�����û�����,���ΪNULL/���ı�,˵����ǰʹ������δ�õ���Ȩ.
}LIB_INFO2, * PLIB_INFO2;

//////////////////////////////////////////////////////////////////////////

#define LIB_BMP_RESOURCE        "LIB_BITMAP"        // ֧�ֿ����ṩ��ͼ����Դ������
#define LIB_BMP_CX              16                  // ÿһͼ����Դ�Ŀ��
#define LIB_BMP_CY              13                  // ÿһͼ����Դ�ĸ߶�
#define LIB_BMP_BKCOLOR         RGB(255, 255, 255)  // ͼ����Դ�ĵ�ɫ

////////////////////////////

#define    WU_GET_WND_PTR       (WM_APP + 2)        // �����ڷǺ���֧�ֿ��еĴ������֧���¼�����



//ȡʱ�䲿��,����1Ϊֻ��ʱ�䲿�ֵ�DATE����
inline void GetTimePart(DATE dt, INT& nHour, INT& nMinute, INT& nSecond)
{
    INT nSecCount = (int)DATE(86400 * fabs(dt) + 0.5);//������
    nHour = nSecCount / 3600;
    nSecCount %= 3600;
    nMinute = nSecCount / 60;
    nSecond = nSecCount % 60;
}

//ȡ���ڲ���,����1Ϊֻ�����ڲ��ֵ�DATE����
//1899��12��30��0ʱ00��00�� Ϊ0��׼,��λΪ������С��ֵ
inline void GetDatePart(DATE dt, INT& nYear, INT& nMonth, INT& nDay)
{
    if (dt == 0 || dt == 1)
    {
        nYear = 1899;
        nMonth = 12;
        nDay = 30 + (int)dt;
        return;
    }
    INT nCountDay;
    INT nStatrYear;
    INT nYearDay;
    INT nStep;
    if (dt > 0)
    {
        nCountDay = (int)dt - 1;//��1900��1��1��Ϊ��׼
        nStatrYear = 1900;
        nStep = 1;
    }
    else
    {
        nCountDay = (int)fabs(dt - 1);//��1899��12��31��Ϊ��׼
        nStatrYear = 1899;
        nStep = -1;
    }

    while (1)
    {
        nYearDay = 365;
        if ((nStatrYear % 400 == 0) || (nStatrYear % 100 != 0) && (nStatrYear % 4 == 0))//����
            nYearDay++;
        if (nCountDay <= nYearDay)//������ķ�Χ��
        {
            nYear = nStatrYear;
            if (nStep == -1)
            {
                nCountDay = nYearDay - nCountDay;
            }

            break;
        }
        nCountDay -= nYearDay;
        nStatrYear += nStep;
    }
    DWORD nMonDay[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((nYear % 400 == 0) || (nYear % 100 != 0) && (nYear % 4 == 0))//����
        nMonDay[1] = 29; //����

    for (INT i = 0; i < 12; i++)
    {
        if (nCountDay <= (int)nMonDay[i])
        {
            nMonth = i + 1;
            nDay = nCountDay;
            break;
        }
        nCountDay -= nMonDay[i];

    }

}

//��ʽ��ʱ���ı�
inline void DateTimeFormat(LPSTR strValue, int size, DATE dtDt, BOOL bOnlyDatePart)
{
    DATE dd, dt;
    INT nYear, nMonth, nDay, nHour, nMinute, nSecond;
    dt = modf(dtDt, &dd);


    GetTimePart(dt, nHour, nMinute, nSecond);
    GetDatePart(dd, nYear, nMonth, nDay);


    char strFormat[128];
#if _MSC_VER < 1201

    strcpy(strFormat, "%d-%02d-%02d ");


    //��ʽ��ʱ�䲿��
    char strFormatTime[128];

    if (nSecond)
        strcpy(strFormatTime, "%02d:%02d:%02d");
    else if (nMinute && nSecond == 0)
        strcpy(strFormatTime, "%02d:%02d");
    else if (nHour && nMinute == 0 && nSecond == 0)
        strcpy(strFormatTime, "%02d");
    else
        strFormatTime[0] = 0;

    if (bOnlyDatePart == FALSE)
        strcat(strFormat, strFormatTime);


    sprintf(strValue, strFormat, nYear, nMonth, nDay, nHour, nMinute, nSecond);
#else

    strcpy_s(strFormat, 128, "%d-%02d-%02d ");


    //��ʽ��ʱ�䲿��
    char strFormatTime[128];

    if (nSecond)
        strcpy_s(strFormatTime, 128, "%02d:%02d:%02d");
    else if (nMinute && nSecond == 0)
        strcpy_s(strFormatTime, 128, "%02d:%02d");
    else if (nHour && nMinute == 0 && nSecond == 0)
        strcpy_s(strFormatTime, 128, "%02d");
    else
        strFormatTime[0] = 0;

    if (bOnlyDatePart == FALSE)
        strcat_s(strFormat, 128, strFormatTime);

    sprintf_s(strValue, size, strFormat, nYear, nMonth, nDay, nHour, nMinute, nSecond);

#endif
}
//ȡָ��ʱ�� ����ʱ��ֵ������ȷ��
//1899��12��30��0ʱ00��00�� Ϊ0��׼,��λΪ������С��ֵ
inline double GetSpecDateTime(INT nYear, INT nMonth, INT nDay, INT nHour, INT nMinute, INT nSecond)
{

    double nSecCount = (double)nHour * 3600;//������
    nSecCount += ((double)nMinute * 60);
    nSecCount += nSecond;
    double dTime = nSecCount / 86400;
    double dDate = 0;
    INT nStep;


    if (nYear == 1899)
    {
        if (nMonth == 12)
        {
            if (nDay >= 30)
            {
                dDate = (double)nDay - 30;
                return (dDate + dTime);
            }

        }

        nStep = -1;
    }
    else if (nYear > 1899)
    {
        nStep = 1;

    }
    else
        nStep = -1;



    INT nStatrYear;
    INT nYearDay;
    INT nCountDay = 0;
    if (nStep == 1)
        nStatrYear = 1900;//��1900��1��1��Ϊ��׼
    else
        nStatrYear = 1899;



    while (1)
    {

        if (nStatrYear == nYear)
        {
            DWORD nMonDay[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
            if ((nYear % 400 == 0) || (nYear % 100 != 0) && (nYear % 4 == 0))//����
                nMonDay[1] = 29; //����
            if (nStep == 1)
            {
                for (INT i = 0; i < 12; i++)
                {
                    if (i == nMonth - 1)
                    {
                        nCountDay += nDay;
                        break;
                    }
                    nCountDay += nMonDay[i];
                }
            }
            else {

                for (INT i = 11; i >= 0; i--)
                {
                    if (i == nMonth - 1)
                    {
                        nCountDay += (nMonDay[i] - nDay);

                        break;
                    }
                    nCountDay += nMonDay[i];
                }

            }
            break;

        }
        nYearDay = 365;
        if ((nStatrYear % 400 == 0) || (nStatrYear % 100 != 0) && (nStatrYear % 4 == 0))//����
            nYearDay++;
        nCountDay += nYearDay;
        nStatrYear += nStep;

    }

    if (nStep == 1)
    {
        dDate = (double)nCountDay + 1.0;
        return (dDate + dTime);
    }


    dDate = -((double)nCountDay - 1.0 + dTime);
    return dDate;

}



#endif

//#define SDT_TYPE_OBJECT _SDT_NULL
