#include "FRuleAsset_Actions.h"

#include "RuleSystem/URuleAsset.h"

FColor FRuleAsset_Actions::GetTypeColor() const
{
	return FColor::Green;
}

FText FRuleAsset_Actions::GetName() const
{
	return FText::FromString("Rule Asset");
}

UClass* FRuleAsset_Actions::GetSupportedClass() const
{
	return URuleAsset::StaticClass();
}

uint32 FRuleAsset_Actions::GetCategories()
{
	return FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().FindAdvancedAssetCategory(FName("Chronicle"));
}
