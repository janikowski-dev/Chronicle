#include "UStoryRootNode.h"

void UStoryRootNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("StoryPin"), NAME_None, nullptr, TEXT("Out"));
}
