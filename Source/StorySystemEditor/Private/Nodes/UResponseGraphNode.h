#pragma once

#include "CoreMinimal.h"
#include "UStoryGraphNode.h"
#include "EdGraph/EdGraphNode.h"
#include "UResponseGraphNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UResponseGraphNode : public UStoryGraphNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
};