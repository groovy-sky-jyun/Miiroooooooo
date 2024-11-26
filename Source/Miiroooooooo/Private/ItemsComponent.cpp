// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemsComponent.h"

// Sets default values for this component's properties
UItemsComponent::UItemsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemsComponent::BeginPlay()
{
	Super::BeginPlay();

	//아이템 개수 초기화
	Items.Add(1, 0);
	Items.Add(2, 0);
	Items.Add(3, 0);
	Items.Add(4, 0);
	Items.Add(5, 0);
	Items.Add(6, 0);
	Items.Add(7, 0);
	Items.Add(8, 0);
	Items.Add(9, 0);
	Items.Add(10, 0);
	Items.Add(11, 0);
	Items.Add(12, 0);
	
}


// Called every frame
void UItemsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItemsComponent::AddItems(int32 Number)
{
	//Count 개수 증가
	if(Items.Contains(Number)&& Number!=2)
		Items.Add(Number, Items[Number]+1);

	//RandomPotionItem Liquid Type의 개수 증가는 여기에서만 관리
	if (Number >= 8 && Number <= 12) {
		int32 Count = Items[2]+1;
		Items.Add(2, Count);
	}
		
}

int32 UItemsComponent::GetItemCount(int32 Number)
{
	if (Items.Contains(Number)) {
		if (Number >= 8 && Number <= 12)
			return Items[2];
		else
			return Items[Number];
	}

	return int32();
}

