#include"MapMethods.h"

const float MaxDistance = 500.0f;
struct TempEntity 
{
	Transformer t;
	Imager img;
	Renderer r;
	Collider c;
};
enum class CreateMode
{
	NONE,
	CREATE,
	DELETE,

};

std::string Map::Create(SDL_Renderer* renderer,TTF_TextEngine* te)
{
	EntityManager::GetInstance().GetAllEntity().clear();
	std::cout << "start create map\n";
	std::cout << "Fix or add new (y to fix, n to add new, others to cancel)?\n";
	char input;
	std::cin >> input;
	std::string map_name;
	std::getline(std::cin, map_name);
	if(input == 'y')
	{

		std::cout << "Input your map name: "; 
		
		std::getline(std::cin, map_name);
		Map::Load( map_name, renderer, te);
		Map::LoadUI( map_name, renderer, te);
		std::cout << map_name << " loaded\n";
	}
	else if(input == 'n')
	{
		// Add new map
	}
	else
	{
		return "Map/MapName";
	}
	TimeCalculate timer;
	TempEntity temp;
	mode = GameMode::Creator;
	temp.r.SetRenderer(renderer);
	EntityType target_type = EntityType::PLAYER;
	EntityManager& em = EntityManager::GetInstance();
	TextureManager& tm = TextureManager::GetInstance();
	CreateMode cm{ CreateMode::NONE };
	EntityPointer target_e = nullptr;
	bool click{ false };
	double cd{300.0};
	bool end{};
	while (!end)
	{	
		SDL_RenderClear(renderer);
		click = false;
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
		if (key_board.GetState(Keys::KEY_C))
		{
			std::cout << "Create\n";
			cm = CreateMode::CREATE;
		}
		if (key_board.GetState(Keys::KEY_N))
		{
			std::cout << "None\n";
			cm = CreateMode::NONE;
		}
		if (key_board.GetState(Keys::KEY_D))
		{
			std::cout << "Delete\n";
			cm = CreateMode::DELETE;
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
		if (key_board.GetState(Keys::KEY_4))
		{
			target_type = EntityType::LASER_GUN;
		}
		if (key_board.GetState(Keys::KEY_5))
		{
			target_type = EntityType::BUTTON_UI;
		}
		timer.SetPoint2();
		if (timer.GetDurationMs()>cd && mouse.GetLeftState())
		{
			timer.SetPoint1();
			click = true;
		}
		temp.img.SetTexture(&tm.GetTexture(target_type, TextureType::NONE));
		temp.t.SetPos(mouse.GetRealPos());
		switch (target_type)
		{
		case EntityType::PLAYER:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, PlayerSize.x, PlayerSize.y);
			break;
		case EntityType::GROUND:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, GroundSize.x, GroundSize.y*2.0f);
			break;
		case EntityType::NORMAL_ENERMY:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, EnermySize.x, EnermySize.y);
			break;
		case EntityType::LASER_GUN:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, EquipSize.x, EquipSize.y);
			break;
		case EntityType::BUTTON_UI:
			temp.c.GetHitBox().SetRect(temp.t.GetPos().x, temp.t.GetPos().y, ButtonSize.x, ButtonSize.y);
			break;
		}
		if(cm==CreateMode::CREATE&&click)
		{
			switch (target_type)
			{
			case EntityType::PLAYER:
				GameSystem::Spawn::Player(temp.t.GetPos(), renderer);
				break;
			case EntityType::GROUND:
				GameSystem::Spawn::Ground(temp.t.GetPos(), renderer);
				break;
			case EntityType::NORMAL_ENERMY:
				GameSystem::Spawn::NormalEnermy(temp.t.GetPos(), renderer);
				break;
			case EntityType::LASER_GUN:
				GameSystem::Spawn::LaserGun(temp.t.GetPos(), renderer);
				break;
			case EntityType::BUTTON_UI:
				std::string str;
				float fontsize;
				std::cout << "Input your text: ";
				std::getline(std::cin, str);
				std::cout << "Input Your Font size: ";
				std::cin >> fontsize;
				std::string tmp;
				std::getline(std::cin, tmp);
				timer.SetPoint1();
				GameSystem::Spawn::ButtonUI(mouse.GetScreenPos(), str.c_str(),fontsize, renderer, te);
				std::cout << "Spawn a button\n";
				break;
			}
		}
		if (cm == CreateMode::DELETE && click)
		{
			for(auto& all_e: em.GetAllEntity())
			{
				for(auto& e: all_e.second)
				{
					if (e->Has<Collider>())
					{
						if (e->GetType() != EntityType::BUTTON_UI)
						{
							if (e->Get<Collider>()->GetHitBox().CollideDetectPoint(mouse.GetRealPos()))
							{
								e->SetState(EntityState::DEAD);
							}
						}
						else
						{
							if (e->Get<Collider>()->GetHitBox().CollideDetectPoint(mouse.GetScreenPos()))
							{
								e->SetState(EntityState::DEAD);
							}
						}
						
					}
					
				}
			}
		}
		if (cm == CreateMode::NONE && mouse.GetLeftState())
		{
			for (auto& all_e : em.GetAllEntity())
			{
				for (auto& e : all_e.second)
				{
					if (e->Has<Collider>())
					{
						if (e->GetType() != EntityType::BUTTON_UI)
						{
							if (e->Get<Collider>()->GetHitBox().CollideDetectPoint(mouse.GetRealPos()))
							{
								target_e = e;
							}
						}
						else
						{
							if (e->Get<Collider>()->GetHitBox().CollideDetectPoint(mouse.GetScreenPos()))
							{
								target_e = e;

							}
						}
					}
				}
				
			}
			if (target_e)
			{
				if (target_e->GetType() == EntityType::BUTTON_UI)
				{
					target_e->Get<TextTransformer>()->Increase(mouse.GetChange());

				}
				else
				{
					if (target_e->Has<TransformerWithAngle>())
					{
						target_e->Get<TransformerWithAngle>()->Increase(mouse.GetChange()/scale);
					}
					else if (target_e->Has<Transformer>())
					{
						target_e->Get<Transformer>()->Increase(mouse.GetChange()/scale);
					}
					else
					{
						std::cout << "This entity has no transformer\n";
					}
				}
				
			}
		}
		
		if (target_e)
		{
			if (target_e->GetType() == EntityType::BUTTON_UI)
			{
				if (key_board.GetState(Keys::KEY_Z))
				{
					target_e->Get<Text>()->SetFont("C:\\Windows\\Fonts\\arial.ttf", target_e->Get<Text>()->GetFontSize()-1)->SetText(target_e->Get<Text>()->GetText());
				}
				if (key_board.GetState(Keys::KEY_X))
				{
					target_e->Get<Text>()->SetFont("C:\\Windows\\Fonts\\arial.ttf", target_e->Get<Text>()->GetFontSize() + 1)->SetText(target_e->Get<Text>()->GetText());
				}
				if ((target_e->Get<Collider>()->GetHitBox().GetRect().GetMidPos() - mouse.GetScreenPos()).Length() > MaxDistance/2.0f)
				{
					target_e = nullptr;
				}
				
			}
			else
			{
				if ((target_e->Get<Collider>()->GetHitBox().GetRect().GetMidPos() - mouse.GetRealPos()).Length() > MaxDistance)
				{
					target_e = nullptr;
				}
			}
			
		}
		GameSystem::Recall::Update();
		GameSystem::Transform::Update();
		GameSystem::Collide::Update();
		GameSystem::Assets::Update();
		GameSystem::Render::Update();

		temp.r.SetDstRect({ (temp.t.GetPos().x - g_pos.x) * scale,(temp.t.GetPos().y - g_pos.y) * scale,temp.c.GetHitBox().GetRect().w *scale,temp.c.GetHitBox().GetRect().h * scale })->SetTexture(temp.img.GetTexture());
		if (cm == CreateMode::CREATE) temp.r.Update();
		SDL_RenderPresent(renderer);
	}
	char save;
	std::cout << "Do you want to save the map? (Y/N): "; 
	std::cin >> save;
	if(save=='Y' || save=='y')
	{	
		if (input == 'y')
		{
			Save( map_name);
			return map_name;
		}
		else
		{
			std::string file_name;
			std::cout << "Input your file name: ";
			std::getline(std::cin >> std::ws, file_name);
			if (FileExists( file_name))
			{
				std::cout << "File exists\n";

			}
			else
			{
				Save( file_name);
			}
			return file_name;
		}
		
	}
	else
	{
		std::cout << "Map not saved.\n";
		return "Map/MapName";
	}

}
void ltrim(std::string& s)
{
	s.erase(
		s.begin(),
		std::find_if(s.begin(), s.end(),
			[](unsigned char ch)
			{
				return !std::isspace(ch);
			})
	);
}
void Map::Save(const std::string& file_name)
{
	std::cout << "Save map:" << file_name << std::endl;
	std::ofstream write_file(file_name);
	EntityManager& em = EntityManager::GetInstance();
	for (auto& all : em.GetAllEntity())
	{
		write_file << GetStringOf(all.first)<<std::endl;
		write_file << all.second.size()<<std::endl;

		for (auto& e : all.second)
		{
			if (e->Has<TransformerWithAngle>())
			{
				write_file << e->Get<TransformerWithAngle>()->GetPos().x << " " << e->Get<TransformerWithAngle>()->GetPos().y << " " << e->Get<TransformerWithAngle>()->GetAngle()<<" ";
			}
			else if (e->Has<TextTransformer>())
			{
				write_file << e->Get<TextTransformer>()->GetPos().x << " " << e->Get<TextTransformer>()->GetPos().y << " ";
			}
			else if (e->Has<Transformer>())
			{
				write_file << e->Get<Transformer>()->GetPos().x << " " << e->Get<Transformer>()->GetPos().y<<" ";
			}
			if (e->Has<Text>())
			{
				write_file << e->Get<Text>()->GetFontSize() << " " << e->Get<Text>()->GetText();		
			}
			write_file << std::endl;
		}

	}
	std::cout << "Save complete\n";
	em.GetAllEntity().clear();
	write_file.close();
}

