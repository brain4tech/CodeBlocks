// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CodeFormatting.generated.h"

/**
 * 
 */
UCLASS()
class TURINGSANDBOX_API UCodeFormatting : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category="custom")
	static FText FormatText(FString InputFile);

	UFUNCTION(BlueprintCallable, Category="custom")
	static FString SaveTextToFile(FString Content);
};
