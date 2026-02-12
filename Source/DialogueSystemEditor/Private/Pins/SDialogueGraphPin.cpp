#include "SDialogueGraphPin.h"

#include "SGraphPin.h"

void SDialogueGraphPin::Construct(const FArguments&, UEdGraphPin* InPin)
{
	SGraphPin::Construct(SGraphPin::FArguments(), InPin);
	SetShowLabel(false);
	SetEnabled(false);
}

const FSlateBrush* SDialogueGraphPin::GetPinIcon() const
{
	return nullptr;
}
