#pragma once
#include"EntityManager.h"

namespace GameSystem
{
	namespace Spawn
	{
		void Player(const Vec2d<float>& pos,SDL_Renderer* renderer);
		void NormalEnermy( const Vec2d<float>& pos, SDL_Renderer* renderer);
		void Bullet(const Vec2d<float>& pos, SDL_Renderer* renderer, const Vec2d<float>& veclocity);
	}
	namespace Recall
	{
		void Update();
	}
	namespace Control
	{
		void Update();
	}
	namespace HandleControl
	{
		 void  Update();
	}
	namespace Physic
	{
		void Update();
	} 
	namespace Transform
	{
		void Update();
	}
	namespace Collide
	{
		void Update();
	}
	namespace Assets
	{
		void Update();
	}
	namespace Render
	{
		void Update();
	}

}
//input(skill,....) ->move_object->Physic ->Transform -> Collider -> transform -> render

