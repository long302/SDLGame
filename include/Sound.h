#pragma once
#include"Component.h"
#include"Event.h"
enum class AudioType
{
	NONE, 
	SHOOT
};
class Audio
{
private:
	MIX_Audio* audio{ nullptr };
public:
	Audio() {};
	~Audio() {};

	bool Load(MIX_Mixer* mixer, const char* path);
	MIX_Audio* GetAudio() const { return audio; }
	Audio* Destroy();
};
class AudioManager
{
private:
	MIX_Mixer* mixer{ nullptr };
	std::map<EntityType, std::map<AudioType, Audio>> audios;
	AudioManager() {};
public:
	~AudioManager() {};
	AudioManager* SetMixer(MIX_Mixer* mixer) { this->mixer = mixer; return this; }
	bool AddAudio(EntityType e_type, AudioType au_type, const char* path);
	bool AddAudio(EntityType e_type, AudioType au_type, const std::string& path);
	Audio& GetAudio(EntityType e_type, AudioType au_type) { return audios[e_type][au_type]; };
	AudioManager* PlayAudio(EntityType e_type, AudioType au_type) 
	{
		MIX_PlayAudio(mixer, audios[e_type][au_type].GetAudio());
		return this;
	}
	static AudioManager& GetInstance()
	{
		static AudioManager instance;
		return instance;
	}
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	AudioManager* DestroyAudio(EntityType type);
};
;