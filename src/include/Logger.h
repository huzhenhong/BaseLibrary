#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "BaseDefine.h"
#include "Util.h"
#include "LoggerImp.h"

#define LOG_FUNCTION(msg, level)												\
{																				\
	stringstream ss;															\
																				\
    ss << "[" << Util::GetCurrentSystemTime() << "] "							\
		<< "[pid=" << Util::GetProcessId() << " "								\
		<< "tid=" << Util::GetThreadId() << "] "								\
		<< "[" /*<< __FILE__ << " " << __LINE__ << " "*/ << __FUNCTION__ << "] "\
		<< msg																	\
		<< "\n";																\
																				\
	CLoggerImp::Instance().Write(ss.str(), level);									\
}														


#define LOG_DEBUG(msg)			LOG_FUNCTION(msg, LogLevel::LEVEL_DEBUG)
#define LOG_TRACE(msg)			LOG_FUNCTION(msg, LogLevel::LEVEL_TRACE)
#define LOG_WARN(msg)			LOG_FUNCTION(msg, LogLevel::LEVEL_WARNING)
#define LOG_ERROR(msg)			LOG_FUNCTION(msg, LogLevel::LEVEL_ERROR)
#define LOG_FATAL(msg)			LOG_FUNCTION(msg, LogLevel::LEVEL_FATAL)

#define SET_LOG_LEVEL(level)	CLoggerImp::Instance().SetLogLevel(level)
#define GET_LOG_LEVEL()			CLoggerImp::Instance().GetLogLevel()

#endif // !__LOGGER_H__
