#pragma once
#include"Component.h"
#include"Controller.h"

class AutoControl: public Component
{
private:
	std::vector<ControlState> state;
	int rand_nums{};
	int steps{};
public:
	static constexpr ComponentType type{ComponentType::CONTROL};
	AutoControl() {};
	~AutoControl() {};
	std::vector<ControlState>& GetState() { return state; }
	void Update() override;
};