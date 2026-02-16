#pragma once

#include "SDialogueNode.h"

class URuleTagNode;

class SRuleCallbackNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRuleCallbackNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, URuleTagNode* InNode);
	virtual void UpdateGraphNode() override;

private:
	void Cache(URuleTagNode* InNode);
	void InitCallbacks();
	
private:
	TWeakObjectPtr<URuleTagNode> TypedNode;
	TArray<TSharedPtr<FString>> AllTags;
	TSharedPtr<FString> SelectedTag;
};