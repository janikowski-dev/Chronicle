#pragma once

#include "CoreMinimal.h"
#include "MovieSceneTrackEditor.h"

class CINEMATICTIMELINEEDITOR_API FChronicle_AnimationTrackEditor : public FMovieSceneTrackEditor
{
public:
	explicit FChronicle_AnimationTrackEditor(TSharedRef<ISequencer> InSequencer);

	static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);

	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const override;
	virtual TSharedRef<ISequencerSection> MakeSectionInterface(
		UMovieSceneSection& SectionObject,
		UMovieSceneTrack& Track,
		FGuid ObjectBinding
	) override;
};