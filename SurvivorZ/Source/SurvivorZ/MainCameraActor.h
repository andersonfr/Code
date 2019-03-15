// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainCameraActor.generated.h"

UCLASS()
class SURVIVORZ_API AMainCameraActor : public AActor
{
	GENERATED_BODY()

private:
	APlayerController* playerController;

public:	
	// Sets default values for this actor's properties
	AMainCameraActor();
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* camera;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PositioningCamera(const FVector& actorLocation, const FVector& mouseLocation);

};
	