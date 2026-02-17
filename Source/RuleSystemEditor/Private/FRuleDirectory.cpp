#include "FRuleDirectory.h"

FRuleSet FRuleDirectory::Conditions(FName("/Game/Rules/Conditions"));
FRuleSet FRuleDirectory::Callbacks(FName("/Game/Rules/Callbacks"));

FRuleSet& FRuleDirectory::GetConditions()
{
	return Conditions;
}

FRuleSet& FRuleDirectory::GetCallbacks()
{
	return Callbacks;
}

void FRuleDirectory::Refresh()
{
	Conditions.Refresh();
	Callbacks.Refresh();
}
