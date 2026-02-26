#include "FRuleDirectory.h"

#include "RuleSystem/ERuleParameterType.h"

FRuleSet FRuleDirectory::IntegerParameterConditions(FName("/Game/Rules/Conditions"), ERuleParameterType::Integer);
FRuleSet FRuleDirectory::IntegerParameterCallbacks(FName("/Game/Rules/Callbacks"), ERuleParameterType::Integer);

FRuleSet FRuleDirectory::CharacterParameterConditions(FName("/Game/Rules/Conditions"), ERuleParameterType::CharacterId);
FRuleSet FRuleDirectory::CharacterParameterCallbacks(FName("/Game/Rules/Callbacks"), ERuleParameterType::CharacterId);

FRuleSet FRuleDirectory::NoParameterConditions(FName("/Game/Rules/Conditions"), ERuleParameterType::None);
FRuleSet FRuleDirectory::NoParameterCallbacks(FName("/Game/Rules/Callbacks"), ERuleParameterType::None);

FRuleSet& FRuleDirectory::GetConditions(const ERuleParameterType ParameterType)
{
	switch (ParameterType)
	{
	case ERuleParameterType::None:
		return NoParameterConditions;
	case ERuleParameterType::CharacterId:
		return CharacterParameterConditions;
	case ERuleParameterType::Integer:
		return IntegerParameterConditions;
	}

	return NoParameterConditions;
}

FRuleSet& FRuleDirectory::GetCallbacks(const ERuleParameterType ParameterType)
{
	switch (ParameterType)
	{
	case ERuleParameterType::None:
		return NoParameterCallbacks;
	case ERuleParameterType::CharacterId:
		return CharacterParameterCallbacks;
	case ERuleParameterType::Integer:
		return IntegerParameterCallbacks;
	}

	return NoParameterCallbacks;
}

void FRuleDirectory::Refresh()
{
	NoParameterCallbacks.Refresh();
	CharacterParameterCallbacks.Refresh();
	IntegerParameterCallbacks.Refresh();
	NoParameterConditions.Refresh();
	CharacterParameterConditions.Refresh();
	IntegerParameterConditions.Refresh();
}
