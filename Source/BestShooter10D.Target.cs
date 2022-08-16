// Best Shooter Ever

using UnrealBuildTool;
using System.Collections.Generic;

public class BestShooter10DTarget : TargetRules
{
	public BestShooter10DTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "BestShooter10D" } );
	}
}
