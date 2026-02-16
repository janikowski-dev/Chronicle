#include "UDialogueNode.h"

#include "Assets/UDialogueAsset.h"
#include "Graphs/URuleGraph.h"
#include "Schemas/UDialogueNodeGraphSchema.h"

void UDialogueNode::PostPlacedNewNode()
{
	Super::PostPlacedNewNode();
	AssignId();
}

FText UDialogueNode::GetTitle()
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
	
		InnerGraph->Schema = UDialogueNodeGraphSchema::StaticClass();
		InnerGraph->GetSchema()->CreateDefaultNodesForGraph(*InnerGraph);
		Asset->InnerGraphsByNode.Add(this, InnerGraph);
		return InnerGraph;
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
