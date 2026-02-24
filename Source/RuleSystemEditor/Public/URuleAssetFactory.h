#pragma once

#include "URuleAssetFactory.generated.h"

class URuleAsset;

UCLASS()
class URuleAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	URuleAssetFactory();

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
