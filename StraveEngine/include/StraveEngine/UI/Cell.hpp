#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/vector2.hpp>
#include <StraveEngine/UI/UserInterface.hpp>


#define CELL_DEF_MARGINS	85.0f


namespace Strave
{
	class GameObject;
	class Texture;

	class STRAVE_UI_API Cell final : public UserInterface
	{
	private:
		class ObjectHolder : public UserInterface
		{
		public:
			ObjectHolder(Cell& cell);
			ObjectHolder(ObjectHolder& objectHolder) = default;
			~ObjectHolder() = default;

			inline UIType GetType(void) const override final { return UIType::Undefined; };

			inline const GameObject* Peek(void) const { return m_GameObject; }
			void Hold(const GameObject& object);
			void Release(void);

		private:
			void Init(Cell& cell);

		private:
			const GameObject* m_GameObject;
		};

	public:
		Cell(std::string name = EMPTY_STR);
		Cell(const Vector2f& position, const Vector2f& spriteSize, std::string name = EMPTY_STR);
		Cell(Texture& texture, const Vector2f& position, const Vector2f& spriteSize, std::string name = EMPTY_STR);
		Cell(Cell& cell, std::string name = EMPTY_STR);
		~Cell();

		inline UIType GetType(void) const override final { return UIType::Cell; };
		inline void Show(void) override final;
		inline void Hide(void) override final;

		inline ObjectHolder* GetHolder(void) const {  return m_ObjectHolder; }
		inline const GameObject& GetObjectFromHolder(void) const { return *m_ObjectHolder->Peek(); }
		inline void Insert(const GameObject& object) const { m_ObjectHolder->Hold(object); }
		inline void Empty(void) const { m_ObjectHolder->Release(); }
		inline bool IsEmpty(void) const { return m_ObjectHolder->Peek() == UNDEF_PTR ? true : false; }

	private:
		void Draw(void) const override final;

	private:
		ObjectHolder* m_ObjectHolder;
	};
}
