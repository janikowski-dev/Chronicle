using UnrealBuildTool;

public class CharacterSystemEditor : ModuleRules
{
	public CharacterSystemEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange([
			"CharacterSystem",
			"Core",
			"CoreUObject",
			"Engine"
		]);

		PrivateDependencyModuleNames.AddRange([
			"ChronicleCore",
			"ChronicleCoreEditor",
			"PropertyEditor",
			"AssetRegistry",
			"AssetTools",
			"UnrealEd",
			"Slate",
			"SlateCore",
			"DeveloperSettings",
			"InputCore"
		]);
	}
}