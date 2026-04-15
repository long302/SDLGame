#include"Sound.h"

bool Audio::Load(MIX_Mixer* mixer, const char* path)
{
	audio = MIX_LoadAudio(mixer, path, false);
	if (!audio)
	{
		std::cout << "Load Audio: " << path << " Fail\n";
		return false;
	}
	return true;
}
Audio* Audio::Destroy()
{
	MIX_DestroyAudio(audio);
	return this;
}

AudioManager* AudioManager::DestroyAudio(EntityType type)
{
	for (auto& au : audios[type])
	{
		au.second.Destroy();
	}
	audios[type].clear();
	return this;
}

bool AudioManager::AddAudio(EntityType e_type, AudioType au_type, const char* path)
{
	if (!mixer) std::cout << "Mixer is null\n";

	audios[e_type][au_type].Load(mixer, path);
	return true;
}
