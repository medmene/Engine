#include "include/input/SoundManager.h"
#include "include/controller/ResourceManager.h"
#include "include/input/KeyboardInput.h"


SoundManager * SoundManager::sm_instance = nullptr;

SoundManager::Sound::Sound(Resource* res, Mix_Music* music)
	: m_res(res)
	, m_music(music)
{
}

// --------------------------------------------------------------------------- //

SoundManager::SoundManager()
	: m_paused(false)
{
}

SoundManager::~SoundManager()
{
	for (auto && snd : m_sounds)
	{
		Mix_FreeMusic(snd->m_music);
		delete snd;
	}
	m_sounds.clear();

	for (auto && music : m_musics)
	{
		Mix_FreeMusic(music->m_music);
		delete music;
	}
	m_musics.clear();
}

SoundManager* SoundManager::instance()
{
	if (!sm_instance)
	{
		sm_instance = new SoundManager();
		Mix_Init(MIX_INIT_MP3);
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		Mix_VolumeMusic(40);
	}
	return sm_instance;
}

void SoundManager::PlaySound(Resource* res)
{
	if (res)
	{
		Mix_Music *music = Mix_LoadMUS(res->GetPath().c_str());
		Mix_PlayMusic(music, 1);
		m_sounds.emplace_back( new Sound (res, music));
	}
}

void SoundManager::PauseAll()
{
	m_paused = true;
	Mix_PauseMusic();
}

void SoundManager::ResumeAll()
{
	m_paused = false;
	Mix_ResumeMusic();
}

void SoundManager::Update()
{
	if (KeyboardInput::instance()->GetState() == kb::KEY_DOWN)
	{
		if (KeyboardInput::instance()->GetKey() == kb::J)
		{
			m_paused = !m_paused;
			if (m_paused)
			{
				Mix_ResumeMusic();
			}
			else
			{
				Mix_PauseMusic();
			}
		}
	}
}

