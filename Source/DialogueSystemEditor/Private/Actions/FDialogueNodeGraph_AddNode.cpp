#include "FDialogueNodeGraph_AddNode.h"
#include "EdGraph/EdGraph.h"

UEdGraphNode* FDialogueNodeGraph_AddNode::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin*,
	const FVector2f& Location,
	const bool
)
{
	const FScopedTransaction Transaction(NSLOCTEXT("NodeGraph", "AddNode", "Add Node"));
	return CreateNewNode(ParentGraph, Location);
}

UEdGraphNode* FDialogueNodeGraph_AddNode::CreateNewNode(UEdGraph* ParentGraph, const FVector2f& Location) const
{
	ParentGraph->Modify();

	UEdGraphNode* NewNode = NewObject<UEdGraphNode>(
		ParentGraph,
		NodeClass,
		NAME_None,
		RF_Transactional
	);
	
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
	
	NewNode->CreateNewGuid();
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	ParentGraph->AddNode(NewNode, true, true);
	
	return NewNode;
}
