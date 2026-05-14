#include "Sequences/Subtitle/UChronicle_SubtitleTrack.h"

#include "Sequences/Subtitle/FChronicle_SubtitleTrackEvaluator.h"

FMovieSceneEvalTemplatePtr UChronicle_SubtitleTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const
{
	return FChronicle_SubtitleTrackEvaluator(*CastChecked<UChronicle_SubtitleSection>(&InSection));
}

UMovieSceneSection* UChronicle_SubtitleTrack::CreateNewSection()
{
	return NewObject<UChronicle_SubtitleSection>(this, NAME_None, RF_Transactional);
}

void UChronicle_SubtitleTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}

void UChronicle_SubtitleTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UChronicle_SubtitleTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UChronicle_SubtitleTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

bool UChronicle_SubtitleTrack::IsEmpty() const
{
	return Sections.IsEmpty();
}

bool UChronicle_SubtitleTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UChronicle_SubtitleSection::StaticClass();
}

const TArray<UMovieSceneSection*>& UChronicle_SubtitleTrack::GetAllSections() const
{
	return reinterpret_cast<const TArray<UMovieSceneSection*>&>(Sections);
}