#include "SRuleConditionNode.h"

#include "Data/EDialogueCondition.h"
#include "Nodes/Unreal/URuleTagNode.h"

void SRuleConditionNode::Construct(const FArguments&, URuleTagNode* InNode)
{
	Cache(InNode);
	InitConditions();
	UpdateGraphNode();
}

void SRuleConditionNode::UpdateGraphNode()
{
	SetupErrorReporting();

	RemoveSlot(ENodeZone::Center);

	GetOrAddSlot(ENodeZone::Center)
	[
		SNew(SBorder)
		.BorderImage(FAppStyle::GetBrush("Graph.Node.Body"))
		.BorderBackgroundColor(TypedNode->GetBackgroundColor())
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SBox)
				.Padding(4)
				[
					SNew(STextBlock)
					.Text(TypedNode->GetTitle())
				]
			]
			
			+ SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
			
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&AllTags)
					.OnGenerateWidget_Lambda([](const TSharedPtr<FString>& InItem)
					{
						return SNew(STextBlock).Text(FText::FromString(*InItem));
					})
					.OnSelectionChanged_Lambda([this](const TSharedPtr<FString>& NewSelection, ESelectInfo::Type)
					{
						SelectedTag = NewSelection;
					})
					.InitiallySelectedItem(SelectedTag)
					[
						SNew(STextBlock)
						.Text_Lambda([this]() -> FText
						{
							return SelectedTag.IsValid() ? FText::FromString(*SelectedTag) : FText::FromString("Select...");
						})
					]
				]
				
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					SNew(SSpacer)
				]
			
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(RightNodeBox, SVerticalBox)
				]
			]
		]
	];
	
	CreatePinWidgets();
}

void SRuleConditionNode::Cache(URuleTagNode* InNode)
{
	TypedNode = Cast<URuleTagNode>(InNode);
	GraphNode = InNode;
}

void SRuleConditionNode::InitConditions()
{
	const UEnum* ConditionsEnum = StaticEnum<EDialogueCondition>();

	AllTags.Empty();
	
	for (int32 i = 0; i < ConditionsEnum->NumEnums() - 1; i++)
	{
		AllTags.Add(MakeShared<FString>(ConditionsEnum->GetDisplayNameTextByIndex(i).ToString()));
	}

	if (AllTags.Num() > 0)
	{
		SelectedTag = AllTags[0];
	}
}
