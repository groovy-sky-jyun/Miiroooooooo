// Fill out your copyright notice in the Description page of Project Settings.


#include "MiirooooGameInstance.h"
#include "Engine/GameInstance.h"


UMiirooooGameInstance::UMiirooooGameInstance()
{
}

void UMiirooooGameInstance::Init()
{
	Super::Init();
	SetUsableItemTotal();
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

void UMiirooooGameInstance::SetUsableItemTotal()
{
	TArray<FItemInformation*> Rows;
	ItemData->GetAllRows<FItemInformation>(TEXT("ItemDataTable"), Rows);
	
	int32 UsableItemCount = 0;

	for (FItemInformation* Row : Rows)
	{
		if (Row->ItemType == EItemType::Usable)
		{
			UsableItemCount++;
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
