#pragma once

#include "SDialogueNode.h"

class URuleTagNode;

class SRuleTagNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRuleTagNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, URuleTagNode* InNode);
	virtual void UpdateGraphNode() override;

private:
	TWeakObjectPtr<URuleTagNode> TypedNode;
	TArray<TSharedPtr<FString>> AllTags;
	TSharedPtr<FString> SelectedTag;
};