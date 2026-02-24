#include "UCharacterAssetFactory.h"

#include "CharacterSystem/UCharacterAsset.h"

UCharacterAssetFactory::UCharacterAssetFactory()
{
	SupportedClass = UCharacterAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UCharacterAssetFactory::FactoryCreateNew(UClass* Class,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn
)
{
	return NewObject<UCharacterAsset>(InParent, Class, Name, Flags);
}
