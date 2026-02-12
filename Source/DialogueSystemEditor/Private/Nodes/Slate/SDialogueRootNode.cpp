#include "SDialogueRootNode.h"

#include "Nodes/Unreal/UDialogueRootNode.h"

void SDialogueRootNode::Construct(const FArguments&, UDialogueRootNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

void SDialogueRootNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
}

FText SDialogueRootNode::GetTitle(UDialogueNode* Node)
{
	return FText::FromString("ROOT");
}

FSlateColor SDialogueRootNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Black);
}
