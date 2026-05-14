#pragma once

#include "Subsystems/GameInstanceSubsystem.h"
#include "UChronicle_SubtitleSubsystem.generated.h"

UCLASS()
class SUBTITLESYSTEM_API UChronicle_SubtitleSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
private:
	UPROPERTY()
	UUserWidget* SubtitleWidget = nullptr;

public:
	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	void ShowSubtitle(const FText& Text);

	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	void ShowResponses(const TArray<FText>& Responses);

	UFUNCTION(BlueprintCallable, Category = "Subtitles")
	void HideSubtitles();

private:
	void ShowSubtitleInternal(const FText& Text);
	void ShowResponsesInternal(const TArray<FText>& Responses);
};