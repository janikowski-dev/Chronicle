#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "UDialogueGraph.generated.h"

struct FDialogueLayoutNode;
class UDialogueNode;

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	virtual void PostLoad() override;
	UDialogueNode* GetRootNode() const;
	void Refresh() const;
	
private:
	void ApplyLayout() const;
	void ApplyLineIndexes() const;
	
	FDialogueLayoutNode* BuildLayoutTree(
		UDialogueNode* Node,
		TMap<UDialogueNode*, FDialogueLayoutNode*>& LayoutMap
	) const;
	
	float LayoutSubtree(
		FDialogueLayoutNode* Node,
		float& CursorY,
		float VerticalSpacing
	) const;
	
	void ApplyLayout(
		FDialogueLayoutNode* LayoutNode,
		int32 Depth,
		float CellWidth
	) const;

	void ApplyLineIndexes(
		UDialogueNode* Node,
		int32& NodeIndex,
		TSet<UDialogueNode*>& Visited
	) const;

	void ApplyResponseIndexes() const;

public:
	TArray<TSharedPtr<FGuid>> SharedParticipantIds;
	
	UPROPERTY()
	TArray<FGuid> ParticipantIds;
};