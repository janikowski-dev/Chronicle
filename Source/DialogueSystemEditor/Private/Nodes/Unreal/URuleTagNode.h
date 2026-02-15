#pragma once

#include "URuleNode.h"
#include "GameplayTagContainer.h"
#include "URuleTagNode.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API URuleTagNode : public URuleNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	FGameplayTag Tag;
};
