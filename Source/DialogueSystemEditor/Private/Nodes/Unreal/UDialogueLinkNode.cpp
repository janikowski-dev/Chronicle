#include "UDialogueLinkNode.h"

#include "UDialogueLineNode.h"

void UDialogueLinkNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, TEXT("DialoguePin"), NAME_None, nullptr, TEXT("In"));
}

FText UDialogueLinkNode::GetTitle() const
{
	if (LinkedNode)
	{
		return FText::Format(FText::FromString("Link To Line #{0}"), LinkedNode->LineIndex);
	}
	
	return FText::FromString("Empty Link");
}

UDialogueLineNode* UDialogueLinkNode::GetLinkedNode() const
{
	return LinkedNode;
}

void UDialogueLinkNode::SetLinkedNode(UDialogueLineNode* InNode)
{
	LinkedNode = InNode;
}
