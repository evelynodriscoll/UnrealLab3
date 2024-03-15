// Copyright Epic Games, Inc. All Rights Reserved.


#include "Lab3CharacterGameModeBase.h"


ALab3CharacterGameModeBase::ALab3CharacterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALab3CharacterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ALab3CharacterGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

