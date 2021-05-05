#pragma once

#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/Thread/Task.hpp>

#include <thread>
#include <atomic>
#include <mutex>
#include <queue>
#include <functional>


#define THRP_TASK					Strave::Uint16
#define THRP_TASK_LOCKED			true
#define THRP_TASK_COMPLETED			true
#define THRP_MAIN_THREAD			1
#define THRP_UNDEF_THREAD_STATE		ERROR_TYPE

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
			Task*			_Task;
			state_t			Locked;
			state_t			Completed;
			Task::Priority	_Priority;
		};

		struct TaskQueue
		{
			std::queue<EnqueuedTask*> MainQueue;
			std::queue<EnqueuedTask*> BasicQueue;
			std::queue<EnqueuedTask*> LockedQueue;
		};

	public:
		ThreadPool(ThreadPool& threadPool) = delete;

		static void Create(void);
		static Exception Delete(void);
		inline static ThreadPool& Get(void) { return *m_ThreadPool; }
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
		ThreadPool();
		~ThreadPool() = default;

		void StartThreads(void);
		void UpdateTaskQueue(void);

	private:
		static ThreadPool*			m_ThreadPool;

		std::vector<Thread*>		m_ThreadContainer;
		std::mutex					m_Mutex;
		TaskQueue					m_TaskQueue;
	};

	void TestFunction()
	{
		THRP_TASK taskA;
		THRP_TASK taskB;

		THRP_TASK_START(taskA)

			UpdateLogic();

		THRP_TASK_END;

		THRP_TASK_START(taskB)

			RenderScene();

			THRP_TASK_LOCK(taskB);
		THRP_TASK_END;

		THRP_TASK_WAIT(taskA);
		THRP_TASK_UNLOCK(taskB);
	}
}

