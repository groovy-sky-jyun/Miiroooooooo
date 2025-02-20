// Fill out your copyright notice in the Description page of Project Settings.


#include "MiiroooPlayerController.h"
#include "HUDWidget.h"

void AMiiroooPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMiiroooPlayerController::ShowHUDWidget()
{
	if (BP_HUDWidget!=nullptr)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
}

void AMiiroooPlayerController::HideHUDWidget()
{
	HUDWidget->RemoveFromParent(); //화면에서 제거
	HUDWidget->Destruct(); //객체 삭제
}

void AMiiroooPlayerController::AddItemToInventory(FName ItemName, UTexture2D* Texture)
{
	HUDWidget->AddItem(ItemName, Texture);
}

void AMiiroooPlayerController::UpdateItemToInventory(FName ItemName, int Count)
{
	HUDWidget->UpdateItemCount(ItemName, Count);
}
