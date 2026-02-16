#include "FDialogueGraphConnectionDrawingPolicy.h"

#include "Assets/UDialogueAsset.h"
#include "Graphs/URuleGraph.h"
#include "Nodes/Unreal/UDialogueNode.h"
#include "Nodes/Unreal/UDialogueResponseNode.h"
#include "Nodes/Unreal/URuleOutputNode.h"

struct FLineSegment
{
	FVector2f A;
	FVector2f B;
};

FDialogueGraphConnectionDrawingPolicy::FDialogueGraphConnectionDrawingPolicy(
	const int32 InBackLayerID,
	const int32 InFrontLayerID,
	const float InZoomFactor,
	const FSlateRect& InClippingRect,
	FSlateWindowElementList& InDrawElements
)
	: FConnectionDrawingPolicy(
		InBackLayerID,
		InFrontLayerID,
		InZoomFactor,
		InClippingRect,
		InDrawElements
	)
{
}

void FDialogueGraphConnectionDrawingPolicy::DrawSplineWithArrow(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FConnectionParams& Params
)
{
	if (!IsTargetNodeEnabled(Params))
	{
		return;
	}

	const FVector2f PinOffset = GetPinOffset();
	
	if (IsStraightConnection(StartPoint, EndPoint))
	{
		DrawStraightConnection(StartPoint + PinOffset, EndPoint - PinOffset, Params);
	}
	else
	{
		DrawAngledConnection(StartPoint, EndPoint, PinOffset, Params);
	}
	
	DrawArrow(EndPoint, PinOffset, Params);
	CacheOwner(Params);
	
	if (HasRules(Params.AssociatedPin2, EOutputType::Requirements))
	{
		DrawKeyIcon(StartPoint, EndPoint, Params);
	}
	
	if (HasRules(Params.AssociatedPin2, EOutputType::PreCallback))
	{
		DrawInLinkIcon(StartPoint, EndPoint, Params);
	}
	
	if (HasRules(Params.AssociatedPin1, EOutputType::PostCallback))
	{
		DrawOutLinkIcon(StartPoint, EndPoint, Params);
	}
}

void FDialogueGraphConnectionDrawingPolicy::DrawAngledConnection(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FVector2f& PinOffset,
	const FConnectionParams& Params
) const
{
	const TArray<FLineSegment> Segments = BuildOrthogonalWire(StartPoint, EndPoint, PinOffset, Params);

	for (const auto& [A, B] : Segments)
	{
		DrawStraightConnection(A, B, Params);
	}
}

void FDialogueGraphConnectionDrawingPolicy::DrawStraightConnection(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FConnectionParams& Params
) const
{
	TArray<FVector2f> Points;
	
	Points.Add(StartPoint);
	Points.Add(EndPoint);
	
	FSlateDrawElement::MakeLines(
		DrawElementsList,
		WireLayerID,
		FPaintGeometry(),
		Points,
		ESlateDrawEffect::NoBlending,
		Params.WireColor,
		true,
		Params.WireThickness
	);
}

void FDialogueGraphConnectionDrawingPolicy::DrawArrow(
	const FVector2f& EndPoint,
	const FVector2f& PinOffset,
	const FConnectionParams& Params
) const
{
	const FVector2f ArrowPoint = EndPoint - ArrowRadius - PinOffset;
	
	FSlateDrawElement::MakeBox(
		DrawElementsList,
		ArrowLayerID,
		FPaintGeometry(ArrowPoint, ArrowImage->ImageSize * ZoomFactor, ZoomFactor),
		ArrowImage,
		ESlateDrawEffect::None,
		Params.WireColor
	);
}

void FDialogueGraphConnectionDrawingPolicy::DrawOutLinkIcon(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
) const
{
	const FSlateBrush* LinkBrush = FSlateIcon("FDialogueGraphEditorStyle", "Icons.Link").GetIcon();
	const FVector2f LinkPoint = FVector2f(
		StartPoint.X + (EndPoint.X - StartPoint.X) * 0.5f - LinkBrush->ImageSize.X * ZoomFactor * 0.5f,
		StartPoint.Y - LinkBrush->ImageSize.X * ZoomFactor * 0.5f
	);
	
	FSlateDrawElement::MakeBox(
		DrawElementsList,
		ArrowLayerID,
		FPaintGeometry(LinkPoint, LinkBrush->ImageSize * ZoomFactor, ZoomFactor),
		LinkBrush,
		ESlateDrawEffect::None,
		Params.WireColor
	);
}

