// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class TESTRPG_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHealthBar(const int32 CurrentHealth, const int32 TotalHealth);

	UFUNCTION()
	void UpdateEnemyState(FText State);

	UFUNCTION(BlueprintImplementableEvent)
	void ShowCurrentTextHealth(int32 HitHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor BarColor = FLinearColor::Red;

private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* HealthValue;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* EnemyState;
};
