// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
  // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
  Super::BeginPlay();

  StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);

  // Move platform forward
  // Get current location
  FVector CurrentLocation = GetActorLocation();
  // add vector to that location
  CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
  // Set the vector to that location
  SetActorLocation(CurrentLocation);
  // Send the platform back if gone too far
  // Check how far we've gone
  float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
  // Reverse direction of motion if gone too far

  if (DistanceMoved > MoveDistance)
  {
    float OverShoot = DistanceMoved - MoveDistance;
    FVector MoveDirection = PlatformVelocity.GetSafeNormal();
    StartLocation = StartLocation + MoveDirection * MoveDistance;
    SetActorLocation(StartLocation);
    PlatformVelocity = -PlatformVelocity;

    UE_LOG(LogTemp, Display, TEXT("COnfigured Moved Distance: %f"), OverShoot);
  }
}
