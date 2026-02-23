#include "SDialogueLinkNode.h"

#include "Graphs/UDialogueGraph.h"
#include "Nodes/Unreal/UDialogueLineNode.h"
#include "Nodes/Unreal/UDialogueLinkNode.h"
#include "Utils/FDialogueGraphEditorStyle.h"
#include "Utils/FSlateHelper.h"

void SDialogueLinkNode::Construct(const FArguments&, UDialogueLinkNode* InNode)
{
    Cache(InNode);
    UpdateGraphNode();
}

void SDialogueLinkNode::UpdateGraphNode()
{
    SDialogueNode::UpdateGraphNode();
    RefreshAvailableNodes();
}

void SDialogueLinkNode::AddBody(const TSharedRef<SVerticalBox>& Box)
{
    Box->AddSlot()
    .AutoHeight()
    .Padding(0, 0, 0, 4)
    [
        SNew(SComboButton)
        .OnGetMenuContent(this, &SDialogueLinkNode::GetLineNodesMenu)
        .ButtonContent()
        [
            SNew(STextBlock)
            .Text(this, &SDialogueLinkNode::GetSelectedNodeTitle)
        ]
    ];

    if (!TypedNode->GetLinkedNode())
    {
        return;
    }

    Box->AddSlot()
    .AutoHeight()
    .Padding(4)
    [
        MakeCharacterDisplay(
            FDialogueGraphEditorStyle::Get().GetBrush("Icons.Speaker"),
            TAttribute<FText>(this, &SDialogueLinkNode::GetSpeakerName)
        )
    ];

    Box->AddSlot()
    .AutoHeight()
    .Padding(4)
    [
        MakeCharacterDisplay(
            FDialogueGraphEditorStyle::Get().GetBrush("Icons.Listener"),
            TAttribute<FText>(this, &SDialogueLinkNode::GetListenerName)
        )
    ];
    
    Box->AddSlot()
    .AutoHeight()
    [
        MakeTextField(TAttribute<FText>(this, &SDialogueLinkNode::GetSelectedNodeText))
    ];
}

FSlateColor SDialogueLinkNode::GetHeaderColor() const
{
    return FSlateColor(FLinearColor(0.8f, 0.0f, 0.0f));
}

TSharedRef<SWidget> SDialogueLinkNode::GetLineNodesMenu()
{
    FMenuBuilder MenuBuilder(true, nullptr);

    for (TWeakObjectPtr Node : AvailableNodes)
    {
        if (!Node.IsValid())
        {
            continue;
        }

        UDialogueLineNode* LineNode = Node.Get();

        MenuBuilder.AddMenuEntry(
            LineNode->GetTitle(),
            FText::FromString("Link to this dialogue line"),
            FSlateIcon(),
            FUIAction(FExecuteAction::CreateSP(this, &SDialogueLinkNode::SelectNode, LineNode))
        );
    }

    return MenuBuilder.MakeWidget();
}

FText SDialogueLinkNode::GetSelectedNodeTitle() const
{
    if (TypedNode.IsValid() && TypedNode->GetLinkedNode())
    {
        return TypedNode->GetLinkedNode()->GetTitle();
    }
    
    return FText::FromString("Pick a line");
}

FText SDialogueLinkNode::GetSelectedNodeText() const
{
    if (TypedNode.IsValid() && TypedNode->GetLinkedNode())
    {
        return TypedNode->GetLinkedNode()->Text;
    }
    
    return FText::FromString("Node is not linked");
}

FText SDialogueLinkNode::GetListenerName() const
{
    return FText::FromName(FCharacterDirectory::GetAll().GetName(TypedNode->LinkedNode->ListenerId));
}

FText SDialogueLinkNode::GetSpeakerName() const
{
    return FText::FromName(FCharacterDirectory::GetAll().GetName(TypedNode->LinkedNode->SpeakerId));
}

void SDialogueLinkNode::SelectNode(UDialogueLineNode* Node) const
{
    if (!TypedNode.IsValid())
    {
        return;
    }
    
    if (!Node)
    {
        return;
    }

    TypedNode->Modify();
    TypedNode->SetLinkedNode(Node);

    if (UDialogueGraph* Graph = Cast<UDialogueGraph>(TypedNode->GetGraph()))
    {
        Graph->NotifyGraphChanged();
    }
}

void SDialogueLinkNode::RefreshAvailableNodes()
{
    AvailableNodes.Empty();

    for (UEdGraphNode* Node : GraphNode->GetGraph()->Nodes)
    {
        if (UDialogueLineNode* LineNode = Cast<UDialogueLineNode>(Node))
        {
            AvailableNodes.Add(LineNode);
        }
    }
    
    AvailableNodes.Sort([](const TWeakObjectPtr<UDialogueLineNode>& A, const TWeakObjectPtr<UDialogueLineNode>& B)
    {
        return A->GetTitle().ToString() < B->GetTitle().ToString();
    });
}