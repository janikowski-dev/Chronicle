#pragma once

#include "FDialogueNodeData.generated.h"

USTRUCT()
struct FDialogueNodeData
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
	int32 RequirementsIndex = -1; 

	UPROPERTY(VisibleAnywhere)
	TArray<FGuid> Callbacks;

	UPROPERTY(VisibleAnywhere)
	TArray<FGuid> Children;
};