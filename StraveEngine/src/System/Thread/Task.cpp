#include <StraveEngine/System/Thread/Task.hpp>


namespace Strave
{
	Task::Task(NoParam noParamTask) :
		m_NoParamTask(std::move(noParamTask))
	{}
}