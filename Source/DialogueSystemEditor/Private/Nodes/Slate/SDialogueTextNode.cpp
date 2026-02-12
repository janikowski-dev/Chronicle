#include "SDialogueTextNode.h"

#include "Widgets/Input/SMultiLineEditableTextBox.h"

void SDialogueTextNode::AddTextField(
	const TSharedRef<SVerticalBox>& Box,
	const TAttribute<FText>& Getter,
	const FOnTextCommitted& Setter
)
{
	Box->AddSlot()
	.AutoHeight()
	[
		SNew(SBox)
		.MinDesiredHeight(150.0f)
		.MinDesiredWidth(275.0f)
		.Padding(4)
		[
			SNew(SMultiLineEditableTextBox)
			.Text(Getter)
			.OnTextCommitted(Setter)
			.AutoWrapText(true)
		]
	];
	
}
