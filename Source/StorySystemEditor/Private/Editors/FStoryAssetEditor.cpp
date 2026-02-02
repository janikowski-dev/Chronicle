#include "FStoryAssetEditor.h"

#include "Assets/UStoryAsset.h"
#include "Graphs/UStoryGraph.h"
#include "GraphEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"

static const FName StoryGraphTabName(TEXT("StoryGraph"));

FName FStoryAssetEditor::GetToolkitFName() const
{
	return FName("StoryAssetEditor");
}

FText FStoryAssetEditor::GetBaseToolkitName() const
{
	return FText::FromString("Story Asset Editor");
}

FString FStoryAssetEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("Story");
}

FLinearColor FStoryAssetEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.1f, 0.6f, 1.0f);
}

void FStoryAssetEditor::InitStoryAssetEditor(
	const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UStoryAsset* Asset
)
{
	const TSharedRef<FTabManager::FLayout> Layout =
		FTabManager::NewLayout("StoryAssetEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(StoryGraphTabName, ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		);

	InitAssetEditor(
		Mode,
		InitToolkitHost,
		GetToolkitFName(),
		Layout,
		true,
		true,
		Cache(Asset)
	);

	RegenerateMenusAndToolbars();
}

void FStoryAssetEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->RegisterTabSpawner(
		StoryGraphTabName,
		FOnSpawnTab::CreateRaw(this, &FStoryAssetEditor::SpawnGraphTab)
	)
	.SetDisplayName(FText::FromString("Story Graph"));
}

void FStoryAssetEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(StoryGraphTabName);
}

TSharedRef<SDockTab> FStoryAssetEditor::SpawnGraphTab(const FSpawnTabArgs&)
{
	const TObjectPtr<UStoryGraph> Graph = EditedAsset->Graph;
	
	GraphEditor = SNew(SGraphEditor)
		.GraphToEdit(Graph)
		.IsEditable(true);
	
	Graph->Editor = GraphEditor;

	return SNew(SDockTab)
		.Label(FText::FromString("Story Graph"))
		[
			GraphEditor.ToSharedRef()
		];
}

TArray<UObject*> FStoryAssetEditor::Cache(UStoryAsset* Asset)
{
	TArray<UObject*> Result;
	EditedAsset = Asset;
	Result.Add(Asset);
	return Result;
}