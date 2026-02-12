#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Graphs/UDialogueGraph.h"
#include "Nodes/Unreal/UDialogueNode.h"
#include "UDialogueAsset.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UDialogueGraph> Graph;
	UPROPERTY()
	TMap<TObjectPtr<UDialogueNode>, TObjectPtr<UEdGraph>> InnerGraphsByNode;
};