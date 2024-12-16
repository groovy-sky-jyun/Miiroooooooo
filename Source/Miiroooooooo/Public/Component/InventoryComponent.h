// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryWidget.h"
#include "InventoryComponent.generated.h"

class BasicItem;

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

private:
	//Item Overlap 관련---
	UPROPERTY(VisibleAnywhere, Category = "InventoryItems")
	TArray<ABasicItem*> OverlapItems;

	//Item Add 관련---
	UPROPERTY(VisibleAnywhere, Category = "InventoryItems")
	TMap<int, int> InventoryItems;

public:
	UFUNCTION(BlueprintCallable)
	void AddOverlapItem(ABasicItem* ItemClass);

	UFUNCTION(BlueprintCallable)
	void RemoveOverlapItem(ABasicItem* ItemClass);
	//----------------

public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInventoryWidget* ItemWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemClass") 
	UDataTable* ItemTable; 

	UFUNCTION(BlueprintCallable)
	void AddToInventory();

private:
	UFUNCTION(BlueprintCallable)
	void AddItem(FItemStructure ItemStructure);

	UFUNCTION(BlueprintCallable)
	FItemStructure GetRnadItem(EItem ItemType);

	UFUNCTION(BlueprintCallable)
	ABasicItem* CloseToPlayer();
	//----------------
	
	/*Item Use 관련---
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
	----------------*/
	

	
};