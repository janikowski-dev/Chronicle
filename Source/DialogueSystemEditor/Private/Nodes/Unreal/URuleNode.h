#pragma once

#include "CoreMinimal.h"
#include "URuleNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual void PostPlacedNewNode() override;
	virtual bool CanUserDeleteNode() const override;
	
	virtual bool AllowMultipleInputs() const;
	virtual FText GetTitle() const;
	virtual FSlateColor GetBackgroundColor() const;

private:
	void AssignId();

public:
	FGuid Id;
};