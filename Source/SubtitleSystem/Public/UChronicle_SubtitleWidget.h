#pragma once

#include "UObject/Interface.h"
#include "UChronicle_SubtitleWidget.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UChronicle_SubtitleWidget : public UInterface
{
	GENERATED_BODY()
};

class SUBTITLESYSTEM_API IChronicle_SubtitleWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Chronicle|Subtitles")
	void SetSubtitleText(const FText& Text);

	UFUNCTION(BlueprintNativeEvent, Category="Chronicle|Subtitles")
	void SetResponses(const TArray<FText>& Responses);
};