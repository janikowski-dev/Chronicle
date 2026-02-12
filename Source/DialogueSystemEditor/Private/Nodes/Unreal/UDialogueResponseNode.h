#pragma once

#include "CoreMinimal.h"
#include "UDialogueNode.h"
#include "UDialogueResponseNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueResponseNode : public UDialogueNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	
public:
	UPROPERTY(EditAnywhere)
	FText Text;
	UPROPERTY()
	int32 ParentIndex;
	UPROPERTY()
	int32 OrderIndex;
};