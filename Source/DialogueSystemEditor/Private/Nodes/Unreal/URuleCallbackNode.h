#pragma once

#include "URuleTagNode.h"
#include "URuleCallbackNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleCallbackNode : public URuleTagNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTitle() const override;
	virtual FSlateColor GetBackgroundColor() const override;
};
