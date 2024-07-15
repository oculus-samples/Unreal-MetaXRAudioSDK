/*
Copyright (c) Meta Platforms, Inc. and affiliates.
All rights reserved.

Licensed under the Oculus SDK License Agreement (the "License");
you may not use the Oculus SDK except in compliance with the License,
which is provided at the time of installation or download, or which
otherwise accompanies this software in either electronic or hard copy form.

You may obtain a copy of the License at

https://developer.oculus.com/licenses/oculussdk/

Unless required by applicable law or agreed to in writing, the Oculus SDK
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "HelicopterController.h"

// Sets default values for this component's properties
UHelicopterController::UHelicopterController() {
  // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
  // off to improve performance if you don't need them.
  PrimaryComponentTick.bCanEverTick = true;

  RigidBodyMass = 1;
  RigidBodyDrag = 0.5f;
  RigidBodyAngularDrag = 0.5f;
  Force = 500.f;
  Torque = 500.f;
  FloatAmplitude = .5f;
  FloatFrequency = .5f;
  Straightness = 20.f;
  LookAtSmoothness = 1.0f;
  IntervalTime = 4.95f;
}

float UHelicopterController::CalculateAngle(const FVector& Left, const FVector& Right) {
  FVector leftNormal = Left.GetUnsafeNormal();
  FVector rightNormal = Right.GetUnsafeNormal();
  return FMath::Acos(FVector::DotProduct(leftNormal, rightNormal));
}

// Called when the game starts
void UHelicopterController::BeginPlay() {
  Super::BeginPlay();

  SetAsyncPhysicsTickEnabled(true);

  // Create objects
  Goal = GetWorld()->SpawnActor<AActor>();
  Goal->AddComponentByClass(USceneComponent::StaticClass(), false, FTransform::Identity, false);
  GoalLookAt = GetWorld()->SpawnActor<AActor>();
  GoalLookAt->AddComponentByClass(USceneComponent::StaticClass(), false, FTransform::Identity, false);

  RigidBody = dynamic_cast<UPrimitiveComponent*>(GetOwner()->GetRootComponent());
  if (!RigidBody) {
    UE_LOG(LogTemp, Error, TEXT("Root component is not derived from UPrimitiveComponent"));
  }

  SetMassOverrideInKg(NAME_None, RigidBodyMass);
  SetLinearDamping(RigidBodyDrag);
  SetAngularDamping(RigidBodyAngularDrag);
  if (Checkpoints.Num() > 1) {
    FollowCheckpoints = true;
    FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, false);
    GoalLookAt->AttachToActor(Goal, FAttachmentTransformRules::KeepWorldTransform);
    GoalLookAt->SetActorRelativeLocation(FVector::ForwardVector * 2);
    Goal->SetActorLocation(FMath::Lerp(GetComponentLocation(), Checkpoints[TargetCheckpointN]->GetActorLocation(), .5f));
    SetWorldRotation(FMath::Lerp(GetComponentRotation(), Goal->GetActorRotation(), LookAtSmoothness * GetWorld()->GetDeltaSeconds()));
  }
}

// Called every frame
void UHelicopterController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // Rotation
  UpAim = FloatZPos + FVector::UpVector * Straightness * 100;
  if (FollowCheckpoints) {
    Timer += DeltaTime;
    Goal->SetActorLocation(FMath::Lerp(
        Checkpoints[TargetCheckpointN]->GetActorLocation(), Checkpoints[NextCheckpointN]->GetActorLocation(), Timer / IntervalTime));
    if (Timer >= IntervalTime) {
      Timer = 0;
      // If it's not the case to restart the looping trajectory...
      if (NextCheckpointN == 0) {
        TargetCheckpointN = 0;
        NextCheckpointN = 1;
      }
      //...increment the checkpoints...
      else {
        TargetCheckpointN++;
        NextCheckpointN = TargetCheckpointN + 1;
        //...untill you reach the last one when we have to aim to the starting point.
        if (NextCheckpointN == Checkpoints.Num()) {
          TargetCheckpointN = Checkpoints.Num() - 1;
          NextCheckpointN = 0;
        }
      }
    }
    FVector lerpedAim = FMath::Lerp(
        FVector::VectorPlaneProject(Checkpoints[TargetCheckpointN]->GetActorForwardVector(), FVector::UpVector),
        FVector::VectorPlaneProject(Checkpoints[NextCheckpointN]->GetActorForwardVector(), FVector::UpVector),
        Timer / IntervalTime);
    FRotator lookAt = FRotationMatrix::MakeFromXZ(lerpedAim, UpAim - GetComponentLocation()).Rotator();
    FRotator lerpedRotator = FMath::Lerp(GetComponentRotation(), lookAt, LookAtSmoothness * DeltaTime);
    // SetWorldRotation(lerpedRotator, false, nullptr, ETeleportType::TeleportPhysics);
  } else {
    FRotator lookAt =
        FRotationMatrix::MakeFromXZ(GoalLookAt->GetActorLocation() - GetComponentLocation(), UpAim - GetComponentLocation()).Rotator();
    FRotator lerpedRotator = FMath::Lerp(GetComponentRotation(), lookAt, LookAtSmoothness * DeltaTime);
    // SetWorldRotation(lerpedRotator, false, nullptr, ETeleportType::TeleportPhysics);
    if (GEngine)
      GEngine->AddOnScreenDebugMessage(10, 5.0f, FColor::White, GetComponentVelocity().ToString());
  }
}

void UHelicopterController::AsyncPhysicsTickComponent(float DeltaTime, float SimTime) {
  Super::AsyncPhysicsTickComponent(DeltaTime, SimTime);

  FloatZPos = Goal->GetActorLocation() +
      FVector(
          FMath::PerlinNoise2D({DeltaTime * FloatFrequency, 0}) - .5f,
          FMath::PerlinNoise2D({DeltaTime * FloatFrequency, 1}) - .5f,
          FMath::PerlinNoise2D({DeltaTime * FloatFrequency, 2}) - .5f) *
          FloatAmplitude * 100;

  // Movement
  float chasingForce = FVector::Distance(GetComponentLocation(), Goal->GetActorLocation());
  FVector direction = FloatZPos - GetComponentLocation();
  AddForce(direction.GetUnsafeNormal() * chasingForce * Force);

  // Rotation

  // FVector lerpedAim = FMath::Lerp(
  //    FVector::VectorPlaneProject(Checkpoints[TargetCheckpointN]->GetActorForwardVector(), FVector::UpVector),
  //    FVector::VectorPlaneProject(Checkpoints[NextCheckpointN]->GetActorForwardVector(), FVector::UpVector),
  //    Timer / IntervalTime);

  float torqueScaling = CalculateAngle(GetForwardVector(), direction) / PI;
  FRotator rotation = direction.Rotation() - GetComponentLocation().Rotation();
  AddTorqueInDegrees(Torque * torqueScaling * rotation.Euler());

  if (GEngine) {
    GEngine->AddOnScreenDebugMessage(10, 5.0f, FColor::White, "Velocity " + GetPhysicsLinearVelocity().ToString());
    GEngine->AddOnScreenDebugMessage(11, 5.0f, FColor::White, "Angular Velocity " + GetPhysicsAngularVelocityInDegrees().ToString());
    GEngine->AddOnScreenDebugMessage(12, 5.0f, FColor::White, "Angular Scaling " + FString::SanitizeFloat(torqueScaling));
  }
}
