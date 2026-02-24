#pragma once

#include "URuleAssetFactory.generated.h"

UCLASS()
class URuleAssetFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	URuleAssetFactory();

	virtual UObject* FactoryCreateNew(UClass* Class,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
};