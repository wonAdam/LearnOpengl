#pragma once
#include <vector>

#include "GameObject.h"

class Game
{
private: 
	static std::vector<GameObject*> _gameObjects;
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

