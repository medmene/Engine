#pragma once


class ICharacter
{
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsVisible() = 0;
	virtual void SetVisible(bool visible) = 0;
protected:
	~ICharacter() = default;
};