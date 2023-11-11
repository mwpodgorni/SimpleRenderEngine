#include "ComponentBackground.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"
#include "ComponentController.h"
#include "Engine/ComponentFactory.h"


void ComponentBackground::Init(rapidjson::Value&) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	auto p_spriteComp = gameObject->FindComponent<ComponentRendererSprite>();

	if (auto spriteComp = p_spriteComp.lock()) {
		sre::Sprite* sprite = spriteComp->GetSprite();
		float scale = MyEngine::Engine::GetInstance()->GetScreenSize().y / sprite->getSpriteSize().y;
		sprite->setScale({ scale, scale });
		auto gameObject = GetGameObject().lock();
		auto pos = gameObject->GetPosition();
		pos.x = -78;
		gameObject->SetPosition(pos);
	}
}
void ComponentBackground::Update(float deltaTime) {

	auto gameObject = GetGameObject().lock();

	// Update the background position with a constant value every frame
	auto pos = gameObject->GetPosition();
	pos.x += 67.0f * deltaTime;  // Adjust the constant value as needed
	gameObject->SetPosition(pos);

}
//if (controller) {
//	std::cout << "ComponentController found!" << std::endl;

//	//// Assuming ComponentController is the type you expect
//	//auto controllerComponent = std::static_pointer_cast<ComponentController>(controller);

//	//// Get the position of the ComponentController
//	//glm::vec3 controllerPosition = controllerComponent->GetControllerPosition();

//	//// Update the position of the background
//	//auto gameObjectBackground = GetGameObject().lock();
//	//std::cout << "SAVED:" << pos.x << std::endl;
//	//pos.x = controllerPosition.x;
//	//gameObjectBackground->SetPosition(pos);
//}
//else {
//	// Handle the case where the ComponentController is not found
//	std::cout << "ComponentController not found!" << std::endl;
//}