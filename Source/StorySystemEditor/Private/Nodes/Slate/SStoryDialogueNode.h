#pragma once

#include "SStoryTextNode.h"

class UStoryDialogueNode;

class SStoryDialogueNode : public SStoryTextNode
{
public:
	SLATE_BEGIN_ARGS(SStoryDialogueNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, UStoryDialogueNode* InNode);
	
protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FText GetTitle(UStoryNode* Node) override;
	virtual FSlateColor GetHeaderColor() const override;

private:
	FText GetText() const;
	void SetText(const FText& NewText, ETextCommit::Type CommitType) const;
};
