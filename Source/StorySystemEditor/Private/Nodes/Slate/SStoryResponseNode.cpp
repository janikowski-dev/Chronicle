#include "SStoryResponseNode.h"
#include "Nodes/Unreal/UStoryResponseNode.h"

void SStoryResponseNode::Construct(const FArguments&, UStoryResponseNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

FText SStoryResponseNode::GetTitle(UStoryNode* Node)
{
	return FText::Format(FText::FromString("Response_{0}"), Node->EditorIndex);
}

FSlateColor SStoryResponseNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Blue);
}

void SStoryResponseNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
	AddTextField(
		Box,
		TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateSP(this, &SStoryResponseNode::GetText)),
		FOnTextCommitted::CreateSP(this, &SStoryResponseNode::SetText)
	);
}

FText SStoryResponseNode::GetText() const
{
	return CastChecked<UStoryResponseNode>(GraphNode)->Text;
}

void SStoryResponseNode::SetText(const FText& NewText, ETextCommit::Type) const
{
	UStoryResponseNode* Node = CastChecked<UStoryResponseNode>(GraphNode);
	Node->Modify();
	Node->Text = NewText;
}

