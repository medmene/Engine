#include "include/Animator.h"


Animation::Animation(Animator * animator, const string& name, const Vector2& objSize)
	: m_objectSize(objSize)
	, m_name(name)
	, m_playing(false)
	, m_looped(false)
	, m_animator(animator)
{
}

inline void Animation::Stop()
{
	m_playing = false;
	m_index = 0;
	m_counter = 0.f;
	
	if (m_next)
	{
		m_animator->PlayAnimation(m_next);
	}
}

inline void Animation::Play()
{
	m_playing = true;
	m_index = 0;
	m_counter = 0.f;
}

void Animation::SetState(int state)
{
	if (state > -1 && state < m_state.size())
	{
		m_playing = false;
		m_index = state;
		m_counter = 0.f;
	}
}

void Animation::Update(float dt)
{
	if (m_playing)
	{
		m_counter += dt;
		
		if (m_counter > m_frameTime)
		{
			m_index++;
			m_counter = 0;
		}
		
		if (m_index >= m_state.size())
		{
			if (m_looped)
			{
				m_index = 0;
			}
			else
			{
				Stop();
			}
		}
	}
}

Animator::Animator(const Vector2& objSize, const Vector2 & textureSize)
	: m_objectSize(objSize)
	, m_textureSize(textureSize)
{
}

Animator::~Animator()
{
	for (auto && anim : m_animations)
	{
		delete anim;
	}
	m_animations.clear();
}

Animation * Animator::AddAnimation(const string& name, int count, const Vector2& startPos)
{
}

void Animator::SetAnimationFrameTime(const string& name, float frameTime)
{
	if (auto anim = GetAnimation(name))
	{
		anim->SetFrameTime(frameTime);
	}
}

void Animator::SetAnimationState(const string& name, int state)
{
	if (auto anim = GetAnimation(name))
	{
		anim->SetState(state);
	}
}

void Animator::PlayAnimation(const string& name)
{
	if (auto anim = GetAnimation(name))
	{
		anim->Play();
		m_activeAnimation = anim;
	}
}

void Animator::PlayAnimation(Animation* anim)
{
	if (anim)
	{
		anim->Play();
		m_activeAnimation = anim;
	}
}

void Animator::StopAnimation(const string& name)
{
	if (auto anim = GetAnimation(name))
	{
		anim->Stop();
	}
}

void Animator::PauseAnimation(const string& name)
{
	if (auto anim = GetAnimation(name))
	{
		anim->Pause();
	}
}

void Animator::ResumeAnimation(const string& name)
{
	if (auto anim = GetAnimation(name))
	{
		anim->Resume();
	}
}

bool Animator::IsAnimationPlaying(const string& name)
{
	if (auto anim = GetAnimation(name))
	{
		return anim->IsPlaying();
	}
	return false;
}

bool Animator::IsAnimationLooped(const string& name)
{
	if (auto anim = GetAnimation(name))
	{
		return anim->IsLooped();
	}
	return false;
}

Animation* Animator::GetAnimation(const string& name)
{
	for (auto && anim : m_animations)
	{
		if (anim->GetName() == name)
		{
			return anim;
		}
	}
	return nullptr;
}

int Animator::GetAnimationStateCount(const string& name)
{
	if (auto anim = GetAnimation(name))
	{
		return anim->GetStateCount();
	}
	return 0;
}

void Animator::Update(float dt)
{
	for (auto && anim : m_animations)
	{
		anim->Update(dt);
	}
}
