#include "UDialogueLineNode.h"

void UDialogueLineNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input,  TEXT("DialoguePin"), NAME_None, nullptr, TEXT("In"));
	CreatePin(EGPD_Output, TEXT("DialoguePin"), NAME_None, nullptr, TEXT("Out"));
}

FText UDialogueLineNode::GetTitle() const
{
	return  FText::Format(FText::FromString("Line #{0}"), LineIndex);
}
