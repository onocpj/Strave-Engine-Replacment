#include <StraveEngine/System/ICollectable.hpp>

#include <StraveEngine/System/GarbageCollector.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/System/ExceptionHandler.hpp>


namespace Strave
{
	////////////////////////////////////////////////////////////
	/// ICollectable
	////////////////////////////////////////////////////////////
	ICollectable::ICollectable()
	{
		ExceptionHandler::Handle(GarbageCollector::Insert(*this, this->m_KEY));
	}

	ICollectable::~ICollectable()
	{
		ExceptionHandler::Handle(GarbageCollector::Erase(this->m_KEY));
	}
}
