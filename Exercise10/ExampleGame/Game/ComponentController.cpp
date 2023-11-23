#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_body = gameObject->FindComponent<ComponentPhysicsBody>();
	_sprite = gameObject->FindComponent<ComponentRendererSprite>();
}

void ComponentController::Update(float deltaTime) {
	auto body = _body.lock();
	if (!body)
		return;

	auto linearVelocity = body->getLinearVelocity();
	linearVelocity.x = _mov.x * _movSpeed;
	body->setLinearVelocity(linearVelocity);

	if (_jump) {
		body->addImpulse(glm::vec2(0, _jumpStrength));
		_jump = false;
	}
	UpdateAnimation(body->getLinearVelocity());
}

void ComponentController::KeyEvent(SDL_Event& event) {
	// movement
	switch (event.key.keysym.sym) {
	case SDLK_a: _mov.x = -(event.type == SDL_KEYDOWN); break;
	case SDLK_d: _mov.x = +(event.type == SDL_KEYDOWN); break;
	}

	// jump
	if (_grounded && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		_jump = true;

}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (manifold->localNormal.y > .99)
		_grounded = true;
}

void ComponentController::OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (manifold->localNormal.y > .99)
		_grounded = false;
}
void ComponentController::UpdateAnimation(glm::vec2 velocity) {
	auto sprite = _sprite.lock();
	if (_grounded) {
		if (velocity.x == 0) {
			sprite->SetSprite("platformer-art-deluxe", "19.png");
		}
		else {

			_animationTimer += _animationSpeed;
			if (_animationTimer >= 1.0) {
				_switchAnimation = !_switchAnimation;
				_animationTimer = 0.0;
			}

			if (_switchAnimation) {
				sprite->SetSprite("platformer-art-deluxe", "21.png");
			}
			else {
				sprite->SetSprite("platformer-art-deluxe", "20.png");
			}
			if (velocity.x > 0) {
				sprite->SetDirection(false);
			}
			else {
				sprite->SetDirection(true);
			}
		}
	}
	else {
		if (velocity.y > 0.7) {
			sprite->SetSprite("platformer-art-deluxe", "26.png");
		}
		else if (velocity.y < -0.7) {
			sprite->SetSprite("platformer-art-deluxe", "28.png");
		}
		else {
			sprite->SetSprite("platformer-art-deluxe", "27.png");
		}
	}
}