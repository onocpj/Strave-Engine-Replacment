#pragma once

#include <StraveEngine/System/DataTypes.hpp>

#include <functional>


#define LAMBDA(_body)		[](){ _body }
#define LAMBDA_R(_body)		[&](){ _body }
#define LAMBDA_V(_body)		[=](){ _body }


namespace Strave
{
	class Task final
	{
	public:
		typedef std::function<void(void)> NoParam;

		enum Priority
		{
			Low = 0,
			Medium,
			High
		};

	public:
		Task(NoParam noParamTask);
		Task(Task& task) = delete;
		~Task() = default;

		inline void Call(void) const { m_NoParamTask(); }
		inline NoParam Get(void) { return std::move(m_NoParamTask); }

	private:
		NoParam m_NoParamTask;
	};
}
