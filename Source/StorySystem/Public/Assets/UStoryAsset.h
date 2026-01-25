#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UStoryAsset.generated.h"

class UStoryGraph;

UCLASS()
class STORYSYSTEM_API UStoryAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UStoryGraph> Graph;
};