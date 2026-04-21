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
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_MOUSE_WHEEL)
			{	
				int y = event.wheel.y; 
				if (y > 0)
				{
					scale += 0.1;
				}
				else if (y < 0)
				{
					scale -= 0.1;
				}
				if (scale < 0.2) scale = 0.2;
				if (scale > 2.0) scale = 2.0;
				g_pos = mouse.GetRealPos() - ((mouse.GetScreenPos() / scale));
			}
		}
		
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
		temp.t.SetPos(mouse.GetRealPos());
		
		switch (target_type)
		{
		case EntityType::PLAYER:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, 100, 100);
			if (create)
			{
				GameSystem::Spawn::Player(temp.t.GetPos(), renderer);
			}
			break;
		case EntityType::GROUND:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, 400, 200);
			if (create)
			{
				GameSystem::Spawn::Ground(temp.t.GetPos() , renderer);
			}
			break;
		case EntityType::NORMAL_ENERMY:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x , temp.t.GetPos().y, 100, 100);
			if (create)
			{
				GameSystem::Spawn::NormalEnermy(temp.t.GetPos() , renderer);
			}
			break;
		}
	
		GameSystem::Transform::Update();
		GameSystem::Assets::Update();
		GameSystem::Render::Update();

		temp.r.SetDstRect({ (temp.t.GetPos().x - g_pos.x) * scale,(temp.t.GetPos().y - g_pos.y) * scale,temp.c.GetHitBox().GetRect().w *scale,temp.c.GetHitBox().GetRect().h * scale })->SetTexture(temp.img.GetTexture());
		temp.r.Update();
		SDL_RenderPresent(renderer);	
	}
}

void Map::Save(const std::string& file_name)
{
	std::ofstream write_file(file_name);
	EntityManager& em = EntityManager::GetInstance();
	for (auto& all : em.GetAllEntity())
	{
		write_file << GetStringOf(all.first)<<std::endl;
		write_file << all.second.size()<<std::endl;

		for (auto& e : all.second)
		{
			write_file << e->Get<Transformer>()->GetPos().x << " " << e->Get<Transformer>()->GetPos().y << std::endl;
		}
	}
	em.GetAllEntity().clear();
	write_file.close();
}

void Map::Load(const std::string& file_name,SDL_Renderer* renderer)
{
	EntityManager::GetInstance().GetAllEntity().clear();
	std::ifstream read_file{file_name};
	std::string tmp{};
	int nums;
	float x, y;
	while (std::getline(read_file, tmp))
	{
		std::cout << tmp << std::endl;
		if (tmp.size() >= 10)
		{
			if (tmp.substr(0, 10) == "EntityType")
			{
				read_file >> nums;
				std::cout << nums << std::endl;
				for (int i = 0;i < nums;i++)
				{
					read_file >> x;
					read_file >> y;
					std::cout << x<<" "<<y << std::endl;
					if (tmp == GetStringOf(EntityType::PLAYER)) GameSystem::Spawn::Player({x,y}, renderer);
					if (tmp == GetStringOf(EntityType::NORMAL_ENERMY)) GameSystem::Spawn::NormalEnermy({x,y}, renderer);
					if (tmp == GetStringOf(EntityType::GROUND)) GameSystem::Spawn::Ground({x,y}, renderer);
					if (tmp == GetStringOf(EntityType::BACK_GROUND)) GameSystem::Spawn::BackGround({x,y}, renderer);
				}
				std::getline(read_file, tmp);
			}
		}
	}
	read_file.close();
}
