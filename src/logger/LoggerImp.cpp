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
	if (size > 1 * 1024 * 1024)
	{
		m_fileStream.close();
		
		static int backupIdx = 0;
		++backupIdx;

		// 备份当前文件
		auto oldName = m_logPath.string();
		auto newName = oldName + "_" + to_string(backupIdx);
		auto i = std::rename(oldName.data(), newName.data());
		m_backupFiles.emplace_back(newName);

		// 只保留最近的几个文件
		if (m_backupFiles.size() > m_maxFiles)
		{
			// 删除最先备份的文件
			auto filename = m_backupFiles.front();
			std::remove(filename.data());
			m_backupFiles.pop_front();

			// 重命名备份文件
			for (auto& filename : m_backupFiles)
			{
				auto backname = filename;
				char idx = filename.back();
				filename.pop_back();
				--idx;
				filename.push_back(idx);
				std::rename(backname.data(), filename.data());
			}

			--backupIdx;
		}

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
