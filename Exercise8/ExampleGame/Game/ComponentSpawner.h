#pragma once

#include "Engine/Component.h"

class ComponentSpawner : public MyEngine::Component {
	void Init(rapidjson::Value&) override;

	void SpawnObject(std::string name, std::string sprite, glm::vec3 pos, bool isSensor);
	void SpawnFloor(std::string name, float yPos);
};