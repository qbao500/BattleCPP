// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UMasterShip.h"

#include "CarrierShip.generated.h"

/**
 * 
 */
UCLASS()
class BATTLECPP_API UCarrierShip: public UMasterShip
{
	GENERATED_BODY()
	
public:
	UCarrierShip();
	~UCarrierShip();
};
