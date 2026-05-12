#pragma once

#include "MovieSceneSection.h"
#include "UChronicle_SubtitleSection.generated.h"

UCLASS()
class CINEMATICTIMELINE_API UChronicle_SubtitleSection : public UMovieSceneSection
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Subtitle;

public:
	UChronicle_SubtitleSection();
};
