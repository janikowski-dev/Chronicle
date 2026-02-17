#pragma once

class URuleAsset;

class RULESYSTEMEDITOR_API FRuleSet
{
public:
	explicit FRuleSet(const FName& Directory);
	
public:
	TArray<TSharedPtr<FGuid>> GetSharedIds() const;
	FName GetName(FGuid Id) const;
	bool IsValid(FGuid Id) const;
	
	void Refresh();
	
private:
	TArray<TSharedPtr<FGuid>> Ids;
	TMap<FGuid, FName> NamesById;
	FName Directory;
};
