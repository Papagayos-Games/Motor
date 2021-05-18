#include "..\..\include\LUA\LUAManager.h"
#include "..\..\include\LUA\LUAManager.h"
#include "LUAManager.h"
#include <iostream>

//physics
#include <Rigidbody.h>
#include <PhysicsManager.h>

//Papagayo
#include <Managers/SceneManager.h>
#include <Scene/Scene.h>

//common
#include <Vector3.h>
#include <Transform.h>
#include <Entity.h>
#include <CommonManager.h>

//input
#include <./Input/InputSystem.h>

//graphics
#include <MeshComponent.h>
#include <Camera.h>
#include <LightComponent.h>
#include <PlaneComponent.h>
#include <RenderManager.h>
#include <OgreContext.h>

//LUA
#include "LuaComponent.h"
#include <LuaBridge.h>

//
#include "LoaderSystem.h"

using namespace luabridge;

LUAManager* LUAManager::instance_ = nullptr;


bool LUAManager::CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK) {
		std::string err = lua_tostring(L, -1);
		std::cout << err << "\n";
		return false;
	}
	return true;
}

LUAManager::~LUAManager()
{
	lua_close(L);
	L = nullptr;
}

LUAManager* LUAManager::getInstance()
{
	return instance_;
}

bool LUAManager::setUpInstance()
{
	if (instance_ == nullptr) {
		try {
			instance_ = new LUAManager();
		}
		catch (...) {
			return false;
		}
	}
	return true;
}

void LUAManager::start()
{
	for (Component* cmp : _compsList)
	{
		cmp->setUp();
	}
}

void LUAManager::update()
{
	for (Component* cmp : _compsList)
	{
		cmp->update();
	}
}

void LUAManager::clean()
{
	instance_->destroyAllComponents();
}

void LUAManager::destroy() {
	instance_->clean();
	delete instance_;
}

