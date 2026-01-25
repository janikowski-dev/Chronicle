#include "FStorySystemModule.h"
#include "AssetToolsModule.h"
#include "Actions/FAssetTypeActions_Story.h"

#define LOCTEXT_NAMESPACE "FStorySystemModule"

void FStorySystemModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetTools.RegisterAssetTypeActions(MakeShared<FAssetTypeActions_Story>());
}

void FStorySystemModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStorySystemModule, StorySystem)