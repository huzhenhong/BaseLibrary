#include "Util.h"

#ifndef __linux__
#pragma warning(disable: 4996)
#else

#endif

namespace Util
{
	int GetProcessId()
	{
#ifndef __linux__
		return GetCurrentProcessId();
#else
		return getpid();
#endif
	}

	int GetThreadId()
	{
#ifndef __linux__
		return GetCurrentThreadId();
#else
		return syscall(__NR_gettid);
#endif
	}

	string GetCurrentPath()	
	{
		return filesystem::current_path().string();
	}

	string GetRunPath()
	{
		char pFullPath[1000]{ 0 };
#ifndef __linux__
		if (0 == GetModuleFileName(NULL, pFullPath, 1000)) { return ""; }
#else
		if (!getcwd(pFullPath, 1000)) { return ""; }
#endif
		string str(pFullPath);
		
		auto index = str.find_last_of('\\');

		return str.substr(0, index);
	}

	string GetModulePathName()
	{
		char pFullPath[1000]{ 0 };
#ifndef __linux__
		if (0 == GetModuleFileName(NULL, pFullPath, 1000)) { return ""; }
#else
		if (!getcwd(pFullPath, 1000)) { return ""; }
#endif

		return string(pFullPath);
	}

	string GetModuleName()
	{
		char pFullPath[1000]{ 0 };
#ifndef __linux__
		if (0 == GetModuleFileName(NULL, pFullPath, 1000)) { return ""; }
#else
		if (!getcwd(pFullPath, 1000)) { return ""; }
#endif
		filesystem::path path(pFullPath);
		auto filename = path.filename();
		
		auto str = filename.string();
		return str;
	}

	string GetCurrentSystemTime()
	{
		auto now = chrono::system_clock::now();
		auto time = chrono::system_clock::to_time_t(now);

		auto milliSeconds = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
		auto msecs = milliSeconds % 1000;

		stringstream ss;
	
		ss << put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
		//ss << put_time(localtime(&time), "%c"); // 日期和时间中间有空格
		ss << "." << msecs;
		return ss.str();
	}

	bool CreateDirectories(const string& dir)
	{
		filesystem::path path(dir);

		if (filesystem::exists(path)) { return true; }

		return filesystem::create_directories(path);
	}

	void Split(string& str, vector<string>& tokens, string& delimiter)
	{
		string::size_type startPos = str.find_first_not_of(delimiter, 0);		// 从头开始找第一个非目标字符
		string::size_type splitPos = str.find_first_of(delimiter, startPos);	// 从第一个非目标字符开始找第一个目标字符

		while (startPos != string::npos || splitPos != string::npos)
		{
			tokens.push_back(str.substr(startPos, splitPos - startPos));		// 从第一个非目标字符截取到第一个目标字符
			startPos = str.find_first_not_of(delimiter, splitPos);
			splitPos = str.find_first_of(delimiter, startPos);
		}
	}

	bool IsStrVecEqual(const vector<string>& left, const vector<string>& right)
	{
		if (left.size() != right.size()) { return false; }

		size_t size = left.size();

		for (size_t i = 0; i < size; ++i)
		{
			if (left[i] != right[i]) { return false; }
		}

		return true;
	}
	void Sleep(int time)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}
}
