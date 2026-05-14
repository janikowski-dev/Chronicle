#include "AChronicle_CharacterActor.h"
#include "Animation/AnimSingleNodeInstance.h"

AChronicle_CharacterActor::AChronicle_CharacterActor()
{
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	RootComponent = MeshComponent;
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
		MeshComponent->PlayAnimation(Animation, true);
		MeshComponent->TickAnimation(0.0f, false);
		MeshComponent->RefreshBoneTransforms();
	}
}

UAnimSequence* AChronicle_CharacterActor::GetAnimation(const FChronicle_AnimationData& Data) const
{
	UAnimSequence* Animation = Data.Animation.LoadSynchronous();

	if (!Animation)
	{
		return nullptr;
	}

	UAnimSingleNodeInstance* SingleNode = MeshComponent->GetSingleNodeInstance();

	if (SingleNode && SingleNode->GetCurrentAsset() == Animation)
	{
		return nullptr;
	}

	return Animation;
}