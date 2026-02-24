#pragma once

#include "UCharacterAsset.generated.h"

UCLASS()
class CHRONICLECORE_API UCharacterAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UCharacterAsset();

	virtual void PostDuplicate(EDuplicateMode::Type) override;
	
public:
	UPROPERTY(EditAnywhere)
	FName CharacterName;
	UPROPERTY(VisibleAnywhere)
	FGuid CharacterId;
};
