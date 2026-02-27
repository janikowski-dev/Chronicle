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
	case EOutputType::PostCallback: return FText::FromString("Post Callbacks");
	case EOutputType::Requirements: return FText::FromString("Availability Requirements");
	default: return FText::FromString("Invalid Node");
	}
}

FSlateColor URuleOutputNode::GetBackgroundColor() const
{
	if (Type == EOutputType::Requirements)
	{
		return FColors::Condition;
	}
	
	return FColors::Callback;
}

bool URuleOutputNode::CanUserDeleteNode() const
{
	return false;
}
