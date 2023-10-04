#pragma once

#include "Engine/Component.h"

namespace ExampleGame {
	class AsteroidController : public MyEngine::Component {
		const float AsteroidController::MaxVelocity = 50.0f;
		const float RotSpeed = 50;
		const float MovSpeed = 5;
		const float MovAmount = 20;
		glm::vec2 window_size;

	public:
		glm::vec2 MovDirection = glm::vec2(1, 0);
		glm::vec2 position;
		float rotation;

		glm::vec2 playerSize = glm::vec2(98, 96);


		AsteroidController(const glm::vec2& screenSize);
		void Init() override;
		void Update(float) override;
	};
}