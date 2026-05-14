#include "UChronicle_SubtitleSubsystem.h"

#include "UChronicle_SubtitleSettings.h"
#include "UChronicle_SubtitleWidget.h"
#include "Blueprint/UserWidget.h"
#include "Engine/GameInstance.h"

void UChronicle_SubtitleSubsystem::ShowSubtitle(const FText& Text)
{
    HideSubtitles();
    ShowSubtitleInternal(Text);
}

void UChronicle_SubtitleSubsystem::ShowResponses(const TArray<FText>& Responses)
{
    HideSubtitles();
    ShowResponsesInternal(Responses);
}

void UChronicle_SubtitleSubsystem::HideSubtitles()
{
    if (!SubtitleWidget)
    {
        return;
    }
    
    SubtitleWidget->RemoveFromParent();
    SubtitleWidget = nullptr;
}

void UChronicle_SubtitleSubsystem::ShowSubtitleInternal(const FText& Text)
{
    const TSubclassOf<UUserWidget> WidgetClass = GetDefault<UChronicle_SubtitleSettings>()->SubtitleWidgetClass;
    
    if (!WidgetClass)
    {
        return;
    }

    APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
    SubtitleWidget = CreateWidget<UUserWidget>(PlayerController, WidgetClass);
    
    if (SubtitleWidget && SubtitleWidget->GetClass()->ImplementsInterface(UChronicle_SubtitleWidget::StaticClass()))
    {
        IChronicle_SubtitleWidget::Execute_SetSubtitleText(SubtitleWidget, Text);
        SubtitleWidget->AddToViewport();
    }
}

void UChronicle_SubtitleSubsystem::ShowResponsesInternal(const TArray<FText>& Responses)
{
    const TSubclassOf<UUserWidget> WidgetClass = GetDefault<UChronicle_SubtitleSettings>()->SubtitleWidgetClass;
    
    if (!WidgetClass)
    {
        return;
    }

    APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
    SubtitleWidget = CreateWidget<UUserWidget>(PlayerController, WidgetClass);
    
    if (SubtitleWidget && SubtitleWidget->GetClass()->ImplementsInterface(UChronicle_SubtitleWidget::StaticClass()))
    {
        IChronicle_SubtitleWidget::Execute_SetResponses(SubtitleWidget, Responses);
        SubtitleWidget->AddToViewport();
    }
}