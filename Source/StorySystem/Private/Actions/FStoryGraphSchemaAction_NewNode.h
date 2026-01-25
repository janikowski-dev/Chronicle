#pragma once

#include "EdGraph/EdGraphSchema.h"

class UStoryGraphNode;

struct FStoryGraphSchemaAction_NewNode : FEdGraphSchemaAction
{
public:
	FStoryGraphSchemaAction_NewNode();

	virtual UEdGraphNode* PerformAction(
		UEdGraph* ParentGraph,
		UEdGraphPin* FromPin,
		const FVector2f& Location,
		bool bSelectNewNode = true
	) override;
};