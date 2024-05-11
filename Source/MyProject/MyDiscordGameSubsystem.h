// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DiscordGame/DiscordGameSubsystem.h"
#include "MyDiscordGameSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMyDiscordGameSubsystem : public UDiscordGameSubsystem
{
	GENERATED_BODY()
public:
	static UMyDiscordGameSubsystem* Get() { return const_cast<UMyDiscordGameSubsystem*>(Cast<UMyDiscordGameSubsystem>(UDiscordGameSubsystem::Get())); }

	static UMyDiscordGameSubsystem* GetChecked() {
		UMyDiscordGameSubsystem* Subsystem = Get();
		check(Subsystem);
		return Subsystem;
	}
	FDateTime GameStart;

	UMyDiscordGameSubsystem();

	virtual void NativeOnDiscordCoreCreated() override;
	virtual void NativeOnDiscordCoreReset() override;

	bool UpdateActivity();

	UFUNCTION(BlueprintCallable, Category = "Discord Integration")
	void UpdateDiscordActivity(FString Details, FString State, FString LargeImageName, FString LargeText, FString SmallImageName, FString SmallText);

};


