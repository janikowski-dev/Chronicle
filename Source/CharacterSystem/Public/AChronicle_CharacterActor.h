#pragma once

#include "CoreMinimal.h"
#include "FChronicle_AnimationData.h"
#include "GameFramework/Character.h"
#include "AChronicle_CharacterActor.generated.h"

UCLASS()
class CHARACTERSYSTEM_API AChronicle_CharacterActor : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FChronicle_AnimationData IdleAnimationData;

public:
	AChronicle_CharacterActor();
	void PlayAnimation(const FChronicle_AnimationData& Data) const;
	
private:
	UAnimSequence* GetAnimation(const FChronicle_AnimationData& Data) const;
};
