#pragma once

#include "Widgets/Input/SMultiLineEditableTextBox.h"

static TSharedRef<SWidget> MakeTextField(
	const TAttribute<FText>& Getter,
	const FOnTextCommitted& Setter
)
{
	return SNew(SBox)
	.HeightOverride(150.0f)
	.WidthOverride(225.0f)
	.Padding(4)
	[
		SNew(SMultiLineEditableTextBox)
		.HScrollBar(
			SNew(SScrollBar)
			.Thickness(FVector2D(0, 0))
			.AlwaysShowScrollbar(false)
			.AlwaysShowScrollbarTrack(false).
			Visibility(EVisibility::Hidden)
		)
		.Text(Getter)
		.OnTextCommitted(Setter)
		.AutoWrapText(true)
	];
}

static TSharedRef<SWidget> MakeTextField(
	const TAttribute<FText>& Getter
)
{
	return SNew(SBox)
	.HeightOverride(122.0f)
	.WidthOverride(225.0f)
	.Padding(4)
	[
		SNew(SMultiLineEditableTextBox)
		.BackgroundColor(FLinearColor::Transparent)
		.HScrollBar(
			SNew(SScrollBar)
			.Thickness(FVector2D(0, 0))
			.AlwaysShowScrollbar(false)
			.AlwaysShowScrollbarTrack(false).
			Visibility(EVisibility::Hidden)
		)
		.Text(Getter)
		.IsReadOnly(true)
		.AutoWrapText(true)
	];
}