void FDialogueGraphConnectionDrawingPolicy::DrawInLinkIcon(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
) const
{
	const FSlateBrush* LinkBrush = FSlateIcon("FDialogueGraphEditorStyle", "Icons.Link").GetIcon();
	const FVector2f LinkPoint = FVector2f(
		StartPoint.X + (EndPoint.X - StartPoint.X) * 0.75f - LinkBrush->ImageSize.X * ZoomFactor * 0.75f,
		EndPoint.Y - LinkBrush->ImageSize.X * ZoomFactor * 0.5f
	);
	
	FSlateDrawElement::MakeBox(
		DrawElementsList,
		ArrowLayerID,
		FPaintGeometry(LinkPoint, LinkBrush->ImageSize * ZoomFactor, ZoomFactor),
		LinkBrush,
		ESlateDrawEffect::None,
		Params.WireColor
	);
}

void FDialogueGraphConnectionDrawingPolicy::DrawKeyIcon(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
) const
{
	const FSlateBrush* KeyBrush = FSlateIcon("FDialogueGraphEditorStyle", "Icons.Key").GetIcon();
	const FVector2f KeyPoint = FVector2f(
		(StartPoint.X + EndPoint.X) * 0.5f - KeyBrush->ImageSize.X * ZoomFactor * 0.5f,
		EndPoint.Y - KeyBrush->ImageSize.X * ZoomFactor * 0.5f
	);
	
	FSlateDrawElement::MakeBox(
		DrawElementsList,
		ArrowLayerID,
		FPaintGeometry(KeyPoint, KeyBrush->ImageSize * ZoomFactor, ZoomFactor),
		KeyBrush,
		ESlateDrawEffect::None,
		Params.WireColor
	);
}

TArray<FLineSegment> FDialogueGraphConnectionDrawingPolicy::BuildOrthogonalWire(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint,
	const FVector2f& PinOffset,
	const FConnectionParams& Params
) const
{
	TArray<FLineSegment> Segments;

	const FVector2f HorizontalAnchorOffset(
		Params.WireThickness * 0.5f,
		0.0f
	);
	
	const FVector2f VerticalAnchorOffset(
		0.0f,
		Params.WireThickness * 0.5f
	);
	
	const FVector2f StartAnchor(
		(StartPoint.X + EndPoint.X) * 0.5f,
		StartPoint.Y
	);

	const FVector2f EndAnchor(
		(StartPoint.X + EndPoint.X) * 0.5f,
		EndPoint.Y
	);

	FVector2f BottomAnchor;
	FVector2f TopAnchor;

	if (StartAnchor.Y > EndAnchor.Y)
	{
		BottomAnchor = EndAnchor;
		TopAnchor = StartAnchor;
	}
	else
	{
		BottomAnchor = StartAnchor;
		TopAnchor = EndAnchor;
	}

	Segments.Add(FLineSegment(StartPoint + PinOffset, StartAnchor + HorizontalAnchorOffset));
	Segments.Add(FLineSegment(TopAnchor + VerticalAnchorOffset, BottomAnchor - VerticalAnchorOffset));
	Segments.Add(FLineSegment(EndAnchor - HorizontalAnchorOffset, EndPoint - PinOffset));
	
	return Segments;
}

FVector2f FDialogueGraphConnectionDrawingPolicy::GetPinOffset() const
{
	const FVector2f PinOffset(
		17.5f,
		0.0f
	);

	return PinOffset * ZoomFactor;
}

bool FDialogueGraphConnectionDrawingPolicy::IsStraightConnection(
	const FVector2f& StartPoint,
	const FVector2f& EndPoint
) const
{
	return StartPoint.Y == EndPoint.Y;
}

bool FDialogueGraphConnectionDrawingPolicy::IsTargetNodeEnabled(const FConnectionParams& Params) const
{
	UEdGraphNode* Node = Params.AssociatedPin2->GetOwningNode();
	const UDialogueNode* TypedNode = Cast<UDialogueNode>(Node);
	return !TypedNode->bIsHidden;
}

void FDialogueGraphConnectionDrawingPolicy::CacheOwner(const FConnectionParams& Params)
{
	Owner = Params.AssociatedPin1->GetOwningNode()->GetGraph()->GetTypedOuter<UDialogueAsset>();
}

bool FDialogueGraphConnectionDrawingPolicy::HasRules(const UEdGraphPin* Pin, const EOutputType Type) const
{
	if (!Pin)
	{
		return false;
	}
	
	const UEdGraphNode* Node = Pin->GetOwningNode();
	
	if (!Node)
	{
		return false;
	}

	const UDialogueResponseNode* TypedNode = Cast<UDialogueResponseNode>(Node);

	if (!TypedNode)
	{
		return false;
	}

	const TObjectPtr<URuleGraph>* RuleGraphPointer = Owner->InnerGraphsByNode.Find(TypedNode);
	
	if (!RuleGraphPointer)
	{
		return false;
	}
	
	const URuleGraph* RuleGraph = RuleGraphPointer->Get();
	
	if (!RuleGraph)
	{
		return false;
	}
	
	return RuleGraph->GetRules(Type).Num() > 1;
}
