#include "ComponentRendererMesh.h"
#include "LevelLayout.h"
#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "glm/gtx/transform.hpp"
float textureWidth = 1039.0f;
float textureHeight = 389.0f;
float elementWidth = 64.0f;
float elementHeight = 64.0f;

int numRows = 6;      // Number of rows in the PNG file
int numCols = 16;     // Number of textures per row

int textureIndex = 16; // Index of the desired texture (0-based index)


std::vector<glm::vec4> GetUvCoordinates(int textureIndex) {
	int row = textureIndex / numCols;
	int col = textureIndex % numCols;

	float uMin = static_cast<float>(col) * (elementWidth / textureWidth);
	float uMax = static_cast<float>(col + 1) * (elementWidth / textureWidth);
	float vMin = 1.0f - (static_cast<float>(row) + 1.0f) * (elementHeight / textureHeight);
	float vMax = 1.0f - static_cast<float>(row) * (elementHeight / textureHeight);

	std::vector<glm::vec4> uvCoordinates = {
		// front
		{uMin, vMax, 0.0f, 0.0f},  // Top-left (u, v, s, t)
		{uMax, vMax, 0.0f, 0.0f},  // Top-right (u, v, s, t)
		{uMax, vMin, 0.0f, 0.0f},  // Bottom-right (u, v, s, t)
		{uMin, vMin, 0.0f, 0.0f},   // Bottom-left (u, v, s, t)
		// left
		{uMin, vMax, 0.0f, 0.0f},
		{uMax, vMax, 0.0f, 0.0f},
		{uMax, vMin, 0.0f, 0.0f},
		{uMin, vMin, 0.0f, 0.0f},
		// back
		{uMin, vMax, 0.0f, 0.0f},
		{uMax, vMax, 0.0f, 0.0f},
		{uMax, vMin, 0.0f, 0.0f},
		{uMin, vMin, 0.0f, 0.0f},
		// right
		{uMin, vMax, 0.0f, 0.0f},
		{uMax, vMax, 0.0f, 0.0f},
		{uMax, vMin, 0.0f, 0.0f},
		{uMin, vMin, 0.0f, 0.0f}
	};
	return uvCoordinates;
}

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
		auto levelLayout = std::dynamic_pointer_cast<LevelLayout>(levelLayoutComponent);

		if (levelLayout) {
			const std::vector<int>& layout = levelLayout->layout;
			const std::vector<glm::vec3>& cubePositions = levelLayout->cubePositions;

			for (size_t i = 0; i < cubePositions.size(); i++) {

				static std::shared_ptr<sre::Material> material = sre::Shader::getUnlit()->createMaterial();
				material->setTexture(_texture);
				if (layout[i] != 0) {
					std::vector<glm::vec4> coordinates = GetUvCoordinates(layout[i]);
					auto cube = sre::Mesh::create().withCube(0.5f)
						.withUVs(coordinates)
						.build();
					renderPass.draw(cube, glm::translate(cubePositions[i]), material);
				}
			}

		}
	}
}

