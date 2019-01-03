// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class StudyRPG_Rev2Target : TargetRules
{
	public StudyRPG_Rev2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "StudyRPG_Rev2" } );
	}
}
