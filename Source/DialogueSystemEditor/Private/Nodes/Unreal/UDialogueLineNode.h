#pragma once

#include "CoreMinimal.h"
#include "UDialogueNode.h"
#include "UDialogueLineNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueLineNode : public UDialogueNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTitle() const override;
	virtual FText GetText() const override;
	
public:
	UPROPERTY(EditAnywhere)
	FText Text;
	UPROPERTY()
	int32 LineIndex;
	UPROPERTY()
	FGuid SpeakerId;
	UPROPERTY()
	FGuid ListenerId;
};