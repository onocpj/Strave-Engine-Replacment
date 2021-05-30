#include <StraveEngine/System/Thread/ThreadPool.hpp>

#include <StraveEngine/System/Thread/Thread.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Application.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/MapContainer.cpp>

#include <string>


namespace Strave
{
	Uint16 ThreadPool::ThreadsInfo::Count = UNDEF_UINT16;
	Uint16 ThreadPool::ThreadsInfo::Working = UNDEF_UINT16;
	ThreadPool* ThreadPool::s_ThreadPool = UNDEF_PTR;

	////////////////////////////////////////////////////////////
	/// ThreadPool
	////////////////////////////////////////////////////////////
	void ThreadPool::Create(Uint16 threadCount)
	{
		ThreadPool::ThreadsInfo::Count = threadCount;

		ThreadPool::s_ThreadPool = new ThreadPool();
		ThreadPool::s_ThreadPool->StartThreads();
	}

	/*Exception*/ int ThreadPool::Delete(void)
	{
		// try
		// {
		// 	delete ThreadPool::m_ThreadPool;
		// 	ThreadPool::m_ThreadPool = nullptr;
		// }
		// catch (...)
		// {
		// 	return THROW__EXC_THRP_DEL;
		// }
		// 
		// return NO_EXCEPTION;

		return 0;
	}

	Int16 ThreadPool::GetThreadStatus(const std::thread::id& threadID)
	{
		typedef std::vector<std::shared_ptr<ThreadPack>>::iterator iter;
		for (iter thread = ThreadPool::Get()->m_ThreadContainer.begin(), end = ThreadPool::Get()->m_ThreadContainer.end(); thread != end; ++thread)
			if ((*thread)->_Thread->GetID() == threadID)
				return (Uint16)(*thread)->_Thread->GetState();
	
		return THRP_UNDEF_THREAD_STATE;
	}

	void ThreadPool::Mute(Task::NoParam& task)
	{
		std::mutex mutex;
		std::unique_lock<std::mutex> locker(mutex);

		task();

		locker.unlock();
	}

	Int16* ThreadPool::Enqueue(Task::NoParam task)
	{
		EnqueuedTask* enqTask = new EnqueuedTask{
			// THRP_KEY_UNASSIGNED,
			THRP_OWNER_UNASSIGNED,
			std::move(task),
			!THRP_TASK_LOCKED,
			// !THRP_TASK_COMPLETED,
			// Task::Priority::Low,
			// new std::mutex()
		};

		ThreadPool::Get()->m_TaskQueue.push_back(enqTask);

		return &enqTask->Owner; // should return thread key
	}

	void ThreadPool::EnqueueParallel(Task::NoParam task)
	{
		EnqueuedTask* enqTask = new EnqueuedTask{
			// THRP_KEY_UNASSIGNED,
			THRP_OWNER_UNASSIGNED,
			std::move(task),
			!THRP_TASK_LOCKED,
			// !THRP_TASK_COMPLETED,
			// Task::Priority::Low,
			// new std::mutex()
		};

		ThreadPool::Get()->m_TaskQueue.push_back(enqTask);
	}

	void ThreadPool::Lock(Int16* thread)
	{
		// auto predicate = THRP_PREDICATE(return (thread != nullptr && *thread >= 0));
		// while (!predicate()) {}
		// 
		// {
		// 	std::unique_lock<std::mutex> taskStateLock(*(ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->TaskStateMutex));
		// 	ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->Locked = THRP_TASK_LOCKED;
		// 	ThreadPool::Get()->m_ThreadContainer[*thread]->CV->wait(
		// 		taskStateLock,
		// 		THRP_PREDICATE(return !ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->Locked)
		// 	);
		// }
		// 
		// *thread = THRP_THREAD_FINISHED;

		return;
	}

	void ThreadPool::Unlock(Int16* thread)
	{
		// auto predicate = THRP_PREDICATE(return (thread != nullptr && *thread >= 0));
		// while (!predicate()) {}
		// 
		// {
		// 	std::unique_lock<std::mutex> taskStateLock(*(ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->TaskStateMutex));
		// 	ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->Locked = !THRP_TASK_LOCKED;
		// }
		// 
		// *thread = THRP_THREAD_FINISHED;

		return;
	}

	void ThreadPool::Join(Int16* thread)
	{
		// Optimalized version:
		//
		// wait till thread proceed task
		auto predicate = THRP_PREDICATE_START
			state_t result = false;		

			{
				// std::unique_lock<std::mutex> taskFinishedLock(ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolderCheckMutex);
				result = (thread != nullptr && *thread >= 0);
			}

			return result;

		THRP_PREDICATE_END
		while (!predicate()) {}
		
		{
			std::unique_lock<std::mutex> taskFinishedLock(ThreadPool::Get()->m_ThreadContainer[*thread]->ThreadJoinMutex);
			ThreadPool::Get()->m_ThreadContainer[*thread]->Joined = THRP_THREAD_JOINED;
		}

		*thread = THRP_THREAD_FINISHED;

		// Old version:
		// 
		// EnqueuedTask* taskToTerminate = UNDEF_PTR;
		// auto predicate = THRP_PREDICATE(return (thread != nullptr && *thread >= 0));
		// 
		// while (!predicate()) {}
		// 
		// {
		// 	std::unique_lock<std::mutex> taskStateLock(*(ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->TaskStateMutex));
		// 	ThreadPool::Get()->m_ThreadContainer[*thread]->CV->wait(
		// 		taskStateLock,
		// 		THRP_PREDICATE(return ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->Completed)
		// 	);
		// 
		// 	taskToTerminate = ThreadPool::Get()->m_TerminateTaskMap.GetElement((Uint64)ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->KEY);
		// 	ThreadPool::Get()->m_TerminateTaskMap.EraseFromContainer((Uint64)ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->KEY);
		// }
		// 
		// {
		// 	std::unique_lock<std::mutex> taskQueueLock(ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolderCheckMutex);
		// 	ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder = THRP_TASK_FINISHED;
		// 	*thread = THRP_THREAD_FINISHED;
		// }
		// 
		// delete taskToTerminate;	
		// taskToTerminate = nullptr;

		return;
	}

