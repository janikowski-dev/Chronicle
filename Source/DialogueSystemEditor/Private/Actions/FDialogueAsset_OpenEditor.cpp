#include "FDialogueAsset_OpenEditor.h"
#include "Assets/UDialogueAsset.h"
#include "Editors/FDialogueAssetEditor.h"

FText FDialogueAsset_OpenEditor::GetName() const
{
	return NSLOCTEXT("Assets", "DialogueAsset", "Dialogue Asset");
}

FColor FDialogueAsset_OpenEditor::GetTypeColor() const
{
	return FColor::Purple;
}

UClass* FDialogueAsset_OpenEditor::GetSupportedClass() const
{
	return UDialogueAsset::StaticClass();
}

uint32 FDialogueAsset_OpenEditor::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FDialogueAsset_OpenEditor::OpenAssetEditor(
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
