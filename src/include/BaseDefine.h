#ifndef __BASEDEFINE_H__
#define __BASEDEFINE_H__

#if (defined (WIN32) || defined (WIN64))
	#ifdef LIBRARY_EXPORT
		#define LIBRARY_API __declspec(dllexport)
	#else
		#define LIBRARY_API __declspec(dllimport)
	#endif // LIBRARY_EXPORT

#else // NOT define win32 or win64
	#define LIBRARY_API
#endif

#define EXTERN_C extern "C"


enum class LogLevel
{
	LEVEL_DEBUG,	// 调试，打印所有日志
	LEVEL_TRACE,	// 跟踪，打印需要持续跟踪的信息
	LEVEL_WARNING,	// 警告，未达预期
	LEVEL_ERROR,	// 错误，操作错误
	LEVEL_FATAL,	// 崩溃，程序产生致命性错误
};


#endif // !__BASEDEFINE_H__