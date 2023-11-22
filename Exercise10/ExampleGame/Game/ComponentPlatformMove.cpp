#include "ComponentPlatformMove.h"
#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentPhysicsBody.h"


void ComponentPlatformMove::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	auto pos = gameObject->GetPosition();

	_yoyo = serializedData["yoyo"].GetBool();
	_duration = serializedData["duration"].GetFloat();

	_str = pos + MyEngine::GameObject::DeserializeVector(serializedData["start"]);
	_end = pos + MyEngine::GameObject::DeserializeVector(serializedData["end"]);
	_easing = static_cast<EasingType>(serializedData["easing"].GetInt());

	_easing = SmoothStep;
	_body = gameObject->FindComponent<ComponentPhysicsBody>();
}

void ComponentPlatformMove::Update(float delta) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_t = std::fmod(_t + delta, _duration);

	float t = _t / _duration;
	if (_yoyo) {
		t *= 2;
		if (t > 1)
			t = 2 - t;
	}

	float v = Easing(t);

	glm::vec3 pos = _str * (1 - v) + _end * v;


	glm::vec2 d = pos - gameObject->GetPosition();

	auto a = d * (1 / MyEngine::Engine::GetInstance()->PHYSICS_SCALE);
	_body.lock()->setLinearVelocity(d);
	//gameObject->SetPosition(pos);
}

float ComponentPlatformMove::Easing(float t) {
	switch (_easing) {
	case Constant: return 0;
	case Linear: return t;
	case Sin: return glm::sin(t);
	case UpDown: return UpDownEasing(t);
	case DownUp: return DownUpEasing(t);
	case SmoothStep: return SmoothStepEasing(t);
	}
}
float ComponentPlatformMove::UpDownEasing(float t) {
	return 0.5f + 0.5f * glm::sin(pi * t);
}
float ComponentPlatformMove::DownUpEasing(float t) {
	return 0.5f - 0.5f * glm::sin(pi * t);
}
float ComponentPlatformMove::SmoothStepEasing(float t) {
	return glm::smoothstep(0.0f, 1.0f, glm::mix(0.0f, 1.0f, t));
}
