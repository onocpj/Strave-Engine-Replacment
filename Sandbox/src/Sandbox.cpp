#include "Sandbox.hpp"


namespace Sandbox
{
	GameObject* Object;
	GameObject* Object2;
	GameObject* Object3;
	Texture* ObjectTexture;

	float rotation = 0.0f;
	float movForward, movBackward, movLeft, movRight;

	// Function is called upon start
	void Game::OnStart(void) const
	{
		Object = new GameObject("Object");
		Object2 = new GameObject("Object");
		Object3 = new GameObject("Object");
		ObjectTexture = Texture::LoadTexture("D:\\Documents\\Strave Pictures\\texture_pack\\player", "Object texture");
		Object->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);
		Object2->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);
		Object3->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);
		Object3->GetComponent<Transform>().SetPosition(Vector2f(50.0f, 50.0f));

		Object->AddComponent<CharacterController>();
		Object->AssignComponent(Camera::GetCamera(MAIN_CAMERA));

		movForward = Input::GetAxisDirection(Input::Direction::Up);
		movBackward = Input::GetAxisDirection(Input::Direction::Down);
		movLeft = Input::GetAxisDirection(Input::Direction::Left);
		movRight = Input::GetAxisDirection(Input::Direction::Right);
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
	}

	// Function is called upon exit
	void Game::OnEnd(void) const
	{
		
	}
}
