#pragma once

#include "CoreMinimal.h"
#include "UDialogueNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
    virtual void PostPlacedNewNode() override;
	
	UEdGraph* GetOrCreateInnerGraph();

private:
	void AssignId();
	
public:
	UPROPERTY()
	bool bIsCollapsed = false;
	UPROPERTY()
	bool bIsHidden = false;
	UPROPERTY()
	FGuid Id;
};