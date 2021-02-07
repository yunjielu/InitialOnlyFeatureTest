// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class InitialOnlyFeatureTarget : TargetRules
{
	public InitialOnlyFeatureTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("InitialOnlyFeature");
	}
}
