#pragma once

#include "SDialogueTextNode.h"

class UDialogueResponseNode;

class SDialogueResponseNode : public SDialogueTextNode
{
public:
	SLATE_BEGIN_ARGS(SDialogueResponseNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UDialogueResponseNode* InNode);

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FText GetTitle(UDialogueNode* Node) override;
	virtual FSlateColor GetHeaderColor() const override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&) override;

private:
	FText GetText() const;
	void SetText(const FText& NewText, ETextCommit::Type) const;
	void OpenNodeEditor() const;
};
