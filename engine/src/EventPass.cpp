#include "include/EventPass.h"

bool EventPass::CheckEvent()
{
	switch (checkBy)
	{
	case CENTER:
		x = object->GetCenterPos().x , y = object->GetCenterPos().y;
		return x >= rect.x && x <= (rect.x + rect.w) &&
		y >= rect.y && y <= (rect.y + rect.h);
		break;
	
	default:
	throw std::exception("Not implemented yet");
		break;
	}
}