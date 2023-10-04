#include "LaserController.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	LaserController::LaserController(const glm::vec2& screenSize) : window_size(screenSize) {	}
	void LaserController::Init() {
		// Random rotation between 0 and 360 degrees
		rotation = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * 360.0f;
		// uandomize MovDirection
		float angle = glm::radians(rotation);
		MovDirection = glm::vec2(glm::cos(angle), glm::sin(angle));

		//randomize initial position within the screen boundaries
		MyEngine::GameObject* parent = GetGameObject();
		parent->position.x = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * window_size.x;
		parent->position.y = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) * window_size.y;
	}

	void LaserController::Update(float deltaTime) {
		MyEngine::GameObject* parent = GetGameObject();

		//update position based on MovDirection and wrap around the screen
		parent->position += MovDirection * MaxVelocity * deltaTime;
	}
}
