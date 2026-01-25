#include "URootGraphNode.h"

void URootGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("StoryPin"), NAME_None, nullptr, TEXT("Out"));
}