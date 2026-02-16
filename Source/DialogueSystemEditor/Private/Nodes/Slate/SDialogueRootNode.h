#pragma once

#include "SDialogueNode.h"

class UDialogueRootNode;

class SDialogueRootNode : public SDialogueNode
{
public:
	SLATE_BEGIN_ARGS(SDialogueRootNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, UDialogueRootNode* InNode);

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FSlateColor GetHeaderColor() const override;
};
