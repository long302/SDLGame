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
	static inline std::size_t id = 0;
	EntityState state{ EntityState::NONE };
	std::size_t m_id;
	ComponentMap components;
	EntityType type{EntityType::NONE};
public:
	Entity() { id++; m_id = id; }
	~Entity() ;

	template<typename N>
	std::shared_ptr<N> Get() 
	{
		//debuger
		if (components.find(N::type) == components.end())
		{
			std::cout << GetStringOf(type) << " didnt init " <<GetStringOf(N::type) << std::endl;
			__debugbreak();
			return nullptr;
		}
		if (strcmp(typeid(N).name(), typeid(*components[N::type]).name()) != 0)
		{
			std::cout << GetStringOf(type) << " doesnt have " << typeid(N).name() <<", must be "<< typeid(*components[N::type]).name()<< std::endl;
			__debugbreak();
			return nullptr;
		}
		//end debuger
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