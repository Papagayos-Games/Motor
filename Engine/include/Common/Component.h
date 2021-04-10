#pragma once
#include <math.h>
#include "ecs.h"

class Component {
protected:
	ecs::CmpId id;   // identificador del tipo de componente
	bool active;

	virtual void init() = 0;
public:
	//constructor
	Component(ecs::CmpId id);
	virtual ~Component();


	void setId(ecs::CmpId id) {
		id = id;
	}

	ecs::CmpId getId() const {
		return id;
	}

	virtual void update() = 0;

	bool isActive();
	void setActive(bool act);
};