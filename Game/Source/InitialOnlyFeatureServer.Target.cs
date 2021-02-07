// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class InitialOnlyFeatureServerTarget : TargetRules
{
	public InitialOnlyFeatureServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		ExtraModuleNames.Add("InitialOnlyFeature");
	}
}
