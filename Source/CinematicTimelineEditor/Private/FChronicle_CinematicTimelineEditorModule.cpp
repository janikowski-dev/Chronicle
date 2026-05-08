#include "FChronicle_CinematicTimelineEditorModule.h"

#include "ISequencerModule.h"
#include "Editors/FChronicle_AnimationTrackEditor.h"
#include "Editors/FChronicle_SubtitleTrackEditor.h"

#define LOCTEXT_NAMESPACE "ChronicleCinematicTimelineEditorModule"

void FChronicle_CinematicTimelineEditorModule::StartupModule()
{
	FModuleManager::LoadModuleChecked<ISequencerModule>("Sequencer").RegisterTrackEditor(
		FOnCreateTrackEditor::CreateStatic(&FChronicle_AnimationTrackEditor::CreateTrackEditor)
	);
	
	FModuleManager::LoadModuleChecked<ISequencerModule>("Sequencer").RegisterTrackEditor(
		FOnCreateTrackEditor::CreateStatic(&FChronicle_SubtitleTrackEditor::CreateTrackEditor)
	);
}

void FChronicle_CinematicTimelineEditorModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FChronicle_CinematicTimelineEditorModule, CinematicTimelineEditor)