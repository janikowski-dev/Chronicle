#pragma once

#include "FRuleSet.h"

class RULESYSTEMEDITOR_API FRuleDirectory
{
public:
	static FRuleSet& GetConditions();
	static FRuleSet& GetCallbacks();
	static void Refresh();
	
private:
	static FRuleSet Conditions;
	static FRuleSet Callbacks;
};
