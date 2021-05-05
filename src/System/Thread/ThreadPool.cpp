#include <StraveEngine/System/Thread/ThreadPool.hpp>

#include <StraveEngine/System/Thread/Thread.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Application.hpp>


namespace Strave
{
	Uint16 ThreadPool::Threads::Count = THRP_GET_AVAILABLE_THREAD_NUMBER(std::thread::hardware_concurrency());
	Uint16 ThreadPool::Threads::Working = UNDEF_UINT16;
	ThreadPool* ThreadPool::m_ThreadPool;

	////////////////////////////////////////////////////////////
	/// ThreadPool
	////////////////////////////////////////////////////////////
	ThreadPool::ThreadPool()
	{
		StartThreads();
	}

	void ThreadPool::Create(void)
	{
		ThreadPool::m_ThreadPool = new ThreadPool();
	}

	Exception ThreadPool::Delete(void)
	{
		try
		{
			delete ThreadPool::m_ThreadPool;
			ThreadPool::m_ThreadPool = nullptr;
		}
		catch (...)
		{
			return THROW__EXC_THRP_DEL;
		}

		return NO_EXCEPTION;
	}

	Int16 ThreadPool::GetThreadStatus(const std::thread::id& threadID)
	{
		for (Thread* thread : ThreadPool::Get().m_ThreadContainer)
			if (thread->GetID() == threadID)
				thread->GetState();

		return THRP_UNDEF_THREAD_STATE;
	}

	Uint16 ThreadPool::Enqueue(Task::NoParam task)
	{
		EnqueuedTask enqTask = {
			new Task(std::move(task)),
			!THRP_TASK_LOCKED,
			!THRP_TASK_COMPLETED,
			Task::Priority::Low
		};

		ThreadPool::Get().m_TaskQueue.MainQueue.push(&enqTask);
	}

	void ThreadPool::EnqueueParallel(Task::NoParam task)
	{
		EnqueuedTask enqTask = {
			new Task(std::move(task)),
			!THRP_TASK_LOCKED,
			!THRP_TASK_COMPLETED,
			Task::Priority::Low
		};

		ThreadPool::Get().m_TaskQueue.MainQueue.push(&enqTask);
	}

	void ThreadPool::Mute(Task::NoParam& task)
	{
		std::mutex mutex;
		std::unique_lock<std::mutex> locker { mutex };

		task();

		locker.unlock();
	}

	void ThreadPool::Lock(Uint16 thread)
	{
		return;
	}

	void ThreadPool::Unlock(Uint16 thread)
	{
		return;
	}

	void ThreadPool::Wait(Uint16 thread)
	{
		return;
	}

	void ThreadPool::StartThreads(void)
	{
		for (Uint16 index = 0; index <= ThreadPool::Threads::Count; index++)
		{	
			auto initThread = LAMBDA(
				// while application exit state is not invoked
				while (!StraveApplication->GetOnExitState())
				{
					// make sure mutex is locked to ensure that multiple threads will not access 
					// container of tasks at the same time and pick the same task
					std::unique_lock<std::mutex> locker{ m_Mutex };

					// check if there is any task in queue in container
					if (!ThreadPool::Get().m_TaskQueue.empty())
					{
						Task::NoParam task;
						task = std::move(ThreadPool::Get().m_TaskQueue.front());		// if there is any task in queue, pick this task

						ThreadPool::Get().m_TaskQueue.pop();							// remove task from container so other threads will not be able to pick up the same task
						locker.unlock();												// unlock task container for other threads

						ThreadFlag t_ThreadRise(*this, m_ThreadContainer.at(index));	// rise flag that represents: new thread from thread pool is active
						task();															// start task
					}
				}
			);

			Thread* thread = new Thread(std::move(initThread));
			ThreadPool::Get().m_ThreadContainer.push_back(thread); // move thread instance to the thread container
		}
	}

	void ThreadPool::UpdateTaskQueue(void)
	{
			
	}
}
