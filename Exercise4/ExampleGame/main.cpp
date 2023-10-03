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
void CreateAsteroid(int index);


MyEngine::Engine engine;

glm::vec2 window_size = glm::vec2(800, 500);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

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
	std::cout << "INIT ASTEROIDS" << std::endl;
	//MyEngine::Engine* engine = MyEngine::Engine::GetInstance();

	//---------------------------------------------------------------------------
	auto asteroidObject1 = engine.CreateGameObject("Asteroid1");
	auto asteroidController1 = std::make_shared<ExampleGame::ComponentController>(window_size);
	auto asteroidRenderer1 = std::make_shared<ExampleGame::ComponentRendererSprite>();

	asteroidObject1->AddComponent(asteroidController1);
	asteroidObject1->AddComponent(asteroidRenderer1);

	asteroidRenderer1->sprite = atlas->get("meteorBrown_big4.png");
	std::cout << "FIRST ASTEROID:" << std::endl;

	//---------------------------------------------------------------------------
	auto asteroidObject2 = engine.CreateGameObject("Asteroid2");
	auto asteroidController2 = std::make_shared<ExampleGame::ComponentController>(window_size);
	auto asteroidRenderer2 = std::make_shared<ExampleGame::ComponentRendererSprite>();

	asteroidObject2->AddComponent(asteroidController2);
	asteroidObject2->AddComponent(asteroidRenderer2);

	asteroidRenderer2->sprite = atlas->get("meteorGrey_big3.png");
	std::cout << "SECOND ASTEROID:" << std::endl;

	//---------------------------------------------------------------------------
	auto asteroidObject3 = engine.CreateGameObject("Asteroid3");
	auto asteroidController3 = std::make_shared<ExampleGame::ComponentController>(window_size);
	auto asteroidRenderer3 = std::make_shared<ExampleGame::ComponentRendererSprite>();

	asteroidObject3->AddComponent(asteroidController3);
	asteroidObject3->AddComponent(asteroidRenderer3);

	asteroidRenderer3->sprite = atlas->get("meteorGrey_big3.png");
	std::cout << "SECOND ASTEROID:" << std::endl;

	//---------------------------------------------------------------------------
	auto asteroidObject4 = engine.CreateGameObject("Asteroid4");
	auto asteroidController4 = std::make_shared<ExampleGame::ComponentController>(window_size);
	auto asteroidRenderer4 = std::make_shared<ExampleGame::ComponentRendererSprite>();

	asteroidObject4->AddComponent(asteroidController4);
	asteroidObject4->AddComponent(asteroidRenderer4);

	asteroidRenderer4->sprite = atlas->get("meteorGrey_big3.png");
	std::cout << "SECOND ASTEROID:" << std::endl;

	//---------------------------------------------------------------------------
	auto asteroidObject5 = engine.CreateGameObject("Asteroid5");
	auto asteroidController5 = std::make_shared<ExampleGame::ComponentController>(window_size);
	auto asteroidRenderer5 = std::make_shared<ExampleGame::ComponentRendererSprite>();

	asteroidObject5->AddComponent(asteroidController5);
	asteroidObject5->AddComponent(asteroidRenderer5);

	asteroidRenderer5->sprite = atlas->get("meteorGrey_big3.png");
	std::cout << "SECOND ASTEROID:" << std::endl;


	//for (int i = 0; i < numberOfAsteroids; i++) {
	//	CreateAsteroid(i);
	//}
}
void CreateAsteroid(int index) {
	std::cout << "SINGLE:" << index << std::endl;
	MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
	auto asteroidObject = engine->CreateGameObject("Asteroid" + std::to_string(index));
	auto asteroidController = std::make_shared<ExampleGame::ComponentController>(window_size);
	auto asteroidRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();

	asteroidObject->AddComponent(asteroidController);
	asteroidObject->AddComponent(asteroidRenderer);

	asteroidRenderer->sprite = atlas->get("meteorBrown_big4.png");
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

