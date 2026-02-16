#pragma once

#include "SDialogueNode.h"

class URuleTagNode;

class SRuleConditionNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRuleConditionNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, URuleTagNode* InNode);
	virtual void UpdateGraphNode() override;

private:
	void Cache(URuleTagNode* InNode);
	void InitConditions();
	
private:
	TWeakObjectPtr<URuleTagNode> TypedNode;
	TArray<TSharedPtr<FString>> AllTags;
	TSharedPtr<FString> SelectedTag;
};