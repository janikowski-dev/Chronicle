#include "FRuleSet.h"

#include "URuleAsset.h"
#include "AssetRegistry/AssetRegistryModule.h"

FRuleSet::FRuleSet(const FName& Directory) : Directory(Directory)
{
}

FName FRuleSet::GetName(const FGuid Id) const
{
	if (FName const* Found = NamesById.Find(Id))
	{
		return *Found;
	}

	return NAME_None;
}

TArray<TSharedPtr<FGuid>> FRuleSet::GetSharedIds() const
{
	return Ids;
}

bool FRuleSet::IsValid(const FGuid Id) const
{
	for (const TSharedPtr<FGuid>& IdPointer : Ids)
	{
		if (IdPointer.IsValid() && *IdPointer == Id)
		{
			return true;
		}
	}
	return false;
}

void FRuleSet::Refresh()
{
	NamesById.Empty();
	Ids.Empty();

	const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	FARFilter Filter;
    Filter.ClassPaths.Add(FTopLevelAssetPath(URuleAsset::StaticClass()));
	Filter.PackagePaths.Add(Directory);
	Filter.bRecursivePaths = true;

	TArray<FAssetData> RuleAssets;
	AssetRegistry.GetAssets(Filter, RuleAssets);

	for (const FAssetData& AssetData : RuleAssets)
	{
		if (const URuleAsset* Asset = Cast<URuleAsset>(AssetData.GetAsset()))
		{
			TSharedPtr<FGuid> SharedRuleId = MakeShared<FGuid>(Asset->RuleId);
			NamesById.Add(Asset->RuleId, Asset->RuleName);
			Ids.Add(SharedRuleId);

			UE_LOG(LogTemp, Warning, TEXT("Loaded Rule Asset: %s | RuleId: %s"), 
				*Asset->RuleName.ToString(), 
				*Asset->RuleId.ToString()
			);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Loaded Rule Assets"));
}
