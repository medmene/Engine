#include "include/Animator.h"
#include "pugixml/pugixml.hpp"
#include "include/GameObject.h"
#include "include/Button.h"




Animation::Animation(Animator * animator, const string& name, const Vector2& objSize)
	: m_objectSize(objSize)
	, m_name(name)
	, m_playing(false)
	, m_looped(false)
	, m_index(0)
	, m_animator(animator)
{
}

void Animation::Stop()
{
	m_playing = false;
	m_index = 0;
	m_counter = 0.f;
	
	// TODO made this later
	// if (m_next)
	// {
	// 	m_animator->PlayAnimation(m_next);
	// }
}

void Animation::Play()
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

void Animation::SetStates(int row, int count)
{
	for (int i = 0; i < count; ++i)
	{
		SDL_Rect r = { i * (int)m_objectSize.x,row * (int)m_objectSize.y,
			(int)m_objectSize.x, (int)m_objectSize.y };
		m_state.emplace_back(r);
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

// ------------------------------------------------------------------------------------------ //

Animator::Animator(pugi::xml_document * doc)
{
	auto rootNode = doc->child("object");
	auto sizeNode = rootNode.child("animSize");
	
	m_objectSize.x = std::stoi(sizeNode.attribute("x").value());
	m_objectSize.y = std::stoi(sizeNode.attribute("y").value());

	for (pugi::xml_node anim : rootNode.children("animation"))
	{
		m_animations.emplace_back(new Animation(this, anim.attribute("name").value(), m_objectSize));

		auto count = std::stoi(anim.attribute("count").value());
		auto row = std::stoi(anim.attribute("row").value());
		string loop = anim.attribute("loop").value();

		m_animations.back()->SetStates(row, count);
		m_animations.back()->SetLooped(loop == "true" ? true : false);
		m_animations.back()->SetFrameTime(std::stoi(anim.attribute("speed").value()));
	}
	
	for (pugi::xml_node anim : rootNode.children("animation"))
	{
		auto nextState = anim.attribute("next_state").value();
		auto curName = anim.attribute("name").value();

		GetAnimation(curName)->SetNextAnimation(GetAnimation(nextState));
	}

	m_activeAnimation = m_animations.front();
	m_prevAnimation = m_activeAnimation;
}

Animator::~Animator()
{
	for (auto && anim : m_animations)
	{
		delete anim;
	}
	m_animations.clear();
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
		// if (m_prevAnimation)
		// {
		// 	m_prevAnimation->Stop();
		// }

		StopAllAnimations();
		
		anim->Play();
		m_prevAnimation = m_activeAnimation;
		m_activeAnimation = anim;
	}
}

void Animator::StopAllAnimations()
{
	for (auto && anim : m_animations)
	{
		anim->Stop();
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
	if (m_animationsEnabled)
	{
		for (auto && anim : m_animations)
		{
			anim->Update(dt);
		}
	}
}
