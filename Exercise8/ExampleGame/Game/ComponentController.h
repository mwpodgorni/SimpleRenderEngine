#pragma once

#include "Engine/Component.h"
#include "Engine/Components/ComponentPhysicsBody.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other) override;
	glm::vec3 GetControllerPosition();

private:
	glm::vec3 _mov;
	float mov_speed;
	float rot_speed;
	std::shared_ptr<ComponentPhysicsBody> body;
	float displacementX = 0;
};