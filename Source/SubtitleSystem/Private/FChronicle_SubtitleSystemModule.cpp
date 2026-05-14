#include "FChronicle_SubtitleSystemModule.h"

#define LOCTEXT_NAMESPACE "ChronicleSubtitleSystemModule"

void FChronicle_SubtitleSystemModule::StartupModule()
{
	FSoftObjectPath(TEXT("/Chronicle/Runtime/Fonts/EBGaramond-Medium_Font.EBGaramond-Medium_Font")).TryLoad();
	FSoftObjectPath(TEXT("/Chronicle/Runtime/Fonts/EBGaramond-Medium.EBGaramond-Medium")).TryLoad();
}

void FChronicle_SubtitleSystemModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FChronicle_SubtitleSystemModule, SubtitleSystem)