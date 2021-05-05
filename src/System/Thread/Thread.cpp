#include <StraveEngine/System/Thread/Thread.hpp>


namespace Strave
{
	Thread::Thread(ThreadType threadType, std::string name) :
		Object(name),
		m_Thread(new std::thread()),
		m_State(false),
		m_ThreadType(threadType)
	{}

	Thread::Thread(ThreadType threadType, Task::NoParam noParamTask, std::string name) :
		Object(name),
		m_Thread(new std::thread(std::move(noParamTask))),
		m_State(false),
		m_ThreadType(threadType)
	{}

	Thread::~Thread()
	{
		delete m_Thread;
	}
}
