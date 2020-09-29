#ifndef __UTIL_H__
#define __UTIL_H__

#include "BaseDefine.h"
#include "BaseInclude.h"

using namespace std;

namespace Util
{
	LIBRARY_API int								GetProcessId();							// ��ȡ��ǰ����ID

	LIBRARY_API int								GetThreadId();							// ��ȡ��ǰ�߳�ID

	LIBRARY_API string							GetCurrentPath();						// ��ǰ(�ļ�)·��

	LIBRARY_API string							GetRunPath();							// ����·��

	LIBRARY_API string							GetModulePathName();					// ��ǰģ��ȫ·��

	LIBRARY_API string							GetModuleName();						// ��ǰģ����

	LIBRARY_API string							GetCurrentSystemTime();					// ��ȡ��ǰϵͳʱ��

	LIBRARY_API bool							CreateDirectories(const string& dir);	// �ݹ鴴��Ŀ¼

	LIBRARY_API void							Split(const string& str, vector<string>& tokens, const string& delimiter = ";");

	LIBRARY_API bool							IsStrVecEqual(const vector<string>& left, const vector<string>& right);

	LIBRARY_API void							Sleep(int time);
}

#endif // !__UTIL_H__
