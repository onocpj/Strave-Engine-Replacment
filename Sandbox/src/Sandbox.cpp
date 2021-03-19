#include "Sandbox.hpp"


namespace Sandbox
{
	GameObject* Object;
	Texture* ObjectTexture;

	float rotation = 0.0f;

	float movForward, movBackward, movLeft, movRight;

	// Function is called upon start
	void Game::OnStart(void) const
	{
		Object = new GameObject("Object");
		ObjectTexture = Texture::LoadTexture("D:\\Documents\\Strave Pictures\\texture_pack\\player", "Object texture");
		Object->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);

		Object->AddComponent<CharacterController>();

		movForward = Input::GetAxisDirection(Input::Direction::Up);
		movBackward = Input::GetAxisDirection(Input::Direction::Down);
		movLeft = Input::GetAxisDirection(Input::Direction::Left);
		movRight = Input::GetAxisDirection(Input::Direction::Right);
	}

	// Function is called every frame
	void Game::OnUpdate(void) const
	{
		Object->GetComponent<Transform>().SetRotation(rotation+=0.1f);

		if (Keyboard::IsKeyPressed(Keyboard::Key::W))
			Object->GetComponent<CharacterController>().Move(Input::Axis::Vertical, movForward * EngineClocks::DeltaTime * 2.0f);
		if (Keyboard::IsKeyPressed(Keyboard::Key::S))
			Object->GetComponent<CharacterController>().Move(Input::Axis::Vertical, movBackward * EngineClocks::DeltaTime * 2.0f);
		if (Keyboard::IsKeyPressed(Keyboard::Key::A))
			Object->GetComponent<CharacterController>().Move(Input::Axis::Horizontal, movLeft * EngineClocks::DeltaTime * 2.0f);
		if (Keyboard::IsKeyPressed(Keyboard::Key::D))
			Object->GetComponent<CharacterController>().Move(Input::Axis::Horizontal, movRight * EngineClocks::DeltaTime * 2.0f);
	}

	// Function is called upon exit
	void Game::OnEnd(void) const
	{
		
	}
}
