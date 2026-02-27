#pragma once

#include "SDialogueNode.h"

class UDialogueLineNode;

class SDialogueLineNode : public SDialogueNode<UDialogueLineNode>
{
public:
	SLATE_BEGIN_ARGS(SDialogueLineNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, UDialogueLineNode* InNode);
	
protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FSlateColor GetHeaderColor() const override;
	virtual void UpdateGraphNode() override;
	virtual FReply OnMouseButtonDoubleClick(const FGeometry& InMyGeometry, const FPointerEvent& InMouseEvent) override;

private:
	FText GetText() const;
	void SetText(const FText& NewText, ETextCommit::Type) const;
	
	FText GetListenerName() const;
	void SetListener(TSharedPtr<FGuid> Id, ESelectInfo::Type) const;
	
	FText GetSpeakerName() const;
	void SetSpeaker(TSharedPtr<FGuid> Id, ESelectInfo::Type) const;
	
	void FixAssignedIds() const;
	void OpenNodeEditor() const;
};
