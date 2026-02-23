#pragma once

#include "FCharacterDirectory.h"
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
	.HeightOverride(123.0f)
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

static TSharedRef<SWidget> MakeCharacterSelector(
	const FSlateBrush* Icon,
	const TAttribute<FText>& NameGetter,
	const SComboBox<TSharedPtr<FGuid>>::FOnSelectionChanged& OnSelectionChanged,
	const TArray<TSharedPtr<FGuid>>* CharacterIds
)
{
	return SNew(SHorizontalBox)
	
	+ SHorizontalBox::Slot()
	.AutoWidth()
	.VAlign(VAlign_Center)
	[
		SNew(SBox)
		.WidthOverride(16.0f)
		.HeightOverride(16.0f)
		[
			SNew(SImage)
			.Image(Icon)
		]
	]

	+ SHorizontalBox::Slot()
	.FillWidth(1.0f)
	.Padding(FMargin(4.0f, 0.0f, 0.0f, 0.0f))
	[
		SNew(SComboBox<TSharedPtr<FGuid>>)
		.OptionsSource(CharacterIds)
		.OnGenerateWidget_Lambda([](const TSharedPtr<FGuid>& Id)
		{
			return SNew(STextBlock)
				.Text(FText::FromName(FCharacterDirectory::GetAll().GetName(*Id)));
		})
		.Content()
		[
			SNew(STextBlock)
			.Text(NameGetter)
		]
		.OnSelectionChanged(OnSelectionChanged)
	];
}

static TSharedRef<SWidget> MakeCharacterDisplay(
	const FSlateBrush* Icon,
	const TAttribute<FText>& NameGetter
)
{
	return SNew(SHorizontalBox)

	+ SHorizontalBox::Slot()
	.AutoWidth()
	.VAlign(VAlign_Center)
	[
		SNew(SBox)
		.WidthOverride(16.0f)
		.HeightOverride(16.0f)
		[
			SNew(SImage)
			.Image(Icon)
		]
	]

	+ SHorizontalBox::Slot()
	.FillWidth(1.0f)
	.VAlign(VAlign_Center)
	.Padding(FMargin(4.0f, 0.0f, 0.0f, 0.0f))
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("ToolPanel.GroupBorder"))
		.Padding(4)
		[
			SNew(STextBlock)
			.Text(NameGetter)
		]
	];
}
