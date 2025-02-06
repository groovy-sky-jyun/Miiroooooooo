// Fill out your copyright notice in the Description page of Project Settings.

#include "Pit.h"

void APit::SetDamage()
{
	Damage = 20;
}

void APit::OverlapToPlayer()
{
	DamageThePlayer();
}

void APit::DamageThePlayer()
{
	int32 Value = GetDamage();
	DamagedOnChange.Broadcast(Value);
}
