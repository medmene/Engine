#pragma once
#include "Event.h"
#include "GameObject.h"

class EventPass : public Event
{
public:
	enum State
	{
		GET_IN = 0,
		STAY_IN,
		GET_OUT,
		STAY_OUT
	};

	enum CheckPos
	{
		CENTER = 0,
		BOTTOM,
		TOP,
		RIGHT,
		LEFT
	};

	EventPass() {};
	EventPass(State s) { state = s; }

	void SetCurrentState(State s) { state = s; }
	State GetCurrentState() { return state; }

	void SetRect(Vector2 left, Vector2 right) { rect = { left, right }; }
	pair<Vector2, Vector2> GetRect() { return rect; }

	void SetObject(GameObject *o) { object = o; }
	GameObject * GetObject() { return object; }

	// Default CENTER
	void SetCheckStrategy(CheckPos c) { checkBy = c; }
	CheckPos GetCheckStrategy() { return checkBy; }

	bool CheckEvent();

private:
	State state = STAY_OUT;
	GameObject *object = 0;
	pair<Vector2,Vector2> rect;
	EventPass::CheckPos checkBy = CENTER;
	float x, y; //object pos
};