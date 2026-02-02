#include "FStoryNodeGraph_AddNode.h"
#include "EdGraph/EdGraph.h"

UEdGraphNode* FStoryNodeGraph_AddNode::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin* FromPin,
	const FVector2f& Location,
	const bool bSelectNewNode
)
{
	const FScopedTransaction Transaction(NSLOCTEXT("NodeGraph", "AddNode", "Add Node"));
	return CreateNewNode(ParentGraph);
}

UEdGraphNode* FStoryNodeGraph_AddNode::CreateNewNode(UEdGraph* ParentGraph) const
{
	ParentGraph->Modify();

	UEdGraphNode* NewNode = NewObject<UEdGraphNode>(
		ParentGraph,
		NodeClass,
		NAME_None,
		RF_Transactional
	);

	ParentGraph->AddNode(NewNode, true, true);
	NewNode->CreateNewGuid();
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();
	
	return NewNode;
}
