// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UDP_Connectivity_POCEditorTarget : TargetRules
{
	public UDP_Connectivity_POCEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "UDP_Connectivity_POC" } );
	}
}
