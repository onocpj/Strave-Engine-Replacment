#pragma once

#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/Thread/Task.hpp>
#include <StraveEngine/System/Thread/Thread.hpp>
#include <StraveEngine/System/MapContainer.hpp>

#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>


#define THRP_PREDICATE(_body)		([&thread]() -> bool { _body; })
#define THRP_TASK			Strave::Uint16
#define THRP_TASK_LOCKED		true
#define THRP_TASK_COMPLETED		true
#define THRP_MAIN_THREAD		1

#define THRP_UNDEF_THREAD_STATE		ERROR_TYPE
#define THRP_KEY_UNASSIGNED		ERROR_TYPE
#define THRP_OWNER_UNASSIGNED		ERROR_TYPE
#define THRP_EMPTY_TASK_HOLDER		UNDEF_PTR
#define THRP_EMPTY_EXC_TASK		UNDEF_PTR

#define THRP_GET_AVAILABLE_THREAD_NUMBER(_total) (_total - THRP_MAIN_THREAD)


namespace Strave
{
	class Thread;
	struct Exception;

	class ThreadPool final
	{
	public:
		struct Threads
		{
			static Uint16 Count;
			static Uint16 Working;
		};

		struct EnqueuedTask
		{
			EnqueuedTask() = default;
			~EnqueuedTask();

			Int16 KEY;					// identifier that is used to search for specific task in container
			Int16 Owner;					// thread that is owner of the task
			Task _Task;
			state_t	Locked;
			state_t	Completed;
			Task::Priority _Priority;
			std::mutex* TaskStateMutex;
		};

		struct ThreadPack
		{
			ThreadPack() = default;
			ThreadPack(Thread* thread);
			~ThreadPack();

			Thread* _Thread;
			EnqueuedTask* TaskHolder;
			Task::NoParam ExecutableTask;
			std::condition_variable* CV;
		};

	public:
		ThreadPool(const ThreadPool& threadPool) = delete;

		static void Create(void);
		static Exception Delete(void);
		inline static ThreadPool* Get(void) { return m_ThreadPool; }
		static Int16 GetThreadStatus(const std::thread::id& threadID);
		static void Mute(Task::NoParam& task);

		static Int16* Enqueue(Task::NoParam task);
		static void EnqueueParallel(Task::NoParam task);
		#define THRP_TASK_START(_thread) _thread = ThreadPool::Enqueue([&]() {
		#define THRP_TASK_END })

		static void Lock(Int16* thread);
		#define THRP_THREAD_LOCK(_thread) ThreadPool::Lock(_thread)

		static void Unlock(Int16* thread);
		#define THRP_THREAD_UNLOCK(_thread) ThreadPool::Unlock(_thread)

		static void Wait(Int16* thread);
		#define THRP_THREAD_WAIT(_thread) ThreadPool::Wait(_thread)

	private:
		ThreadPool() = default;
		~ThreadPool() = default;

		void StartThreads(void);
		void ProceedTask(Uint16 thread); // Runtime function

	private:
		static ThreadPool* m_ThreadPool;

		std::vector<std::shared_ptr<ThreadPack>>	m_ThreadContainer;
		std::mutex					m_TaskQueueMutex;
		std::deque<EnqueuedTask*>			m_TaskQueue;
		MapContainer<EnqueuedTask>			m_TerminateTaskMap;
	};
}

