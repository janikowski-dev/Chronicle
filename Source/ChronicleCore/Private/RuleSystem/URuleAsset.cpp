#include "RuleSystem/URuleAsset.h"

URuleAsset::URuleAsset()
{
	if (RuleId.IsValid())
	{
		return;
	}
	
	RuleId = FGuid::NewGuid();
}

void URuleAsset::PostDuplicate(EDuplicateMode::Type)
{
	RuleId = FGuid::NewGuid();
}
