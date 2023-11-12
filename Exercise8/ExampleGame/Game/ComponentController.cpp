#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	mov_speed = serializedData["movSpeed"].GetFloat();

	// start text
	auto engine = MyEngine::Engine::GetInstance();
	auto current = GetGameObject();
	float width = engine->GetScreenSize().x;
	text = engine->CreateGameObject("GetReady", current).lock();
	auto renderer = text->CreateComponent<ComponentRendererSprite>().lock();
	renderer->SetSprite("bird", "get-ready.png");
	auto sprite = renderer->GetSprite();
	sprite->setScale({ 1, 1 });
	glm::vec3 pos{
		100,
		350,
		0
	};
	text->SetPosition(pos);
}

void ComponentController::Update(float deltaTime) {
	auto gameObject = GetGameObject().lock();
	glm::vec3 pos = gameObject->GetPosition();
	MyEngine::Engine::GetInstance()->UpdatePlayerPos(pos);
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
		if (!gameStarted) {
			gameStarted = true;
			RestartGame();
		}
		else if (!gameOver) {
			auto gameObject = GetGameObject().lock();
			auto body = gameObject->FindComponent<ComponentPhysicsBody>().lock();
			glm::vec2 impulseVector(0.0f, 4.0f + std::max(0.0f, -body->getLinearVelocity().y));
			body->addImpulse(impulseVector);
		}

	}
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	auto collidingObject = other->GetGameObject().lock();

	if (collidingObject) {
		std::string objectName = collidingObject->GetName();
		if (objectName.find("Coin") != std::string::npos) {
			auto engine = MyEngine::Engine::GetInstance();
			engine->DeregisterPhysicsComponent(other);
			engine->DestroyGameObject(collidingObject.get());
		}
		if ((objectName.find("Wall") != std::string::npos
			|| objectName.find("Ground") != std::string::npos
			|| objectName.find("Ceiling") != std::string::npos) && !gameOver) {
			GameOver();
		}
	}
}
void ComponentController::RestartGame() {
	gameOver = false;

	auto engine = MyEngine::Engine::GetInstance();
	engine->SetGravity(0, -9.8);
	auto gameObject = GetGameObject().lock();
	auto body = gameObject->FindComponent<ComponentPhysicsBody>().lock();
	body->setLinearVelocity(glm::vec2(mov_speed, 0.0f));
}
void ComponentController::GameOver() {
	auto engine = MyEngine::Engine::GetInstance();
	gameOver = true;
	engine->DestroyGameObject(text.get());
	auto lockedGameObject = GetGameObject().lock();

	auto body = lockedGameObject->FindComponent<ComponentPhysicsBody>().lock();
	body->setLinearVelocity(glm::vec2(0, 0.0f));


	auto gameObject = GetGameObject();

	float width = engine->GetScreenSize().x;

	text = engine->CreateGameObject("GameOver", gameObject).lock();
	auto renderer = text->CreateComponent<ComponentRendererSprite>().lock();
	renderer->SetSprite("bird", "game-over.png");
	auto sprite = renderer->GetSprite();
	sprite->setScale({ 1, 1 });
	glm::vec3 pos{
		lockedGameObject->GetPosition().x,
		350,
		0
	};
	text->SetPosition(pos);
}
glm::vec2 ComponentController::GetControllerPosition() {
	auto gameObject = GetGameObject().lock();
	auto body = gameObject->FindComponent<ComponentPhysicsBody>().lock();
	return body->GetPosition();
}