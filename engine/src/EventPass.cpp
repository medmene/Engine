#include "include/EventPass.h"

bool EventPass::CheckEvent()
{
	switch (checkBy)
	{
	case CENTER:
		x = object->GetCenterPos().x , y = object->GetCenterPos().y;
		return x >= rect.first.x && x <= rect.second.x &&
		y >= rect.first.y && y <= rect.second.y;
		break;
	
	default:
	throw std::exception("Not implemented yet");
		break;
	}
}