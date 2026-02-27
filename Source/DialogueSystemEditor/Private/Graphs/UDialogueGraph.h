#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "UDialogueGraph.generated.h"

struct FDialogueLayoutNode;
class UDialogueLineNode;
class UDialogueNode;

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueGraph : public UEdGraph
{
	GENERATED_BODY()

public:
	virtual void PostLoad() override;
	virtual void Serialize(FStructuredArchive::FRecord Record) override;
	
	UDialogueNode* GetRootNode() const;
	void Refresh();

	bool HasParticipant(const TSharedPtr<FGuid>& Id) const;
	void AddParticipant(const TSharedPtr<FGuid>& Id);
	void RemoveParticipant(const TSharedPtr<FGuid>& Id);
	
private:
	void ApplyLayout() const;
	void IndexLines() const;
	
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

	void IndexLines(
		UDialogueNode* Node,
		int32& NodeIndex,
		TSet<UDialogueNode*>& Visited
	) const;

	void IndexResponses() const;

	bool TrySave(FStructuredArchive::FRecord Record);
	bool TryLoad(FStructuredArchive::FRecord Record);
	
	bool HasParticipantInternal(const TSharedPtr<FGuid>& Id) const;
	void AddParticipantInternal(const TSharedPtr<FGuid>& Id);
	void RemoveParticipantInternal(const TSharedPtr<FGuid>& Id);
	
	void SortParticipants();

	void CacheLines();

public:
	TArray<TWeakObjectPtr<UDialogueLineNode>> LineNodes;
	TArray<TSharedPtr<FGuid>> SharedParticipantIds;
	
	UPROPERTY()
	TArray<FGuid> ParticipantIds;
};