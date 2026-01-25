#pragma once

#include "UStoryGraphNode.generated.h"

UCLASS()
class UStoryGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual bool CanUserDeleteNode() const override
	{
		return true;
	}

	UEdGraphPin* GetInputPin() const
	{
		for (UEdGraphPin* Pin : Pins)
		{
			if (Pin && Pin->Direction == EGPD_Input)
			{
				return Pin;
			}
		}
		return nullptr;
	}

	UEdGraphPin* GetOutputPin() const
	{
		for (UEdGraphPin* Pin : Pins)
		{
			if (Pin && Pin->Direction == EGPD_Output)
			{
				return Pin;
			}
		}
		return nullptr;
	}
};