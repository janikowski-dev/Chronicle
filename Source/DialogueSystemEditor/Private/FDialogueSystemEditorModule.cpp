#include "FDialogueSystemEditorModule.h"

#include "AssetToolsModule.h"
#include "EdGraphUtilities.h"
#include "Actions/FDialogueAsset_Actions.h"
#include "Factories/FRuleNodeFactory.h"
#include "Factories/FDialogueNodeFactory.h"
#include "Utils/FDialogueGraphEditorStyle.h"

#define LOCTEXT_NAMESPACE "FDialogueSystemModule"

void FDialogueSystemEditorModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAssetTypeActions(MakeShared<FDialogueAsset_Actions>());
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShared<FDialogueNodeFactory>());
	FEdGraphUtilities::RegisterVisualNodeFactory(MakeShared<FRuleNodeFactory>());
	FDialogueGraphEditorStyle::Initialize();
}

void FDialogueSystemEditorModule::ShutdownModule()
{
	FDialogueGraphEditorStyle::Shutdown();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)