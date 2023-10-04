#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"

#include "Game/ComponentController.h"
#include "Game/AsteroidController.h"
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

glm::vec2 window_size = glm::vec2(1000, 700);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;
std::list<MyEngine::GameObject*> asteroids;
int main() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;

	renderer.setWindowSize(window_size);
	renderer.init();
	InitGame();
	camera.setWindowCoordinates();

	atlas = sre::SpriteAtlas::create("data/asteroids.json", "data/asteroids.png");

	auto playerObject = engine.CreateGameObject("Player");
	auto playerController = std::make_shared<ExampleGame::PlayerController>(window_size, atlas);
	auto playerRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
	playerRenderer->sprite = atlas->get("playerShip2_blue.png");
	playerObject->AddComponent(playerController);
	playerObject->AddComponent(playerRenderer);

	InitAsteroids(5);

	//auto componentController = std::make_shared<ExampleGame::PlayerController>(window_size);

	//auto componentController = std::shared_ptr<ExampleGame::PlayerController>(new ExampleGame::PlayerController());
	//auto componentController = std::shared_ptr<ExampleGame::ComponentController>(new ExampleGame::ComponentController());


	engine.Init();

	renderer.startEventLoop();
}
void InitAsteroids(int numberOfAsteroids) {
	std::cout << "INIT ASTEROIDS" << std::endl;

	//---------------------------------------------------------------------------
	auto asteroidObject1 = engine.CreateGameObject("Asteroid1");
	auto asteroidController1 = std::make_shared<ExampleGame::AsteroidController>(window_size);
	auto asteroidRenderer1 = std::make_shared<ExampleGame::ComponentRendererSprite>();
	asteroidRenderer1->sprite = atlas->get("meteorBrown_big4.png");

	asteroidObject1->AddComponent(asteroidController1);
	asteroidObject1->AddComponent(asteroidRenderer1);
	asteroids.push_back(asteroidObject1);



	//---------------------------------------------------------------------------
	auto asteroidObject2 = engine.CreateGameObject("Asteroid2");
	auto asteroidController2 = std::make_shared<ExampleGame::AsteroidController>(window_size);
	auto asteroidRenderer2 = std::make_shared<ExampleGame::ComponentRendererSprite>();
	asteroidRenderer2->sprite = atlas->get("meteorGrey_big3.png");

	asteroidObject2->AddComponent(asteroidController2);
	asteroidObject2->AddComponent(asteroidRenderer2);
	asteroids.push_back(asteroidObject2);

	//---------------------------------------------------------------------------
	auto asteroidObject3 = engine.CreateGameObject("Asteroid3");
	auto asteroidController3 = std::make_shared<ExampleGame::AsteroidController>(window_size);
	auto asteroidRenderer3 = std::make_shared<ExampleGame::ComponentRendererSprite>();
	asteroidRenderer3->sprite = atlas->get("meteorGrey_big3.png");

	asteroidObject3->AddComponent(asteroidController3);
	asteroidObject3->AddComponent(asteroidRenderer3);
	asteroids.push_back(asteroidObject3);


	//---------------------------------------------------------------------------
	auto asteroidObject4 = engine.CreateGameObject("Asteroid4");
	auto asteroidController4 = std::make_shared<ExampleGame::AsteroidController>(window_size);
	auto asteroidRenderer4 = std::make_shared<ExampleGame::ComponentRendererSprite>();
	asteroidRenderer4->sprite = atlas->get("meteorGrey_big3.png");

	asteroidObject4->AddComponent(asteroidController4);
	asteroidObject4->AddComponent(asteroidRenderer4);
	asteroids.push_back(asteroidObject4);


	//---------------------------------------------------------------------------
	auto asteroidObject5 = engine.CreateGameObject("Asteroid5");
	auto asteroidController5 = std::make_shared<ExampleGame::AsteroidController>(window_size);
	auto asteroidRenderer5 = std::make_shared<ExampleGame::ComponentRendererSprite>();
	asteroidRenderer5->sprite = atlas->get("meteorGrey_big3.png");

	asteroidObject5->AddComponent(asteroidController5);
	asteroidObject5->AddComponent(asteroidRenderer5);
	asteroids.push_back(asteroidObject5);

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

