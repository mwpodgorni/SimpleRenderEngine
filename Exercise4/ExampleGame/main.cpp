#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"

#include "Game/ComponentController.h"
#include "Game/ComponentRendererSprite.h"
#include "Game/PlayerController.h"
#include <Windows.h>
#include <list>
void InitGame();
void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();
void InitAsteroids(int numberOfAsteroids);


MyEngine::Engine engine;

glm::vec2 window_size = glm::vec2(1500, 1000);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

int main() {
	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;

	renderer.setWindowSize(window_size);
	renderer.init();
	InitGame();
	camera.setWindowCoordinates();

	atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");

	auto gameObject = engine.CreateGameObject("GameObject");
	InitAsteroids(5);
	auto componentController = std::make_shared<ExampleGame::PlayerController>(window_size, atlas);

	//auto componentController = std::make_shared<ExampleGame::PlayerController>(window_size);

	//auto componentController = std::shared_ptr<ExampleGame::PlayerController>(new ExampleGame::PlayerController());
	//auto componentController = std::shared_ptr<ExampleGame::ComponentController>(new ExampleGame::ComponentController());
	auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
	gameObject->AddComponent(componentController);
	gameObject->AddComponent(componentRenderer);

	componentRenderer->sprite = atlas->get("playerShip2_blue.png");
	//componentRenderer->sprite = atlas->get("laserRed04.png");
	//componentRenderer->sprite = atlas->get("meteorBrown_big4.png");
	//componentRenderer->sprite = atlas->get("meteorBrown_med3.png");
	//componentRenderer->sprite = atlas->get("meteorBrown_small2.png");

	engine.Init();

	renderer.startEventLoop();
}
void InitAsteroids(int numberOfAsteroids) {
	for (int i = 0; i < numberOfAsteroids; i++) {
		auto gameObject = engine.CreateGameObject("Asteroid" + std::to_string(i));
		auto asteroidRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
		auto asteroidController = std::make_shared<ExampleGame::ComponentController>(window_size);
		gameObject->AddComponent(asteroidController);
		gameObject->AddComponent(asteroidRenderer);
		asteroidRenderer->sprite = atlas->get("meteorBrown_big4.png");
	}
	std::cout << "INIT ASTEROIDS" << std::endl;
}
void InitGame() {
}

void ProcessEvents(SDL_Event& event) {
	engine.ProcessEvents(event);

}

void Update(float deltaTime) {
	engine.Update(deltaTime);
}

void Render() {
	engine.Render();
}

