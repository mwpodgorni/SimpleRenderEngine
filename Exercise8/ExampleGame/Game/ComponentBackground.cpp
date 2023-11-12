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
	glm::vec3 playerPos = MyEngine::Engine::GetInstance()->GetPlayerPos();
	auto gameObject = GetGameObject().lock();

	auto pos = gameObject->GetPosition();
	pos.x = playerPos.x - 172;
	gameObject->SetPosition(pos);
}
