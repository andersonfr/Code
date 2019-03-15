// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORZ_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	float cameraDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<class AMainCameraActor> mainCameraClass;

	class AMainCameraActor* mainCamera;




public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void RotateCharacter(FVector& mouseLocation);
};