//Aqui van todas las funciones y clases correspondientes 
void LUAManager::registerClassAndFunctions(lua_State* L) {

	getGlobalNamespace(L).beginClass<Entity>("Entity")
		.addFunction("getName", &Entity::getName)
		.endClass();

	getGlobalNamespace(L).beginClass<Vector3>("Vector3")
		.addConstructor<void (*) (float, float, float)>()
		.addConstructor<void (*) (const Vector3 &)>()
		.addProperty("x", &Vector3::x)
		.addProperty("y", &Vector3::y)
		.addProperty("z", &Vector3::z)
		.addFunction("add", &Vector3::operator+=)
		.addFunction("substract", &Vector3::operator-=)
		.addFunction("multiplyByNumber",&Vector3::operator*=)
		.addFunction("isEqual", &Vector3::operator==)
		.addFunction("normalize", &Vector3::normalize)
		.endClass();
	
	//input
	getGlobalNamespace(L).beginClass<InputSystem>("InputSystem")
		.addFunction("keyPressed", &InputSystem::isKeyDown)
		.addFunction("mouseButtonPressed", &InputSystem::clickEvent)
		.addFunction("getMouseX", &InputSystem::getMouseX)
		.addFunction("getMouseY", &InputSystem::getMouseY)
		.endClass();
	
	//common
	getGlobalNamespace(L).beginClass<Component>("Component")
		.addFunction("isActive", &Component::isActive)
		.addFunction("getEntity", &Component::getEntity)
		.endClass();

	
	getGlobalNamespace(L).deriveClass<Transform, Component>("Transform")
		.addFunction("getPosition", &Transform::getPos)
		.addFunction("setPosition", &Transform::setPos)
		.addFunction("getRotation", &Transform::getRot)
		.addFunction("setRotation", &Transform::setRot)
		.addFunction("getDimensions", &Transform::getDimensions)
		.addFunction("setDimensions", &Transform::setDimensions)
		.endClass();

	//phisics
	getGlobalNamespace(L).deriveClass<RigidBody, Component>("Rigidbody")
		.addFunction("setPosition", &RigidBody::setPosition)
		.addFunction("addForce1", &RigidBody::addForce)
		.addFunction("setGravity", &RigidBody::setGravity)
		.addFunction("addTorque",&RigidBody::addTorque)
		.addFunction("setGravity", &RigidBody::setGravity)
		.addFunction("setTrigger", &RigidBody::setTrigger)
		.addFunction("isTrigger", &RigidBody::isTrigger)
		.addFunction("setKinematic", &RigidBody::setKinematic)
		.addFunction("isKinematic", &RigidBody::isKinematic)
		.addFunction("setStatic", &RigidBody::setStatic)
		.addFunction("isStatic", &RigidBody::isStatic)
		.addFunction("setLinearVelocity",& RigidBody::setLinearVelocity)
		.addFunction("getLinearVelocity", &RigidBody::getLinearVelocity)
		.addFunction("onCollisionEnter", &RigidBody::onCollisionEnter)
		.addFunction("collidesWithTag", &RigidBody::collidesWithTag)
		.endClass();

	//graphics
	getGlobalNamespace(L).deriveClass<MeshComponent,Component>("Mesh")
		.addFunction("setActive", &MeshComponent::setActive)
		.addFunction("setMaterial", &MeshComponent::setMaterial)
		.endClass();

	getGlobalNamespace(L).deriveClass<Camera,Component>("Camera")
		.addFunction("setCameraPos", &Camera::setCameraPosition)
		.addFunction("getCameraPos", &Camera::getCameraPosition)
		.addFunction("setCameraDir", &Camera::setCameraDir)
		.addFunction("setBackgroundColor", &Camera::setBackgroundColor)
		.addFunction("setNearClipDistance", &Camera::setNearClipDistance)
		.addFunction("setFarClipDistance", &Camera::setFarClipDistance)
		.addFunction("getScreenCoordinates", &Camera::getScreenCoordinates)
		.endClass();

	getGlobalNamespace(L).deriveClass<LightComponent,Component>("Light")
		.addFunction("turnOn", &LightComponent::turnOn)
		.addFunction("turnOff", &LightComponent::turnOff)
		.addFunction("setColor", &LightComponent::setColor)
		.addFunction("setLightPower", &LightComponent::setLightPower)
		.addFunction("setCastShadow", &LightComponent::setCastShadow)
		.endClass();
	getGlobalNamespace(L).deriveClass<PlaneComponent, Component>("Plane")
		.addFunction("setMaterial", &PlaneComponent::setMaterial)
		.endClass();

	getGlobalNamespace(L).beginClass<OgreContext>("WindowGenerator")
		.addFunction("getWindowWidth", &OgreContext::getWindowWidth)
		.addFunction("getWindowHeight", &OgreContext::getWindowHeight)
		.endClass();


	getGlobalNamespace(L).beginClass<Scene>("Scene")
		.addFunction("clean", &Scene::clean)
		.addFunction("addEntity", &Scene::addEntity)
		.addFunction("setName", &Scene::setName)
		.addFunction("getName", &Scene::getName)
		.addFunction("getEntity", &Scene::getEntity)
		.endClass();		

	getGlobalNamespace(L).beginClass<LUAManager>("LuaManager")
		.addFunction("getEntity", &LUAManager::getEntity)
		.addFunction("getInputManager", &LUAManager::getInputManager)
		.addFunction("getLight", &LUAManager::getLightComponent)
		.addFunction("getRigidbody", &LUAManager::getRigidbody)
		.addFunction("getCamera", &LUAManager::getCamera)
		.addFunction("getPlane", &LUAManager::getPlaneComponent)
		.addFunction("getMesh", &LUAManager::getMeshComponent)
		.addFunction("getTransform", &LUAManager::getTransform)
		.addFunction("getLuaClass", &LUAManager::getLuaClass)
		.addFunction("instantiate", &LUAManager::instantiate)
		.addFunction("getOgreContext", &LUAManager::getOgreContext)
		.endClass();
}

bool LUAManager::reloadLuaScript(lua_State* L, const std::string& luafile) {
	int state = luaL_dofile(L, luafile.c_str());
	
	if (state != LUA_OK) {
		return false;
	}
	return true;
}

