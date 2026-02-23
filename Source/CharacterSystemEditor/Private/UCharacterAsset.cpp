#include "UCharacterAsset.h"

UCharacterAsset::UCharacterAsset()
{
	if (CharacterId.IsValid())
	{
		return;
	}
	
	CharacterId = FGuid::NewGuid();
}