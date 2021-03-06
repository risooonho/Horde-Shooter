// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

UCLASS()
class HORDESHOOTER_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Weapon fire input function
	UFUNCTION(BlueprintCallable, Category = "Player")
	void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Player")
	void StopFire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* CameraComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USHealthComponent* HealthComp;

	// Default FOV get by the camera component on BeginPlay()
	float DefaultFOV;

	// FOV Value when player zooms the camera.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay")
	float ZoomedFOV;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay", meta = (ClampMin = 0.1, ClampMax = 100))
	float ZoomInterpSpeed;

	bool bWantsToZoom;

	UPROPERTY(Replicated)
	class ASWeapon* CurrentWeapon;

	// Default weapon of the character. Spawned on BeginPlay.
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class ASWeapon> DefaultWeapon;

	// Name of the socket the weapon will be attached to.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponSocket;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Gameplay")
	bool bIsDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Overwritten so the line trace (Used by the Weapon)
	// Comes from the camera instead Character's Eye View Point.
	virtual FVector GetPawnViewLocation() const override;

	// Movement input functions
	void MoveForward(float Value);
	void MoveRight(float Value);

	// Crouch input functions
	void BeginCrouch();
	void EndCrouch();

	// Jump input functions
	void BeginJump();
	void EndJump();

	// Zoom input functions
	void BeginZoom();
	void EndZoom();

	// Spawns the default weapon of the character.
	// See DefaultWeapon.
	void SpawnDefaultWeapon();

	// Function called by HealthComponent when broadcasted
	// Handles the Health change of the Character
	UFUNCTION()
	void OnHealthChanged(class USHealthComponent* HealthComponent, float Health, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
