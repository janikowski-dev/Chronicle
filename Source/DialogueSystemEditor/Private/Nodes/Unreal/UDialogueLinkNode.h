#pragma once

#include "CoreMinimal.h"
#include "UDialogueNode.h"
#include "UDialogueLinkNode.generated.h"

class UDialogueLineNode;

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueLinkNode : public UDialogueNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTitle() const override;

	UDialogueLineNode* GetLinkedNode() const;
	void SetLinkedNode(UDialogueLineNode* InNode);

public:
	UPROPERTY()
	TObjectPtr<UDialogueLineNode> LinkedNode;
};