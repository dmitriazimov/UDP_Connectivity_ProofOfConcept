// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UDP_Connectivity_POCTarget : TargetRules
{
	public UDP_Connectivity_POCTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "UDP_Connectivity_POC" } );
	}
}
