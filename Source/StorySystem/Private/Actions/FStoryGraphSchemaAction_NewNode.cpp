#include "FStoryGraphSchemaAction_NewNode.h"
#include "Nodes/UStoryGraphNode.h"
#include "EdGraph/EdGraph.h"

FStoryGraphSchemaAction_NewNode::FStoryGraphSchemaAction_NewNode()
	: FEdGraphSchemaAction(
		FText::FromString("Story"),
		FText::FromString("Add Story Node"),
		FText::FromString("Creates a new story node"),
		0
	)
{
}

UEdGraphNode* FStoryGraphSchemaAction_NewNode::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin* FromPin,
	const FVector2f& Location,
	bool bSelectNewNode
)
{
	if (!ParentGraph)
	{
		return nullptr;
	}

	ParentGraph->Modify();

	UStoryGraphNode* NewNode = NewObject<UStoryGraphNode>(ParentGraph);
	ParentGraph->AddNode(NewNode, true, bSelectNewNode);

	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;

	NewNode->AllocateDefaultPins();
	NewNode->AutowireNewNode(FromPin);

	return NewNode;
}
