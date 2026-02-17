#include "URuleAsset.h"

URuleAsset::URuleAsset()
{
	if (RuleId.IsValid())
	{
		return;
	}
	
	RuleId = FGuid::NewGuid();
}
