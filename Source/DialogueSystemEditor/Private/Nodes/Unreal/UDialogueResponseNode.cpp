#include "UDialogueResponseNode.h"

void UDialogueResponseNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input,  TEXT("DialoguePin"), NAME_None, nullptr, TEXT("In"));
	CreatePin(EGPD_Output, TEXT("DialoguePin"), NAME_None, nullptr, TEXT("Out"));
}

FText UDialogueResponseNode::GetTitle() const
{
	return FText::Format(FText::FromString("Response #{0}.{1}"), ParentIndex, OrderIndex);
}
