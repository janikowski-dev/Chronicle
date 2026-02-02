#include "SStoryNode.h"

#include "Editors/FStoryNodeEditor.h"
#include "Nodes/Unreal/UStoryNode.h"
#include "Pins/SStoryGraphPin.h"
#include "Widgets/Layout/SWidgetSwitcher.h"
#include "SGraphPanel.h"
#include "Graphs/UStoryGraph.h"

void SStoryNode::MoveTo(const FVector2f& NewPosition, FNodeSet& NodeFilter, bool bMarkDirty)
{
}

TSharedPtr<SGraphPin> SStoryNode::CreatePinWidget(UEdGraphPin* Pin) const
{
	return SNew(SStoryGraphPin, Pin);
}

TSharedPtr<SGraphPin> SStoryNode::GetHoveredPin(const FGeometry&, const FPointerEvent&) const
{
	return nullptr;
}

FReply SStoryNode::OnMouseButtonDoubleClick(const FGeometry&, const FPointerEvent&)
{
	OpenNodeEditor();
	return FReply::Handled();
}

void SStoryNode::UpdateGraphNode()
{
	SGraphNode::UpdateGraphNode();
	SetupErrorReporting();

	const TSharedRef<SVerticalBox> RegularView = SNew(SVerticalBox);
	const TSharedRef<SVerticalBox> CollapsedView = SNew(SVerticalBox);
	const TSharedRef<SWidget> HiddenView = SNew(SSpacer);
	
	SAssignNew(LeftNodeBox, SVerticalBox);
	SAssignNew(RightNodeBox, SVerticalBox);

	AddHeader(CollapsedView);
	AddHeader(RegularView);
	AddBody(RegularView);
	
	SAssignNew(WidgetSwitcher, SWidgetSwitcher)
	.WidgetIndex(this, &SStoryNode::GetBodyIndex)
	+ SWidgetSwitcher::Slot()
	[
		RegularView
	]

	+ SWidgetSwitcher::Slot()
	[
		CollapsedView
	]

	+ SWidgetSwitcher::Slot()
	[
		HiddenView
	];

	RemoveSlot(ENodeZone::Center);
	
	GetOrAddSlot(ENodeZone::Center)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
		.BorderBackgroundColor(this, &SStoryNode::GetHeaderColor)
		[
			WidgetSwitcher.ToSharedRef()
		]
	];
	
	CreatePinWidgets();
}

void SStoryNode::AddHeader(const TSharedRef<SVerticalBox>& Box)
{
	const FText Title = GetTitle(Cast<UStoryNode>(GraphNode));
	
	Box->AddSlot()
	.AutoHeight()
	[
		SNew(SOverlay)
		
		+ SOverlay::Slot()
		[
			SNew(SBox)
			.WidthOverride(275.0f)
			.Padding(4)
			[
				SNew(STextBlock)
				.Text(Title)
			]
		]

		+ SOverlay::Slot()
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.Padding(FMargin(0.0f, 4.0f))
			.AutoWidth()
			[
				LeftNodeBox.ToSharedRef()
			]
			
			+ SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SNew(SSpacer)
			]

			+ SHorizontalBox::Slot()
			.Padding(FMargin(0.0f, 4.0f))
			.AutoWidth()
			[
				RightNodeBox.ToSharedRef()
			]
		]

		+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		[
			SNew(SButton)
			.ButtonStyle(FAppStyle::Get(), "HoverHintOnly")
			.ContentPadding(FMargin(4))
			.ClickMethod(EButtonClickMethod::MouseDown)
			.OnClicked(this, &SStoryNode::ToggleCollapse)
			[
				SNew(SImage)
				.Image_Lambda([this]()
				{
					return bIsCollapsed
						? FAppStyle::Get().GetBrush("Icons.ChevronRight")
						: FAppStyle::Get().GetBrush("Icons.ChevronDown");
				})
			]
		]
	];
}

FReply SStoryNode::ToggleCollapse()
{
	bIsCollapsed = !bIsCollapsed;
	TSet<UEdGraphNode*> Visited;
	ApplyCollapse(GraphNode, GraphNode, Visited);
	Cast<UStoryGraph>(GraphNode->GetGraph())->AutoLayout();
	return FReply::Handled();
}

void SStoryNode::ApplyCollapse(
	UEdGraphNode* CurrentNode,
	UEdGraphNode* RootNode,
	TSet<UEdGraphNode*>& Visited
) const
{
	if (!CurrentNode || Visited.Contains(CurrentNode))
	{
		return;
	}

	Visited.Add(CurrentNode);

	TSharedPtr<SGraphPanel> GraphPanel = GetOwnerPanel();
	if (!GraphPanel.IsValid())
	{
		return;
	}

	if (CurrentNode != RootNode)
	{
		if (TSharedPtr<SGraphNode> Widget = GraphPanel->GetNodeWidgetFromGuid(CurrentNode->NodeGuid))
		{
			StaticCastSharedPtr<SStoryNode>(Widget)->bIsHidden = bIsCollapsed;
		}
	}

	for (UEdGraphPin* Pin : CurrentNode->Pins)
	{
		if (Pin->Direction != EGPD_Output)
		{
			continue;
		}

		for (UEdGraphPin* LinkedPin : Pin->LinkedTo)
		{
			if (UEdGraphNode* ChildNode = LinkedPin->GetOwningNode())
			{
				ApplyCollapse(ChildNode, RootNode, Visited);
			}
		}
	}
}

void SStoryNode::OpenNodeEditor() const
{
	if (UStoryNode* NodeAsset = Cast<UStoryNode>(GraphNode))
	{
		const TSharedRef<FStoryNodeEditor> Editor = MakeShared<FStoryNodeEditor>();

		Editor->InitNodeAssetEditor(
			EToolkitMode::Standalone,
			TSharedPtr<IToolkitHost>(),
			NodeAsset
		);
	}
}

int SStoryNode::GetBodyIndex() const
{
	if (bIsCollapsed)
	{
		return Collapsed;
	}

	if (bIsHidden)
	{
		return Hidden;
	}
	
	return Regular;
}

void SStoryNode::Cache(UEdGraphNode* Node)
{
	GraphNode = Node;
}
