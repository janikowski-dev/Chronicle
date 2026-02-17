#pragma once

#include "ConnectionDrawingPolicy.h"
#include "Graphs/URuleGraph.h"

class UDialogueAsset;
struct FLineSegment;

class DIALOGUESYSTEMEDITOR_API FDialogueGraphConnectionDrawingPolicy : public FConnectionDrawingPolicy
{
public:
	FDialogueGraphConnectionDrawingPolicy(
		int32 InBackLayerID,
		int32 InFrontLayerID,
		float InZoomFactor,
		const FSlateRect& InClippingRect,
		FSlateWindowElementList& InDrawElements
	);

protected:
	virtual void DrawSplineWithArrow(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
	) override;

private:
	void DrawStraightConnection(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
	) const;

	void DrawAngledConnection(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FVector2f& PinOffset,
		const FConnectionParams& Params
	) const;

	void DrawArrow(
		const FVector2f& EndPoint,
		const FVector2f& PinOffset,
		const FConnectionParams& Params
	) const;

	void DrawLinkIcon(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
	) const;
	
	void DrawKeyIcon(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FConnectionParams& Params
	) const;

	TArray<FLineSegment> BuildOrthogonalWire(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint,
		const FVector2f& PinOffset,
		const FConnectionParams& Params
	) const;

	FVector2f GetPinOffset() const;

	bool IsStraightConnection(
		const FVector2f& StartPoint,
		const FVector2f& EndPoint
	) const;

	bool IsTargetNodeEnabled(const FConnectionParams& Params) const;
	void CacheOwner(const FConnectionParams& Params);
	bool HasRules(const UEdGraphPin* Pin, const EOutputType Type) const;

private:
	UDialogueAsset* Owner;
};