#include "Sandbox.hpp"


namespace Sandbox
{
	GameObject* Object;
	GameObject* Object2;
	GameObject* Object3;

	Texture* ObjectTexture;
	Texture* GridTexture;
	AnimationTexture* ObjectAnimationTexture;

	Animation* ObjectAnimation;
	Animation* Object2Animation;

	Cell* CellPrefab;
	Grid* Inventory;

	float rotation = 0.0f;
	float movForward, movBackward, movLeft, movRight;

	// Function is called upon start
	void Game::OnStart(void) const
	{
		Object = new GameObject("Object");
		Object2 = new GameObject("Object2");
		Object3 = new GameObject("Object3");

		ObjectTexture = Texture::LoadTexture("D:\\Documents\\Strave Pictures\\texture_pack\\player", "Object texture");
		ObjectAnimationTexture = Texture::LoadTexture("D:\\Documents\\Strave Pictures\\animation_pack\\player_animation", "Object animation texture");
		GridTexture = Texture::LoadTexture("D:\\Documents\\Strave Pictures\\texture_pack\\inventory");

		Object->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);
		Object2->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);
		Object3->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);
		Object3->GetComponent<Transform>().SetPosition(Vector2f(50.0f, 50.0f));

		Animation::Constraints AnimationConstraints[] = {
			ANIMATION_CONSTRAINTS,
			{ 6, 0.20f },
			{ 6, 0.20f },
		};
		ObjectAnimation = new Animation(*ObjectAnimationTexture, 3, AnimationConstraints);
		Object2Animation = new Animation(*ObjectAnimation);

		Object->AddComponent<CharacterController>();
		Object->AssignComponent(Camera::GetCamera(MAIN_CAMERA));
		Object->AssignComponent<Animation>(*ObjectAnimation);
		Object2->AssignComponent<Animation>(*Object2Animation);

		movForward = Input::GetAxisDirection(Input::Direction::Up);
		movBackward = Input::GetAxisDirection(Input::Direction::Down);
		movLeft = Input::GetAxisDirection(Input::Direction::Left);
		movRight = Input::GetAxisDirection(Input::Direction::Right);

		CellPrefab = new Cell("Cell Prefab");
		CellPrefab->GetComponent<Mesh>().ApplyTexture(*GridTexture);

		Inventory = new Grid(*GridTexture, *CellPrefab, Vector2u(4, 4), "Inventory");
		Inventory->SetGridPosition(Vector2f(100.0f, 100.0f));
		Inventory->GetComponent<Transform>().SetScale(Vector2f(250.0f, 500.0f));

		CellPrefab->Hide();
	}

	// Function is called every frame
	void Game::OnUpdate(void) const
	{
		Object->GetComponent<CharacterController>().Move(Input::Axis::Vertical, movForward * EngineClocks::DeltaTime * 2.0f, Keyboard::Key::W);
		Object->GetComponent<CharacterController>().Move(Input::Axis::Vertical, movBackward * EngineClocks::DeltaTime * 2.0f, Keyboard::Key::S);
		Object->GetComponent<CharacterController>().Move(Input::Axis::Horizontal, movLeft * EngineClocks::DeltaTime * 2.0f, Keyboard::Key::A);
		Object->GetComponent<CharacterController>().Move(Input::Axis::Horizontal, movRight * EngineClocks::DeltaTime * 2.0f, Keyboard::Key::D);

		if (Keyboard::IsKeyPressed(Keyboard::Key::V))
		{
			if (!Object2->HaveAssignComponent<Camera>())
			{
				Object->UnassignComponent<Camera>();
				Object2->AssignComponent(Camera::GetCamera(MAIN_CAMERA));
			}
		}
		else
		{
			if (!Object->HaveAssignComponent<Camera>())
			{
				Object2->UnassignComponent<Camera>();
				Object->AssignComponent(Camera::GetCamera(MAIN_CAMERA));
			}
		}

		Object->GetComponent<Animation>().Animate(2);
		Object2->GetComponent<Animation>().Animate(1);
	}

	// Function is called upon exit
	void Game::OnEnd(void) const
	{
		
	}
}
