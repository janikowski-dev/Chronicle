#pragma once

#include "SDialogueNode.h"

class SDialogueTextNode : public SDialogueNode
{
protected:
	void AddTextField(
		const TSharedRef<SVerticalBox>& Box,
		const TAttribute<FText>& Getter,
		const FOnTextCommitted& Setter
	);
};
