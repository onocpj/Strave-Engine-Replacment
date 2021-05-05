#include <StraveEngine/UI/Cell.hpp>

#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/UI/UserInterface.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>
#include <StraveEngine/Component/Image.hpp>


namespace Strave
{
	////////////////////////////////////////////////////////////
	/// Cell
	////////////////////////////////////////////////////////////
	Cell::Cell(std::string name) :
		UserInterface(name),
		m_ObjectHolder(new ObjectHolder(*this))
	{}

	Cell::Cell(const Vector2f& position, const Vector2f& spriteSize, std::string name) :
		UserInterface(name),
		m_ObjectHolder(new ObjectHolder(*this))
	{}

	Cell::Cell(Texture& texture, const Vector2f& position, const Vector2f& spriteSize, std::string name) :
		UserInterface(name),
		m_ObjectHolder(new ObjectHolder(*this))
	{
		this->GetComponent<Image>().ApplyTexture(texture);
	}

	Cell::Cell(Cell& cell, std::string name) :
		UserInterface(cell),
		m_ObjectHolder(new ObjectHolder(*this))
	{
		this->GetComponent<Image>().ApplyTexture(cell.GetComponent<Image>().GetTexture());
	}

	Cell::~Cell() 
	{ 
		delete m_ObjectHolder; 
	}

	void Cell::Draw() const 
	{
		Renderer::Draw(this->GetComponent<Image>());

		if (!this->IsEmpty())
			Renderer::Draw(m_ObjectHolder->GetComponent<Image>());
	}

	////////////////////////////////////////////////////////////
	/// ObjectHolder
	////////////////////////////////////////////////////////////
	Cell::ObjectHolder::ObjectHolder(Cell& cell) :
		UserInterface(),
		m_GameObject(UNDEF_PTR)
	{
		Init(cell);
	}

	void Cell::ObjectHolder::Init(Cell& cell)
	{
		Image& holderImage = this->GetComponent<Image>();
		Transform& holderTransforms = this->GetComponent<Transform>();

		Transform& cellTransforms = cell.GetComponent<Transform>();
		Vector2f& cellPosition = cellTransforms.GetPosition();
		Vector2f cellSize = cell.GetComponent<Image>().GetNativeSize();

		Vector2f holderSize;
		Vector2f holderPosition;

		holderSize = cellSize * (CELL_DEF_MARGINS / 100.0f);
		holderPosition = {
			cellPosition.x + cellSize.x - holderSize.x,
			cellPosition.y + cellSize.y - holderSize.y,
		};

		holderImage.ApplyTexture(const_cast<Texture&>(Texture::GetEmpty()));
		holderTransforms.SetScale(holderSize);
		holderTransforms.SetPosition(holderPosition);
	}

	inline void Cell::Show(void) 
	{
		m_ShowState = true;
		m_ObjectHolder->Show();
	}

	inline void Cell::Hide(void)
	{
		m_ShowState = false;
		m_ObjectHolder->Hide();
	}

	void Cell::ObjectHolder::Hold(const GameObject& object) 
	{
		m_GameObject = &object;
		this->GetComponent<Image>().UpdateTexture(object.GetComponent<Mesh>().GetTexture());
	}

	void Cell::ObjectHolder::Release(void)
	{
		m_GameObject = UNDEF_PTR;
		this->GetComponent<Image>().UpdateTexture(Texture::GetEmpty());
	}
}
