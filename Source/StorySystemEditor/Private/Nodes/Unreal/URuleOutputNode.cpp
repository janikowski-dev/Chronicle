#include "URuleOutputNode.h"

void URuleOutputNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("RulePin"), NAME_None, nullptr, TEXT("Result"));
}

FText URuleOutputNode::GetNodeTitle(ENodeTitleType::Type) const
{
	switch (Type)
	{
	case EOutputType::PreCallback: return FText::FromString("Pre Response Callback");
	case EOutputType::PostCallback: return FText::FromString("Post Response Callback");
	case EOutputType::Prerequisites: return FText::FromString("Prerequisites For Response");
	default: return FText::FromString("Invalid Node");
	}
}
