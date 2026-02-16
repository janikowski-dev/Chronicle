#include "SDialogueResponseNode.h"

#include "Editors/FDialogueNodeEditor.h"
#include "Nodes/Unreal/UDialogueResponseNode.h"

void SDialogueResponseNode::Construct(const FArguments&, UDialogueResponseNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

FSlateColor SDialogueResponseNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Blue);
}

FReply SDialogueResponseNode::OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&)
{
	OpenNodeEditor();
	return FReply::Handled();
}

void SDialogueResponseNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
	AddTextField(
		Box,
		TAttribute<FText>::Create(TAttribute<FText>::FGetter::CreateSP(this, &SDialogueResponseNode::GetText)),
		FOnTextCommitted::CreateSP(this, &SDialogueResponseNode::SetText)
	);
}

FText SDialogueResponseNode::GetText() const
{
	return CastChecked<UDialogueResponseNode>(GraphNode)->Text;
}

void SDialogueResponseNode::SetText(const FText& NewText, ETextCommit::Type) const
{
	UDialogueResponseNode* Node = CastChecked<UDialogueResponseNode>(GraphNode);
	Node->Modify();
	Node->Text = NewText;
}

void SDialogueResponseNode::OpenNodeEditor() const
{
	if (UDialogueNode* NodeAsset = Cast<UDialogueNode>(GraphNode))
	{
		const TSharedRef<FDialogueNodeEditor> Editor = MakeShared<FDialogueNodeEditor>();

		Editor->InitNodeAssetEditor(
			EToolkitMode::Standalone,
			TSharedPtr<IToolkitHost>(),
			NodeAsset
		);
	}
}
