#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "Toolkits/IToolkitHost.h"

class UDialogueAsset;

class DIALOGUESYSTEMEDITOR_API FDialogueAssetEditor : public FAssetEditorToolkit
{
public:
	void InitDialogueAssetEditor(
		const EToolkitMode::Type Mode,
		const TSharedPtr<IToolkitHost>& InitToolkitHost,
		UDialogueAsset* Asset
	);
	
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

private:
	TSharedRef<SDockTab> SpawnGraphTab(const FSpawnTabArgs& Args);
	TArray<UObject*> Cache(UDialogueAsset* Asset);

private:
	TSharedPtr<SGraphEditor> GraphEditor;
	UDialogueAsset* EditedAsset = nullptr;
};