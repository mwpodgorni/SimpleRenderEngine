#include "ComponentSpline.h"



void ComponentSpline::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;
	auto pos = gameObject->GetPosition();

	_speed = serializedData["speed"].GetFloat();

	for (int i = 0; i < serializedData["points"].Size(); ++i)
		_points.emplace_back(MyEngine::GameObject::DeserializeVector(serializedData["points"][i]) + pos);

	// Create point pairs for debug purposes
	for (int i = 0; i < _points.size() - 1; ++i)
		_pairs.emplace_back(std::vector<glm::vec3>{_points[i], _points[i + 1]});
}

void ComponentSpline::Update(float delta) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_t += delta * _speed;

	int segment = static_cast<int>(_t);
	float t = _t - segment;

	// catmull-rom interpolation
	// Position=0.5f*((-t^3+2*t^2-t)*P0+(3*t^3-5*t^2+2)*P1+(-3*t^3+4*t^2+t)*P2+(t^3-t^2)*P3)
	// four consecutive control points that wrap around if segment goes outside of the total number of points
	glm::vec3 p0 = _points[segment % _points.size()];
	glm::vec3 p1 = _points[(segment + 1) % _points.size()];
	glm::vec3 p2 = _points[(segment + 2) % _points.size()];
	glm::vec3 p3 = _points[(segment + 3) % _points.size()];

	// weighted sum of control points
	glm::vec3 position = 0.5f * (
		//contribution of the previous point
		(-t * t * t + 2 * t * t - t) * p0 +
		//contribution from the current point
		(3 * t * t * t - 5 * t * t + 2) * p1 +
		// contribution from the next point
		(-3 * t * t * t + 4 * t * t + t) * p2 +
		// contribution from the next, next point
		(t * t * t - t * t) * p3
		);

	gameObject->SetPosition(position);
}
void ComponentSpline::Render(sre::RenderPass& renderPass) {
	for (auto& pair : _pairs)
		renderPass.drawLines(pair);
}