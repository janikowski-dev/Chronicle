#include "Sequences/Animation/FChronicle_AnimationExecutionToken.h"
#include "AChronicle_CharacterActor.h"
#include "IMovieScenePlayer.h"

void FChronicle_AnimationExecutionToken::Execute(
	const FMovieSceneContext& Context,
	const FMovieSceneEvaluationOperand& Operand,
	FPersistentEvaluationData& PersistentData,
	IMovieScenePlayer& Player
)
{
	for (TWeakObjectPtr BoundObject : Player.FindBoundObjects(Operand))
	{
		if (AChronicle_CharacterActor* Character = Cast<AChronicle_CharacterActor>(BoundObject.Get()))
		{
			Character->PlayAnimation(AnimationData);
		}
	}
}