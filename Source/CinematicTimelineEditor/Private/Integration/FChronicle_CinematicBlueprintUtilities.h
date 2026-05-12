#pragma once

#include "AChronicle_CharacterActor.h"
#include "Data/FChronicle_DialogueInfo.h"
#include "Data/FChronicle_SequenceInfo.h"
#include "Data/UChronicle_CinematicData.h"

struct CINEMATICTIMELINEEDITOR_API FTrackInfo
{
	FChronicle_AnimationData Animation;
	TSoftObjectPtr<USoundBase> Sound;
	FFrameNumber StartFrame;
	FFrameNumber EndFrame;
	FGuid ParticipantId;
	FGuid EmotionId;
	FText Subtitle;
	FGuid Id;
};

struct CINEMATICTIMELINEEDITOR_API FSequenceInfo
{
	TMap<FGuid, FTransform> TransformByParticipantIds;
	TMap<FGuid, FGuid> CameraIdByParticipantIds;
	TMap<FGuid, FGuid> ModelIdByParticipantIds;
	TArray<FString> AnimationTrackNames;
	TArray<FGuid> AnimationOwnerIds;
	FFrameNumber EntryEndFrameCount;
	FFrameNumber TotalFrameCount;
	TArray<FTrackInfo> Tracks;
	FGuid MainParticipantId;
	FGuid EntryCameraId;
	bool bIsEntry;
	FGuid Id;
};

class CINEMATICTIMELINEEDITOR_API FChronicle_CinematicBlueprintUtilities
{
public:
	static void RandomizeAnimations(UChronicle_CinematicData* CinematicData);
	
	static UBlueprint* CreateBlueprintFromParent(
		UClass* ParentClass,
		const FString& PackagePath,
		const FString& BlueprintName,
		const FChronicle_DialogueInfo& Info,
		const FTransform& ResponseTransform,
		const TArray<FTransform>& CameraTransforms,
		const TArray<FTransform>& ParticipantTransforms
	);
	
	static FChronicle_SequenceInfo InitSequence(
		ULevelSequence* LevelSequence,
		UChronicle_CinematicData* CinematicData,
		const FChronicle_SequenceData& SequenceData
	);

private:
	static void RandomizeAnimation(
		UChronicle_CinematicData* CinematicData,
		const FChronicle_DialogueNodeData& Node,
		const TSharedPtr<FGuid>& ParticipantId
	);
	
	static bool TryGetMovieScene(const ULevelSequence* LevelSequence, UMovieScene*& MovieScene);
	static void ApplyInfo(UMovieScene* MovieScene, const FSequenceInfo& SequenceInfo);

	static FChronicle_SequenceInfo ConvertToRuntimeInfo(
		const ULevelSequence* LevelSequence,
		const FSequenceInfo& SequenceInfo,
		const UChronicle_CinematicData* CinematicData,
		const FChronicle_SequenceData& SequenceData
	);
	
	static FSequenceInfo ConvertToInfo(
		UMovieScene* MovieScene,
		const UChronicle_CinematicData* CinematicData,
		const FChronicle_SequenceData& SequenceData
	);
	
	static void PopulateCameraCutTrack(
		UMovieScene* MovieScene,
		const FSequenceInfo& SequenceInfo
	);
	
	static void PopulateAudioTrack(
		UMovieScene* MovieScene,
		const FSequenceInfo& SequenceInfo
	);
	
	static void PopulateAnimationTrack(
		UMovieScene* MovieScene,
		const FSequenceInfo& SequenceInfo
	);
	
	static void PopulateSubtitleTrack(
		UMovieScene* MovieScene,
		const FSequenceInfo& SequenceInfo
	);
	
	static void PopulateEntryTrack(
		UMovieScene* MovieScene,
		const FSequenceInfo& SequenceInfo
	);
	
	static FGuid AddCamera(
		UMovieScene* MovieScene,
		const FTransform& SpawnTransform
	);
	
	static FGuid AddModel(
		UMovieScene* MovieScene,
		TSoftClassPtr<AChronicle_CharacterActor> CharacterClass,
		const FTransform& SpawnTransform
	);
	
	static void ApplyChanges(
		ULevelSequence* LevelSequence,
		UChronicle_CinematicData* CinematicData,
		const FChronicle_SequenceData& SequenceData
	);
};
