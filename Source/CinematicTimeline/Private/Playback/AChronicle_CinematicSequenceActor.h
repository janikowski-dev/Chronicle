#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "AChronicle_CinematicSequenceActor.generated.h"

UCLASS()
class CINEMATICTIMELINE_API AChronicle_CinematicSequenceActor : public AActor
{
	GENERATED_BODY()

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chronicle|Debug")
	TArray<FTransform> ParticipantTransforms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Chronicle|Debug")
	TArray<FTransform> CameraTransforms;
#endif

public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Chronicle|Runtime")
	void UpdateParticipantsPreview(UInstancedStaticMeshComponent* MeshComponent);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Chronicle|Runtime")
	void UpdateCamerasPreview(UInstancedStaticMeshComponent* MeshComponent);
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Runtime")
	static void PlayDefaultIdleAnimations(ALevelSequenceActor* LevelSequenceActor);
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Runtime")
	static void OffsetSpawnableTransforms(
		ALevelSequenceActor* LevelSequenceActor,
		const FVector& LocationOffset,
		const FRotator& RotationOffset
	);
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Cinematics")
	static void OffsetResponseCamera(
		const ALevelSequenceActor* LevelSequenceActor,
		const FTransform& ResponseCameraTransform,
		const FVector& LocationOffset,
		const FRotator& RotationOffset
	);
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Runtime")
	static void LockOnTheLastFrame(ALevelSequenceActor* LevelSequenceActor);
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Runtime")
	static void SetPlaybackPosition(
		ALevelSequenceActor* LevelSequenceActor,
		FFrameNumber StartFrame
	);
};