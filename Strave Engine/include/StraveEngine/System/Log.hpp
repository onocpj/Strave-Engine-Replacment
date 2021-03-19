#pragma once

#include <StraveEngine/System/Logger.hpp>
#include <StraveEngine/System/Exception.hpp>

#include <memory>


namespace Strave 
{
	namespace svlog 
	{
		class Log abstract final
		{
		public:
			inline static void Init(std::string coreLoggerName, std::string clientLoggerName, logcol_t coreLoggerColors, logcol_t clientLoggerColors)
			{
				m_CoreLogger = new Logger(coreLoggerName, coreLoggerColors);
				m_ClientLogger = new Logger(clientLoggerName, clientLoggerColors);
			}

			inline static Logger& GetCoreLogger() { return *m_CoreLogger; }
			inline static Logger& GetClientLogger() { return *m_ClientLogger; }


			inline static Exception Delete(void)
			{
				try 
				{
					delete m_CoreLogger;
					delete m_ClientLogger;

					m_CoreLogger = nullptr;
					m_ClientLogger = nullptr;
				}
				catch (...)
				{
					return THROW__EXC_LOG_DEL;
				}
		
				return NO_EXCEPTION;
			}

		private:
			static Logger* m_CoreLogger;
			static Logger* m_ClientLogger;
		};
	}
}

#define CORE_LOGGER			::Strave::svlog::Log::GetCoreLogger()
#define CLIENT_LOGGER		::Strave::svlog::Log::GetClientLogger()

// Core Logger
#define SV_CORE_INFO(...)		APPLY_INFO_COLOR(CORE_LOGGER); (::Strave::svlog::Log::GetCoreLogger().*(::Strave::svlog::Log::GetCoreLogger().Info))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
#define SV_CORE_TRACE(...)		APPLY_TRACE_COLOR(CORE_LOGGER); (::Strave::svlog::Log::GetCoreLogger().*(::Strave::svlog::Log::GetCoreLogger().Trace))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
#define SV_CORE_WARN(...)		APPLY_WARN_COLOR(CORE_LOGGER); (::Strave::svlog::Log::GetCoreLogger().*(::Strave::svlog::Log::GetCoreLogger().Warn))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
#define SV_CORE_ERROR(...)		APPLY_ERROR_COLOR(CORE_LOGGER); (::Strave::svlog::Log::GetCoreLogger().*(::Strave::svlog::Log::GetCoreLogger().Error))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
#define SV_CORE_FATAL(...)		APPLY_FATAL_COLOR(CORE_LOGGER); (::Strave::svlog::Log::GetCoreLogger().*(::Strave::svlog::Log::GetCoreLogger().Fatal))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR

// Client Logger
#define SV_CLIENT_INFO(...)		APPLY_INFO_COLOR(CLIENT_LOGGER); (::Strave::svlog::Log::GetClientLogger().*(::Strave::svlog::Log::GetCoreLogger().Info))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
#define SV_CLIENT_TRACE(...)	APPLY_TRACE_COLOR(CLIENT_LOGGER); (::Strave::svlog::Log::GetClientLogger().*(::Strave::svlog::Log::GetCoreLogger().Trace))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
#define SV_CLIENT_WARN(...)		APPLY_WARN_COLOR(CLIENT_LOGGER); (::Strave::svlog::Log::GetClientLogger().*(::Strave::svlog::Log::GetCoreLogger().Warn))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
#define SV_CLIENT_ERROR(...)	APPLY_ERROR_COLOR(CLIENT_LOGGER); (::Strave::svlog::Log::GetClientLogger().*(::Strave::svlog::Log::GetCoreLogger().Error))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
#define SV_CLIENT_FATAL(...)	APPLY_FATAL_COLOR(CLIENT_LOGGER); (::Strave::svlog::Log::GetClientLogger().*(::Strave::svlog::Log::GetCoreLogger().Fatal))(__VA_ARGS__, NULL); UNAPPLY_LOG_COLOR
