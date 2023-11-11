#include "ComponentSpawner.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentSpawner::Init(rapidjson::Value&) {
	float winHeight = MyEngine::Engine::GetInstance()->GetScreenSize().y;

	// these should probably go in the json file
	// you can tweak these to find a pipe distriv
	float xOffsetStart = 45;
	float curve = 250;
	float heighVariation = 30;
	float xVariation = 50;
	int nWalls = 50;

	for (int i = 0; i < nWalls; ++i) {
		float xOffset = xVariation * cos(i * curve * 0.2f) + xOffsetStart;
		float heightBot = sin(i * curve) * heighVariation;
		float heightTop = winHeight - sin(i * curve) * heighVariation - 200;
		glm::vec3 posBot{
			i * 300 + xOffset,
			heightBot,
			0
		};
		glm::vec3 posTop{
			i * 300 + xOffset,
		heightTop,
			0
		};
		float midHeight = (heightTop + heightBot) / 2.0f + 50;
		glm::vec3 posCoin{
			i * 300 + xOffset + 100,
			midHeight,
			0
		};
		//std::cout << "Top pos" << posTop.y << std::endl;
		//std::cout << "Bot pos" << posBot.y << std::endl;
		SpawnObject("WallBottom" + std::to_string(i), "column_bottom.png", posBot, false);
		SpawnObject("WallTop" + std::to_string(i), "column_top.png", posTop, false);
		SpawnObject("Coin" + std::to_string(i), "coin.png", posCoin, true);
	}
	SpawnFloor("Ground", 10);
}

void ComponentSpawner::SpawnObject(std::string name, std::string spriteId, glm::vec3 pos, bool isSensor) {
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto wall = engine->CreateGameObject(name, gameObject).lock();
	auto renderer = wall->CreateComponent<ComponentRendererSprite>().lock();
	renderer->SetSprite("bird", spriteId);

	auto sprite = renderer->GetSprite();
	sprite->setScale({ 2, 2 });

	pos.y += sprite->getSpriteSize().y / 2;
	wall->SetPosition(pos);

	auto body = wall->CreateComponent<ComponentPhysicsBody>().lock();
	glm::vec2 s{ sprite->getSpriteSize().x * sprite->getScale().x / 2, sprite->getSpriteSize().y * sprite->getScale().y / 2 };
	body->CreateBody(b2_staticBody, isSensor, s);
}
void ComponentSpawner::SpawnFloor(std::string name, float yPos) {
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto floor = engine->CreateGameObject(name, gameObject).lock();

	auto body = floor->CreateComponent<ComponentPhysicsBody>().lock();

	glm::vec2 groundSize{ engine->GetScreenSize().x, 10.0f };
	body->CreateBody(b2_staticBody, false, groundSize);

	glm::vec3 pos{
		engine->GetScreenSize().x / 2,
		yPos,
		0
	};
	glm::vec2 bodyPos{
		pos.x,
		pos.y
	};
	floor->SetPosition(pos);
	body->SetPosition(bodyPos);
}