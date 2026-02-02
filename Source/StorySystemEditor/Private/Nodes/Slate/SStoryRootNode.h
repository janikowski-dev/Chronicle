#pragma once

#include "SStoryNode.h"

class UStoryRootNode;

class SStoryRootNode : public SStoryNode
{
public:
	SLATE_BEGIN_ARGS(SStoryRootNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, UStoryRootNode* InNode);

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FText GetTitle(UStoryNode* Node) override;
	virtual FSlateColor GetHeaderColor() const override;
};
