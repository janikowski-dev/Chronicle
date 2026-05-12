#include "AChronicle_CharacterActor.h"

#include "Animation/AnimSingleNodeInstance.h"

AChronicle_CharacterActor::AChronicle_CharacterActor()
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
}

void AChronicle_CharacterActor::BeginPlay()
{
	Super::BeginPlay();
	PlayAnimation(IdleAnimationData);
}

void AChronicle_CharacterActor::PlayAnimation(const FChronicle_AnimationData& Data) const
{
	if (UAnimSequence* Animation = GetAnimation(Data))
	{
		GetMesh()->PlayAnimation(Animation, true);
		GetMesh()->TickAnimation(0.0f, false);
		GetMesh()->RefreshBoneTransforms();
	}
}

UAnimSequence* AChronicle_CharacterActor::GetAnimation(const FChronicle_AnimationData& Data) const
{
	UAnimSequence* Animation = Data.Animation.LoadSynchronous();

	if (!Animation)
	{
		return nullptr;
	}
	
	UAnimSingleNodeInstance* SingleNode = GetMesh()->GetSingleNodeInstance();

	if (SingleNode->GetCurrentAsset() == Animation)
	{
		return nullptr;
	}
	
	return Animation;
}
