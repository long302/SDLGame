#include "Transformer.h"

void Transformer::Update()
{
	if (pos.y >= 500)
	{
		pos.y = 500;
		on_ground = true;
	}
	else
	{
		on_ground = false;
	}
}
