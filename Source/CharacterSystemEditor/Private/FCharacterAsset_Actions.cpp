#include "FCharacterAsset_Actions.h"

#include "CharacterSystem/UCharacterAsset.h"

FColor FCharacterAsset_Actions::GetTypeColor() const
{
	return FColor::Blue;
}

FText FCharacterAsset_Actions::GetName() const
{
	return FText::FromString("Character Asset");
}

UClass* FCharacterAsset_Actions::GetSupportedClass() const
{
	return UCharacterAsset::StaticClass();
}

uint32 FCharacterAsset_Actions::GetCategories()
{
	return FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().FindAdvancedAssetCategory(FName("Chronicle"));
}
