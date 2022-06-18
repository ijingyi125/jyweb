#pragma once
#include "hook/MinHook.h"


// ÿ������������׳��쳣,����Ϊ apiHookError
class apiHook
{
private:
    PVOID m_oldFun;    // hookǰ�ĵ�ַ
    PVOID* m_ppOld;    // �ɿ�ʼhookʱ�������,ȡ��hookʱ,��ԭ��������m_oldFunд�뵽�����ַ��
    bool m_isBegin;    // �Ƿ��Ѿ���ʼhook
    PVOID m_newFun;    // hook��ָ��ĵ�ַ
public:
    // Ĭ�Ϲ��캯��,������
    apiHook() : m_oldFun(0), m_ppOld(0), m_isBegin(0), m_newFun(0)
    {
    }

    // ��ʼ��
    // oldFun    = ��hook�ĵ�ַ,ͬʱhook�ɹ�����ԭ��ַд������,ʧ����д�� &(LPVOID&)function
    // newFun    = hookָ��ĵ�ַ,�����뱻hook�ĵ�ַ����һ��
    // isBegin    = �Ƿ�ʼhook,Ĭ��Ϊ��
    apiHook(LPVOID* oldFun, LPVOID newFun, bool isBegin = true) : m_oldFun(0), m_ppOld(0), m_isBegin(0), m_newFun(0)
    {
        hook(oldFun, newFun);
    }

    // ����ʼ��
    ~apiHook()
    {
        unHook();
    }

    // hook
    // oldFun    = ��hook�ĵ�ַ,ͬʱhook�ɹ�����ԭ��ַд������,ʧ����д�� &(LPVOID&)function
    // newFun    = hookָ��ĵ�ַ,�����뱻hook�ĵ�ַ����һ��
    // isBegin    = �Ƿ�ʼhook,Ĭ��Ϊ��
    bool hook(LPVOID* oldFun, LPVOID newFun, bool isBegin = true)
    {
        if (!oldFun || !newFun)return false;
        if ((*oldFun == m_oldFun && m_newFun == newFun) || (oldFun == m_ppOld && m_newFun == newFun))
            return true;

        int ret = MH_Initialize();
        if (ret != MH_OK && ret != MH_ERROR_ALREADY_INITIALIZED)
            return false;

        if (m_oldFun) unHook();
        m_ppOld = oldFun;
        m_oldFun = *oldFun;
        m_newFun = newFun;

        if (MH_CreateHook(m_oldFun, newFun, reinterpret_cast<LPVOID*>(oldFun)) != MH_OK)
            return false;
        if (isBegin) return begin();
        return true;
    }

    // ��ʼhook, ���ؼ����ʾδhook
    bool begin()
    {
        if (!m_oldFun)return false;
        if (m_isBegin)return true;    // �Ѿ���ʼ�Ͳ�����ִ��,ֱ�ӷ�����

        if (MH_EnableHook(m_oldFun) != MH_OK)
            return false;
        m_isBegin = true;
        return true;
    }

    // ��ͣhook, ���ؼ����ʾδhook
    bool end()
    {
        if (!m_oldFun)return false;
        if (!m_isBegin)return true;    // û�п�ʼ�Ͳ�ִ�йرղ���,ֱ�ӷ�����

        if (MH_DisableHook(m_oldFun) != MH_OK)
            return false;
        m_isBegin = false;
        return true;
    }

    // ����ʼ��, ���ؼ����ʾδhook
    bool unHook()
    {
        if (!(m_oldFun)) return false;
        bool b = end();

        *m_ppOld = m_oldFun;    // ��ԭ����д��ȥ
        m_oldFun = 0;
        m_newFun = 0;
        m_isBegin = 0;
        m_ppOld = 0;

        if (MH_Uninitialize() != MH_OK)
            return false;

        return b;
    }

};

