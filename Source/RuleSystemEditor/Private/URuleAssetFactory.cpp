#include "URuleAssetFactory.h"

#include "AssetToolsModule.h"
#include "URuleAsset.h"

URuleAssetFactory::URuleAssetFactory()
{
	SupportedClass = URuleAsset::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* URuleAssetFactory::FactoryCreateNew(UClass* InClass,
	UObject* InParent,
	FName InName,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn
)
{
	return NewObject<URuleAsset>(InParent, InClass, InName, Flags);
}

uint32 URuleAssetFactory::GetMenuCategories() const
{
	return FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().FindAdvancedAssetCategory(FName("Chronicle"));
}

FText URuleAssetFactory::GetDisplayName() const
{
	return FText::FromString("Rule Asset");
}
