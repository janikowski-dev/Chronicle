#pragma once

#include "Styling/SlateStyle.h"

class FDialogueGraphEditorStyle
{
public:
	static const ISlateStyle& Get();
	
	static void Initialize();
	static void Shutdown();

private:
	static bool TryInitializing();
	static void InitializeContentDirectory();
	static void InitializeIcons();
	static void InitializeBoxes();
	
private:
	static TSharedPtr<FSlateStyleSet> StyleInstance;
};
