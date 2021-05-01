#pragma once

#include <StraveEngine/System/Export.hpp>
#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/DataTypes.hpp>
#include <StraveEngine/UI/UserInterface.hpp>

#include <vector>
#include <string>


#define GRID_DEF_MARGINS	{ 85.0f, 85.0f }
#define GRID_NO_MARGINS		UNDEF_VECTOR2F


namespace Strave
{
	class Texture;
	class GameObject;
	class Cell;
	class Transforms;

	class STRAVE_UI_API Grid final : public UserInterface
	{
	public:
		Grid(std::string name = EMPTY_STR);
		Grid(Cell& cellPrefab, Vector2u dimensions, std::string name = EMPTY_STR);
		Grid(Texture& texture, Cell& cellPrefab, Vector2u dimensions, std::string name = EMPTY_STR);
		Grid(Grid& grid, std::string name = EMPTY_STR);
		~Grid() = default;

		inline UIType GetType(void) const override final { return UIType::Grid; };
		inline const Cell* GetCell(Uint32 index) const { return m_Cells.at(index); }
		const Cell* GetCell(Vector2u cellPosition) const;
		inline const GameObject* GetObject(const Cell& cell) const;
		inline const GameObject* GetObject(Uint32 index) const;
		void SetMargins(Vector2f margins);
		void SetGridPosition(Vector2f position);
		void SetGridSize(Vector2f size);
		void Show(void) override final;
		void Hide(void) override final;
		bool MouseDrag(void) override final;
		void Insert(const GameObject& object);
		void Insert(const GameObject& object, Uint32 cellIndex);
		void Insert(const GameObject& object, Vector2u cellPosition);
		void Erase(const GameObject& object);
		void Erase(Uint32 cellIndex);
		void Erase(const Vector2u cellPosition);

	private:
		void Init(void);
		void Init(Texture& texture);

		void Draw(void) const override final;
		void CreateCells(Vector2u dimensions, Vector2f position, Vector2f size);

	private:
		Vector2u			m_Dimensions;
		Vector2f			m_Margins;
		Cell*				m_CellPrefab;
		std::vector<Cell*>	m_Cells;
	};
}

