#pragma once

#include "SDialogueNode.h"

class URuleNode;

class SRuleDefaultNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRuleDefaultNode) {}
	SLATE_END_ARGS()
	void Construct(const FArguments&, URuleNode* InNode);
	virtual void UpdateGraphNode() override;

private:
	void Cache(URuleNode* InNode);
	
private:
	TWeakObjectPtr<URuleNode> TypedNode;
};