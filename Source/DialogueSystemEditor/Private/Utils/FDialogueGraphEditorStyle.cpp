#include "FDialogueGraphEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr<FSlateStyleSet> FDialogueGraphEditorStyle::StyleInstance;

void FDialogueGraphEditorStyle::Initialize()
{
	if (!TryInitializing())
	{
		return;
	}

	InitializeContentDirectory();
	InitializeIcons();
	FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
}

void FDialogueGraphEditorStyle::Shutdown()
{
	if (!StyleInstance.IsValid())
	{
		return;
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	StyleInstance.Reset();
}

const ISlateStyle& FDialogueGraphEditorStyle::Get()
{
	return *StyleInstance;
}

bool FDialogueGraphEditorStyle::TryInitializing()
{
	if (StyleInstance.IsValid())
	{
		return false;
	}

	StyleInstance = MakeShared<FSlateStyleSet>("FDialogueGraphEditorStyle");
	return true;
}

void FDialogueGraphEditorStyle::InitializeContentDirectory()
{
	const FString PluginDirectory = IPluginManager::Get().FindPlugin(TEXT("StorySystem"))->GetBaseDir();
	const FString ContentDirectory = PluginDirectory / TEXT("Resources");
	StyleInstance->SetContentRoot(ContentDirectory);
}

void FDialogueGraphEditorStyle::InitializeIcons()
{
	StyleInstance->Set(
		"Icons.Key",
		new FSlateImageBrush(
			StyleInstance->RootToContentDir(TEXT("Key.png")),
			FVector2D(24.0f, 24.0f)
		)
	);

	StyleInstance->Set(
		"Icons.Link",
		new FSlateImageBrush(
			StyleInstance->RootToContentDir(TEXT("Link.png")),
			FVector2D(24.0f, 24.0f)
		)
	);

	StyleInstance->Set(
		"Icons.Listener",
		new FSlateImageBrush(
			StyleInstance->RootToContentDir(TEXT("Listener.png")),
			FVector2D(24.0f, 24.0f)
		)
	);

	StyleInstance->Set(
		"Icons.Speaker",
		new FSlateImageBrush(
			StyleInstance->RootToContentDir(TEXT("Speaker.png")),
			FVector2D(24.0f, 24.0f)
		)
	);

	StyleInstance->Set(
		"Icons.Participant",
		new FSlateImageBrush(
			StyleInstance->RootToContentDir(TEXT("Participant.png")),
			FVector2D(24.0f, 24.0f)
		)
	);
}