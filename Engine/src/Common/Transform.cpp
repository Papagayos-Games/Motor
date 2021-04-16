#include "Vector3.h"
#include "CommonManager.h"
#include "Transform.h"

Transform::Transform() : 
	Component(CommonManager::getInstance(), (int)CommonManager::CommonCmpId::TransId),
	_position(),
	_velocity(),
	_dimensions(),
	_rotation() 
{
}

Transform::Transform(Vector3 pos, Vector3 vel,Vector3 dim, Vector3 rotation) :
	Component(CommonManager::getInstance(), (int)CommonManager::CommonCmpId::TransId),
	_position(pos), //
	_velocity(vel), //
	_dimensions(dim),
	_rotation(rotation) //
{
}

Transform::Transform(std::map<std::string, std::string> params) : Component(CommonManager::getInstance(), (int)CommonManager::CommonCmpId::TransId)
{
	auto it = params.find("position");
	if (it != params.end())
		_position = Vector3(it->second);
	else
		_position = Vector3();
	if ((it = params.find("velocity")) != params.end())
		_velocity = Vector3(it->second);
	else
		_velocity = Vector3();
	if ((it = params.find("dimensions")) != params.end())
		_dimensions = Vector3(it->second);
	else
		_dimensions = Vector3(1,1,1);
	if ((it = params.find("rotation")) != params.end())
		_rotation = Vector3(it->second);
	else
		_rotation = Vector3();
}

Transform::~Transform() {
}

void Transform::init() {

}

void Transform::update() {

}

 Vector3 Transform::getPos() 
{
	return _position;
}

void Transform::setPos(const Vector3& pos)
{
	_position.set(pos);
}

void Transform::setPosX(double x)
{
	_position.setX(x);
}

void Transform::setPosY(double y)
{
	_position.setY(y);
}

void Transform::setPosZ(double z)
{
	_position.setZ(z);
}

Vector3 Transform::getRot() const
{
	return _rotation;
}

void Transform::setRot(Vector3 angle)
{
	_rotation = angle;
}

void Transform::setRotX(double x)
{
	_rotation.setX(x);
}

void Transform::setRotY(double y)
{
	_rotation.setY(y);
}

void Transform::setRotZ(double z)
{
	_rotation.setZ(z);
}

const Vector3& Transform::getVel() const
{
	return _velocity;
}

void Transform::setVel(const Vector3& vel)
{
	_velocity.set(vel);
}

void Transform::setVelX(double x)
{
	_velocity.setX(x);
}

void Transform::setVelY(double y)
{
	_velocity.setY(y);
}

void Transform::setVelZ(double z)
{
	_velocity.setZ(z);
}

Vector3 Transform::getDimensieons()
{
	return _dimensions;
}

void Transform::setDimensions(const Vector3 dim)
{
	_dimensions.set(dim);
}

void Transform::setDimX(double x)
{
	_dimensions.setX(x);
}

void Transform::setDimY(double y)
{
	_dimensions.setY(y);
}

void Transform::setDimZ(double z)
{
	_dimensions.setZ(z);
}

