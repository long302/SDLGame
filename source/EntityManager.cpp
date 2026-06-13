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
		for (auto it = vec.begin(); it != vec.end(); it++)
		{
			if ((*it)->GetState() == EntityState::DEAD)
			{
				vec.erase(it);
				it--;
			}
		}
	}
	
	for (auto it = id_map.begin(); it != id_map.end(); it++ )
	{
		if ((*it).second->GetState() == EntityState::DEAD)
		{
			id_map.erase((*it).first);
			it--;
		}
	}
	return *this;
}

