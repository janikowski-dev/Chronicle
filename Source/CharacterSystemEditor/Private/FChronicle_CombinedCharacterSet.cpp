#include "FChronicle_CombinedCharacterSet.h"

#include "FChronicle_AnimationData.h"
#include "FChronicle_CharacterSet.h"

FChronicle_CombinedCharacterSet::FChronicle_CombinedCharacterSet(FChronicle_CharacterSet& InSet1, FChronicle_CharacterSet& InSet2)
	: Set1(InSet1)
	, Set2(InSet2)
{
}

void FChronicle_CombinedCharacterSet::Refresh(const TArray<FChronicle_Character>& Characters)
{
}

TArray<TSharedPtr<FGuid>> FChronicle_CombinedCharacterSet::GetSharedIds() const
{
	TArray<TSharedPtr<FGuid>> Combined = Set1.GetSharedIds();
	Combined.Append(Set2.GetSharedIds());
	return Combined;
}

FChronicle_AnimationData FChronicle_CombinedCharacterSet::GetRandomAnimation(const FGuid& Id, const FGuid& EmotionId) const
{
	FChronicle_AnimationData Sequence1 = Set1.GetRandomAnimation(Id, EmotionId);
	
	if (Sequence1 != FChronicle_AnimationData{})
	{
		return Sequence1;
	}

	FChronicle_AnimationData Sequence2 = Set2.GetRandomAnimation(Id, EmotionId);
	
	if (Sequence2 != FChronicle_AnimationData{})
	{
		return Sequence2;
	}

	return {};
}

FName FChronicle_CombinedCharacterSet::GetName(const FGuid Id) const
{
	if (const FName Name = Set1.GetName(Id); !Name.IsNone())
	{
		return Name;
	}

	if (const FName Name = Set2.GetName(Id); !Name.IsNone())
	{
		return Name;
	}

	return NAME_None;
}

bool FChronicle_CombinedCharacterSet::IsValid(const FGuid Id) const
{
	return Set1.IsValid(Id) || Set2.IsValid(Id);
}
