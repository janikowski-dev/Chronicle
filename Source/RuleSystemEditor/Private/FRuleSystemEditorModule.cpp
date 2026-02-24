#include "FRuleSystemEditorModule.h"

#include "AssetToolsModule.h"
#include "FRuleAsset_Actions.h"

#define LOCTEXT_NAMESPACE "FRuleSystemModule"

void FRuleSystemEditorModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAdvancedAssetCategory(
		FName("Chronicle"),
		FText::FromString("Chronicle")
	);
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAssetTypeActions(
		MakeShared<FRuleAsset_Actions>()
	);
}

void FRuleSystemEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FRuleSystemEditorModule, RuleSystemEditor)