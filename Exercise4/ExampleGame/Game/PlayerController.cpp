#include "PlayerController.h"
#include "Engine/MyEngine.h"

namespace ExampleGame {
	void PlayerController::Init() {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		glm::vec2 basePos = engine->GetScreenSize() / 2.f;
		MyEngine::GameObject* parent = GetGameObject();
		parent->position += basePos;
	}

	void PlayerController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		//glm::vec2 basePos = engine->GetScreenSize() / 2.f;

		//parent->rotation += RotSpeed * deltaTime;
		//parent->position = basePos + MovDirection * MovAmount * glm::sin(MovSpeed * engine->GetTime());
		parent->rotation = rotation;

		// Ensure that rotation is within the range of 0 to 360 degrees
		rotation = fmod(rotation, 360.0f);
		// Handle negative rotation values
		if (rotation < 0.0f) {
			rotation += 360.0f;
		}
		float radians = glm::radians(rotation);
		MovDirection = glm::vec2(-glm::sin(radians), glm::cos(radians));

		if (isWKeyPressed) {
			/*		std::cout << "ROTATION:" << rotation << std::endl;
			std::cout << "rotationRadians:" << radians << std::endl;
			std::cout << "X:" << -glm::sin(radians) << std::endl;
			std::cout << "Y:" << glm::cos(radians) << std::endl;*/
			parent->position += MovDirection * MovAmount * glm::sin(MovSpeed * engine->GetTime());
			parent->position.x = fmod(parent->position.x, 800.0f);
			if (parent->position.x < 0)
				parent->position.x += 800.0f;

			// Wrap position.y around 0-600
			parent->position.y = fmod(parent->position.y, 600.0f);
			if (parent->position.y < 0)
				parent->position.y += 600.0f;
			std::cout << "POSITION_X:" << parent->position.x << std::endl;
			std::cout << "POSITION_Y:" << parent->position.y << std::endl;
		}
	}
	void PlayerController::KeyEvent(SDL_Event& event) {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
			{
				std::cout << "W PRESSED" << std::endl;
				//MovDirection = glm::vec2(0, 1);
				isWKeyPressed = true;
			}
			break;
			case SDLK_a:
			{
				std::cout << "A PRESSED" << std::endl;
				rotation += RotSpeed;
			}
			break;
			case SDLK_d:
			{
				std::cout << "D PRESSED" << std::endl;
				rotation -= RotSpeed;
			}
			break;
			case SDLK_SPACE:
			{
				std::cout << "SPACE PRESSED" << std::endl;
			}
			break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_w:
				// Stop moving forward when "W" is released
				//MovDirection = glm::vec2(0, 0);
				isWKeyPressed = false;
				break;
			case SDLK_SPACE:
				// Handle key releases as needed
				break;
			}
		}
	
	}
}