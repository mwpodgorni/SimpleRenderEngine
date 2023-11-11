#include "ComponentBackground.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"
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
	/*std::cout << "UPDATE<" << std::endl;
	auto controller =  MyEngine::ComponentFactory::GetComponentOfType("CONTROLLER");
	auto controllerObject = controller->GetGameObject();
	std::cout << "UPDATE2" << std::endl;
	std::shared_ptr<MyEngine::GameObject> controllerPointer = controllerObject.lock();
	glm::vec3 controllerPosition = controllerPointer->GetPosition();
	std::cout << "UPDATE3" << std::endl;

	auto gameObject = GetGameObject().lock(); 
	glm::vec3 pos = gameObject->GetPosition();
	std::cout << "UPDATE4" << std::endl;
	pos.x = controllerPosition.x;
	gameObject->SetPosition(pos);*/

}
