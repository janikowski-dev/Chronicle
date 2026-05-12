#include "Sequences/Entry/FChronicle_EntryExecutionToken.h"

#include "IMovieScenePlayer.h"
#include "Evaluation/MovieScenePlayback.h"

// Quite a few magic numbers here, but it's a throw-away script anyways.
// Basically it pans the camera on the beginning of a cinematic.
void FChronicle_EntryExecutionToken::Execute(
	const FMovieSceneContext& Context,
	const FMovieSceneEvaluationOperand& Operand,
	FPersistentEvaluationData& PersistentData,
	IMovieScenePlayer& Player
)
{
	const TArrayView<TWeakObjectPtr<>> BoundCameras = Player.FindBoundObjects(CameraId, Operand.SequenceID);
	const TArrayView<TWeakObjectPtr<>> BoundParticipants = Player.FindBoundObjects(MainParticipantId, Operand.SequenceID);
	const AActor* ParticipantActor = Cast<AActor>(BoundParticipants[0].Get());
	AActor* CameraActor = Cast<AActor>(BoundCameras[0].Get());

	const FTransform MainParticipantTransform = ParticipantActor->GetActorTransform();
	
	const FFrameRate TickResolution = Context.GetFrameRate();
	const double CurrentSeconds = TickResolution.AsSeconds(Context.GetTime().FrameNumber);
	const double StartSeconds = TickResolution.AsSeconds(SectionStartFrame);
	const double EndSeconds = TickResolution.AsSeconds(SectionEndFrame);
	const double SectionLength = EndSeconds - StartSeconds;
	
	const float Alpha = SectionLength > KINDA_SMALL_NUMBER
		? FMath::Clamp(static_cast<float>((CurrentSeconds - StartSeconds) / SectionLength), 0.0f, 1.0f)
		: 0.0f;
	
	const FVector LocalPosition  = FMath::Lerp(FVector(-25.0f, -100.0f, 75.0f), FVector(-75.0f, -100.0f, 135.0f), Alpha);
	const FVector WorldPosition  = MainParticipantTransform.TransformPosition(LocalPosition);
	
	const FRotator BaseRotation = MainParticipantTransform.GetRotation().Rotator();
	const FRotator FinalRotation = BaseRotation + FRotator(0.0f, 85.0f, 0.0f);

	CameraActor->SetActorLocationAndRotation(WorldPosition, FinalRotation);
}
	