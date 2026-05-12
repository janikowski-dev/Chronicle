#include "Sequences/Entry/FChronicle_EntryTrackEvaluator.h"

#include "Sequences/Entry/FChronicle_EntryExecutionToken.h"

FChronicle_EntryTrackEvaluator::FChronicle_EntryTrackEvaluator(
	const UChronicle_EntrySection& InSection
) : MainParticipantId(InSection.MainParticipantId), CameraId(InSection.CameraId)
{
}

UScriptStruct& FChronicle_EntryTrackEvaluator::GetScriptStructImpl() const
{
	return *StaticStruct();
}

void FChronicle_EntryTrackEvaluator::Evaluate(
	const FMovieSceneEvaluationOperand& Operand,
	const FMovieSceneContext& Context,
	const FPersistentEvaluationData& PersistentData,
	FMovieSceneExecutionTokens& ExecutionTokens
) const
{
	const UMovieSceneSection* Source = GetSourceSection();
	const FFrameNumber StartFrame = Source->GetInclusiveStartFrame();
	const FFrameNumber EndFrame = Source->GetExclusiveEndFrame();
	ExecutionTokens.Add(FChronicle_EntryExecutionToken(MainParticipantId, CameraId, StartFrame, EndFrame));
}
