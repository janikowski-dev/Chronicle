#include "UChronicle_EmotionsFunctionLibrary.h"

#include "UChronicle_EmotionSettings.h"

TArray<FChronicle_EmotionData> UChronicle_EmotionsFunctionLibrary::GetAll()
{
	return GetMutableDefault<UChronicle_EmotionSettings>()->Emotions;
}

FChronicle_EmotionData UChronicle_EmotionsFunctionLibrary::Add()
{
	UChronicle_EmotionSettings* Settings = GetMutableDefault<UChronicle_EmotionSettings>();
	FChronicle_EmotionData EmotionData;
	Settings->Emotions.Add(EmotionData);
	Settings->SaveConfig();
	return EmotionData;
}

void UChronicle_EmotionsFunctionLibrary::Remove(const FGuid& Id)
{
	UChronicle_EmotionSettings* Settings = GetMutableDefault<UChronicle_EmotionSettings>();
	
	Settings->Emotions.RemoveAll([&Id](const FChronicle_EmotionData& Emotion)
	{
		return Emotion.Id == Id;
	});
	
	Settings->SaveConfig();
}

void UChronicle_EmotionsFunctionLibrary::Rename(const FGuid& Id, const FString& Name)
{
	UChronicle_EmotionSettings* Settings = GetMutableDefault<UChronicle_EmotionSettings>();

	for (FChronicle_EmotionData& Emotion : Settings->Emotions)
	{
		if (Emotion.Id != Id)
		{
			continue;
		}
		
		Emotion.Name = Name;
		break;
	}

	Settings->SaveConfig();
}