	void ThreadPool::StartThreads(void)
	{
		for (Uint16 index = 0; index < ThreadPool::ThreadsInfo::Count; index++)
		{
			auto threadWorker = std::move(
				LAMBDAV_START

					Uint16 threadID = index;
					state_t threadJoined = UNDEF_BOOL;

					while (true /* !StraveApplication->GetOnExitState() */) 
					{ 
						// Old version:
						//
						// {
						// 	std::unique_lock<std::mutex> taskFinishedLock(m_ThreadContainer[threadID]->TaskHolderCheckMutex);
						// 	threadFinishedTask = (m_ThreadContainer[threadID]->TaskHolder == THRP_TASK_FINISHED);
						// }
						// 
						// if (threadFinishedTask)
						//	ProceedTask(threadID);

						// Optimalized version:
						//
						{
							std::unique_lock<std::mutex> taskFinishedLock(m_ThreadContainer[threadID]->ThreadJoinMutex);
							threadJoined = m_ThreadContainer[threadID]->Joined;
						}

						if(threadJoined)
							ProceedTask(threadID);
					} 

				LAMBDA_END
			);

			Thread* thread = new Thread(threadWorker);
			ThreadPool::Get()->m_ThreadContainer.push_back(std::make_shared<ThreadPack>(thread));
		}
	}

	void ThreadPool::ProceedTask(Uint16 thread)
	{
		std::unique_lock<std::mutex> taskQueueLock(m_TaskQueueMutex);

		if (!m_TaskQueue.empty())
		{
			// Timer Timer("Proceeding task");

			{
				std::unique_lock<std::mutex> taskFinishedLock(m_ThreadContainer[thread]->ThreadJoinMutex);
				m_ThreadContainer[thread]->Joined = !THRP_THREAD_JOINED;
			}

			m_ThreadContainer[thread]->TaskHolder = m_TaskQueue.front();
			m_TaskQueue.pop_front();
			taskQueueLock.unlock();
			
			m_ThreadContainer[thread]->ExecutableTask = m_ThreadContainer[thread]->TaskHolder->_Task.Get();
			m_ThreadContainer[thread]->ExecutableTask();
			
			// Optimalized version:
			//
			{
				// inform about that task was completed
				std::unique_lock<std::mutex> taskFinishedLock(m_ThreadContainer[thread]->TaskHolderCheckMutex);
				m_ThreadContainer[thread]->TaskHolder->Owner = thread;

				// delete finished task
				delete m_ThreadContainer[thread]->TaskHolder;
				m_ThreadContainer[thread]->TaskHolder = THRP_TASK_FINISHED;
			}

			// Old version:
			//
			// {
			// 	std::unique_lock<std::mutex> taskStateLock(*(m_ThreadContainer[thread]->TaskHolder->TaskStateMutex));
			// 	m_ThreadContainer[thread]->TaskHolder->Completed = THRP_TASK_COMPLETED;
			// 	m_ThreadContainer[thread]->TaskHolder->Owner = thread;
			// 
			// 	m_ThreadContainer[thread]->TaskHolder->KEY = (Uint16)m_TerminateTaskMap.InsertToContainerRecycled(*m_ThreadContainer[thread]->TaskHolder); // !! Optimize, cant work like this.. !!
			// }
			
			// m_ThreadContainer[thread]->CV->notify_one();
		}
	}

	////////////////////////////////////////////////////////////
	/// EnqueuedTask
	////////////////////////////////////////////////////////////
	ThreadPool::EnqueuedTask::~EnqueuedTask()
	{
		// delete TaskStateMutex;
		// TaskStateMutex = nullptr;
	}

	////////////////////////////////////////////////////////////
	/// ThreadPack
	////////////////////////////////////////////////////////////
	ThreadPool::ThreadPack::ThreadPack(Thread* thread) :
		_Thread(thread),
		Joined(THRP_THREAD_JOINED),
		TaskHolder(THRP_EMPTY_TASK_HOLDER),
		ExecutableTask(THRP_EMPTY_EXC_TASK)
		// CV(new std::condition_variable())
	{}

	ThreadPool::ThreadPack::~ThreadPack()
	{
		delete _Thread;
		// delete CV;
	
		_Thread = nullptr;
		// CV = nullptr;
	}
}

