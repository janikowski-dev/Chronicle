#include "UStoryGraphSchema.h"
#include "Actions/FStoryGraphSchemaAction_NewNode.h"
#include "Nodes/UStoryGraphNode.h"

void UStoryGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UStoryGraphNode* EntryNode = NewObject<UStoryGraphNode>(&Graph);

	Graph.AddNode(EntryNode, true, false);

	EntryNode->NodePosX = 0;
	EntryNode->NodePosY = 0;

	EntryNode->AllocateDefaultPins();
}

const FPinConnectionResponse UStoryGraphSchema::CanCreateConnection(
	const UEdGraphPin* A,
	const UEdGraphPin* B
) const
{
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(
			CONNECT_RESPONSE_DISALLOW,
			TEXT("Same direction")
		);
	}

	return FPinConnectionResponse(
		CONNECT_RESPONSE_MAKE,
		TEXT("")
	);
}

void UStoryGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	if (ContextMenuBuilder.FromPin)
	{
		return;
	}

	const TSharedPtr<FStoryGraphSchemaAction_NewNode> Action = MakeShared<FStoryGraphSchemaAction_NewNode>();
	ContextMenuBuilder.AddAction(Action);
}