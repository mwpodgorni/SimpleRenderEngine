#include "PlayerController.h"
#include "Engine/MyEngine.h"
#include "ComponentRendererSprite.h"
#include "ComponentController.h"
#include "LaserController.h"
namespace ExampleGame {
	PlayerController::PlayerController(const glm::vec2& screenSize, std::shared_ptr<sre::SpriteAtlas>& atlasRef)
		: window_size(screenSize), atlas(atlasRef) {}
	void PlayerController::Init() {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		glm::vec2 basePos = engine->GetScreenSize() / 2.f;
		MyEngine::GameObject* parent = GetGameObject();
		parent->position += basePos;
	}

	void PlayerController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

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
			parent->position += MovDirection * MovAmount * glm::sin(MovSpeed * engine->GetTime());
			parent->position.x = fmod(parent->position.x, window_size.x);
			//wrap around screen
			if (parent->position.x < 0)
				parent->position.x += window_size.x;
			parent->position.y = fmod(parent->position.y, window_size.y);
			if (parent->position.y < 0)
				parent->position.y += window_size.y;
		}
	}
	void PlayerController::Render(sre::SpriteBatch::SpriteBatchBuilder&) {
		//std::cout << "PLAYER RENDER" << std::endl;
	}
	void PlayerController::KeyEvent(SDL_Event& event) {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_w) {
				std::cout << "W PRESSED" << std::endl;
				isWKeyPressed = true;
			}

		switch (event.key.keysym.sym) {
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
			}
		}
		if (event.key.keysym.sym == SDLK_SPACE) {
			std::cout << "SPACE PRESSED" << std::endl;
			ShootLaser();
		}
		else if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_w) {
				isWKeyPressed = false;
			}
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				break;
			}
		}

	}
	void PlayerController::ShootLaser() {
		std::cout << "SHOOT" << std::endl;
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		// Create a new game object for the laser
		auto laserObject = engine->CreateGameObject("Laser");

		// Add the ComponentLaser and ComponentRendererSprite to the laser object
		auto laserController = std::make_shared<LaserController>(window_size);
		auto laserRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
		laserObject->AddComponent(laserController);
		laserObject->AddComponent(laserRenderer);

		// Set the sprite for the laser (replace "laserSprite.png" with the actual sprite)
		laserRenderer->sprite = atlas->get("laserRed04.png");

		// Set the position and direction of the laser (e.g., based on player's position and direction)
		laserObject->position = parent->position;
		laserObject->rotation = parent->rotation;
		laserController->MovDirection = MovDirection;
	}
}