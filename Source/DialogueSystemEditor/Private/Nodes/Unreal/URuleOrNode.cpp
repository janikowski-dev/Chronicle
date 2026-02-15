#include "URuleOrNode.h"

#include "Utils/FColors.h"

void URuleOrNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Condition A"));
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Condition B"));
	CreatePin(EGPD_Output, TEXT("Condition"), NAME_None, nullptr, TEXT("A or B"));
}

FText URuleOrNode::GetTitle() const
{
	return FText::FromString("Or");
}

FSlateColor URuleOrNode::GetBackgroundColor() const
{
	return FColors::Turquoise;
}
