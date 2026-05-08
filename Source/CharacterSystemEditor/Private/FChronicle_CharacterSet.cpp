#include "FChronicle_CharacterSet.h"

#include "FChronicle_Character.h"

void FChronicle_CharacterSet::Refresh(const TArray<FChronicle_Character>& Characters)
{
	for (const FChronicle_Character& Character : Characters)
	{
		const bool bContainsId = Ids.ContainsByPredicate([&](const TSharedPtr<FGuid>& Id)
		{
			return *Id == Character.Id;
		});
		
		if (bContainsId)
		{
			FallbackAnimationsById[Character.Id] = Character.FallbackAnimations;
			EmotionAnimationsById[Character.Id] = Character.AnimationEntries;
			NamesById[Character.Id] = Character.Name;
		}
		else
		{
			TSharedPtr<FGuid> SharedId = MakeShared<FGuid>(Character.Id);
			FallbackAnimationsById.Add(Character.Id, Character.FallbackAnimations);
			EmotionAnimationsById.Add(Character.Id, Character.AnimationEntries);
			NamesById.Add(Character.Id, Character.Name);
			Ids.Add(SharedId);
		}
	}
}

FName FChronicle_CharacterSet::GetName(const FGuid Id) const
{
	if (FName const* Found = NamesById.Find(Id))
	{
		return *Found;
	}

	return NAME_None;
}

TArray<TSharedPtr<FGuid>> FChronicle_CharacterSet::GetSharedIds() const
{
	return Ids;
}

FChronicle_AnimationData FChronicle_CharacterSet::GetRandomAnimation(const FGuid& Id, const FGuid& EmotionId) const
{
	if (TArray<FChronicle_EmotionAnimationEntry> const* Found = EmotionAnimationsById.Find(Id); Found && Found->Num() > 0)
	{
		for (const FChronicle_EmotionAnimationEntry& Entry : *Found)
		{
			if (Entry.EmotionId.Value != EmotionId || Entry.Sequences.Num() < 1)
			{
				continue;
			}
			
			const int32 Index = FMath::RandHelper(Entry.Sequences.Num());
			return Entry.Sequences[Index];
		}
	}
	
	if (TArray<FChronicle_AnimationData> const* Found = FallbackAnimationsById.Find(Id); Found && Found->Num() > 0)
	{
		const int32 RandomIndex = FMath::RandRange(0, Found->Num() - 1);
		return Found->operator[](RandomIndex);
	}

	return {};
}

bool FChronicle_CharacterSet::IsValid(const FGuid Id) const
{
	for (const TSharedPtr<FGuid>& IdPointer : Ids)
	{
		if (IdPointer.IsValid() && *IdPointer == Id)
		{
			return true;
		}
	}
	return false;
}
