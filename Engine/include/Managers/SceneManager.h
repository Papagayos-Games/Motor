#pragma once
#include <string>
#include <vector>

class LoaderSystem;
class Entity;
class Scene;

class SceneManager {
public:
	~SceneManager();

	static SceneManager* getInstance();
	static bool setupInstance();
	static void clean();

	void loadScene(const std::string& sceneName);
	static void cleanupScene();

	// Añade entidades y componentes a esas entidades al iniciar la escena y al instanciar gameObjects durante ejecuccion
	void addEntity() {};
	void addComponentTo(const std::string& entName) {};
	void addComponentTo(const Entity *ent){};

private:
	SceneManager();
	static SceneManager* instance_;
	static Scene* currentScene_;
	std::vector<std::string> sceneFiles_;
	LoaderSystem* loader_;
	// Crea la escena por defecto
	void createStartScene();
};