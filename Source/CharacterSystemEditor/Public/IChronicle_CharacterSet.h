#pragma once

#include "FChronicle_AnimationData.h"

struct FChronicle_Character;

class CHARACTERSYSTEMEDITOR_API IChronicle_CharacterSet
{
public:
	virtual ~IChronicle_CharacterSet() = default;

public:
	virtual FChronicle_AnimationData GetRandomAnimation(const FGuid& Id, const FGuid& EmotionId) const = 0;
	virtual void Refresh(const TArray<FChronicle_Character>& Characters) = 0;
	virtual TArray<TSharedPtr<FGuid>> GetSharedIds() const = 0;
	virtual FName GetName(FGuid Id) const = 0;
	virtual bool IsValid(FGuid Id) const = 0;
};