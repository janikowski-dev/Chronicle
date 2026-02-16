#include "URuleOutputNode.h"

#include "Utils/FColors.h"

void URuleOutputNode::AllocateDefaultPins()
{
	if (Type == EOutputType::Requirements)
	{
		CreatePin(EGPD_Input, TEXT("Condition"), NAME_None, nullptr, TEXT("Result"));
	}
	else
	{
		CreatePin(EGPD_Input, TEXT("Callback"), NAME_None, nullptr, TEXT("Result"));
	}
}

bool URuleOutputNode::AllowMultipleInputs() const
{
	return Type != EOutputType::Requirements;
}

FText URuleOutputNode::GetTitle() const
{
	switch (Type)
	{
	case EOutputType::PreCallback: return FText::FromString("Pre Response Callback");
	case EOutputType::PostCallback: return FText::FromString("Post Response Callback");
	case EOutputType::Requirements: return FText::FromString("Requirements For Response");
	default: return FText::FromString("Invalid Node");
	}
}

FSlateColor URuleOutputNode::GetBackgroundColor() const
{
	if (Type == EOutputType::Requirements)
	{
		return FColors::Turquoise;
	}
	
	return FColors::Purple;
}

bool URuleOutputNode::CanUserDeleteNode() const
{
	return false;
}
