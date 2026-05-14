#include "Sequences/Animation/FChronicle_AnimationTrackEvaluator.h"
#include "Sequences/Animation/FChronicle_AnimationExecutionToken.h"

FChronicle_AnimationTrackEvaluator::FChronicle_AnimationTrackEvaluator(
	const UChronicle_AnimationSection& InSection
) : AnimationData(InSection.AnimationData)
{
}

UScriptStruct& FChronicle_AnimationTrackEvaluator::GetScriptStructImpl() const
{
	return *StaticStruct();
}

void FChronicle_AnimationTrackEvaluator::Evaluate(
	const FMovieSceneEvaluationOperand& Operand,
	const FMovieSceneContext& Context,
	const FPersistentEvaluationData& PersistentData,
	FMovieSceneExecutionTokens& ExecutionTokens
) const
{
	ExecutionTokens.Add(FChronicle_AnimationExecutionToken(AnimationData));
}
