#include "UDialogueAssetFactory.h"
#include "Assets/UDialogueAsset.h"
#include "Graphs/UDialogueGraph.h"
#include "Schemas/UDialogueGraphSchema.h"

UDialogueAssetFactory::UDialogueAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UDialogueAsset::StaticClass();
}

UObject* UDialogueAssetFactory::FactoryCreateNew(
	UClass* InClass,
	UObject* InParent,
	const FName InName,
	const EObjectFlags Flags,
	UObject* Context,
	FFeedbackContext* Warn
)
{
	UDialogueAsset* Asset = NewObject<UDialogueAsset>(
		InParent,
		InClass,
		InName,
		Flags | RF_Transactional
	);

	Asset->Graph = NewObject<UDialogueGraph>(
		Asset,
		UDialogueGraph::StaticClass(),
		NAME_None,
		RF_Transactional
	);

	Asset->Graph->Schema = UDialogueGraphSchema::StaticClass();
	Asset->Graph->GetSchema()->CreateDefaultNodesForGraph(*Asset->Graph);
	Asset->Graph->Modify();
	Asset->Modify();

	return Asset;
}