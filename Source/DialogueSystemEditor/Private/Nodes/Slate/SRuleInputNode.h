#pragma once

#include "FCharacterSet.h"
#include "FRuleSet.h"
#include "SDialogueNode.h"

class URuleInputNode;

class SRuleInputNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SRuleInputNode) {}
	SLATE_END_ARGS()
	
	void Construct(const FArguments&,
		URuleInputNode* InNode,
		const FRuleSet& InRuleSet,
		const FCharacterSet& InCharacterSet
	);
	
	virtual void UpdateGraphNode() override;

private:
	TSharedRef<SWidget> GetInputBody() const;
	TSharedRef<SWidget> GetRuleSelectionBody() const;
	TSharedRef<SWidget> GetIntegerInputBody() const;
	TSharedRef<SWidget> GetCharacterSelectionBody() const;
	
	void Cache(URuleInputNode* InNode);
	void Cache(const FRuleSet& InSet);
	void Cache(const FCharacterSet& InSet);
	
private:
	TWeakObjectPtr<URuleInputNode> TypedNode;
	
	TArray<TSharedPtr<FGuid>> CharacterIds;
	FCharacterSet* CharacterSet = nullptr;
	
	TArray<TSharedPtr<FGuid>> RuleIds;
	FRuleSet* RuleSet = nullptr;
};