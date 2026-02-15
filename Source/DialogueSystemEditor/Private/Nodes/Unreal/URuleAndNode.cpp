#include "URuleAndNode.h"

#include "Utils/FColors.h"

void URuleAndNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Condition A"));
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Condition B"));
	CreatePin(EGPD_Output, TEXT("Condition"), NAME_None, nullptr, TEXT("A and B"));
}

FText URuleAndNode::GetTitle() const
{
	return FText::FromString("And");
}

FSlateColor URuleAndNode::GetBackgroundColor() const
{
	return FColors::Turquoise;
}
