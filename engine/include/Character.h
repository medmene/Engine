#pragma once

struct PassabilityArea;
class TextBubble;

class ICharacter
{
public:
	virtual TextBubble * GetTextObject() = 0;
	virtual PassabilityArea * GetPassabilityArea() = 0;
protected:
	~ICharacter() = default;
};