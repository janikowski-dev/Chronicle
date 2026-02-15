#include "URuleCallbackNode.h"

#include "Utils/FColors.h"

void URuleCallbackNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("Callback"), NAME_None, nullptr, TEXT("Output"));
}

FText URuleCallbackNode::GetTitle() const
{
	return FText::FromString("Callback");
}

FSlateColor URuleCallbackNode::GetBackgroundColor() const
{
	return FColors::Purple;
}
