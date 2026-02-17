#pragma once

#include "FRuleSet.h"
#include "SDialogueNode.h"

class URuleTagNode;

class SRuleTagNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRuleTagNode) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments&, URuleTagNode* InNode, const FRuleSet& Set);
	virtual void UpdateGraphNode() override;

private:
	void Cache(URuleTagNode* InNode);
	void Cache(const FRuleSet& Set);
	
private:
	TWeakObjectPtr<URuleTagNode> TypedNode;
	TArray<TSharedPtr<FGuid>> Ids;
	FRuleSet* RuleSet = nullptr;
};