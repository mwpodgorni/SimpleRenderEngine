#include "sre/SpriteAtlas.hpp"
//#include "sre/RenderPass.hpp"
//#include "sre/SDLRenderer.hpp"

#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "Game/ComponentCamera.h"
#include "Game/ComponentRendererMesh.h"
#include "Game/ComponentController.h"
#include "Game/LevelLayout.h"

MyEngine::Engine engine;

std::shared_ptr<sre::SpriteAtlas> atlas;

int main() {
	MyEngine::ComponentFactory::RegisterComponentOfType("LEVEL_LAYOUT", std::make_shared<LevelLayout>());
	MyEngine::ComponentFactory::RegisterComponentOfType("CONTROLLER", std::make_shared<ComponentController>());
	MyEngine::ComponentFactory::RegisterComponentOfType("CAMERA", std::make_shared<ComponentCamera>());
	MyEngine::ComponentFactory::RegisterComponentOfType("CUBE_RENDERER", std::make_shared<ComponentRendererMesh>());
	engine.Init("data/scene.json");
}
