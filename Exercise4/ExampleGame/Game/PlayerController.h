#pragma once

#include "Engine/Component.h"
#include "sre/RenderPass.hpp"
#include "sre/SpriteAtlas.hpp"

namespace ExampleGame {
	class PlayerController : public MyEngine::Component {
		const float RotSpeed = 10;
		const float MovSpeed = 50;
		const float MovAmount = 10;
		glm::vec2 MovDirection = glm::vec2(1, 1);
		glm::vec2 window_size;
		bool isWKeyPressed = false;
		std::shared_ptr<sre::SpriteAtlas>& atlas;

	public:
		glm::vec2 playerSize = glm::vec2(99, 75);

		glm::vec2 position;
		float rotation;

		PlayerController(const glm::vec2& screenSize, std::shared_ptr<sre::SpriteAtlas>& atlasRef);
		void Init() override;
		void Update(float) override;
		virtual void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
		virtual void KeyEvent(SDL_Event& event)override;
		void ShootLaser();
	};
}