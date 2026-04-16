
#include"GameSystem.h"
#include<thread>
#include"SDL3_mixer/SDL_mixer.h"
TimeCalculate timer;

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	MIX_Init();

	SDL_AudioSpec spec{};
	spec.freq = 44100;
	spec.format = SDL_AUDIO_S32;
	spec.channels = 2;

	MIX_Mixer* mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK,&spec);
	
	AudioManager& am = AudioManager::GetInstance();
	am.SetMixer(mixer)->AddAudio(EntityType::NONE, AudioType::NONE, "assets/sound/tokyo.mp3");
	am.SetMixer(mixer)->AddAudio(EntityType::PLAYER, AudioType::SHOOT, "assets/sound/shot.wav");
	am.PlayAudio(EntityType::NONE, AudioType::NONE);
	SDL_Window* window = SDL_CreateWindow("InfinityBattle", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	int t=100;
	for(t=0;t<1;t++)
	{
		GameSystem::Spawn::Player( { 50.0f+static_cast<float>(t),50.0f + static_cast<float>(t) },renderer);
	}
	for (t = 0; t < 1; t++)
	{
		GameSystem::Spawn::NormalEnermy( { 50.0f + static_cast<float>(t),50.0f + static_cast<float>(t) }, renderer);
	}
	TextureManager& tm = TextureManager::GetInstance();
	tm.AddTexture(EntityType::BULLET, TextureType::NONE, renderer, "assets/image/Laser.png", 1, 1);
	bool end{false};
	int count = 0;
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

			}
		}

		SDL_RenderClear(renderer); 
		//Update here:
		GameSystem::Control::Update();
		GameSystem::HandleControl::Update();
		GameSystem::Physic::Update();
		GameSystem::Transform::Update();
		GameSystem::Collide::Update();
		GameSystem::Render::Update();
		GameSystem::Recall::Update();
		//
		SDL_RenderPresent(renderer);
		timer.SetPoint2();
		float time = timer.GetDurationMs();
		float fps = 60.0;
		if (time <1000.0/fps)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((long long)(1000.0/fps-time)));
		}
		timer.SetPoint2();
		std::cout << timer.GetDurationSec()<<"\n";
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;

}