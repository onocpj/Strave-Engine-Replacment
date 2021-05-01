#include <StraveEngine/UI/Grid.hpp>

#include <StraveEngine/System/UndefinedDataTypes.hpp>
#include <StraveEngine/System/Convert.hpp>
#include <StraveEngine/System/ExceptionHandler.hpp>
#include <StraveEngine/System/Exception.hpp>
#include <StraveEngine/UI/UserInterfaceContainer.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>
#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/Component/Transform.hpp>
#include <StraveEngine/Component/Image.hpp>
#include <StraveEngine/UI/Cell.hpp>
#include <StraveEngine/Utility/Matrix.hpp>


namespace Strave
{
	////////////////////////////////////////////////////////////
	/// Grid
	////////////////////////////////////////////////////////////
	Grid::Grid(std::string name) :
		UserInterface(name),
		m_Dimensions(UNDEF_VECTOR2U),
		m_Margins(GRID_NO_MARGINS),
		m_CellPrefab(UNDEF_PTR),
		m_Cells()
	{
		Init();
	}

	Grid::Grid(Cell& cellPrefab, Vector2u dimensions, std::string name) :
		UserInterface(name),
		m_Dimensions(dimensions),
		m_Margins(GRID_NO_MARGINS),
		m_CellPrefab(&cellPrefab),
		m_Cells()
	{
		Init();
	}

	Grid::Grid(Texture& texture, Cell& cellPrefab, Vector2u dimensions, std::string name) :
		UserInterface(name),
		m_Dimensions(dimensions),
		m_Margins(GRID_NO_MARGINS),
		m_CellPrefab(&cellPrefab),
		m_Cells()
	{
		Init(texture);
	}

	Grid::Grid(Grid& grid, std::string name) :
		UserInterface(grid),
		m_Dimensions(grid.m_Dimensions),
		m_Margins(grid.m_Margins),
		m_CellPrefab(grid.m_CellPrefab),
		m_Cells(grid.m_Cells)
	{
		Init(grid.GetComponent<Image>().GetTexture());
	}

	void Grid::Init(void)
	{
		ExceptionHandler::Handle(UserInterfaceContainer::Insert(*this, this->m_KEY));
		CreateCells(m_Dimensions, this->GetComponent<Transform>().GetPosition(), this->GetComponent<Image>().GetNativeSize());
	}

	void Grid::Init(Texture& texture)
	{
		this->GetComponent<Image>().ApplyTexture(texture);
		ExceptionHandler::Handle(UserInterfaceContainer::Insert(*this, this->m_KEY));
		CreateCells(m_Dimensions, this->GetComponent<Transform>().GetPosition(), this->GetComponent<Image>().GetNativeSize());
	}

	const Cell* Grid::GetCell(Vector2u position) const
	{
		return GetCell(Matrix::PositionToIndex(position));
	}

	const GameObject* Grid::GetObject(const Cell& cell) const
	{
		if (!cell.IsEmpty())
			return cell.GetObjectHolder()->Peek();

		return nullptr;
	}

	const GameObject* Grid::GetObject(Uint32 index) const
	{
		if (!m_Cells.at(index)->IsEmpty())
			return m_Cells.at(index)->GetObjectHolder()->Peek();

		return nullptr;
	}

