#include "UDialogueNode.h"

#include "Assets/UDialogueAsset.h"
#include "Schemas/UDialogueNodeGraphSchema.h"

void UDialogueNode::PostPlacedNewNode()
{
	Super::PostPlacedNewNode();
	AssignId();
}

UEdGraph* UDialogueNode::GetOrCreateInnerGraph()
{
	if (UDialogueAsset* Asset = GetTypedOuter<UDialogueAsset>())
	{
		if (const TObjectPtr<UEdGraph>* Found = Asset->InnerGraphsByNode.Find(this))
		{
			return Found->Get();
		}

		UEdGraph* InnerGraph = NewObject<UEdGraph>(
			Asset,
			UEdGraph::StaticClass(),
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
