#include "Sequences/Subtitle/FChronicle_SubtitleExecutionToken.h"

#include "IMovieScenePlayer.h"
#include "UChronicle_SubtitleSubsystem.h"

void FChronicle_SubtitleExecutionToken::Execute(
	const FMovieSceneContext& Context,
	const FMovieSceneEvaluationOperand& Operand,
	FPersistentEvaluationData& PersistentData,
	IMovieScenePlayer& Player
)
{
	const UObject* PlaybackContext = Player.GetPlaybackContext();
	const UWorld* World = PlaybackContext->GetWorld();
	const UGameInstance* GameInstance = World->GetGameInstance();
	
	if (!GameInstance)
	{
		return;
	}

	if (UChronicle_SubtitleSubsystem* SubtitleSubsystem = GameInstance->GetSubsystem<UChronicle_SubtitleSubsystem>())
	{
		SubtitleSubsystem->ShowSubtitle(Subtitle);
	}
}
