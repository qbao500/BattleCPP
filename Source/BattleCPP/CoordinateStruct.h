// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoordinateStruct.generated.h"

USTRUCT(BlueprintType)
struct FCoordinateStruct
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly)
	int32 Row;
	UPROPERTY(VisibleInstanceOnly)
	int32 Column;
};
