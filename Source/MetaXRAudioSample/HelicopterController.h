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

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "HelicopterController.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class METAXRAUDIOSAMPLE_API UHelicopterController : public UStaticMeshComponent {
  GENERATED_BODY()

 public:
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float RigidBodyMass;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float RigidBodyDrag;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float RigidBodyAngularDrag;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float Force;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float Torque;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float FloatAmplitude;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float FloatFrequency;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float Straightness;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float LookAtSmoothness;

  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  float IntervalTime;

  /** Add transforms here to use them as checkpoints,
      the goal position and lookat will be driven by
      their position and forward vectors. */
  UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Helicopter Flight")
  TArray<AActor*> Checkpoints;

 private:
  AActor* Goal = nullptr;
  AActor* GoalLookAt = nullptr;
  UPrimitiveComponent* RigidBody = nullptr;

  int TargetCheckpointN = 0;
  int NextCheckpointN = 1;
  float Timer = 0;
  bool FollowCheckpoints = false;
  FVector FloatZPos;
  FVector UpAim;

  // Sets default values for this component's properties
  UHelicopterController();

  float CalculateAngle(const FVector& Left, const FVector& Right);

 protected:
  // Called when the game starts
  virtual void BeginPlay() override;

 public:
  // Called every frame
  virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

  virtual void AsyncPhysicsTickComponent(float DeltaTime, float SimTime) override;
};
