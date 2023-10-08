#include "ComponentRendererMesh.h"

#include "glm/gtx/transform.hpp"

//void ComponentRendererMesh::Init(rapidjson::Value& serializedData) {
//	_mesh = sre::Mesh::create()
//		.withPositions(positions)
//		.withUVs(uvs)
//		.withIndices(idxs, sre::MeshTopology::Triangles, 0)
//		.build();
//	_material = sre::Shader::getUnlit()->createMaterial();
//
//	_texture = sre::Texture::create().withFile("data/level0.png")
//		.withGenerateMipmaps(false)
//		.withFilterSampling(false)
//		.build();
//	_material->setTexture(_texture);
//
//
//
//	float textureWidth = 1039.0f / 16.0f;  // Adjust based on your calculation
//	float textureHeight = 389.0f / 6.0f;    // Adjust based on your calculation
//
//	std::vector<glm::vec4> uvCoordinates = {
//		{0.0f, 0.0f, 0.0f, 0.0f},                          // Bottom-left (u, v, s, t)
//		{textureWidth, 0.0f, 0.0f, 0.0f},                  // Bottom-right (u, v, s, t)
//		{textureWidth, textureHeight, 0.0f, 0.0f},          // Top-right (u, v, s, t)
//		{0.0f, textureHeight, 0.0f, 0.0f}                   // Top-left (u, v, s, t)
//	};
//
//	// Use UV coordinates when creating the mesh
//	_mesh = sre::Mesh::create()
//		.withPositions(positions)
//		.withUVs(uvCoordinates)  // Pass UV coordinates with four components
//		.withIndices(idxs, sre::MeshTopology::Triangles, 0)
//		.build();
//}
void ComponentRendererMesh::Init(rapidjson::Value& serializedData) {
	// Load the texture
	_texture = sre::Texture::create().withFile("data/level0.png")
		.withGenerateMipmaps(false)
		.withFilterSampling(false)
		.build();

	// Create a new mesh with updated UV coordinates
	float textureWidth = 1039.0f;
	float textureHeight = 389.0f;
	float elementWidth = 64.0f;             // Adjust based on the element size
	float elementHeight = 64.0f;            // Adjust based on the element size

	// Calculate UV coordinates for the first element (top-left corner) without rotation
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

	std::shared_ptr<sre::Mesh> newMesh = sre::Mesh::create()
		.withPositions(positions)
		.withUVs(uvCoordinates)  // Pass UV coordinates with four components
		.withIndices(idxs, sre::MeshTopology::Triangles, 0)
		.build();

	// Swap the existing mesh with the new one
	_mesh = newMesh;

	// Create the material and set the texture
	_material = sre::Shader::getUnlit()->createMaterial();
	_material->setTexture(_texture);
}

void ComponentRendererMesh::Update(float deltaTime) {
	//GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::pi<float>() * deltaTime, glm::vec3(0, 1, 0));
}

void ComponentRendererMesh::Render(sre::RenderPass& renderPass) {
	//renderPass.draw(_mesh, GetGameObject()->transform, _material);
	// Create a rotation matrix for a 90-degree rotation around the Z-axis
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0, 0, 1));

	// Apply the rotation to the cube's transformation matrix
	glm::mat4 transformedMatrix = GetGameObject()->transform * rotationMatrix;

	// Render the cube with the rotated transformation
	renderPass.draw(_mesh, transformedMatrix, _material);
	//static auto cube = sre::Mesh::create().withCube(0.5f).build();
	//static std::vector<std::shared_ptr<sre::Material> > materials = {
	//		sre::Shader::getUnlit()->createMaterial(),
	//		sre::Shader::getUnlit()->createMaterial(),
	//		sre::Shader::getUnlit()->createMaterial()
	//};

	//std::vector<glm::vec3> positions = {
	//		{-1,0,-2},
	//		{ 0,0,-3},
	//		{ 1,0,-4}
	//};
	//std::vector<sre::Color> colors = {
	//		{1,0,0,1},
	//		{0,1,0,1},
	//		{0,0,1,1},
	//};
	//for (int i = 0; i < positions.size(); i++) {
	//	materials[i]->setColor(colors[i]);
	//	renderPass.draw(cube, glm::translate(positions[i]), materials[i]);
	//}
}