#pragma once

#include "FRuleData.h"
#include "FDialogueNodeData.generated.h"

USTRUCT()
struct DIALOGUESYSTEMEDITOR_API FDialogueNodeData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	FGuid Id;

	UPROPERTY(VisibleAnywhere)
	FString Text;

	UPROPERTY(VisibleAnywhere)
	FGuid SpeakerId;

	UPROPERTY(VisibleAnywhere)
	FGuid ListenerId;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FRuleData> Rules;

	UPROPERTY(VisibleAnywhere)
	TArray<FGuid> Callbacks;

	UPROPERTY(VisibleAnywhere)
	TArray<FGuid> Children;
};