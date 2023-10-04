#include "MyEngine.h"

#include <random>

#include "sre/RenderPass.hpp"

namespace MyEngine {
	Engine* Engine::_instance = nullptr;

	Engine::Engine() {
		assert(_instance == nullptr && " Only one instance of MyEngine::Engine allowed!");
		_instance = this;

		_root = std::make_shared<GameObject>();
		_root->SetName("root");
	}

	glm::vec2 Engine::GetScreenSize() const
	{
		return WIN_SIZE;
	}

	void Engine::Init() {
		// initializes random generator
		std::srand(std::time(nullptr));

		_camera.setWindowCoordinates();

		_root->Init();

		for (auto it1 = _root->_children.begin(); it1 != _root->_children.end();) {
			std::cout << "NAME:" << (*it1)->GetName() << std::endl;
			++it1;
		}
	}

	void Engine::ProcessEvents(SDL_Event& event) {
		_root->KeyEvent(event);
	}

	void Engine::DetectCollisions() {

		std::queue<int> deleteQueue;

		for (auto it1 = _root->_children.begin(); it1 != _root->_children.end(); ++it1) {
			if ((*it1)->GetName().find("Asteroid") != std::string::npos) {
				for (auto it2 = _root->_children.begin(); it2 != _root->_children.end(); ++it2) {
					if (it1 != it2) {
						float dist = glm::distance((*it1)->position, (*it2)->position);
						float collisionThreshold = (*it1)->size + (*it2)->size;

						if (dist <= collisionThreshold) {
							if ((*it2)->GetName().find("Player") != std::string::npos) {
								std::cout << "Asteroid and Player collided" << std::endl;
							}
							else if ((*it2)->GetName().find("Laser") != std::string::npos) {
								std::cout << "Asteroid and Laser collided" << std::endl;
								deleteQueue.push(std::distance(_root->_children.begin(), it1));
								deleteQueue.push(std::distance(_root->_children.begin(), it2));

							}


							/*	deleteQueue.push(std::distance(_root->_children.begin(), it1));
							deleteQueue.push(std::distance(_root->_children.begin(), it2));*/
						}
					}
				}
			}
		}

		while (!deleteQueue.empty()) {
			int idx1 = deleteQueue.front();
			deleteQueue.pop();
			int idx2 = deleteQueue.front();
			deleteQueue.pop();

			auto it1 = std::next(_root->_children.begin(), idx1);
			auto it2 = std::next(_root->_children.begin(), idx2);

			_root->_children.erase(it2);
			_root->_children.erase(it1);
		}
	}
	void Engine::Update(float deltaTime) {
		++frame;
		time += deltaTime;
		_root->Update(deltaTime);
		DetectCollisions();
	}

	void Engine::Render()
	{
		sre::RenderPass renderPass = sre::RenderPass::create()
			.withCamera(_camera)
			.withClearColor(true, { .3f, .3f, 1, 1 })
			.build();

		sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();

		_root->Render(spriteBatchBuilder);

		auto spriteBatch = spriteBatchBuilder.build();
		renderPass.draw(spriteBatch);
	}

	GameObject* Engine::CreateGameObject(std::string name) {
		auto ret = std::make_shared<GameObject>();
		ret->_self = ret;
		ret->_parent = _root;
		ret->SetName(name);
		_root->AddChild(ret);

		return ret.get();
	}

}
