#include "FCharacterSystemEditorModule.h"

#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FDialogueSystemModule"

void FCharacterSystemEditorModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAdvancedAssetCategory(
		FName("Chronicle"),
		FText::FromString("Chronicle")
	);
}

void FCharacterSystemEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCharacterSystemEditorModule, CharacterSystemEditor)