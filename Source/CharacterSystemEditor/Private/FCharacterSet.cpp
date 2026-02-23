#include "FCharacterSet.h"

#include "UCharacterAsset.h"
#include "AssetRegistry/AssetRegistryModule.h"

FCharacterSet::FCharacterSet(const FName& Directory) : Directory(Directory)
{
}

FName FCharacterSet::GetName(const FGuid Id) const
{
	if (FName const* Found = NamesById.Find(Id))
	{
		return *Found;
	}

	return NAME_None;
}

TArray<TSharedPtr<FGuid>> FCharacterSet::GetSharedIds() const
{
	return Ids;
}

bool FCharacterSet::IsValid(const FGuid Id) const
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

void FCharacterSet::Refresh()
{
	NamesById.Empty();
	Ids.Empty();

	const IAssetRegistry& AssetRegistry = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry").Get();

	FARFilter Filter;
	Filter.ClassPaths.Add(FTopLevelAssetPath(UCharacterAsset::StaticClass()));
	Filter.PackagePaths.Add(Directory);
	Filter.bRecursivePaths = true;

	TArray<FAssetData> CharacterAssets;
	AssetRegistry.GetAssets(Filter, CharacterAssets);

	for (const FAssetData& AssetData : CharacterAssets)
	{
		if (const UCharacterAsset* Asset = Cast<UCharacterAsset>(AssetData.GetAsset()))
		{
			TSharedPtr<FGuid> SharedCharacterId = MakeShared<FGuid>(Asset->CharacterId);
			NamesById.Add(Asset->CharacterId, Asset->CharacterName);
			Ids.Add(SharedCharacterId);

			UE_LOG(LogTemp, Warning, TEXT("Loaded Character Asset: %s | CharacterId: %s"), 
				*Asset->CharacterName.ToString(), 
				*Asset->CharacterId.ToString()
			);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Loaded Character Assets"));
}
