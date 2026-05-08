#pragma once

#include "FChronicle_EmotionAnimationEntry.h"
#include "IChronicle_CharacterSet.h"

struct FChronicle_AnimationData;
struct FChronicle_Character;

class CHARACTERSYSTEMEDITOR_API FChronicle_CharacterSet : public IChronicle_CharacterSet
{
public:
	virtual FChronicle_AnimationData GetRandomAnimation(const FGuid& Id, const FGuid& EmotionId) const override;
	virtual void Refresh(const TArray<FChronicle_Character>& Characters) override;
	virtual TArray<TSharedPtr<FGuid>> GetSharedIds() const override;
	virtual FName GetName(FGuid Id) const override;
	virtual bool IsValid(FGuid Id) const override;
	
private:
	TMap<FGuid, TArray<FChronicle_EmotionAnimationEntry>> EmotionAnimationsById;
	TMap<FGuid, TArray<FChronicle_AnimationData>> FallbackAnimationsById;
	TArray<TSharedPtr<FGuid>> Ids;
	TMap<FGuid, FName> NamesById;
	FName Directory;
};
