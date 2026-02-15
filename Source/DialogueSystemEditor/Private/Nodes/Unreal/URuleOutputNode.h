#pragma once

#include "URuleNode.h"
#include "URuleOutputNode.generated.h"

UENUM()
enum class EOutputType : int8
{
	PreCallback,
	PostCallback,
	Requirements
};

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleOutputNode : public URuleNode
{
	GENERATED_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual bool AllowMultipleInputs() const override;
	virtual FText GetTitle() const override;
	virtual FSlateColor GetBackgroundColor() const override;
	
public:
	UPROPERTY()
	EOutputType Type;
};
