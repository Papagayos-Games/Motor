#pragma once

#ifndef _GRAPHICS_CAMERA_H
#define _GRAPHICS_CAMERA_H

#include "Component.h"
#include <string>

class Vector3;
class Transform;

namespace Ogre {
	class Camera;
	class SceneNode;
	class Viewport;
}

enum class CameraType : int {
	STATIC = 0,
	DYNAMIC
};

class Camera : public Component
{
protected:
	//Nodo que contiene a esta camara
	Ogre::SceneNode* camNode_ = nullptr;
	Ogre::Camera* mCamera_ = nullptr;
	Ogre::Viewport* vp_ = nullptr;
	std::string name_ = "";
	Transform* tr_ = nullptr;
	CameraType type_ = CameraType::STATIC;

public:

	Camera();
	//	Constructora de la c�mara con un nodo padre
	//Camera(Ogre::SceneNode* parentNode,std::string name);
	
	virtual ~Camera();

	virtual void update(float deltaTime)override;
	virtual void setUp()override;
	virtual void load(const nlohmann::json& params) override;
	virtual void init()override;

	void setCameraPosition(const Vector3& newPos);
	void setCameraDir(Vector3& newDir);
	void setBackgroundColor(const Vector3& newColor ,float alpha);
	void setNearClipDistance(int distance);
	void setFarClipDistance(int distance);

	Vector3 getScreenCoordinates(const Vector3& iPoint);

	//const Vector3& getCameraPosition();
	const Vector3& getCameraPosition() const;
	//inline Ogre::Camera* getCamera();
	inline Ogre::Camera* getCamera() const;
};

#endif