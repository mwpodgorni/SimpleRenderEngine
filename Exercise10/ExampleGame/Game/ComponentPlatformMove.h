#pragma once

#include "Engine/Component.h"

enum EasingType {
	Constant,
	Linear,
	Sin,
	UpDown,
	DownUp,
	SmoothStep,
};

class ComponentPlatformMove : public MyEngine::Component {
private:
	static constexpr float pi = 3.14159265358979323846f;
	bool _yoyo;
	float _duration;
	glm::vec3 _str;
	glm::vec3 _end;
	EasingType _easing;

	// interpolation time, always betwee 0 and 1.
	// called `t` as a convention
	float _t = 0;

	std::weak_ptr<ComponentPhysicsBody> _body;

	virtual void Init(rapidjson::Value& serializedData) override;
	virtual void Update(float) override;

	float Easing(float t);
	float UpDownEasing(float t);
	float DownUpEasing(float t);
	float SmoothStepEasing(float t);
};