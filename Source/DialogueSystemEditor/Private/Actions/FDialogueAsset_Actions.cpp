#include "FDialogueAsset_Actions.h"
#include "Assets/UDialogueAsset.h"
#include "Editors/FDialogueAssetEditor.h"
#include "Export/FDialogueExporter.h"

FText FDialogueAsset_Actions::GetName() const
{
	return NSLOCTEXT("Assets", "DialogueAsset", "Dialogue Asset");
}

FColor FDialogueAsset_Actions::GetTypeColor() const
{
	return FColor::Purple;
}

UClass* FDialogueAsset_Actions::GetSupportedClass() const
{
	return UDialogueAsset::StaticClass();
}

uint32 FDialogueAsset_Actions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FDialogueAsset_Actions::OpenAssetEditor(
	const TArray<UObject*>& InObjects,
	const TSharedPtr<IToolkitHost> EditWithinLevelEditor
)
{
	for (UObject* Object : InObjects)
	{
		UDialogueAsset* Asset = Cast<UDialogueAsset>(Object);
		
		if (!Asset)
		{
			continue;
		}
		
		const TSharedRef<FDialogueAssetEditor> Editor = MakeShared<FDialogueAssetEditor>();

		Editor->InitDialogueAssetEditor(
			EToolkitMode::Standalone,
			EditWithinLevelEditor,
			Asset
		);
	}
}

void FDialogueAsset_Actions::GetActions(const TArray<UObject*>& InObjects, FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString("Export to runtime UObject"),
		FText::FromString("Export dialogue to runtime asset"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Save"),
		FUIAction(FExecuteAction::CreateLambda([InObjects]
		{
			for (UObject* Object : InObjects)
			{
				if (const UDialogueAsset* Asset = Cast<UDialogueAsset>(Object))
				{
					FDialogueExporter::ExportToAsset(Asset);
				}
			}
		}))
	);
	
	MenuBuilder.AddMenuEntry(
		FText::FromString("Copy JSON to clipboard"),
		FText::FromString("Copies asset as JSON to clipboard"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "Icons.Clipboard"),
		FUIAction(FExecuteAction::CreateLambda([InObjects]
		{
			for (UObject* Object : InObjects)
			{
				if (const UDialogueAsset* Asset = Cast<UDialogueAsset>(Object))
				{
					FDialogueExporter::CopyToClipboard(Asset);
				}
			}
		}))
	);
}
