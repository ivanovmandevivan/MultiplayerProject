#include "MultiplayerMenu.h"

// Runtime -> UMG
#include "Components/Button.h"

// MultiplayerSessions -> MultiplayerSessions
#include "MultiplayerSessionsSubSystem.h"

void UMultiplayerMenu::SetupMenu()
{
    AddToViewport();
    SetVisibility(ESlateVisibility::Visible);
    SetIsFocusable(true);

    UWorld* World = GetWorld();
    if (!ensureAlwaysMsgf(nullptr != World, TEXT("Unable to fetch a valid world for the Multiplayer Menu Widget.")))
    {
        return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensureAlwaysMsgf(nullptr != PlayerController, TEXT("Unable to get first player controller from World.")))
    {
        return;
    }

    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    PlayerController->SetInputMode(InputModeData);

    // Get Multiplayer Session Subsystem:
    UGameInstance* GameInstance = GetGameInstance();
    if (!ensureAlwaysMsgf(nullptr != GameInstance, TEXT("Unable to get game instance, therefore can't fetch MultiplayerSessionSubSystem.")))
    {
        return;
    }

    MultiplayerSessionsSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionsSubSystem>();
}

bool UMultiplayerMenu::Initialize()
{
    if (!Super::Initialize())
    {
        return false;
    }

    if (!HostButton || !JoinButton)
    {
        return false;
    }

    HostButton->OnClicked.AddDynamic(this, &ThisClass::HostButtonClicked);
    JoinButton->OnClicked.AddDynamic(this, &ThisClass::JoinButtonClicked);

    return true;
}

void UMultiplayerMenu::HostButtonClicked()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            15.f,
            FColor::Yellow,
            FString(TEXT("Host Button Clicked!"))
        );
    }

    ensureAlways(MultiplayerSessionsSubsystem);
    MultiplayerSessionsSubsystem->CreateSession(4, FString("FreeForAll"));
}

void UMultiplayerMenu::JoinButtonClicked()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            15.f,
            FColor::Yellow,
            FString(TEXT("Join Button Clicked!"))
        );
    }
}
