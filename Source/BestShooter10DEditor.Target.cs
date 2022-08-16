// Best Shooter Ever

using UnrealBuildTool;
using System.Collections.Generic;

public class BestShooter10DEditorTarget : TargetRules
{
	public BestShooter10DEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "BestShooter10D" } );
	}
}
