#pragma once

#include "AssetTypeActions_Base.h"

class FCharacterAsset_Actions : public FAssetTypeActions_Base
{
public:
	virtual FColor GetTypeColor() const override;
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;
};
