#pragma once
#include<string>
#include<iostream>
#include<SDL3/SDL.h>
#include<SDL3_image/SDL_image.h>
#include"Vec2d.h"
enum class ComponentType
{
	CONTROL,
	TRANSFORM,
	COLLIDE,
	LOGIC,
	IMAGE,
	RENDER,
	PHYSIC
};
constexpr std::string_view GetStringOf(ComponentType type)
{
	switch (type)
	{
	case ComponentType::COLLIDE:  return "ComponentType::COLLIDE";
	case ComponentType::CONTROL: return "ComponentType::CONTROL";
	case ComponentType::TRANSFORM:  return "ComponentType::TRANSFORM";
	case ComponentType::LOGIC: return "ComponentType::LOGIC";
	case ComponentType::IMAGE: return "ComponentType::IMAGE";
	case ComponentType::RENDER: return "ComponentType::RENDER";
	case ComponentType::PHYSIC: return "ComponentType::PHYSIC";
	default: return "Unknown";
	}
}
class Component
{
private:
public:
	Component() = default;
	virtual ~Component() {};

	virtual void Update() = 0;
};
class TestComponent: public Component
{
private:
	std::string name{ "Dog" };
public:
	void Update() override;

};