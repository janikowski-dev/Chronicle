#pragma once

#include "EConditionNodeType.h"
#include "FRuleData.generated.h"

USTRUCT()
struct FRuleData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	EConditionNodeType Type = EConditionNodeType::Raw;

	UPROPERTY(VisibleAnywhere)
	TArray<FGuid> Input;
	
	UPROPERTY(VisibleAnywhere)
	TArray<FGuid> Output;
	
	UPROPERTY(VisibleAnywhere)
	FGuid Id;
};