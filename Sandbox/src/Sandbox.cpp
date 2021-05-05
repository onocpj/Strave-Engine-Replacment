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
		// Test: Create game objects
		Object = new GameObject("Object");
		Object2 = new GameObject("Object2");
		Object3 = new GameObject("Object3");

		// Loading textures
		ObjectTexture = Texture::LoadTexture("D:\\Documents\\Strave Pictures\\texture_pack\\player");
		ObjectAnimationTexture = Texture::LoadTexture("D:\\Documents\\Strave Pictures\\animation_pack\\player_animation");
		GridTexture = Texture::LoadTexture("D:\\Documents\\Strave Pictures\\texture_pack\\inventory");

		// Using objects components
		Object->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);				// Applying texture for object mesh
		Object2->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);				// Applying texture for object mesh
		Object3->GetComponent<Mesh>().ApplyTexture(*ObjectTexture);				// Applying texture for object mesh
		Object3->GetComponent<Transform>().SetPosition(Vector2f(50.0f, 50.0f)); // Applying position for object

		// Creating animation map (animation texture map constraints)
		Animation::Constraints AnimationConstraints[] = {
			ANIMATION_CONSTRAINTS,	// animation 1
			{ 6, 0.20f },			// animation 2
			{ 6, 0.20f },			// animation 3
		};
		ObjectAnimation = new Animation(*ObjectAnimationTexture, 3, AnimationConstraints);  // Creating animation
		Object2Animation = new Animation(*ObjectAnimation);									// Copying existing animation

		// Assigning component for objects
		Object->AddComponent<CharacterController>();						// Assigning character controller for object (player)
		Object->AssignComponent<Camera>(Camera::GetCamera(MAIN_CAMERA));	// Assigning main camera to object (player)
		Object->AssignComponent<Animation>(*ObjectAnimation);				// Assigning created animations for object
		Object2->AssignComponent<Animation>(*Object2Animation);				// Assigning created animations for object

		// Getting input axis direction values for movement
		movForward = Input::GetAxisDirection(Input::Direction::Up);
		movBackward = Input::GetAxisDirection(Input::Direction::Down);
		movLeft = Input::GetAxisDirection(Input::Direction::Left);
		movRight = Input::GetAxisDirection(Input::Direction::Right);

		// Creating user interface
		CellPrefab = new Cell("Cell Prefab");
		CellPrefab->GetComponent<Image>().ApplyTexture(*GridTexture);

		Inventory = new Grid(*GridTexture, *CellPrefab, Vector2u(8, 4), "Inventory");
		Inventory->SetMargins(Vector2f(15.0f, 15.0f));
		Inventory->SetGridPosition(Vector2f(5.0f, 5.0f));
		Inventory->SetGridSize(Vector2f(250.0f, 500.0f));
	}

	// Function is called every frame
	void Game::OnUpdate(void) const
	{
		// Testing mouse events
		if (Mouse::DoubleClick(Mouse::Button::Left, *Object)) 
			Console::PrintLine("Object double clicked");

		if(Mouse::DoubleClick(Mouse::Button::Right)) 
			Console::PrintLine("Right mouse button clicked");

		if(Mouse::DoubleClick(Mouse::Button::Left, *Inventory))
			Inventory->MouseDrag();

		// Binding movement of player to keys
		Object->GetComponent<CharacterController>().Move(Input::Axis::Vertical, movForward * EngineClocks::DeltaTime * 2.0f, Keyboard::Key::W);
		Object->GetComponent<CharacterController>().Move(Input::Axis::Vertical, movBackward * EngineClocks::DeltaTime * 2.0f, Keyboard::Key::S);
		Object->GetComponent<CharacterController>().Move(Input::Axis::Horizontal, movLeft * EngineClocks::DeltaTime * 2.0f, Keyboard::Key::A);
		Object->GetComponent<CharacterController>().Move(Input::Axis::Horizontal, movRight * EngineClocks::DeltaTime * 2.0f, Keyboard::Key::D);

		// Testing switching camera on key press between two objects
		if (Keyboard::IsKeyPressed(Keyboard::Key::V))
			Camera::Switch(Camera::GetCamera(MAIN_CAMERA), *Object, *Object2);
		else
			Camera::Switch(Camera::GetCamera(MAIN_CAMERA), *Object2, *Object);

		// Testing object animations
		Object->GetComponent<Animation>().Animate(2);	// 2 means play second animation from animation map
		Object2->GetComponent<Animation>().Animate(1);	// 1 means play first animation from animation map
	}

	// Function is called upon exit
	void Game::OnEnd(void) const
	{
		
	}
}
