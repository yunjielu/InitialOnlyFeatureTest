// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class InitialOnlyFeatureEditorTarget : TargetRules
{
	public InitialOnlyFeatureEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("InitialOnlyFeature");
	}
}
