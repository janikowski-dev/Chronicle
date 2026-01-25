#include "UStoryGraphNode.h"

void UStoryGraphNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input,  TEXT("StoryPin"), NAME_None, nullptr, TEXT("In"));
	CreatePin(EGPD_Output, TEXT("StoryPin"), NAME_None, nullptr, TEXT("Out"));
}

FText UStoryGraphNode::GetNodeTitle(ENodeTitleType::Type) const
{
	return FText::FromString("Story Node");
}