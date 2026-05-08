#include "FChronicle_AnimationTrackEditor.h"
#include "SequencerSectionPainter.h"
#include "Sequences/UChronicle_AnimationTrack.h"

class FChronicle_AnimationSectionPainter : public ISequencerSection
{
public:
	UMovieSceneSection& SectionObject;
	
public:
	explicit FChronicle_AnimationSectionPainter(
		UMovieSceneSection& InSection
	) : SectionObject(InSection)
	{
	}

	virtual UMovieSceneSection* GetSectionObject() override
	{
		return &SectionObject;
	}

	virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override
	{
		return Painter.PaintSectionBackground();
	}
};

FChronicle_AnimationTrackEditor::FChronicle_AnimationTrackEditor(
	TSharedRef<ISequencer> InSequencer
) : FMovieSceneTrackEditor(MoveTemp(InSequencer))
{
	
}

TSharedRef<ISequencerTrackEditor> FChronicle_AnimationTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FChronicle_AnimationTrackEditor(InSequencer));
}

TSharedRef<ISequencerSection> FChronicle_AnimationTrackEditor::MakeSectionInterface(
	UMovieSceneSection& SectionObject,
	UMovieSceneTrack& Track,
	FGuid ObjectBinding
)
{
	return MakeShareable(new FChronicle_AnimationSectionPainter(SectionObject));
}

bool FChronicle_AnimationTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const
{
	return TrackClass == UChronicle_AnimationTrack::StaticClass();
}