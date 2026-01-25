#pragma once

#include "CoreMinimal.h"
#include "UStoryGraphNode.h"
#include "EdGraph/EdGraphNode.h"
#include "UDialogueGraphNode.generated.h"

UCLASS()
class UDialogueGraphNode : public UStoryGraphNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText DialogueText;

	virtual void AllocateDefaultPins() override;
};