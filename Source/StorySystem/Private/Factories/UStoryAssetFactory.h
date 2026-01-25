#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UStoryAssetFactory.generated.h"

UCLASS()
class STORYSYSTEM_API UStoryAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UStoryAssetFactory();

	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
};