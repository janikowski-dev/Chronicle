#pragma once
#include "FChronicle_EmotionData.h"

#include "UChronicle_EmotionsFunctionLibrary.generated.h"

UCLASS()
class CHRONICLECOREEDITOR_API UChronicle_EmotionsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Chronicle|Core")
	static TArray<FChronicle_EmotionData> GetAll();
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Core")
	static FChronicle_EmotionData Add();
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Core")
	static void Remove(const FGuid& Id);
	
	UFUNCTION(BlueprintCallable, Category="Chronicle|Core")
	static void Rename(const FGuid& Id, const FString& Name);
};