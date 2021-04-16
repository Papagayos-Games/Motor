#pragma once


#include <json.hpp>
using json = nlohmann::json;

class Scene;
class Entity;

class LoaderSystem
{
public:
	void loadScenes(std::string fileName);
	void loadEntities(std::string fileName/*, Scene* scene*/);
	void loadComponents(json comps, Entity* entity);
	void readParameters(std::string dump, std::map<std::string, std::string>& params);
};

