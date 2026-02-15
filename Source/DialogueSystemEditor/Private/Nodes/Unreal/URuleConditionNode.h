#pragma once

#include "URuleTagNode.h"
#include "URuleConditionNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleConditionNode : public URuleTagNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTitle() const override;
	virtual FSlateColor GetBackgroundColor() const override;
};
