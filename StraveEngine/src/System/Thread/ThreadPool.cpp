#include <StraveEngine/System/Thread/ThreadPool.hpp>

#include <StraveEngine/System/Thread/Thread.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/Application.hpp>
#include <StraveEngine/System/Log.hpp>
#include <StraveEngine/System/MapContainer.cpp>


namespace Strave
{
	Uint16 ThreadPool::Threads::Count = THRP_GET_AVAILABLE_THREAD_NUMBER(std::thread::hardware_concurrency()) - THRP_MAIN_THREAD;
	Uint16 ThreadPool::Threads::Working = UNDEF_UINT16;
	ThreadPool* ThreadPool::m_ThreadPool;

	Uint16 ChooseOptimalGetwayNumber(Uint16 totalThreads);
	Thread::Type GetThreadType(Uint16 totalThreads, Uint16 currIterartion);
	Thread::GameType GetThreadGameType(Uint16 currIterartion);

	////////////////////////////////////////////////////////////
	/// ThreadPool
	////////////////////////////////////////////////////////////
	void ThreadPool::Create(void)
	{
		ThreadPool::m_ThreadPool = new ThreadPool();
		ThreadPool::m_ThreadPool->StartThreads();
	}

	Exception ThreadPool::Delete(void)
	{
		Uint16 freedUpThreadsNum = UNDEF_UINT16;
		ThreadPool* instance = ThreadPool::Get();

		if (instance != UNDEF_PTR)
		{
			try 
			{
				for (Uint16 index = 0; index != ThreadPool::Threads::Count; index++) 
				{
					if (instance->m_ThreadContainer.at(index)->Joinable()) 
					{
						instance->m_ThreadContainer.at(index)->Join();
						delete instance->m_ThreadContainer.at(index);
						instance->m_ThreadContainer.at(index) = nullptr;

						freedUpThreadsNum++;					
					}
				}

				if (freedUpThreadsNum == ThreadPool::Threads::Count)
				{
					delete ThreadPool::m_ThreadPool;
					ThreadPool::m_ThreadPool = nullptr;
				}
				else 
					throw Exception();

			}
			catch (...) 
			{
				return THROW__EXC_THRP_DEL;
			}
		}

		return NO_EXCEPTION;
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
			THRP_KEY_UNASSIGNED,
			THRP_OWNER_UNASSIGNED,
			std::move(task),
			!THRP_TASK_LOCKED,
			!THRP_TASK_COMPLETED,
			Task::Priority::Low,
			new std::mutex()
		};

		ThreadPool::Get()->m_TaskQueue.push_back(enqTask);

		return &enqTask->Owner; // should return thread key
	}

	void ThreadPool::EnqueueParallel(Task::NoParam task)
	{
		EnqueuedTask* enqTask = new EnqueuedTask{
			THRP_KEY_UNASSIGNED,
			THRP_OWNER_UNASSIGNED,
			std::move(task),
			!THRP_TASK_LOCKED,
			!THRP_TASK_COMPLETED,
			Task::Priority::Low,
			new std::mutex()
		};

		ThreadPool::Get()->m_TaskQueue.push_back(enqTask);
	}

	void ThreadPool::Lock(Int16* thread)
	{
		return;
	}

	void ThreadPool::Unlock(Int16* thread)
	{
		return;
	}

	void ThreadPool::Wait(Int16* thread)
	{
		// auto predicate = [&thread]() -> bool {
		// 	return (thread != nullptr && *thread >= 0);
		// };
		// 
		// while (!predicate())
		// {}

		{
			std::condition_variable threadProceededTask;
			std::mutex waitThread;

			std::unique_lock<std::mutex> taskProceededLock(waitThread);
			threadProceededTask.wait(
				taskProceededLock,
				THRP_PREDICATE(return (thread != nullptr && *thread >= 0))
			);
		}

		{
			std::unique_lock<std::mutex> taskStateLock(*(ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->TaskStateMutex));
			ThreadPool::Get()->m_ThreadContainer[*thread]->CV->wait(
				taskStateLock,
				THRP_PREDICATE(return ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->Completed)
			);
		}

		EnqueuedTask* taskToTerminate = ThreadPool::Get()->m_TerminateTaskMap.GetElement((Uint64)ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->KEY);
		ThreadPool::Get()->m_TerminateTaskMap.EraseFromContainer((Uint64)ThreadPool::Get()->m_ThreadContainer[*thread]->TaskHolder->KEY);

		delete taskToTerminate;
		taskToTerminate = nullptr;

		return;
	}

	void ThreadPool::StartThreads(void)
	{
		for (Uint16 index = 0; index < ThreadPool::Threads::Count; index++)
		{
			auto threadWorker = std::move(
				LAMBDAV_START

					Uint16 threadID = index;
					while (true /* !StraveApplication->GetOnExitState() */) { ProceedTask(threadID); }

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

			EnqueuedTask* enqTask = m_TaskQueue.front();
			m_ThreadContainer[thread]->TaskHolder = enqTask;
			m_ThreadContainer[thread]->ExecutableTask = enqTask->_Task.Get();
			m_TaskQueue.pop_front();

			taskQueueLock.unlock();
			m_ThreadContainer[thread]->ExecutableTask();

			{
				std::unique_lock<std::mutex> taskStateLock(*(enqTask->TaskStateMutex));
				enqTask->Completed = THRP_TASK_COMPLETED;
				enqTask->Owner = thread;

				enqTask->KEY = (Uint16)m_TerminateTaskMap.InsertToContainerRecycled(*enqTask);
			}

			m_ThreadContainer[thread]->CV->notify_one();
		}
	}

	////////////////////////////////////////////////////////////
	/// EnqueuedTask
	////////////////////////////////////////////////////////////
	ThreadPool::EnqueuedTask::~EnqueuedTask()
	{
		delete TaskStateMutex;
		TaskStateMutex = nullptr;
	}

	////////////////////////////////////////////////////////////
	/// EnqueuedTask
	////////////////////////////////////////////////////////////
	ThreadPool::ThreadPack::ThreadPack(Thread* thread) :
		_Thread(thread),
		TaskHolder(THRP_EMPTY_TASK_HOLDER),
		ExecutableTask(THRP_EMPTY_EXC_TASK),
		CV(new std::condition_variable())
	{}

	ThreadPool::ThreadPack::~ThreadPack()
	{
		delete CV;
		CV = nullptr;
	}
}
