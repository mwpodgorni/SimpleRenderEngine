#pragma once

#include "Engine/Component.h"


class LevelLayout : public MyEngine::Component {
public:
	std::vector<int> layout;
	std::vector<glm::vec3> cubePositions;

	void Init(rapidjson::Value& serializedData) override;
	void Test();
};