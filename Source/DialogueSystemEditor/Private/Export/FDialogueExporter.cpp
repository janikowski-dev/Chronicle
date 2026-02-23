#include "FDialogueExporter.h"

#include "JsonObjectConverter.h"
#include "Assets/UDialogueAsset.h"
#include "Graphs/UDialogueGraph.h"
#include "Graphs/URuleGraph.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Nodes/Unreal/UDialogueLinkNode.h"
#include "Nodes/Unreal/UDialogueLineNode.h"
#include "Nodes/Unreal/UDialogueRootNode.h"
#include "Nodes/Unreal/URuleAndNode.h"
#include "Nodes/Unreal/URuleCallbackNode.h"
#include "Nodes/Unreal/URuleConditionNode.h"
#include "Nodes/Unreal/URuleNotNode.h"
#include "Nodes/Unreal/URuleOrNode.h"
#include "Nodes/Unreal/URuleOutputNode.h"
#include "StorySystemCore/Public/Data/UDialogueData.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

void FDialogueExporter::CopyToClipboard(const UDialogueAsset* Asset)
{
    FString JsonString;
    FJsonObjectConverter::UStructToJsonObjectString(UDialogueData::StaticClass(), ConvertToTemporaryAsset(Asset), JsonString);
    FPlatformApplicationMisc::ClipboardCopy(*JsonString);
}

void FDialogueExporter::ExportToAsset(const UDialogueAsset* Asset)
{
    FAssetRegistryModule::AssetCreated(ConvertToAsset(Asset));
}

UDialogueData* FDialogueExporter::ConvertToAsset(const UDialogueAsset* Asset)
{
    const FString AssetName = FString::Printf(TEXT("%s_Data"), *Asset->GetName());
    UPackage* Package = CreatePackage(*(FPackageName::GetLongPackagePath(Asset->GetOutermost()->GetName()) / AssetName));
    UDialogueData* Data = NewObject<UDialogueData>(Package, *AssetName, RF_Public | RF_Standalone);
    return PopulateData(Data, Asset);
}

UDialogueData* FDialogueExporter::ConvertToTemporaryAsset(const UDialogueAsset* Asset)
{
    UDialogueData* Data = NewObject<UDialogueData>(GetTransientPackage());
    return PopulateData(Data, Asset);
}

UDialogueData* FDialogueExporter::PopulateData(UDialogueData* Data, const UDialogueAsset* Asset)
{
    for (UEdGraphNode* GraphNode : Asset->Graph->Nodes)
    {
        if (const UDialogueRootNode* RootNode = Cast<UDialogueRootNode>(GraphNode))
        {
            Data->ParticipantIds = RootNode->ParticipantIds;
        }
        else if (UDialogueNode* Node = Cast<UDialogueNode>(GraphNode))
        {
            Data->Nodes.Add(PopulateNodeData(Node, Data));
        }
    }

    return Data;
}

FDialogueNodeData FDialogueExporter::PopulateNodeData(UDialogueNode* Node, UDialogueData* Data)
{
    if (const UDialogueLinkNode* LinkNode = Cast<UDialogueLinkNode>(Node))
    {
        Node = LinkNode->GetLinkedNode();
        
        if (!Node)
        {
            return {};
        }
    }
    
    FDialogueNodeData NodeData;
    NodeData.Id = Node->Id;
    NodeData.Text = Node->GetText().ToString();

    if (const UDialogueLineNode* LineNode = Cast<UDialogueLineNode>(Node))
    {
        NodeData.ListenerId = LineNode->ListenerId;
        NodeData.SpeakerId = LineNode->SpeakerId;
    }
    
    if (const URuleGraph* RuleGraph = Node->GetInnerGraph())
    {
        const TArray<URuleNode*> Rules = RuleGraph->GetRules(EOutputType::Requirements);
        
        if (Rules.Num() > 0)
        {
            NodeData.RequirementsIndex = PopulateRuleData(Rules[0], Data);
        }

        for (URuleNode* Rule : RuleGraph->GetRules(EOutputType::PostCallback))
        {
            if (const URuleCallbackNode* Callback = Cast<URuleCallbackNode>(Rule))
            {
                NodeData.Callbacks.Add(Callback->TagId);
            }
        }
    }

    for (UEdGraphPin* Pin : Node->Pins)
    {
        if (Pin->Direction != EGPD_Output)
        {
            continue;
        }
        
        for (const UEdGraphPin* Linked : Pin->LinkedTo)
        {
            if (const UDialogueNode* Response = Cast<UDialogueNode>(Linked->GetOwningNode()))
            {
                NodeData.Children.Add(Response->Id);
            }
        }
    }

    return NodeData;
}

int32 FDialogueExporter::PopulateRuleData(URuleNode* Rule, UDialogueData* Data)
{
    FRuleData RuleData;

    if (const URuleConditionNode* Condition = Cast<URuleConditionNode>(Rule))
    {
        RuleData.ConditionId = Condition->TagId;
        RuleData.Type = EConditionNodeType::Raw;

        const int Index = Data->Rules.IndexOfByPredicate([&Condition](const FRuleData& ExistingRule)
        {
            if (ExistingRule.Type != EConditionNodeType::Raw)
            {
                return false;
            }
            
            return ExistingRule.ConditionId == Condition->TagId;
        });

        if (Index != INDEX_NONE)
        {
            return Index;
        }
    }
    else if (Cast<URuleAndNode>(Rule))
    {
        RuleData.Type = EConditionNodeType::And;
    }
    else if (Cast<URuleOrNode>(Rule))
    {
        RuleData.Type = EConditionNodeType::Or;
    }
    else if (Cast<URuleNotNode>(Rule))
    {
        RuleData.Type = EConditionNodeType::Not;
    }

    for (UEdGraphPin* Pin : Rule->Pins)
    {
        if (Pin->Direction != EGPD_Input)
        {
            continue;
        }
        
        for (const UEdGraphPin* LinkedTo : Pin->LinkedTo)
        {
            if (URuleNode* Child = Cast<URuleNode>(LinkedTo->GetOwningNode()))
            {
                RuleData.InputIndices.Add(PopulateRuleData(Child, Data));
            }
        }
    }

    if (RuleData.Type == EConditionNodeType::Raw && !RuleData.ConditionId.IsValid())
    {
        return INDEX_NONE;
    }
    
    const int32 Index = Data->Rules.Add(RuleData);
    return Index;
}
