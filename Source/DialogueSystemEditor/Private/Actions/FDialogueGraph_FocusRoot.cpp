#include "FDialogueGraph_FocusRoot.h"

#include "Editors/FDialogueAssetEditor.h"
#include "Nodes/Unreal/UDialogueNode.h"
#include "Graphs/UDialogueGraph.h"

UEdGraphNode* FDialogueGraph_FocusRoot::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin*,
	const FVector2f&,
	bool
)
{
	const UDialogueNode* RootNode = Cast<UDialogueGraph>(ParentGraph)->GetRootNode();
	
	if (!RootNode)
	{
		return nullptr;
	}

	UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
	IAssetEditorInstance* EditorInstance = AssetEditorSubsystem->FindEditorForAsset(ParentGraph->GetOuter(), false);
    
	if (const FDialogueAssetEditor* DialogueEditor = static_cast<FDialogueAssetEditor*>(EditorInstance))
	{
		DialogueEditor->GraphEditor->JumpToNode(Cast<UEdGraphNode>(RootNode));
	}
	
	return nullptr;
}
