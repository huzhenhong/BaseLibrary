#ifndef __LOGGERIMP_H__
#define __LOGGERIMP_H__

#include "BaseDefine.h"
#include "Util.h"


class LIBRARY_API CLoggerImp
{
public:
	static CLoggerImp& Instance()
	{
		static CLoggerImp instance;
		return instance;
	}

	void								SetLogLevel(LogLevel level);

	LogLevel							GetLogLevel();
	
	void								Write(const string& msg, LogLevel level);

private:
	CLoggerImp();
	~CLoggerImp();
	CLoggerImp(const CLoggerImp&) = delete;
	CLoggerImp(const CLoggerImp&&) = delete;
	CLoggerImp& operator=(const CLoggerImp&) = delete;
	CLoggerImp& operator=(const CLoggerImp&&) = delete;

private:
	fstream								m_fileStream;

	filesystem::path					m_logPath;

	LogLevel							m_level { LogLevel::LEVEL_DEBUG };

	int									m_maxFiles { 5 };

	deque<string>						m_backupFiles;

	deque<string>						m_messages;

	mutex								m_mtx;

	thread								m_workThread;

	bool								m_bRun { true };
};


#endif // !__LOGGERIMP_H__
