#pragma once
#include "Core.h"
#include "Vector2.h"
#include "ResourceManager.h"


class Animation;
class GameObject;
class Button;

namespace pugi
{
	class xml_document;
}

class Animator
{
public:
	explicit Animator(pugi::xml_document * doc, GameObject * object);
	explicit Animator(pugi::xml_document * doc, Button * object);
	explicit Animator(GameObject * object);
	~Animator();

	void SetAnimationsEnabled(bool enabled) { m_animationsEnabled = enabled; }
	void SetAnimationFrameTime(const string & name, float frameTime);
	void SetAnimationState(const string & name, int state);
	
	void PlayAnimation(const string & name);
	void PlayAnimation(Animation * anim);
	void StopAnimation(const string & name);
	void PauseAnimation(const string & name);
	void ResumeAnimation(const string & name);
	
	bool IsAnimationPlaying(const string & name);
	bool IsAnimationLooped(const string & name);
	bool IsAnimationsEnabled() { return m_animationsEnabled; }

	Animation * GetAnimation(const string & name);
	int GetAnimationStateCount(const string & name);
	Animation * GetActiveAnimation() { return m_activeAnimation; }
	Animation * GetPreviousAnimation() { return m_prevAnimation; }
	
	void Update(float dt);
private:
	Vector2								m_objectSize;
	vector<Animation *>					m_animations;
	Animation						  * m_activeAnimation = nullptr;
	Animation						  * m_prevAnimation = nullptr;
	GameObject						  * m_object;
	Button							  * m_objectButton;
	bool								m_animationsEnabled = false;

	void StopAllAnimations();
};



class Animation
{
public:
	explicit Animation(Animator * animator, const string &name, const Vector2 & objSize);

	bool IsPlaying() { return m_playing; }
	bool IsLooped() { return m_looped; }
	
	inline void Stop();
	inline void Play();
	void Pause() { m_playing = false; }
	void Resume() { m_playing = true; }

	void SetFrameTime(float fTime) { m_frameTime = fTime; }
	void SetLooped(bool looped) { m_looped = looped; }
	void SetState(int state);
	void SetStates(int row, int count);
	void SetNextAnimation(Animation * next) { m_next = next; }

	size_t GetStateCount() { return m_state.size(); }
	const SDL_Rect & GetCurrentState() { return m_state[m_index]; }
	float GetFrameTime() { return m_frameTime; }
	const string & GetName() { return m_name; }
	Animation * GetNextAnimation() { return m_next; }

	void Update(float dt);

protected:
	Vector2					m_objectSize;
	string					m_name;
	float					m_frameTime = 0.2f;
	bool					m_looped;
	bool					m_playing;
	vector<SDL_Rect>		m_state;
	Animation			  * m_next = nullptr;
	
	Animator			  * m_animator = nullptr;
	float					m_counter = 0.f;
	int						m_index;
};
