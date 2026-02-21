#include "SDialogueLineNode.h"

#include "SGraphPanel.h"
#include "Editors/FDialogueNodeEditor.h"
#include "Nodes/Unreal/UDialogueLineNode.h"
#include "Utils/FSlateHelper.h"

void SDialogueLineNode::Construct(const FArguments&, UDialogueLineNode* InNode)
{
	Cache(InNode);
	UpdateGraphNode();
}

FSlateColor SDialogueLineNode::GetHeaderColor() const
{
	return FSlateColor(FLinearColor::Red);
}

FReply SDialogueLineNode::OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent)
{
	OpenNodeEditor();
	return FReply::Handled();
}

void SDialogueLineNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
	Box->AddSlot()
	.AutoHeight()
	[
		MakeTextField(
			TAttribute<FText>(this, &SDialogueLineNode::GetText),
			FOnTextCommitted::CreateSP(this, &SDialogueLineNode::SetText)
		)
	];
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

void SDialogueLineNode::OpenNodeEditor() const
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