void Map::Load(const std::string& file_name,SDL_Renderer* renderer,TTF_TextEngine* te)
{

	EntityManager::GetInstance().GetAllEntity().clear();
	mode = GameMode::Player;
	std::cout << "Load map " << file_name << std::endl;
	GameSystem::Spawn::BackGround({ -2 * WIDTH,-1.0f * HEIGHT }, renderer);
	std::ifstream read_file{file_name};
	std::string tmp{};
	int nums;
	float x, y, font_size{};
	std::string text{};
	while (std::getline(read_file, tmp))
	{
		std::cout << tmp << std::endl;
		if (tmp.size() >= 10)
		{
			if (tmp.substr(0, 10) == "EntityType")
			{
				if (tmp == "EntityType::BUTTON_UI")
				{
					continue;
				}
				read_file >> nums;
				std::cout << nums << std::endl;

				for (int i = 0;i < nums;i++)
				{
					read_file >> x;
					read_file >> y;
					std::cout << x<<" "<<y<<" ";
					//if (tmp == "EntityType::BUTTON_UI")
					//{
					//	read_file >> font_size;
					//	std::getline(read_file, text);
					//	ltrim(text);
					//	std::cout << font_size <<" " << text;
					//}
					std::cout << std::endl;
					if (tmp == GetStringOf(EntityType::PLAYER)) GameSystem::Spawn::Player({x,y}, renderer);
					if (tmp == GetStringOf(EntityType::NORMAL_ENERMY)) GameSystem::Spawn::NormalEnermy({x,y}, renderer);
					if (tmp == GetStringOf(EntityType::GROUND)) GameSystem::Spawn::Ground({x,y}, renderer);
					if (tmp == GetStringOf(EntityType::BACK_GROUND)) GameSystem::Spawn::BackGround({x,y}, renderer);
					if (tmp == GetStringOf(EntityType::BUTTON_UI)) GameSystem::Spawn::ButtonUI({ x,y }, text.c_str(), font_size, renderer, te);
					if (tmp == GetStringOf(EntityType::EQUIPMENT)) GameSystem::Spawn::LaserGun({ x,y }, renderer);
				}
				//if (tmp != "EntityType::BUTTON_UI")
					std::getline(read_file, tmp);
			}
		}
	}
	read_file.close();
}

