#include "FChronicle_CoreEditorModule.h"

#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FChronicleCoreEditorModule"

void FChronicle_CoreEditorModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get().RegisterAdvancedAssetCategory(
		FName("Chronicle"),
		FText::FromString("Chronicle")
	);
}

void FChronicle_CoreEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FChronicle_CoreEditorModule, ChronicleCoreEditor)