#include "UCharacterAsset.h"

UCharacterAsset::UCharacterAsset()
{
	if (CharacterId.IsValid())
	{
		return;
	}
	
	CharacterId = FGuid::NewGuid();
}

void UCharacterAsset::PostDuplicate(EDuplicateMode::Type)
{
	CharacterId = FGuid::NewGuid();
}
