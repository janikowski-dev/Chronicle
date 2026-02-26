#include "FDialogueGraph_AddNode.h"
#include "EdGraph/EdGraph.h"
#include "Graphs/UDialogueGraph.h"

UEdGraphNode* FDialogueGraph_AddNode::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin* FromPin,
	const FVector2f& Location,
	const bool bSelectNewNode
)
{
	UEdGraphNode* NewNode = CreateNewNode(ParentGraph);
	TryAttachingPin(ParentGraph, NewNode, FromPin);
	Cast<UDialogueGraph>(ParentGraph)->Refresh();
	return NewNode;
}

UEdGraphNode* FDialogueGraph_AddNode::CreateNewNode(UEdGraph* ParentGraph) const
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

void FDialogueGraph_AddNode::TryAttachingPin(
	const UEdGraph* ParentGraph,
	UEdGraphNode* NewNode,
	UEdGraphPin* FromPin
) const
{
	if (!FromPin)
	{
		return;
	}
	
	UEdGraphPin* TargetPin = nullptr;

	for (UEdGraphPin* Pin : NewNode->Pins)
	{
		if (Pin->Direction == FromPin->Direction || Pin->PinType.PinCategory != FromPin->PinType.PinCategory)
		{
			continue;
		}
		
		TargetPin = Pin;
		break;
	}

	if (!TargetPin)
	{
		return;
	}

	ParentGraph->GetSchema()->TryCreateConnection(
		FromPin,
		TargetPin
	);
}
