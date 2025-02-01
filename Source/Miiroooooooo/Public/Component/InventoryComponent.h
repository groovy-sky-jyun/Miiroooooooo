// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HUDWidget.h"
#include "InventoryComponent.generated.h"

class UsableItem;

UCLASS(meta = (BlueprintSpawnableComponent))
class MIIROOOOOOOO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	/*
public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "InventoryItems")
	TArray<AUsableItem*> OverlapItems;

	UPROPERTY(VisibleAnywhere, Category = "InventoryItems")
	TMap<int, int> InventoryItems;

	UPROPERTY(VisibleAnywhere, Category = "InventoryItems")
	TMap<int, int> CurrentItems;

public:
	UFUNCTION(BlueprintCallable)
	void AddOverlapItem(AUsableItem* ItemClass);

	UFUNCTION(BlueprintCallable)
	void RemoveOverlapItem(AUsableItem* ItemClass);


public: 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHUDWidget* ItemWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ItemClass") 
	UDataTable* ItemTable; 

	//UFUNCTION(BlueprintCallable)
	//void AddToInventory();

private:
	UFUNCTION(BlueprintCallable)
	void AddItem(FItemStructure ItemStructure);

	//UFUNCTION(BlueprintCallable)
	//FItemStructure GetRnadItem(EItem ItemType);

	UFUNCTION(BlueprintCallable)
	AUsableItem* CloseToPlayer();

public:
	UFUNCTION(BlueprintCallable)
	void PressUseItem(int KeyNum);

	UFUNCTION(BlueprintCallable)
	void UseItemToInventory(int Index, AUsableItem* ItemClass);

private:
	Item Use ฐüทร
	UPROPERTY()
	AUsableItem* HealthClass;

	UPROPERTY()
	AUsableItem* RandomClass;

	UPROPERTY()
	AUsableItem*  FireBombClass;

	UPROPERTY()
	AUsableItem* AcidBloodClass;

	UPROPERTY()
	AUsableItem* SprayClass;


	*/
};