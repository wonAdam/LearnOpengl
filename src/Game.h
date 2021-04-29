#pragma once
#include <vector>
#include <memory>

class Shader;
class GameObject;
class Camera;
class Gui;
class DirectionalLight;
class PointLight;
class Spotlight;

class Game
{
public:
	static DirectionalLight* gLight;
	static Camera* gCamera;
	static Gui* gGui;
	static std::vector<PointLight*> pointLights;
	static std::vector<Spotlight*> spotLights;
public: 
	std::vector<GameObject*> _gameObjects;

private:
	// Singletone
	static Game* instance;

public:
	// Singletone
	static Game* Instance();

	void static AddGameObejct(GameObject* go);
	void Initialize();
	void Update(float deltaTime, float gameTime);
	void static SetLightUniformValues(std::shared_ptr<Shader> shader);

	Game();
	virtual ~Game();
};

