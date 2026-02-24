#include "FCharacterSystemEditorModule.h"

#include "AssetToolsModule.h"
#include "FCharacterAsset_Actions.h"

#define LOCTEXT_NAMESPACE "FCharacterSystemModule"

void FCharacterSystemEditorModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAdvancedAssetCategory(
		FName("Chronicle"),
		FText::FromString("Chronicle")
	);
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAssetTypeActions(
		MakeShared<FCharacterAsset_Actions>()
	);
}

void FCharacterSystemEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCharacterSystemEditorModule, CharacterSystemEditor)