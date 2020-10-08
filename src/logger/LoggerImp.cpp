#include "LoggerImp.h"

CLoggerImp::CLoggerImp()
{
	auto logFileName = Util::GetModuleName() + "_" + std::to_string(Util::GetProcessId()) + ".log";

	filesystem::path logPath(Util::GetRunPath());

	m_logPath = logPath / logFileName;

	m_fileStream.open(m_logPath, std::ios::out | std::ios::trunc);

#ifdef Asynchronous
	thread workThread([&](){
		while (m_bRun)
		{
			while(m_messages.size() > 0)
			{
				lock_guard<mutex> guard(m_mtx);

				string msg(move(m_messages.front()));
				m_messages.pop_front();
				
				m_fileStream << msg;
				m_fileStream.flush();
			}
			
			Util::Sleep(10);
		}
	});

	m_workThread = move(workThread);
#endif
}

CLoggerImp::~CLoggerImp()
{
#ifdef Asynchronous
	m_bRun = false;

	if(m_workThread.joinable())
	{
		m_workThread.join();
	}
#endif

	m_fileStream.close();
}

void CLoggerImp::Write(const string& msg, LogLevel level)
{
	lock_guard<mutex> guard(m_mtx);

	if (level < m_level) { return; }

	m_fileStream.seekp(0, std::ios::end);
	auto size = m_fileStream.tellp();
	if (size > m_logFileSize)
	{
		m_fileStream.close();
		
		static int backupIdx = 0;
		++backupIdx;

		// 只保留最近的几个文件
		if (m_backupFiles.size() >= m_maxFiles)
		{
			// 删除最先备份的文件
			auto filename = m_backupFiles.front();
			std::remove(filename.data());
			m_backupFiles.pop_front();

			// 重命名备份文件
			for (auto& backupName : m_backupFiles)
			{
				auto logName = backupName.substr(0, backupName.rfind("."));	// 去掉后缀

				char idx = logName.back();
				logName.pop_back();
				--idx;
				logName.push_back(idx);
				auto newName = logName + ".log";

				std::rename(backupName.data(), newName.data());
			}

			--backupIdx;
		}

		// 备份当前文件
		auto logPathName = m_logPath.string();
		auto logName = logPathName.substr(0, logPathName.rfind("."));	// 去掉后缀
		auto backupName = logName + "_" + to_string(backupIdx) + ".log";
		std::rename(logPathName.data(), backupName.data());
		m_backupFiles.emplace_back(backupName);

		// 打开新的文件
		m_fileStream.open(m_logPath, std::ios::out | std::ios::trunc);
	}

		std::string levelMsg;

		if (LogLevel::LEVEL_DEBUG == level) { levelMsg = "[DEBUG]" + msg; }

		else if (LogLevel::LEVEL_TRACE == level) { levelMsg = "[TRACE]" + msg; }

		else if (LogLevel::LEVEL_WARNING == level) { levelMsg = "[WARNING]" + msg; }

		else if (LogLevel::LEVEL_ERROR == level) { levelMsg = "[ERROR]" + msg; }

		else if (LogLevel::LEVEL_FATAL == level) { levelMsg = "[FATAL]" + msg; }

#ifdef Asynchronous
		m_messages.emplace_back(std::move(levelMsg));
#else
		m_fileStream << levelMsg;
		m_fileStream.flush();
#endif

}
