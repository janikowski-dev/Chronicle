#pragma once

#include "CoreMinimal.h"
#include "FChronicle_AnimationData.h"
#include "MovieSceneExecutionToken.h"

struct CINEMATICTIMELINE_API FChronicle_AnimationExecutionToken : IMovieSceneExecutionToken
{
	FChronicle_AnimationData AnimationData;
	
	explicit FChronicle_AnimationExecutionToken(const FChronicle_AnimationData& InAnimationData) : AnimationData(InAnimationData)
	{
	}

	virtual void Execute(
		const FMovieSceneContext& Context,
		const FMovieSceneEvaluationOperand& Operand,
		FPersistentEvaluationData& PersistentData,
		IMovieScenePlayer& Player
	) override;
};