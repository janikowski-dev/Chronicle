#include "FChronicle_SubtitleTrackEditor.h"
#include "SequencerSectionPainter.h"
#include "Sequences/Subtitle/UChronicle_SubtitleTrack.h"

class FChronicle_SubtitleSectionPainter : public ISequencerSection
{
public:
	UMovieSceneSection& SectionObject;
	
public:
	explicit FChronicle_SubtitleSectionPainter(
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

FChronicle_SubtitleTrackEditor::FChronicle_SubtitleTrackEditor(
	TSharedRef<ISequencer> InSequencer
) : FMovieSceneTrackEditor(MoveTemp(InSequencer))
{
	
}

TSharedRef<ISequencerTrackEditor> FChronicle_SubtitleTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FChronicle_SubtitleTrackEditor(InSequencer));
}

TSharedRef<ISequencerSection> FChronicle_SubtitleTrackEditor::MakeSectionInterface(
	UMovieSceneSection& SectionObject,
	UMovieSceneTrack& Track,
	FGuid ObjectBinding
)
{
	return MakeShareable(new FChronicle_SubtitleSectionPainter(SectionObject));
}

bool FChronicle_SubtitleTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const
{
	return TrackClass == UChronicle_SubtitleTrack::StaticClass();
}