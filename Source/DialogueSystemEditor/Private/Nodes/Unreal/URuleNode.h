#pragma once

#include "CoreMinimal.h"
#include "URuleNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual bool AllowMultipleInputs() const;
	virtual FText GetTitle() const;
	virtual FSlateColor GetBackgroundColor() const;
};