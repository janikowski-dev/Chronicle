#pragma once

#include "SDialogueTextNode.h"

class UDialogueLineNode;

class SDialogueLineNode : public SDialogueTextNode
{
public:
	SLATE_BEGIN_ARGS(SDialogueLineNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, UDialogueLineNode* InNode);
	
protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FText GetTitle(UDialogueNode* Node) override;
	virtual FSlateColor GetHeaderColor() const override;

private:
	FText GetText() const;
	void SetText(const FText& NewText, ETextCommit::Type CommitType) const;
};
