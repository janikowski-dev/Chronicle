#pragma once

#include "SDialogueNode.h"

class UDialogueLinkNode;
class UDialogueLineNode;

class SDialogueLinkNode : public SDialogueNode<UDialogueLinkNode>
{
public:
	SLATE_BEGIN_ARGS(SDialogueLinkNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UDialogueLinkNode* InNode);

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FSlateColor GetHeaderColor() const override;
	virtual void UpdateGraphNode() override;
	
private:
	TSharedRef<SWidget> GetLineNodesMenu();
	void SelectNode(UDialogueLineNode* Node) const;
	FText GetSelectedNodeTitle() const;
	FText GetSelectedNodeText() const;
	FText GetListenerName() const;
	FText GetSpeakerName() const;
	void RefreshAvailableNodes();

private:
	TArray<TWeakObjectPtr<UDialogueLineNode>> AvailableNodes;
};