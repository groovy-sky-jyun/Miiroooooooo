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
	TArray<bool> bIsUsedInventory; //�κ��丮 ĭ ��ȣ (��� ������ Ȯ��)

	UPROPERTY()
	TArray<FName> ItemInventory; //�κ��丮 ĭ ��ȣ - ������ �̸� (��Ī)

	UPROPERTY(VisibleAnywhere)
	TMap<FName, int32> OwnItemList; //<�������̸�,��������>

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
	TMap<EItemName, float> ItemProbabilisticInfo; //<�������̸�,Ȯ��>

	UPROPERTY(VisibleAnywhere)
	float ProbabilitySum; //Ȯ����

	UPROPERTY(VisibleAnywhere, Category = "ItemTable")
	UDataTable* ItemClassData;

	UFUNCTION()
	void SetItemClassData();

	UPROPERTY(VisibleAnywhere)
	TMap<FName, ABaseItem*> ItemClassInfo; //<������ �̸�, ������ Ŭ���� ��ü>


private:
	UPROPERTY()
	TObjectPtr<class AMiiroooPlayerController> PlayerController;

	UFUNCTION()
	UTexture2D* GetItemTexture(FName ItemName);

	UFUNCTION()
	FName EnumValueToFName(EItemName Value);
};
