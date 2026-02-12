#include "SDialogueLineNode.h"

#include "SGraphPanel.h"
#include "Nodes/Unreal/UDialogueLineNode.h"

void SDialogueLineNode::Construct(const FArguments&, UDialogueLineNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

FText SDialogueLineNode::GetTitle(UDialogueNode* Node)
{
	return FText::Format(FText::FromString("Line #{0}"), Cast<UDialogueLineNode>(Node)->LineIndex);
}

FSlateColor SDialogueLineNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Red);
}

void SDialogueLineNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
	AddTextField(
		Box,
		TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateSP(this, &SDialogueLineNode::GetText)),
		FOnTextCommitted::CreateSP(this, &SDialogueLineNode::SetText)
	);
}

FText SDialogueLineNode::GetText() const
{
	return CastChecked<UDialogueLineNode>(GraphNode)->Text;
}

void SDialogueLineNode::SetText(const FText& NewText, ETextCommit::Type) const
{
	UDialogueLineNode* Node = CastChecked<UDialogueLineNode>(GraphNode);
	Node->Modify();
	Node->Text = NewText;
}
