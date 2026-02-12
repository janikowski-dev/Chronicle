#include "FDialogueNodeEditor.h"

#include "GraphEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Framework/Docking/TabManager.h"
#include "Nodes/Unreal/UDialogueNode.h"

static const FName NodeGraphTabName(TEXT("NodeGraph"));

FName FDialogueNodeEditor::GetToolkitFName() const
{
	return FName("NodeAssetEditor");
}

FText FDialogueNodeEditor::GetBaseToolkitName() const
{
	return FText::FromString("Node Asset Editor");
}

FString FDialogueNodeEditor::GetWorldCentricTabPrefix() const
{
	return TEXT("Node");
}

FLinearColor FDialogueNodeEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.1f, 0.6f, 1.0f);
}

void FDialogueNodeEditor::InitNodeAssetEditor(
	const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost,
	UDialogueNode* Node
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

void FDialogueNodeEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->RegisterTabSpawner(
		NodeGraphTabName,
		FOnSpawnTab::CreateRaw(this, &FDialogueNodeEditor::SpawnGraphTab)
	)
	.SetDisplayName(FText::FromString("Node Graph"));
}

void FDialogueNodeEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	InTabManager->UnregisterTabSpawner(NodeGraphTabName);
}

TSharedRef<SDockTab> FDialogueNodeEditor::SpawnGraphTab(const FSpawnTabArgs&)
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

TArray<UObject*> FDialogueNodeEditor::Cache(UDialogueNode* Node)
{
	TArray<UObject*> Result;
	EditedNode = Node;
	Result.Add(Node);
	return Result;
}