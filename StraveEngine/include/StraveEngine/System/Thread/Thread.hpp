#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/Thread/Task.hpp>
#include <StraveEngine/Entity/Object.hpp>

#include <thread>


namespace Strave
{
	class STRAVE_SYSTEM_API Thread final : public Object
	{
	public:
		enum GameType
		{
			RenderThread = 0,
			LogicThread = 0,
			AudioThread = 0,
			NetworkThread
		};

		enum Type
		{
			Worker = 0,
			Getway
		};

		struct ThreadType
		{
			Thread::GameType _GameType;
			Thread::Type _Type;
		};

	public:	
		Thread(ThreadType threadType, std::string name = EMPTY_STR);
		Thread(ThreadType threadType, Task::NoParam noParamTask, std::string name = EMPTY_STR);
		Thread(Thread& thread) = delete;
		~Thread();

		inline state_t IsActive(void) { return m_State; }
		inline state_t GetState(void) { return m_State; }
		inline std::thread::id GetID(void) { return m_Thread->get_id(); }
		inline void SetState(state_t working) { m_State = working; }

	private:
		std::thread*	m_Thread;
		state_t			m_State;
		ThreadType		m_ThreadType;
	};
}

