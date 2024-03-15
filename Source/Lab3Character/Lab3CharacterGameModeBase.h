// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Lab3CharacterGameModeBase.generated.h"

class AObjectPool;
/**
 * 
 */
UCLASS()
class LAB3CHARACTER_API ALab3CharacterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

//STEP 3

protected:
	virtual void BeginPlay() override;
	
public:

	ALab3CharacterGameModeBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
