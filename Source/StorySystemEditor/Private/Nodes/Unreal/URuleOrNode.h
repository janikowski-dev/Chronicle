#pragma once

#include "URuleNode.h"
#include "URuleOrNode.generated.h"

UCLASS()
class STORYSYSTEMEDITOR_API URuleOrNode : public URuleNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type) const override;
};
