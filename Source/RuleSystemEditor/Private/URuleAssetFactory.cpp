#include "URuleAssetFactory.h"

#include "RuleSystem/URuleAsset.h"

URuleAssetFactory::URuleAssetFactory()
{
	SupportedClass = URuleAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* URuleAssetFactory::FactoryCreateNew(UClass* Class,
	UObject* InParent,
	FName Name,
	EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn
)
{
	return NewObject<URuleAsset>(InParent, Class, Name, Flags);
}
