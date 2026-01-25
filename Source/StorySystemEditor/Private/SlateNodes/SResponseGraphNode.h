#pragma once

#include "SStoryGraphNode.h"

class UResponseGraphNode;

class SResponseGraphNode : public SStoryGraphNode
{
public:
	SLATE_BEGIN_ARGS(SResponseGraphNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UResponseGraphNode* InNode);
	virtual void UpdateGraphNode() override;
};