	void Grid::SetMargins(const Vector2f margins) 
	{
		Uint32 rowCounter;
		Uint32 columnCounter;

		Vector2f snipSize;
		Vector2f cellSize;
		Vector2f tablePosition;
		Vector2f cellPosition;

		m_Margins = margins;
		rowCounter = UNDEF_UINT;
		columnCounter = UNDEF_UINT;

		// Value that represents table edge size for both axis
		// Those margins are times by two
		// This will ensure that there will be enough space for the side edges and upper and lower edges
		snipSize = {
			(2 * margins.x) / m_Dimensions.y,
			(2 * margins.y) / m_Dimensions.x
		};
		// Value represents size of the each cell
		// Value is set to the table size devided by number of cells in rows and columns, minus size of the added edges
		// This give us average size of cell to be able to fit this cells to table with edges
		cellSize = {
			this->GetComponent<Image>().GetNativeSize().x / m_Dimensions.y - snipSize.x,
			this->GetComponent<Image>().GetNativeSize().y / m_Dimensions.x - snipSize.y
		};
		// Value that represents position of the table
		// Value is base position of table plus edge size
		// This will ensure that cell will be put to table starting position, with left space for upper and side edge
		tablePosition = {
			this->GetComponent<Transform>().GetPosition().x + margins.x,
			this->GetComponent<Transform>().GetPosition().y + margins.y
		};
		// Value represents position of the first cell 
		cellPosition = {
			tablePosition.x,
			tablePosition.y
		};

		// Cycle whole container of cells
		typedef std::vector<Cell*>::iterator cellIter;
		for (cellIter cell = m_Cells.begin(); cell != m_Cells.end(); cell++)
		{
			// If column counter is less than number of final columns
			if (columnCounter < m_Dimensions.y) 
			{
				(*cell)->GetComponent<Transform>().SetPosition(cellPosition);	// Set position of iterator cell to new position
				(*cell)->GetComponent<Image>().SetNativeSize(cellSize);			// Set sprite size of this cell, to be able to fit cells in one row, with enough space for side edges

				// Set cell position to last cell position, plus size of one cell
				// This will ensure that next cell in row will be right next to the last one
				cellPosition.x += cellSize.x;

				columnCounter++; // Count nuumber of columns in one row
			}
			else // If you filled one row
			{ 
				columnCounter = UNDEF_UINT; 	// Reset value, that represents cells in one row
				cellPosition.x = tablePosition.x;	// Reset cell x axis position. So next row of cells can start again from edge of the table 
				cellPosition.y += cellSize.y;		// Set y axis cell position to last cell position plus cell y size. This will ensure that next row of cells will be right under the last one

				rowCounter++; // Count number of rows
				cell--; // When we jump to initializing next row of cells, no cell is iniintialized, but iterator is still counting. We need to uncount this iterator when we cycle each row
			}
		}
	}

	void Grid::SetGridPosition(Vector2f position) 
	{
		Uint32 rowCounter;
		Uint32 columnCounter;

		Vector2f tablePosition;
		Vector2f cellPosition;
		Vector2f cellSize;

		rowCounter = UNDEF_UINT;
		columnCounter = UNDEF_UINT;

		// Value that represents position of the table
		// Value is base position of table plus edge size
		// This will ensure that cell will be put to table starting position, with left space for upper and side edge
		tablePosition = {
			position.x + m_Margins.x,
			position.y + m_Margins.y
		};
		// Value represents position of the first cell 
		cellPosition = {
			tablePosition.x,
			tablePosition.y
		};
		// Value represents size of the each cell
		// Value is set to the cell size on x and y axis
		// Because each cell have same size, we are using size of the first cell from container as reference
		cellSize = {
			m_Cells.at(0)->GetComponent<Image>().GetNativeSize().x,
			m_Cells.at(0)->GetComponent<Image>().GetNativeSize().y
		};

		this->GetComponent<Transform>().SetPosition(position); // Sets position of table backround

		// Cycle whole cell container
		typedef std::vector<Cell*>::iterator cellIter;
		for (cellIter cell = m_Cells.begin(); cell != m_Cells.end(); cell++)
		{
			// If column counter is less than number of final columns
			if (columnCounter < m_Dimensions.y) 
			{
				(*cell)->GetComponent<Transform>().SetPosition(Vector2f(cellPosition.x, cellPosition.y));	// Set position of cell to the new position

				auto element = *(*cell)->GetObjectHolder();

				element.GetComponent<Transform>().SetPosition(Vector2f(										// Set position of elements
					cellPosition.x + cellSize.x - element.GetComponent<Image>().GetNativeSize().x,
					cellPosition.y + cellSize.y - element.GetComponent<Image>().GetNativeSize().y
				));																					

				// Set cell position to last cell position, plus size of one cell
				// This will ensure that next cell in row will be right next to the last one
				cellPosition.x += cellSize.x;

				columnCounter++; // Count nuumber of columns in one row
			}
			else // If you filled one row
			{ 
				columnCounter = UNDEF_UINT;		// Reset value, that represents cells in one row
				cellPosition.x = tablePosition.x;	// Reset cell x axis position. So next row of cells can start again from edge of the table 
				cellPosition.y += cellSize.y;		// Set y axis cell position to last cell position plus cell y size. This will ensure that next row of cells will be right under the last one

				rowCounter++; // Count number of rows
				cell--; // When we jump to initializing next row of cells no cell is iniintialized, but iterator is still counting. We need to uncount this iterator when we cycle each row
			}
		}
	}