Entity* LUAManager::getEntity(std::string name)
{
	std::error_code errorCode;
	Entity* ent = SceneManager::getInstance()->getCurrentScene()->getEntity(name);
	return ent;
}


RigidBody* LUAManager::getRigidbody(Entity* ent)
{
	std::error_code errorCode;
	RigidBody* r = nullptr;
	if(ent->hasComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId))
		r = static_cast<RigidBody*>(ent->getComponent((int)ManID::Physics, (int)PhysicsManager::PhysicsCmpId::RigigbodyId));
	return r;
}

InputSystem* LUAManager::getInputManager()
{
	std::error_code errorCode;
	return InputSystem::getInstance();
}

MeshComponent* LUAManager::getMeshComponent(Entity* ent)
{
	std::error_code errorCode;
	MeshComponent* m = nullptr;
	if(ent->hasComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Mesh))
		m = static_cast<MeshComponent*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Mesh));
	return m;
}

PlaneComponent* LUAManager::getPlaneComponent(Entity* ent)
{
	std::error_code errorCode;
	PlaneComponent* m = nullptr;
	if(ent->hasComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Plane))
		m = static_cast<PlaneComponent*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Plane));
	return m;
}

LightComponent* LUAManager::getLightComponent(Entity* ent)
{
	std::error_code errorCode;
	LightComponent* m = nullptr;
	if(ent->hasComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Light))
		m = static_cast<LightComponent*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Light));
	return m;
}

Camera* LUAManager::getCamera(Entity* ent)
{
	std::error_code errorCode;
	Camera* m = nullptr;
	if (ent->hasComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Camera))
		m = static_cast<Camera*>(ent->getComponent((int)ManID::Render, (int)RenderManager::RenderCmpId::Camera));
	return m;
}

Transform* LUAManager::getTransform(Entity* ent)
{
	std::error_code errorCode;
	Transform* m = nullptr;
	if (ent->hasComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId))
		m = static_cast<Transform*>(ent->getComponent((int)ManID::Common, (int)CommonManager::CommonCmpId::TransId));
	return m;
}

luabridge::LuaRef LUAManager::getLuaClass(Entity* ent, const std::string& c_name)
{
	std::error_code errorCode;
	luabridge::LuaRef m = luabridge::LuaRef(L);//nil
	if(ent->hasComponent((int)ManID::LUA, enum_map_[c_name]))
		m = (static_cast<LuaComponent*>(ent->getComponent((int)ManID::LUA, enum_map_[c_name])))->getClass();
	return m;
}

Entity* LUAManager::instantiate(std::string prefabName)
{
	Entity* e = new Entity();
	LoaderSystem s;

	s.loadPrefabByName(prefabName, e);
	SceneManager::getCurrentScene()->addEntity(prefabName, e);
	e->start();
	return e;
}

void LUAManager::addRegistry(const std::string& compName)
{
	int id = registeredFiles;
	registerComponent(compName, registeredFiles, [compName, id]() -> LuaComponent* { return new LuaComponent(compName, id); });
	registeredFiles++;
}

OgreContext* LUAManager::getOgreContext()
{
	return OgreContext::getInstance();
}

lua_State* LUAManager::getLuaState() const
{
	return L;
}

void LUAManager::buildLuaEngine(const std::string& file) {
	// need check L
	luaL_openlibs(L);
	auto ok = reloadLuaScript(L, file);
	if (!ok) {
		lua_close(L);
		L = nullptr;
	}
}

LUAManager::LUAManager() : Manager(ManID::LUA), registeredFiles(0)
{
	//Registro de componentes
	registerComponent("default", registeredFiles++, []() -> LuaComponent* { return new LuaComponent(); });

	//Inicializacion del estado de LUA
	L = luaL_newstate();
	buildLuaEngine("LuaScripts/clases.lua");
	
	//Registro de las funciones
	if (L) {
		registerClassAndFunctions(L);
	}
	else throw std::exception("ERROR: LUA is not compiling correctly\n");
}