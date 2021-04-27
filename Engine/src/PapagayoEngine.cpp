#include "PapagayoEngine.h"

#include <stdexcept>
#include <iostream>

#include "Managers/SceneManager.h"

#include "Graphics/OgreContext.h"

#include "Input/InputSystem.h"

//pruebas
#include "Graphics/Camera.h"
#include "Graphics/MeshComponent.h"
#include "Graphics/LightComponent.h"
#include "OgreRoot.h"
#include "Entity.h"
#include "Transform.h"
#include "CommonManager.h"
#include "Graphics/RenderManager.h"
#include "Vector3.h"
#include "LoaderSystem.h"

#include "OgrePlane.h"
#include "Graphics/PlaneComponent.h"
#include "Physics/PhysicsManager.h"

PapagayoEngine* PapagayoEngine::instance_ = nullptr;

PapagayoEngine::PapagayoEngine(const std::string& appName) : appName_(appName) {
}

PapagayoEngine::~PapagayoEngine()
{
}

PapagayoEngine* PapagayoEngine::getInstance()
{
	if (instance_ == nullptr)
		if (!setupInstance("PAPAGAYO ENGINE"))
			throw "ERROR: PapagayoEngine couldn't be created\n";
	return instance_;
}

bool PapagayoEngine::setupInstance(const std::string& appName)
{
	if (instance_ == nullptr) {
		instance_ = new PapagayoEngine(appName);
		return true;
	}

	return false;
}

void PapagayoEngine::clean()
{
	// se borrarian todos los managers del motor
	PhysicsManager::getInstance()->clean();
	SceneManager::getInstance()->clean();
	OgreContext::getInstance()->clean();
	//RenderManager::getInstance()->clean();
	InputSystem::getInstance()->clean();

	delete instance_;
}

void PapagayoEngine::init()
{
	try { OgreContext::setupInstance("PAPAGAYO ENGINE"); }
	catch (const std::exception & e)
	{
		throw std::runtime_error("OgreContext init fail \n" + (std::string)e.what() + "\n");
	}
	
	try { SceneManager::setupInstance(); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("SceneManager init fail \n" + (std::string)e.what() + "\n");
	}

	manRegistry_["Physics"] = PhysicsManager::getInstance();
	manRegistry_["Common"] = CommonManager::getInstance();
	manRegistry_["Render"] = RenderManager::getInstance();

	LoaderSystem loader;
#pragma region TOERASE
	OgreContext::getInstance()->setSkyPlane("SkyPlaneMat", Ogre::Plane(Ogre::Vector3::UNIT_Z, -70), 10, 10, 4.0);
#pragma endregion

	PhysicsManager::getInstance()->init(Vector3(0.0, -9.8, 0.0));
	RenderManager::getInstance()->start();
	PhysicsManager::getInstance()->start();
}

void PapagayoEngine::update()
{
	try {
		PhysicsManager::getInstance()->update();
		RenderManager::getInstance()->update();
		InputSystem::getInstance()->handleInput();
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error("Fallo de renderizado \n" + (std::string)e.what() + "\n");
	}

}

void PapagayoEngine::run() {
	init();
	//running_ = false;
	// ciclo principal de juego
	while (running_) {
		update();
	}
}

std::map<std::string, Manager*> PapagayoEngine::getManagers()
{
	return manRegistry_;
}
