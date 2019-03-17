// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlayerController.h"
#include "BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "MainCameraActor.h"
#include "Heap.h"

void ABasePlayerController::BeginPlay()
{
	FInputModeGameAndUI inputMode;
	inputMode.SetHideCursorDuringCapture(false);
	SetInputMode(inputMode);
	FVector clocation = GetCharacter()->GetActorLocation();
	mainCamera = GetWorld()->SpawnActor<AMainCameraActor>(mainCameraClass, clocation, FRotator::ZeroRotator);

	SetViewTarget(mainCamera);
	cameraDistance = (mainCamera->springArm)->TargetArmLength;
}

void ABasePlayerController::Tick(float DeltaTime)
{
	FVector mouseLocation(ForceInit);
	RotateCharacter(mouseLocation);
	mainCamera->PositioningCamera(GetCharacter()->GetActorLocation(), mouseLocation);
}

void ABasePlayerController::RotateCharacter(FVector& mouseLocation)
{
	FVector mouseDirection, characterLocation;
	characterLocation = GetCharacter()->GetActorLocation();
	DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

	FVector targetLocation = mouseDirection * cameraDistance + mouseLocation;
	
	FVector position = FMath::LinePlaneIntersection(mouseLocation, targetLocation, characterLocation, FVector(0, 0, 1));
	FVector direction = (position - characterLocation);
	
	FRotator rotation = FRotator(GetCharacter()->GetActorRotation().Pitch, direction.Rotation().Yaw, GetCharacter()->GetActorRotation().Roll);
	//mouseLocation = position;
	GetCharacter()->SetActorRotation(rotation);

}

