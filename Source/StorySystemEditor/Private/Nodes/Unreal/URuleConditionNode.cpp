#include "URuleConditionNode.h"

void URuleConditionNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("RulePin"), NAME_None, nullptr, TEXT("Value"));
}

FText URuleConditionNode::GetNodeTitle(ENodeTitleType::Type) const
{
	return FText::FromString("Condition");
}
