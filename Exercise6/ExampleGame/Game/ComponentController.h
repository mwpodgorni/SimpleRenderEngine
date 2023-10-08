#pragma once
#include "Component.h"

class ComponentController : public MyEngine::Component {
public:
	float mov_speed;
	float rot_speed;
	bool isWPressed;
	bool isSPressed;
	bool isAPressed;
	bool isDPressed;
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void Render(sre::RenderPass&) override;
};