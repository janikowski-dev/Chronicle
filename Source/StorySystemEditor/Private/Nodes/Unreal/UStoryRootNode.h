#pragma once

#include "CoreMinimal.h"
#include "UStoryNode.h"
#include "UStoryRootNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API UStoryRootNode : public UStoryNode
{
	GENERATED_BODY()

public:
	virtual void AllocateDefaultPins() override;
};