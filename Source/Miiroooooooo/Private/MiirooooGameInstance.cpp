// Fill out your copyright notice in the Description page of Project Settings.


#include "MiirooooGameInstance.h"
#include "Engine/GameInstance.h"
#include "ItemStructure.h"
#include "Math/UnrealMathUtility.h"


UMiirooooGameInstance::UMiirooooGameInstance()
{
}

void UMiirooooGameInstance::Init()
{
	Super::Init();
	SetUsableItemFromData();
}

UTexture2D* UMiirooooGameInstance::GetItemTexture(FName ItemName)
{
	FItemInformation* Row = ItemData->FindRow<FItemInformation>(ItemName, TEXT("ItemStructure"));
	if (Row)
	{
		return Row->Texture;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HUDWidget : Can't find ItemName from DataTable"));
		return nullptr;
	}
}

void UMiirooooGameInstance::SetUsableItemFromData()
{
	TArray<FItemInformation*> Rows;
	check(ItemData);
	ItemData->GetAllRows<FItemInformation>(TEXT("ItemDataTable"), Rows);
	
	int32 UsableItemCount = 0;

	for (FItemInformation* Row : Rows)
	{
		if (Row->ItemType == EItemType::Usable)
		{
			UsableItemCount++;

			EItemName Name = Row->ItemName;
			float Probability = Row->Probability;
			ProbabilitySum += Probability;
			UsableItemProbabilistic.Add(Name, Probability);
		}
	}
	
	UsableItemTotal = UsableItemCount;
}

int32 UMiirooooGameInstance::GetUsableItemTotal()
{
	return UsableItemTotal;
}

void UMiirooooGameInstance::AddItem(FName ItemName)
{
	if (ItemList.Contains(ItemName))
	{
		ItemList[ItemName]++;
	}
	else
	{
		ItemList.Add(ItemName,1);
	}

	check(HUDWidgetComponent);
	//HUDWidgetComponent->
}

void UMiirooooGameInstance::UseItem(FName ItemName)
{
	if (ItemList.Contains(ItemName) && ItemList[ItemName]>0)
	{
		ItemList[ItemName]--;
	}
}

bool UMiirooooGameInstance::HasItemInInventory(FName ItemName)
{
	if (ItemList.Contains(ItemName))
	{
		return true;
	}
	return false;
}

AUsableItem* UMiirooooGameInstance::GetRandomItem()
{
	EItemName Name = GetProbabilisticItem();
	
	TArray<FUsableItemClass*> Rows;
	check(ItemClass);
	ItemClass->GetAllRows<FUsableItemClass>(TEXT("ItemDataTable"), Rows);

	for (FUsableItemClass* Row : Rows)
	{
		if (Row->ItemName == Name)
		{
			return Row->ItemClass;
		}
	}

	return nullptr;
}

EItemName UMiirooooGameInstance::GetProbabilisticItem()
{
	if (ProbabilitySum > 0.f)
	{
		// 구간 0 ~ ProbabilitySum-1 중 랜덤으로 숫자 하나 뽑음
		int32 RandValue = FMath::RandRange(0.f, (ProbabilitySum*100)-1);
		// 그 구간에 맞는 확률을 가진 아이템을 찾아 반환
		int32 Panel = 0.f;
		for (auto &UsableItem : UsableItemProbabilistic)
		{
			Panel += UsableItem.Value * 100;
			if (RandValue < Panel)
			{
				return UsableItem.Key;
			}
		}
	}
	return EItemName();
}

void UMiirooooGameInstance::IncreasePlayerHealth(int32 Value)
{
	PlayerHealth += Value;
}

void UMiirooooGameInstance::DecreasePlayerHealth(int32 Value)
{
	PlayerHealth -= Value;
}

int32 UMiirooooGameInstance::GetPlayerHealth()
{
	return PlayerHealth;
}

bool UMiirooooGameInstance::IsHealthFull()
{
	if (PlayerHealth >= 100)
	{
		return true;
	}
	return false;
}
