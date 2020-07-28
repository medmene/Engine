#pragma once
#include "include/Core.h"


class Resource;

class SoundManager
{
	struct Sound
	{
		Sound(Resource* res, Mix_Music* music);
		Resource	* m_res;
		Mix_Music	* m_music;
	};
public:
	static SoundManager * instance();
	~SoundManager();

	void PlaySound(Resource * res);
	void PauseAll();
	void ResumeAll();
	bool IsPaused() { return m_paused; }

	void Update();
private:
	vector< Sound*>						m_sounds;
	vector< Sound*>						m_musics;
	
	bool								m_paused;
	
	SoundManager();
	SoundManager(const SoundManager&) = default;
	static SoundManager			  * sm_instance;
};