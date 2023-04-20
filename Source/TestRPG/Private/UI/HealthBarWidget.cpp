// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
void UHealthBarWidget::NativeConstruct()
{
	HealthBar->SetPercent(1);
	HealthBar->SetFillColorAndOpacity(BarColor);

	Super::NativeConstruct();
}

void UHealthBarWidget::UpdateHealthBar(const int32 CurrentHealth, const int32 TotalHealth)
{
	const FText HealthText = FText::Format(FText::FromString(TEXT("{0} / {1}")), CurrentHealth, TotalHealth);
	HealthValue->SetText(HealthText);
	
	const float HealthPercentage = static_cast<float>(CurrentHealth) / TotalHealth;
	const int32 HitHealth = FMath::RoundToFloat((TotalHealth * 0.01f) * ((HealthBar->GetPercent() - HealthPercentage * 100)));

	HealthBar->SetPercent(HealthPercentage);

	if (HitHealth > 0)
	{
		ShowCurrentTextHealth(-HitHealth);
	}
}

void UHealthBarWidget::UpdateEnemyState(FText State)
{
	EnemyState->SetText(State);
}