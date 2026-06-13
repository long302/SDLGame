#include "EntityManager.h"


EntityManager& EntityManager::DeleteAllEntity()
{
	for (auto& pair : entities)
	{
		pair.second.clear();
	}
	id_map.clear();
	return *this;
}
EntityPointer EntityManager::AddEntity(EntityType type)
{
	entities[type].push_back(EntityPointer(new Entity));
	int pos = entities[type].size() - 1;
	entities[type][pos]->SetType(type);
	id_map[entities[type][pos]->GetId()] = entities[type][pos];
	return entities[type][pos];
}


EntityManager& EntityManager::DeleteEntityById(std::size_t id)
{
	if (id_map.find(id) == id_map.end())
	{
		std::cout << "No entity with id " << id << std::endl;
		return *this;
	}
	EntityPointer e = id_map[id];
	EntityType type = e->GetType();
	auto& vec = entities[type];
	vec.erase(std::remove(vec.begin(), vec.end(), e), vec.end());
	id_map.erase(id);
	return *this;
}

EntityManager& EntityManager::DeleteDeadEntity()
{

	for (auto& pair : entities)
	{
		auto& vec = pair.second;
		vec.erase(std::remove_if(vec.begin(), vec.end(), [](const EntityPointer& e) { return e->GetState() == EntityState::DEAD; }), vec.end());
	}
	std::erase_if(id_map, [](const auto& pair) { return pair.second->GetState() == EntityState::DEAD; });
	return *this;
}

