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
	
	Heap p = Heap();
	p.Insert(Node(4));
	p.Insert(Node(3));
	p.Insert(Node(15));
	p.Insert(Node(7));
	p.Insert(Node(2));
	for (int i = 0; i < 4; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT(" %d "), p.GetMin().index);
		p.DeleteMin();
	}
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

