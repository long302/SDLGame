#pragma once
#include<memory>
#include<vector>
#include<map>
#include<iostream>
#include"Controller.h"
#include"Movement.h"
#include"Renderer.h"
#include"Transformer.h"
#include"Physics.h"
#include"Collider.h"
#include"AutoControl.h"
#include"Sound.h"
#include"BulletController.h"
#define ComponentPointer std::shared_ptr<Component>
#define ComponentMap  std::map<ComponentType, ComponentPointer> 


class EntityManager;
class Entity
{
private:
	static inline unsigned int id = 0;
	EntityState state{ EntityState::NONE };
	unsigned int m_id;
	ComponentMap components;
	EntityType type{EntityType::NONE};
public:
	Entity() { id++; m_id = id; }
	~Entity() = default;

	template<typename N>
	std::shared_ptr<N> Get() 
	{
		if (components.find(N::type) == components.end())
		{
			__debugbreak();
			return nullptr;
		}
		return std::dynamic_pointer_cast<N>(components[N::type]); 
	}
	int GetId() const { return m_id; }
	Entity* SetType(EntityType t) { type = t; return this; }
	Entity* SetState(EntityState es) { state = es; return this; }
	EntityType GetType() { return type; }
	EntityState GetState() { return state; }
	template<typename N>
	Entity* Add()
	{
		components[N::type] = ComponentPointer(new N);
		return this;
	}
	friend EntityManager;
};