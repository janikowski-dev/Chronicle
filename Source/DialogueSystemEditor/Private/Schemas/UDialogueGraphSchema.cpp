#include "UDialogueGraphSchema.h"

#include "Policies/FDialogueGraphConnectionDrawingPolicy.h"
#include "Actions/FDialogueGraph_AddNode.h"
#include "Nodes/Unreal/UDialogueResponseNode.h"
#include "Nodes/Unreal/UDialogueRootNode.h"
#include "Nodes/Unreal/UDialogueLineNode.h"
#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "Actions/FDialogueGraph_DeleteNodeWithChildren.h"
#include "Actions/FDialogueGraph_FocusRoot.h"
#include "Nodes/Unreal/UDialogueLinkNode.h"

#pragma region Initialization

void UDialogueGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	MakeShared<FDialogueGraph_AddNode>(
		UDialogueRootNode::StaticClass()
	)->PerformAction(&Graph,nullptr, FVector2f::Zero());
}

#pragma endregion

#pragma region Connection

FConnectionDrawingPolicy* UDialogueGraphSchema::CreateConnectionDrawingPolicy(
	const int32 InBackLayerID,
	const int32 InFrontLayerID,
	const float InZoomFactor,
	const FSlateRect& InClippingRect,
	FSlateWindowElementList& InDrawElements,
	UEdGraph* InGraphObj
) const
{
	return new FDialogueGraphConnectionDrawingPolicy(
		InBackLayerID,
		InFrontLayerID,
		InZoomFactor,
		InClippingRect,
		InDrawElements
	);
}

const FPinConnectionResponse UDialogueGraphSchema::CanCreateConnection(
	const UEdGraphPin* A,
	const UEdGraphPin* B
) const
{
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool UDialogueGraphSchema::TryCreateConnection(
	UEdGraphPin* A,
	UEdGraphPin* B
) const
{
	A->Modify();
	B->Modify();
	A->MakeLinkTo(B);
	return true;
}

#pragma endregion

#pragma region Additional Actions

void UDialogueGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	ContextMenuBuilder.AddAction(MakeShared<FDialogueGraph_FocusRoot>());
}

#pragma endregion

#pragma region Node Creation

void UDialogueGraphSchema::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection* Section = CreateSection(Menu, Context);

	if (!Section)
	{
		return;
	}

	AddLineContext(Context, Section);
	AddResponseContext(Context, Section);
	AddRootContext(Context, Section);
	AddLinkContext(Context, Section);
}

void UDialogueGraphSchema::AddLineContext(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	const UDialogueLineNode* Node = Cast<UDialogueLineNode>(Context->Node);
	
	if (!Node)
	{
		return;
	}
	
	AddResponseAction(Context, Section);
	AddLineAction(Context, Section);
	AddLinkAction(Context, Section);
	AddDeleteAction(Context, Section);
}

void UDialogueGraphSchema::AddLinkContext(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	const UDialogueLinkNode* Node = Cast<UDialogueLinkNode>(Context->Node);
	
	if (!Node)
	{
		return;
	}
	
	AddDeleteAction(Context, Section);
}

void UDialogueGraphSchema::AddResponseContext(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	const UDialogueResponseNode* Node = Cast<UDialogueResponseNode>(Context->Node);
	
	if (!Node)
	{
		return;
	}
	
	if (!HasAnyChild(Node))
	{
		AddLineAction(Context, Section);
		AddLinkAction(Context, Section);
	}
	
	AddDeleteAction(Context, Section);
}

void UDialogueGraphSchema::AddRootContext(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	const UDialogueRootNode* Node = Cast<UDialogueRootNode>(Context->Node);
	
	if (!Node)
	{
		return;
	}
	
	if (HasAnyChild(Node))
	{
		return;
	}
	
	AddLineAction(Context, Section);
}

void UDialogueGraphSchema::AddLineAction(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	UEdGraph* Graph = const_cast<UEdGraph*>(Context->Graph.Get());
	UEdGraphPin* Pin = GetOutputPin(Context->Node);
	
	Section->AddMenuEntry(
		"AddLineNode",
		FText::FromString("Line Node"),
		FText::FromString("Adds a line node"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([Graph, Pin]
			{
				MakeShared<FDialogueGraph_AddNode>(
					UDialogueLineNode::StaticClass()
				)->PerformAction(Graph, Pin, FVector2f::Zero(), true);
			})
		)
	);
}

void UDialogueGraphSchema::AddLinkAction(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	UEdGraph* Graph = const_cast<UEdGraph*>(Context->Graph.Get());
	UEdGraphPin* Pin = GetOutputPin(Context->Node);
	
	Section->AddMenuEntry(
		"AddLinkNode",
		FText::FromString("Link Node"),
		FText::FromString("Adds a link node"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([Graph, Pin]
			{
				MakeShared<FDialogueGraph_AddNode>(
					UDialogueLinkNode::StaticClass()
				)->PerformAction(Graph, Pin, FVector2f::Zero(), true);
			})
		)
	);
}

void UDialogueGraphSchema::AddResponseAction(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	UEdGraph* Graph = const_cast<UEdGraph*>(Context->Graph.Get());
	UEdGraphPin* Pin = GetOutputPin(Context->Node);
	
	Section->AddMenuEntry(
		"AddResponseNode",
		FText::FromString("Response Node"),
		FText::FromString("Adds a response node"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([Graph, Pin]
			{
				MakeShared<FDialogueGraph_AddNode>(
					UDialogueResponseNode::StaticClass()
				)->PerformAction(Graph, Pin, FVector2f::Zero(), true);
			})
		)
	);
}

void UDialogueGraphSchema::AddDeleteAction(const UGraphNodeContextMenuContext* Context, FToolMenuSection* Section) const
{
	UEdGraph* Graph = const_cast<UEdGraph*>(Context->Graph.Get());
	UEdGraphPin* Pin = Context->Node->Pins[0];
	
	Section->AddMenuEntry(
		"DeleteNode",
		FText::FromString("Delete Node"),
		FText::FromString("Deletes node and its' children"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda([Graph, Pin]
			{
				MakeShared<FDialogueGraph_DeleteNodeWithChildren>()->PerformAction(Graph, Pin, FVector2f::Zero(), true);
			})
		)
	);
}

bool UDialogueGraphSchema::HasChildOfType(const UEdGraphNode* Node, UClass* ChildClass) const
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

bool UDialogueGraphSchema::HasAnyChild(const UEdGraphNode* Node) const
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

FToolMenuSection* UDialogueGraphSchema::CreateSection(UToolMenu* Menu, const UGraphNodeContextMenuContext* Context) const
{
	if (!Context->Node)
	{
		return nullptr;
	}
	
	return &Menu->AddSection("SchemaNode", FText::FromString("Schema"));
}

UEdGraphPin* UDialogueGraphSchema::GetOutputPin(const UEdGraphNode* Node) const
{
	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin && Pin->Direction == EGPD_Output)
		{
			return Pin;
		}
	}
	return nullptr;
}

#pragma endregion
