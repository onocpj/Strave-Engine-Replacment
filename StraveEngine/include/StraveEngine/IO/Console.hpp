#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Log.hpp>

#include <iostream>


namespace Strave
{
	class STRAVE_IO_API Console abstract final
	{
	public:
		template<typename T> inline static void Print(T print) { std::cout << print << " "; }
		template<typename T> inline static void PrintLine(T print) { std::cout << print << std::endl; }
		template<typename T> inline static void PrintInfo(T info) { SV_CLIENT_INFO(info); }
		template<typename T> inline static void PrintWarn(T warn) { SV_CLIENT_WARN(warn); }
		template<typename T> inline static void PrintTrace(T trace) { SV_CLIENT_TRACE(trace); }
		template<typename T> inline static void PrintError(T error) { SV_CLIENT_ERROR(error); }
		template<typename T> inline static void PrintFatal(T fatal) { SV_CLIENT_FATAL(fatal); }
	};
}

