#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UEdGraph* GetOrCreateInnerGraph();

public:
	int32 EditorIndex;
};