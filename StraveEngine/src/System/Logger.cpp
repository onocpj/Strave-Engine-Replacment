#include <StraveEngine/System/Logger.hpp>

#include <cstdarg>


namespace Strave
{
	namespace svlog
	{
		Logger::Logger(std::string name, logcol_t colors) :
			Info(&Logger::Output),
			Trace(&Logger::Output),
			Warn(&Logger::Output),
			Error(&Logger::Output),
			Fatal(&Logger::Output),

			m_LogerName(name), 
			m_LoggerTime(GET_SYSTEM_CLOCKS), 
			m_LogColor(colors)
		{}

		Color Logger::GetProperColor(const Logger& logger, LogType log)
		{
			LogColor selectedLog = logger.m_LogColor;
			
			switch (log)
			{
			case LogType::Info: return static_cast<Color>(selectedLog.info);
			case LogType::Trace: return static_cast<Color>(selectedLog.trace);
			case LogType::Warn: return static_cast<Color>(selectedLog.warn);
			case LogType::Error: return static_cast<Color>(selectedLog.error);
			case LogType::Fatal: return static_cast<Color>(selectedLog.fatal);
			default: return Color::Unknown;
			}
		}

		void Logger::Output(const char* arg, ...)
		{
			m_LoggerTime = GET_SYSTEM_CLOCKS;
			std::time_t currentTime = GET_SYSTEM_TIME(m_LoggerTime);
		
			std::cout << "[" << std::ctime(&currentTime) << "] " << m_LogerName << ": ";
		
			va_list arguments;
			for (va_start(arguments, arg); arg != NULL; arg = va_arg(arguments, const char*))
				std::cout << arg << std::endl;
		
			va_end(arguments);
		}
	}
}
