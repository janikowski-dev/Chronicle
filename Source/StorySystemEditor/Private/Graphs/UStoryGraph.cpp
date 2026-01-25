#include "UStoryGraph.h"

#include "Nodes/URootGraphNode.h"
#include "Nodes/UStoryGraphNode.h"

void UStoryGraph::PostLoad()
{
	Super::PostLoad();
	AutoLayout();
}

void UStoryGraph::AutoLayout() const
{
	constexpr float CellWidth  = 350.0f;
	constexpr float CellHeight = 300.0f;

	UStoryGraphNode* Root = GetRootNode();
	
	if (!Root)
	{
		return;
	}

	TMap<UStoryGraphNode*, FStoryLayoutNode*> LayoutMap;
	FStoryLayoutNode* RootLayout = BuildLayoutTree(Root, LayoutMap);

	float CursorY = 0.0f;
	LayoutSubtree(RootLayout, CursorY, CellHeight);
	ApplyLayout(RootLayout, 0, CellWidth);

	for (const auto& Pair : LayoutMap)
	{
		delete Pair.Value;
	}
}

FStoryLayoutNode* UStoryGraph::BuildLayoutTree(
	UStoryGraphNode* Root,
	TMap<UStoryGraphNode*, FStoryLayoutNode*>& OutMap
) const
{
	auto GetOrCreate = [&](UStoryGraphNode* Node)
	{
		if (!OutMap.Contains(Node))
		{
			OutMap.Add(Node, new FStoryLayoutNode{Node});
		}
		
		return OutMap[Node];
	};

	TQueue<UStoryGraphNode*> Queue;
	Queue.Enqueue(Root);
	GetOrCreate(Root);

	while (!Queue.IsEmpty())
	{
		UStoryGraphNode* Current;
		Queue.Dequeue(Current);

		FStoryLayoutNode* ParentLayout = GetOrCreate(Current);

		for (UEdGraphPin* Pin : Current->Pins)
		{
			if (Pin->Direction != EGPD_Output)
			{
				continue;
			}

			for (const UEdGraphPin* Linked : Pin->LinkedTo)
			{
				auto* Child = Cast<UStoryGraphNode>(Linked->GetOwningNode());
				
				if (!Child)
				{
					continue;
				}

				FStoryLayoutNode* ChildLayout = GetOrCreate(Child);

				if (!ParentLayout->Children.Contains(ChildLayout))
				{
					ParentLayout->Children.Add(ChildLayout);
				}

				Queue.Enqueue(Child);
			}
		}
	}

	return OutMap[Root];
}

float UStoryGraph::LayoutSubtree(
	FStoryLayoutNode* LayoutNode,
	float& CursorY,
	const float VerticalSpacing
) const
{
	if (LayoutNode->bLaidOut)
	{
		return LayoutNode->Y;
	}

	LayoutNode->bLaidOut = true;

	if (LayoutNode->Children.Num() == 0)
	{
		LayoutNode->Y = CursorY;
		CursorY += VerticalSpacing;
		return LayoutNode->Y;
	}

	float FirstY = 0.f;
	float LastY  = 0.f;
	bool bFirst  = true;

	for (FStoryLayoutNode* Child : LayoutNode->Children)
	{
		const float ChildY = LayoutSubtree(Child, CursorY, VerticalSpacing);

		if (bFirst)
		{
			FirstY = ChildY;
			bFirst = false;
		}

		LastY = ChildY;
	}

	LayoutNode->Y = (FirstY + LastY) * 0.5f;
	return LayoutNode->Y;
}

void UStoryGraph::ApplyLayout(
	FStoryLayoutNode* LayoutNode,
	const int32 Depth,
	const float CellWidth
) const
{
	if (!LayoutNode || !LayoutNode->Node)
	{
		return;
	}

	LayoutNode->Node->NodePosX = Depth * CellWidth;
	LayoutNode->Node->NodePosY = LayoutNode->Y;

	for (FStoryLayoutNode* Child : LayoutNode->Children)
	{
		ApplyLayout(Child, Depth + 1, CellWidth);
	}
}

UStoryGraphNode* UStoryGraph::GetRootNode() const
{
	for (UEdGraphNode* Node : Nodes)
	{
		if (auto* Root = Cast<URootGraphNode>(Node))
		{
			return Root;
		}
	}
	
	return nullptr;
}