#include "UDialogueGraph.h"

#include "Nodes/Unreal/UDialogueLineNode.h"
#include "Nodes/Unreal/UDialogueResponseNode.h"
#include "Nodes/Unreal/UDialogueRootNode.h"

struct FDialogueLayoutNode
{
	UDialogueNode* Node = nullptr;
	TArray<FDialogueLayoutNode*> Children;
	float Y = 0.0f;
};

void UDialogueGraph::PostLoad()
{
	Super::PostLoad();
	Refresh();
}

void UDialogueGraph::Refresh() const
{
	ApplyLayout();
	ApplyLineIndexes();
	ApplyResponseIndexes();
}

void UDialogueGraph::ApplyLayout() const
{
	constexpr float CellWidth  = 350.0f;
	constexpr float CellHeight = 300.0f;
	float CursorY = 0.0f;

	TMap<UDialogueNode*, FDialogueLayoutNode*> LayoutMap;
	FDialogueLayoutNode* Layout = BuildLayoutTree(GetRootNode(), LayoutMap);
	LayoutSubtree(Layout, CursorY, CellHeight);
	ApplyLayout(Layout, 0, CellWidth);
	
	for (const TPair<UDialogueNode*, FDialogueLayoutNode*>& Iterator : LayoutMap)
	{
		delete Iterator.Value;
	}
}

void UDialogueGraph::ApplyLineIndexes() const
{
	int32 NodeIndex = 0;
	TSet<UDialogueNode*> Visited;
	ApplyLineIndexes(GetRootNode(), NodeIndex, Visited);
}

UDialogueNode* UDialogueGraph::GetRootNode() const
{
	for (UEdGraphNode* Node : Nodes)
	{
		if (UDialogueRootNode* Root = Cast<UDialogueRootNode>(Node))
		{
			return Root;
		}
	}
	
	return nullptr;
}

FDialogueLayoutNode* UDialogueGraph::BuildLayoutTree(
	UDialogueNode* Node,
	TMap<UDialogueNode*, FDialogueLayoutNode*>& LayoutMap
) const
{
	FDialogueLayoutNode*& Layout = LayoutMap.FindOrAdd(Node);
	
	if (Layout)
	{
		return Layout;
	}
	
	Layout = new FDialogueLayoutNode{ Node };

	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (const UEdGraphPin* Linked : Pin->LinkedTo)
		{
			UDialogueNode* Child = Cast<UDialogueNode>(Linked->GetOwningNode());
			
			if (!Child)
			{
				continue;
			}
			
			Layout->Children.Add(BuildLayoutTree(Child, LayoutMap));
		}
	}

	return Layout;
}

float UDialogueGraph::LayoutSubtree(
	FDialogueLayoutNode* Node,
	float& CursorY,
	const float VerticalSpacing
) const
{
	if (Node->Children.IsEmpty())
	{
		Node->Y = CursorY;
		CursorY += VerticalSpacing;
		return Node->Y;
	}

	float MinY = TNumericLimits<float>::Max();
	float MaxY = TNumericLimits<float>::Lowest();

	for (FDialogueLayoutNode* Child : Node->Children)
	{
		const float ChildY = LayoutSubtree(Child, CursorY, VerticalSpacing);
		MinY = FMath::Min(MinY, ChildY);
		MaxY = FMath::Max(MaxY, ChildY);
	}

	Node->Y = (MinY + MaxY) * 0.5f;
	return Node->Y;
}

void UDialogueGraph::ApplyLayout(
	FDialogueLayoutNode* LayoutNode,
	const int32 Depth,
	const float CellWidth
) const
{
	constexpr float InvisibleAndOutOfSightNodeX = -100000.0f;
	
	if (!LayoutNode || !LayoutNode->Node)
	{
		return;
	}

	if (LayoutNode->Node->bIsHidden)
	{
		LayoutNode->Node->NodePosX = InvisibleAndOutOfSightNodeX;
	}
	else
	{
		LayoutNode->Node->NodePosX = Depth * CellWidth;
	}
	
	LayoutNode->Node->NodePosY = LayoutNode->Y;

	for (FDialogueLayoutNode* Child : LayoutNode->Children)
	{
		ApplyLayout(Child, Depth + 1, CellWidth);
	}
}

void UDialogueGraph::ApplyLineIndexes(
	UDialogueNode* Node,
	int32& NodeIndex,
	TSet<UDialogueNode*>& Visited
) const
{
	if (!Node || Visited.Contains(Node))
	{
		return;
	}

	Visited.Add(Node);

	if (UDialogueLineNode* Line = Cast<UDialogueLineNode>(Node))
	{
		Line->LineIndex = ++NodeIndex;
	}

	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (const UEdGraphPin* Linked : Pin->LinkedTo)
		{
			if (UDialogueNode* Child = Cast<UDialogueNode>(Linked->GetOwningNode()))
			{
				ApplyLineIndexes(Child, NodeIndex, Visited);
			}
		}
	}
}

void UDialogueGraph::ApplyResponseIndexes() const
{
	for (UEdGraphNode* GraphNode : Nodes)
	{
		UDialogueLineNode* Line = Cast<UDialogueLineNode>(GraphNode);
		
		if (!Line)
		{
			continue;
		}

		int32 ChildIndex = 0;

		for (UEdGraphPin* Pin : Line->Pins)
		{
			if (Pin->Direction != EGPD_Output)
			{
				continue;
			}

			for (const UEdGraphPin* Linked : Pin->LinkedTo)
			{
				if (UDialogueResponseNode* Response = Cast<UDialogueResponseNode>(Linked->GetOwningNode()))
				{
					Response->ParentIndex = Line->LineIndex;
					Response->OrderIndex = ++ChildIndex;
				}
			}
		}
	}
}
