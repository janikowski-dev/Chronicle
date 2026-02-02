#include "UStoryNode.h"

#include "Assets/UStoryAsset.h"
#include "Schemas/UStoryNodeGraphSchema.h"

UEdGraph* UStoryNode::GetOrCreateInnerGraph()
{
	if (UStoryAsset* Asset = GetTypedOuter<UStoryAsset>())
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
	
		InnerGraph->Schema = UStoryNodeGraphSchema::StaticClass();
		InnerGraph->GetSchema()->CreateDefaultNodesForGraph(*InnerGraph);
		Asset->InnerGraphsByNode.Add(this, InnerGraph);
		return InnerGraph;
	}

	return nullptr;
}
