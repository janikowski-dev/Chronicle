#pragma once

#include "CoreMinimal.h"
#include "FChronicle_AnimationData.h"
#include "AChronicle_CharacterActor.generated.h"

UCLASS()
class CHARACTERSYSTEM_API AChronicle_CharacterActor : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FChronicle_AnimationData IdleAnimationData;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USkeletalMeshComponent> MeshComponent;

public:
    AChronicle_CharacterActor();
    virtual void BeginPlay() override;
    void PlayAnimation(const FChronicle_AnimationData& Data) const;

private:
    UAnimSequence* GetAnimation(const FChronicle_AnimationData& Data) const;
};