#pragma once

#include "DataTypes.hpp"
#include "UndefinedDataTypes.hpp"
#include "Task.hpp"
#include "Thread.hpp"

#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>
#include <vector>
#include <memory>


#define THRP_TASK					Strave::Uint16
#define THRP_TASK_LOCKED			true
#define THRP_TASK_COMPLETED			true
#define THRP_MAIN_THREAD			1
#define THRP_UNDEF_THREAD_STATE		ERROR_TYPE
#define THRP_UNDEF_THREAD_OWNER		ERROR_TYPE

#define THRP_GET_AVAILABLE_THREAD_NUMBER(_total)	_total - THRP_MAIN_THREAD


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

			Task _Task;
			state_t	Locked;
			state_t	Completed;
			Task::Priority _Priority;
			Int16 ThreadOwner;
		};

		struct ThreadPack
		{
			ThreadPack() = default;
			ThreadPack(const ThreadPack&) = delete;
			ThreadPack(Thread* thread, std::mutex* mutex);
			~ThreadPack();

			Thread* _Thread;
			std::mutex* TaskStateMutex;
			std::queue<EnqueuedTask*>* SelectedQueue;
		};

		struct TaskQueue
		{
			std::queue<EnqueuedTask*> GetwayQueue;
			std::queue<EnqueuedTask*> WorkerQueue;
		};

	public:
		ThreadPool(const ThreadPool& threadPool) = delete;

		static void Create(void);
		static /*Exception*/ int Delete(void);
		inline static ThreadPool* Get(void) { return m_ThreadPool; }
		static Int16 GetThreadStatus(const std::thread::id& threadID);
		static Uint16 Enqueue(Task::NoParam task);
		static void EnqueueParallel(Task::NoParam task);
		static void Mute(Task::NoParam& task);
		static void Lock(Uint16 task);
		static void Unlock(Uint16 task);
		static void Wait(Uint16 task);

		#define THRP_TASK_LOCK(_task) ThreadPool::Lock(_task)
		#define THRP_TASK_UNLOCK(_task) ThreadPool::Unlock(_task)
		#define THRP_TASK_WAIT(_task) ThreadPool::Wait(_task)
		#define THRP_TASK_START(_task) _task = ThreadPool::Enqueue([&]() {
		#define THRP_TASK_END })

	private:
		ThreadPool() = default;
		~ThreadPool() = default;

		void StartThreads(void);
		void ProceedTask(Uint16 thread, Thread::ThreadType& threadType); // Runtime function
		std::queue<EnqueuedTask*>& GetCorrectQueue(Thread::ThreadType& threadType);
		static std::queue<EnqueuedTask*>& GetCorrectQueue(EnqueuedTask& enqTask);

	private:
		static ThreadPool*							m_ThreadPool;

		std::vector<std::shared_ptr<ThreadPack>>	m_ThreadContainer;
		std::mutex									m_TaskQueueMutex;
		TaskQueue									m_TaskQueue;
	};
}