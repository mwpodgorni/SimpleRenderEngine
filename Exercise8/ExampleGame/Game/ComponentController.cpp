#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	// TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`
	mov_speed = serializedData["movSpeed"].GetFloat();
	rot_speed = serializedData["rotSpeed"].GetFloat();

	auto gameObject = GetGameObject().lock();
	if (gameObject) {
		body = gameObject->CreateComponent<ComponentPhysicsBody>().lock();
		body->CreateBody(b2_dynamicBody, false, glm::vec2(10.0f, 15.0f));
		body->setLinearVelocity(glm::vec2(3.0f, 0.0f));
	}
}

void ComponentController::Update(float deltaTime) {
	auto gameObject = GetGameObject().lock(); // Convert the weak_ptr to a shared_ptr

	//if (gameObject) {
	//	//std::cout << "space pressed" << displacementx << std::endl;
	//	displacementX += mov_speed * deltaTime;
	//	glm::vec3 pos = gameObject->GetPosition();
	//	pos.x += displacementX;
	//	gameObject->SetPosition(pos);
	//}
	//std::cout << "1:" << body->getLinearVelocity().y << std::endl;
	//std::cout << "2:" << body->GetPosition().y << std::endl;
	//std::cout << "3:" << gameObject->GetPosition().y << std::endl;
	//std::cout << "VELOCITY:" << body->getLinearVelocity().y << std::endl;
	//std::cout << "POS:" << body->GetPosition().y << std::endl;
	glm::vec3 pos = gameObject->GetPosition();
	pos.x = body->GetPosition().x * 100;
	pos.y = body->GetPosition().y * 100;
	gameObject->SetPosition(pos);
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
		std::cout << "SPACE PRESSEDdddddddddddddddddddddddddddddddddddddddddddd" << std::endl;
		glm::vec2 impulseVector(0.0f, 5.0f + std::max(0.0f, -body->getLinearVelocity().y));
		body->addImpulse(impulseVector);
	}
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	std::cout << "OnCollisionStart" << std::endl;
	// TODO gameOver on touching pipes, despawn coins
}
glm::vec3 ComponentController::GetControllerPosition() {
	auto gameObject = GetGameObject().lock();
	return gameObject->GetPosition();
}