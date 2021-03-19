#include <StraveEngine/Entity/Object.hpp>


namespace Strave
{
	void Object::Destory(Object*& obj)
	{
		delete obj;
	}

	bool Object::Exists(const Object* obj)
	{
		return obj == UNDEF_PTR ? true : false;
	}
}
