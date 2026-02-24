#pragma once

#include "UCharacterAssetFactory.generated.h"

class UCharacterAsset;

UCLASS()
class UCharacterAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UCharacterAssetFactory();

	virtual UObject* FactoryCreateNew(UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;

	virtual uint32 GetMenuCategories() const override;
	virtual FText GetDisplayName() const override;
};
