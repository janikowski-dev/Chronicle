#include "UDialogueNode.h"

#include "Assets/UDialogueAsset.h"
#include "Graphs/URuleGraph.h"
#include "Schemas/URuleGraphSchema.h"

void UDialogueNode::PostPlacedNewNode()
{
	Super::PostPlacedNewNode();
	AssignId();
}

FText UDialogueNode::GetTitle() const
{
	return FText::GetEmpty();
}

FText UDialogueNode::GetText() const
{
	return FText::GetEmpty();
}

URuleGraph* UDialogueNode::GetOrCreateInnerGraph()
{
	if (UDialogueAsset* Asset = GetTypedOuter<UDialogueAsset>())
	{
		if (const TObjectPtr<URuleGraph>* Found = Asset->InnerGraphsByNode.Find(this))
		{
			return Found->Get();
		}

		URuleGraph* InnerGraph = NewObject<URuleGraph>(
			Asset,
			URuleGraph::StaticClass(),
			NAME_None,
			RF_Transactional
		);
	
		InnerGraph->Schema = URuleGraphSchema::StaticClass();
		InnerGraph->GetSchema()->CreateDefaultNodesForGraph(*InnerGraph);
		Asset->InnerGraphsByNode.Add(this, InnerGraph);
		return InnerGraph;
	}

	return nullptr;
}

URuleGraph* UDialogueNode::GetInnerGraph() const
{
	if (UDialogueAsset* Asset = GetTypedOuter<UDialogueAsset>())
	{
		if (const TObjectPtr<URuleGraph>* Found = Asset->InnerGraphsByNode.Find(this))
		{
			return Found->Get();
		}
	}

	return nullptr;
}

void UDialogueNode::AssignId()
{
	if (Id.IsValid())
	{
		return;
	}
	
	Id = FGuid::NewGuid();
}
