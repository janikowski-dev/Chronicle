#pragma once

#include "FRuleSet.h"

class RULESYSTEMEDITOR_API FRuleDirectory
{
public:
	static FRuleSet& GetConditions(const ERuleParameterType ParameterType);
	static FRuleSet& GetCallbacks(const ERuleParameterType ParameterType);
	static void Refresh();
	
private:
	static FRuleSet IntegerParameterConditions;
	static FRuleSet IntegerParameterCallbacks;
	static FRuleSet CharacterParameterConditions;
	static FRuleSet CharacterParameterCallbacks;
	static FRuleSet NoParameterConditions;
	static FRuleSet NoParameterCallbacks;
};
