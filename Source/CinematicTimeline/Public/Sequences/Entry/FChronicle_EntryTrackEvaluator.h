#pragma once

#include "UChronicle_EntrySection.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "FChronicle_EntryTrackEvaluator.generated.h"

USTRUCT()
struct CINEMATICTIMELINE_API FChronicle_EntryTrackEvaluator : public FMovieSceneEvalTemplate
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid MainParticipantId;
	
	UPROPERTY()
	FGuid CameraId;

public:
	FChronicle_EntryTrackEvaluator() = default;
	explicit FChronicle_EntryTrackEvaluator(const UChronicle_EntrySection& InSection);

private:
	virtual UScriptStruct& GetScriptStructImpl() const override;

	virtual void Evaluate(
		const FMovieSceneEvaluationOperand& Operand,
		const FMovieSceneContext& Context,
		const FPersistentEvaluationData& PersistentData,
		FMovieSceneExecutionTokens& ExecutionTokens
	) const override;
};