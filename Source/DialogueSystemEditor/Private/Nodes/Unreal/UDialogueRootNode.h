#pragma once

#include "CoreMinimal.h"
#include "UDialogueNode.h"
#include "UDialogueRootNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueRootNode : public UDialogueNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTitle() override;
};