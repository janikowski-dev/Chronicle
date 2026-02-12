#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "UDialogueAssetFactory.generated.h"

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueAssetFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDialogueAssetFactory();

	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
};