#include "UStoryNodeGraphSchema.h"

#include "ToolMenus.h"
#include "ToolMenuSection.h"
#include "Actions/FStoryNodeGraph_AddNode.h"
#include "Nodes/Unreal/URuleAndNode.h"
#include "Nodes/Unreal/URuleConditionNode.h"
#include "Nodes/Unreal/URuleOrNode.h"
#include "Nodes/Unreal/URuleOutputNode.h"

void UStoryNodeGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UEdGraphNode* PreCallbackOutput = MakeShared<FStoryNodeGraph_AddNode>(
		FText::FromString("Nodes"),
		FText::FromString("Output Node"),
		FText::FromString("Adds a output node"),
		URuleOutputNode::StaticClass()
	)->PerformAction(&Graph, nullptr, FVector2f::Zero(), true);
	Cast<URuleOutputNode>(PreCallbackOutput)->Type = EOutputType::PreCallback;
	
	UEdGraphNode* PostCallbackOutput = MakeShared<FStoryNodeGraph_AddNode>(
		FText::FromString("Nodes"),
		FText::FromString("Output Node"),
		FText::FromString("Adds a output node"),
		URuleOutputNode::StaticClass()
	)->PerformAction(&Graph, nullptr, FVector2f::Zero(), true);
	Cast<URuleOutputNode>(PostCallbackOutput)->Type = EOutputType::PostCallback;
	
	UEdGraphNode* PrerequisitesOutput = MakeShared<FStoryNodeGraph_AddNode>(
		FText::FromString("Nodes"),
		FText::FromString("Output Node"),
		FText::FromString("Adds a output node"),
		URuleOutputNode::StaticClass()
	)->PerformAction(&Graph, nullptr, FVector2f::Zero(), true);
	Cast<URuleOutputNode>(PrerequisitesOutput)->Type = EOutputType::Prerequisites;
}

void UStoryNodeGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	ContextMenuBuilder.AddAction(MakeShared<FStoryNodeGraph_AddNode>(
			FText::FromString("Nodes"),
			FText::FromString("Condition Node"),
			FText::FromString("Adds a condition node"),
			URuleConditionNode::StaticClass()
		)
	);
	
	ContextMenuBuilder.AddAction(MakeShared<FStoryNodeGraph_AddNode>(
			FText::FromString("Nodes"),
			FText::FromString("And Node"),
			FText::FromString("Adds an and node"),
			URuleAndNode::StaticClass()
		)
	);
	
	ContextMenuBuilder.AddAction(MakeShared<FStoryNodeGraph_AddNode>(
			FText::FromString("Nodes"),
			FText::FromString("Or Node"),
			FText::FromString("Adds an or node"),
			URuleOrNode::StaticClass()
		)
	);
}

const FPinConnectionResponse UStoryNodeGraphSchema::CanCreateConnection(
	const UEdGraphPin* A,
	const UEdGraphPin* B
) const
{
	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

bool UStoryNodeGraphSchema::TryCreateConnection(
	UEdGraphPin* A,
	UEdGraphPin* B
) const
{
	A->Modify();
	B->Modify();
	A->MakeLinkTo(B);
	return true;
}
