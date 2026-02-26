#pragma once

#include "URuleInputNode.h"
#include "URuleConditionNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleConditionNode : public URuleInputNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTitle() const override;
	virtual FSlateColor GetBackgroundColor() const override;
};
