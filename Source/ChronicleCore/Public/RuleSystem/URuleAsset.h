#pragma once
#include "ERuleParameterType.h"

#include "URuleAsset.generated.h"

UCLASS()
class CHRONICLECORE_API URuleAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	URuleAsset();

	virtual void PostDuplicate(EDuplicateMode::Type) override;
	
public:
	UPROPERTY(EditAnywhere)
	ERuleParameterType ParameterType;
	
	UPROPERTY(EditAnywhere)
	FName RuleName;
	
	UPROPERTY(VisibleAnywhere)
	FGuid RuleId;
};
