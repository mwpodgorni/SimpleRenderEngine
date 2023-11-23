#pragma once

#include "Engine/Component.h"
#include "Engine/Components/ComponentRendererSprite.h"
class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) override;
	void OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) override;
	void UpdateAnimation(glm::vec2 velocity);

private:
	std::weak_ptr<ComponentPhysicsBody> _body;
	std::weak_ptr<ComponentRendererSprite> _sprite;
	glm::vec3 _mov;
	bool _jump;
	bool _grounded;

	float _movSpeed = 2;
	float _jumpStrength = 5;

	// Animation variables
	bool _switchAnimation = false;
	double _animationTimer = 0.0;
	const double _animationSpeed = 0.2; // Adjust the speed as needed
};