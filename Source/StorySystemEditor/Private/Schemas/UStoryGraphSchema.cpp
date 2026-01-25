#include "UStoryGraphSchema.h"
#include "Actions/FGraphSchemaAction_AddNode.h"
#include "Nodes/UDialogueGraphNode.h"
#include "Nodes/UResponseGraphNode.h"
#include "Nodes/URootGraphNode.h"
#include "Policies/StoryConnectionDrawingPolicy.h"

#pragma region Initialization

void UStoryGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	URootGraphNode* EntryNode = NewObject<URootGraphNode>(
		&Graph,
		URootGraphNode::StaticClass(),
		NAME_None,
		RF_Transactional
	);

	Graph.AddNode(EntryNode, true, false);

	EntryNode->CreateNewGuid();
	EntryNode->PostPlacedNewNode();
	EntryNode->AllocateDefaultPins();

	EntryNode->NodePosX = 0;
	EntryNode->NodePosY = 0;
}

#pragma endregion

#pragma region Connection

const FPinConnectionResponse UStoryGraphSchema::CanCreateConnection(
	const UEdGraphPin* A,
	const UEdGraphPin* B
) const
{
	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(
			CONNECT_RESPONSE_DISALLOW,
			TEXT("Pins must be input/output")
		);
	}

	if (A->PinType.PinCategory != B->PinType.PinCategory)
	{
		return FPinConnectionResponse(
			CONNECT_RESPONSE_DISALLOW,
			TEXT("Pin types do not match")
		);
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool UStoryGraphSchema::TryCreateConnection(
	UEdGraphPin* A,
	UEdGraphPin* B
) const
{
	if (!A || !B)
	{
		return false;
	}
	
	if (const FPinConnectionResponse Response = CanCreateConnection(A, B); Response.Response == CONNECT_RESPONSE_DISALLOW)
	{
		return false;
	}

	UEdGraph* Graph = A->GetOwningNode()->GetGraph();
	check(Graph);

	Graph->Modify();

	A->Modify();
	B->Modify();

	A->MakeLinkTo(B);

	Graph->NotifyGraphChanged();
	return true;
}

FConnectionDrawingPolicy* UStoryGraphSchema::CreateConnectionDrawingPolicy(
	const int32 InBackLayerID,
	const int32 InFrontLayerID,
	const float InZoomFactor,
	const FSlateRect& InClippingRect,
	FSlateWindowElementList& InDrawElements,
	UEdGraph* InGraphObj
) const
{
	return new FStoryConnectionDrawingPolicy(
		InBackLayerID,
		InFrontLayerID,
		InZoomFactor,
		InClippingRect,
		InDrawElements
	);
}

#pragma endregion

#pragma region Nodes Creation

void AddDialogueAction(FGraphContextMenuBuilder& ContextMenuBuilder)
{
	ContextMenuBuilder.AddAction(MakeShared<FGraphSchemaAction_AddNode>(
		FText::FromString("Dialogue"),
		FText::FromString("Dialogue Node"),
		FText::FromString("Adds a dialogue node"),
		UDialogueGraphNode::StaticClass()
	));
}

void AddResponseAction(FGraphContextMenuBuilder& ContextMenuBuilder)
{
	ContextMenuBuilder.AddAction(MakeShared<FGraphSchemaAction_AddNode>(
		FText::FromString("Response"),
		FText::FromString("Response Node"),
		FText::FromString("Adds a response node"),
		UResponseGraphNode::StaticClass()
	));
}

bool HasChildOfType(const UEdGraphNode* Node, UClass* ChildClass)
{
	for (const UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (const UEdGraphPin* Linked : Pin->LinkedTo)
		{
			if (!Linked || !Linked->GetOwningNode()->IsA(ChildClass))
			{
				continue;
			}
			
			return true;
		}
	}

	return false;
}

bool HasAnyChild(const UEdGraphNode* Node)
{
	for (const UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}
		
		for (const UEdGraphPin* Linked : Pin->LinkedTo)
		{
			if (Linked)
			{
				return true;
			}
		}
	}

	return false;
}

void AddDialogueContext(const UDialogueGraphNode* Node, FGraphContextMenuBuilder& ContextMenuBuilder)
{
	if (HasChildOfType(Node, UResponseGraphNode::StaticClass()))
	{
		AddResponseAction(ContextMenuBuilder);
	}
	else if (!HasAnyChild(Node))
	{
		AddDialogueAction(ContextMenuBuilder);
		AddResponseAction(ContextMenuBuilder);
	}
}

void AddResponseContext(const UResponseGraphNode* Node, FGraphContextMenuBuilder& ContextMenuBuilder)
{
	if (HasAnyChild(Node))
	{
		return;
	}
	
	AddDialogueAction(ContextMenuBuilder);
}

void AddRootContext(FGraphContextMenuBuilder& ContextMenuBuilder)
{
	AddDialogueAction(ContextMenuBuilder);
}

void UStoryGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	if (!ContextMenuBuilder.FromPin)
	{
		return;
	}

	const UEdGraphNode* FromNode = ContextMenuBuilder.FromPin->GetOwningNode();
	Super::GetGraphContextActions(ContextMenuBuilder);

	if (const UDialogueGraphNode* DialogueNode = Cast<UDialogueGraphNode>(FromNode))
	{
		AddDialogueContext(DialogueNode, ContextMenuBuilder);
	}
	
	if (const UResponseGraphNode* ResponseNode = Cast<UResponseGraphNode>(FromNode))
	{
		AddResponseContext(ResponseNode, ContextMenuBuilder);
	}
	
	if (Cast<URootGraphNode>(FromNode))
	{
		AddRootContext(ContextMenuBuilder);
	}
}

#pragma endregion
