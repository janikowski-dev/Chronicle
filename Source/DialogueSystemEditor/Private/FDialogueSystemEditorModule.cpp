#include "FDialogueSystemEditorModule.h"

#include "AssetToolsModule.h"
#include "EdGraphUtilities.h"
#include "Actions/FDialogueAsset_OpenEditor.h"
#include "Factories/FRuleNodeFactory.h"
#include "Factories/FDialogueNodeFactory.h"

#define LOCTEXT_NAMESPACE "FDialogueSystemModule"

void FDialogueSystemEditorModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAssetTypeActions(MakeShared<FDialogueAsset_OpenEditor>());
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShared<FDialogueNodeFactory>());
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShared<FRuleNodeFactory>());
}

void FDialogueSystemEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)