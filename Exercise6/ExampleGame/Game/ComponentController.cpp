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
    std::cout << "ROTATION1:" << GetGameObject()->transform[1][0] << std::endl;
    std::cout << "ROTATION2:" << GetGameObject()->transform[1][1] << std::endl;
    std::cout << "ROTATION3:" << GetGameObject()->transform[1][2] << std::endl;

    if (isWPressed) {
        glm::mat4 playerTransform = GetGameObject()->transform;

        // Extract the rotation part of the transformation matrix as a 3x3 matrix
        glm::mat3 rotationMatrix = glm::mat3(playerTransform);

        // Calculate the forward vector based on the rotation matrix
        glm::vec3 forwardVector = glm::normalize(rotationMatrix * glm::vec3(0.0f, 0.0f, -1.0f));

        // Calculate the new position based on the forward vector and movement speed
        glm::vec3 newPosition = glm::vec3(playerTransform[3]) + (forwardVector  * 0.2f * mov_speed* deltaTime);

        // Update the player's transformation matrix with the new position
        playerTransform[3] = glm::vec4(newPosition, 1.0f);
        GetGameObject()->transform = playerTransform;
    }

    if (isAPressed) {


        GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::radians(rot_speed*deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));


    }

    if (isDPressed) {

        GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::radians(-rot_speed * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));

    }
    //if (isWPressed) {
    //    // Calculate the forward vector based on the player's rotation
    //    glm::vec3 forwardDirection = glm::vec3(0.0f, 0.0f, 1.0f); // Forward direction in local coordinates

    //    // Extract Euler angles from the transform's rotation
    //    glm::vec3 eulerAngles = glm::degrees(glm::eulerAngles(glm::quat_cast(GetGameObject()->transform)));

    //    // Calculate the forward vector based on the extracted Euler angles
    //    glm::quat rotationQuat = glm::quat(glm::radians(eulerAngles));
    //    glm::vec3 forwardVector = rotationQuat * forwardDirection;

    //    // Normalize and scale the forward vector by mov_speed and deltaTime for smooth movement
    //    glm::vec3 moveVector = glm::normalize(forwardVector) * mov_speed * deltaTime;

    //    // Translate the object's transform matrix by the move vector
    //    GetGameObject()->transform = glm::translate(GetGameObject()->transform, moveVector);
    //}

    //if (isAPressed) {
    //    GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::radians(rot_speed * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
    //}

    //if (isDPressed) {
    //    GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::radians(-rot_speed * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
    //}
}

void ComponentController::KeyEvent(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_w) {
            std::cout << "W PRESSED" << std::endl;
            isWPressed = true;
        }
        if (event.key.keysym.sym == SDLK_a) {
            std::cout << "A PRESSED" << std::endl;
            isAPressed = true;
        }
        if (event.key.keysym.sym == SDLK_d) {
            std::cout << "D PRESSED" << std::endl;
            isDPressed = true;
        }
    }
    else if (event.type == SDL_KEYUP) {
        std::cout << "KEYUP" << std::endl;
        if (event.key.keysym.sym == SDLK_w) {
            isWPressed = false;
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
	// we don't really care about these for gameObjects, but we need to matck glm::decompose() signature
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