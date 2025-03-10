// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseItem.h"
#include "ItemInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MIIROOOOOOOO_API UItemInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UItemInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UFUNCTION()
	void OverlapItem();

	UFUNCTION()
	void UnOverlapItem();

	UFUNCTION()
	void PickUpAnItem();

	UFUNCTION()
	void PressUseItem(int KeyNum);

private:
	UPROPERTY()
	bool bIsOverlapItem;

	UPROPERTY()
	int32 InventoryTotal = 5;

	UPROPERTY()
	TArray<bool> bIsUsedInventory; //인벤토리 칸 번호 (사용 중인지 확인)

	UPROPERTY()
	TArray<FName> ItemInventory; //인벤토리 칸 번호 - 아이템 이름 (매칭)

	UPROPERTY(VisibleAnywhere)
	TMap<FName, int32> OwnItemList; //<아이템이름,소지개수>

	UFUNCTION()
	EItemName GetRandomItem();

	UFUNCTION()
	void AddItem(FName ItemName);


private:
	UPROPERTY(VisibleAnywhere, Category = "ItemTable")
	UDataTable* ItemData;

	UFUNCTION()
	void SetItemData();

	UPROPERTY(VisibleAnywhere)
	TMap<EItemName, float> ItemProbabilisticInfo; //<아이템이름,확률>

	UPROPERTY(VisibleAnywhere)
	float ProbabilitySum; //확률합

	UPROPERTY(VisibleAnywhere, Category = "ItemTable")
	UDataTable* ItemClassData;

	UFUNCTION()
	void SetItemClassData();

	UPROPERTY(VisibleAnywhere)
	TMap<FName, ABaseItem*> ItemClassInfo; //<아이템 이름, 아이템 클래스 객체>


private:
	UPROPERTY()
	TObjectPtr<class AMiiroooPlayerController> PlayerController;

	UFUNCTION()
	UTexture2D* GetItemTexture(FName ItemName);

	UFUNCTION()
	FName EnumValueToFName(EItemName Value);
};