	void Grid::SetGridSize(Vector2f size)
	{
		Uint32 rowCounter;
		Uint32 columnCounter;

		Vector2f tablePosition;
		Vector2f cellPosition;
		Vector2f snipSize;
		Vector2f cellSize;

		rowCounter = UNDEF_UINT;
		columnCounter = UNDEF_UINT;

		this->GetComponent<Image>().SetNativeSize(size);

		// Value that represents position of the table
		// Value is base position of table plus edge size
		// This will ensure that cell will be put to table starting position, with left space for upper and side edge
		tablePosition = {
			this->GetComponent<Transform>().GetPosition().x + m_Margins.x,
			this->GetComponent<Transform>().GetPosition().y + m_Margins.y
		};
		// Value represents position of the first cell 
		cellPosition = {
			tablePosition.x,
			tablePosition.y
		};
		// Value that represents table edge size for both axis
		// Those margins are times by two
		// This will ensure that there will be enough space for the side edges and upper and lower edges
		snipSize = {
			(2 * m_Margins.x) / m_Dimensions.y,
			(2 * m_Margins.y) / m_Dimensions.x
		};
		// Value represents size of the each cell
		// Value is set to the table size devided by number of cells in rows and columns
		// This give us average size of cell to be able to fit this cells to table
		cellSize = {
			(size.x / m_Dimensions.y) - snipSize.x,
			(size.y / m_Dimensions.x) - snipSize.y
		};

		// Cycle whole cell container
		typedef std::vector<Cell*>::iterator cellIter;
		for (cellIter cell = m_Cells.begin(); cell != m_Cells.end(); cell++)
		{
			// If column counter is less than number of final columns
			if (columnCounter < m_Dimensions.y)
			{
				(*cell)->GetComponent<Transform>().SetPosition(cellPosition);						// Set position of cell to the new position
				(*cell)->GetComponent<Image>().SetNativeSize(cellSize);						

				auto element = *(*cell)->GetObjectHolder();

				element.GetComponent<Transform>().SetPosition(Vector2f(								// Set position of elements
					cellPosition.x + cellSize.x - element.GetComponent<Image>().GetNativeSize().x,
					cellPosition.y + cellSize.y - element.GetComponent<Image>().GetNativeSize().y
				));
				element.GetComponent<Image>().SetNativeSize(Vector2f(
					cellSize.x,
					cellSize.y
				));

				// Set cell position to last cell position, plus size of one cell
				// This will ensure that next cell in row will be right next to the last one
				cellPosition.x += cellSize.x;

				columnCounter++; // Count nuumber of columns in one row
			}
			else // If you filled one row
			{
				columnCounter = UNDEF_UINT;		// Reset value, that represents cells in one row
				cellPosition.x = tablePosition.x;	// Reset cell x axis position. So next row of cells can start again from edge of the table 
				cellPosition.y += cellSize.y;		// Set y axis cell position to last cell position plus cell y size. This will ensure that next row of cells will be right under the last one

				rowCounter++; // Count number of rows
				cell--; // When we jump to initializing next row of cells no cell is iniintialized, but iterator is still counting. We need to uncount this iterator when we cycle each row
			}
		}
	}

	void Grid::Show(void)
	{
		if (m_ShowState == false)
		{
			m_ShowState = true;

			typedef std::vector<Cell*>::iterator cellIter;
			for (cellIter cell = m_Cells.begin(), end = m_Cells.end();
				cell != end;
				++cell)
			{
				(*cell)->Show();
			}
		}
	}

	void Grid::Hide(void)
	{
		if (m_ShowState == true)
		{
			m_ShowState = false;

			typedef std::vector<Cell*>::iterator cellIter;
			for (cellIter cell = m_Cells.begin(), end = m_Cells.end();
				cell != end;
				++cell)
			{
				(*cell)->Hide();
			}
		}
	}

	bool Grid::MouseDrag(void)
	{
		if (m_ShowState == true)
		{
			bool dragable = Mouse::Drag(*this);

			if (dragable)
			{
				this->SetGridPosition(this->GetComponent<Transform>().GetPosition());
				return dragable;
			}
		}

		return false;
	}

	void Grid::Insert(const GameObject& object) 
	{
		typedef std::vector<Cell*>::iterator cellIter;
		for (cellIter cell = m_Cells.begin(), end = m_Cells.end(); cell != end; ++cell)
		{
			if ((*cell)->IsEmpty()) 
			{
				(*cell)->Insert(object);
				return;
			}
		}
	}

