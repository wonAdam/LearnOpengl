#pragma once
#include <vector>
#include <memory>

class GameObject;
class Light;

class Game
{
public:
	static Light* _light;
private: 
	std::vector<GameObject*> _gameObjects;
	// Singletone
	static Game* instance;

public:
	// Singletone
	static Game* Instance();

	void static AddGameObejct(GameObject* go);
	void Initialize();
	void Update(float deltaTime, float gameTime);

	Game();
	virtual ~Game();
};

