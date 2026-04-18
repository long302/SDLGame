#pragma once
#include"Texture.h"
#include"Sound.h"
//definition should move to cpp
namespace LoadData
{
	void AllTexture(SDL_Renderer* renderer)
	{
		TextureManager& tm = TextureManager::GetInstance();

		tm.AddTexture(EntityType::PLAYER, TextureType::NONE, renderer, "assets/image/idle.png", 2, 3);
		tm.AddTexture(EntityType::PLAYER, TextureType::RUN_RIGHT, renderer, "assets/image/Run.png", 2, 3);
		tm.AddTexture(EntityType::PLAYER, TextureType::RUN_LEFT, renderer, "assets/image/Run.png", 2, 3);
		tm.AddTexture(EntityType::PLAYER, TextureType::JUMP, renderer, "assets/image/idle.png", 2, 3);
		tm.AddTexture(EntityType::BULLET, TextureType::NONE, renderer, "assets/image/Laser.png", 1, 1);

		tm.AddTexture(EntityType::NORMAL_ENERMY, TextureType::NONE, renderer, "assets/image/Run.png", 2, 3);

		tm.AddTexture(EntityType::GROUND, TextureType::NONE, renderer, "assets/image/ground.png", 1, 1);
	}
	void AllAudio(MIX_Mixer* mixer)
	{
		AudioManager& am = AudioManager::GetInstance();
		am.SetMixer(mixer)->AddAudio(EntityType::NONE, AudioType::NONE, "assets/sound/tokyo.mp3");
		am.SetMixer(mixer)->AddAudio(EntityType::PLAYER, AudioType::SHOOT, "assets/sound/shot.wav");
		am.PlayAudio(EntityType::NONE, AudioType::NONE);
	}
}