	void Grid::Insert(const GameObject& object, Uint32 index)
	{
		m_Cells.at((size_t)index)->Insert(object);
	}

	void Grid::Insert(const GameObject& object, Vector2u cellPosition)
	{
		m_Cells.at((size_t)Matrix::PositionToIndex(cellPosition))->Insert(object);
	}

	void Grid::Erase(const GameObject& object) 
	{
		// Need optimalization: remove element at specific index and dont iterate through whole table !!!
		typedef std::vector<Cell*>::iterator cellIter;
		for (cellIter cell = m_Cells.begin(), end = m_Cells.end(); cell != end; ++cell)
		{
			if (!(*cell)->IsEmpty()) 
			{
				if ((*cell)->GetObjectHolder()->Peek() == &object) 
				{
					(*cell)->Empty();
					return;
				}
			}
		}
	}

	void Grid::Erase(const Vector2u cellPosition)
	{
		Uint32 position = Matrix::PositionToIndex(cellPosition);

		if(position < m_Cells.size())
			m_Cells.at((size_t)position)->Empty();
	}

	void Grid::Erase(Uint32 index)
	{
		if (index < m_Cells.size()) 
			m_Cells.at((size_t)index)->Empty();
	}

	void Grid::Draw(void) const 
	{
		Renderer::Draw(this->GetComponent<Image>());

		typedef std::vector<Cell*>::iterator cellIter;
		typedef std::vector<Cell*> cells;

		for (cellIter cell = const_cast<cells&>(m_Cells).begin(), end = const_cast<cells&>(m_Cells).end(); cell != end; ++cell)
		{
			Renderer::Draw((*cell)->GetComponent<Image>());

			if (!(*cell)->IsEmpty())
				Renderer::Draw((*cell)->GetObjectHolder()->GetComponent<Image>());
		}
	}

	void Grid::CreateCells(Vector2u dimensions, Vector2f position, Vector2f size)
	{
		Uint32 rowCounter;
		Uint32 columnCounter;

		Vector2f cellPosition;
		Vector2f cellSize;

		rowCounter = UNDEF_UINT;
		columnCounter = UNDEF_UINT;

		// Value represents position of the first cell 
		cellPosition = {
			position.x,
			position.y
		};
		// Value represents size of the each cell
		// Value is set to the table size devided by number of cells in rows and columns
		// This give us average size of cell to be able to fit this cells to table
		cellSize = {
			(size.x / dimensions.y),
			(size.y / dimensions.x)
		};

		// Use cell prefab as init cell of grid, set its position, scale and so on
		m_Cells.push_back(m_CellPrefab);
		m_Cells[0]->GetComponent<Transform>().SetPosition(Vector2f(cellPosition.x, cellPosition.y));
		m_Cells[0]->GetComponent<Image>().SetNativeSize(Vector2f(cellSize.x, cellSize.y));

		cellPosition.x += cellSize.x;

		// Cycle to initialize each cell
		for (Uint32 i = 1; i != (dimensions.x * dimensions.y); i++)
		{
			// If column counter is less than number of final columns
			if (columnCounter < dimensions.y)
			{
				// Create new cell and push it to the container
				m_Cells.push_back(new Cell(*m_CellPrefab));
				m_Cells[i]->SetName("Cell" + std::to_string(i + 2));

				m_Cells[i]->GetComponent<Transform>().SetPosition(Vector2f(cellPosition.x, cellPosition.y));
				m_Cells[i]->GetComponent<Image>().SetNativeSize(Vector2f(cellSize.x, cellSize.y));

				// Set cell position to last cell position, plus size of one cell
				// This will ensure that next cell in row will be right next to the last one
				cellPosition.x += cellSize.x;

				columnCounter++; // Count nuumber of columns in one row
			}
			else // If you filled one row
			{
				columnCounter = UNDEF_UINT;		// Reset value, that represents cells in one row
				cellPosition.x = position.x;	// Reset cell x axis position. So next row of cells can start again from edge of the table 
				cellPosition.y += cellSize.y;	// Set y axis cell position to last cell position plus cell y size. This will ensure that next row of cells will be right under the last one

				rowCounter++;	// Count number of rows
				i--;			// When we jump to initializing next row of cells, no cell is iniintialized, but iterator is still counting. We need to uncount this iterator when we cycle each row
			}
		}
	}
}
