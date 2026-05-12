#include "Sequences/FChronicle_SubtitleTrackEvaluator.h"

#include "Sequences/FChronicle_SubtitleExecutionToken.h"

FChronicle_SubtitleTrackEvaluator::FChronicle_SubtitleTrackEvaluator(
	const UChronicle_SubtitleSection& InSection
) : Subtitle(InSection.Subtitle)
{
}

UScriptStruct& FChronicle_SubtitleTrackEvaluator::GetScriptStructImpl() const
{
	return *StaticStruct();
}

void FChronicle_SubtitleTrackEvaluator::Evaluate(
	const FMovieSceneEvaluationOperand& Operand,
	const FMovieSceneContext& Context,
	const FPersistentEvaluationData& PersistentData,
	FMovieSceneExecutionTokens& ExecutionTokens
) const
{
	ExecutionTokens.Add(FChronicle_SubtitleExecutionToken(Subtitle));
}
