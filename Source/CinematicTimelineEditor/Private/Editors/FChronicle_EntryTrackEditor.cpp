#include "FChronicle_EntryTrackEditor.h"
#include "SequencerSectionPainter.h"
#include "Sequences/Entry/UChronicle_EntryTrack.h"

class FChronicle_EntrySectionPainter : public ISequencerSection
{
public:
	UMovieSceneSection& SectionObject;
	
public:
	explicit FChronicle_EntrySectionPainter(
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

FChronicle_EntryTrackEditor::FChronicle_EntryTrackEditor(
	TSharedRef<ISequencer> InSequencer
) : FMovieSceneTrackEditor(MoveTemp(InSequencer))
{
	
}

TSharedRef<ISequencerTrackEditor> FChronicle_EntryTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer)
{
	return MakeShareable(new FChronicle_EntryTrackEditor(InSequencer));
}

TSharedRef<ISequencerSection> FChronicle_EntryTrackEditor::MakeSectionInterface(
	UMovieSceneSection& SectionObject,
	UMovieSceneTrack& Track,
	FGuid ObjectBinding
)
{
	return MakeShareable(new FChronicle_EntrySectionPainter(SectionObject));
}

bool FChronicle_EntryTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> TrackClass) const
{
	return TrackClass == UChronicle_EntryTrack::StaticClass();
}