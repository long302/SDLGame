#pragma once
#include"Component.h"
#include<vector>

class Equipments : public Component
{
private:
	int current_id{ -1 };
	std::vector<int> ids;
public:
	static constexpr ComponentType type = ComponentType::EQUIP;
	Equipments() {};
	~Equipments() {};
	
	Equipments* SetCurrentId(int id) { current_id = id; return this; }
	Equipments* Loot(int id) { ids.push_back(id); return this; }

	ComponentType GetType() override { return type; }
	int GetCurrentId() const { return current_id; }
	bool CanUse() 
	{
		if (current_id >= 0) return true;
		else return false;
	}
	std::vector<int>& GetIds() { return ids; }
	void Update() override;
};



