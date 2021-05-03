#include "Managers/SceneManager.h"
#include "Scene/Scene.h"
#include "Graphics/WindowGenerator.h"
#include "Graphics/OgreContext.h"
#include "LoaderSystem.h"

#include "PapagayoEngine.h"
#include "OgreContext.h"
#include "WindowGenerator.h"
#include "OgreRenderWindow.h"

SceneManager* SceneManager::instance_= nullptr;
Scene* SceneManager::currentScene_ = nullptr;

SceneManager::~SceneManager()
{
	clean();
}

SceneManager* SceneManager::getInstance()
{
	if (instance_ == nullptr)
		return nullptr;
	
		return instance_;
}

bool SceneManager::setupInstance()
{
	if (instance_ == nullptr) {
		instance_ = new SceneManager();
		return true;
	}

	return false;
}

void SceneManager::clean()
{
	instance_->cleanupScene();
	delete instance_->loader_;
	delete instance_;
}

void SceneManager::loadScene(const std::string& sceneName)
{
	//crea escena vacia
	currentScene_ = new Scene();
	currentScene_->setName(sceneName);
	//la llena de objetos
	loader_->loadEntities(sceneName, currentScene_);

	//json j = ResourceManager::getInstance()->getSceneFile(sceneName);
	//currentScene_->load(j);
}

void SceneManager::cleanupScene()
{
	currentScene_->clean();
	delete currentScene_; 
	currentScene_ = nullptr;
	WindowGenerator::getInstance()->getRenderWindow()->removeAllViewports();
}

SceneManager::SceneManager() {
	loader_ = new LoaderSystem();
	change_ = false;
}


void SceneManager::update()
{
	if (change_) {
		cleanupScene();
		loadScene(nextScene_);
		
		change_ = false;
		nextScene_ = "";
		
		PapagayoEngine::getInstance()->start();
	}
}

void SceneManager::changeScene(const std::string& sceneName)
{
	bool exist = false;
	int i = 0;
	while (i < sceneFiles_.size() && !exist) {
		exist = sceneFiles_[i] == sceneName;
		i++;
	}
	if (exist) {
		nextScene_ = sceneName;
		change_ = true;
	}
	else {
		throw std::runtime_error("ERROR: Scene: " + sceneName + " doesn't exist\n");	
	}
}

void SceneManager::createStartScene() {
	
	sceneFiles_ = loader_->loadScenes("Scenes/scenes.json");
	loadScene(sceneFiles_[0]);
}
