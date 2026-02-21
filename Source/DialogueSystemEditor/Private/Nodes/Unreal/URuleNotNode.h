#pragma once

#include "URuleNode.h"
#include "URuleNotNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleNotNode : public URuleNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetTitle() const override;
	virtual FSlateColor GetBackgroundColor() const override;
};
