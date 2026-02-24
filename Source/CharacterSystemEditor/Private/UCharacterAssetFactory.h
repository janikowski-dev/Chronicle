#pragma once

#include "UCharacterAssetFactory.generated.h"

UCLASS()
class UCharacterAssetFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UCharacterAssetFactory();

	virtual UObject* FactoryCreateNew(UClass* Class,
		UObject* InParent,
		FName Name,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
};