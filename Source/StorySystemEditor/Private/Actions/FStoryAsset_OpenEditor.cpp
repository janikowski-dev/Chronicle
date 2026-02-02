#include "FStoryAsset_OpenEditor.h"
#include "Assets/UStoryAsset.h"
#include "Editors/FStoryAssetEditor.h"

FText FStoryAsset_OpenEditor::GetName() const
{
	return NSLOCTEXT("Assets", "StoryAsset", "Story Asset");
}

FColor FStoryAsset_OpenEditor::GetTypeColor() const
{
	return FColor::Purple;
}

UClass* FStoryAsset_OpenEditor::GetSupportedClass() const
{
	return UStoryAsset::StaticClass();
}

uint32 FStoryAsset_OpenEditor::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FStoryAsset_OpenEditor::OpenAssetEditor(
	const TArray<UObject*>& InObjects,
	const TSharedPtr<IToolkitHost> EditWithinLevelEditor
)
{
	for (UObject* Object : InObjects)
	{
		UStoryAsset* Asset = Cast<UStoryAsset>(Object);
		
		if (!Asset)
		{
			continue;
		}
		
		const TSharedRef<FStoryAssetEditor> Editor = MakeShared<FStoryAssetEditor>();

		Editor->InitStoryAssetEditor(
			EToolkitMode::Standalone,
			EditWithinLevelEditor,
			Asset
		);
	}
}
