#pragma once

#include "FChronicle_AnimationData.generated.h"

USTRUCT(BlueprintType)
struct CHARACTERSYSTEM_API FChronicle_AnimationData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UAnimSequence> Animation;

	bool operator==(const FChronicle_AnimationData& Other) const
	{
		return Animation == Other.Animation;
	}

	bool operator!=(const FChronicle_AnimationData& Other) const
	{
		return !(*this == Other);
	}
};
