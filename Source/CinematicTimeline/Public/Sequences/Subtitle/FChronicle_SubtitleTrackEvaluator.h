#pragma once

#include "UChronicle_SubtitleSection.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "FChronicle_SubtitleTrackEvaluator.generated.h"

USTRUCT()
struct CINEMATICTIMELINE_API FChronicle_SubtitleTrackEvaluator : public FMovieSceneEvalTemplate
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FText Subtitle;

public:
	FChronicle_SubtitleTrackEvaluator() = default;
	explicit FChronicle_SubtitleTrackEvaluator(const UChronicle_SubtitleSection& InSection);

private:
	virtual UScriptStruct& GetScriptStructImpl() const override;

	virtual void Evaluate(
		const FMovieSceneEvaluationOperand& Operand,
		const FMovieSceneContext& Context,
		const FPersistentEvaluationData& PersistentData,
		FMovieSceneExecutionTokens& ExecutionTokens
	) const override;
};