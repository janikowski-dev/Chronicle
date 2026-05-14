#pragma once

#include "FChronicle_AnimationData.h"
#include "UChronicle_AnimationSection.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "FChronicle_AnimationTrackEvaluator.generated.h"

USTRUCT()
struct CINEMATICTIMELINE_API FChronicle_AnimationTrackEvaluator : public FMovieSceneEvalTemplate
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FChronicle_AnimationData AnimationData;

public:
    FChronicle_AnimationTrackEvaluator() = default;
    explicit FChronicle_AnimationTrackEvaluator(const UChronicle_AnimationSection& InSection);

private:
    virtual UScriptStruct& GetScriptStructImpl() const override;

    virtual void Evaluate(
        const FMovieSceneEvaluationOperand& Operand,
        const FMovieSceneContext& Context,
        const FPersistentEvaluationData& PersistentData,
        FMovieSceneExecutionTokens& ExecutionTokens
    ) const override;
};