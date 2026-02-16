#pragma once

UENUM()
enum EDialogueCallback : uint16
{
	FirstCallback		UMETA(DisplayName = "Main.First Callback"),
	SecondCallback		UMETA(DisplayName = "Main.Second Callback"),
	ThirdCallback		UMETA(DisplayName = "Side.Third Callback")
};
