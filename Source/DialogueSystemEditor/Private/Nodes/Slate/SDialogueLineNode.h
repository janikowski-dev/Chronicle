#pragma once

#include "SDialogueNode.h"

class UDialogueLineNode;

class SDialogueLineNode : public SDialogueNode<UDialogueLineNode>
{
public:
	SLATE_BEGIN_ARGS(SDialogueLineNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, UDialogueLineNode* InNode);
	
protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FSlateColor GetHeaderColor() const override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;

private:
	FText GetText() const;
	void SetText(const FText& NewText, ETextCommit::Type CommitType) const;
	void OpenNodeEditor() const;
};
