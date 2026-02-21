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
	FGuid ConditionId;

	UPROPERTY(VisibleAnywhere)
    TArray<int32> InputIndices;
};