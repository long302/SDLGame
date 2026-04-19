#include"MapMethods.h"
#include<thread>
#include"SDL3_mixer/SDL_mixer.h"
#include"SDL3_ttf/SDL_ttf.h"
#include"DataAssets.h"
TimeCalculate timer;

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	MIX_Init();
	TTF_Init();
	SDL_AudioSpec spec{};
	spec.freq = 44100;
	spec.format = SDL_AUDIO_S32;
	spec.channels = 2;
	MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
	LoadData::AllAudio(mixer);
	SDL_Window* window = SDL_CreateWindow("InfinityBattle", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	LoadData::AllTexture(renderer);
	float t = 100;
	for (t = 0;t < 1;t++)
	{
		GameSystem::Spawn::Player({ 50.0f + t,50.0f + t }, renderer);
	}
	for (t = 0; t < 1; t++)
	{
		GameSystem::Spawn::NormalEnermy({ 50.0f + t,50.0f + t }, renderer);
	}
	for (t = 0; t < 10; t++)
	{
		GameSystem::Spawn::Ground({ t * 300.0f,500.0f }, renderer);
	}
	for (t = 0; t < 1; t++)
	{
		GameSystem::Spawn::Ground({ t * 400.0f,250.0f }, renderer);
	}
	int choosen{};
	std::cin >> choosen;
	if (choosen==1)
	{
		Map::Create(renderer);
	}
	bool end{false};
	Map::Load();
	while (!end)
	{
		timer.SetPoint1();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				end = true;
				return 0;
			}
			else
			{
				if (event.type == SDL_EVENT_MOUSE_WHEEL)
				{
					const Vec2d<float> old_pos = mouse.GetRealPos();
					int y = event.wheel.y;
					if (y > 0)
					{
						scale += 0.1;
					}
					else if (y < 0)
					{
						scale -= 0.1;
					}
					if (scale < 0.1) scale = 0.1;
					g_pos = old_pos - ((mouse.GetScreenPos() / scale));
				}
			}
		}

		SDL_RenderClear(renderer); 
		//Update here:
		GameSystem::Control::Update();
		GameSystem::HandleControl::Update();
		GameSystem::Physic::Update();
		GameSystem::Transform::Update();
		GameSystem::Collide::Update();
		GameSystem::Assets::Update();
		GameSystem::Render::Update();
		GameSystem::Recall::Update();
		//
		SDL_RenderPresent(renderer);
		timer.SetPoint2();
		float time = timer.GetDurationMs();
		float fps = 60.0;
		if (time <1000.0/fps)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((long long)(1000.0 / fps - time)));
		}
		timer.SetPoint2();
		//std::cout << timer.GetDurationSec()<<"\n";
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;

}