#include "FAssetTypeActions_Story.h"
#include "Assets/UStoryAsset.h"
#include "Editors/FStoryAssetEditor.h"

void FAssetTypeActions_Story::OpenAssetEditor(
	const TArray<UObject*>& InObjects,
	const TSharedPtr<IToolkitHost> EditWithinLevelEditor
)
{
	for (UObject* Object : InObjects)
	{
		if (UStoryAsset* StoryAsset = Cast<UStoryAsset>(Object))
		{
			const TSharedRef<FStoryAssetEditor> Editor = MakeShared<FStoryAssetEditor>();

			Editor->InitStoryAssetEditor(
				EToolkitMode::Standalone,
				EditWithinLevelEditor,
				StoryAsset
			);
		}
	}
}
