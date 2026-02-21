#pragma once

#include "Widgets/Input/SMultiLineEditableTextBox.h"

static TSharedRef<SWidget> MakeTextField(
	const TAttribute<FText>& Getter,
	const FOnTextCommitted& Setter
)
{
	return SNew(SBox)
	.MinDesiredHeight(150.0f)
	.MinDesiredWidth(275.0f)
	.Padding(4)
	[
		SNew(SMultiLineEditableTextBox)
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
	.MinDesiredHeight(150.0f)
	.MinDesiredWidth(275.0f)
	.Padding(4)
	[
		SNew(SMultiLineEditableTextBox)
		.BackgroundColor(FLinearColor::Transparent)
		.Text(Getter)
		.IsReadOnly(true)
		.AutoWrapText(true)
	];
}