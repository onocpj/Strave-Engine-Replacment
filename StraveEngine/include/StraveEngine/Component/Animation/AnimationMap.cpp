#include <StraveEngine/Component/Animation/AnimationMap.hpp>


namespace Strave
{
	template<Uint64 size> AnimationMap<size>::AnimationMap() :
		m_AnimationComposition(new Composition()[size])
	{}

	template<Uint64 size> AnimationMap<size>::~AnimationMap()
	{
		delete[] m_AnimationComposition;
	}
}
