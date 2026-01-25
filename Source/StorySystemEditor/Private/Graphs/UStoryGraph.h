#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "UStoryGraph.generated.h"

class UStoryGraphNode;

struct FStoryLayoutNode
{
	UStoryGraphNode* Node = nullptr;
	TArray<FStoryLayoutNode*> Children;
	float Y = 0.f;
	bool bLaidOut = false;
};

UCLASS()
class STORYSYSTEMEDITOR_API UStoryGraph : public UEdGraph
{
	GENERATED_BODY()
public:
	virtual void PostLoad() override;
	UStoryGraphNode* GetRootNode() const;
	
	FStoryLayoutNode* BuildLayoutTree(
		UStoryGraphNode* Root,
		TMap<UStoryGraphNode*, FStoryLayoutNode*>& OutMap
	) const;
	float LayoutSubtree(
		FStoryLayoutNode* LayoutNode,
		float& CursorY,
		float VerticalSpacing
	) const;
	void ApplyLayout(
		FStoryLayoutNode* LayoutNode,
		int32 Depth,
		float CellWidth
	) const;
	void AutoLayout() const;
};