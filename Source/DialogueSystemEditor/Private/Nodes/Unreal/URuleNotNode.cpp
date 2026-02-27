#include "URuleNotNode.h"

#include "Utils/FColors.h"

void URuleNotNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("In"));
	CreatePin(EGPD_Output, TEXT("Condition"), NAME_None, nullptr, TEXT("Out"));
}

FText URuleNotNode::GetTitle() const
{
	return FText::FromString("Not");
}

FSlateColor URuleNotNode::GetBackgroundColor() const
{
	return FColors::Condition;
}
