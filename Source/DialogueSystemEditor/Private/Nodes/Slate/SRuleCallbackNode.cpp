#include "SRuleCallbackNode.h"

#include "Data/EDialogueCallback.h"
#include "Nodes/Unreal/URuleTagNode.h"

void SRuleCallbackNode::Construct(const FArguments&, URuleTagNode* InNode)
{
	Cache(InNode);
	InitCallbacks();
	UpdateGraphNode();
}

void SRuleCallbackNode::UpdateGraphNode()
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

void SRuleCallbackNode::Cache(URuleTagNode* InNode)
{
	TypedNode = Cast<URuleTagNode>(InNode);
	GraphNode = InNode;
}

void SRuleCallbackNode::InitCallbacks()
{
	const UEnum* CallbacksEnum = StaticEnum<EDialogueCallback>();

	AllTags.Empty();
	
	for (int32 i = 0; i < CallbacksEnum->NumEnums() - 1; i++)
	{
		AllTags.Add(MakeShared<FString>(CallbacksEnum->GetDisplayNameTextByIndex(i).ToString()));
	}

	if (AllTags.Num() > 0)
	{
		SelectedTag = AllTags[0];
	}
}
