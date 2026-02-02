#include "FStoryNodeEditor.h"

#include "GraphEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"
#include "Nodes/Unreal/UStoryNode.h"

static const FName NodeGraphTabName(TEXT("NodeGraph"));

FName FStoryNodeEditor::GetToolkitFName() const
{
	return FName("NodeAssetEditor");
}

FText FStoryNodeEditor::GetBaseToolkitName() const
{
	return FText::FromString("Node Asset Editor");
}

FString FStoryNodeEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("Node");
}

FLinearColor FStoryNodeEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.1f, 0.6f, 1.0f);
}

void FStoryNodeEditor::InitNodeAssetEditor(
	const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UStoryNode* Node
)
{
	const TSharedRef<FTabManager::FLayout> Layout =
		FTabManager::NewLayout("NodeAssetEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(NodeGraphTabName, ETabState::OpenedTab)
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
		Cache(Node)
	);

	RegenerateMenusAndToolbars();
}

void FStoryNodeEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->RegisterTabSpawner(
		NodeGraphTabName,
		FOnSpawnTab::CreateRaw(this, &FStoryNodeEditor::SpawnGraphTab)
	)
	.SetDisplayName(FText::FromString("Node Graph"));
}

void FStoryNodeEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(NodeGraphTabName);
}

TSharedRef<SDockTab> FStoryNodeEditor::SpawnGraphTab(const FSpawnTabArgs&)
{
	UEdGraph* Graph = EditedNode->GetOrCreateInnerGraph();
	
	GraphEditor = SNew(SGraphEditor)
		.GraphToEdit(Graph)
		.IsEditable(true);
	
	return SNew(SDockTab)
		.Label(FText::FromString("Node Graph"))
		[
			GraphEditor.ToSharedRef()
		];
}

TArray<UObject*> FStoryNodeEditor::Cache(UStoryNode* Node)
{
	TArray<UObject*> Result;
	EditedNode = Node;
	Result.Add(Node);
	return Result;
}