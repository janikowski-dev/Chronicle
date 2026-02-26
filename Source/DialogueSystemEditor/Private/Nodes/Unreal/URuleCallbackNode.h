#pragma once

#include "URuleInputNode.h"
#include "URuleCallbackNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleCallbackNode : public URuleInputNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTitle() const override;
	virtual FSlateColor GetBackgroundColor() const override;
};
