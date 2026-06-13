#pragma once
#include"Component.h"
#include"Event.h"
#include"Vec2d.h"
#include<vector>
enum class ControlState
{
	NONE,
	RUN_LEFT,
	RUN_RIGHT,
	JUMP,
	FALL,
	ATTACK,
	USING_SK1,
	USING_SK2,
	LOOT,
	REMOVE_WEAPON,
	SWAP_WEAPON
};
class Controller : public Component
{
private:
	std::vector<ControlState> state;

public: 
	constexpr static ComponentType type = ComponentType::CONTROL;
	Controller() { }
	~Controller() = default;

	 std::vector<ControlState>& GetState()  { return state; }
	 ComponentType GetType() override { return type; }
	void Update() override;

};