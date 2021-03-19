#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/ICollectable.hpp>

#include <string>


namespace Strave
{
	class STRAVE_ENTITY_API Object : public ICollectable
	{
	protected:
		Object() : ICollectable(), m_Name(EMPTY_STR) {};
		Object(std::string name) : ICollectable(), m_Name(name) {};
		virtual ~Object() = default;
		Object(const Object&) = default;

	public:
		inline virtual const std::string& ToString(void) const { return m_Name; }
		static void Destory(Object*& obj);
		static bool Exists(const Object* obj);

	private:
		std::string m_Name;
	};
}

