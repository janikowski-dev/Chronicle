#pragma once

class UCharacterAsset;

class CHARACTERSYSTEMEDITOR_API FCharacterSet
{
public:
	explicit FCharacterSet(const FName& Directory);
	
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
