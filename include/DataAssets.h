#pragma once
#include"Texture.h"
#include"Sound.h"
//definition should move to cpp
namespace LoadData
{	
	void AllTexture(SDL_Renderer* renderer)
	{
		TextureManager& tm = TextureManager::GetInstance();
		const std::string url = "assets/image/";
		tm.AddTexture(EntityType::PLAYER, TextureType::NONE, renderer, url + "Block.png", 1, 1);
		tm.AddTexture(EntityType::PLAYER, TextureType::RUN_RIGHT, renderer, url + "BlockRunRight.png", 1, 3);
		tm.AddTexture(EntityType::PLAYER, TextureType::RUN_LEFT, renderer, url + "BlockRunLeft.png", 1, 3);
		tm.AddTexture(EntityType::PLAYER, TextureType::JUMP, renderer, url + "Block.png", 1, 1);

		tm.AddTexture(EntityType::NORMAL_ENERMY, TextureType::NONE, renderer, url + "idle.png", 2, 3);

		tm.AddTexture(EntityType::GROUND, TextureType::NONE, renderer, url + "ground.png", 1, 1);

		tm.AddTexture(EntityType::BACK_GROUND, TextureType::NONE, renderer, url + "back_ground.png", 1, 1);

		tm.AddTexture(EntityType::LASER_GUN, TextureType::NONE, renderer, url + "Gun.png", 1, 1);
		tm.AddTexture(EntityType::ROCKET_GUN, TextureType::NONE, renderer, url + "RocketGun.png", 1, 1);
		tm.AddTexture(EntityType::BOMB_GUN, TextureType::NONE, renderer, url + "Gun.png", 1, 1);

		tm.AddTexture(EntityType::LASER_BULLET, TextureType::NONE, renderer, url + "Laser.png", 1, 1);
		tm.AddTexture(EntityType::LASER_BULLET, TextureType::DEAD, renderer, url + "bullet_dead.png", 1, 4);

		tm.AddTexture(EntityType::ROCKET_BULLET, TextureType::NONE, renderer, url + "Rocket.png", 1, 3);
		tm.AddTexture(EntityType::ROCKET_BULLET, TextureType::DEAD, renderer, url + "rocket_dead.png", 1, 5);

		tm.AddTexture(EntityType::BUTTON_UI, TextureType::NONE, renderer, url + "buttonUI.png", 1, 1);
	}
	void AllAudio(MIX_Mixer* mixer)
	{
		AudioManager& am = AudioManager::GetInstance();
		const std::string url = "assets/sound/";
		am.SetMixer(mixer)->AddAudio(EntityType::NONE, AudioType::NONE, url+ "tokyo.mp3");
		am.SetMixer(mixer)->AddAudio(EntityType::PLAYER, AudioType::SHOOT, url+"shot.wav");
		am.SetMixer(mixer)->AddAudio(EntityType::PLAYER, AudioType::SWAP_WEAPON, url + "swap_weapon.wav");
	}
}

