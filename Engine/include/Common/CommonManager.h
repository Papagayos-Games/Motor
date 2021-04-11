#pragma once

#ifndef _COMMON_COMMANAGER_H
#define _COMMON_COMMANAGER_H

#include "Manager.h"

class CommonManager: public Manager {
private:
	static CommonManager* _instance;

	CommonManager();
	~CommonManager();
public:
	enum class CommonCmpId : int {
		TransId = 0,
		LastCommonCmpId
	};

	static CommonManager* getInstance();

	void addComponent(Entity* ent, int compId);
	void start();
	void update();
};

#endif 