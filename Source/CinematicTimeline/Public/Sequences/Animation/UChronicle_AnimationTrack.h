#pragma once

#include "FChronicle_AnimationTrackEvaluator.h"
#include "MovieSceneNameableTrack.h"
#include "Compilation/IMovieSceneTrackTemplateProducer.h"
#include "UChronicle_AnimationTrack.generated.h"

UCLASS()
class CINEMATICTIMELINE_API UChronicle_AnimationTrack : public UMovieSceneNameableTrack, public IMovieSceneTrackTemplateProducer
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TArray<TObjectPtr<UMovieSceneSection>> Sections;

public:
	virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const override;
	virtual UMovieSceneSection* CreateNewSection() override;
	virtual void AddSection(UMovieSceneSection& Section) override;
	virtual void RemoveSection(UMovieSceneSection& Section) override;
	virtual void RemoveSectionAt(int32 SectionIndex) override;
	virtual bool HasSection(const UMovieSceneSection& Section) const override;
	virtual bool IsEmpty() const override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const override;
	virtual const TArray<UMovieSceneSection*>& GetAllSections() const override;
};