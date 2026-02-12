#include "FDialogueGraph_FocusRoot.h"

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

	Cast<UDialogueGraph>(ParentGraph)->Editor->JumpToNode(Cast<UEdGraphNode>(RootNode));
	return nullptr;
}
