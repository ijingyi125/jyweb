// pch.h: ����Ԥ�����ͷ�ļ���
// �·��г����ļ�������һ�Σ�����˽������ɵ��������ܡ�
// �⻹��Ӱ�� IntelliSense ���ܣ�����������ɺ�������������ܡ�
// ���ǣ�����˴��г����ļ��е��κ�һ��������֮���и��£�����ȫ�����������±��롣
// �����ڴ˴����ҪƵ�����µ��ļ����⽫ʹ������������Ч��

//#define __E_FNENAME jywke    // ���붨�������

#ifndef PCH_H
#define PCH_H
#pragma warning(disable:4786)// ZC: �����Ҫ���� "#include <map>"��ǰ��


#define DLLAPI
#ifdef DLLAPI
#undef DLLAPI
#define DLLAPI extern "C" __declspec(dllexport) 
#else
#define DLLAPI extern "C" __declspec(dllimport) 
#endif


// ���Ҫ�ڴ˴�Ԥ����ı�ͷ
#include "wke_typedef.h"








#endif //PCH_H
