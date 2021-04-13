#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/Element/IElement.hpp>


namespace Strave
{
	class STRAVE_ELEMENT_API ISprite abstract : public IElement
	{
	public:
		ISprite();
		ISprite(std::string name);
		~ISprite() = default;
		ISprite(const ISprite&) = default;

		virtual void* GetInstance(void) = 0;
	};
}
