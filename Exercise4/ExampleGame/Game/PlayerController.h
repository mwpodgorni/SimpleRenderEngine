#pragma once

#include "Engine/Component.h"
#include "sre/RenderPass.hpp"

namespace ExampleGame {
	class PlayerController : public MyEngine::Component {
		const float RotSpeed = 5;
		const float MovSpeed = 0.1;
		const float MovAmount = 20;
		glm::vec2 MovDirection = glm::vec2(1, 1);
		bool isWKeyPressed = false;

	public:
		glm::vec2 position;	
		float rotation;

		void Init() override;
		void Update(float) override;
		//virtual void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
		virtual void KeyEvent(SDL_Event& event)override;
	};
}