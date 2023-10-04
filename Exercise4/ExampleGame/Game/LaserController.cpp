#include "LaserController.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	LaserController::LaserController(const glm::vec2& screenSize) : window_size(screenSize) {	}
	void LaserController::Init() {
		// Initialize random seed

		// Randomize rotation
		rotation = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 360.0f; // Random rotation between 0 and 360 degrees

		// Randomize MovDirection
		float angle = glm::radians(rotation);
		MovDirection = glm::vec2(glm::cos(angle), glm::sin(angle));

		// Randomize initial position within the screen boundaries
		std::cout << "x:" << window_size.x << "y:" << window_size.y << std::endl;
		MyEngine::GameObject* parent = GetGameObject();
		parent->position.x = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * window_size.x;
		parent->position.y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * window_size.y;
		std::cout << "rand x:" << position.x << "y:" << position.y << std::endl;
	}

	void LaserController::Update(float deltaTime) {
		MyEngine::GameObject* parent = GetGameObject();

		// Update position based on MovDirection and wrap around the screen
		parent->position += MovDirection * MaxVelocity * deltaTime;

		// Wrap around screen
		/*	MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
			MyEngine::GameObject* parent = GetGameObject();

			glm::vec2 basePos = engine->GetScreenSize() / 2.f;

			parent->rotation += RotSpeed * deltaTime;
			parent->position = basePos + MovDirection * MovAmount * glm::sin(MovSpeed * engine->GetTime());*/
	}
}
