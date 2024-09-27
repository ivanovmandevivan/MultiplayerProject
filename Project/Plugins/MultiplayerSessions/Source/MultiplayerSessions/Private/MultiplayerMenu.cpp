#include "MultiplayerMenu.h"

// Runtime -> UMG
#include "Components/Button.h"

// MultiplayerSessions -> MultiplayerSessions
#include "MultiplayerSessionsSubSystem.h"

void UMultiplayerMenu::SetupMenu(const int32 InNumPublicConnections, const FString& InTypeOfMatch)
{
    NumPublicConnections = InNumPublicConnections;
    MatchType = InTypeOfMatch;

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
    
    // If this gets fired, the 'MultiplayerSessionsSubSystem' plugin was not enabled or this UUserWidget is used outside of where it is meant to be used.
    check(MultiplayerSessionsSubsystem);

    // Bind Callbacks:
    MultiplayerSessionsSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
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

void UMultiplayerMenu::NativeDestruct()
{
    TearDownMenu();
    Super::NativeDestruct();
}

void UMultiplayerMenu::OnCreateSession(const bool bWasSuccessful)
{
    if (bWasSuccessful)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                15.f,
                FColor::Green,
                FString(TEXT("Session created successfully!"))
            );
        }

        UWorld* World = GetWorld();
        if (nullptr == World)
        {
            UE_LOG(LogTemp, Warning, TEXT("There is no world, unable to host a session, please check that GetWorld() returns a valid world."))
                return;
        }

        World->ServerTravel("/Game/Levels/Lobby?listen");
    }
    else
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1,
                15.f,
                FColor::Red,
                FString(TEXT("Session created unsuccessfully!"))
            );
        }
    }
    
}

void UMultiplayerMenu::HostButtonClicked()
{
    ensureAlways(MultiplayerSessionsSubsystem);
    MultiplayerSessionsSubsystem->CreateSession(NumPublicConnections, MatchType);
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

void UMultiplayerMenu::TearDownMenu()
{
    RemoveFromParent();

    UWorld* World = GetWorld();
    if (!World)
    {
        UE_LOG(LogTemp, Warning, TEXT("There is no world, unable to host a session, please check that GetWorld() returns a valid world."))
        return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!PlayerController)
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not fetch a valid player controller, please check that there is a valid one."))
        return;
    }

    FInputModeGameOnly InpuitModeData;
    PlayerController->SetInputMode(InpuitModeData);
    PlayerController->SetShowMouseCursor(false);

}
