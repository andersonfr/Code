// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCameraActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMainCameraActor::AMainCameraActor()
{
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	springArm->SetupAttachment(RootComponent);
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm, USpringArmComponent::SocketName);
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainCameraActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCameraActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMainCameraActor::PositioningCamera(const FVector& actorLocation, const FVector& mouseLocation)
{
	if (!mouseLocation.ContainsNaN())
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), (actorLocation + mouseLocation) / 2, GetWorld()->DeltaTimeSeconds, 5));
}

