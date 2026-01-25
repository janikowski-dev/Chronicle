#pragma once

#include "FStorySystemNodeFactory.h"
#include "SlateNodes/SDialogueGraphNode.h"
#include "SlateNodes/SRootGraphNode.h"
#include "SlateNodes/SResponseGraphNode.h"
#include "Nodes/UDialogueGraphNode.h"
#include "Nodes/UResponseGraphNode.h"
#include "Nodes/URootGraphNode.h"

TSharedPtr<SGraphNode> FStorySystemNodeFactory::CreateNode(UEdGraphNode* Node) const
{
	if (UDialogueGraphNode* DialogueNode = Cast<UDialogueGraphNode>(Node))
	{
		return SNew(SDialogueGraphNode, DialogueNode);
	}
		
	if (URootGraphNode* RootNode = Cast<URootGraphNode>(Node))
	{
		return SNew(SRootGraphNode, RootNode);
	}
		
	if (UResponseGraphNode* ResponseNode = Cast<UResponseGraphNode>(Node))
	{
		return SNew(SResponseGraphNode, ResponseNode);
	}
		
	return nullptr;
}
