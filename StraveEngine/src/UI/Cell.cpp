#include <StraveEngine/UI/Cell.hpp>

#include <StraveEngine/Element/Texture.hpp>
#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/Entity/GameObject.hpp>
#include <StraveEngine/UI/UserInterface.hpp>
#include <StraveEngine/Component/Mesh.hpp>
#include <StraveEngine/Renderer/Renderer.hpp>


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
		this->GetComponent<Mesh>().ApplyTexture(texture);
	}

	Cell::Cell(Cell& cell, std::string name) :
		UserInterface(cell),
		m_ObjectHolder(new ObjectHolder(*this))
	{
		this->GetComponent<Mesh>().ApplyTexture(cell.GetComponent<Mesh>().GetTexture());
	}

	Cell::~Cell() 
	{ 
		delete m_ObjectHolder; 
	}

	void Cell::Draw() const 
	{
		Renderer::Draw(this->GetComponent<Mesh>());

		if (!this->IsEmpty())
			Renderer::Draw(m_ObjectHolder->GetComponent<Mesh>());
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
		Mesh& holderMesh = this->GetComponent<Mesh>();
		Transform& holderTransforms = this->GetComponent<Transform>();

		Transform& cellTransforms = cell.GetComponent<Transform>();
		Vector2f& cellPosition = cellTransforms.GetPosition();
		Vector2f& cellScale = cellTransforms.GetScale();

		Vector2f holderSize;
		Vector2f holderPosition;

		holderSize = cellScale * (CELL_DEF_MARGINS / 100.0f);
		holderPosition = {
			cellPosition.x + cellScale.x - holderSize.x,
			cellPosition.y + cellScale.y - holderSize.y,
		};

		holderMesh.ApplyTexture(const_cast<Texture&>(Texture::GetEmpty()));
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
		this->GetComponent<Mesh>().UpdateTexture(object.GetComponent<Mesh>().GetTexture());
	}

	void Cell::ObjectHolder::Release(void)
	{
		m_GameObject = UNDEF_PTR;
		this->GetComponent<Mesh>().UpdateTexture(Texture::GetEmpty());
	}
}
