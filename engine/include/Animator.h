#pragma once
#include "Core.h"
#include "Vector2.h"


class Animation;

class Animator
{
public:
	explicit Animator(const Vector2 & objSize, const Vector2 & textureSize);
	~Animator();

	Animation * AddAnimation(const string & name, int count, const Vector2 & startPos);
	void SetAnimationFrameTime(const string & name, float frameTime);
	void SetAnimationState(const string & name, int state);
	
	void PlayAnimation(const string & name);
	void PlayAnimation(Animation * anim);
	void StopAnimation(const string & name);
	void PauseAnimation(const string & name);
	void ResumeAnimation(const string & name);
	bool IsAnimationPlaying(const string & name);
	bool IsAnimationLooped(const string & name);

	Animation * GetAnimation(const string & name);
	int GetAnimationStateCount(const string & name);
	Animation * GetActiveAnimation() { return m_activeAnimation; }
	
	void Update(float dt);
private:
	Vector2								m_objectSize;
	Vector2								m_textureSize;
	vector<Animation *>					m_animations;
	Animation						  * m_activeAnimation = nullptr;
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
	void SetState(int state);
	void SetNextAnimation(Animation * next) { m_next = next; }

	size_t GetStateCount() { return m_state.size(); }
	float GetFrameTime() { return m_frameTime; }
	const string & GetName() { return m_name; }
	Animation * GetNextAnimation() { return m_next; }

	void Update(float dt);

protected:
	Vector2					m_objectSize;
	string					m_name;
	float					m_frameTime = 0.2f;
	float					m_counter = 0.f;
	bool					m_playing;
	bool					m_looped;
	vector<SDL_Rect>		m_state;
	int						m_index;
	Animation			  * m_next;
	Animator			  * m_animator;
};
