#include "UDialogueRootNode.h"

void UDialogueRootNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Output, TEXT("DialoguePin"), NAME_None, nullptr, TEXT("Out"));
}
