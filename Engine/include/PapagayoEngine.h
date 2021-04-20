#pragma once

#include <map>
#include <string>
#ifdef _DEBUG
#include "checkML.h"
#endif
class Manager;

class PapagayoEngine {
public:
	~PapagayoEngine();
	static PapagayoEngine* getInstance();
	static bool setupInstance(const std::string& appName);
	static void clean();
	void run();
	std::map<std::string, Manager*> getManagers();
	
private:
	static PapagayoEngine* instance_;
	std::string appName_;
	std::map<std::string, Manager*> manRegistry_;
	bool running_ = true;

	PapagayoEngine(const std::string& appName);
	void init();
	void update();
	void pollEvents();


};