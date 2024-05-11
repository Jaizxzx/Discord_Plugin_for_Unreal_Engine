// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDiscordGameSubsystem.h"

UMyDiscordGameSubsystem::UMyDiscordGameSubsystem()
{
	// Application ID on the discord dev dashboard
	ClientId = 1238846011338657833;
	//ClientId = AppId;
	MinimumLogLevel = discord::LogLevel::Debug;
	CreateRetryTime = 5.0f;
}

void UMyDiscordGameSubsystem::NativeOnDiscordCoreCreated()
{
	discord::Activity Activity{};
	Super::NativeOnDiscordCoreCreated();
	UpdateActivity();
}

void UMyDiscordGameSubsystem::NativeOnDiscordCoreReset()
{
	Super::NativeOnDiscordCoreReset();
}

bool UMyDiscordGameSubsystem::UpdateActivity()
{
	bool bResult{ false };
		if (this->IsDiscordRunning()) {
			bResult = true;
			discord::Activity Activity{};
			Activity.SetType(discord::ActivityType::Playing);
			Activity.SetApplicationId(ClientId);
			Activity.SetSupportedPlatforms(static_cast<uint32_t>(discord::ActivitySupportedPlatformFlags::Desktop));
			discord::ActivityTimestamps& Timestamps = Activity.GetTimestamps();
			GameStart = FDateTime::UtcNow();
			Timestamps.SetStart(GameStart.ToUnixTimestamp());
			discord::ActivityAssets& Assets = Activity.GetAssets();
			// Image Name Should mach the one which is set in the discord dev applications rich presence menu
			Assets.SetLargeImage("gotenks_ssj_logo");
			Assets.SetLargeText("Goooootenkss");

			DiscordCore().ActivityManager().UpdateActivity(Activity, [this](discord::Result Result)
				{
					const FString RequestDescription(TEXT("Updating Activity"));
					LogDiscordResult(Result, RequestDescription);
				});
		}
	return bResult;
}

void UMyDiscordGameSubsystem::UpdateDiscordActivity(FString Details, FString State, FString LargeImageName, FString LargeText, FString SmallImageName, FString SmallText)
{
	if (this->IsDiscordRunning()) {
		discord::Activity Activity{};
		Activity.SetType(discord::ActivityType::Playing);
		Activity.SetApplicationId(ClientId);
		Activity.SetState(TCHAR_TO_ANSI(*State));
		const char* details = TCHAR_TO_ANSI(*Details);
		Activity.SetDetails(details);
		Activity.SetSupportedPlatforms(static_cast<uint32_t>(discord::ActivitySupportedPlatformFlags::Desktop));
		discord::ActivityTimestamps& Timestamps = Activity.GetTimestamps();
		Timestamps.SetStart(GameStart.ToUnixTimestamp());

		discord::ActivityAssets& Assets = Activity.GetAssets(); // Declare and initialize Assets

		Assets.SetLargeImage(StringCast<ANSICHAR>(*LargeImageName).Get());
		Assets.SetLargeText(StringCast<ANSICHAR>(*LargeText).Get());
		Assets.SetSmallImage(StringCast<ANSICHAR>(*SmallImageName).Get());
		Assets.SetSmallText(StringCast<ANSICHAR>(*SmallText).Get());

		DiscordCore().ActivityManager().UpdateActivity(Activity, [this](discord::Result Result)
			{
				const FString RequestDescription(TEXT("Updating Activity"));
				LogDiscordResult(Result, RequestDescription);
			});
	}
}