void Map::LoadUI(const std::string& file_name, SDL_Renderer* renderer, TTF_TextEngine* te)
{
	EntityManager& em = EntityManager::GetInstance();
	GameSystem::Spawn::BackGround({ -2 * WIDTH,-1.0f * HEIGHT }, renderer);
	std::string temp;
	std::ifstream read_file{ file_name };
	while (std::getline(read_file, temp))
	{
		if (temp == "EntityType::BUTTON_UI")
		{
			int nums;
			read_file >> nums;
			float x, y, font_size{};
			std::string text;
			for (int i = 0; i < nums; i++)
			{
				read_file >> x >> y >> font_size;
				std::getline(read_file, text);
				ltrim(text);
				GameSystem::Spawn::ButtonUI({ x,y }, text.c_str(), font_size, renderer, te);
			}
		}
	}


}

void Map::Update(SDL_Renderer* renderer, TTF_TextEngine* te)
{
	EntityManager& em = EntityManager::GetInstance();
	Vec2d<float> b_pos{ 100.0f,100.0f };
	for (std::string m : getFileNames("Map/"))
	{
		if (b_pos.x > WIDTH)
		{
			b_pos.x = 100.0f;
			b_pos.y += 100.0f;
		}
		GameSystem::Spawn::ButtonUI(b_pos, m.c_str(), 30.0f, renderer, te);
		auto& btn = em.GetEntity(EntityType::BUTTON_UI).back();
		b_pos += {btn->Get<Collider>()->GetHitBox().GetRect().w, 0.0f };

	}
	GameSystem::Spawn::ButtonUI({ 1393.0f ,680.0f }, "Back", 30.0f, renderer, te);
	Save("ViewMap/Load");
	em.DeleteAllEntity();
}
