#include "AChronicle_CharacterActor.h"

void AChronicle_CharacterActor::PlayAnimation(const FChronicle_AnimationData& Data)
{
	if (Data.Animation)
	{
		UE_LOG(LogTemp, Log, TEXT("%s is playing animation: %s"), *GetName(), *Data.Animation->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s attempted to play a null animation sequence!"), *GetName());
	}
}
