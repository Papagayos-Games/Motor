#include "..\..\include\Graphics\RenderManager.h"
#include "..\..\include\Graphics\RenderManager.h"
#include "RenderManager.h"
#include "OgreContext.h"
#include <checkML.h>
#include "OgreRoot.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "Camera.h"
#include "LightComponent.h"
#include "PlaneComponent.h"

RenderManager* RenderManager::instance_ = nullptr;

RenderManager::RenderManager() : Manager(ManID::Render)
{
	ogreRoot_ = OgreContext::getInstance()->getOgreRoot();

	registerComponent("MeshComponent", (int)RenderCmpId::Mesh,[]() -> MeshComponent* { return new  MeshComponent(); });
	registerComponent("Camera", (int)RenderCmpId::Camera, []() -> Camera* { return new Camera(); });
	registerComponent("LightComponent", (int)RenderCmpId::Light, []() -> LightComponent* { return new LightComponent(); });
	registerComponent("PlaneComponent", (int)RenderCmpId::Plane, []() -> PlaneComponent* { return new PlaneComponent(); });
}

RenderManager::~RenderManager()
{
}

RenderManager* RenderManager::getInstance()
{
	return instance_;
}

bool RenderManager::setUpInstance() {
	if (!instance_) {
		try {
			instance_ = new RenderManager();
		}
		catch (...) {
			return false;
		}
	}
	return true;
}

void RenderManager::clean()
{
	instance_->destroyAllComponents();
}

void RenderManager::destroy()
{
	instance_->clean();
	delete instance_;
}

void RenderManager::start()
{
	for (Component* cmp : _compsList)
	{
		cmp->setUp();
	}
}

void RenderManager::update(float deltaTime)
{
	for (Component* cmp : _compsList)
	{
		cmp->update(deltaTime);
	}
	ogreRoot_->renderOneFrame();	//TODO: esto no lo esta lanzando el RenderManager

}
