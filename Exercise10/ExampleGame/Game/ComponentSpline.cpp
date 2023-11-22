#include "ComponentSpline.h"



void ComponentSpline::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;
	auto pos = gameObject->GetPosition();

	//_speed = serializedData["speed"].GetFloat();
	_speed = 1;

	// apply transform to spline point offsets
	for (int i = 0; i < serializedData["points"].Size(); ++i)
		_points.emplace_back(MyEngine::GameObject::DeserializeVector(serializedData["points"][i]) + pos);

	// create point pairs, for debug purposes
	for (int i = 0; i < _points.size() - 1; ++i)
		_pairs.emplace_back(std::vector<glm::vec3> { _points[i], _points[i + 1]});

	_tangentPoints.resize(_points.size());

	float scalingFactor = 0.3f;

	// Calculate tangent points based on control points with scaling
	for (int i = 0; i < _points.size(); ++i) {
		int prevIndex = (i == 0) ? _points.size() - 1 : i - 1;
		int nextIndex = (i + 1) % _points.size();

		_tangentPoints[i] = _points[i] + (_points[nextIndex] - _points[prevIndex]) * scalingFactor;
	}
}

void ComponentSpline::Update(float delta) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_t += delta * _speed;

	int segment = static_cast<int>(_t) % (_points.size() - 1);
	float t = fmod(_t, 1.0f);

	// Calculate Quadratic Bezier curve point
	glm::vec3 p0 = _points[segment];
	glm::vec3 p1 = _tangentPoints[segment];
	glm::vec3 p2 = _points[segment + 1];

	glm::vec3 position = ((1 - t) * (1 - t)) * p0 + 2 * (1 - t) * t * p1 + (t * t) * p2;

	gameObject->SetPosition(position);
}

void ComponentSpline::Render(sre::RenderPass& renderPass) {
	for (auto& pair : _pairs)
		renderPass.drawLines(pair);
}