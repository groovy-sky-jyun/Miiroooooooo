// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicItem.h"
#include "ItemStructure.h"
#include "InventoryWidget.h"
#include "InventoryComponent.generated.h"


UCLASS(meta = (BlueprintSpawnableComponent))
class MIIROOOOOOOO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Item Overlap 관련---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InventoryList")
	TArray<ABasicItem*> OverlapItemList;

	UFUNCTION(BlueprintCallable)
	void AddOverlapItem(ABasicItem* ItemClass);

	UFUNCTION(BlueprintCallable)
	void RemoveOverlapItem(ABasicItem* ItemClass);
	//----------------
	
	//Item Add 관련---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InventoryList")
	TMap<FName, int> InventoryList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "InventoryList")
	TArray<FItemStructure> ChestStructureList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryWidget* ItemWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemClass") 
	UDataTable* ItemTable; 

	UFUNCTION(BlueprintCallable)
	void GetStructuresForType(EItem ItemType);

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory();

	UFUNCTION(BlueprintCallable)
	ABasicItem* CloseToPlayer();

	UFUNCTION(BlueprintCallable)
	void AddChestItem();

	UFUNCTION(BlueprintCallable)
	void AddWearItem(ABasicItem* WearItem);

	UFUNCTION(BlueprintCallable)
	void AddItemList(int InventoryIndex, FName RowName);
	//----------------
	
	//Item Use 관련---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="ItemClass")
	ABasicItem* StaminaClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemClass")
	ABasicItem* RandomClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemClass")
	ABasicItem* AcidBloodClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemClass")
	ABasicItem* FireBombClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemClass")
	ABasicItem* SprayClass;

	UFUNCTION(BlueprintCallable)
	void PressUseItem(int KeyNum);

	UFUNCTION(BlueprintCallable)
	void UseItemClass(ABasicItem* Item, int Index);

	UFUNCTION(BlueprintCallable)
	void UpdateItemList(FName RowName);
	//----------------
	

	
};