#include"MapMethods.h"
struct TempEntity 
{
	Transformer t;
	Imager img;
	Renderer r;
	Collider c;
};

void Map::Create(SDL_Renderer* renderer)
{
	TimeCalculate timer;
	TempEntity temp;
	temp.r.SetRenderer(renderer);
	EntityType target_type = EntityType::PLAYER;
	EntityManager& em = EntityManager::GetInstance();
	TextureManager& tm = TextureManager::GetInstance();
	bool create{};
	double cd{300.0};
	bool end{};
	while (!end)
	{
		SDL_RenderClear(renderer);
		create = false;
		mouse.Update();
		SDL_PollEvent(&event);
		
		if (key_board.GetState(Keys::KEY_0))
		{
			end = true;
		}
		if (key_board.GetState(Keys::KEY_1))
		{
			target_type = EntityType::PLAYER;
		}
		if (key_board.GetState(Keys::KEY_2))
		{
			target_type = EntityType::NORMAL_ENERMY;
		}
		if (key_board.GetState(Keys::KEY_3))
		{
			target_type = EntityType::GROUND;
		}
		timer.SetPoint2();
		if (timer.GetDurationMs()>cd && mouse.GetLeftState())
		{
			timer.SetPoint1();
			create = true;
		}
		temp.img.SetTexture(&tm.GetTexture(target_type, TextureType::NONE));
		temp.t.SetPos(mouse.GetPos());
		
		switch (target_type)
		{
		case EntityType::PLAYER:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, 100, 100);
			if (create)
			{
				GameSystem::Spawn::Player(temp.t.GetPos()+ g_pos, renderer);
			}
			break;
		case EntityType::GROUND:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, 400, 100);
			if (create)
			{
				GameSystem::Spawn::Ground(temp.t.GetPos() + g_pos, renderer);
				std::cout << "spawn an Ground\n";
			}
			break;
		case EntityType::NORMAL_ENERMY:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x , temp.t.GetPos().y, 100, 100);
			if (create)
			{
				GameSystem::Spawn::NormalEnermy(temp.t.GetPos() + g_pos, renderer);
			}
			break;
		}
	
		GameSystem::Transform::Update();
		GameSystem::Assets::Update();
		GameSystem::Render::Update();

		temp.r.SetDstRect({ temp.t.GetPos().x,temp.t.GetPos().y,temp.c.GetHitBox().GetRect().w,temp.c.GetHitBox().GetRect().h })->SetTexture(temp.img.GetTexture());
		temp.r.Update();
		
		SDL_RenderPresent(renderer);
		
	}
	

}
void Map::Load()
{

}