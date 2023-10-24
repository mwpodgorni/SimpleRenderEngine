#include "ComponentController.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/transform.hpp"
#include "SDL.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	mov_speed = serializedData["movSpeed"].GetFloat();
	rot_speed = serializedData["rotSpeed"].GetFloat();
}

void ComponentController::Update(float deltaTime) {

	if (isWPressed) {
		glm::mat4 playerTransform = GetGameObject()->transform;

		// extract the rotation part of the transformation matrix as a 3x3 matrix
		glm::mat3 rotationMatrix = glm::mat3(playerTransform);

		// calculate the forward vector based on the rotation matrix
		glm::vec3 forwardVector = glm::normalize(rotationMatrix * glm::vec3(0.0f, 0.0f, -1.0f));

		// calculate the new position based on the forward vector and movement speed
		glm::vec3 newPosition = glm::vec3(playerTransform[3]) + (forwardVector * 0.2f * mov_speed * deltaTime);

		// update the player's transformation matrix with the new position
		playerTransform[3] = glm::vec4(newPosition, 1.0f);
		GetGameObject()->transform = playerTransform;
	}
	else if (isSPressed) {
		glm::mat4 playerTransform = GetGameObject()->transform;

		// extract the rotation part of the transformation matrix as a 3x3 matrix
		glm::mat3 rotationMatrix = glm::mat3(playerTransform);

		// calculate the forward vector based on the rotation matrix
		glm::vec3 forwardVector = glm::normalize(rotationMatrix * glm::vec3(0.0f, 0.0f, 1.0f));

		// Calculate the new position based on the forward vector and movement speed
		glm::vec3 newPosition = glm::vec3(playerTransform[3]) + (forwardVector * 0.2f * mov_speed * deltaTime);

		// Update the player's transformation matrix with the new position
		playerTransform[3] = glm::vec4(newPosition, 1.0f);
		GetGameObject()->transform = playerTransform;
	}

	if (isAPressed) {
		GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::radians(rot_speed * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (isDPressed) {
		GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::radians(-rot_speed * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));

	}
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_w) {
			std::cout << "W PRESSED" << std::endl;
			isWPressed = true;
		}
		if (event.key.keysym.sym == SDLK_s) {
			std::cout << "S PRESSED" << std::endl;
			isSPressed = true;
		}
		if (event.key.keysym.sym == SDLK_a) {
			std::cout << "A PRESSED" << std::endl;
			isAPressed = true;
		}
		if (event.key.keysym.sym == SDLK_d) {
			std::cout << "D PRESSED" << std::endl;
			isDPressed = true;
		}
		if (event.key.keysym.sym == SDLK_x) {
			std::cout << "X PRESSED - Closing application" << std::endl;
			// Exit the application
			exit(0);
		}
	}
	else if (event.type == SDL_KEYUP) {
		std::cout << "KEYUP" << std::endl;
		if (event.key.keysym.sym == SDLK_w) {
			isWPressed = false;
		}
		if (event.key.keysym.sym == SDLK_s) {
			isSPressed = false;
		}
		if (event.key.keysym.sym == SDLK_a) {
			isAPressed = false;
		}
		if (event.key.keysym.sym == SDLK_d) {
			isDPressed = false;
		}
	}

}

void ComponentController::Render(sre::RenderPass&) {
	glm::vec3 position, scale;
	glm::quat rotation;
	glm::vec3 skew; glm::vec4 perspective;

	glm::decompose(GetGameObject()->transform, scale, rotation, position, skew, perspective);

	glm::vec3 display_rot = glm::degrees(glm::eulerAngles(rotation));
	ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 75), ImGuiSetCond_Always);
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::DragFloat3("Position", glm::value_ptr(position));
	ImGui::DragFloat("Rotation", &display_rot.y);
	ImGui::End();

	GetGameObject()->transform =
		glm::scale(scale) *
		glm::translate(position) *
		glm::mat4_cast(glm::quat(glm::radians(display_rot)));
}

