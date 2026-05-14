#include "Sequences/Entry/UChronicle_EntryTrack.h"

#include "Sequences/Entry/FChronicle_EntryTrackEvaluator.h"

FMovieSceneEvalTemplatePtr UChronicle_EntryTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const
{
	return FChronicle_EntryTrackEvaluator(*CastChecked<UChronicle_EntrySection>(&InSection));
}

UMovieSceneSection* UChronicle_EntryTrack::CreateNewSection()
{
	return NewObject<UChronicle_EntrySection>(this, NAME_None, RF_Transactional);
}

void UChronicle_EntryTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}

void UChronicle_EntryTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UChronicle_EntryTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UChronicle_EntryTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

bool UChronicle_EntryTrack::IsEmpty() const
{
	return Sections.IsEmpty();
}

bool UChronicle_EntryTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UChronicle_EntrySection::StaticClass();
}

const TArray<UMovieSceneSection*>& UChronicle_EntryTrack::GetAllSections() const
{
	return reinterpret_cast<const TArray<UMovieSceneSection*>&>(Sections);
}