#pragma once

#include "CoreMinimal.h"
#include "UDialogueNode.generated.h"

class URuleGraph;

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
    virtual void PostPlacedNewNode() override;
	
	virtual FText GetTitle() const;
	virtual FText GetText() const;
	
	URuleGraph* GetOrCreateInnerGraph();
	URuleGraph* GetInnerGraph() const;

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