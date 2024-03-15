// Copyright (c) 2017 GAM1528. All Rights Reserved.

#pragma once

#include <GameFramework/Actor.h>
#include "ItemBase.generated.h"

//TODO Lab3: Study this Class

UCLASS()
class LAB3CHARACTER_API AItemBase : public AActor
{
	GENERATED_BODY()
	
protected:
	AItemBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

};
