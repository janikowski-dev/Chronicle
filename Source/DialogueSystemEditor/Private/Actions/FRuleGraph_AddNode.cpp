#include "FRuleGraph_AddNode.h"
#include "EdGraph/EdGraph.h"
#include "Nodes/Unreal/URuleInputNode.h"

UEdGraphNode* FRuleGraph_AddNode::PerformAction(
	UEdGraph* ParentGraph,
	UEdGraphPin*,
	const FVector2f& Location,
	const bool
)
{
	return CreateNewNode(ParentGraph, Location);
}

UEdGraphNode* FRuleGraph_AddNode::CreateNewNode(UEdGraph* ParentGraph, const FVector2f& Location) const
{
	ParentGraph->Modify();

	UEdGraphNode* NewNode = NewObject<UEdGraphNode>(
		ParentGraph,
		NodeClass,
		NAME_None,
		RF_Transactional
	);

	if (URuleInputNode* InputNode = Cast<URuleInputNode>(NewNode))
	{
		InputNode->ParameterType = ParameterType;
	}

	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;
	
	NewNode->CreateNewGuid();
	NewNode->PostPlacedNewNode();
	NewNode->AllocateDefaultPins();

	ParentGraph->AddNode(NewNode, true, true);
	
	return NewNode;
}
