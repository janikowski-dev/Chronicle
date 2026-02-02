#include "SStoryDialogueNode.h"

#include "SGraphPanel.h"
#include "Nodes/Unreal/UStoryDialogueNode.h"

void SStoryDialogueNode::Construct(const FArguments&, UStoryDialogueNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

FText SStoryDialogueNode::GetTitle(UStoryNode* Node)
{
	return FText::Format(FText::FromString("Dialogue_{0}"), Node->EditorIndex);
}

FSlateColor SStoryDialogueNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Red);
}

void SStoryDialogueNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
	AddTextField(
		Box,
		TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateSP(this, &SStoryDialogueNode::GetText)),
		FOnTextCommitted::CreateSP(this, &SStoryDialogueNode::SetText)
	);
}

FText SStoryDialogueNode::GetText() const
{
	return CastChecked<UStoryDialogueNode>(GraphNode)->Text;
}

void SStoryDialogueNode::SetText(const FText& NewText, ETextCommit::Type) const
{
	UStoryDialogueNode* Node = CastChecked<UStoryDialogueNode>(GraphNode);
	Node->Modify();
	Node->Text = NewText;
}
