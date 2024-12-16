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
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "InventoryItems")
	TArray<ABasicItem*> OverlapItems;

	UPROPERTY(VisibleAnywhere, Category = "InventoryItems")
	TMap<int, int> InventoryItems;

	UPROPERTY(VisibleAnywhere, Category = "InventoryItems")
	TMap<int, int> CurrentItems;

public:
	UFUNCTION(BlueprintCallable)
	void AddOverlapItem(ABasicItem* ItemClass);

	UFUNCTION(BlueprintCallable)
	void RemoveOverlapItem(ABasicItem* ItemClass);


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

public:
	UFUNCTION(BlueprintCallable)
	void PressUseItem(int KeyNum);

	UFUNCTION(BlueprintCallable)
	void UseItemToInventory(int Index, ABasicItem* ItemClass);

private:
	/*Item Use ฐüทร---*/
	UPROPERTY()
	ABasicItem* StaminaClass;

	UPROPERTY()
	ABasicItem* RandomClass;

	UPROPERTY()
	ABasicItem* FireBombClass;

	UPROPERTY()
	ABasicItem* AcidBloodClass;

	UPROPERTY()
	ABasicItem* SprayClass;


	

	
};