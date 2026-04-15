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
class Component
{
private:
public:
	Component() = default;
	~Component() = default;

	virtual void Update() = 0;
};
class TestComponent: public Component
{
private:
	std::string name{ "Dog" };
public:
	void Update() override;

};