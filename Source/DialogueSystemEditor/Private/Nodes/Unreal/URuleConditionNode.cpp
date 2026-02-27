#include "URuleConditionNode.h"

#include "Utils/FColors.h"

void URuleConditionNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("Condition"), NAME_None, nullptr, TEXT("Value"));
}

FText URuleConditionNode::GetTitle() const
{
	return FText::FromString("Condition");
}

FSlateColor URuleConditionNode::GetBackgroundColor() const
{
	return FColors::Condition;
}
