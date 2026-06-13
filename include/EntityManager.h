#pragma once
#include"Entity.h"

#define EntityPointer std::shared_ptr<Entity>
#define EntityVec std::vector<EntityPointer>
#define EntityMap std::unordered_map<EntityType, EntityVec>
#define EntityIdMap std::unordered_map<std::size_t, EntityPointer>
class EntityManager 
{
private:
	EntityMap entities;
	EntityIdMap id_map;
	EntityManager() = default;
public:
	~EntityManager() = default;
	EntityPointer AddEntity(EntityType type);

	EntityVec& GetEntity(EntityType type) { return entities[type];}
	EntityMap& GetAllEntity() { return entities; }
	
	EntityPointer GetEntityById(std::size_t id) { return id_map[id]; }
	EntityIdMap& GetAllEntityById() { return id_map; }

	EntityManager& DeleteAllEntity();
	EntityManager& DeleteEntityById(std::size_t id);
	EntityManager& DeleteDeadEntity();

	static EntityManager& GetInstance()
	{
		static EntityManager instance;
		return instance;
	}
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
};
