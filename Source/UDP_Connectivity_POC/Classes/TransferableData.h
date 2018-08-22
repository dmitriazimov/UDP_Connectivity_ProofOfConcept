// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TransferableData.generated.h"

USTRUCT(BlueprintType)
struct UDP_CONNECTIVITY_POC_API FTransferableData
{
	GENERATED_BODY()
	
public:	

	FTransferableData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data") FString time_stamp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data") int count;

};

FORCEINLINE FArchive& operator<<(FArchive &archive, FTransferableData& data) 
{
	archive << data.time_stamp;
	archive << data.count;

	return archive;
}