#pragma once

class GameObject;

class ICharacter
{
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsVisible() = 0;
	virtual void SetVisible(bool visible) = 0;
	virtual GameObject * GetGameObject() = 0;
protected:
	~ICharacter() = default;
};