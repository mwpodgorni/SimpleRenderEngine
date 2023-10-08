#include "ComponentRendererMesh.h"
#include "LevelLayout.h"
#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "glm/gtx/transform.hpp"

float textureWidth = 1039.0f;
float textureHeight = 389.0f;
float elementWidth = 64.0f;
float elementHeight = 64.0f;

float uMin = 0.0f;
float uMax = elementWidth / textureWidth;
float vMin = 1.0f - elementHeight / textureHeight;
float vMax = 1.0f;

std::vector<glm::vec4> uvCoordinates = {
	{uMin, vMax, 0.0f, 0.0f},  // Top-left (u, v, s, t)
	{uMax, vMax, 0.0f, 0.0f},  // Top-right (u, v, s, t)
	{uMax, vMin, 0.0f, 0.0f},  // Bottom-right (u, v, s, t)
	{uMin, vMin, 0.0f, 0.0f}   // Bottom-left (u, v, s, t)
};
void ComponentRendererMesh::Init(rapidjson::Value& serializedData) {
	// Load the texture
	_texture = sre::Texture::create().withFile("data/level0.png")
		.withGenerateMipmaps(false)
		.withFilterSampling(false)
		.build();
}

void ComponentRendererMesh::Update(float deltaTime) {
	//GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::pi<float>() * deltaTime, glm::vec3(0, 1, 0));
}

void ComponentRendererMesh::Render(sre::RenderPass& renderPass) {
	// Use the ComponentFactory to get the LevelLayout component
	auto levelLayoutComponent = MyEngine::ComponentFactory::GetComponentOfType("LEVEL_LAYOUT");

	if (levelLayoutComponent) {
		// Cast the component to the LevelLayout type
		auto levelLayout = std::dynamic_pointer_cast<LevelLayout>(levelLayoutComponent);

		if (levelLayout) {
			// Access layout and cubePositions from the LevelLayout component
			const std::vector<std::vector<int>>& layout = levelLayout->layout;
			const std::vector<glm::vec3>& cubePositions = levelLayout->cubePositions;

			// Now you can use the layout and cubePositions as needed
			// ...

			static auto cube = sre::Mesh::create().withCube(0.5f)
				.withUVs({
				// Front face
				{uMin, vMax, 0.0f, 0.0f},
				{uMax, vMax, 0.0f, 0.0f},
				{uMax, vMin, 0.0f, 0.0f},
				{uMin, vMin, 0.0f, 0.0f},

				// Back face
				{uMin, vMax, 0.0f, 0.0f},
				{uMax, vMax, 0.0f, 0.0f},
				{uMax, vMin, 0.0f, 0.0f},
				{uMin, vMin, 0.0f, 0.0f},

				// Left face
				{uMin, vMax, 0.0f, 0.0f},
				{uMax, vMax, 0.0f, 0.0f},
				{uMax, vMin, 0.0f, 0.0f},
				{uMin, vMin, 0.0f, 0.0f},

				// Right face
				{uMin, vMax, 0.0f, 0.0f},
				{uMax, vMax, 0.0f, 0.0f},
				{uMax, vMin, 0.0f, 0.0f},
				{uMin, vMin, 0.0f, 0.0f}
					})
				.build();

			static std::shared_ptr<sre::Material> material = sre::Shader::getUnlit()->createMaterial();
			material->setTexture(_texture);

			for (const auto& position : cubePositions) {
				renderPass.draw(cube, glm::translate(position), material);
			}
		}
	}
}