#include "ComponentController.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	ComponentController::ComponentController(const glm::vec2& screenSize) : window_size(screenSize) {	}
	void ComponentController::Init() {
		// Initialize random seed
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

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

	void ComponentController::Update(float deltaTime) {
		MyEngine::GameObject* parent = GetGameObject();

		// Update position based on MovDirection and wrap around the screen
		parent->position += MovDirection * MaxVelocity * deltaTime;

		// Wrap around screen
		parent->position.x = fmod(parent->position.x, window_size.x);
		if (parent->position.x < 0)
			parent->position.x += window_size.x;

		parent->position.y = fmod(parent->position.y, window_size.y);
		if (parent->position.y < 0)
			parent->position.y += window_size.y;
		/*	MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
			MyEngine::GameObject* parent = GetGameObject();

			glm::vec2 basePos = engine->GetScreenSize() / 2.f;

			parent->rotation += RotSpeed * deltaTime;
			parent->position = basePos + MovDirection * MovAmount * glm::sin(MovSpeed * engine->GetTime());*/
	}
}