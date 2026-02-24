#pragma once

#include "URuleAsset.generated.h"

UCLASS()
class RULESYSTEMEDITOR_API URuleAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	URuleAsset();

	virtual void PostDuplicate(EDuplicateMode::Type) override;
	
public:
	UPROPERTY(EditAnywhere)
	FName RuleName;
	UPROPERTY(VisibleAnywhere)
	FGuid RuleId;
};
