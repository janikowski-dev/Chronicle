#pragma once

#include "SStoryNode.h"

class SStoryTextNode : public SStoryNode
{
protected:
	void AddTextField(
		const TSharedRef<SVerticalBox>& Box,
		const TAttribute<FText>& Getter,
		const FOnTextCommitted& Setter
	);
};
