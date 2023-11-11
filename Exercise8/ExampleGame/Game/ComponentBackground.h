#pragma once

#include "Engine/Component.h"
#include "ComponentController.h"

class ComponentBackground : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
private:
	std::shared_ptr<ComponentController> controller;
};