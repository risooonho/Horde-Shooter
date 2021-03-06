// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SWeapon.generated.h"

// Contains Information of a single hitscan weapon linetrace
USTRUCT()
struct FHitScanTrace {
	GENERATED_BODY()

public:
	UPROPERTY()
	TEnumAsByte<EPhysicalSurface> SurfaceType;
	
	UPROPERTY()
	FVector_NetQuantize TraceTo;
};

UCLASS()
class HORDESHOOTER_API ASWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASWeapon();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartFire();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StopFire();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float WeaponRange;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	float CriticalMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<class UDamageType> DamageType;

	// Name of the socket that MuzzleEffect will be attached to
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;

	// Visual Effect that will be spawned at the barrel of the Gun
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* MuzzleEffect;

	// Visual Effect that will be spawned at hit location of the bullet
	// If the Surface hit is Default
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* DefaultImpactEffect;

	// Visual Effect that will be spawned at hit location of the bullet
	// If the Surface hit is Vulnerable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	class UParticleSystem* VulnerableImpactEffect;

	// Sound that will be played on Fire
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	class USoundBase* FireSound;

	// Camera shake class that will be played on Fire
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<class UCameraShake> CameraShake;

	FTimerHandle TimerHandle_WeaponFire;

	// Holds the last time this weapon was shot
	float LastFiredTime;

	// Fire rate of the weapon. Should be used as Bullets Per Minute.
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float RateOfFire;

	// Helper variable to determine the amount of time between shots.
	// 60 / ROF = FireDelay
	float FireDelay;

	UPROPERTY(ReplicatedUsing = OnRep_HitScanTrace)
	FHitScanTrace HitScanTrace;

	// Bullet spread in degrees
	UPROPERTY(EditDefaultsOnly, Category = "Weapon", Meta = (ClampMin = 0.f))
	float BulletSpread;

protected:

	// Plays the fire effect at the weapon muzzle
	void PlayFireEffects();

	void PlayImpactEffect(EPhysicalSurface SurfaceType, FVector ImpactPoint);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();

	// ASK the server to run the Fire function
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerFire();

	UFUNCTION()
	void OnRep_HitScanTrace();
};
