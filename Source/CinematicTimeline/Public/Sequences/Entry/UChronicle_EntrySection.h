#pragma once

#include "MovieSceneSection.h"
#include "UChronicle_EntrySection.generated.h"

UCLASS()
class CINEMATICTIMELINE_API UChronicle_EntrySection : public UMovieSceneSection
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FGuid MainParticipantId;
	
	UPROPERTY(EditAnywhere)
	FGuid CameraId;

public:
	UChronicle_EntrySection();
};
