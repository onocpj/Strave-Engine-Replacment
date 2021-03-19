#pragma once

#include <StraveEngine/System/DataTypes.hpp>

#include <memory>
#include <queue>
#include <iostream>


#define EH_PRINTOUT_EXCEPTION(EXCEPTION) std::cout << "Exception [" << EXCEPTION.code << "] thrown: " << EXCEPTION.title << std::endl
#define EH_PRINTOU_FINAL(EXCEPTION_COUNT) std::cout << "STRAVE: thrown [" << EXCEPTION_COUNT << "] exceptions" << std::endl


namespace Strave
{
	struct Exception;
	class ExceptionHandler final
	{
	public:
		ExceptionHandler() = default;
		~ExceptionHandler() = default;;
		ExceptionHandler(const ExceptionHandler&) = delete;

		static void HandleQueue(void);
		static state_t Handle(const Exception& exception);
		static void Pass(const Exception& exception);

	private:
		static ExceptionHandler s_ExceptionCollector;
		static std::shared_ptr<std::queue<Exception>> s_ExceptionHandlerQueue;
	};
}

