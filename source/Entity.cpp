#include "Entity.h"

Entity::~Entity()
{
	components.clear();
	//std::cout << m_id << " Clear components\n";
			
}
