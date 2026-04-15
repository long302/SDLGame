#pragma once
#include"Entity.h"

#define EntityPointer std::shared_ptr<Entity>
#define EntityVec std::vector<EntityPointer>
#define EntityMap std::map<EntityType, EntityVec>
class EntityManager 
{
private:
	EntityMap entities;
	EntityManager() = default;
public:
	~EntityManager() = default;
	EntityPointer AddEntity(EntityType type)
	{	
		entities[type].push_back(EntityPointer(new Entity));
		int pos = entities[type].size() - 1;
		entities[type][pos]->SetType(type);
		return entities[type][pos];
	}
	EntityVec& GetEntity(EntityType type) { return entities[type];}
	EntityMap& GetAllEntity() { return entities; }
	void DeleteEntity();
	static EntityManager& GetInstance()
	{
		static EntityManager instance;
		return instance;
	}
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
};
