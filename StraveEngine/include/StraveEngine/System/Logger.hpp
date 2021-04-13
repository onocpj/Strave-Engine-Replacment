#pragma once

#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <Windows.h>


#define DEFAULT_CONSOLE_COLOR				15
#define SYSTEM_TIME							std::chrono::system_clock::time_point
#define GET_SYSTEM_CLOCKS					std::chrono::system_clock::now()
#define GET_SYSTEM_TIME(SYSTEM_CLOCKS)		std::chrono::system_clock::to_time_t(SYSTEM_CLOCKS)
#define GET_LOG_PROPER_COLOR(LOGGER, LOG)	Strave::svlog::Logger::GetProperColor(LOGGER, LOG)
#define SET_LOG_COLOR(COLOR)				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR)
#define UNAPPLY_LOG_COLOR					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DEFAULT_CONSOLE_COLOR)

#define APPLY_INFO_COLOR(LOGGER)	SET_LOG_COLOR(GET_LOG_PROPER_COLOR(LOGGER, ::Strave::svlog::LogType::Info))
#define APPLY_TRACE_COLOR(LOGGER)	SET_LOG_COLOR(GET_LOG_PROPER_COLOR(LOGGER, ::Strave::svlog::LogType::Trace))
#define APPLY_WARN_COLOR(LOGGER)	SET_LOG_COLOR(GET_LOG_PROPER_COLOR(LOGGER, ::Strave::svlog::LogType::Warn))
#define APPLY_ERROR_COLOR(LOGGER)	SET_LOG_COLOR(GET_LOG_PROPER_COLOR(LOGGER, ::Strave::svlog::LogType::Error))
#define APPLY_FATAL_COLOR(LOGGER)	SET_LOG_COLOR(GET_LOG_PROPER_COLOR(LOGGER, ::Strave::svlog::LogType::Fatal))


namespace Strave 
{
	namespace svlog 
	{
		enum Color 
		{
			Unknown = 0,
			Red = 4,
			Purple = 5,
			Gray = 8,
			Blue = 9,
			Green = 10,
			Pink = 13,
			Yellow = 14,
			White = 15,
			Default = 15
		};

		enum class LogType
		{
			Info = 0,
			Trace,
			Warn,
			Error,
			Fatal
		};

		struct LogColor
		{
			Uint16
				info, 
				trace,
				warn,
				error, 
				fatal;
		};

		class Logger;
		typedef LogColor logcol_t;
		template<typename Arg, typename... Args> using LogFunction = void(Logger::*)(Arg, Args...);

		class Logger final
		{
		public:
			Logger() = delete;
			Logger(std::string name, logcol_t colors);
			~Logger() = default;
			Logger(const Logger&) = delete;

		public:
			template<typename Arg, typename... Args> typename static LogFunction<Arg, Args...> InfoT;
			template<typename Arg, typename... Args> typename static LogFunction<Arg, Args...> TraceT;
			template<typename Arg, typename... Args> typename static LogFunction<Arg, Args...> WarnT;
			template<typename Arg, typename... Args> typename static LogFunction<Arg, Args...> ErrorT;
			template<typename Arg, typename... Args> typename static LogFunction<Arg, Args...> FatalT;
			void (Logger::*Info)(const char* arg, ...);
			void (Logger::*Trace)(const char* arg, ...);
			void (Logger::*Warn)(const char* arg, ...);
			void (Logger::*Error)(const char* arg, ...);
			void (Logger::*Fatal)(const char* arg, ...);

			static Color GetProperColor(const Logger& logger, LogType log);

		private:
			void Output(const char* arg, ...);

		private:
			std::string	m_LogerName;
			SYSTEM_TIME	m_LoggerTime;
			logcol_t	m_LogColor;
		};
	}
}

