#include "ThreadPool.hpp"
#include "Timer.hpp"

#include <iostream>
#include <string>


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

	Uint16 ThreadPool::Enqueue(Task::NoParam task)
	{
		EnqueuedTask* enqTask = new EnqueuedTask {
			std::move(task),
			!THRP_TASK_LOCKED,
			!THRP_TASK_COMPLETED,
			Task::Priority::Low,
			THRP_UNDEF_THREAD_OWNER
		};

		std::queue<ThreadPool::EnqueuedTask*>* selectedQueue = &GetCorrectQueue(*enqTask);
		selectedQueue->push(enqTask);

		return UNDEF_UINT16; // should return thread key
	}

	void ThreadPool::EnqueueParallel(Task::NoParam task)
	{
		EnqueuedTask* enqTask = new EnqueuedTask{
			std::move(task),
			!THRP_TASK_LOCKED,
			!THRP_TASK_COMPLETED,
			Task::Priority::Low,
			THRP_UNDEF_THREAD_OWNER
		};

		std::queue<ThreadPool::EnqueuedTask*>* selectedQueue = &GetCorrectQueue(*enqTask);
		selectedQueue->push(enqTask);
	}

	void ThreadPool::Mute(Task::NoParam& task)
	{
		std::mutex mutex;
		std::unique_lock<std::mutex> locker{ mutex };

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
		Thread::Type basicTypeBuffer;
		Thread::GameType gameTypeBuffer = Thread::GameType::RenderThread;
		Thread::ThreadType threadTypeBuffer;

		for (Uint16 index = 0; index < ThreadPool::Threads::Count; index++)
		{
			basicTypeBuffer = GetThreadType(ThreadPool::Threads::Count, index);
			gameTypeBuffer = GetThreadGameType(index);

			threadTypeBuffer = {
				gameTypeBuffer,
				basicTypeBuffer
			};

			auto threadWorker = std::move(
				LAMBDAV_START

					Uint16 threadKey = index;
					Thread::ThreadType threadType = threadTypeBuffer;
					while (true /* !StraveApplication->GetOnExitState() */) { ProceedTask(threadKey, threadType); } 

				LAMBDA_END
			);

			std::mutex* threadMutex = new std::mutex(); // each thread needs to have own mutex for task state
			Thread* thread = new Thread(threadTypeBuffer, threadWorker, Thread::ThreadType::ToString(threadTypeBuffer));
			ThreadPool::Get()->m_ThreadContainer.push_back(std::make_shared<ThreadPack>(thread, threadMutex)); 
		}
	}

	void ThreadPool::ProceedTask(Uint16 thread, Thread::ThreadType& threadType)
	{
		std::queue<ThreadPool::EnqueuedTask*>* selectedQueue = &GetCorrectQueue(threadType);
		std::unique_lock<std::mutex> taskQueueLock(m_TaskQueueMutex);

		if (!selectedQueue->empty())
		{
			Timer Timer("Proceeding task");

			EnqueuedTask* enqTask = selectedQueue->front();
			enqTask->ThreadOwner = thread;
			Task::NoParam task = std::move(enqTask->_Task.Get());

			selectedQueue->pop();
			taskQueueLock.unlock();

			// ThreadFlag threadRise(*this, m_ThreadContainer.at(index));	
			task();

			// Use thread mutex and change task state to completed
			std::unique_lock<std::mutex> taskStateLock(*(m_ThreadContainer[thread]->TaskStateMutex));
			enqTask->Completed = true;
			taskStateLock.unlock();

			delete enqTask;
			enqTask = nullptr;
		}
	}

	std::queue<ThreadPool::EnqueuedTask*>& ThreadPool::GetCorrectQueue(Thread::ThreadType& threadType)
	{
		if (threadType._Type == Thread::Type::Worker)
			if (!m_TaskQueue.WorkerQueue.empty())
				return m_TaskQueue.WorkerQueue;

		return m_TaskQueue.GetwayQueue;
	}

	std::queue<ThreadPool::EnqueuedTask*>& ThreadPool::GetCorrectQueue(EnqueuedTask& enqTask)
	{
		if (enqTask.Locked)
			return ThreadPool::Get()->m_TaskQueue.WorkerQueue;

		return ThreadPool::Get()->m_TaskQueue.GetwayQueue;
	}

	////////////////////////////////////////////////////////////
	/// ThreadPack
	////////////////////////////////////////////////////////////
	ThreadPool::ThreadPack::ThreadPack(Thread* thread, std::mutex* mutex) :
		_Thread(thread),
		TaskStateMutex(mutex),
		SelectedQueue(UNDEF_PTR)
	{}

	ThreadPool::ThreadPack::~ThreadPack()
	{
		delete TaskStateMutex;
		TaskStateMutex = nullptr;
	}

	////////////////////////////////////////////////////////////
	/// Functions
	////////////////////////////////////////////////////////////
	Uint16 ChooseOptimalGetwayNumber(Uint16 totalThreads)
	{
		Uint16 getwayCounter = UNDEF_INT16;

		// if total number of threads is more than 3
		if (totalThreads > 3)
		{
			// create more getways
			if (totalThreads % 2 != 0)
				getwayCounter++;

			for (Uint16 i = 2; i <= totalThreads; i++)
			{
				if (totalThreads % i == 0)
					getwayCounter++;
			}
		}
		else
			getwayCounter = 1; // else create only one getway

		return getwayCounter;
	}

	Thread::Type GetThreadType(Uint16 totalThreads, Uint16 currIterartion)
	{
		Uint16 getwayNumber = ChooseOptimalGetwayNumber(totalThreads);
		return currIterartion < (totalThreads - getwayNumber) ? Thread::Type::Worker : Thread::Type::Getway;
	}

	Thread::GameType GetThreadGameType(Uint16 currIterartion)
	{
		if(currIterartion <= 2)
			// we need to add 2 to current iteration because rendering thread is main thread, 
			// so we dont want to initialize any of the additional threads as rendering thread.
			// also we need to skip uninitialized thread type 
			//
			// +1 : for undefined thread
			// +1 : for rendering thread
			return static_cast<Thread::GameType>(currIterartion + 2);
		else
			return Thread::GameType::Undefined;
	}
}
