#include"MapMethods.h"
#include<thread>
#include"SDL3_ttf/SDL_ttf.h"
#include"DataAssets.h"
#include"UISystem.h"
//Create -> Save; Load-> PLayGame        
/*
ui:
1. create button
2. create view 
3. UI system
view_vector 
ViewType
*/
bool InitSDL();
MIX_Mixer* CreateSDLMixer();
void PlayGame(SDL_Renderer* renderer, TTF_TextEngine* engine);
void ShowUI(SDL_Renderer* renderer, TTF_TextEngine* engine);
int main()
{
	if (!InitSDL()) return 0;
	MIX_Mixer* mixer = CreateSDLMixer();
	LoadData::AllAudio(mixer);

	SDL_Window* window = SDL_CreateWindow("Infinity Battle", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	TTF_TextEngine* engine = TTF_CreateRendererTextEngine(renderer);
	LoadData::AllTexture(renderer);
	Map::Update(renderer, engine);
	Map::LoadUI("ViewMap/Home", renderer, engine);
	PlayGame(renderer, engine);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	return 0;

}
bool InitSDL()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_AUDIO);
	MIX_Init();
	TTF_Init();
	return true;
}
MIX_Mixer* CreateSDLMixer()
{
	SDL_AudioSpec spec{};
	spec.freq = 44100;
	spec.format = SDL_AUDIO_S32;
	spec.channels = 2;
	return MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
}
void PlayGame(SDL_Renderer* renderer, TTF_TextEngine* engine)
{
	GameSystem::Spawn::LaserGun({ 400.0f,300.0f }, renderer);
	GameSystem::Spawn::RocketGun({ 1000.0f,300.0f }, renderer);
	GameSystem::Spawn::NormalEnermy({ 200.0f,300.0f }, renderer);
	GameSystem::Spawn::NormalEnermy({ 200.0f,300.0f }, renderer);
	GameSystem::Spawn::NormalEnermy({ 200.0f,300.0f }, renderer);
	GameSystem::Spawn::NormalEnermy({ 200.0f,300.0f }, renderer);
	TimeCalculate timer;
	bool end{ false };
	scale = 1;
	mode = GameMode::Player;
	while (!end)
	{
		timer.SetPoint1();
		mouse.Update();
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				end = true;
				return;
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
					if (scale < 0.2) scale = 0.2;
					if (scale > 2.0) scale = 2.0;
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
		GameSystem::Equip::Update();
		GameSystem::Render::Update();
		GameSystem::Recall::Update();
		UISystem::Update(renderer, engine);
		//
		SDL_RenderPresent(renderer);
		timer.SetPoint2();
		float time = timer.GetDurationMs();
		float fps = 60.0;
		if (time < 1000.0 / fps)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((long long)(1000.0 / fps - time)));
		}
		timer.SetPoint2();
		//std::cout << mouse.GetScreenPos().x << " " << mouse.GetScreenPos().y << std::endl;
		//std::cout << timer.GetDurationSec()<<"\n";
	}
}
