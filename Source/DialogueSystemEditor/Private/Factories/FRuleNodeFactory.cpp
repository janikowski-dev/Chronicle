#pragma once

#include "FRuleNodeFactory.h"

#include "FCharacterDirectory.h"
#include "FRuleDirectory.h"
#include "Nodes/Slate/SRuleDefaultNode.h"
#include "Nodes/Slate/SRuleInputNode.h"
#include "Nodes/Unreal/URuleCallbackNode.h"
#include "Nodes/Unreal/URuleConditionNode.h"

TSharedPtr<SGraphNode> FRuleNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (URuleCallbackNode* TypedNode = Cast<URuleCallbackNode>(Node))
	{
		return SNew(SRuleInputNode, TypedNode, FRuleDirectory::GetCallbacks(TypedNode->ParameterType), FCharacterDirectory::GetAll());
	}
	
	if (URuleConditionNode* TypedNode = Cast<URuleConditionNode>(Node))
	{
		return SNew(SRuleInputNode, TypedNode, FRuleDirectory::GetConditions(TypedNode->ParameterType), FCharacterDirectory::GetAll());
	}
	
	if (URuleNode* TypedNode = Cast<URuleNode>(Node))
	{
		return SNew(SRuleDefaultNode, TypedNode);
	}
	
	return nullptr;
}
