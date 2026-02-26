#pragma once

#include "SDialogueNode.h"

class UDialogueRootNode;

class SDialogueRootNode : public SDialogueNode<UDialogueRootNode>
{
public:
	SLATE_BEGIN_ARGS(SDialogueRootNode) {}
	SLATE_END_ARGS()

	void Construct(const FArguments&, UDialogueRootNode* InNode);

protected:
	virtual void AddBody(const TSharedRef<SVerticalBox>& Box) override;
	virtual FSlateColor GetHeaderColor() const override;
	FReply OpenAddParticipantWindow() const;

private:
	void AddCurrentParticipantList(const TSharedRef<SVerticalBox>& Box) const;
	void AddNewParticipantButton(const TSharedRef<SVerticalBox>& Box) const;
	
	bool HasParticipant(const TSharedPtr<FGuid>& Id) const;
	void AddParticipant(const TSharedPtr<FGuid>& Id) const;
	void RemoveParticipant(const TSharedPtr<FGuid>& Id) const;
};
