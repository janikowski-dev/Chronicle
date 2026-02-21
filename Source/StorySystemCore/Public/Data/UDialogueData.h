#pragma once

#include "FDialogueNodeData.h"
#include "FRuleData.h"
#include "UDialogueData.generated.h"

UCLASS()
class STORYSYSTEMCORE_API UDialogueData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FDialogueNodeData> Nodes;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FRuleData> Rules;
};
