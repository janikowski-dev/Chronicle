#pragma once

#include "CoreMinimal.h"
#include "MovieSceneExecutionToken.h"

struct CINEMATICTIMELINE_API FChronicle_SubtitleExecutionToken : IMovieSceneExecutionToken
{
	FText Subtitle;
	
	explicit FChronicle_SubtitleExecutionToken(const FText& Subtitle) : Subtitle(Subtitle)
	{
	}

	virtual void Execute(
		const FMovieSceneContext& Context,
		const FMovieSceneEvaluationOperand& Operand,
		FPersistentEvaluationData& PersistentData,
		IMovieScenePlayer& Player
	) override;
};