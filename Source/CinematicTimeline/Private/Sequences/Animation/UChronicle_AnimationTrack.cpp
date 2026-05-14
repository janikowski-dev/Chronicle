#include "Sequences/Animation/UChronicle_AnimationTrack.h"

FMovieSceneEvalTemplatePtr UChronicle_AnimationTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const
{
	return FChronicle_AnimationTrackEvaluator(*CastChecked<UChronicle_AnimationSection>(&InSection));
}

UMovieSceneSection* UChronicle_AnimationTrack::CreateNewSection()
{
	return NewObject<UChronicle_AnimationSection>(this, NAME_None, RF_Transactional);
}

void UChronicle_AnimationTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}

void UChronicle_AnimationTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UChronicle_AnimationTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UChronicle_AnimationTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

bool UChronicle_AnimationTrack::IsEmpty() const
{
	return Sections.IsEmpty();
}

bool UChronicle_AnimationTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UChronicle_AnimationSection::StaticClass();
}

const TArray<UMovieSceneSection*>& UChronicle_AnimationTrack::GetAllSections() const
{
	return reinterpret_cast<const TArray<UMovieSceneSection*>&>(Sections);
}