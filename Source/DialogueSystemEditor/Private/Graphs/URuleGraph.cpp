#include "URuleGraph.h"

#include "Nodes/Unreal/URuleOutputNode.h"

TArray<URuleNode*> URuleGraph::GetRules(const EOutputType Type) const
{
	URuleNode* OutputNode = GetOutputNode(Type);
	TArray<URuleNode*> Rules;
	GetRules(OutputNode, Rules);
	return Rules;
}

URuleNode* URuleGraph::GetOutputNode(const EOutputType Type) const
{
	UEdGraphNode* MatchingNode = Nodes.FindByPredicate([Type](const TObjectPtr<UEdGraphNode> Node)
	{
		const URuleOutputNode* OutputNode = Cast<URuleOutputNode>(Node.Get());

		if (!OutputNode)
		{
			return false;
		}
		
		return OutputNode->Type == Type;
	})->Get();

	return Cast<URuleNode>(MatchingNode);
}

void URuleGraph::GetRules(URuleNode* Node, TArray<URuleNode*>& Rules) const
{
	if (!Node)
	{
		return;
	}

	Rules.Add(Node);

	for (UEdGraphPin* Pin : Node->Pins)
	{
		if (Pin->Direction != EGPD_Input)
		{
			continue;
		}
		
		for (const UEdGraphPin* LinkedPin : Pin->LinkedTo)
		{
			UEdGraphNode* PinOwner = LinkedPin->GetOwningNode();
			URuleNode* TypedOwner = Cast<URuleNode>(PinOwner);
			GetRules(TypedOwner, Rules);
		}
	}
}