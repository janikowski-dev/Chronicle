#pragma once

#include "FChronicle_AnimationData.h"
#include "MovieSceneSection.h"
#include "UChronicle_AnimationSection.generated.h"

UCLASS()
class CINEMATICTIMELINE_API UChronicle_AnimationSection : public UMovieSceneSection
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FChronicle_AnimationData AnimationData;

public:
    UChronicle_AnimationSection();
};
