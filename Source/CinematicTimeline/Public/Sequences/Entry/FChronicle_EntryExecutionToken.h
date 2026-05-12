#pragma once

#include "CoreMinimal.h"
#include "MovieSceneExecutionToken.h"

struct CINEMATICTIMELINE_API FChronicle_EntryExecutionToken : IMovieSceneExecutionToken
{
	FFrameNumber SectionStartFrame;
	FFrameNumber SectionEndFrame;
	FGuid MainParticipantId;
	FGuid CameraId;
	
	explicit FChronicle_EntryExecutionToken(
		const FGuid& InMainParticipantId,
		const FGuid& InCameraId,
		const FFrameNumber& InSectionStartFrame,
		const FFrameNumber& InSectionEndFrame
	) : SectionStartFrame(InSectionStartFrame),SectionEndFrame(InSectionEndFrame), MainParticipantId(InMainParticipantId), CameraId(InCameraId)
	{
	}

	virtual void Execute(
		const FMovieSceneContext& Context,
		const FMovieSceneEvaluationOperand& Operand,
		FPersistentEvaluationData& PersistentData,
		IMovieScenePlayer& Player
	) override;
};