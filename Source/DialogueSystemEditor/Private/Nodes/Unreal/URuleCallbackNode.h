#pragma once

#include "URuleNode.h"
#include "URuleCallbackNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleCallbackNode : public URuleNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
};
