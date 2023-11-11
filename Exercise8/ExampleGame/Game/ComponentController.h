#pragma once

#include "Engine/Component.h"
#include "Engine/GameObject.h"
#include "Engine/Components/ComponentRendererSprite.h"
#include "Engine/Components/ComponentPhysicsBody.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other) override;
	void RestartGame();
	void GameOver();
public:
	glm::vec2 GetControllerPosition();


private:
	bool gameStarted = false;
	bool gameOver = false;
	glm::vec3 _mov;
	float mov_speed;
	float rot_speed;
	float displacementX = 0;
	std::shared_ptr<MyEngine::GameObject> text;
};