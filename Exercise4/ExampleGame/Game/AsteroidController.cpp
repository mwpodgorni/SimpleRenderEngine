#include "AsteroidController.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	AsteroidController::AsteroidController(const glm::vec2& screenSize) : window_size(screenSize) {	}
	void AsteroidController::Init() {
		// Random rotation between 0 and 360 degrees
		rotation = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 360.0f;

		// Randomize MovDirection
		float angle = glm::radians(rotation);
		MovDirection = glm::vec2(glm::cos(angle), glm::sin(angle));

		// Randomize initial position within the screen boundaries
		MyEngine::GameObject* parent = GetGameObject();
		parent->position.x = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * window_size.x;
		parent->position.y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * window_size.y;

	}

	void AsteroidController::Update(float deltaTime) {
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
	}
}