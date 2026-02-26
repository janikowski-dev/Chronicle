#pragma once

enum class ERuleParameterType : uint8;
class URuleAsset;

class RULESYSTEMEDITOR_API FRuleSet
{
public:
	explicit FRuleSet(const FName& Directory, const ERuleParameterType& ParameterType);
	
public:
	TArray<TSharedPtr<FGuid>> GetSharedIds() const;
	FName GetName(FGuid Id) const;
	bool IsValid(FGuid Id) const;
	
	void Refresh();
	
private:
	ERuleParameterType ParameterType;
	TArray<TSharedPtr<FGuid>> Ids;
	TMap<FGuid, FName> NamesById;
	FName Directory;
};
