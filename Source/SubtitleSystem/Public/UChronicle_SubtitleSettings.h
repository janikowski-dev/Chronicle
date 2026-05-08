#pragma once

#include "Engine/DeveloperSettings.h"
#include "UChronicle_SubtitleSettings.generated.h"

UCLASS(Config=SubtitleSystem, DefaultConfig, meta=(DisplayName="Subtitles"))
class SUBTITLESYSTEM_API UChronicle_SubtitleSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, Category="Subtitles")
	TSoftClassPtr<UUserWidget> SubtitleWidgetClass;

public:
	virtual FName GetCategoryName() const override;
};
