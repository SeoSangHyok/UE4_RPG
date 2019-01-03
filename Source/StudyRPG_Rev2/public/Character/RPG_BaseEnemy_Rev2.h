// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Rpg_TableDef.h"
#include "RPG_BaseEnemy_Rev2.generated.h"

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Chase,
	Attack,
	Back,
	Run

};

UCLASS()
class STUDYRPG_REV2_API ARPG_BaseEnemy_Rev2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPG_BaseEnemy_Rev2();

	virtual void PostInitializeComponents() override;
	virtual void OnConstruction(const FTransform& Transform);

	UFUNCTION(BlueprintCallable, Category = "RPG_BaseEnemy_Rev2")
	bool LoadMonsterByTable(int32 TableID);

	virtual float GetSightRange() { return 1000.0f; }

	const FMonsterInfoTB* GetMonsterInfoTB() { return MonsterInfoTB; }

	const FSkillInfoTB* CurrentUsingSkill = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	FVector GetHomePosition() { return HomePosition; }


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG_BaseEnemy_Rev2")
	float CurrentHP = 0.0f;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RPG_BaseEnemy_Rev2", meta = (AllowPrivateAccess = "true"))
	int MonsterInfoTableID = 1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RPG_BaseEnemy_Rev2", meta = (AllowPrivateAccess = "true"))
	FVector HomePosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG_BaseEnemy_Rev2", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* WeaponComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "RPG_BaseEnemy_Rev2", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ArmorComp;

	const FMonsterInfoTB* MonsterInfoTB = nullptr;
};
