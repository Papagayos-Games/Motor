#include "Graphics/Camera.h"
#include <OgreCamera.h>
#include "Graphics/OgreContext.h"
#include "Graphics/WindowGenerator.h"
#include "Ogre.h"
#include "OgreSceneNode.h"
#include "Vector3.h"

void Camera::init()
{
	mCamera_ = OgreContext::getInstance()->getSceneManager()->createCamera("MainCamera");
	mCamera_->setNearClipDistance(1);
	mCamera_->setFarClipDistance(10000);
	//mCamera_->lookAt(0, 0, -1);
	mCamera_->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	camNode_ = OgreContext::getInstance()->getSceneManager()->getRootSceneNode()->createChildSceneNode("mCam");
	camNode_->attachObject(mCamera_);

	camNode_->setPosition(0, 0, 1000);
	camNode_->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	Ogre::Viewport* vp = WindowGenerator::getInstance()->getRenderWindow()->addViewport(mCamera_);
	vp->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0, 1.0));//cambia el color del fondo
}

Camera::Camera(): Component(ecs::CmpId::Camera)
{
	init();

}

Camera::~Camera()
{

}

void Camera::update()
{
}

void Camera::setCameraPosition(Vector3 newPos)
{
	camNode_->setPosition(Ogre::Vector3(newPos.x, newPos.y, newPos.z));
}

//void Camera::setCameraDir(Vector3 newDir, Ogre::Node::TransformSpace transformSpace)
//{
//	newDir.normalize();
//	camNode_->lookAt(Ogre::Vector3(newDir.x, newDir.y, newDir.z), transformSpace);
//}

Vector3 Camera::getCameraPosition()
{
	Ogre::Vector3 aux = camNode_->getPosition();
	return Vector3(aux.x, aux.y, aux.z);
}

Ogre::Camera* Camera::getCamera() {
	return mCamera_;
}
