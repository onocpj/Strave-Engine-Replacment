#include <StraveEngine/System/ExceptionHandler.hpp>

#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Log.hpp>


namespace Strave
{
	ExceptionHandler ExceptionHandler::s_ExceptionCollector;
	std::shared_ptr<std::queue<Exception>> ExceptionHandler::s_ExceptionHandlerQueue = std::make_shared<std::queue<Exception>>();

		void ExceptionHandler::HandleQueue(void)
	{
		Uint16 exceptionCounter = 0;

		while (!ExceptionHandler::s_ExceptionHandlerQueue->empty())
		{
			Exception& exception = ExceptionHandler::s_ExceptionHandlerQueue->front();
			
			if (Handle(exception))
				exceptionCounter++;
			
			ExceptionHandler::s_ExceptionHandlerQueue->pop();
		}

		EH_PRINTOU_FINAL(exceptionCounter);
	}

	state_t ExceptionHandler::Handle(const Exception& exception)
	{
		if (exception.code != EXC_CODE_0) {
			EH_PRINTOUT_EXCEPTION(exception);
			return 1;
		}
		
		return 0;
	}

	void ExceptionHandler::Pass(const Exception& result)
	{
		ExceptionHandler::s_ExceptionHandlerQueue->push(result);
	}
}
