#pragma once
#include <vector>
#include <memory>

#include "GameObject.h"
#include "Texture.h"
#include "Shader.h"
#include "Cube.h"

class Game
{
private: 
	std::vector<GameObject*> _gameObjects;
	// Singletone
	static Game instance;

public:
	// Singletone
	static Game& Instance();

	void static AddGameObejct(GameObject* go);
	void Initialize();
	void Update(float deltaTime);

	Game();
	virtual ~Game();
};

