#include "UCharacterAssetFactory.h"

#include "AssetToolsModule.h"
#include "UCharacterAsset.h"

UCharacterAssetFactory::UCharacterAssetFactory()
{
	SupportedClass = UCharacterAsset::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UCharacterAssetFactory::FactoryCreateNew(UClass* InClass,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn
)
{
	return NewObject<UCharacterAsset>(InParent, InClass, InName, Flags);
}

uint32 UCharacterAssetFactory::GetMenuCategories() const
{
	return FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().FindAdvancedAssetCategory(FName("Chronicle"));
}

FText UCharacterAssetFactory::GetDisplayName() const
{
	return FText::FromString("Character Asset");
}
