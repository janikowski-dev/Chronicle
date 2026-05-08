#include "AChronicle_CinematicSequenceActor.h"

#include "AChronicle_CharacterActor.h"
#include "CineCameraActor.h"
#include "LevelSequencePlayer.h"
#include "Components/InstancedStaticMeshComponent.h"

void AChronicle_CinematicSequenceActor::UpdateParticipantsPreview(UInstancedStaticMeshComponent* MeshComponent)
{
#if WITH_EDITORONLY_DATA
    if (!MeshComponent)
    {
        return;
    }
    
    MeshComponent->ClearInstances();

    for (const FTransform& Transform : ParticipantTransforms)
    {
        MeshComponent->AddInstance(Transform, false);
    }
#endif
}

void AChronicle_CinematicSequenceActor::UpdateCamerasPreview(UInstancedStaticMeshComponent* MeshComponent)
{
#if WITH_EDITORONLY_DATA
    if (!MeshComponent)
    {
        return;
    }
    
    MeshComponent->ClearInstances();

    const FQuat RotationDelta = FQuat(FVector::UpVector, FMath::DegreesToRadians(90.0f));

    for (FTransform Transform : CameraTransforms)
    {
        Transform.SetRotation(RotationDelta * Transform.GetRotation());
        MeshComponent->AddInstance(Transform, false);
    }
#endif
}
void AChronicle_CinematicSequenceActor::PlayDefaultIdleAnimations(ALevelSequenceActor* LevelSequenceActor)
{
    const ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->GetSequence());

    if (!LevelSequence)
    {
        return;
    }

    UMovieScene* MovieScene = LevelSequence->GetMovieScene();

    if (!MovieScene)
    {
        return;
    }

    ULevelSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();

    if (!Player)
    {
        return;
    }

    const int32 SpawnableCount = MovieScene->GetSpawnableCount();

    for (int i = 0; i < SpawnableCount; i++)
    {
        TArray<UObject*> BoundObjects = Player->GetBoundObjects(FMovieSceneObjectBindingID(MovieScene->GetSpawnable(i).GetGuid()));

        for (UObject* BoundObject : BoundObjects)
        {
            AChronicle_CharacterActor* Actor = Cast<AChronicle_CharacterActor>(BoundObject);

            if (!Actor)
            {
                continue;
            }

            Actor->PlayAnimation(Actor->IdleAnimationData);
        }
    }
}

void AChronicle_CinematicSequenceActor::OffsetSpawnableTransforms(
    ALevelSequenceActor* LevelSequenceActor,
    const FVector& LocationOffset,
    const FRotator& RotationOffset
)
{
    const ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->GetSequence());
    
    if (!LevelSequence)
    {
        return;
    }

    UMovieScene* MovieScene = LevelSequence->GetMovieScene();
    
    if (!MovieScene)
    {
        return;
    }

    ULevelSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();

    const FTransform ParentTransform(RotationOffset, LocationOffset);

    for (int i = 0; i < MovieScene->GetSpawnableCount(); i++)
    {
        TArray<UObject*> BoundObjects = Player->GetBoundObjects(FMovieSceneObjectBindingID(MovieScene->GetSpawnable(i).GetGuid()));

        for (UObject* BoundObject : BoundObjects)
        {
            AActor* Actor = Cast<AActor>(BoundObject);
            const FTransform LocalTransform = Actor->GetActorTransform();
            const FTransform WorldTransform = LocalTransform * ParentTransform;
            Actor->SetActorTransform(WorldTransform);
        }
    }
}

void AChronicle_CinematicSequenceActor::OffsetResponseCamera(
    const ALevelSequenceActor* LevelSequenceActor,
    const FTransform& ResponseCameraTransform,
    const FVector& LocationOffset,
    const FRotator& RotationOffset
)
{
    ULevelSequencePlayer* Player = LevelSequenceActor->GetSequencePlayer();
    const ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->GetSequence());
    UMovieScene* MovieScene = LevelSequence->GetMovieScene();

    const FTransform ParentTransform(RotationOffset, LocationOffset);

    for (int i = 0; i < MovieScene->GetSpawnableCount(); i++)
    {
        const FMovieSceneSpawnable& Spawnable = MovieScene->GetSpawnable(i);
        
        if (!Spawnable.GetObjectTemplate()->IsA<ACineCameraActor>())
        {
            continue;
        }

        TArray<UObject*> BoundObjects = Player->GetBoundObjects(FMovieSceneObjectBindingID(Spawnable.GetGuid()));

        for (UObject* BoundObject : BoundObjects)
        {
            AActor* Actor = Cast<AActor>(BoundObject);
            
            if (!Actor)
            {
                continue;
            }

            const FTransform WorldTransform = ResponseCameraTransform * ParentTransform;
            Actor->SetActorTransform(WorldTransform);
        }
    }
}

void AChronicle_CinematicSequenceActor::SetPlaybackPosition(
    ALevelSequenceActor* LevelSequenceActor,
    const FFrameNumber StartFrame
)
{
    const ULevelSequence* LevelSequence = Cast<ULevelSequence>(LevelSequenceActor->GetSequence());
    const UMovieScene* MovieScene = LevelSequence->GetMovieScene();
    
    const FFrameRate TickResolution = MovieScene->GetTickResolution();
    const FFrameRate DisplayRate = MovieScene->GetDisplayRate();

    const double Seconds = TickResolution.AsSeconds(StartFrame);
    const FFrameTime DisplayFrame = DisplayRate.AsFrameTime(Seconds);

    FMovieSceneSequencePlaybackParams Params;
    
    Params.Frame = DisplayFrame;
    Params.PositionType = EMovieScenePositionType::Frame;
    Params.UpdateMethod = EUpdatePositionMethod::Jump;

    LevelSequenceActor->GetSequencePlayer()->SetPlaybackPosition(Params);
}
